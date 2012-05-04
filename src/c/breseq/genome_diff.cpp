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

#include "libbreseq/genome_diff.h"
#include "libbreseq/annotated_sequence.h"
#include "libbreseq/output.h"

namespace breseq {

// Common keywords used for diff entries:
const char* TYPE="type";
const char* ID="id";
const char* PID="parent";
const char* SEQ_ID="seq_id";
const char* START="start";
const char* END="end";
const char* START_RANGE="start_range";
const char* END_RANGE="end_range";
const char* LEFT_OUTSIDE_COV="left_outside_cov";
const char* LEFT_INSIDE_COV="left_inside_cov";
const char* RIGHT_INSIDE_COV="right_inside_cov";
const char* RIGHT_OUTSIDE_COV="right_outside_cov";
const char* POSITION="position";
const char* INSERT_POSITION="insert_position";
const char* QUALITY="quality";
const char* POLYMORPHISM_QUALITY="polymorphism_quality";
const char* REF_BASE="ref_base";
const char* NEW_BASE="new_base";
const char* FREQUENCY="frequency";
const char* REJECT="reject";
const char* REF_COV="ref_cov";
const char* NEW_COV="new_cov";
const char* TOT_COV="tot_cov";
const char* ERROR="error";
  
//For JC
const char* SIDE_1_SEQ_ID = "side_1_seq_id";
const char* SIDE_1_POSITION = "side_1_position";
const char* SIDE_1_STRAND = "side_1_strand";
const char* SIDE_1_REDUNDANT = "side_1_redundant";
  
const char* SIDE_2_SEQ_ID = "side_2_seq_id";
const char* SIDE_2_POSITION = "side_2_position";
const char* SIDE_2_STRAND = "side_2_strand";
const char* SIDE_2_REDUNDANT = "side_2_redundant";

const char* SIDE_1_READ_COUNT="side_1_read_count";
const char* SIDE_2_READ_COUNT="side_2_read_count";
const char* NEW_JUNCTION_READ_COUNT="new_junction_read_count";

const char* SIDE_1_COVERAGE = "side_1_coverage";
const char* SIDE_2_COVERAGE = "side_2_coverage";
const char* NEW_JUNCTION_COVERAGE = "new_junction_coverage";
  
map<gd_entry_type, vector<string> > line_specification = make_map<gd_entry_type, vector<string> >
//! seq_id and positions are already parameters in cDiffEntry
//## mutations
(SNP,make_vector<string> ("seq_id")("position")("new_seq"))
(SUB,make_vector<string> ("seq_id")("position")("size")("new_seq"))
(DEL,make_vector<string> ("seq_id")("position")("size"))
(INS,make_vector<string> ("seq_id")("position")("new_seq"))
(MOB,make_vector<string> ("seq_id")("position")("repeat_name")("strand")("duplication_size"))
(INV,make_vector<string> ("seq_id")("position")("size"))
(AMP,make_vector<string> ("seq_id")("position")("size")("new_copy_number"))
(CON,make_vector<string> ("seq_id")("position")("size")("region"))

//## evidence
(RA,make_vector<string> ("seq_id")("position")("insert_position")("ref_base")("new_base"))
(MC,make_vector<string> ("seq_id")("start")("end")("start_range")("end_range"))
(JC,make_vector<string> ("side_1_seq_id")("side_1_position")("side_1_strand")("side_2_seq_id")("side_2_position")("side_2_strand")("overlap"))
(CN,make_vector<string> ("seq_id")("start")("end")("copy_number"))
(UN,make_vector<string> ("seq_id")("start")("end"))

//## validation
(CURA,make_vector<string> ("expert"))
(FPOS,make_vector<string> ("expert"))
(PHYL,make_vector<string> ("gd"))
(TSEQ,make_vector<string> ("seq_id")("primer_1_start")("primer_1_end")("primer_2_start")("primer_2_end"))
(PFLP,make_vector<string> ("seq_id")("primer_1_start")("primer_1_end")("primer_2_start")("primer_2_end"))
(RFLP,make_vector<string> ("seq_id")("primer_1_start")("primer_1_end")("primer_2_start")("primer_2_end"))
(PFGE,make_vector<string> ("seq_id")("enzyme"))
(NOTE,make_vector<string> ("note"))

  
; // end line specifications


const vector<string>gd_entry_type_lookup_table =
  make_vector<string>("UNKNOWN")("SNP")("SUB")("DEL")("INS")("MOB")("AMP")("INV")("CON")("RA")("MC")("JC")("CN")("UN")("CURA")("FPOS")("PHYL")("TSEQ")("PFLP")("RFLP")("PFGE")("NOTE");


// Field order.
static const char* s_field_order[] = { 
  SEQ_ID,
  POSITION,
  INSERT_POSITION,
  REF_BASE,
  NEW_BASE,
  START,
  END,
  START_RANGE,
  END_RANGE,
0}; // required trailing null.


/*! Constructor.
 */
cDiffEntry::cDiffEntry(const gd_entry_type type)
: _type(type)
, _id("")
, _evidence()
{
}

cDiffEntry::cDiffEntry()
: _type(UNKNOWN)
, _id("")
, _evidence()
{
}

cDiffEntry::cDiffEntry(const string &line)
  : _type(UNKNOWN)
  ,_id("")
  ,_evidence()
{
  cDiffEntry *de = this;
  typedef vector<string> string_vector_t;
  string_vector_t tokens = split_on_whitespace(line);
  int COLUMN = 0;

  //! Step: Get the type. (Convert from string to enumeration.)
  string type = tokens[COLUMN++]; 

  //Find the string value in the lookup table and cast index to enumeration.
  const size_t lookup_table_size = gd_entry_type_lookup_table.size();
  for (size_t i = 0; i < lookup_table_size; i++) {
    if (type == gd_entry_type_lookup_table[i]) {
      de->_type = (gd_entry_type) i;
      break;
    }
  }

  /*Check that the type is set. If there is an error confirm that gd_entry_type
   and the lookup table are identical in size and order and contain this type.*/
  if (de->_type == UNKNOWN) {
    string message = "";
    sprintf(message,
            "cDiffEntry::cDiffEntry(%s): Could not determine type.",
            line.c_str()
            );
    WARN(message);
    return;
  }

  //! Step: Get the id.
  de->_id = tokens[COLUMN++];

  /*! Step: If this diff entry is a mutation we need to get it's supporting
  evidence. */
  if (de->is_mutation()) {
    string evidence = tokens[COLUMN++];

    string_vector_t evidence_vector = split(evidence, ",");

    const size_t evidence_vector_size = evidence_vector.size();
    if (evidence_vector_size) {
      de->_evidence.resize(evidence_vector_size);

      for (size_t i = 0; i < evidence_vector_size; i++) {
        de->_evidence[i] = evidence_vector[i];
      }
    } 

  } 

  /*! Step: Get line specifications and assign them. */
  const string_vector_t &diff_entry_specs = line_specification[de->_type];
  const size_t diff_entry_specs_size = diff_entry_specs.size();
  for (size_t i = 0; i < diff_entry_specs_size; i++) {
     const diff_entry_key_t &key = diff_entry_specs[i];
     diff_entry_value_t value = COLUMN + 1 > tokens.size() ? "" : tokens[COLUMN++];
     if (value.empty()) {
       value = "?";
       string msg = "";
       sprintf(msg,
               "cDiffEntry::cDiffEntry(%s): Line specification [%s] has no value.",
               line.c_str(), key.c_str());
       WARN(msg);
     }
     de->insert(pair<diff_entry_key_t, diff_entry_value_t>(key, value));
  }

  /*! Step: Get the rest of the fields.*/
  while (COLUMN < tokens.size()) {
    string key_value_pair = tokens[COLUMN++];
    if (key_value_pair.empty()) {
      continue;
    }

    size_t equal_sign_pos = 0;
    const size_t key_value_pair_size = key_value_pair.size();
    for (size_t i = 0; i < key_value_pair_size; i++) {
      if (key_value_pair[i] == '=') {
        equal_sign_pos = i;
        break;
      }
    }

    //Confirm this is a key=value field.
    if (!equal_sign_pos) {
      string message = "";
      sprintf(message,
              "cDiffEntry::cDiffEntry(%s): Field %s is not a key=value pair.",
              line.c_str(), key_value_pair.c_str()
              );
      WARN(message);
      return;
    }

    const string &key   = key_value_pair.substr(0, equal_sign_pos);
    const string &value = key_value_pair.substr(equal_sign_pos + 1,
                                                key_value_pair_size);

    de->insert(pair<string, string>(key, value));
  }
  //All done!
  return;

}

bool cDiffEntry::is_mutation() const
{
  return gd_entry_type_lookup_table[_type].size() == 3;
}

bool cDiffEntry::is_evidence() const
{
  return gd_entry_type_lookup_table[_type].size() == 2;
}

bool cDiffEntry::is_validation() const
{
  return gd_entry_type_lookup_table[_type].size() == 4;
}
  
uint32_t cDiffEntry::get_start()
{
  switch (this->_type) {
    case SNP:
    case SUB:
    case DEL:
    case INS:
    case MOB:
    case INV:
    case AMP:
    case CON:
      return from_string<uint32_t>((*this)[POSITION]);
    case UN:
      return from_string<uint32_t>((*this)[START]);
    default:
      ERROR("cDiffEntry::get_start not implemented for type: " + gd_entry_type_lookup_table[this->_type]);
  }
  return 0;
}
  
uint32_t cDiffEntry::get_end()
{
  switch (this->_type) {
    case SNP:
      return from_string<uint32_t>((*this)[POSITION]);
    case SUB:
    case DEL:
    case INV:
    case AMP:
    case CON:
      return from_string<uint32_t>((*this)[POSITION]) + from_string<uint32_t>((*this)[SIZE]);
    case INS:
      return from_string<uint32_t>((*this)[POSITION]) + (*this)[NEW_SEQ].length();
    case MOB:
      return from_string<uint32_t>((*this)[POSITION]) + from_string<uint32_t>((*this)["duplication_size"]);
    case UN:
      return from_string<uint32_t>((*this)[END]);
    default:
      ERROR("cDiffEntry::get_end not implemented for type: " + gd_entry_type_lookup_table[this->_type]);
  }
  return 0;
}


cDiffEntry cDiffEntry::to_spec() const
{
  cDiffEntry de(_type);

  const vector<diff_entry_key_t>& specs = line_specification[_type];

  for(vector<diff_entry_key_t>::const_iterator it = specs.begin(); it != specs.end(); it++) {
    const diff_entry_key_t& spec(*it);
    de[spec] = this->get(spec);
  }

  return de;
}
  
  
//Comparing IDs here will currently break cGenomeDiff::merge and cGenomeDiff::subtract
bool cDiffEntry::operator==(const cDiffEntry& de)
{
  //! Case: Easy if not same type
  if (this->_type != de._type) {
    return false;
  }
  //! Case: Same type, but are fields that are common equal?
  else {
    // Get common keys
    const vector<diff_entry_key_t>& specs = line_specification[this->_type];
    for(vector<diff_entry_key_t>::const_iterator it = specs.begin(); it != specs.end(); it++) {
      const diff_entry_key_t& spec(*it);
      if ((*this)[spec] != de.find(spec)->second)
        return false;
    }
    return true;
  }
}


/*! Marshal this diff entry into an ordered list of fields.
 */
void cDiffEntry::marshal(field_list_t& s) const {
  s.push_back(gd_entry_type_lookup_table[_type]);
	s.push_back(_id);
  
  s.push_back(join(_evidence, ","));

	// deep copy all fields:
  cDiffEntry cp= *this;

	// marshal specified fields in-order, removing them from the copy after they've 
	// been printed:
  
  vector<string>& f = line_specification[_type];

  for (vector<string>::iterator it=f.begin(); it != f.end(); it++)
  {
    diff_entry_map_t::iterator iter=cp.find(*it);
    
    ASSERT(iter != cp.end(), "Did not find required field '" + *it + "' to write in entry id " + _id + " of type '" + gd_entry_type_lookup_table[_type] + "'.");
    
    s.push_back(iter->second);
    cp.erase(iter);
  
	}
	
	// marshal whatever's left, unless it's an empty field or _begins with an underscore
  for(diff_entry_map_t::iterator i=cp.begin(); i!=cp.end(); ++i) {
    
    assert(i->first.size());
    if (i->first.substr(0,1) == "_") continue;
    
    if (i->second.size() > 0) 
    {
      s.push_back(i->first + "=" + i->second);
    }
  }
}
  
vector<string> cDiffEntry::get_reject_reasons()
{
  vector<string> return_value;
  if (this->entry_exists("reject")) {
    return_value = split((*this)["reject"], ",");
  } 
  return return_value;
}

size_t cDiffEntry::number_reject_reasons()
{
  if(this->entry_exists(REJECT))
  {
    return this->get_reject_reasons().size();
  }
  return 0;
}
  
/*! Add reject reason to diff entry.
 */
void add_reject_reason(cDiffEntry& de, const string &reason) {

  if (de.find(REJECT) == de.end()) {
      de[REJECT] = reason;
  }
  // exists already, make comma separated list
  else {
    string reject = de[REJECT];
    reject += ",";
    reject +=reason; 
  }

}

uint32_t number_reject_reasons(cDiffEntry& de) {

	if (!de.entry_exists(REJECT) || de[REJECT].size() == 0)
		return 0;

	uint32_t reason_count = 1;
	for (uint32_t i = 0; i < de[REJECT].size(); i++)
		if (de[REJECT][i] == ',') reason_count++;
	return reason_count;
}

string cDiffEntry::to_string(void) const
{
  field_list_t fields;
  marshal(fields);

  return join(fields, "\t");
}

/*! Output operator for a diff entry.
 */
ostream& operator<<(ostream& out, const cDiffEntry& de) {
	field_list_t fields;
	de.marshal(fields);
	out << join(fields, "\t");
	return out;
}
/*! Constructor.
 */
cGenomeDiff::cGenomeDiff(const string& filename)
 : _default_filename(filename)
 , _unique_id_counter(0) 
{
 read(filename);  
}

/*! Merge Constructor.
 */
cGenomeDiff::cGenomeDiff(cGenomeDiff& merge1, cGenomeDiff& merge2, bool unique, bool new_id, bool verbose)
 : _unique_id_counter(0)
{
  this->merge(merge1, unique, new_id, verbose);
  this->merge(merge2, unique, new_id, verbose);
}
  
uint32_t cGenomeDiff::new_unique_id()
{ 
  uint32_t assigned_id = ++_unique_id_counter;
  
  while (unique_id_used.count(assigned_id))
  {
    assigned_id++;
  }
  return assigned_id;
}

/*! Add evidence to this genome diff.
 */
uint32_t cGenomeDiff::add(const cDiffEntry& item, bool lowest_unique) {

  // allocating counted_ptr takes care of disposal
  cDiffEntry* diff_entry_copy = new cDiffEntry(item);
  diff_entry_ptr_t added_item(diff_entry_copy);
  _entry_list.push_back(added_item);
  
  uint32_t new_id = 0;    
  
  if ((added_item->_id.size() == 0) || lowest_unique || unique_id_used.count(from_string<uint32_t>(added_item->_id)))  {
    new_id = new_unique_id();
    added_item->_id = to_string(new_id);
  }
  else  {
    new_id = from_string<uint32_t>(added_item->_id);
  }  

  unique_id_used[new_id] = true;

  return new_id;
}

//! Subtract mutations using gd_ref as reference.
void cGenomeDiff::set_subtract(cGenomeDiff& gd_ref, bool verbose)
{
  // We will be erasing inside the it loop.  This is to keep
  // track of whether or not we should iterate to the next element.
  bool it_iterate = true;
  
  //Iterate through all the entries
  for (diff_entry_list_t::iterator it = _entry_list.begin(); it != _entry_list.end(); )
  {
    it_iterate = true;
    //The current entry we're looking at
    cDiffEntry& entry = **it;
    
    //if (verbose) cout << entry << endl;
    
    //Is the entry a mutation?
    if(entry.is_mutation())
    {
      //Iterate through all the entries we're checking against.
      for (diff_entry_list_t::iterator it_ref = gd_ref._entry_list.begin(); it_ref != gd_ref._entry_list.end(); it_ref++)
      {
        //The current entry we're looking at
        cDiffEntry& entry_ref = **it_ref;
        
        if(!entry_ref.is_mutation())
          continue;
        
        //if (verbose) cout << "  " << entry_ref << endl;
        
        //Does the current entry match any of the reference entries?
        if(entry == entry_ref)
        {
          //Notify the user of the action.
          if(verbose){cout << "REMOVE\t" << to_string(entry._type) << "\t" << entry._id << endl;}
          it = _entry_list.erase(it);
          //We just removed the current feauture, do not iterate.
          it_iterate = false;
          break; // Done comparing to this mutaion.
        }
      }
    }
    
    // Iterate it ONLY if we haven't erased something.
    if(it_iterate)it++;
  }
}


//! Merge GenomeDiff information using gd_new as potential new info.
//  Evidence IDs that are not unique are given new IDs.  Mutations
//  that refer to this evidence have their evidence updated as well.
//
//  bool unique:  TRUE will NOT merge entries that match existing entries.
//                FALSE WILL merge entries that match existing entries.
//
//  bool new_id:  TRUE will give assign all new entries with the lowest available ID.
//                FALSE will allow all entries to retain their IDs if they are unique.
void cGenomeDiff::merge(cGenomeDiff& gd_new, bool unique, bool new_id, bool verbose)
{
  uint32_t old_unique_ids = unique_id_used.size();
  
  //Iterate through all the potential new entries
  for (diff_entry_list_t::iterator it_new = gd_new._entry_list.begin(); it_new != gd_new._entry_list.end(); it_new++)
  {
    //The current potential new entry we're looking at
    cDiffEntry& entry_new = **it_new;
    bool new_entry = true;
    
    //Iterate through all the entries in the current list.
    for (diff_entry_list_t::iterator it_cur = _entry_list.begin(); it_cur != _entry_list.end() && unique; it_cur++)
    {
      //The current entry we're looking at
      cDiffEntry& entry = **it_cur;
      
      //Does the new entry match the current entry?
      if(entry == entry_new)
      {
        //Existing matching entry found, this is not new
        new_entry = false;
        break;
      }
    }
    
    //We definately have a new entry
    if(new_entry)
    {      
      //Add the new entry to the existing list
      add(entry_new, new_id);
      
      //Notify user of new entry
      if(verbose)cout << "\tNEW ENTRY\t" << entry_new._id << " >> " << _entry_list.back()->_id << "\t" << gd_new._default_filename << endl;
    }
  }
  
  //Iterate through all the entries in the new list.
  //This is where we update the evidence IDs for mutations.
  for (diff_entry_list_t::iterator it = _entry_list.begin(); it != _entry_list.end(); it++)
  {
    // @JEB: optimization: we don't need to do this for evidence items.
    if ( (*it)->is_evidence() ) continue;
    
    //Is this one of the new entries?
    if(from_string<uint32_t>((**it)._id) > old_unique_ids && (**it).is_mutation())
    {                
      //For every piece of evidence this entry has
      for(int32_t iter = 0; iter < (int32_t)(**it)._evidence.size(); iter++)
      {
        bool found_match = false;
        
        //Iterate through all the potential new entries
        for (diff_entry_list_t::iterator it_new = gd_new._entry_list.begin(); it_new != gd_new._entry_list.end(); it_new++)
        {            
          //Does this evidence ID match an ID in the old list?
          if((**it)._evidence[iter] == (**it_new)._id && !found_match)
          {
            //Iterate through all the current entries
            for (diff_entry_list_t::iterator it_cur =_entry_list.begin(); it_cur != _entry_list.end(); it_cur++)
            {
              //Does the new entry match the current entry?
              if((**it_cur) == (**it_new))
              {
                //Notify user of the update
                if(verbose)cout << "\tID: " << (**it)._id  << "\tEVIDENCE\t" << (**it)._evidence[iter] << " >> " << (**it_cur)._id << endl;
                
                //Change the evidence ID to it's new ID in the new updated list
                (**it)._evidence[iter] = (**it_cur)._id;
                found_match = true;  
                break;
              }
            }
          }
        }
        
        // If we've gone through all the lists, and can't find the evidence
        // then remove the evidence entry completely, as it matches to nothing.
        if(!found_match)
        {
          //Notify user of the update
          if(verbose)cout << "\tID: " << (**it)._id  << "\tEVIDENCE  \t" << (**it)._evidence[iter] << " >> REMOVED" << endl;
          
          (**it)._evidence.erase((**it)._evidence.begin() + iter--);
        }        
      }
    }
  }
  
  //Notify user of the update
  if(verbose)cout << "\tMERGE DONE - " << gd_new._default_filename << endl;
  
}

void cGenomeDiff::unique()
{
  bool (*comp_fn) (const diff_entry_ptr_t&, const diff_entry_ptr_t&) = diff_entry_ptr_sort;
  typedef set<diff_entry_ptr_t, bool(*)(const diff_entry_ptr_t&, const diff_entry_ptr_t&)> diff_entry_set_t;
  //Filter entries.
  diff_entry_set_t seen(comp_fn);
  //Store pointers to mutations.
  map<string, vector<diff_entry_ptr_t> > keep_ids;
  //Store ids of evidence to erase.
  set<string> erase_ids;

  this->sort();
  diff_entry_list_t::iterator it = _entry_list.begin();
  while (it != _entry_list.end()) {
    if (!(**it).is_mutation()) break;

    const vector<string>& ids = (**it)._evidence;
    uint32_t n = ids.size();

    //Is mutation unique?
    //Case: true.
    if (seen.insert(*it).second) { 
      for (uint32_t i = 0; i < n; ++i) {
        keep_ids[ids[i]].push_back(*it);
      }
      ++it;
    } 
    //Case: false.
    else { 
      for (uint32_t i = 0; i < n; ++i) {
        erase_ids.insert(ids[i]);
      }
      it = _entry_list.erase(it);
    }
  }

  seen.clear(); //Re-use to filter the evidence.
  while (it != _entry_list.end()) {
    //Keep this evidence?
    //Case: unkown.
    if (keep_ids.count((**it)._id) && erase_ids.count((**it)._id)) {
      //Is evidence unique?
      //Case: true.
      if (seen.insert(*it).second) {
        ++it;
      } 
      //Case: false.
      else {
        it = _entry_list.erase(it);
        //Update mutations that may of been using this id.
        for (uint32_t i = 0; i < keep_ids[(**it)._id].size(); ++it) {
          vector<string>* evidence = &(*keep_ids[(**it)._id][i])._evidence;
          vector<string>::iterator jt = std::remove(evidence->begin(), evidence->end(), (**it)._id);
          //evidence->erase(jt);
        }
      }
    } 
    //Case: false.
    else if (!keep_ids.count((**it)._id) && erase_ids.count((**it)._id)) {
      it = _entry_list.erase(it);
    } 
    //Case: false.
    else if (!keep_ids.count((**it)._id) && !erase_ids.count((**it)._id)) {
      stringstream ss;
      ss << "\tRemoving [entry]:\t" << **it << endl;
      ss << "\tfrom [file]:\t" << this->_default_filename << endl;
      ss << "\tbecause no mutation referenced it's ID." << endl; 
      WARN(ss.str());
      it = _entry_list.erase(it);
    }
    
    //Case: true.
    else {
      ++it;
    }
  }

  return;
}

void cGenomeDiff::fast_merge(const cGenomeDiff& gd)
{  
  diff_entry_list_t gd_list = gd.list();
  for(diff_entry_list_t::const_iterator it=gd_list.begin(); it!= gd_list.end(); it++) {
    this->add(**it);
  }
}

/*! Read a genome diff(.gd) from the given file to class member
  _entry_list
 */

void cGenomeDiff::read(const string& filename) {
  ifstream in(filename.c_str());
  ASSERT(in.good(), "Could not open file for reading: " + filename);

  //! Step: Handle header parameters.
  //Example header:
  //#=GENOME_DIFF 1.0
  //#=AUTHOR    Barrick JE
  //#=REFSEQ    Genbank:NC_012967.1
  //#=READSEQ   SRA:SRR066595

  /*#=GENOME_DIFF version must be initialized for this file to be recognized
   as a genome diff file. */
  metadata.version = "";
  while(in.peek() == 35) { //35 is ASCII of '#'.
    in.get();
    if (in.peek() != 61) { //61 is ASCII of '='.
      in.unget();
      break;
    } else {
      in.unget();
    }
    
    string whole_line = "";
    string second_half = "";
    
    getline(in, whole_line);
    
    vector<string> split_line = split_on_whitespace(whole_line);
    
    if(split_line.size() > 1)second_half = split_line[1];
    for(size_t j = 2; j < split_line.size(); j++)  {
      second_half += " " + split_line[j];  }    
    
    //Evaluate key.
    if (split_line[0] == "#=GENOME_DIFF" && split_line.size() > 1) {
      metadata.version = second_half;
    }
    else if (split_line[0] == "#=AUTHOR" && split_line.size() > 1) {
      metadata.author = second_half;
    }
    else if (split_line[0] == "#=REFSEQ" && split_line.size() > 1) {
      metadata.ref_seqs.resize(metadata.ref_seqs.size() + 1);
      metadata.ref_seqs.back() = second_half;
    }
    else if (split_line[0] == "#=READSEQ" && split_line.size() > 1) {
      metadata.read_seqs.resize(metadata.read_seqs.size() + 1);
      metadata.read_seqs.back() = second_half;
    }
    else if (split_line[0] == "#=TITLE" && split_line.size() > 1) {
      metadata.run_name = second_half;
      replace(metadata.run_name.begin(), metadata.run_name.end(), ' ', '_');
    }
    else if (split_line[0].substr(0, 2) == "#=") {continue;}
    else {
      //Warn if unkown header lines are encountered.
      printf("cGenomeDiff:read(%s): Header line: %s is not recognized.",
             filename.c_str(), whole_line.c_str()
             );
    }
  }

  /*Error if #=GENOME_DIFF is not found. Genome diff files are required to have
   this header line. */
  if (metadata.version.empty()) {
    string message = "";
    sprintf(message,
            "cGenomeDiff:read(%s): No #=GENOME_DIFF XX header line in this file.",
            filename.c_str()
            );
    ERROR(message);
  }

	/*If the run_name/title is not set by a #=TITLE tag in the header info then
		default to the name of the file. */
	if (metadata.run_name.empty()) {
		string *run_name = &metadata.run_name;
			*run_name = filename.substr(0, filename.find(".gd"));
			if (run_name->find('/') !=  string::npos) {
				run_name->erase(0, run_name->find_last_of('/') + 1);
			}
	}

  //! Step: Handle the diff entries.
  while (in.good()) {
    string line = "";
    std::getline(in, line);
    //Warn if commented out or a possibly blank line is encountered.
    if (line.empty()) {
      continue;
    } else if (line[0] == '#') {
      //printf("Discarding Genome Diff comment file:%s line:\n%s\n", filename.c_str(), line.c_str());
      continue;
    } else if (line.find_first_not_of(' ') == string::npos) {
      continue;
    }
    const cDiffEntry de(line);
    if (de._type != UNKNOWN) add(cDiffEntry(line));

  }

  return;
}

void cDiffEntry::normalize_to_sequence(const cAnnotatedSequence &sequence)
{
  //! Step: Initialize parameters.
  //Only diff entries applicable to de sequence can be considered.
  assert(this->entry_exists("seq_id") || (*this)["seq_id"] == sequence.m_seq_id);
  assert(this->entry_exists("position"));

  //Sequences should be viewed as having index + one offset.
  typedef size_t pos_1_t;
  const pos_1_t pos_1 = strtoul((*this)["position"].c_str(), NULL, 0);
  if (!pos_1) {
    this->insert(pair<string, string>("comment_out", "True"));
    return;
  }

  /*! Step: Type specific normalizations. For some, the initial parameters given
    can be altered to be normalized, for others the parameters can't be altered
    and the mutation is not valid for the given reference sequence. */
  switch (this->_type)
  {
  case DEL:
  {
    /*     
      +++EXAMPLE DEL: pos_1 = 1, size = 3

      START:
      Ref: ACTACTATCACACTAATACAATA
           ^ pos_1
      seq_1 = ACT
      seq_2 = ACT
      NOT VALID, ACT == ACT

      NEXT(pos_1++):
      Ref: ACTACTATCACACTAATACAATA
            ^ pos_1
      seq_1 = CTA
      seq_2 = CTA
      NOT VALID, CTA == CTA

      NEXT(pos_1++):
      Ref: ACTACTATCACACTAATACAATA
             ^ pos_1
      seq_1 = TAC
      seq_2 = TAT
                ^ first mismatch, normalize pos_1 to here.

      THEREFOR: pos_1 = 8. 
     */

    assert(this->entry_exists("size"));

    //! Step: Initialize parameters.
    typedef string sequence_t;
    typedef sequence_t::const_iterator base_itr_t;
    typedef pair<base_itr_t, base_itr_t> base_pair_t;
    const size_t n = strtoul((*this)["size"].c_str(), NULL, 0);

    if (!n) {
      this->insert(pair<string, string>("comment_out", "True"));
      return;
    }

    /*! Step: Attempt to normalize the start position by iterating through new
    start positions. */
    pos_1_t i = pos_1;
    for(;;++i) {
      const sequence_t &first =
          sequence.get_circular_sequence_1(i, n);
      assert(first.size());

      const sequence_t &second =
          sequence.get_circular_sequence_1(i + n, n);
      assert(second.size());

      const base_pair_t &base_pair =
          mismatch(first.begin(), first.end(), second.begin());

      if (base_pair.first != first.end()) {
        i += (base_pair.first - first.begin());
        break;
      }
    }

    //! Step: Determine if the start pos needed to be normilized.
    bool is_new_position = pos_1 != i;
    if (is_new_position) {
      sprintf((*this)["position"], "%u", i);
      sprintf((*this)["norm_pos"], "%u_to_%u", pos_1, i);
    }
  } break;

  case INS:
  {
    /*
      +++EXAMPLE INS: pos_1 = 1, new_seq = CAA

      START:
      Ref: ACTACTATCACACTAATACAATA
           ^ pos_1
      seq_1 = CAA
      seq_2 = CTA
              ^ match, could be predicted as a SNP, NOT VALID

      NEXT(pos_1++):
      Ref: ACTACTATCACACTAATACAATA
            ^ pos_1
      seq_1 = CAA
      seq_2 = TAC
              ^ mismatch, won't be predicted as a SNP, normalize pos_1 to here.

      THEREFOR: pos_1 = 2.


      +++EXAMPLE INS -> AMP: pos_1 = 1, new_seq = CTA

      START:
      Ref: ACTACTATCACACTAATACAATA
           ^ pos_1
      seq_1 = CTA
      seq_2 = CTA
      NOT VALID, CTA == CTA, possible AMP.

      NEXT(pos_1 += 3):
      Ref: ACTACTATCACACTAATACAATA
              ^ pos_1
      seq_1 = CTA
      seq_2 = CTA
      NOT VALID, CTA == CTA, possible AMP.

      NEXT(pos_1 += 3):
      Ref: ACTACTATCACACTAATACAATA
                 ^ pos_1
      seq_1 = CTA
      seq_2 = TCA
      VALID, Passes SNP check and will be evaluated as an AMP.
      
      THEREFOR: INS->AMP, pos_1 = 1, size = 3, new_copy_number = 2, orig_type = INS.

     */
    assert(this->entry_exists("new_seq"));

    //! Step: Initialize parameters.
    typedef string sequence_t;
    const string first = (*this)["new_seq"];
    const size_t n = first.size();
    assert(n);

    /*! Step: Attempt to normalize the start position by iterating through new
    start positions. */
    pos_1_t i = pos_1;
    
    bool bAmp, bSnp;
    bAmp = true;
    bSnp = true;
    
    while(bAmp || bSnp)
    {
      bAmp = true;
      bSnp = true;
      
      for(;;i += n)
      {
        const string second = sequence.get_circular_sequence_1(i + 1, n);
        assert(second.size());
        
        if (first != second)  {
          bAmp = false;
          break;  }
      }
      
      for(;;i += 1)
      {
        const string second = sequence.get_circular_sequence_1(i + 1, n);
        assert(second.size());
        
        if (first[0] != second[0])  {
          bSnp = false;
          break;  }
      }
    }

    //! Step: Determine if the start pos needs to be normilized.
    bool is_new_position = pos_1 != i;
    if (is_new_position) {
      sprintf((*this)["position"], "%u", i);
      sprintf((*this)["norm_pos"], "%u_to_%u", pos_1, i);
    }
    
    //! Step: Determine if this is actually an AMP.
    if ((sequence.get_circular_sequence_1(i - (n - 1), n) == first)  && (n > 1)) {
      this->_type = AMP;
      sprintf((*this)["size"], "%u", n);
      sprintf((*this)["new_copy_number"], "2");
      sprintf((*this)["orig_type"], "INS");
    }
  } break;

  case SNP:
  {
    assert(this->entry_exists("new_seq"));
    assert((*this)["new_seq"].size() == 1);

    //! Step: Initialize parameters.
    const base_char first = (*this)["new_seq"][0];

    //! Step: Compare bases.
    const base_char second = sequence.get_circular_sequence_1(pos_1, 1)[0];

    //! Step: If bases are not equal then it's not a valid snp.
    bool is_base_not_equal = (first != second);
    if (!is_base_not_equal) {
      sprintf((*this)["norm"], "is_not_valid");
    }
  } break;

  case SUB:
  {
    assert(this->entry_exists("size"));
    assert(this->entry_exists("new_seq"));

   //! Step: Initialize parameters.
    const size_t n = strtoul((*this)["size"].c_str(), NULL, 0);
    assert(n);
    const string first = (*this)["new_seq"];
    assert(first.size());

    const string second = sequence.get_circular_sequence_1(pos_1, n);
    const string third = sequence.get_circular_sequence_1(pos_1 + n, 1);

    if (first.find_first_of(second) != string::npos &&
        first.find_first_of(third) != string::npos ) {
      sprintf((*this)["norm"], "is_not_valid");
    }
  } break;

  case MOB:
  {
    assert(this->entry_exists("repeat_name"));
    assert(this->entry_exists("strand"));
    assert(this->entry_exists("duplication_size"));
  } break;

  case INV:
  {
    assert(this->entry_exists("size"));
    const size_t n =  strtoul((*this)["size"].c_str(), NULL, 0);
    assert(n);
  } break;

  case AMP:
  {
    assert(this->entry_exists("size"));
    assert(this->entry_exists("new_copy_number"));
  } break;

  case CON:
  {
    assert(this->entry_exists("size"));
    assert(this->entry_exists("region"));
  } break;

  default:
    break;
      
  }//End switch.

  return;
}



void cGenomeDiff::normalize_to_sequence(cReferenceSequences &ref)
{
  diff_entry_list_t muts = this->mutation_list();
  for (diff_entry_list_t::iterator it = muts.begin();
       it != muts.end(); it++) {
    cDiffEntry &mut = **it;
    mut.normalize_to_sequence(ref[mut["seq_id"]]);
  }

}

  
// All fields must be assigned in this table and be required fields of the gd entries.
map<gd_entry_type, sort_fields_item> diff_entry_sort_fields = make_map<gd_entry_type, sort_fields_item>
  (SNP, sort_fields_item(1, SEQ_ID, POSITION))
  (SUB, sort_fields_item(1, SEQ_ID, POSITION))
  (DEL, sort_fields_item(1, SEQ_ID, POSITION))
  (INS, sort_fields_item(1, SEQ_ID, POSITION))
  (MOB, sort_fields_item(1, SEQ_ID, POSITION))
  (AMP, sort_fields_item(1, SEQ_ID, POSITION))
  (INV, sort_fields_item(1, SEQ_ID, POSITION))
  (CON, sort_fields_item(1, SEQ_ID, POSITION))
  (RA,  sort_fields_item(2, SEQ_ID, POSITION))
  (MC,  sort_fields_item(3, SEQ_ID, START))
  (JC,  sort_fields_item(4, "side_1_seq_id", "side_1_position"))
  (CN,  sort_fields_item(5, SEQ_ID, START))
  (UN,  sort_fields_item(6, SEQ_ID, START))
  (CURA, sort_fields_item(7, "expert", "expert"))
  (FPOS, sort_fields_item(7, "expert", "expert"))
  (PHYL, sort_fields_item(7, "gd", "gd"))
  (TSEQ, sort_fields_item(7, "seq_id", "primer_1_start"))
  (PFLP, sort_fields_item(7, "seq_id", "primer_1_start"))
  (RFLP, sort_fields_item(7, "seq_id", "primer_1_start"))
  (PFGE, sort_fields_item(7, "seq_id", "enzyme"))
  (NOTE, sort_fields_item(7, "note", "note"))
;

map<gd_entry_type, uint8_t> sort_order = make_map<gd_entry_type, uint8_t>
  (SNP, 2)
  (SUB, 4)
  (DEL, 1)
  (INS, 3)
  (MOB, 5)
  (AMP, 6)
  (INV, 7)
  (CON, 8)
  (RA,  9)
  (MC,  10)
  (JC,  11)
  (CN,  12)  
  (UN,  13)
  (CURA, 14)
  (FPOS, 15)
  (PHYL, 16)
  (TSEQ, 17)
  (PFLP, 18)
  (RFLP, 19)
  (PFGE, 20)
  (NOTE, 20)
;


/*! Write this genome diff to a file.
 */
bool diff_entry_ptr_sort(const diff_entry_ptr_t& a, const diff_entry_ptr_t& b) {

  gd_entry_type a_type = a->_type;
  gd_entry_type b_type = b->_type;

  sort_fields_item a_sort_fields = diff_entry_sort_fields[a_type];
  sort_fields_item b_sort_fields = diff_entry_sort_fields[b_type];
  
  
  if (a_sort_fields._f1 < b_sort_fields._f1) {
    return true;
  } else if (a_sort_fields._f1 > b_sort_fields._f1) {
    return false;
  }
  
  string a_sort_field_2 = (*a)[a_sort_fields._f2];
  string b_sort_field_2 = (*b)[b_sort_fields._f2];
  
  if (a_sort_field_2 < b_sort_field_2) {
    return true;
  } else if (a_sort_field_2 > b_sort_field_2) {
    return false;
  }  

  uint32_t a_sort_field_3 = from_string<uint32_t>((*a)[a_sort_fields._f3]);
  uint32_t b_sort_field_3 = from_string<uint32_t>((*b)[b_sort_fields._f3]);
  
  if (a_sort_field_3 < b_sort_field_3) {
    return true;
  } else if (a_sort_field_3 > b_sort_field_3) {
    return false;
  }  
  
  uint8_t a_sort_order = sort_order[a_type];
  uint8_t b_sort_order = sort_order[b_type];

  if (a_sort_order < b_sort_order) {
    return true;
  } else if (a_sort_order > b_sort_order) {
    return false;
  } 
  
  // last sort by id
  uint32_t a_sort_id = from_string(a->_id);
  uint32_t b_sort_id = from_string(b->_id);

  if (a_sort_id < b_sort_id) {
    return true;
  } else if (a_sort_id > b_sort_id) {
    return false;
  } 
  
  return false;
}

bool diff_entry_sort(const cDiffEntry &_a, const cDiffEntry &_b) {
  cDiffEntry a =_a;
  cDiffEntry b = _b;

  gd_entry_type a_type = a._type;
  gd_entry_type b_type = b._type;

  sort_fields_item a_sort_fields = diff_entry_sort_fields[a_type];
  sort_fields_item b_sort_fields = diff_entry_sort_fields[b_type];


  if (a_sort_fields._f1 < b_sort_fields._f1) {
    return true;
  } else if (a_sort_fields._f1 > b_sort_fields._f1) {
    return false;
  }

  string a_sort_field_2 = a[a_sort_fields._f2];
  string b_sort_field_2 = b[b_sort_fields._f2];

  if (a_sort_field_2 < b_sort_field_2) {
    return true;
  } else if (a_sort_field_2 > b_sort_field_2) {
    return false;
  }

  uint32_t a_sort_field_3 = from_string<uint32_t>(a[a_sort_fields._f3]);
  uint32_t b_sort_field_3 = from_string<uint32_t>(b[b_sort_fields._f3]);

  if (a_sort_field_3 < b_sort_field_3) {
    return true;
  } else if (a_sort_field_3 > b_sort_field_3) {
    return false;
  }

  uint8_t a_sort_order = sort_order[a_type];
  uint8_t b_sort_order = sort_order[b_type];

  if (a_sort_order < b_sort_order) {
    return true;
  } else if (a_sort_order > b_sort_order) {
    return false;
  }

  // last sort by id
  uint32_t a_sort_id = from_string(a._id);
  uint32_t b_sort_id = from_string(b._id);

  if (a_sort_id < b_sort_id) {
    return true;
  } else if (a_sort_id > b_sort_id) {
    return false;
  }

  return false;
}

/*! Write this genome diff to a file.
  NOTES:
    1) If you want a diff entry to be commented out(prefix with '#') add the key
    "comment_out" to the diff entry.
 */
void cGenomeDiff::write(const string& filename) {
  string basename = cString(filename).get_base_name();
  string dir = cString(filename).remove_ending(basename);
  if (dir.size()) {
    create_path(dir);
  }
  ofstream os(filename.c_str());


  //! Step: Header lines.
  /*Always write version tag. It's how we identify it as a genome diff file
   in cGenomeDiff::read(). */
  fprintf(os, "#=GENOME_DIFF\t%s\n", metadata.version.c_str());
  
  fprintf(os, "#=AUTHOR\t%s\n", metadata.author.c_str());

  for (size_t i = 0; i < metadata.ref_seqs.size(); i++) {
    fprintf(os, "#=REFSEQ\t%s\n", metadata.ref_seqs[i].c_str());
  }

  for (size_t i = 0; i < metadata.read_seqs.size(); i++) {
    fprintf(os, "#=READSEQ\t%s\n", metadata.read_seqs[i].c_str());
  }
  if (!metadata.breseq_data.empty()) {
    for (map<key_t,string>::iterator it = metadata.breseq_data.begin();
         it != metadata.breseq_data.end(); it ++) {
      fprintf(os, "#=%s\t%s\n", it->first.c_str(), it->second.c_str());
    }
  }
  
  // sort
  this->sort();
  
  for(diff_entry_list_t::iterator it=_entry_list.begin(); it!=_entry_list.end(); ++it) {
    if (!(*it)->entry_exists("comment_out")) {
      fprintf(os, "%s\n", (**it).to_string().c_str());
    } else {
      (*it)->erase("comment_out");
      fprintf(os, "#%s\n", (**it).to_string().c_str());
    }
	}
  os.close();
}

void cGenomeDiff::remove(cGenomeDiff::group group)
{
  this->sort();
  diff_entry_list_t::iterator it1 = _entry_list.begin();
  diff_entry_list_t::iterator it2 = _entry_list.begin();

  //Mutations.
  while (it2 != _entry_list.end()) {
    if (!(**it2).is_mutation()) break;
    ++it2;
  }
  if (group == cGenomeDiff::MUTATIONS) {
    _entry_list.erase(it1, it2);
    return;
  }

  //Evidence.
  it1 = it2; 
  while (it2 != _entry_list.end()) {
    if (!(**it2).is_evidence()) break;
    ++it2;
  }
  if (group == cGenomeDiff::EVIDENCE) {
    _entry_list.erase(it1, it2);
    return;
  }

  //Validation.
  it1 = it2; 
  while (it2 != _entry_list.end()) {
    if (!(**it2).is_validation()) break;
    ++it2;
  }
  if (group == cGenomeDiff::VALIDATION) {
    _entry_list.erase(it1, it2);
    return;
  }

  return;
}

  
//! Removes all GD entries that aren't used as evidence.
void cGenomeDiff::filter_not_used_as_evidence(bool verbose)
{
  // Yes, I know the bool is useless.
  map<string,bool> used_evidence;
  
  diff_entry_list_t muts = this->mutation_list();
  //Iterate through all mutations
  for (diff_entry_list_t::iterator it = muts.begin(); it != muts.end(); it++)
  {    
    //For every piece of evidence this entry has
    for(uint32_t iter = 0; iter < (**it)._evidence.size(); iter++)
    {
      //Each piece of evidence will only get assigned to the map once.
      used_evidence[(**it)._evidence[iter]] = true;
    }
  }
  
  // We will be erasing inside the it loop.  This is to keep
  // track of whether or not we should iterate to the next element.
  bool it_iterate = true;
  
  //Iterate through all entries
  for (diff_entry_list_t::iterator it = _entry_list.begin(); it != _entry_list.end(); )
  {
    bool it_iterate = true;
    
    //Is this ID in our map of used_evidence?
    if(!(used_evidence.count((**it)._id)) && (**it).is_evidence())
    {
      //Inform the user
      if(verbose){cout << "NOT USED AS EVIDENCE: " << (**it)._id << endl;}
      
      //Remove this entry from the list.
      it = _entry_list.erase(it);
      
      //We just removed the current feauture, do not iterate.
      it_iterate = false;
    }
    
    // Iterate it ONLY if we haven't erased something.
    if(it_iterate)it++;
  }
}
  
//! Call to assure that every entry in a cGenomeDiff
//  has the same SEQ_ID as the ref_seq_info.
//  This will also try and check entry positions and
//  sizes against the length of the ref_seq_info.
bool cGenomeDiff::is_valid(cReferenceSequences& ref_seq_info, bool verbose)
{  
  //Go through every cDiffEntry for this cGenomeDiff
  for (diff_entry_list_t::iterator entry = _entry_list.begin(); entry != _entry_list.end(); entry++)
  {    
    //Grab the information based on type for this entry
    const list_t spec = line_specification[(**(entry))._type];
    
    //For every entry of this type go through each of their fields
    for(size_t i = 0; i < spec.size(); i++)
    {
      //Does the current field contain a SEQ_ID?
      if(spec[i].find(SEQ_ID) != string::npos)
      {
        bool no_match = true;
        vector<string> failure;
        
        for (vector<cAnnotatedSequence>::iterator it_as = ref_seq_info.begin(); it_as < ref_seq_info.end(); it_as++)
        {
          //If the current entry has any SEQ_ID fields, does that SEQ_ID
          // field match any from ref_seq_info?
          if((**(entry))[spec[i]] == it_as->m_seq_id)
            no_match = false;
          
          failure.push_back(it_as->m_seq_id);
        }
        
        //If we couldn't find any matching SEQ_IDs, perform notification and failure.
        if(no_match)
        {
          cout << "LOADED REFERENCE\t" << *failure.begin() << endl;
          for(vector<string>::iterator it_fail = ++failure.begin(); it_fail < failure.end(); it_fail++)cout << "\t\t\t\t\t" << *it_fail << endl;
          cout << "LOADED GENOMEDIFF\t" << (**(entry))[spec[i]] << " ID=" << (**(entry))._id << endl;
          return false;
        }
      }
      
      string temp_seq_id = "";
      
      //Find the previous SEQ_ID; the one associated with this position
      // To do this, we iterate backwards from the current field.
      for(int32_t x = 0 + i; x >= 0; --x)
      {
        //Does the current entry have a SEQ_ID field?
        if(spec[x].find(SEQ_ID) != string::npos)
        {
          temp_seq_id = (**(entry))[spec[x]];
          break;
        }
      }
      
      //Does the current entry have any POSITION fields?
      // WARNING!
      // Position check might fail if the entry has multiple
      // position fields as well as a size field.
      if(spec[i].find(POSITION) != string::npos)
      {        
        int32_t temp_pos = from_string<int32_t>((**(entry))[spec[i]]);
        
        //Grab the information based on type for this entry
        const list_t temp_spec = line_specification[(**(entry))._type];
        
        //For every entry of this type go through each of their fields
        for(size_t u = 0 + i; u < temp_spec.size(); u++)
        {
          //Does the current entry have a SIZE field?
          if(spec[u] == SIZE)
          {
            //Add the size field to the position, size should include the current
            // position, so subtract 1.
            temp_pos += from_string<int32_t>((**(entry))[temp_spec[u]]) - 1;
          }
        }        
        
        for(vector<cAnnotatedSequence>::iterator it_as = ref_seq_info.begin(); it_as < ref_seq_info.end(); it_as++)
        {
          //Does the position in this field, plus any field that might indicate
          //size, exceed the length of the relevant sequence in ref_seq_info?
          if(it_as->m_seq_id == temp_seq_id && temp_pos > it_as->m_length)
          {
            cout << "LOADED REFERENCE\t" << it_as->m_seq_id << "\tLENGTH:\t" << it_as->m_length << endl;
            cout << "LOADED GENOMEDIFF\t" << temp_seq_id << "\tID=" << (**(entry))._id << "\t" << temp_pos << " POTENTIAL POSITION" << endl;
            return false;
          }
        }
      }
      
      //Does the current entry have a START field?
      if(spec[i] == START)
      {        
        for(vector<cAnnotatedSequence>::iterator it_as = ref_seq_info.begin(); it_as < ref_seq_info.end(); it_as++)
        {
          //Does this entry have a START larger than ref_seq_info length?
          if(it_as->m_seq_id == temp_seq_id && from_string<int32_t>((**(entry))[spec[i]]) > it_as->m_length)
          {
            cout << "LOADED REFERENCE\t" << it_as->m_seq_id << "\tLENGTH:\t" << it_as->m_length << endl;
            cout << "LOADED GENOMEDIFF\t" << temp_seq_id << "\tID=" << (**(entry))._id << "\t" << (**(entry))[spec[i]] << " START" << endl;
            return false;
          }
        }
      }
      
      //Does the current entry have a END field?
      if(spec[i] == END)
      {        
        for(vector<cAnnotatedSequence>::iterator it_as = ref_seq_info.begin(); it_as < ref_seq_info.end(); it_as++)
        {
          //Does this entry have a END larger than ref_seq_info length?
          if(it_as->m_seq_id == temp_seq_id && from_string<int32_t>((**(entry))[spec[i]]) > it_as->m_length)
          {
            cout << "LOADED REFERENCE\t" << it_as->m_seq_id << "\tLENGTH:\t" << it_as->m_length << endl;
            cout << "LOADED GENOMEDIFF\t" << temp_seq_id << "\tID=" << (**(entry))._id << "\t" << (**(entry))[spec[i]] << " END" << endl;
            return false;
          }
        }        
      }
    }
  }
   
  //Notify the user that the files match.
  if(verbose)
    cout << "** LOADED FILES MATCH **" << endl;
  
  return true;
}
  
//! Call to generate random mutations.
void cGenomeDiff::random_mutations(const string& exclusion_file, const string& type, uint32_t number, uint32_t read_length, cAnnotatedSequence& ref_seq_info, uint32_t rand_seed, bool verbose)
{
  // If we have an exclusion_file to load, we will save
  // the info in this map.
  map<uint32_t, uint32_t> match_list;
  
  // Don't try and load the exlusion file if they didn't provide one.
  if(exclusion_file.size())
  {
    ifstream in(exclusion_file.c_str());
    ASSERT(in.good(), "Could not open exclusion file: " + exclusion_file);
    
    string line;
    
    // Grab 2 lines.  The file we'll be dealing with has a single header line
    // followed by the column names.  This will drop that info.
    getline(in, line);
    getline(in, line);
    
    while (!in.eof() && getline(in,line))
    {
      RemoveLeadingTrailingWhitespace(line);
      vector<string> cols = split_on_whitespace(line);
      
      // If we find the letter 'r' in the second colummn
      // we know that it's a reverse complement match.
      bool complement = (cols[1].find("r") != string::npos);
      if(complement)  {
        cols[1].resize(cols[1].size() - 1);  }
      
      ASSERT(cols.size() == 3, "Column size is incorrect");
      
      uint32_t start1 = from_string<uint32_t>(cols[0]);
      uint32_t start2 = from_string<uint32_t>(cols[1]);
      uint32_t match_size = from_string<uint32_t>(cols[2]);
      
      if(complement)
      {
        start2 = start2 - (match_size - 1);
      }
      
      if(match_list.count(start1))
      {
        if(match_list[start1] < match_size)  {
          match_list[start1] = match_size;  }
      }
      else
      {
        match_list[start1] = match_size;
      }
      
      if(match_list.count(start2))
      {
        if(match_list[start2] < match_size)  {
          match_list[start2] = match_size;  }
      }
      else
      {
        match_list[start2] = match_size;
      }
    }
    
    in.close();
    
    // Go through everything in the list and combine entries
    // that overlap the same area.
    for(map<uint32_t, uint32_t>::iterator i = match_list.begin(); i != match_list.end();)
    {
      bool no_loop = true;
      uint32_t end_pos = (*i).first + (*i).second;
      uint32_t& uSize = (*i).second;
      
      for(map<uint32_t, uint32_t>::iterator j = ++i; j != match_list.end() && ((*j).first - 1) <= end_pos;)
      {
        uint32_t pot_end_pos = (*j).first + (*j).second;
        if(pot_end_pos > end_pos)
        {
          uSize += pot_end_pos - end_pos;
          end_pos = pot_end_pos;
        }
        
        map<uint32_t, uint32_t>::iterator j_temp = j;
        j_temp++;
        match_list.erase(j);      
        j = j_temp;
        i = j;
        no_loop = false;
      }
      
      if(no_loop)  {
        i++;  }
    }
  } // Done loading exclusion file.
  
  vector<string> type_options = split_on_any(type, ":-");
  gd_entry_type mut_type;
  int32_t uBuffer = (read_length * 2) + 1;
  uint32_t max_attempts = (ref_seq_info.get_sequence_size() / read_length) * 2;
  uint32_t uAttempts = 0;
  
  const uint32_t seed_value = rand_seed;
  srand(seed_value);
  metadata.author = "RANDOM GENERATOR SEED - " + to_string(seed_value);
  
  //Find the string value in the lookup table and cast index to enumeration.
  const size_t lookup_table_size = gd_entry_type_lookup_table.size();
  for (size_t i = 0; i < lookup_table_size; i++) {
    if (type_options[0] == gd_entry_type_lookup_table[i]) {
      mut_type = (gd_entry_type) i;
      break;
    }
  }
  
  if(verbose)  {
    CHECK(number < 30000, "Number of requested mutations is large.\nAttempting this many mutations could take awhile.");
    cout << "Generating " << number << " " << type_options[0] << " mutations." << endl;
  }
  
  switch(mut_type)
  {
    case SNP :
    {      
      set<uint32_t> used_positions;
      
      for(uint32_t i = 0; i < number && uAttempts < max_attempts; i++)
      {
        uAttempts++;
        uint32_t rand_pos = (rand() % ref_seq_info.get_sequence_size()) + 1;
        bool bRedo = false;
        
        for(map<uint32_t, uint32_t>::iterator j = match_list.begin(); j != match_list.end(); j++)
        {
          if(rand_pos >= (*j).first && rand_pos < ((*j).first + (*j).second))  {
            bRedo = true;
            break;  }
        }
        
        if(bRedo)  {
          i--;
          continue;  }
        
        for(set<uint32_t>::iterator k = used_positions.begin(); k != used_positions.end(); k++)
        {
          if(abs(static_cast<int32_t>((*k) - rand_pos)) < uBuffer)  {
            bRedo = true;
            break;  }
        }
        
        if(bRedo)  {
          i--;
          continue;  }
        
        cDiffEntry new_item;        
        new_item._type = mut_type;
        new_item["seq_id"] = ref_seq_info.m_seq_id;
        new_item["position"] = to_string(rand_pos);
        new_item["new_seq"] = FastqSimulationUtilities::get_random_error_base(ref_seq_info.m_fasta_sequence.m_sequence.at(rand_pos - 1));        
        
        uAttempts = 0;
        
        new_item.normalize_to_sequence(ref_seq_info);
        if(from_string<uint32_t>(new_item["position"]) != rand_pos)  {
          i--;
          continue;  }
        
        used_positions.insert(rand_pos);
        
        add(new_item);
      }      
    }  break;
      
    case DEL :
    {
      uint32_t opt_1 = 1;
      uint32_t opt_2 = 1;      
      map<uint32_t, uint32_t> used_positions;
      
      switch(type_options.size())
      {
        case 1:  {
        }  break;
          
        case 2:  {
          opt_1 = from_string<uint32_t>(type_options[1]);
          opt_2 = from_string<uint32_t>(type_options[1]);
        }  break;
          
        case 3:  {
          opt_1 = from_string<uint32_t>(type_options[1]);
          opt_2 = from_string<uint32_t>(type_options[2]);
        }  break;
          
        default:      
          ERROR("CANNOT PARSE: " + type);
      }
      
      if(verbose)  {
        cout << "SIZE RANGE: " << opt_1 <<  " - " << opt_2 << endl;  }
      
      for(uint32_t i = 0; i < number && uAttempts < max_attempts; i++)
      {
        uAttempts++;
        
        uint32_t del_size = (i % (opt_2 - (opt_1-1))) + opt_1;
        if(opt_2 - opt_1 >= number)  {
          del_size = (rand() % number) + opt_1;  }
        uint32_t rand_pos = (rand() % (ref_seq_info.get_sequence_size() - del_size)) + 1;
        bool bRedo = false;
        
        for(map<uint32_t, uint32_t>::iterator j = match_list.begin(); j != match_list.end(); j++)
        {
          if((rand_pos >= (*j).first && rand_pos < ((*j).first + (*j).second)) ||
             (rand_pos+del_size-1 >= (*j).first && rand_pos+del_size-1 < ((*j).first + (*j).second)) ||
             (rand_pos <= (*j).first && rand_pos+del_size-1 >= ((*j).first + (*j).second)))  {
            bRedo = true;
            break;  }
        }
        
        if(bRedo)  {
          i--;
          continue;  }
        
        for(map<uint32_t, uint32_t>::iterator k = used_positions.begin(); k != used_positions.end(); k++)
        {
          if((rand_pos >= (*k).first && rand_pos < ((*k).first + (*k).second)) ||
             (rand_pos+del_size-1 >= (*k).first && rand_pos+del_size-1 < ((*k).first + (*k).second)) ||
             (rand_pos <= (*k).first && rand_pos+del_size-1 >= ((*k).first + (*k).second)))  {
            bRedo = true;
            break;  }
          
          if((abs(static_cast<int32_t>((*k).first - rand_pos)) < uBuffer) ||
             (abs(static_cast<int32_t>((*k).first+(*k).second-1 - rand_pos)) < uBuffer))  {
            bRedo = true;
            break;  }
        }
        
        if(bRedo)  {
          i--;
          continue;  }
        
        cDiffEntry new_item;        
        new_item._type = mut_type;
        new_item["seq_id"] = ref_seq_info.m_seq_id;
        new_item["position"] = to_string(rand_pos);        
        new_item["size"] = to_string(del_size);        
        
        uAttempts = 0;
        
        new_item.normalize_to_sequence(ref_seq_info);
        if(from_string<uint32_t>(new_item["position"]) != rand_pos)  {
          i--;
          continue;  }
        
        used_positions[rand_pos] = del_size;
        
        add(new_item);
      }
    }  break;
      
    case INS :
    {
      uint32_t opt_1 = 1;
      uint32_t opt_2 = 1;      
      set<uint32_t> used_positions;
      
      switch(type_options.size())
      {
        case 1:  {
        }  break;
          
        case 2:  {
          opt_1 = from_string<uint32_t>(type_options[1]);
          opt_2 = from_string<uint32_t>(type_options[1]);
        }  break;
          
        case 3:  {
          opt_1 = from_string<uint32_t>(type_options[1]);
          opt_2 = from_string<uint32_t>(type_options[2]);
        }  break;
          
        default:      
          ERROR("CANNOT PARSE: " + type);
      }
      
      if(verbose)  {
        cout << "SIZE RANGE: " << opt_1 <<  " - " << opt_2 << endl;  }
      
      for(uint32_t i = 0; i < number && uAttempts < max_attempts; i++)
      {
        uAttempts++;
        
        uint32_t ins_size = (i % (opt_2 - (opt_1-1))) + opt_1;
        if(opt_2 - opt_1 >= number)  {
          ins_size = (rand() % number) + opt_1;  }
        uint32_t rand_pos = (rand() % (ref_seq_info.get_sequence_size())) + 1;
        bool bRedo = false;
        
        for(map<uint32_t, uint32_t>::iterator j = match_list.begin(); j != match_list.end(); j++)
        {
          if(rand_pos >= (*j).first && rand_pos < ((*j).first + (*j).second))  {
            bRedo = true;
            break;  }
        }
        
        if(bRedo)  {
          i--;
          continue;  }
        
        for(set<uint32_t>::iterator k = used_positions.begin(); k != used_positions.end(); k++)
        {
          if(abs(static_cast<int32_t>((*k) - rand_pos)) < uBuffer)  {
            bRedo = true;
            break;  }
        }
        
        if(bRedo)  {
          i--;
          continue;  }
        
        cDiffEntry new_item;        
        new_item._type = mut_type;
        new_item["seq_id"] = ref_seq_info.m_seq_id;
        new_item["position"] = to_string(rand_pos);      
        
        string ins_seq = "";        
        for(uint32_t ij = 0; ij < ins_size; ij++)  {
          ins_seq += FastqSimulationUtilities::get_random_insertion_base();  }
        
        new_item["new_seq"] = ins_seq;
        
        uAttempts = 0;
        
        new_item.normalize_to_sequence(ref_seq_info);
        if((from_string<uint32_t>(new_item["position"]) != rand_pos) || (new_item["new_seq"] != ins_seq) || (new_item._type != mut_type))  {
          i--;
          continue;  }
        
        used_positions.insert(rand_pos);
        
        add(new_item);
      }
    }  break;
      
    case MOB :
    {      
      //ERROR("THE BRESEQENSTEIN MUTATION GENERATOR DOES NOT YET HANDLE MOBS\nESPECIALLY IF THEY HAVE TORCHES AND PITCHFORKS");
      
      uint32_t opt_1 = 0;
      uint32_t opt_2 = 0;
      uint32_t repeats = 0;
      set<uint32_t> used_positions;
      map<uint32_t,string> ins_elements;
      
      for (cSequenceFeatureList::iterator it_rep = ref_seq_info.m_repeats.begin(); it_rep != ref_seq_info.m_repeats.end(); it_rep++)
      {
        ins_elements[repeats] = (*it_rep)->SafeGet("name");
        repeats++;
      }
      
      switch(type_options.size())
      {
        case 1:  {
        }  break;
          
        case 2:  {
          opt_1 = from_string<uint32_t>(type_options[1]);
          opt_2 = from_string<uint32_t>(type_options[1]);
        }  break;
          
        case 3:  {
          opt_1 = from_string<uint32_t>(type_options[1]);
          opt_2 = from_string<uint32_t>(type_options[2]);
        }  break;
          
        default:      
          ERROR("CANNOT PARSE: " + type);
      }
      
      if(verbose)  {
        cout << "REPEAT SIZE RANGE: " << opt_1 <<  " - " << opt_2 << endl;  }
      
      for(uint32_t i = 0; i < number && uAttempts < max_attempts; i++)
      {
        uAttempts++;
        
        uint32_t rep_size = (i % (opt_2 - (opt_1-1))) + opt_1;
        if(opt_2 - opt_1 >= number)  {
          rep_size = (rand() % number) + opt_1;  }
        uint32_t ins_fam = rand() % (ins_elements.size());
        uint32_t rand_pos = (rand() % (ref_seq_info.get_sequence_size())) + 1;
        int32_t new_strand = ((rand() % 2) > 0) ? 1 : -1;
        bool bRedo = false;
        
        for(map<uint32_t, uint32_t>::iterator j = match_list.begin(); j != match_list.end(); j++)
        {
          if(rand_pos >= (*j).first && rand_pos < ((*j).first + (*j).second))  {
            bRedo = true;
            break;  }
        }
        
        if(bRedo)  {
          i--;
          continue;  }
        
        for(set<uint32_t>::iterator k = used_positions.begin(); k != used_positions.end(); k++)
        {
          if(abs(static_cast<int32_t>((*k) - rand_pos)) < uBuffer)  {
            bRedo = true;
            break;  }
        }
        
        if(bRedo)  {
          i--;
          continue;  }
        
        cDiffEntry new_item;        
        new_item._type = mut_type;
        new_item["seq_id"] = ref_seq_info.m_seq_id;
        new_item["position"] = to_string(rand_pos);
        new_item["repeat_name"] = ins_elements[ins_fam];        
        new_item["strand"] = to_string(new_strand);        
        new_item["duplication_size"] = to_string(rep_size);
        
        cDiffEntry fake_item_ins;        
        fake_item_ins._type = INS;
        fake_item_ins["seq_id"] = ref_seq_info.m_seq_id;
        fake_item_ins["position"] = to_string(rand_pos);
        fake_item_ins["new_seq"] = ref_seq_info.get_sequence_1(rand_pos, rand_pos+rep_size-1);
        
        uAttempts = 0;
        
        fake_item_ins.normalize_to_sequence(ref_seq_info);
        if((from_string<uint32_t>(fake_item_ins["position"]) != rand_pos) || (fake_item_ins["new_seq"] != ref_seq_info.get_sequence_1(rand_pos, rand_pos+rep_size-1)) || (fake_item_ins._type != INS))  {
          i--;
          continue;  }
        
        new_item.normalize_to_sequence(ref_seq_info);
        
        used_positions.insert(rand_pos);
        
        add(new_item);
      }
    }  break;
      
    default:
      ERROR("MUTATION TYPE NOT HANDLED: " + type_options[0]);
  }
  
  CHECK(max_attempts != uAttempts, "Forced to halt mutation generation.\nAttempted " +
        to_string(uAttempts) + " times to generate another mutation.\n" + 
        "It's likely that it's no longer possible to add new mutations.");
  
}

void cGenomeDiff::add_breseq_data(const key_t &key, const string& value)
{
  this->metadata.breseq_data.insert(pair<string,string>(key, value));
}


// Convert GD file to GVF file
void GDtoGVF( const string &gdfile, const string &gvffile, bool snv_only){
  
  cGenomeDiff gd_object(gdfile);
  diff_entry_list_t diff_entry_list = gd_object.list();
  diff_entry_list_t::iterator it = diff_entry_list.begin();
  
  // Stores the features
  vector< vector<string> > features;
  vector< vector<string> > featuresGVF;
  // Keeps track of the index of the entry associated with a particular evidence number
  map< string, int > eDict;

  //Read input into array
  ifstream gd( gdfile.c_str() );
  string line;
  getline( gd, line);

  while( !gd.eof() )
  {
    // split line on tabs
    char * cstr = new char [line.size()+1];
    strcpy (cstr, line.c_str());

    if( cstr[0] == '#' ){ getline(gd,line); continue; }
    vector<string> feature;
    char * pch;
    pch = strtok(cstr,"\t");

    while (pch != NULL)
    {
        feature.push_back(pch);
        pch = strtok (NULL, "\t");
        
    }  
    features.push_back(feature);

    // If it is evidence, note its index
    if( feature[0].size() == 2 ){
        eDict[ feature[1]] = (int)features.size()-1;
    }

    delete[] cstr;
    getline(gd,line);
      
  }
  gd.close();
    
  // Processes the features
  // gvf[0]: ID of reference
  // gvf[1]: Source
  // gvf[2]: Type
  // gvf[3]: Start
  // gvf[4]: End
  // gvf[5]: Score
  // gvf[6]: Strand
  // gvf[7]: Phase
  // gvf[8]: Attributes    

  for( size_t i=0; i<features.size() ; i++ )
  {
    if (it == diff_entry_list.end()) break;
    cDiffEntry& de = **it;
    it++;
    
    vector<string> gvf(9,"");

    for( int j=5; j<8; j++ ){
      gvf[j] = ".";
    }

    if( features[i].size() <= 4 || features[i][0].size() == 2 ){
      continue;
    }

    // SeqID
    gvf[0] = features[i][3];
    // Source
    gvf[1] = "breseq";
    // Type
    gvf[3] = features[i][4];

    if( features[i][0].compare( "SNP") == 0 )
    {
      gvf[2] = "SNV";
      stringstream ss;
      ss << atoi( gvf[3].c_str() );
      ss >> gvf[4];
      gvf[8].append("Variant_seq=").append( features[i][5] );
      
      //Look for evidence information
      vector<string> evidenceNums = split( features[i][2], "," );
      vector<string> evidence = features[ eDict[ evidenceNums[0] ] ];
      
      gvf[6] = "+";
      
      if (evidence.size() > 0) {
        gvf[8].append(";Reference_seq=").append( evidence[5] );
      }
      
      for( size_t j=0; j<evidence.size(); j++ ){
        string s = evidence[j];
        if( s.size()>8 && s.substr(0,8).compare("quality=") == 0){
          gvf[5] = s.substr(8,s.size()-8);
        }
        if( s.size()>8 && s.substr(0,8).compare("new_cov=") == 0){
          s = s.substr(8,s.size()-8);
          vector<string> covs = split( s, "/" );
          uint32_t cov = from_string<uint32_t>(covs[0]) + from_string<uint32_t>(covs[1]);
          gvf[8] = gvf[8].append(";Variant_reads=").append(to_string(cov));
        }
      
        if( s.size()>8 && s.substr(0,8).compare("tot_cov=") == 0){
          s = s.substr(8,s.size()-8);
          vector<string> covs = split( s, "/" );
          uint32_t cov = from_string<uint32_t>(covs[0]) + from_string<uint32_t>(covs[1]);
          gvf[8] = gvf[8].append(";Total_reads=").append(to_string(cov));
        }
      }
      
      for( size_t j=0; j<features[i].size(); j++ ){
        if( features[i][j].size()>10 && features[i][j].substr(0,10).compare("frequency=") == 0){
          gvf[8].append(";Variant_freq=").append( features[i][j].substr(10,features[i][j].size()-10 ) );
        }
      }
      
      if (de.entry_exists("snp_type")) {
        if (de["snp_type"] == "nonsynonymous") {
          gvf[8].append(";Variant_effect=non_synonymous_codon");
        }
        else if (de["snp_type"] == "synonymous") {
          gvf[8].append(";Variant_effect=synonymous_codon");
        }
        else if (de["snp_type"] == "intergenic") {
          gvf[8].append(";Variant_effect=intergenic_variant");
        }
        else if (de["snp_type"] == "RNA") {
          gvf[8].append(";Variant_effect=nc_transcript_variant");
        }
        else if (de["snp_type"] == "pseudogene") {
          ERROR("Mutation annotated as pseudogene encountered. Not clear how to annotate.");
        }
      }
    }

    else if( features[i][0].compare("SUB") == 0 ){
      //Look for evidence information
      vector<string> evidenceNums = split( features[i][2], "," );
      string s = "";
      for( size_t j=0; j<evidenceNums.size(); j++ ){
        vector<string> e = features[ eDict[ evidenceNums[j] ] ];
        s.append( e[5] );
      }
      gvf[8].append("Reference_seq=").append(s);
      gvf[2] = "substitution";
      stringstream ss;
      ss << atoi( features[i][4].c_str() ) + atoi( features[i][5].c_str() );
      ss >> gvf[4]; 
      gvf[8].append(";Variant_seq=").append( features[i][6] );
    }

    else if( features[i][0].compare("DEL") == 0){
      gvf[2] = "deletion";
      stringstream ss; int length = atoi(features[i][4].c_str()) + atoi(features[i][5].c_str());
      ss << length;
      ss >> gvf[4];
    }

    else if( features[i][0].compare("INS") == 0 ){
      gvf[2] = "insertion";
      gvf[4] = gvf[3];
      gvf[8] = gvf[8].append("Variant_seq=").append( features[i][5] );
    }

    else if( features[i][0].compare("MOB") == 0 ){
      gvf[2] = "transposable_element";
      gvf[4] = gvf[3];
      gvf[8] = string("ID=").append( features[i][5] );
      //Strand
      if( atoi( features[i][6].c_str() ) > 0 ){
          gvf[6] = "+";
      }
      else{ gvf[6] = "-"; }
    }

    else if( features[i][0].compare("AMP") == 0 )
    {
      WARN("Input file contains AMP features that are currently not converted to GVF");
      /* @JEB TODO This code seg faults. Broken 2011-11-17.
      int x, y; 
      gvf[2] = "insertion";
      stringstream ss;
      ss << gvf[3] << gvf[5]; ss >> x; ss >> y; x += y; ss << x;
      ss >> gvf[4];
      gvf[3] = gvf[4];
      gvf[8].append( "Variant_seq=" );
      for( int i=0; i < (atoi(features[i][6].c_str())-1)*atoi(features[i][5].c_str()); i++ ){
        gvf[8].append("N");
      }
      */
    }
    else if( features[i][0].compare("INV") == 0 ){
      gvf[2] = "inversion";
      gvf[3] = features[i][4];
      stringstream ss;
      ss << atoi( features[i][4].c_str() ) + atoi( features[i][5].c_str() );
      ss >> gvf[4]; 
    }
    else if( features[i][0].compare("CON") == 0 ){
      gvf[2] = "substitution";
      gvf[4] = gvf[3];
      stringstream ss;
      ss << atoi( features[i][4].c_str() ) + atoi( features[i][5].c_str() );
      ss >> gvf[4];
      gvf[8].append(";Variant_seq=").append( features[i][6] );
    }

    // ID attribute
    if( gvf[8].compare( "" ) == 0 || ( gvf[8].size()>8 && !gvf[8].substr(0,3).compare("ID=") == 0) ){
      string s = "";
      s.append("ID=").append(gvf[0]).append(":").append(gvf[1]).append(":");
      s.append(gvf[2]).append(":").append(gvf[3]).append(";");
      s.append(gvf[8]);
      gvf[8] = s;
    }

    if (!snv_only || (gvf[2] == "SNV"))
      featuresGVF.push_back(gvf);
  }

  // Write results to file
  ofstream output( gvffile.c_str() );
  output << "##gff-version 3" << endl;
  output << "##gvf-version 1.0" << endl;
  output << "" << endl;
  output << "##source-method Source=breseq;Type=SNV;Dbxref=http://barricklab.org/breseq;Comment=Mapping and variant calling with breseq;" << endl;
  output << "" << endl;
  for( size_t i=0; i<featuresGVF.size(); i++ ){
    for( size_t j=0; j<featuresGVF[i].size(); j++ ){
      output << featuresGVF[i][j] << "\t";
    }
    output << "\n";
  }
  output.close();
    
}

void VCFtoGD( const string& vcffile, const string& gdfile ){
    // Stores the features
    vector< vector<string> > featuresVCF;
    vector< vector<string> > featuresGD;
    vector< vector<string> > evidences;
    // Keeps track of the index of the entry associated with a particular evidence number
    
    //Read input into array
    ifstream vcf( vcffile.c_str() );
    string line;
    getline( vcf, line);
    
    while( !vcf.eof() ){
        // split line on tabs
        char * cstr = new char [line.size()+1];
        strcpy (cstr, line.c_str());
        
        if( cstr[0] == '#' ){ getline(vcf,line); continue; }
        vector<string> feature;
        char * pch;
        pch = strtok(cstr,"\t");
        
        while (pch != NULL)
        {
            feature.push_back(pch);
            pch = strtok (NULL, "\t");
            
        }  
        featuresVCF.push_back(feature);
        
        delete[] cstr;
        getline(vcf,line);
        
    }
    vcf.close();
    
    for( size_t i=0; i<featuresVCF.size(); i++ ){
        vector<string> gd(9,"");
        vector<string> ev(9,"");

        // SeqID
        if( featuresVCF[i][3].size() > featuresVCF[i][4].size() ){
            gd[0] = "DEL";
        }
        else if( featuresVCF[i][3].size() < featuresVCF[i][4].size() ){
            gd[0] = "INS";
        }
        else if( featuresVCF[i][3].size() == 1 ){
            gd[0] = "SNP";
        }
        else{
            gd[0] = "SUB";
        }
        
        stringstream ss; ss << i+1;
        ss >> gd[1];
        ss << i+featuresVCF.size()+1;
        ss >> gd[2];
        gd[3] = featuresVCF[i][0];
        gd[4] = featuresVCF[i][1];
        gd[5] = featuresVCF[i][4];
        
        ev[0] = "RA";
        ss << i+featuresVCF.size();
        ss >> ev[1];
        ev[2] = ".";
        ev[3] = featuresVCF[i][0];
        ev[4] = featuresVCF[i][1];
        ev[5] = "0";
        ev[6] = featuresVCF[i][3];
        ev[7] = featuresVCF[i][4];
        ev[8] = string("quality=").append( featuresVCF[i][5] );
        
        featuresGD.push_back(gd);
        evidences.push_back(ev);
        
    }
    
    // Write results to file
    ofstream output( gdfile.c_str() );
    for( size_t i=0; i<featuresGD.size(); i++ ){
        for( size_t j=0; j<featuresGD[i].size(); j++ ){
            output << featuresGD[i][j] << "\t";
        }
        output << "\n";
    }
    output.close();
}

void GDtoCircos(const vector<string> &gd_file_names, 
                const vector<string> &reference_file_names,
                const string &circos_directory){
  //Due to circos' unchangeable method of reversing labels (including glyphs)
  //after the 6 o'clock position on a graph, I am manually adding which
  //genomes will be reversed on the MOB graph to compensate for this.
  
  //The author emailed me on 30/4/2012 saying that he's working on an
  //option for enabling/disabling this. Until then, the intelligent method right
  //now will be kept.
  //Aaron
  
  cGenomeDiff combined_gd;
  
  int32_t number_of_mutations = 0;
  
  for (int32_t i = 0; i < gd_file_names.size(); i++){
    cGenomeDiff single_gd(gd_file_names[i]);
    combined_gd.merge(single_gd);
    number_of_mutations += single_gd.mutation_list().size();
  }
  
  cReferenceSequences ref;
  ref.LoadFiles(reference_file_names);
  ref.annotate_mutations(combined_gd, true);
  const vector<string> seq_ids(ref.seq_ids());
  
  string make_me;
  
  Settings settings("");
  
  
  create_path(circos_directory);
  create_path(circos_directory + "/data");
  create_path(circos_directory + "/etc");
  
  //copy run script
  copy_file(settings.program_data_path + "/run_circos.sh", circos_directory + "/run_circos.sh");
  
  //filling circos_dir/etc
  
  copy_file(settings.program_data_path + "/ideogram.conf", circos_directory + "/etc/ideogram.conf");
  copy_file(settings.program_data_path + "/karyotype.and.layout.conf", circos_directory + "/etc/karyotype.and.layout.conf");
  copy_file(settings.program_data_path + "/indels.conf", circos_directory + "/etc/indels.conf");
  copy_file(settings.program_data_path + "/mobs.conf", circos_directory + "/etc/mobs.conf");
  copy_file(settings.program_data_path + "/mutations.conf", circos_directory + "/etc/mutations.conf");
  copy_file(settings.program_data_path + "/combined_circos.conf", circos_directory + "/etc/combined_circos.conf");
  
  //filling circos_dir/data
  
  ofstream karyotype_file;
  ofstream empty_file;
  
  make_me = circos_directory + "/data/karyotype.txt";
  karyotype_file.open(make_me.c_str());
  make_me = circos_directory + "/data/empty_data.txt";
  empty_file.open(make_me.c_str());
  
  map <string, pair<int32_t, int32_t> > right_side;
  map <string, pair<int32_t, int32_t> > left_side;
  
  pair<int32_t, int32_t> push_pair;
  
  //keeps track of current position when examining sequence sizes of genomes
  int32_t current_position = 0;
  bool push_left = false;
  
  int32_t half_ref_length;
  half_ref_length = int32_t(ref.total_length() / 2) + 1;
  
  for (uint32_t i = 0; i < seq_ids.size(); i++){
    uint32_t seq_size;
    seq_size = ref[seq_ids[i]].get_sequence_size();
    
    karyotype_file << "chr - " << seq_ids[i] << " 1 1 " <<
                      seq_size << " black" << endl;
    empty_file << seq_ids[i] << " 1 2 1" << endl;
    
    //if seq_size goes past halfway point of total length of genomes,
    //add this sequence and its bounds to the left_side vector.
    current_position += seq_size;
    
    
    if (!push_left){
      //if current_position equals the cusp, enable left side
      //and push current sequence to the right.
      if (current_position == half_ref_length) {
        push_left = true;
        
        push_pair.first = 1;
        push_pair.second = seq_size;
        right_side[seq_ids[i]] = push_pair;
        
        continue;
      }
      //if it's greater, fragment the sequence's bounds.
      else if (current_position > half_ref_length) {
        push_left = true;
        
        push_pair.first = 1;
        push_pair.second = half_ref_length - (current_position - seq_size);
        right_side[seq_ids[i]] = push_pair;
        
        push_pair.first = half_ref_length - (current_position - seq_size) + 1;
        push_pair.second = seq_size;
        left_side[seq_ids[i]] = push_pair;
        
        continue;
      }
    }
    
    push_pair.first = 1;
    push_pair.second = seq_size;
    
    if (push_left){
      left_side[seq_ids[i]] = push_pair;
    }
    else{
      right_side[seq_ids[i]] = push_pair;
    }
    
  }
  
  karyotype_file.close();
  empty_file.close();
  
  //minimum tile size width for indel graph
  const int32_t MIN_WIDTH = ref.total_length() * .0025;
  
  ofstream indel_file;
  ofstream mob_file;
  
  ofstream synonymous_mutation_file;
  ofstream nonsynonymous_mutation_file;
  ofstream npi_mutation_file;
  
  make_me = circos_directory + "/data/indels_data.txt";
  indel_file.open(make_me.c_str());
  make_me = circos_directory + "/data/mobs_data.txt";
  mob_file.open(make_me.c_str());
  
  make_me = circos_directory + "/data/syn_data.txt";
  synonymous_mutation_file.open(make_me.c_str());
  make_me = circos_directory + "/data/nonsyn_data.txt";
  nonsynonymous_mutation_file.open(make_me.c_str());
  make_me = circos_directory + "/data/npi_data.txt";
  npi_mutation_file.open(make_me.c_str());
  
  map <string, string> mob_colors;
  
  //colors for mobs
  const char* c_colors[] = {"vvdred", "vvdgreen", "vvdblue", "vvdorange", "vvdpurple",
                            "vdred", "vdgreen", "vdblue", "vdorange", "vdpurple",
                            "dred", "dgreen", "dblue", "dorange", "dpurple",
                            "red", "green", "blue", "orange", "purple",
                            "lred", "lgreen", "lblue", "lorange", "lpurple",
                            "vlred", "vlgreen", "vlblue", "vlorange", "vlpurple",
                            "vvlred", "vvlgreen", "vvlblue",  "vvlorange", "vvlpurple"};
  
  vector<string> colors(c_colors, c_colors + 35);
  string color;
  int32_t next_color = 0;
  
  diff_entry_list_t gd_data = combined_gd.mutation_list();
  
  for (diff_entry_list_t::iterator it = gd_data.begin(); it != gd_data.end(); it++){
    
    cDiffEntry diff = **it;
    
    int32_t width;
    string direction;
    
    
    if (diff._type == INS){
      width = from_string<int32_t>(diff["new_seq"]);
      if (width < MIN_WIDTH){
        width = MIN_WIDTH;
      }
      indel_file << diff["seq_id"] << " " <<
                    diff["position"] << " " <<
                    from_string<int32_t>(diff["position"]) + width << " " <<
                    "color=vdgreen" << endl;
    }
    else if (diff._type == AMP){
      width = from_string<int32_t>(diff["size"]);
      if (width < MIN_WIDTH){
        width = MIN_WIDTH;
      }
      indel_file << diff["seq_id"] << " " <<
                    diff["position"] << " " <<
                    from_string<int32_t>(diff["position"]) + width << " " <<
                    "color=vdgreen" << endl;
    }
    else if (diff._type == DEL){
      width = from_string<int32_t>(diff["size"]);
      if (width < MIN_WIDTH){
        width = MIN_WIDTH;
      }
      indel_file << diff["seq_id"] << " " <<
                    from_string<int32_t>(diff["position"]) - width << " " <<
                    diff["position"] << " " <<
                    "color=vdred" << endl;
    }
    else if(diff._type == SNP || diff._type == SUB){
      if (diff["snp_type"] == "synonymous"){
        synonymous_mutation_file << diff["seq_id"] << " " <<
                                    diff["position"] << " " <<
                                    diff["position"] << endl;
      }
      else if (diff["snp_type"] == "nonsynonymous"){
        nonsynonymous_mutation_file << diff["seq_id"] << " " <<
                                    diff["position"] << " " <<
                                    diff["position"] << endl;
      }
      else{
        npi_mutation_file << diff["seq_id"] << " " <<
                                    diff["position"] << " " <<
                                    diff["position"] << endl;
      }
      
    }
    else if(diff._type == MOB){
      
      //if mob is on left side of graph...reverse direction
      if (left_side.count(diff["seq_id"]) > 0){
        if (left_side[diff["seq_id"]].first <= from_string<int32_t>(diff["position"]) &&
            from_string<int32_t>(diff["position"]) <= left_side[diff["seq_id"]].second){
          if( diff["strand"] == "1"){
            direction = "left";
          }
          else{
            direction = "right";
          }
        }
        else{
          if ( diff["strand"] == "1"){
            direction = "right";
          }
          else{
            direction = "left";
          }
        }
      }
      else{
        if( diff["strand"] == "1"){
          direction = "right";
        }
        else{
          direction = "left";
        }
      }
      
      if (mob_colors.count(diff["repeat_name"]) == 0){
        color = colors[next_color];
        mob_colors[diff["repeat_name"]] = color;
        next_color++;
      }
      else{
        color = mob_colors[diff["repeat_name"]];
      }
      
      mob_file << diff["seq_id"] << " " <<
                  diff["position"] << " " <<
                  diff["position"] << " " <<
                  "o" << direction << " " <<
                  "color=" << color << endl;
    }
  }
  
//  diff_entry_list_t gd_data = combined_gd.mutation_list();
  
//  for (diff_entry_list_t::iterator it = gd_data.begin(); it != gd_data.end(); it++){
    
//    cDiffEntry diff = **it;
  
  //reference sequence MOBs
  for(int32_t i = 0; i < ref.size(); i++){
    cAnnotatedSequence ref_seq = ref[i];
    
    for(cSequenceFeatureList::iterator it = ref_seq.m_repeats.begin(); it != ref_seq.m_repeats.end(); it++){
      cSequenceFeature seq_feature = **it;
      int32_t middle = int32_t(seq_feature.m_start + seq_feature.m_end) / 2;
      
      string direction;
      string color;
      
      if (left_side.count(ref_seq.m_seq_id) > 0){
        if (left_side[ref_seq.m_seq_id].first <= middle &&
            middle <= left_side[ref_seq.m_seq_id].second){
          if (seq_feature.m_strand == 1){
            direction = "left";
          }
          else{
            direction = "right";
          }
        }
        else{
          if (seq_feature.m_strand == 1){
            direction = "right";
          } 
          else{
            direction = "left";
          }
        }
      }
      else{
        if (seq_feature.m_strand == 1){
          direction = "right";
        } 
        else{
          direction = "left";
        }
      }
      
      if (mob_colors.count(seq_feature["name"]) == 0){
        color = colors[next_color];
        mob_colors[seq_feature["name"]] = color;
        next_color++;
      }
      else{
        color = mob_colors[seq_feature["name"]];
      }
      
      mob_file << ref_seq.m_seq_id << " " <<
                  seq_feature.m_start << " " <<
                  seq_feature.m_end << " " <<
                  "i" << direction << " " <<
                  "color=" << color << endl;
    }
    
    //seq.m_repeats
    
  }
  
  indel_file.close();
  mob_file.close();
  synonymous_mutation_file.close();
  nonsynonymous_mutation_file.close();
  npi_mutation_file.close();
  
}

void MIRAtoGD(const string &mira_file_name, const string &gd_file_name){
  //this was made on accident :(
  //words cannot express, so I will use another :(
  ifstream mira_file;
  
  mira_file.open(mira_file_name.c_str());
  
  if (!mira_file){
    cerr << "Could not open " << mira_file_name << endl;
    return;
  }
  
  string line;
  
  cGenomeDiff gd;
  
  while (getline(mira_file, line)){
    vector <string> items = split_on_whitespace(line);
    
    if (items[0] == "#"){
      continue;
    }
    
    
    cDiffEntry mut(UNKNOWN);
    
    if (items[9] == "basechange"){
      mut._type = SNP;
      mut["seq_id"] = items[0].substr(0, items[0].length() - 3);
      mut["position"] = items[4];
      mut["new_seq"] = items[10].substr(items[10].length() - 1);
    }
    else if (items[9] == "insertion"){
      mut._type = INS;
      mut["seq_id"] = items[0].substr(0, items[0].length() - 3);
      mut["position"] = items[4].substr(items[4].find(":") + 1);
      mut["new_seq"] = items[10].substr(items[10].length() - 1);
    }
    else if (items[9] == "deletion"){
      mut._type = DEL;
      mut["seq_id"] = items[0].substr(0, items[0].length() - 3);
      mut["position"] = items[4];
      mut["size"] = "1";
    }
    if (mut._type != UNKNOWN) {
      gd.add(mut);
    }
  }
  gd.write(gd_file_name);
  mira_file.close();
}
cGenomeDiff cGenomeDiff::from_vcf(const string &file_name)
{
    //VCF Column order.
    enum {CHROM = 0, POS, ID, REF, ALT, QUAL, FILTER, INFO};

    ifstream in(file_name.c_str());
    string line = "";

    cGenomeDiff gd; //Return value.
    while (!in.eof()) {
      getline(in, line);
      if (!in.good() || line.empty()) break;
      //Discard header lines for now.
      if (line[0] == '#') continue;
      const vector<string> &tokens = split(line, "\t");

      cDiffEntry de;
      const cString &rseq = tokens[REF], &aseq = tokens[ALT];
      if (aseq.contains(',')) {
        //! TODO: Classify these mutations, GATK doesn't predict these(?)
//        de._type = SUB;
//        de[SEQ_ID]   = tokens[CHROM];
//        de[POSITION] = tokens[POS];
//        de[SIZE]     = to_string(tokens[ALT].size());
//        de[NEW_SEQ]  = tokens[ALT];
        WARN("Can't classify line: " + line);
        continue;
      }
      if (rseq.size() > aseq.size()) {
        de._type = DEL;
        de[SEQ_ID]   = tokens[CHROM];
        de[POSITION] = to_string(from_string<uint32_t>(tokens[POS]) + aseq.size());
        de[SIZE]     = to_string(rseq.size() - aseq.size());
      }
      else if (rseq.size() < aseq.size()) {
        de._type = INS;
        de[SEQ_ID]   = tokens[CHROM];
        de[POSITION] = tokens[POS];
        de[NEW_SEQ]  = cString(aseq).remove_starting(rseq);
      }
      else if (rseq.size() == 1) {
        de._type = SNP;
        de[SEQ_ID]   = tokens[CHROM];
        de[POSITION] = tokens[POS];
        de[NEW_SEQ]  = aseq;
      }
      else {
        WARN("Can't classify line: " + line);
        continue;
      }

      const vector<string> &info_tokens = split(tokens[INFO], ";");
      //size_t n = info_tokens.size();
      for (size_t i = 0, n = info_tokens.size(); i < n; ++i) {
        cKeyValuePair kvp(info_tokens[i], '=');
        de[kvp.get_key()] = kvp.get_value();
      }

      gd.add(de);
    }

    return gd;
}

/*! Given a list of types, search and return the cDiffEntry's within diff_entry_list_t whose 
 * _type parameter matches one of those within input types. 
 */ 
diff_entry_list_t cGenomeDiff::list(const vector<gd_entry_type>& types)
{
  // default is to have to types
  if (types.size() == 0)
    return _entry_list;
  
  diff_entry_list_t return_list;
  
  for (diff_entry_list_t::iterator itr_diff_entry = _entry_list.begin();
       itr_diff_entry != _entry_list.end(); itr_diff_entry++)
    {
      for (vector<gd_entry_type>::const_iterator requested_type = types.begin();
           requested_type != types.end(); requested_type++)
      {
        if((*itr_diff_entry)->_type == *requested_type)
          return_list.push_back(*itr_diff_entry);
      }
    }
  
  return return_list;
}


diff_entry_list_t cGenomeDiff::show_list(const vector<gd_entry_type>& types)
{
  diff_entry_list_t ret_list = list(types);
  ret_list.remove_if(cDiffEntry::fields_exist(make_vector<diff_entry_key_t>("deleted")));
  ret_list.remove_if(cDiffEntry::fields_exist(make_vector<diff_entry_key_t>("no_show")));
  return ret_list;
}

/*-----------------------------------------------------------------------------
 * returns entries NOT used as evidence by other entries. 
 *
 *-----------------------------------------------------------------------------*/
diff_entry_list_t cGenomeDiff::filter_used_as_evidence(const diff_entry_list_t& input)
{
  // first we make a map with everything used as evidence by any entry in the entire genome diff
  map<string,bool> used_as_evidence;
  for (diff_entry_list_t::const_iterator it = _entry_list.begin(); it != _entry_list.end(); it++)
  {
    const diff_entry_ptr_t& de = *it;
    for (vector<string>::const_iterator ev_it = de->_evidence.begin(); ev_it != de->_evidence.end(); ev_it++) 
    {  
      used_as_evidence[*ev_it] = true;
    }   
  }
  
  // then construct a list of all items in input with ids not in this map
  diff_entry_list_t return_list;
  for (diff_entry_list_t::const_iterator it = input.begin(); it != input.end(); it++)
  {
    const diff_entry_ptr_t& de = *it;
    if ( !used_as_evidence.count(de->_id) )
      return_list.push_back(de);
  }

  return return_list;
}


// return items with types that are 3 characters long
diff_entry_list_t cGenomeDiff::mutation_list()
{
  this->sort();
  diff_entry_list_t::iterator it = _entry_list.begin();
  while (it != _entry_list.end()) {
    if (!(**it).is_mutation()) {
      break;
    } else {
      ++it;
    }
  }

  return diff_entry_list_t(_entry_list.begin(), it);
}

// return items with types that are 2 characters long
diff_entry_list_t cGenomeDiff::evidence_list()
{
  diff_entry_list_t mut_list;
  
  for(diff_entry_list_t::iterator itr = _entry_list.begin();
      itr != _entry_list.end(); itr ++) {
    cDiffEntry& item = **itr;
    if(item.is_evidence()) {
      mut_list.push_back(*itr);
    }
  }
  
  return mut_list;
}

// return items with types that are 4 characters long
diff_entry_list_t cGenomeDiff::validation_list()
{
  this->sort();
  diff_entry_list_t::reverse_iterator it = _entry_list.rend();
  while (it != _entry_list.rbegin()) {
    if (!(**it).is_validation()) {
      --it;
      break;
    } else {
      ++it; 
    }
  }
  return diff_entry_list_t(it.base(), _entry_list.end());
}


/*! Return all cDiffEntrys within _entry_list whose _id matches one
 * of those within input's item._evidence
 */ 
diff_entry_list_t cGenomeDiff::mutation_evidence_list(const cDiffEntry& item)
{
  diff_entry_list_t return_list;
  
  //return diff_entries with matching evidence
  for (vector<string>::const_iterator itr_i = item._evidence.begin(); itr_i != item._evidence.end(); itr_i ++) 
  {  
    const string& evidence = *itr_i;
    
    for (diff_entry_list_t::iterator itr_j = _entry_list.begin(); itr_j != _entry_list.end(); itr_j ++)
    {  
      cDiffEntry& entry = **itr_j;
    
      if (entry._id == evidence)
        return_list.push_back(*itr_j);
    }   
  }
  return return_list;
}

diff_entry_ptr_t cGenomeDiff::parent(const cDiffEntry& evidence)
{
  for(diff_entry_list_t::iterator itr_test_item = _entry_list.begin();
      itr_test_item != _entry_list.end(); itr_test_item ++) { 

    cDiffEntry& test_item = **itr_test_item;

    for(vector<string>::iterator itr = test_item._evidence.begin();
        itr != test_item._evidence.end(); itr ++) { 
      string& test_evidence_id = (*itr);
      if(test_evidence_id == evidence._id) {      
        return diff_entry_ptr_t(*itr_test_item);
      }
    }
  }
  return diff_entry_ptr_t(NULL);
}

  
// Helper functionf or mutation_unknown and mutation_deleted
bool cGenomeDiff::mutation_in_entry_of_type(cDiffEntry mut, const gd_entry_type type)
{
  uint32_t start = mut.get_start();
  uint32_t end = mut.get_end();
  
  diff_entry_list_t check_list = list(make_vector<gd_entry_type>(type));

  for (diff_entry_list_t::iterator itr = check_list.begin(); itr != check_list.end(); itr++) {
    
    cDiffEntry de(**itr);
    if ( (start >= de.get_start()) && (end <= de.get_end()) ) {
      return true;
    }
  }
  return false;
}
  
void cGenomeDiff::add_reject_reasons(cDiffEntry item, const string& reject)
{
  if (item.entry_exists(REJECT))
    item[REJECT] += ",";
  else 
    item[REJECT] += reject;
}


// This function will use the current GD and apply it to the new_ref_seq_info.
// When calling this function make SURE that you load ref_seq_info and
// new_ref_seq_info seperately.
//
//  TODO: Write a deep copy constructor for cReferenceSequences 
void cGenomeDiff::apply_to_sequences(cReferenceSequences& ref_seq_info, cReferenceSequences& new_ref_seq_info, bool verbose)
{    
  uint32_t count_SNP = 0, count_SUB = 0, count_INS = 0, count_DEL = 0, count_AMP = 0, count_INV = 0, count_MOB = 0, count_CON = 0;

  diff_entry_list_t mutation_list = this->mutation_list();
  for (diff_entry_list_t::iterator itr_mut = mutation_list.begin(); itr_mut != mutation_list.end(); itr_mut++)
  {
    cDiffEntry& mut(**itr_mut);
    uint32_t position = from_string<uint32_t>(mut[POSITION]);
        
    switch (mut._type) 
    {
      case SNP :
      {
        count_SNP++;
        
        new_ref_seq_info.replace_sequence_1(mut[SEQ_ID], position, position, mut[NEW_SEQ], (to_string(mut._type) + " " + mut._id), verbose);
        
        if (verbose)
        {
          cout << "SNP: 1 bp => " << mut[NEW_SEQ] << " at position " << position << endl;
          cout << "  shift: none" << endl;
        }
      } break;

      case SUB:
      {
        count_SUB++;
          
        const uint32_t& size = from_string<uint32_t>(mut[SIZE]);
        
        new_ref_seq_info.replace_sequence_1(mut[SEQ_ID], position, position + size - 1, mut[NEW_SEQ], (to_string(mut._type) + " " + mut._id), verbose);
          
        if (verbose)
        {
          cout << "SUB: " << size << " => " << mut[NEW_SEQ] << endl;
          cout << "   shift +" << mut[NEW_SEQ].length() << " bp at position " <<  position << endl;
        }
      } break;

      case INS:
      {          
        count_INS++;
        
        new_ref_seq_info.insert_sequence_1(mut[SEQ_ID], position, mut[NEW_SEQ], (to_string(mut._type) + " " + mut._id), verbose);
          
        if (verbose)
        {
          cout << "INS: 0 => " << mut[NEW_SEQ] << endl;
          cout << "   shift +" << mut[NEW_SEQ].length() << " bp at position " <<  position << endl;
        }
      } break;

      case DEL:
      {
        count_DEL++;
          
        const uint32_t& size = from_string<uint32_t>(mut[SIZE]);
        
        new_ref_seq_info.replace_sequence_1(mut[SEQ_ID], position, position + size -1, "", (to_string(mut._type) + " " + mut._id), verbose);
          
        if (verbose)
        {
          cout << "DEL: " << size << " => 0" << endl;
          cout << "   shift -" << size << " bp at position " <<  position << endl;
        }
      } break;

      case AMP:
      {
        count_AMP++;
          
        const uint32_t& size = from_string<uint32_t>(mut[SIZE]);

        //Build duplicate sequence
        string dup;
        for (uint32_t i = 1; i < from_string<uint32_t>(mut["new_copy_number"]); i++)
          dup.append(new_ref_seq_info.get_sequence_1(mut[SEQ_ID], position, position+size-1));
        ASSERT(!dup.empty(), "Duplicate sequence is empy.");
          
        new_ref_seq_info.insert_sequence_1(mut[SEQ_ID], position-1, dup, (to_string(mut._type) + " " + mut._id), verbose);
        
        if (verbose)
        {
          cout << "AMP: 0" << " => " << dup << endl;
          cout << "   shift +" << dup.length() << " bp at position " << position << endl;
        }        
      } break;
        
      case INV:
      {
        count_INV++;
          
        WARN("INV: mutation type not handled yet");
      } break;

      case MOB:
      {
        //ASSERT(!mut.entry_exists("ins_start") && !mut.entry_exists("ins_end") && !mut.entry_exists("del_start") && !mut.entry_exists("del_end"),
        //       "MOB: does not handle ins_start, ins_end, del_start, del_end yet.");
        ASSERT(mut["strand"] != "?", "Unknown repeat strand");
        
        count_MOB++;
        string new_seq_string = "";
        string rep_string = "";
        string duplicate_sequence = "";
        int32_t iDelStart = 0;
        int32_t iDelEnd = 0;
        int32_t iInsStart = 0;
        int32_t iInsEnd = 0;        
        int32_t iDupLen = 0;
        int32_t uRPos = -1;
        
        if(mut.entry_exists("del_start")) iDelStart = from_string<uint32_t>(mut["del_start"]);
        if(mut.entry_exists("del_end"))   iDelEnd = from_string<uint32_t>(mut["del_end"]);
        ASSERT((iDelStart >= 0) && (iDelEnd >= 0), (to_string(mut._type) + " " + mut._id) + " - NEGATIVE DELETION");
        
        if(mut.entry_exists("repeat_pos"))uRPos = from_string<uint32_t>(mut["repeat_pos"]);        
        if(mut.entry_exists("duplication_size"))iDupLen = from_string<uint32_t>(mut["duplication_size"]);

        // @JEB: correct here to look for where the repeat is in the original ref_seq_info.
        // This saves us from possibly looking at a shifted location...
        rep_string = ref_seq_info.repeat_family_sequence(mut["repeat_name"], from_string<int16_t>(mut["strand"]), uRPos);
        mut["repeat_size"] = to_string(rep_string.length()); // saving this for shifting
        
        // This is the string we're going to pass to be inserted.
        // It will eventually contain the repeat string, insertions
        // and the duplicate_sequence.
        new_seq_string = rep_string;
        
        // Do we have deletes?  Go ahead and delete them from the repeat.
        if(iDelStart)new_seq_string.replace(0,iDelStart,"");
        if(iDelEnd)new_seq_string.resize(new_seq_string.size() - iDelEnd);
        
        // The position of a MOB is the first position that is duplicated
        // Inserting at the position means we have to copy the duplication
        // in FRONT OF the repeat sequence
        if(iDupLen)duplicate_sequence = new_ref_seq_info.get_sequence_1(mut[SEQ_ID], position, position + (from_string<uint32_t>(mut["duplication_size"]) - 1));
        
        // If there are any inserts, put them in front of or behind the
        // repeat sequence.
        if(mut.entry_exists("ins_start")) {new_seq_string = mut["ins_start"] + rep_string;iInsStart = mut["ins_start"].length();}
        if(mut.entry_exists("ins_end"))   {new_seq_string += mut["ins_end"];iInsEnd = mut["ins_end"].length();}
        
        // Add on the duplicated sequence.  This happens AFTER
        // we have inserted any insertions.
        new_seq_string = duplicate_sequence + new_seq_string;        
        
        // Insert our newly minted sequence.
        new_ref_seq_info.insert_sequence_1(mut[SEQ_ID], position-1, new_seq_string, (to_string(mut._type) + " " + mut._id), verbose);
        
        // We've repeated the sequence, now it's time to repeat all the features
        // inside of and including the repeat region.
        new_ref_seq_info.repeat_feature_1(mut[SEQ_ID], position+iInsStart+duplicate_sequence.size(), iDelStart, iDelEnd, ref_seq_info, mut["repeat_name"], from_string<int16_t>(mut["strand"]), uRPos, verbose);
          
        if (verbose)
        {
          cout << "MOB: 0" << " => " << new_seq_string << endl;
          cout << "   shift +" << new_seq_string.length() - iDelStart - iDelEnd << " bp at position " << position << endl;
        }          
      } break;

      case CON:
      {
        count_CON++;
          
        uint32_t size = from_string<uint32_t>(mut[SIZE]);

        uint32_t replace_target_id, replace_start, replace_end;
        new_ref_seq_info.parse_region(mut["region"], replace_target_id, replace_start, replace_end);
        ASSERT(replace_start != replace_end, "Cannot process CON mutation with end == start. ID:" + to_string(mut._id));
        
        Strand strand = (replace_start < replace_end) ?  POS_STRAND : NEG_STRAND;
        
        if (strand == NEG_STRAND) {
          swap(replace_start, replace_end);
        }
        
        // @JEB: correct here to look for where the replacing_sequence is in the original ref_seq_info.
        // This saves us from possible looking at a shifted location...
        string replacing_sequence = ref_seq_info[replace_target_id].get_sequence_1(replace_start, replace_end);

        if (strand == NEG_STRAND) {
          replacing_sequence = reverse_complement(replacing_sequence);
        }

        string displaced_sequence = new_ref_seq_info.get_sequence_1(mut[SEQ_ID], position, position + size - 1);
        
        new_ref_seq_info.replace_sequence_1(mut[SEQ_ID], position, position + size - 1, replacing_sequence, (to_string(mut._type) + " " + mut._id), verbose); 
          
        if (verbose)
        {
          cout << "CON: " << displaced_sequence << " => " << replacing_sequence << endl;
          int32_t size_change = static_cast<int32_t>(replacing_sequence.length()) - static_cast<int32_t>(displaced_sequence.length());
          cout << "   shift " << ((size_change >= 0) ? "+" : "") << size_change << " bp at position " << position << endl;
        }       
      } break;

      default:
        ASSERT(false, "Can't handle mutation type: " + to_string(mut._type));
    }
    
    this->shift_positions(mut, new_ref_seq_info, verbose);
  }
    
  if (verbose)
  {    
    cout << "MUTATION COUNT" << endl;
    cout << "\tSNP: " << count_SNP << endl;
    cout << "\tSUB: " << count_SUB << endl;
    cout << "\tINS: " << count_INS << endl;
    cout << "\tDEL: " << count_DEL << endl;
    cout << "\tAMP: " << count_AMP << endl;
    cout << "\tINV: " << count_INV << endl;
    cout << "\tMOB: " << count_MOB << endl;
    cout << "\tCON: " << count_CON << endl;
  }
  
  //Cleanup.  If any of the sequences are of zero length, remove them.
  for (vector<cAnnotatedSequence>::iterator it_as = new_ref_seq_info.begin(); it_as < new_ref_seq_info.end(); it_as++) {
    if(!it_as->m_length){new_ref_seq_info.erase(it_as);it_as--;}
  }
}


void cGenomeDiff::shift_positions(cDiffEntry &item, cReferenceSequences& ref_seq_info, bool verbose)
{  
  int32_t delta = item.mutation_size_change(ref_seq_info);
  if (verbose)
    cout << "Shift size: " << delta << endl;
  if (delta == UNDEFINED_INT32)
    WARN("Size change not defined for mutation.");

  uint32_t offset = from_string<uint32_t>(item[POSITION]);
  
  // Only offset if past the duplicated part of a MOB (allows putting a mutation in the first copy)
  if (item._type == MOB) {
    offset += from_string<uint32_t>(item["duplication_size"]);
  }
  
  // @JEB TODO: Need manual support for putting mutations within a newly inserted mutation (nesting)
  
  // This could get tricky for mutations that overlap boundaries of other mutations
  // we should check for this and throw an error if it occurs.
    
  if (item.entry_exists("in_mutation")) {
    
    ERROR("'in_mut' key not implemented");
    
  } else if (item.entry_exists("in_copy")) {
    
    ERROR("Expected 'in_mut' key since 'in_copy' key exists for item" + item.to_string());
  }
  
  
  diff_entry_list_t muts = this->mutation_list();
  for (diff_entry_list_t::iterator itr = muts.begin(); itr != muts.end(); itr++) {
    cDiffEntry& mut = **itr;
    
    if (mut._type == INV) {
      ERROR("shift_positions cannot handle inversions yet!");
    } else {
      uint32_t position = from_string<uint32_t>(mut[POSITION]);
      if (item[SEQ_ID] == mut[SEQ_ID] && position > offset)
        mut[POSITION] = to_string(position + delta);
    }

  }
}

//>! Return the
  
int32_t cDiffEntry::mutation_size_change(cReferenceSequences& ref_seq_info)
{  
  switch (this->_type) {
    case SNP: return 0; break;
    case SUB: return (*this)[NEW_SEQ].length() - from_string<uint32_t>((*this)[SIZE]); break;
    case INS: return (*this)[NEW_SEQ].length(); break;
    case DEL: return -(from_string<uint32_t>((*this)[SIZE])); break;
    case AMP: return from_string<uint32_t>((*this)[SIZE]) * (from_string<uint32_t>((*this)["new_copy_number"]) - 1); break;

    case MOB:
    {
      int32_t size = from_string<int32_t>((*this)["repeat_size"]) + from_string<int32_t>((*this)["duplication_size"]);
      if (this->entry_exists("del_start"))
        size -= from_string<uint32_t>((*this)["del_start"]);
      if (this->entry_exists("del_end"))
        size -= from_string<uint32_t>((*this)["del_end"]);
      if (this->entry_exists("ins_start"))
        size += (*this)["ins_start"].length();
      if (this->entry_exists("ins_end"))
        size += (*this)["ins_end"].length();
      return size;
      break;
    }

    case CON:
    {
      uint32_t replace_target_id, replace_start, replace_end;
      ref_seq_info.parse_region((*this)["region"], replace_target_id, replace_start, replace_end);  
      int32_t size = from_string<uint32_t>((*this)[SIZE]);
      
      int32_t new_size = (replace_end > replace_start) ? replace_end - replace_start + 1 : replace_start - replace_end + 1;
      return  new_size - size;
      break;
    }
    default:
      ASSERT(false, "Unable to calculate mutation size change.");
      return UNDEFINED_INT32;
  }
}

void cGenomeDiff::set_intersect(cGenomeDiff &gd, bool verbose)
{
  (void)verbose; //unused

  set<cDiffEntry> seen;
  diff_entry_list_t muts = gd.mutation_list();

  for (diff_entry_list_t::iterator it = muts.begin();
       it != muts.end(); ++it) {
    seen.insert(**it);
  }

  this->sort();
  set<string> ids;
  diff_entry_list_t::iterator it = _entry_list.begin();
  //Handle mutations, store evidence id of deleted mutations
  //to later delete.
  while (it != _entry_list.end()) {
    if (!(**it).is_mutation()) break;

    if (!seen.count(**it)) {
      for (uint32_t i = 0; i < (**it)._evidence.size(); ++i) {
        ids.insert((**it)._evidence[i]); 
      }
      it = _entry_list.erase(it);
    } else {
      ++it;
    }
  }
  //Delete evidence that matches it.
  while (it != _entry_list.end()) {
    if (ids.count((**it)._id)) {
      it = _entry_list.erase(it);
    } else {
      ++it;
    }
  }

  return;

}

void cGenomeDiff::assign_unique_ids()
{
  this->sort();

  //Handle mutations.
  _unique_id_counter = 0;

  map<string, vector<diff_entry_ptr_t> > id_table;
  diff_entry_list_t::iterator it = _entry_list.begin();
  while (it != _entry_list.end()) {
    if (!(**it).is_mutation()) break;
    (**it)._id = to_string(++_unique_id_counter);

    for (uint32_t i = 0; i < (**it)._evidence.size(); ++i) {
      id_table[(**it)._evidence[i]].push_back(*it);
    }

    ++it;
  }

  //Handle the rest.
  while (it != _entry_list.end()) {
    string new_id = to_string(++_unique_id_counter);

    if (id_table.count((**it)._id)) {
      for (uint32_t i = 0; i < id_table[(**it)._id].size(); ++i) {
        vector<string>* evidence = &id_table[(**it)._id][i]->_evidence;
        replace(evidence->begin(), evidence->end(), (**it)._id, new_id);
      }
    }

    (**it)._id = new_id;
    ++it;
  }
}

void cGenomeDiff::set_union(cGenomeDiff& gd, bool verbose)
{
  (void)verbose; //unused
  this->fast_merge(gd);
  this->remove(cGenomeDiff::EVIDENCE);
  this->remove(cGenomeDiff::VALIDATION);
  this->unique(); 
}

void cGenomeDiff::compare(cGenomeDiff& gd, bool verbose)
{
  (void)verbose; //unused

  bool (*comp_fn) (const diff_entry_ptr_t&, const diff_entry_ptr_t&) = diff_entry_ptr_sort;
  typedef set<diff_entry_ptr_t, bool(*)(const diff_entry_ptr_t&, const diff_entry_ptr_t&)> diff_entry_set_t;

  diff_entry_list_t muts = this->mutation_list();
  diff_entry_set_t ctrl_muts(comp_fn);
  copy(muts.begin(), muts.end(), inserter(ctrl_muts, ctrl_muts.begin()));

  muts = gd.mutation_list();
  diff_entry_set_t test_muts(comp_fn);
  copy(muts.begin(), muts.end(), inserter(test_muts, test_muts.begin()));

  if (verbose) {
    printf("\tComparing %u control mutations versus %u test mutations.\n\n",
         static_cast<unsigned int>(ctrl_muts.size()), static_cast<unsigned int>(test_muts.size()));
  }

  this->set_union(gd, verbose);

  uint32_t n_tp = 0, n_fn = 0, n_fp = 0;

  //Handle mutations and gather evidence ids.
  //Evidence id to TP, FN, FP value.
  map<string, string> id_table; 
  diff_entry_list_t::iterator it = _entry_list.begin();
  while (it != _entry_list.end()) {
    if (!(**it).is_mutation()) break;

    assert(ctrl_muts.count(*it) || test_muts.count(*it));

    string key = "";
    if (ctrl_muts.count(*it) && test_muts.count(*it)) {
      key = "TP";
      ++n_tp;
    }
    else if (ctrl_muts.count(*it) && !test_muts.count(*it)) {
      key = "FN";
      ++n_fn;
    }
    else if (!ctrl_muts.count(*it) && test_muts.count(*it)) {
      key = "FP";
      ++n_fp;
    } 

    vector<string>* evidence = &(**it)._evidence;
    for (uint32_t i = 0; i < evidence->size(); ++i) {
      id_table[(*evidence)[i]] = key;
    }

    if (verbose) {
      string temp = "";
      if (key == "TP") temp = "[True  Positive]:\t";
      if (key == "FN") temp = "[False Negative]:\t";
      if (key == "FP") temp = "[False Positive]:\t";
      if (key == "")   temp = "[ERROR]         :\t";
      cout << "\t\t"<< temp << **it << endl;
    }

    (**it)["compare"] = key;
    ++it;
  }

  if (verbose) {
    printf("\tUpdating mutation's evidence.\n"); 
  }

  //Handle the rest.
  while (it != _entry_list.end()) {
    (**it)["compare"] = id_table[(**it)._id];
    ++it;
  }


  //Add TP|FN|FP header info.
  string value = "";
  sprintf(value, "%u|%u|%u", n_tp, n_fn, n_fp);
  this->add_breseq_data("TP|FN|FP", value);

  printf("\t\t#=TP|FN|FP	%s \t for %s versus %s \n",
         value.c_str(),
         this->_default_filename.c_str(),
         gd._default_filename.c_str());

  return;
}


}//namespace bresesq


