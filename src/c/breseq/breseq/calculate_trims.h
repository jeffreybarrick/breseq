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

#ifndef _BRESEQ_CALCULATE_TRIMS_H_
#define _BRESEQ_CALCULATE_TRIMS_H_

#include "breseq/common.h"

using namespace std;

namespace breseq {

  void calculate_trims( const string& in_fasta, const string& in_output_path);
	
} // breseq

#endif