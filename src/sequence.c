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
	if (!geneie_sequence_string_valid(string)) {
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


