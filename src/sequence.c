#include "geneie/sequence.h"

bool geneie_sequence_char_valid(char c)
{
	switch (c) {
		case GENEIE_SEQUENCE_ADENINE:
		case GENEIE_SEQUENCE_CYTOSINE:
		case GENEIE_SEQUENCE_GUANINE:
		case GENEIE_SEQUENCE_THYMINE:
		case GENEIE_SEQUENCE_URACIL:
		case GENEIE_SEQUENCE_PURINE:
		case GENEIE_SEQUENCE_PYRIMDINE:
		case GENEIE_SEQUENCE_KETO:
		case GENEIE_SEQUENCE_AMINO:
		case GENEIE_SEQUENCE_STRONG:
		case GENEIE_SEQUENCE_WEAK:
		case GENEIE_SEQUENCE_NOT_A:
		case GENEIE_SEQUENCE_NOT_C:
		case GENEIE_SEQUENCE_NOT_G:
		case GENEIE_SEQUENCE_NOT_TU:
		case GENEIE_SEQUENCE_ANY:
		case GENEIE_SEQUENCE_MASKED:
		case GENEIE_SEQUENCE_GAP:
			return true;
		default:
			return false;
	}
}

bool geneie_sequence_string_valid(const char *string)
{
	for (; *string; string++)
		if (!geneie_sequence_char_valid(*string))
			return false;
	return true;
}


