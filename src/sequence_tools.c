#include "geneie/sequence_tools.h"

#include <string.h>

struct geneie_sequence_ref
geneie_sequence_tools_ref_from_sequence(struct geneie_sequence *sequence)
{
	return (struct geneie_sequence_ref) {
		sequence ? sequence->length: 0,
		sequence ? sequence->codes: NULL,
	};
}

struct geneie_sequence *
geneie_sequence_tools_sequence_from_ref(struct geneie_sequence_ref reference)
{
	if (!geneie_sequence_ref_valid(reference))
		return NULL;

	struct geneie_sequence *result = geneie_sequence_alloc(reference.length);

	if (!result)
		return NULL;

	memcpy(result->codes, reference.codes, reference.length);
	return result;
}
