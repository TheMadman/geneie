#include "geneie/sequence_tools.h"

#include <string.h>
#include <ctype.h>

#include "geneie/code.h"
#include "geneie/encoding.h"

#include <libadt/vector.h>

typedef struct geneie_sequence seq;
typedef struct geneie_sequence_ref seq_r;
typedef struct geneie_sequence_tools_ref_pair seq_r_pair;

#define index geneie_sequence_ref_index
#define trunc geneie_sequence_ref_trunc
#define one_codon geneie_encoding_one_codon
#define valid geneie_sequence_ref_valid

typedef struct libadt_vector vector;

static const seq invalid_sequence = { 0 };

static seq_r splice_whitespace(seq_r ref, void *_)
{
	// The param is unused
	(void)_;
	for (; valid(ref); ref = index(ref, 1)) {
		if (!isspace(ref.codes[0]))
			continue;

		ssize_t whitespace_length = 0;
		seq_r result = ref;
		for (; valid(ref); ref = index(ref, 1)) {
			if (isspace(ref.codes[0]))
				whitespace_length++;
			else
				break;
		}

		return trunc(result, whitespace_length);
	}

	return (seq_r) { 0 };
}

seq_r geneie_sequence_tools_clean_whitespace(seq_r reference)
{
	return geneie_sequence_tools_splice(
		reference,
		splice_whitespace,
		NULL
	);
}

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

	// 16 picked arbitrarily
	// how should we handle vector errors in append()?
	LIBADT_VECTOR_WITH(splices, sizeof(seq_r), 16) {
		seq_r remaining = strand;

		seq_r to_splice = { 0 };
		while ((to_splice = splicer_func(remaining, state)).length) {
			vector attempt = libadt_vector_append(splices, &to_splice);
			if (libadt_vector_identity(attempt, splices)) {
				// Better error handling somehow?
				// Currently we just proceed with the
				// vector that worked
				break;
			} else {
				splices = attempt;
			}

			const ssize_t start = to_splice.codes - remaining.codes;
			remaining = index(
				remaining,
				start + to_splice.length
			);
		}

		while (splices.length) {
			splices = libadt_vector_pop(splices, &to_splice);

			geneie_code
				*const to_move = to_splice.codes + to_splice.length,
				*const dest = to_splice.codes;
			const size_t
				amount_before = (size_t)(to_splice.codes - strand.codes),
				amount_after = (size_t)strand.length
					- (amount_before + (size_t)to_splice.length);
			memmove(dest, to_move, amount_after);
			strand.length -= to_splice.length;
		}
	}

	return strand;
}


seq_r_pair geneie_sequence_tools_encode(seq_r strand)
{
	ssize_t i = 0;

	for (;; i++) {
		seq_r
			current_in = index(strand, i * 3),
			current_out = index(strand, i);

		if (!one_codon(current_in, current_out))
			break;
		if (current_out.codes[0] == GENEIE_CODE_STOP) {
			// include the stop code in the output
			i++;
			break;
		}
	}

	return (seq_r_pair) {
		{ trunc(strand, i), index(strand, i * 3) },
	};
}

