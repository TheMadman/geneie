#include "geneie/sequence_ref.h"

#include "geneie/sequence.h"

#include <string.h>

bool geneie_sequence_ref_valid(struct geneie_sequence_ref sequence)
{
	return sequence.codes != NULL;
}

struct geneie_sequence_ref geneie_sequence_ref_from_string(char *string)
{
	const ssize_t length = strlen(string);
	const bool valid = geneie_sequence_string_valid(string);
	return (struct geneie_sequence_ref) {
		length,
		valid ? (enum GENEIE_SEQUENCE_CODE *)string : NULL,
	};
}

