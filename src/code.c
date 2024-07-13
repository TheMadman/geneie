#include "geneie/code.h"

#include <ctype.h>

bool geneie_code_nucleic_char_valid(char c)
{
	switch (toupper(c)) {
		case GENEIE_CODE_ADENINE:
		case GENEIE_CODE_CYTOSINE:
		case GENEIE_CODE_GUANINE:
		case GENEIE_CODE_THYMINE:
		case GENEIE_CODE_URACIL:
		case GENEIE_CODE_PURINE:
		case GENEIE_CODE_PYRIMDINE:
		case GENEIE_CODE_KETO:
		case GENEIE_CODE_AMINO:
		case GENEIE_CODE_STRONG:
		case GENEIE_CODE_WEAK:
		case GENEIE_CODE_NOT_A:
		case GENEIE_CODE_NOT_C:
		case GENEIE_CODE_NOT_G:
		case GENEIE_CODE_NOT_TU:
		case GENEIE_CODE_ANY:
		case GENEIE_CODE_MASKED:
		case GENEIE_CODE_GAP:
			return true;
		default:
			return false;
	}
}

bool geneie_code_nucleic_string_valid(const char *string)
{
	for (; *string; string++)
		if (!(geneie_code_nucleic_char_valid(*string) || isspace(*string)))
			return false;
	return true;
}

bool geneie_code_amino_char_valid(char c)
{
	switch (toupper(c)) {
		case GENEIE_CODE_ALANINE:
		case GENEIE_CODE_CYSTEINE:
		case GENEIE_CODE_ASPARTIC_ACID:
		case GENEIE_CODE_GLUTAMIC_ACID:
		case GENEIE_CODE_PHENYLALANINE:
		case GENEIE_CODE_GLYCINE:
		case GENEIE_CODE_HISTIDINE:
		case GENEIE_CODE_ISOLEUCINE:
		case GENEIE_CODE_LYSINE:
		case GENEIE_CODE_LEUCINE:
		case GENEIE_CODE_METHIONINE:
		case GENEIE_CODE_ASPARAGINE:
		case GENEIE_CODE_PROLINE:
		case GENEIE_CODE_GLUTAMINE:
		case GENEIE_CODE_ARGININE:
		case GENEIE_CODE_SERINE:
		case GENEIE_CODE_THREONINE:
		case GENEIE_CODE_VALINE:
		case GENEIE_CODE_TRYPTOPHAN:
		case GENEIE_CODE_TYROSINE:
			return true;
		default:
			return false;
	}
}

bool geneie_code_amino_string_valid(const char *string)
{
	for (; *string; string++)
		if (!(geneie_code_amino_char_valid(*string) || isspace(*string)))
			return false;
	return true;
}

