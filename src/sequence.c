#include "geneie/sequence.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>

bool geneie_sequence_valid(struct geneie_sequence sequence)
{
	return !!sequence.codes;
}

struct geneie_sequence geneie_sequence_alloc(ssize_t length)
{
	if (length < 0)
		return (struct geneie_sequence) { 0 };

	const struct geneie_sequence result = {
		length,
		malloc((size_t)length)
	};
	return result;
}

struct geneie_sequence geneie_sequence_from_string(const char *string)
{
	const bool valid = geneie_code_nucleic_string_valid(string)
		|| geneie_code_amino_string_valid(string);
	if (!valid)
		return (struct geneie_sequence) {
			0,
			NULL,
		};

	const size_t strlen_result = strlen(string);
	if (strlen_result > SSIZE_MAX)
		return (struct geneie_sequence) { 0 };

	const ssize_t length = (ssize_t)strlen_result;
	struct geneie_sequence result = geneie_sequence_alloc(length);

	if (geneie_sequence_valid(result))
		memcpy(result.codes, string, strlen_result);

	return result;
}

struct geneie_sequence geneie_sequence_copy(struct geneie_sequence other)
{
	const ssize_t length = other.length;

	struct geneie_sequence result = geneie_sequence_alloc(length);

	// No ssize_t < 0 check, because I'm assuming other
	// has been constructed by a function that's done that already
	if (geneie_sequence_valid(result))
		memcpy(result.codes, other.codes, (size_t)length);

	return result;
}

void geneie_sequence_free(struct geneie_sequence sequence)
{
	free(sequence.codes);
}

