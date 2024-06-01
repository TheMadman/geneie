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

void geneie_sequence_tools_dna_to_premrna(struct geneie_sequence_ref reference)
{
	const geneie_code *const end = &reference.codes[reference.length];
	for (
		geneie_code *current = reference.codes;
		current < end;
		current++
	) {
		if (*current == GENEIE_CODE_THYMINE)
			*current = GENEIE_CODE_URACIL;
	}
}

struct geneie_sequence_ref geneie_sequence_tools_splice(
	struct geneie_sequence_ref strand,
	geneie_sequence_tools_splicer *splicer_func
)
{
	if (strand.length <= 0)
		return strand;

	struct geneie_sequence_ref to_splice = splicer_func(strand);

	if (to_splice.length <= 0)
		return strand;

	geneie_code *const to_move = &to_splice.codes[to_splice.length];
	const ssize_t remainder_length = strand.length - (to_move - strand.codes);
	struct geneie_sequence_ref remainder = {
		.length = remainder_length,
		.codes = to_move,
	};

	struct geneie_sequence_ref remainder_after_futures = geneie_sequence_tools_splice(remainder, splicer_func);

	const ssize_t amount_to_move = remainder_after_futures.length;

	memcpy(to_splice.codes, to_move, amount_to_move);

	const ssize_t
		amount_before_splice = (to_splice.codes - strand.codes),
		amount_after_splice = remainder_after_futures.length;

	struct geneie_sequence_ref result = {
		amount_before_splice + amount_after_splice,
		strand.codes,
	};

	return result;
}

