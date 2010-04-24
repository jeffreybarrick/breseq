#ifndef _BRESEQ_COMMON_H_
#define _BRESEQ_COMMON_H_

//1 for A, 2 for C, 4 for G,
//8 for T and 15 for N.
#define is_A(x) (x == 0x01)
#define is_C(x) (x == 0x02)
#define is_G(x) (x == 0x04)
#define is_T(x) (x == 0x08)
#define is_N(x) (x == 0x0f)


namespace breseq {
	
	/*! Reverse a base.
	 */
	inline uint8_t reverse_base(uint8_t base) {
		if(base > 0x0f) {
			// ascii
			switch(base) {
				case 'A': return 'T';
				case 'C': return 'G';
				case 'G': return 'C';
				case 'T': return 'A';
				default: assert(false);
			}
		} else {
			// sam-style 4-bit field
			switch(base) {
				case 0x1: return 0x8;
				case 0x2: return 0x4;
				case 0x4: return 0x2;
				case 0x8: return 0x1;
				default: assert(false);
			}		
		}
	}
	
	/*! Convert a base to an ASCII character.
	 */
	inline char base2char(uint8_t base) {
		if(base > 0x0f) {
			// already in ascii format
			return static_cast<char>(base);
		} else {
			// sam-style 4-bit field
			switch(base) {
				case 0x01: return 'A';
				case 0x02: return 'C';
				case 0x04: return 'G';
				case 0x08: return 'T';
				case 0x0f: return '.';
				default: assert(false);
			}		
		}
	}

} // breseq

#endif
