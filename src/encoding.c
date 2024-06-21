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

ref geneie_encode_get_valid_codes(ref codes)
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
