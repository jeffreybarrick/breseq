/*****************************************************************************

AUTHORS

  Jeffrey E. Barrick <jeffrey.e.barrick@gmail.com>
  David B. Knoester

LICENSE AND COPYRIGHT

  Copyright (c) 2008-2010 Michigan State University
  Copyright (c) 2011 The University of Texas at Austin

  breseq is free software; you can redistribute it and/or modify it under the  
  terms the GNU General Public License as published by the Free Software 
  Foundation; either version 1, or (at your option) any later version.

*****************************************************************************/

#ifndef _BRESEQ_IDENTIFY_MUTATIONS_H_
#define _BRESEQ_IDENTIFY_MUTATIONS_H_

#include "common.h"
#include "chisquare.h"
#include "error_count.h"
#include "genome_diff.h"
#include "pileup_base.h"

using namespace std;

namespace breseq {
	      
	/*! Calculate errors in the given BAM file based on reference FAI files.
	 
	 \param bam is the read file generated by breseq.
	 \param fastas is the list of FASTA files that correspond to the reference sequences; generates FAI files as needed.
	 \param output_dir is the directory in which output files will be placed.
	 \param readfiles is a list of read files that were used to build the bam (do not include filename extension)
	 */
  
	void identify_mutations(
                          const Settings& settings,
                          const Summary& summary,
                          const string& bam,
													const string& fasta,
													const string& gd_file,
													const string& output_dir,
													const string& coverage_dir,
                          const vector<double>& deletion_propagation_cutoff,
                          const vector<double>& deletion_seed_cutoff,
													double mutation_cutoff,
                          uint8_t min_qual_score,
                          double polymorphism_cutoff,
                          double polymorphism_frequency_cutoff,
                          const string& error_table_file,
                          bool print_per_position_file
                          );
	
  
  /*! Position base information struct.
	 
   Used for recording observations of bases on different strands.
   
   Note: The "triples" in this struct are to be indexed via the strand, which is
	 either +1 or -1.  As a result, use 1-based indexing, e.g.: unique_cov[1+strand].
	 */
  
  
  struct position_base_info : map<base_char, vector<uint32_t> > {
    
    position_base_info() {
      vector<uint32_t> t;
      t.resize(3,0);
      for(size_t j=0; j<base_list_size; ++j) {
        insert(make_pair(base_char_list[j],t));
      }
      // extra consideration of 'N' necessary
      insert(make_pair('N',t));
    }
    
  };
	
	
	/*! Position coverage struct.
	 
	 Note: The "triples" in this struct are to be indexed via the strand, which is
	 either +1 or -1.  As a result, use 1-based indexing, e.g.: unique_cov[1+strand].
	 Additionally, we use the 1th element as the total field for both strands.
	 */
	struct position_coverage {
		//! Constructor.
		position_coverage() {
			bzero(this,sizeof(position_coverage));
		}

		//! Constructor.
		position_coverage(double v) {
			bzero(this,sizeof(position_coverage));
			unique[0] = v; unique[1] = v; unique[2] = v;
			redundant[0] = v; redundant[1] = v; redundant[2] = v;
		}
		
		position_coverage& operator=(const position_coverage& that) {
			if(this != &that) {
				memcpy(this, &that, sizeof(that));
			}
			return *this;
		}
		
		//! Sum the position coverage fields.
		void sum() {
			unique[1] = unique[0]+unique[2];
			redundant[1] = redundant[0]+redundant[2];
			raw_redundant[1] = raw_redundant[0]+raw_redundant[2];
			total = (int)round(unique[1]) + (int)round(redundant[1]);
		}
		
		double unique[3];
		double redundant[3];
		int raw_redundant[3];
		int total;
	};
	

	/*! Polymorphism data struct.
	 */
	struct polymorphism_data {
		//! Constructor.
		polymorphism_data(uint8_t b, uint8_t q, int s, int32_t f, const covariate_values_t& cv)
		: _base_char(b), _quality(q), _strand(s), _fastq_file_index(f), _cv(cv) {
		}
		
		polymorphism_data(uint8_t b, uint8_t q, int s, int32_t f)
		: _base_char(b), _quality(q), _strand(s), _fastq_file_index(f) {
		}

		base_char _base_char;
		uint8_t _quality;
		int _strand;
		int32_t _fastq_file_index;
    covariate_values_t _cv;
	};

	/*! Polymorphism prediction data struct.
	 */
	struct polymorphism_prediction {
		//! Constructor.
		polymorphism_prediction(double f = 0.0, double l = 0.0, double p = 0.0)
		: frequency(f), log10_base_likelihood(l), p_value(p) {
      log10_e_value = NAN;
		}
		
		double frequency;
		double log10_base_likelihood;
		long double p_value;
    double log10_e_value;
	};	
	
  /*! cDiscreteSNPCaller
	 
	 This class is used to predict SNPs in a single-genome sample.
   
	 */
  
  struct cSNPCall {
    
    cSNPCall() 
    : genotype("N")
    , score(numeric_limits<double>::quiet_NaN())
    {}
    
    string genotype;
    double score;
  };
  
  class cDiscreteSNPCaller {
  public:
    cDiscreteSNPCaller(
                       const string& type, 
                       uint32_t reference_length
                       );
    
    virtual ~cDiscreteSNPCaller() {};

    void add_genotype(const string& genotype, double probability);
    void reset(uint8_t ref_base_index);
    void update(const covariate_values_t& cv, bool obs_top_strand, cErrorTable& et);
    void print();
    
    cSNPCall get_prediction();
    
    vector<double> get_genotype_log10_probabilities() { return _genotype_probability; }
    
  protected:
    uint32_t _observations;      
    string _type;
    vector<double> _genotype_prior;
    vector<double> _genotype_probability;
    vector<vector<base_index> > _genotype_vector;  // holds all possible genotypes as lists of bases
    uint32_t _best_genotype_index;
  };
  
  
	/*! identify_mutations_pileup
	 
	 */
	class identify_mutations_pileup : public breseq::pileup_base {
	public:
		typedef map<string,int> base_count_t;
		typedef map<uint8_t,base_count_t> qual_map_t;
    typedef map<int32_t,qual_map_t> fastq_map_t;
    
    //! Information that is tracked per-sequence.
		struct sequence_info {
			/*! Coverage count table.
			 
			 This is a table of non-deletion reads per position to non-redundancy counts.
			 For example, given unique_only_coverage[i] = x, for all aligned positions p:
			 i is the number of reads that do not indicate a deletion at p
			 x is the number of positions that have no redundancies
			 */
			vector<int> unique_only_coverage;
		};
		
		struct shared_info {
			shared_info() : coverage_unique_total(0), coverage_unique_uncalled(0), coverage_unique_called(0) { }
			int coverage_unique_total;
			int coverage_unique_uncalled;
			int coverage_unique_called;
		};
		
		
		//! Constructor.
		identify_mutations_pileup(
                              const Settings& settings,
                              const Summary& summary,
                              const string& bam,
															const string& fasta,
															const string& output_dir,
															const string& coverage_dir,
                              const vector<double>& deletion_propagation_cutoff,
                              const vector<double>& deletion_seed_cutoffs,
															double mutation_cutoff,
                              uint8_t min_qual_score,
                              double polymorphism_cutoff,
                              double polymorphism_frequency_cutoff,
                              const string& error_table_file,
                              bool print_per_position_file
                            );
				
		//! Destructor.
		virtual ~identify_mutations_pileup();		
		
		//! Called for each alignment.
		virtual void pileup_callback(const pileup& p);
		
    virtual void at_target_start(const uint32_t tid);
    
		//! Called at the end of the pileup.
		virtual void at_target_end(const uint32_t tid);
		
    //! Write the genome diff
    void write_gd(const string& filename)
      { _gd.write(filename); }
    
    
	protected:
		//! Helper method to track deletions.
		void check_deletion_completion(uint32_t position, uint32_t seq_id, const position_coverage& this_position_coverage, double e_value_call);

		//! Helper method to track unknowns.
		void update_unknown_intervals(uint32_t position, uint32_t seq_id, bool base_predicted, bool this_position_unique_only_coverage);

		//! Predict whether there is a significant polymorphism.
    polymorphism_prediction predict_polymorphism (base_char best_base_char, base_char second_best_base_char, vector<polymorphism_data>& pdata );

    //! Predict whether there is a mixed base.
    polymorphism_prediction predict_mixed_base(base_char best_base_char, base_char second_best_base_char, vector<polymorphism_data>& pdata );
    
		//! Find best mixture of two bases and likelihood of producing observed read bases.
    pair<double,double> best_two_base_model_log10_likelihood(base_char best_base_char, base_char second_best_base_char, vector<polymorphism_data>& pdata);

		//! Calculate likelihood of a specific mixture of two bases producing observed read bases.
    double calculate_two_base_model_log10_likelihood (base_char best_base_char, base_char second_best_base_char, const vector<polymorphism_data>& pdata, double best_base_freq);
		
    //! Settings passed at command line
    const Settings& _settings;
		cGenomeDiff _gd; //!< Genome diff.
    uint8_t _min_qual_score; //!< minimum quality score to count base for RA
    vector<double> _deletion_seed_cutoffs; //!< Coverage below which deletions are cutoff.
    vector<double> _deletion_propagation_cutoffs; //!< Coverage above which deletions are cutoff.
		double _mutation_cutoff; //!< log10 e-value cutoff value for mutation predictions.
    double _polymorphism_cutoff; //!< log10 e-value cutoff for predicted polymorphisms.
    double _polymorphism_frequency_cutoff; //!< Frequency cutoff for predicted polymorphisms.
		const string _coverage_dir; //!< Directory in which to store coverage data.
    string _output_dir; //!< Directory containing output

    //! Settings calculated during initialization
		double _log10_ref_length; //!< log10 of the total reference sequence.
    
    //! Initialized once per pileup
    cErrorTable _error_table;
    cDiscreteSNPCaller _snp_caller;
    
		vector<sequence_info> _seq_info; //!< information about each sequence.
		fastq_map_t error_hash; //!< fastq_file_index -> quality map.
		shared_info s; // summary stats
		
		// this is used to output detailed coverage data:
		bool _print_coverage_data; //!< whether or not to print
		ofstream _coverage_data;

		// this is used to output strand and quality information for R to process:
		ofstream _polymorphism_r_input_file;
		
		// these are state variables used by the deletion-prediction method.
		uint32_t _on_deletion_seq_id;
    double _this_deletion_propagation_cutoff;
    double _this_deletion_seed_cutoff;
		uint32_t _last_deletion_start_position;
		uint32_t _last_deletion_end_position;
		uint32_t _last_deletion_redundant_start_position;
		uint32_t _last_deletion_redundant_end_position;
		bool _this_deletion_reaches_seed_value;
		bool _this_deletion_redundant_reached_zero;
		uint32_t _last_position_coverage_printed;
		position_coverage _left_outside_coverage_item;
		position_coverage _left_inside_coverage_item;
		position_coverage _last_position_coverage;
    
		bool _print_per_position_file;
		ofstream _per_position_file;
    
		// these are state variables used by the unknown prediction method.
		uint32_t _last_start_unknown_interval;
	};

  

  
  
} // breseq namespace

#endif
