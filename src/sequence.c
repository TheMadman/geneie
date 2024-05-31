#include "geneie/sequence.h"

#include <stdlib.h>
#include <string.h>

bool geneie_sequence_valid(struct geneie_sequence sequence)
{
	return !!sequence.codes;
}

struct geneie_sequence geneie_sequence_alloc(ssize_t length)
{
	const struct geneie_sequence result = {
		length,
		malloc(length)
	};
	return result;
}

struct geneie_sequence geneie_sequence_from_string(const char *string)
{
	if (!geneie_code_string_valid(string)) {
		return (struct geneie_sequence) {
			0,
			NULL,
		};
	}

	const ssize_t length = strlen(string);
	struct geneie_sequence result = geneie_sequence_alloc(length);

	if (geneie_sequence_valid(result))
		memcpy(result.codes, string, length);

	return result;
}

struct geneie_sequence geneie_sequence_copy(struct geneie_sequence other)
{
	const ssize_t length = other.length;

	struct geneie_sequence result = geneie_sequence_alloc(length);

	if (geneie_sequence_valid(result))
		memcpy(result.codes, other.codes, length);

	return result;
}

void geneie_sequence_free(struct geneie_sequence sequence)
{
	free(sequence.codes);
}

