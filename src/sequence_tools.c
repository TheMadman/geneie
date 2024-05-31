#include "geneie/sequence_tools.h"

#include <string.h>

static const struct geneie_sequence invalid_sequence = { 0 };

struct geneie_sequence_ref
geneie_sequence_tools_ref_from_sequence(struct geneie_sequence sequence)
{
	return (struct geneie_sequence_ref) {
		sequence.length,
		sequence.codes,
	};
}

struct geneie_sequence
geneie_sequence_tools_sequence_from_ref(struct geneie_sequence_ref reference)
{
	if (!geneie_sequence_ref_valid(reference))
		return invalid_sequence;

	struct geneie_sequence result = geneie_sequence_alloc(reference.length);

	if (!geneie_sequence_valid(result))
		return invalid_sequence;

	memcpy(result.codes, reference.codes, reference.length);
	return result;
}
