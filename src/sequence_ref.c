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
		valid ? (geneie_code *)string : NULL,
	};
}

bool geneie_sequence_ref_equal(
	struct geneie_sequence_ref first,
	struct geneie_sequence_ref second
)
{
	if (first.length != second.length)
		return false;

	const geneie_code
		*first_code = first.codes,
		*second_code = second.codes;
	ssize_t length = first.length;

	for(; length; first_code++, second_code++, length--)
		if (*first_code != *second_code)
			return false;

	return true;
}

