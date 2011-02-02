/*****************************************************************************

AUTHORS

  Jeffrey E. Barrick <jeffrey.e.barrick@gmail.com>
  David B. Knoester

LICENSE AND COPYRIGHT

  Copyright (c) 2010 Michigan State University

  breseq is free software; you can redistribute it and/or modify it under the  
  terms the GNU General Public License as published by the Free Software 
  Foundation; either version 1, or (at your option) any later version.

*****************************************************************************/

#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "breseq/identify_mutations.h"

/*! Identify mutations.
 
 This file only does the command-line parsing bit; the real work is over in
 identify_mutations.cpp.
 */
int main(int argc, char* argv[]) {
	using namespace std;
	namespace po = boost::program_options;
	
	// setup and parse configuration options:
	po::options_description cmdline_options("Allowed options");
	cmdline_options.add_options()
	("help,h", "produce this help message")
	("bam,b", po::value<string>(), "bam file containing sequences to be aligned")
	("fasta,f", po::value<string>(), "FASTA file of reference sequence")
	("readfiles,r", po::value<vector<string> >(), "names of readfiles (no extension)")
	("error_dir,e", po::value<string>(), "Directory containing error rates files")
	("genome_diff,g", po::value<string>(), "Genome diff file")
	("output,o", po::value<string>(), "output directory")
	("coverage_dir", po::value<string>()->default_value(string("")), "directory for coverage files")
	("mutation_cutoff,c", po::value<double>()->default_value(2.0), "mutation cutoff (log10 e-value)")
	("deletion_propagation_cutoff,u", po::value<vector<double> >(), "number after which to cutoff deletions")	
  ("minimum_quality_score", po::value<int>()->default_value(0), "ignore base quality scores lower than this")
	("predict_deletions,d", po::value<bool>()->default_value(true), "whether to predict deletions")
	("predict_polymorphisms,p", po::value<bool>()->default_value(false), "whether to predict polymorphisms")
  ("polymorphism_cutoff", po::value<double>()->default_value(2.0), "polymorphism cutoff (log10 e-value)") 
  ("polymorphism_frequency_cutoff", po::value<double>()->default_value(0.0), "ignore polymorphism predictions below this frequency");

	po::variables_map options;
	po::store(po::parse_command_line(argc, argv, cmdline_options), options);
	po::notify(options);
	
	// make sure that the config options are good:
	if(options.count("help")
		 || !options.count("bam")
		 || !options.count("fasta")
		 || !options.count("error_dir")
		 || !options.count("genome_diff")
		 || !options.count("output")
		 || !options.count("readfiles")
		 || !options.count("coverage_dir")
		 || !options.count("deletion_propagation_cutoff")     
		 ) {
		cout << "Usage: identify_mutations --bam <sequences.bam> --fasta <reference.fasta> --error_dir <path> --genome_diff <path> --output <path> --readfiles <filename> --coverage_dir <dirname>" << endl;
		cout << cmdline_options << endl;
		return -1;
	}                       
  
	// attempt to calculate error calibrations:
	try {
		breseq::identify_mutations(
                                 options["bam"].as<string>(),
                                 options["fasta"].as<string>(),
                                 options["error_dir"].as<string>(),
                                 options["genome_diff"].as<string>(),
                                 options["output"].as<string>(),
                                 options["readfiles"].as<vector<string> >(),
                                 options["coverage_dir"].as<string>(),
                                 options["deletion_propagation_cutoff"].as<vector<double> >(),
                                 options["mutation_cutoff"].as<double>(),
                                 options["predict_deletions"].as<bool>(),
                                 options["predict_polymorphisms"].as<bool>(),
                                 options["minimum_quality_score"].as<int>(),
                                 options["polymorphism_cutoff"].as<double>(),
                                 options["polymorphism_frequency_cutoff"].as<double>()
                              );
	} catch(...) {
		// failed; 
		return -1;
	}
	
	return 0;
}
