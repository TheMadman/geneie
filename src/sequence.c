#include "geneie/sequence.h"

#include <stdlib.h>
#include <string.h>

struct geneie_sequence *geneie_sequence_alloc(ssize_t length)
{
	const ssize_t prefix = sizeof(struct geneie_sequence);
	struct geneie_sequence *const result = malloc(prefix + length);
	if (!result)
		return NULL;

	result->length = length;
	return result;
}

struct geneie_sequence *geneie_sequence_from_string(const char *string)
{
	if (!geneie_code_string_valid(string)) {
		return NULL;
	}

	const ssize_t length = strlen(string);
	struct geneie_sequence *result = geneie_sequence_alloc(length);
	if (!result)
		return NULL;

	memcpy(result->codes, string, length);

	return result;
}

struct geneie_sequence *geneie_sequence_copy(struct geneie_sequence *other)
{
	const ssize_t length = other->length;

	struct geneie_sequence *result = geneie_sequence_alloc(length);
	if (!result)
		return NULL;

	memcpy(result->codes, other->codes, length);

	return result;
}

void geneie_sequence_free(struct geneie_sequence *sequence)
{
	free(sequence);
}

