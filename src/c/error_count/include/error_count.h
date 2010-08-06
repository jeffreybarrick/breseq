#ifndef _BRESEQ_ERROR_COUNT_H_
#define _BRESEQ_ERROR_COUNT_H_

#include <string>
#include <vector>

#include "breseq/pileup.h"

namespace breseq {
	
	/*! Calculate errors in the given BAM file based on reference FAI files.
	 
	 \param bam is the read file generated by breseq.
	 \param fastas is the list of FASTA files that correspond to the reference sequences; generates FAI files as needed.
	 \param output_dir is the directory in which output files will be placed.
	 \param readfiles is a list of read files that were used to build the bam (do not include filename extension)
	 */
	void error_count(const std::string& bam, 
									 const std::string& fasta,
									 const std::string& output_dir,
									 const std::vector<std::string>& readfiles,
                   const bool do_coverage,
                   const bool do_errors);
	
	
	/*! Error-counting class.
	 
	 This class is used by the above error_count() function in order to count errors.
	 */
	class error_count_pileup : public breseq::pileup_base {
	public:
		typedef std::map<std::string,int> base_count_t;
		typedef std::map<uint8_t,base_count_t> qual_map_t;
		typedef std::map<int32_t,qual_map_t> fastq_map_t;
		
    bool m_do_coverage;
    bool m_do_errors;
    
		//! Information that is tracked per-sequence.
		struct sequence_info {
			/*! Coverage count table.
			 
			 This is a table of non-deletion reads per position to non-redundancy counts.
			 For example, given unique_only_coverage[i] = x, for all aligned positions p:
			 i is the number of reads that do not indicate a deletion at p
			 x is the number of positions that have no redundancies
			 */
			std::vector<int> unique_only_coverage;
		};
		
		
		//! Constructor.
		error_count_pileup(const std::string& bam, const std::string& fasta, bool do_coverage, bool do_errors);
		
		//! Destructor.
		virtual ~error_count_pileup();		
		
		//! Called for each alignment.
		virtual int callback(uint32_t tid, uint32_t pos, int n, const bam_pileup1_t *pile);
		
		//! Print coverage distribution.
		void print_coverage(const std::string& output_dir);
		
		//! Print error file.
		void print_error(const std::string& output_dir, const std::vector<std::string>& readfiles);
		
	protected:		
		std::vector<sequence_info> _seq_info; //!< information about each sequence.
		fastq_map_t error_hash; //!< fastq_file_index -> quality map.
	};
	
} // breseq

#endif
