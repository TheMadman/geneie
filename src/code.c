#include "geneie/code.h"

bool geneie_code_char_valid(char c)
{
	switch (c) {
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

bool geneie_code_string_valid(const char *string)
{
	for (; *string; string++)
		if (!geneie_code_char_valid(*string))
			return false;
	return true;
}

