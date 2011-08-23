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

#include "breseq/settings.h"

#include "breseq/anyoption.h"


using namespace std;

namespace breseq
{

	void cReadFiles::Init(const vector<string>& read_file_names)
	{
		//clear any existing info
		this->clear();

		uint32_t on_id = 0;
		uint32_t on_error_group = 0;
		uint32_t on_paired_end_group = 0;

		for (vector<string>::const_iterator it = read_file_names.begin(); it < read_file_names.end(); it++)
		{
			cReadFile rf;
			rf.m_original_file_name = *it;

			rf.m_paired_end_group = on_paired_end_group++;
			rf.m_error_group = on_error_group++;
			rf.m_id = on_id++;

			// create base name
			rf.m_base_name = rf.m_original_file_name;
			// - beginning path
			size_t pos = rf.m_base_name.rfind("/");
			if (pos != string::npos) rf.m_base_name.erase(0, pos + 1);
			// - trailing .fastq, must be at the end of the sequence
			pos = rf.m_base_name.rfind(".fastq");
			if ((pos != string::npos) && (pos = rf.m_base_name.size() - 6))
			{
				rf.m_base_name.erase(pos);
			}
			
      // @JEB - this shouldn't be necessary? - it actually causes some problems.
      // Fix when we move to all C++ TODO
      //- trailing .converted
			pos = rf.m_base_name.rfind(".converted");
      if ((pos != string::npos) && (pos = rf.m_base_name.size() - 10))
			{
				rf.m_base_name.erase(pos);
			}
      
      // set up the map for converting base names to fastq file names to be used
      // check to see whether this is a duplicate
      _assert(read_file_to_fastq_file_name_map.count(rf.m_base_name) == 0, 
              "Read file provided multiple times:\n1)" + read_file_to_fastq_file_name_map[rf.m_base_name] + "\n2)" + rf.m_original_file_name);
      read_file_to_fastq_file_name_map[rf.m_base_name] = rf.m_original_file_name;
      
			this->push_back(rf);
		}
	}
  
  string cReadFiles::base_name_to_read_file_name(const string& base_name)
  {    
    if (read_file_to_converted_fastq_file_name_map.count(base_name)) 
    {
      return read_file_to_converted_fastq_file_name_map[base_name];
    }
    
    assert(read_file_to_fastq_file_name_map.count(base_name));
    
    return read_file_to_fastq_file_name_map[base_name];
  }
  
  // Set up defaults and build paths
  Settings::Settings(const string& _base_output_path)
  {
    // things work fine if this is empty ""
    this->base_output_path = _base_output_path;
    
    this->pre_option_initialize();
    // no command line arguments here
		this->post_option_initialize();
	}
  
  Settings::Settings(int argc, char* argv[])
  {
    this->pre_option_initialize();
    
    // we need the path to the executable to locate scripts and our own installed versions of binaries
    this->bin_path = argv[0];
    size_t slash_pos = this->bin_path.rfind("/");
    if (slash_pos != string::npos) this->bin_path.erase(slash_pos);
    
    // setup and parse configuration options:
    AnyOption options("Usage: breseq -r reference.gbk reads1.fastq [reads2.fastq, reads3.fastq...]");
    options
		("help,h", "produce this help message", TAKES_NO_ARGUMENT)
		// convert to basing everything off the main output path, so we don't have to set so many options
		("output,o", "path to breseq output")
		("reference,r", "reference GenBank flatfile")
    .processCommandArgs(argc, argv);
    
    // Reference sequence provided?
		if (options.count("reference") == 0)
		{
      cerr << "No reference sequences provided (-r)." << endl;
      options.printUsage();
      exit(-1);
		}
    
    // Read sequence file provided?
		if (options.getArgc() == 0)
		{
      cerr << "No read sequence files provided." << endl;
      options.printUsage();
      exit(-1);		
    }
    
    // make sure that the other config options are good:
    if(options.count("help")) 
    {
      options.printUsage();
      exit(-1);
    }
    
    this->base_output_path = "";
    if (options.count("output")) this->base_output_path = options["output"];

    //// GENBANK REFERENCE FILES ////
    this->reference_file_names = from_string<vector<string> >(options["reference"]);
    
    //// FASTQ READ FILES ////
    // Remaining command line items are read files
    for (int32_t i = 0; i < options.getArgc(); i++)
    {
      string read_file_name = options.getArgv(i);
      this->read_file_names.push_back(read_file_name);
    }
    this->read_files.Init(read_file_names);
    
    //// Other options ////
    this->junction_prediction = !options.count("no-junction-prediction");
    
    
		this->post_option_initialize();
	}
  
  

	void Settings::pre_option_initialize()
	{    
		// Set up default values for options
    this->bin_path = ".";
		this->full_command_line = "$0 @ARGV";
		this->arguments = "@ARGV";
		this->predicted_quality_type = "";
		this->min_quality = 0;
		this->max_quality = 0;
		this->run_name = "unnamed";
		this->clean = 0;
		this->error_model_method = "EMPIRICAL";
		this->base_quality_cutoff = 3; // avoids problem with Illumina assigning 2 to bad ends of reads!

    this->maximum_read_length = 0;                  // @JEB this will not be an option once porting is complete

		//this->required_unique_length_per_side = 10;                             // Require at least one of the pair of matches supporting a junction to have this
		// much of its match that is unique in the reference sequence.
		this->maximum_inserted_junction_sequence_length = 20; // Ignore junctions with negative overlap (unique inserted sequence between reference
		// matches) greater than this length. Prevents evidence file names that are too long.
		this->minimum_candidate_junctions = 200; // Minimum number of candidate junctions to keep
		this->maximum_candidate_junctions = 5000; // Maximum number of candidate junctions to keep
		this->maximum_candidate_junction_length_factor = 0.1; // Only keep CJ cumulative lengths adding up to this factor times the total reference size
		this->candidate_junction_read_limit = 0; // FOR TESTING: only process this many reads when creating candidate junctions

    //// READ ALIGNMENT ////
    this->add_split_junction_sides = true;     // Add the sides of passed junctions to the SAM file?
    this->require_complete_match = false;
    this->required_match_length = 28;          // Match must span this many bases in query to count as a match
    this->max_read_mismatches = -1;            // Read alignments with more than this number of mismatches are not counted; -1 = OFF
		this->preprocess_junction_min_indel_split_length = 3; // Split the SAM entries on indels of this many bp or more before identifying CJ
		this->candidate_junction_score_method = "POS_HASH"; // Either POS_HASH, or MIN_OVERLAP

    //// Identify CandidateJunctions ////
    
		//// Scoring to decide which pairs of alignments to the same read to consider
		this->required_extra_pair_total_length = 2;       // The union of the pairs must exceed the best of any single match by this length
                                                      // Setting this does penalize some *real* new junctions, so be careful!
		this->required_both_unique_length_per_side = 5;   // Require both of the pair of matches supporting a junction to have this
                                                      // much of their matches unique in the reference sequence.
		this->required_one_unique_length_per_side = 10;   // Require at least one of the pair of matches supporting a junction to have this
                                                      // much of its match that is unique in the reference sequence.
    
		//// Scoring section to choose which ones from list to take
		this->minimum_candidate_junction_pos_hash_score = 0;    // Require at least this many unique start coordinate/strand reads to accept a CJ
                                                            // OFF by default, because a fixed number are taken
		this->minimum_candidate_junction_min_overlap_score = 0; // Require at least this many unique start coordinate/strand reads to accept a CJ
                                                            // OFF by default, because a fixed number are taken
    
    //// WORKFLOW ////
    this->no_junction_prediction = false; // don't perform junction prediction steps
		this->no_mutation_prediction = false;  // don't perform read mismatch/indel prediction steps
		this->no_deletion_prediction = false; // don't perform deletion prediction steps
		this->no_alignment_generation = false; // don't generate alignments
		this->alignment_read_limit = 0; // only go through this many reads when creating alignments
		this->correction_read_limit = 0; // only go through this many reads when correcting alignments

    
		// NOT IMPLEMENTED
		this->no_filter_unwanted = false; // don't filter out unwanted reads with adaptor matches
		this->unwanted_prefix = "UNWANTED:::"; // prefix on unwanted read names

		//// MutationIdentification ////
		this->mutation_log10_e_value_cutoff = 2; // log10 of evidence required for SNP calls
    
    this->polymorphism_prediction = false;          // perform polymorphism prediction
    this->strict_polymorphism_prediction = false;   // perform polymorphism predictin with strict requirements

		this->polymorphism_log10_e_value_cutoff = 2;
		this->polymorphism_bias_p_value_cutoff = 0.05;
		this->polymorphism_frequency_cutoff = 0; // cut off if < X or > 1-X
		this->polymorphism_coverage_both_strands = 0; // require this much coverage on each strand
		this->no_indel_polymorphisms = 0;
    
		//// Output ////
		this->max_rejected_polymorphisms_to_show = 20;
		this->max_rejected_junctions_to_show = 20;
		this->hide_circular_genome_junctions = 1;
    
    this->smalt = false;

		//@{this->execution_times} = ();
	}

	void Settings::post_option_initialize()
	{
		//this->version = $Breseq::VERSION;
		this->byline = "<b><i>breseq</i></b>&nbsp;&nbsp;version this->version";
		this->website = "http://barricklab.org/breseq";
    
		this->lib_path = this->bin_path + "/../lib/perl5/Breseq";

		//neaten up some settings for later string comparisons
		this->error_model_method = to_upper(this->error_model_method);
    
		//on by default
		this->unmatched_reads = (this->no_unmatched_reads) ? 0 : 1;

		// block option
		if (this->strict_polymorphism_prediction)
		{
			this->polymorphism_prediction = true;
			this->maximum_read_mismatches = 1;
			this->require_complete_match = true;
			this->no_indel_polymorphisms = 1;
			this->polymorphism_log10_e_value_cutoff = 5;
		}

		// problems if there are spaces b/c shell removes quotes before we know about them
		// thus require run names to only use underscores (but when printing output, remove).
		/*if (this->run_name =~ m/\s/)
		{
				die("Option <--name|-n> must not contain whitespace characters. Please use underscores '_' in place of spaces.\n");
		}
		this->print_run_name = this->run_name;
		this->print_run_name =~ s/_/ /g;*/

		////////  SETUP FILE NAMES  ////////
		//// '#' replaced with read fastq name
		//// '@' replaced by seq_id of reference sequence

		////// sequence conversion //////
		this->sequence_conversion_path = "01_sequence_conversion";
		if (this->base_output_path.size() > 0) this->sequence_conversion_path = this->base_output_path + "/" + this->sequence_conversion_path;
		this->converted_fastq_file_name = this->sequence_conversion_path + "/#.converted.fastq";
		this->unwanted_fasta_file_name = this->sequence_conversion_path + "/unwanted.fasta";
		this->reference_trim_file_name = this->sequence_conversion_path + "/@.trims";
		this->sequence_conversion_summary_file_name = this->sequence_conversion_path + "/summary.bin";
		this->sequence_conversion_done_file_name = this->sequence_conversion_path + "/sequence_conversion.done";

		////// reference //////
		this->reference_alignment_path = "02_reference_alignment";
		if (this->base_output_path.size() > 0) this->reference_alignment_path = this->base_output_path + "/" + this->reference_alignment_path;
		this->reference_hash_file_name = this->reference_alignment_path + "/reference";
		this->reference_sam_file_name = this->reference_alignment_path + "/#.reference.sam";
		this->reference_alignment_done_file_name = this->reference_alignment_path + "/alignment.done";

		////// candidate junction //////
		this->candidate_junction_path = "03_candidate_junctions";
		if (this->base_output_path.size() > 0) this->candidate_junction_path = this->base_output_path + "/" + this->candidate_junction_path;

		this->preprocess_junction_best_sam_file_name = this->candidate_junction_path + "/best.sam";
		this->preprocess_junction_split_sam_file_name = this->candidate_junction_path + "/#.split.sam";
		this->preprocess_junction_done_file_name = this->candidate_junction_path + "/preprocess_junction_alignment.done";
    
		this->coverage_junction_best_bam_unsorted_file_name = this->candidate_junction_path + "/best.unsorted.bam";
		this->coverage_junction_best_bam_file_name = this->candidate_junction_path + "/best.bam";
		this->coverage_junction_best_bam_prefix = this->candidate_junction_path + "/best";
		this->coverage_junction_distribution_file_name = this->candidate_junction_path + "/@.unique_only_coverage_distribution.tab";
		this->coverage_junction_plot_file_name = this->candidate_junction_path + "/@.coverage.pdf";
		this->coverage_junction_summary_file_name = this->candidate_junction_path + "/coverage.summary.bin";
		this->coverage_junction_done_file_name = this->candidate_junction_path + "/coverage_junction_alignment.done";

		this->candidate_junction_summary_file_name = this->candidate_junction_path + "/candidate_junction_summary.bin";
		this->candidate_junction_fasta_file_name = this->candidate_junction_path + "/candidate_junction.fasta";
		this->candidate_junction_faidx_file_name = this->candidate_junction_path + "/candidate_junction.fasta.fai";
		this->candidate_junction_done_file_name = this->candidate_junction_path + "/candidate_junction.done";

		////// candidate junction alignment //////
		this->candidate_junction_alignment_path = "04_candidate_junction_alignment";
		if (this->base_output_path.size() > 0) this->candidate_junction_alignment_path = this->base_output_path + "/" + this->candidate_junction_alignment_path;
		this->candidate_junction_hash_file_name = this->candidate_junction_alignment_path + "/candidate_junction";
		this->candidate_junction_sam_file_name = this->candidate_junction_alignment_path + "/#.candidate_junction.sam";
		this->candidate_junction_alignment_done_file_name = this->candidate_junction_alignment_path + "/candidate_junction_alignment.done";

		////// alignment correction //////
		this->alignment_correction_path = "05_alignment_correction";
		if (this->base_output_path.size() > 0) this->alignment_correction_path = this->base_output_path + "/" + this->alignment_correction_path;
		this->resolved_reference_sam_file_name = this->alignment_correction_path + "/reference.sam";
		this->resolved_junction_sam_file_name = this->alignment_correction_path + "/junction.sam";
		this->alignment_correction_summary_file_name = this->alignment_correction_path + "/summary.bin";
		this->alignment_correction_done_file_name = this->alignment_correction_path + "/alignment_resolution.done";
		this->jc_genome_diff_file_name = this->alignment_correction_path + "/jc_evidence.gd";

		////// index BAM //////
		this->bam_path = "06_bam";
		if (this->base_output_path.size() > 0) this->bam_path = this->base_output_path + "/" + this->bam_path;
		this->reference_bam_unsorted_file_name = this->bam_path + "/reference.unsorted.bam";
		this->junction_bam_unsorted_file_name = this->bam_path + "/junction.unsorted.bam";
		this->junction_bam_prefix = this->bam_path + "/junction";
		this->junction_bam_file_name = this->bam_path + "/junction.bam";
		this->bam_done_file_name = this->bam_path + "/bam.done";

		////// error rates and coverage distribution //////
		this->error_calibration_path = "07_error_calibration";
		if (this->base_output_path.size() > 0) this->error_calibration_path = this->base_output_path + "/" + this->error_calibration_path;
		this->error_counts_file_name = this->error_calibration_path + "/#.error_counts.tab";
		//FOR TESTING: this->complex_error_counts_file_name = "this->error_calibration_path///.complex_error_counts.tab";
		this->error_rates_file_name = this->error_calibration_path + "/#.error_rates.tab";
		this->error_counts_done_file_name = this->error_calibration_path + "/error_counts.done";
		this->error_rates_done_file_name = this->error_calibration_path + "/error_rates.done";
		this->coverage_file_name = this->error_calibration_path + "/@.coverage.tab";
		this->unique_only_coverage_distribution_file_name = this->error_calibration_path + "/@.unique_only_coverage_distribution.tab";
		this->error_rates_summary_file_name = this->error_calibration_path + "/summary.bin";
		this->error_rates_base_qual_error_prob_file_name = this->error_calibration_path + "/base_qual_error_prob.#.tab";
		this->plot_error_rates_r_script_file_name = this->lib_path + "/plot_error_rate.r";
		this->plot_error_rates_fit_r_script_file_name = this->error_calibration_path + "/fit.#.r_script";
		this->plot_error_rates_r_script_log_file_name = this->error_calibration_path + "/#.plot_error_rate.log";

		////// mutation identification //////
		this->mutation_identification_path = "08_mutation_identification";
		if (this->base_output_path.size() > 0) this->mutation_identification_path = this->base_output_path + "/" + this->mutation_identification_path;
		this->predicted_mutation_file_name = this->mutation_identification_path + "/@.predicted_mutations.bin";
		this->ra_mc_genome_diff_file_name = this->mutation_identification_path + "/ra_mc_evidence.gd";
		this->complete_mutations_text_file_name = this->mutation_identification_path + "/@.mutations.tab";
		this->complete_coverage_text_file_name = this->mutation_identification_path + "/@.coverage.tab";
		this->mutation_identification_done_file_name = this->mutation_identification_path + "/mutation_identification.done";
		this->cnv_coverage_tab_file_name = this->mutation_identification_path + "/@.cnv_coverage.tab";
		this->genome_error_counts_file_name = this->mutation_identification_path + "/error_counts.tab";
		this->polymorphism_statistics_input_file_name = this->mutation_identification_path + "/polymorphism_statistics_input.tab";
		this->polymorphism_statistics_output_file_name = this->mutation_identification_path + "/polymorphism_statistics_output.tab";
		this->polymorphism_statistics_r_script_file_name = this->lib_path + "/polymorphism_statistics.r";
		this->polymorphism_statistics_r_script_log_file_name = this->mutation_identification_path + "/polymorphism_statistics_output.log";
		this->polymorphism_statistics_ra_mc_genome_diff_file_name = this->mutation_identification_path + "/ra_mc_evidence_polymorphism_statistics.gd";
		this->polymorphism_statistics_done_file_name = this->mutation_identification_path + "/polymorphism_statistics.done";

		////// data //////
		// things in this location are needed for running post-processing steps
		this->data_path = "data";
		if (this->base_output_path.size() > 0) this->data_path = this->base_output_path + "/" + this->data_path;
		this->reference_bam_prefix = this->data_path + "/reference";
		this->reference_bam_file_name = this->data_path + "/reference.bam";
		this->reference_fasta_file_name = this->data_path + "/reference.fasta";
		this->reference_faidx_file_name = this->data_path + "/reference.fasta.fai";
		this->reference_features_file_name = this->data_path + "/reference.features.tab";
		this->reference_gff3_file_name = this->data_path + "/reference.gff3";
		this->unmatched_read_file_name = this->data_path + "/#.unmatched.fastq";

		////// output //////
		// things in this location are part of the user-readable output
		this->output_path = "output";
		if (this->base_output_path.size() > 0) this->output_path = this->base_output_path + "/" + this->output_path;
		this->output_done_file_name = this->output_path + "/output.done";
		this->log_file_name = this->output_path + "/log.txt";
		this->index_html_file_name = this->output_path + "/index.html";
		this->summary_html_file_name = this->output_path + "/summary.html";
		this->marginal_html_file_name = this->output_path + "/marginal.html";
		this->final_genome_diff_file_name = this->output_path + "/output.gd";
		this->local_evidence_path = "evidence";
		this->evidence_path = this->output_path + "/" + this->local_evidence_path;
		this->evidence_genome_diff_file_name = this->evidence_path + "/evidence.gd";
		this->local_coverage_plot_path = "evidence";
		this->coverage_plot_path = this->output_path + "/" + this->local_coverage_plot_path;
		this->deletions_text_file_name = this->coverage_plot_path + "/deletions.tab";
		this->coverage_plot_file_name = this->coverage_plot_path + "/@.overview.png";
		this->output_calibration_path = this->output_path + "/calibration";
		this->unique_only_coverage_plot_file_name = this->output_calibration_path + "/@.unique_coverage.pdf";
		this->error_rates_plot_file_name = this->output_calibration_path + "/#.error_rates.pdf";

		// text output files, to be replaced...
		this->settings_text_file_name = this->output_path + "/settings.tab";
		this->summary_text_file_name = this->output_path + "/summary.tab";
		this->tiled_coverage_text_file_name = this->output_path + "/@.tiled_coverage.tab";

		this->breseq_small_graphic_from_file_name = this->lib_path + "/breseq_small.png";
		this->breseq_small_graphic_to_file_name = this->output_path + "/" + this->local_evidence_path + "/breseq_small.png";

		this->long_pairs_file_name = this->output_path + "/long_pairs.tab";

		this->init_installed();
	}

	void Settings::init_installed()
	{

    // Save the path for reference
    char * pPath;
    pPath = getenv("PATH");
    this->installed["path"] = "";
    if (pPath!=NULL)
    {
      this->installed["path"] = pPath;
    }
    
    // breseq C++ and SAMtools executables - look in the local bin path only
    // @JEB this won't be necessary once C++ conversion is complete

		string test_command = "which " + this->bin_path + "/cbreseq";
		this->installed["cbreseq"] = _system_capture_output(test_command, true);
		
    test_command = "which " + this->bin_path + "/cbam2aln";
		this->installed["cbam2aln"] = _system_capture_output(test_command, true);

    test_command = "which " + this->bin_path + "/samtools";
		this->installed["samtools"] = _system_capture_output(test_command, true);
    
		// search first for ssaha2 in the same location as breseq    
    test_command = "which " + this->bin_path + "/ssaha2";
		this->installed["SSAHA2"] = _system_capture_output(test_command, true);
    
    // attempt to fall back on system-wide install
    if (this->installed["SSAHA2"].size() == 0)
      this->installed["SSAHA2"] = _system_capture_output("which ssaha2", true);

    /*
		// check for default names
		this->installed["smalt"] = system("which smalt &>/dev/null") ? "smalt" : "";
		if (this->installed["smalt"].size() == 0)
		{
			this->installed["smalt"] = system("which smalt_i386 &>/dev/null") ? "smalt_i386" : "";
		}
		if (this->installed["smalt"].size() == 0)
		{
			this->installed["smalt"] = system("which smalt_ia64 &>/dev/null") ? "smalt_ia64" : "";
		}
		if (this->installed["smalt"].size() == 0)
		{
			this->installed["smalt"] = system("which smalt_x86_64 &>/dev/null") ? "smalt_x86_64" : "";
		}
		if (this->installed["smalt"].size() == 0)
		{
			this->installed["smalt"] = system("which smalt_MacOSX_i386 &>/dev/null") ? "smalt_MacOSX_i386" : "";
		}
    */
    
		this->installed["R"] = _system_capture_output("which R", true).size() ? "R" : "";
		if (this->installed["R"].size() > 0)
		{
			string R_version = _system_capture_output("R --version", true);
      
      // default if output does not match our pattern
      this->installed["R_version"] = "0";
      
      size_t start_version_pos = R_version.find("R version ");
      if (start_version_pos != string::npos)
      {
        start_version_pos+=10;
        size_t end_version_pos = R_version.find(" ", start_version_pos);
        
        if (end_version_pos == string::npos)
          end_version_pos = R_version.size();
        end_version_pos--;
        
        string version_string = R_version.substr(start_version_pos, end_version_pos - start_version_pos + 1);
        vector<string> split_version_string = split(version_string, ".");
        if (split_version_string.size() == 3)
        {
          uint32_t R_numerical_version = from_string<uint32_t>(split_version_string[0]) * 1000000 + from_string<uint32_t>(split_version_string[1]) * 1000 + from_string<uint32_t>(split_version_string[2]);
          this->installed["R_version"] = to_string(R_numerical_version);
        }
      }
		}

    
	}

	void Settings::check_installed()
	{
   
    // Developer's Note
    //
    // If you are running things through a debugger (like in XCode), your $PATH may need to be
    // set to include the paths where you have SSAHA2 and R installed within your IDE.
    
		bool good_to_go = true;

		if (!this->smalt && this->installed["SSAHA2"].size() == 0)
		{
			good_to_go = false;
			cerr << "---> ERROR Required executable \"ssaha2\" not found." << endl;
			cerr << "---> See http://www.sanger.ac.uk/resources/software/ssaha2" << endl;
		}

		if (this->smalt && this->installed["smalt"].size() == 0)
		{
			good_to_go = false;
			cerr << "---> ERROR Required executable \"smalt\" not found." << endl;
			cerr << "---> See http://www.sanger.ac.uk/resources/software/smalt/" << endl;
		}

		// R version 2.1 required
		if (this->installed["R"].size() == 0)
		{
			good_to_go = false;
			cerr << "---> ERROR Required executable \"R\" not found." << endl;
			cerr << "---> See http://www.r-project.org" << endl;
		}
		else if ( (this->installed["R_version"].size() == 0) || (from_string<uint32_t>(this->installed["R_version"]) < 2001000) )
		{
      good_to_go = false;
      uint32_t R_numerical_version = from_string<uint32_t>(this->installed["R_version"]);
      string R_version = to_string<uint32_t>(floor(R_numerical_version/1000000)) 
        + "." + to_string<uint32_t>(floor(R_numerical_version%1000000/1000))
        + "." + to_string<uint32_t>(floor(R_numerical_version%1000));

      cerr << "---> ERROR Required executable \"R version 2.1.0 or later\" not found." << endl;
      cerr << "---> Your version is " << R_version << endl;
      cerr << "---> See http://www.r-project.org" << endl;
    }

    if (this->installed["samtools"].size() == 0)
    {
      good_to_go = false;
      cerr << "---> ERROR Required executable \"samtools\" not found." << endl;
      cerr << "---> This should have been installed by the breseq installer." << endl;
    }

		if (!good_to_go) exit(0);
	}

	bool Settings::do_step(string done_key, string message)
	{
		string done_file_name = done_key;
		this->done_key_messages[done_key] = message;
    
		if (!file_exists(done_file_name.c_str()))
		{
      cerr << "+++   NOW PROCESSING " << message << endl;
      this->record_start_time(message);
      return true;
		}
    
		cerr << "--- ALREADY COMPLETE " << message << endl;

		ExecutionTime et;
    et.retrieve(done_file_name);    
    // @JEB Should check for errors, such as incomplete reads...

    this->execution_times.push_back(et);

		return false;
	}

	void Settings::done_step(string done_key)
	{
		string done_file_name = done_key;
		string message = this->done_key_messages[done_key];
		this->record_end_time(message);

		// create the done file with timing information
		this->execution_times.back().store(done_file_name);
	}

  string Settings::create_path(string path)
  {
    int status;

    if (path.find("/") != string::npos) {
      string accumulate_path;
      vector<string> directories = split(path, "/");

      for (vector<string>::iterator itr = directories.begin();
           itr != directories.end(); itr ++) {
        accumulate_path.append(*itr);
        status = mkdir(accumulate_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        accumulate_path.append("/");
      }
    } else {
      status = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }

    
    if (status && (errno != EEXIST))
    {
      cerr << "Could not create path: '" << path << "'" << endl;
      exit(-1);
    }
    
		return path;
	}
}

