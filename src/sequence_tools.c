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

static void perform_move(seq_r from, seq_r to)
{
	memmove(to.codes, from.codes, (size_t)from.length);
}

static seq_r perform_moves(seq_r strand, vector splices)
{
	seq_r current_destination = *(seq_r*)vector_index(splices, 0);
	ssize_t spliced = 0;

	for (size_t i = 0; i < splices.length - 1; i++) {
		const seq_r *splice = vector_index(splices, i);
		const seq_r *next = vector_index(splices, i + 1);

		seq_r from_seq_ref = index(*splice, splice->length);
		ssize_t length = next->codes - from_seq_ref.codes;
		from_seq_ref = trunc(from_seq_ref, length);

		// In principle, we should, but in practice,
		// we only pass this to perform_move which we
		// know won't actually _use_ the length
		// current_destination = trunc(current_destination, length);

		perform_move(from_seq_ref, current_destination);

		current_destination = index(
			current_destination,
			length
		);

		spliced += splice->length;
	}

	/*
	 * last move is just whatever's left at the end of the
	 * sequence
	 */
	const seq_r *splice = vector_index(splices, splices.length - 1);
	seq_r from_seq_ref = index(*splice, splice->length);
	ssize_t length = strand.length - (from_seq_ref.codes - strand.codes);
	from_seq_ref = trunc(from_seq_ref, length);

	perform_move(from_seq_ref, current_destination);
	// current_destination = trunc(current_destination, length);

	spliced += splice->length;

	return trunc(strand, strand.length - spliced);
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
		strand = perform_moves(strand, splices);
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

