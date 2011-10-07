/*****************************************************************************

AUTHORS

  Jeffrey E. Barrick <jeffrey.e.barrick@gmail.com
  David B. Knoester

LICENSE AND COPYRIGHT

  Copyright (c) 2008-2010 Michigan State University
  Copyright (c) 2011 The University of Texas at Austin

  breseq is free software; you can redistribute it and/or modify it under the  
  terms the GNU General Public License as published by the Free Software 
  Foundation; either version 1, or (at your option) any later version.

*****************************************************************************/

#ifndef _BRESEQ_CANDIDATE_JUNCTIONS_H_
#define _BRESEQ_CANDIDATE_JUNCTIONS_H_

#include "common.h"

#include "resolve_alignments.h"
#include "alignment.h"

using namespace std;

namespace breseq {

  class PreprocessAlignments
  {
  public:
    /*! Preprocesses alignments
		 */
		static void preprocess_alignments(const Settings& settings, Summary& summary, const cReferenceSequences& ref_seq_info);
    static void split_alignments_on_indels(const Settings& settings, Summary& summary, tam_file& PSAM, int32_t min_indel_split_len, const alignment_list& alignments);
  };
  
  /*! Structure for storing and testing whether alignment pairs support new junctions
   */
  class AlignmentPair
  {
  public:
    bam_alignment	a1;
    bam_alignment a2;
    int32_t union_length;
    int32_t a1_unique_length;
    int32_t a2_unique_length;
    bool pass;
    int32_t intersection_length;
    int32_t a1_length;
    int32_t a2_length;
    int32_t redundancy_1;
    int32_t redundancy_2;
    
    // the constructor - also calculates statistics
    AlignmentPair(bam_alignment& _a1, bam_alignment& _a2, const Settings& settings);
    
  private:
    void calculate_union_and_unique();
    
    //! determines whether a read pair passes
    bool test(const Settings& settings);
    
  };
  
	class CandidateJunctions
	{
	public:

		struct Junction
		{
			string hash_seq_id_1;
			int32_t hash_coord_1;
			bool hash_strand_1;
			string hash_seq_id_2;
			int32_t hash_coord_2;
			bool hash_strand_2;
			int32_t overlap;
			string unique_read_seq_string;
			uint32_t flanking_left;
			uint32_t flanking_right;
		};

		/*! Predicts candidate junctions
		 */
		static void identify_candidate_junctions(const Settings& settings, Summary& summary, const cReferenceSequences& ref_seq_info);

	private:

    
    /*! Sorting functions
     */
    typedef std::map<string, string> map_t;

    static void _by_ref_seq_coord(map_t a, map_t b, map_t ref_seq_info);
		static void _by_score_unique_coord(map_t a, map_t b);

    struct SingleCandidateJunction
		{
			JunctionInfo list;
			string str;
			uint32_t read_begin_coord;
			string side_1_ref_seq;
			string side_2_ref_seq;
      string junction_coord_1;
      string junction_coord_2;
		};
		struct CombinedCandidateJunction
		{
			string id;
			uint32_t pos_hash_score;
			string seq;
			string rc_seq;
      
			// Sort by unique coordinate, then redundant (or second unique) coordinate to get reliable ordering for output
			static bool sort_by_score_unique_coord(const CombinedCandidateJunction& a, const CombinedCandidateJunction &b)
			{
				JunctionInfo a_item = junction_name_split(a.id);
				int32_t a_uc = a_item.sides[0].position;
				int32_t a_rc = a_item.sides[1].position;
				if (a_item.sides[0].redundant != 0) swap(a_uc, a_rc);
        
				JunctionInfo b_item = junction_name_split(b.id);
				int32_t b_uc = b_item.sides[0].position;
				int32_t b_rc = b_item.sides[1].position;
				if (b_item.sides[0].redundant != 0) swap(b_uc, b_rc);
        
				if (b.pos_hash_score != a.pos_hash_score)
					return (b.pos_hash_score < a.pos_hash_score);
				else if (a_uc != b_uc)
					return (a_uc < b_uc);
				else
					return (a_rc < b_rc);
			}
      
			static bool sort_by_scores_and_seq_length(const CombinedCandidateJunction& a, const CombinedCandidateJunction &b)
			{
				if (b.pos_hash_score != a.pos_hash_score)
					return (b.pos_hash_score < a.pos_hash_score);
				else
					return (a.seq.size() < b.seq.size());
			}
      
			static bool sort_by_ref_seq_coord(const CombinedCandidateJunction& a, const CombinedCandidateJunction &b)
			{
				JunctionInfo acj = junction_name_split(a.id);
				JunctionInfo bcj = junction_name_split(b.id);
				//TODO: Uncomment this code after supplying it with a ref_seq_info with a seq_order field
				/*if (ref_seq_info.seq_order[acj.sides[0].seq_id] != ref_seq_info.seq_order[bcj.sides[0].seq_id])
         return (ref_seq_info.seq_order[acj.sides[0].seq_id] < ref_seq_info.seq_order[bcj.sides[0].seq_id]);
         else*/
        return (acj.sides[0].position < bcj.sides[0].position);
			}
		};
    
    static 	bool alignment_pair_to_candidate_junction(
                                                  const Settings& settings, 
                                                  Summary& summary, 
                                                  const cReferenceSequences& ref_seq_info, 
                                                  AlignmentPair& ap,
                                                  SingleCandidateJunction& junction_id_list
                                                  );
    
		static void alignments_to_candidate_junctions(
                                                  const Settings& settings, 
                                                  Summary& summary,  
                                                  const cReferenceSequences& ref_seq_info, 
                                                  map<string, map<string, CandidateJunction>, CandidateJunction::Sorter>& candidate_junctions, 
                                                  alignment_list& alignments);
    
	}; // class CandidateJunction

} // namespace breseq

#endif
