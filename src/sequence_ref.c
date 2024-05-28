#include "geneie/sequence_ref.h"

#include "geneie/code.h"

#include <string.h>

bool geneie_sequence_ref_valid(struct geneie_sequence_ref sequence)
{
	return sequence.codes != NULL;
}

struct geneie_sequence_ref geneie_sequence_ref_from_string(char *string)
{
	const ssize_t length = strlen(string);
	const bool valid = geneie_code_string_valid(string);
	return (struct geneie_sequence_ref) {
		length,
		valid ? (enum GENEIE_CODE *)string : NULL,
	};
}

