#include "geneie/sequence_ref.h"

#include "geneie/code.h"

#include <ctype.h>
#include <string.h>
#include <limits.h>

bool geneie_sequence_ref_valid(struct geneie_sequence_ref sequence)
{
	return sequence.codes != NULL
		&& sequence.length >= 0;
}

struct geneie_sequence_ref geneie_sequence_ref_from_string(char *string)
{
	const size_t strlen_result = strlen(string);

	if (strlen_result > SSIZE_MAX)
		return (struct geneie_sequence_ref){ 0 };

	const ssize_t length = (ssize_t)strlen_result;
	const bool valid = geneie_code_nucleic_string_valid(string)
		|| geneie_code_amino_string_valid(string);
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

struct geneie_sequence_ref geneie_sequence_ref_index(
	struct geneie_sequence_ref ref,
	ssize_t index
)
{
	return (struct geneie_sequence_ref) {
		ref.length - index,
		ref.codes + index,
	};
}

struct geneie_sequence_ref geneie_sequence_ref_trunc(
	struct geneie_sequence_ref ref,
	ssize_t new_size
)
{
	return (struct geneie_sequence_ref) {
		.length = (ssize_t)new_size,
		.codes = ref.codes,
	};
}

bool geneie_sequence_ref_in(
	struct geneie_sequence_ref ref,
	geneie_code code
)
{
	for (; ref.length; ref.length--, ref.codes++)
		if (toupper(*ref.codes) == toupper(code))
			return true;
	return false;
}
