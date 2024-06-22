#include "geneie/encoding.h"
#include "geneie/code.h"

#include <stdbool.h>

typedef struct geneie_sequence_ref ref;

#define ref_from_lit(lit) (ref){ sizeof(lit) - 1, lit }

#define HAS_A (1 << 0)
#define HAS_C (1 << 1)
#define HAS_G (1 << 2)
#define HAS_TU (1 << 3)

#define in geneie_sequence_ref_in
#define trunc geneie_sequence_ref_trunc
#define index geneie_sequence_ref_index
#define get_valid_codes geneie_encoding_get_valid_codes

static bool has_a(ref sequence)
{
	return in(sequence, GENEIE_CODE_ADENINE)
		|| in(sequence, GENEIE_CODE_AMINO)
		|| in(sequence, GENEIE_CODE_PURINE)
		|| in(sequence, GENEIE_CODE_WEAK)
		|| in(sequence, GENEIE_CODE_NOT_C)
		|| in(sequence, GENEIE_CODE_NOT_G)
		|| in(sequence, GENEIE_CODE_NOT_TU)
		|| in(sequence, GENEIE_CODE_ANY);
}

static bool has_c(ref sequence)
{
	return in(sequence, GENEIE_CODE_CYTOSINE)
		|| in(sequence, GENEIE_CODE_PYRIMDINE)
		|| in(sequence, GENEIE_CODE_STRONG)
		|| in(sequence, GENEIE_CODE_AMINO)
		|| in(sequence, GENEIE_CODE_NOT_A)
		|| in(sequence, GENEIE_CODE_NOT_G)
		|| in(sequence, GENEIE_CODE_NOT_TU)
		|| in(sequence, GENEIE_CODE_ANY);
}

static bool has_g(ref sequence)
{
	return in(sequence, GENEIE_CODE_GUANINE)
		|| in(sequence, GENEIE_CODE_PURINE)
		|| in(sequence, GENEIE_CODE_STRONG)
		|| in(sequence, GENEIE_CODE_KETO)
		|| in(sequence, GENEIE_CODE_NOT_A)
		|| in(sequence, GENEIE_CODE_NOT_C)
		|| in(sequence, GENEIE_CODE_NOT_TU)
		|| in(sequence, GENEIE_CODE_ANY);
}

static bool has_tu(ref sequence)
{
	return in(sequence, GENEIE_CODE_THYMINE)
		|| in(sequence, GENEIE_CODE_URACIL)
		|| in(sequence, GENEIE_CODE_PYRIMDINE)
		|| in(sequence, GENEIE_CODE_WEAK)
		|| in(sequence, GENEIE_CODE_KETO)
		|| in(sequence, GENEIE_CODE_NOT_A)
		|| in(sequence, GENEIE_CODE_NOT_C)
		|| in(sequence, GENEIE_CODE_NOT_G)
		|| in(sequence, GENEIE_CODE_ANY);
}

ref geneie_encoding_get_valid_codes(ref codes)
{
	int checks = has_a(codes)
		| has_c(codes) << 1
		| has_g(codes) << 2
		| has_tu(codes) << 3;

	switch (checks) {
		case HAS_A:
			return ref_from_lit("A");
		case HAS_C:
			return ref_from_lit("C");
		case HAS_A | HAS_C:
			return ref_from_lit("ACM");
		case HAS_G:
			return ref_from_lit("G");
		case HAS_G | HAS_A:
			return ref_from_lit("AGR");
		case HAS_G | HAS_C:
			return ref_from_lit("CGS");
		case HAS_G | HAS_C | HAS_A:
			return ref_from_lit("ACGMRSV");
		case HAS_TU:
			return ref_from_lit("TU");
		case HAS_TU | HAS_A:
			return ref_from_lit("ATUW");
		case HAS_TU | HAS_C:
			return ref_from_lit("CTUY");
		case HAS_TU | HAS_C | HAS_A:
			return ref_from_lit("ACTUMWYH");
		case HAS_TU | HAS_G:
			return ref_from_lit("GTUK");
		case HAS_TU | HAS_G | HAS_A:
			return ref_from_lit("AGTURWKD");
		case HAS_TU | HAS_G | HAS_C:
			return ref_from_lit("CGTUSYKB");
		case HAS_TU | HAS_G | HAS_C | HAS_A:
			return ref_from_lit("ACGTURYSWKMBDHVN");
		default:
			return (ref){ 0 };
	}
}

typedef struct {
	const geneie_code *codon;
	const geneie_code amino;
} codon_amino_mapping;

static const codon_amino_mapping amino_table[] = {
	{ "UUY", GENEIE_CODE_PHENYLALANINE },
	{ "UUR", GENEIE_CODE_LEUCINE },
	{ "CUN", GENEIE_CODE_LEUCINE },
	{ "UCN", GENEIE_CODE_SERINE },
	{ "AGY", GENEIE_CODE_SERINE },
	{ "UAY", GENEIE_CODE_TYROSINE },
	{ "UAR", GENEIE_CODE_STOP },
	{ "UGA", GENEIE_CODE_STOP },
	{ "UGY", GENEIE_CODE_CYSTEINE },
	{ "UGG", GENEIE_CODE_TRYPTOPHAN },
	{ "CCN", GENEIE_CODE_PROLINE },
	{ "CAY", GENEIE_CODE_HISTIDINE },
	{ "CAR", GENEIE_CODE_GLUTAMINE },
	{ "CGN", GENEIE_CODE_ARGININE },
	{ "AGR", GENEIE_CODE_ARGININE },
	{ "AUH", GENEIE_CODE_ISOLEUCINE },
	{ "AUG", GENEIE_CODE_METHIONINE },
	{ "ACN", GENEIE_CODE_THREONINE },
	{ "AAY", GENEIE_CODE_ASPARAGINE },
	{ "AAR", GENEIE_CODE_LYSINE },
	{ "GUN", GENEIE_CODE_VALINE },
	{ "GCN", GENEIE_CODE_ALANINE },
	// teehee
	{ "GAY", GENEIE_CODE_ASPARTIC_ACID },
	{ "GAR", GENEIE_CODE_GLUTAMIC_ACID },
	{ "GGN", GENEIE_CODE_GLYCINE },
};


static const codon_amino_mapping
	*amino_table_end = &amino_table[sizeof(amino_table) / sizeof(amino_table[0])];

static bool matches(ref search, ref input)
{
	if (geneie_sequence_ref_equal(search, input))
		return true;

	// assume input from geneie_encoding_one_codon
	// is correct

	for (int i = 0; i < 3; i++) {
		const ref current_code = trunc(index(search, i), 1);
		const ref matches = get_valid_codes(current_code);
		if (!in(matches, input.codes[i]))
			return false;
	}

	return true;
}

bool geneie_encoding_one_codon(ref codon, ref amino_out)
{
	if (codon.length < 3)
		return false;
	if (amino_out.length < 1)
		return false;

	// I hate this
	// Just call this linear search: the library
	// I wish I was smarter than this

	for (
		const codon_amino_mapping *current = amino_table;
		current < amino_table_end;
		current++
	) {
		ref amino_pattern = (ref){
			.length = 3,

			// we don't modify this in `matches` anyway
			.codes = (geneie_code *)current->codon,
		};

		if (matches(amino_pattern, codon)) {
			amino_out.codes[0] = current->amino;
			return true;
		}
	}

	return false;
}
