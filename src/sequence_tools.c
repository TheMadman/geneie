#include "geneie/sequence_tools.h"

#include <string.h>

typedef struct geneie_sequence seq;
typedef struct geneie_sequence_ref seq_r;

static const seq invalid_sequence = { 0 };

seq_r geneie_sequence_tools_ref_from_sequence(seq sequence)
{
	return (seq_r) {
		sequence.length,
		sequence.codes,
	};
}

seq geneie_sequence_tools_sequence_from_ref(seq_r reference)
{
	if (!geneie_sequence_ref_valid(reference))
		return invalid_sequence;

	seq result = geneie_sequence_alloc(reference.length);

	if (!geneie_sequence_valid(result))
		return invalid_sequence;

	memcpy(result.codes, reference.codes, (size_t)reference.length);
	return result;
}

void geneie_sequence_tools_dna_to_premrna(seq_r reference)
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

seq_r geneie_sequence_tools_splice(
	seq_r strand,
	geneie_sequence_tools_splicer *splicer_func,
	void *state
)
{
	if (strand.length <= 0)
		return strand;

	seq_r to_splice = splicer_func(strand, state);

	if (to_splice.length <= 0)
		return strand;

	geneie_code *const to_move = &to_splice.codes[to_splice.length];
	const ssize_t remainder_length = strand.length - (to_move - strand.codes);
	seq_r remainder = {
		.length = remainder_length,
		.codes = to_move,
	};

	seq_r remainder_after_futures = geneie_sequence_tools_splice(
		remainder,
		splicer_func,
		state
	);

	const ssize_t amount_to_move = remainder_after_futures.length;

	memmove(to_splice.codes, to_move, (size_t)amount_to_move);

	const ssize_t
		amount_before_splice = (to_splice.codes - strand.codes),
		amount_after_splice = remainder_after_futures.length;

	seq_r result = {
		amount_before_splice + amount_after_splice,
		strand.codes,
	};

	return result;
}

