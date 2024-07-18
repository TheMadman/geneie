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

#define vector_identity libadt_vector_identity
#define vector_index libadt_vector_index
#define vector_append libadt_vector_append
#define vector_vacuum libadt_vector_vacuum

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

static vector collect_splices(
	vector splices,
	seq_r strand,
	geneie_sequence_tools_splicer *splicer_func,
	void *state
)
{
	seq_r remaining = strand;
	seq_r to_splice = { 0 };
	while ((to_splice = splicer_func(remaining, state)).length) {
		vector attempt = vector_append(splices, &to_splice);
		if (vector_identity(attempt, splices)) {
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
	return splices;
}

static vector precompute_moves(seq_r strand, vector precomputed, vector splices)
{
	/*
	 * This function computes exactly how much memory must
	 * be moved, and where, to avoid moving the same (potentially
	 * huge amount of) memory multiple times.
	 *
	 * I'm not keen on how hard it is to reason about but
	 * I'm not smart enough to make it simpler.
	 */
	ssize_t total_backshift = 0;

	/*
	 * precomputes all but last move
	 * The memory that must be moved is the
	 * memory starting after the current splice
	 * and ending at the beginning of the next splice
	 */
	for (size_t i = 0; i < splices.length - 1; i++) {
		const seq_r *splice = vector_index(splices, i);
		const seq_r *next = vector_index(splices, i + 1);

		geneie_code *from = splice->codes + splice->length;
		ssize_t length = next->codes - from;
		geneie_code *to = from - total_backshift - splice->length;
		total_backshift += splice->length;

		seq_r from_seq_ref = {
			.codes = from,
			.length = length,
		};
		seq_r to_seq_ref = {
			.codes = to,
			.length = length,
		};

		seq_r_pair result = {
			{ from_seq_ref, to_seq_ref }
		};
		precomputed = vector_append(precomputed, &result);
	}

	/*
	 * last move is just whatever's left at the end of the
	 * sequence
	 */
	const seq_r *splice = vector_index(splices, splices.length - 1);
	geneie_code *from = splice->codes + splice->length;
	ssize_t length = strand.length - (from - strand.codes);
	geneie_code *to = from - total_backshift - splice->length;
	seq_r from_seq_ref = {
		.codes = from,
		.length = length,
	};
	seq_r to_seq_ref = {
		.codes = to,
		.length = length,
	};

	seq_r_pair result = {
		{ from_seq_ref, to_seq_ref }
	};
	precomputed = vector_append(precomputed, &result);

	return precomputed;
}

static void perform_move(seq_r_pair pair)
{
	memmove(pair.refs[1].codes, pair.refs[0].codes, (size_t)pair.refs[0].length);
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
		splices = collect_splices(splices, strand, splicer_func, state);
		if (splices.length == 0)
			continue;

		splices = vector_vacuum(splices);

		LIBADT_VECTOR_WITH(precomputed, sizeof(seq_r_pair), splices.length) {
			precomputed = precompute_moves(strand, precomputed, splices);

			for (size_t i = 0; i < precomputed.length; i++) {
				seq_r *splice = vector_index(splices, i);
				seq_r_pair *move = vector_index(precomputed, i);
				perform_move(*move);
				strand.length -= splice->length;
			}
		}
	}

	return strand;
}


typedef struct {
	ssize_t bytes_read;
	geneie_code codon[3];
} read_result;

static read_result read_one_codon(seq_r strand)
{
	read_result result = { 0 };
	for (ssize_t i = 0; valid(strand) && i < 3;) {
		result.codon[i] = *strand.codes;
		result.bytes_read++;
		if (!isspace(*strand.codes)) {
			i++;
		}
		strand = index(strand, 1);
	}
	return result;
}

seq_r_pair geneie_sequence_tools_encode(seq_r strand)
{
	ssize_t
		in = 0,
		out = 0;

	for (;;) {
		read_result read_codon = read_one_codon(index(strand, in));

		seq_r codon = {
			.codes = read_codon.codon,
			.length = 3,
		};

		seq_r amino_out = index(strand, out);

		if (one_codon(codon, amino_out)) {
			in += read_codon.bytes_read;
			out++;
		} else {
			break;
		}

		if (*amino_out.codes == GENEIE_CODE_STOP) {
			break;
		}
	}

	return (seq_r_pair) {
		{ trunc(strand, out), index(strand, in) },
	};
}

