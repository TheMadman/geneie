/*
 * Geneie - A Library and Tools for gene processing
 * Copyright (C) 2024   Marcus Harrison
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "test_macros.h"
#include "geneie/encoding.h"

typedef struct geneie_sequence_ref ref;
#define ref(lit) geneie_sequence_ref_from_literal(lit)
#define ref_str(str) geneie_sequence_ref_from_string(str)
#define arrlen(arr) (sizeof(arr) / sizeof(arr[0]))
#define arrend(arr) (&(arr)[arrlen(arr)])

static bool in(ref sequence, char code)
{
	for (; sequence.length; sequence.codes++, sequence.length--)
		if (code == *sequence.codes)
			return true;
	return false;
}

static bool matches(ref sequence, ref expectations)
{
	for (ref cur = sequence; cur.length; cur.length--, cur.codes++)
		if (!in(expectations, *cur.codes))
			return false;

	for (ref cur = expectations; cur.length; cur.length--, cur.codes++)
		if (!in(sequence, *cur.codes))
			return false;

	return true;
}

// I could, technically, make one giant list of structs
// containing all the letters and all that, but the
// asserts are more useful with more granular functions
// so that's what I'm doing

void test_a(void)
{
	ref a = ref("A");
	const ref expectation = ref("A");

	ref result = geneie_encoding_get_valid_codes(a);

	assert(matches(result, expectation));
}

void test_c(void)
{
	ref c = ref("C");
	const ref expectation = ref("C");

	ref result = geneie_encoding_get_valid_codes(c);

	assert(matches(result, expectation));
}

void test_g(void)
{
	ref g = ref("G");
	const ref expectation = ref("G");

	ref result = geneie_encoding_get_valid_codes(g);

	assert(matches(result, expectation));
}

void test_tu()
{
	const ref expectation = ref("TU");

	{
		ref tu = ref("TU");

		ref result = geneie_encoding_get_valid_codes(tu);

		assert(matches(result, expectation));
	}

	{
		ref t = ref("T");

		ref result = geneie_encoding_get_valid_codes(t);

		assert(matches(result, expectation));
	}

	{
		ref u = ref("U");

		ref result = geneie_encoding_get_valid_codes(u);

		assert(matches(result, expectation));
	}
}

void test_r(void)
{
	const ref expectation = ref("AGR");

	{
		ref ag = ref("AG");

		ref result = geneie_encoding_get_valid_codes(ag);

		assert(matches(result, expectation));
	}

	{
		ref r = ref("R");

		ref result = geneie_encoding_get_valid_codes(r);

		assert(matches(result, expectation));
	}

	{
		ref agr = ref("AGR");

		ref result = geneie_encoding_get_valid_codes(agr);

		assert(matches(result, expectation));
	}
}

void test_y(void)
{
	const ref expectation = ref("CTUY");

	{
		ref test = ref("CT");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("CU");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("CTU");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("Y");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("CTUY");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}
}

void test_s(void)
{
	const ref expectation = ref("GCS");

	{
		ref test = ref("GC");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("S");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("GCS");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}
}

void test_w(void)
{
	const ref expectation = ref("ATUW");

	{
		ref test = ref("AT");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("AU");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("ATU");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("W");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("ATUW");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

}

void test_k(void)
{
	ref expectation = ref("GTUK");

	{
		ref test = ref("GT");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("GU");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("GTU");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("K");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("GTK");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("GUK");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("GTUK");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}
}

void test_m(void)
{
	ref expectation = ref("ACM");

	{
		ref test = ref("AC");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("M");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("ACM");

		ref result = geneie_encoding_get_valid_codes(test);

		assert(matches(result, expectation));
	}
}

void test_b(void)
{
	// oh boy, here we go

	ref expectation = ref("CGTUYSKB");

	ref codes[] = {
		ref("CGT"),
		ref("CGU"),
		ref("CGTU"),
		ref("CK"),
		ref("CKT"),
		ref("CKU"),
		ref("CKTU"),
		ref("ST"),
		ref("SU"),
		ref("STU"),
		ref("GY"),
		ref("B"),
		ref("CGTB"),
		// I'm not doing this combinatorially, sod it
		{ 0 },
	};

	for (ref *code = codes; code->codes; code++) {
		ref result = geneie_encoding_get_valid_codes(*code);

		assert(matches(result, expectation));
	}
}

void test_d(void)
{
	ref expectation = ref("AGTURWKD");

	ref codes[] = {
		ref("AGT"),
		ref("AGU"),
		ref("AGTU"),
		ref("RT"),
		ref("RU"),
		ref("RTU"),
		ref("WG"),
		ref("AK"),
		ref("WR"),
		ref("WK"),
		ref("RK"),
		ref("D"),
		{ 0 },
	};

	for (ref *code = codes; code->codes; code++) {
		ref result = geneie_encoding_get_valid_codes(*code);

		assert(matches(result, expectation));
	}
}

void test_h(void)
{
	ref expectation = ref("ACTUYWMH");

	ref codes[] = {
		ref("ACT"),
		ref("ACU"),
		ref("ACTU"),
		ref("AY"),
		ref("CW"),
		ref("TM"),
		ref("UM"),
		ref("TUM"),
		ref("H"),
		ref("ACTH"),
		{ 0 },
	};

	for (ref *code = codes; code->codes; code++) {
		ref result = geneie_encoding_get_valid_codes(*code);

		assert(matches(result, expectation));
	}
}

void test_v(void)
{
	ref expectation = ref("ACGRSMV");

	ref codes[] = {
		ref("ACG"),
		ref("CR"),
		ref("AS"),
		ref("GM"),
		ref("V"),
		{ 0 },
	};

	for (ref *code = codes; code->codes; code++) {
		ref result = geneie_encoding_get_valid_codes(*code);

		assert(matches(result, expectation));
	}
}

void test_n(void)
{
	ref expectation = ref("ACGTURYSWKMBDHVN");

	ref codes[] = {
		ref("ACGT"),
		ref("ACGU"),
		ref("ACGTU"),
		// good enough for me, all the other cases
		// are already covered above
		{ 0 },
	};

	for (ref *code = codes; code->codes; code++) {
		ref result = geneie_encoding_get_valid_codes(*code);

		assert(matches(result, expectation));
	}
}

static bool all_encode(
	geneie_code (*codons_begin)[4],
	geneie_code (*codons_end)[4],
	geneie_code expect
)
{
	for (; codons_begin < codons_end; codons_begin++) {
		ref current_ref = ref(*codons_begin);

		if (!geneie_encoding_one_codon(current_ref, current_ref))
			return false;

		if (current_ref.codes[0] != expect)
			return false;
	}

	return true;
}

void test_encode_a(void)
{
	const geneie_code expect = GENEIE_CODE_ALANINE;

	// I'm not making these lists exhaustive
	geneie_code codons[][4] = {
		"GCT",
		"GCU",
		"GCC",
		"GCA",
		"GCG",
		"GCR",
		"GCN",
	};

	geneie_code (*codons_end)[4] = arrend(codons);

	assert(all_encode(codons, codons_end, expect));
}

void test_encode_l(void)
{
	const geneie_code expect = GENEIE_CODE_LEUCINE;
	geneie_code codons[][4] = {
		"UUA",
		"TTA",
		"UUG",
		"TTG",
		"UUR",
		"TTR",
		"CUU",
		"CUC",
		"CUA",
		"CUG",
		"CTT",
		"CTC",
		"CTA",
		"CTG",
		"CTN",
	};

	geneie_code (*codons_end)[4] = arrend(codons);

	assert(all_encode(codons, codons_end, expect));
}

void test_encode_s(void)
{
	const geneie_code expect = GENEIE_CODE_SERINE;
	geneie_code codons[][4] = {
		"UCU",
		"UCC",
		"UCA",
		"UCG",
		"UCN",
		"AGU",
		"AGC",
		"AGY",
		"TCT",
		"TCC",
		"TCA",
		"TCG",
		"TCN",
		"AGT",
	};

	geneie_code (*codons_end)[4] = arrend(codons);
	assert(all_encode(codons, codons_end, expect));
}

void test_encode_y(void)
{
	const geneie_code expect = GENEIE_CODE_TYROSINE;
	geneie_code codons[][4] = {
		"UAU",
		"TAT",
		"UAC",
		"TAC",
		"UAY",
		"TAY",
	};

	geneie_code (*codons_end)[4] = arrend(codons);
	assert(all_encode(codons, codons_end, expect));
}

void test_encode_0(void)
{
	const geneie_code expect = GENEIE_CODE_STOP;
	geneie_code codons[][4] = {
		"UAA",
		"TAA",
		"UAG",
		"TAG",
		"UAR",
		"TAR",
		"UGA",
		"TGA",
	};

	assert(all_encode(codons, arrend(codons), expect));
}

void test_encode_c(void)
{
	const geneie_code expect = GENEIE_CODE_CYSTEINE;
	geneie_code codons[][4] = {
		"UGU",
		"TGT",
		"UGC",
		"TGC",
		"UGY",
		"TGY",
	};

	assert(all_encode(codons, arrend(codons), expect));
}

void test_encode_w(void)
{
	const geneie_code expect = GENEIE_CODE_TRYPTOPHAN;
	geneie_code codons[][4] = {
		"UGG",
	};

	assert(all_encode(codons, arrend(codons), expect));
}

void test_encode_p(void)
{
	const geneie_code expect = GENEIE_CODE_PROLINE;
	geneie_code codons[][4] = {
		"CCU",
		"CCT",
		"CCA",
		"CCG",
		"CCN",
	};

	assert(all_encode(codons, arrend(codons), expect));
}

void test_encode_h(void)
{
	const geneie_code expect = GENEIE_CODE_HISTIDINE;
	geneie_code codons[][4] = {
		"CAU",
		"CAT",
		"CAC",
		"CAY",
	};

	assert(all_encode(codons, arrend(codons), expect));
}

void test_encode_q(void)
{
	const geneie_code expect = GENEIE_CODE_GLUTAMINE;
	geneie_code codons[][4] = {
		"CAA",
		"CAG",
		"CAR",
	};

	assert(all_encode(codons, arrend(codons), expect));
}

void test_encode_r(void)
{
	const geneie_code expect = GENEIE_CODE_ARGININE;
	geneie_code codons[][4] = {
		"CGU",
		"CGT",
		"CGC",
		"CGA",
		"CGG",
		"CGN",
		"AGA",
		"AGG",
		"AGR",
	};

	assert(all_encode(codons, arrend(codons), expect));
}

void test_encode_i(void)
{
	const geneie_code expect = GENEIE_CODE_ISOLEUCINE;
	geneie_code codons[][4] = {
		"AUU",
		"AUC",
		"AUA",
		"AUH",
	};

	assert(all_encode(codons, arrend(codons), expect));
}

void test_encode_m(void)
{
	const geneie_code expect = GENEIE_CODE_METHIONINE;
	geneie_code codons[][4] = {
		"AUG",
	};

	assert(all_encode(codons, arrend(codons), expect));
}

void test_encode_t(void)
{
	const geneie_code expect = GENEIE_CODE_THREONINE;
	geneie_code codons[][4] = {
		"ACU",
		"ACT",
		"ACC",
		"ACA",
		"ACG",
		"ACN",
	};

	assert(all_encode(codons, arrend(codons), expect));
}

void test_encode_n(void)
{
	const geneie_code expect = GENEIE_CODE_ASPARAGINE;
	geneie_code codons[][4] = {
		"AAU",
		"AAT",
		"AAC",
		"AAY",
	};

	assert(all_encode(codons, arrend(codons), expect));
}

void test_encode_k(void)
{
	const geneie_code expect = GENEIE_CODE_LYSINE;
	geneie_code codons[][4] = {
		"AAA",
		"AAG",
		"AAR",
	};

	assert(all_encode(codons, arrend(codons), expect));
}

void test_encode_v(void)
{
	const geneie_code expect = GENEIE_CODE_VALINE;
	geneie_code codons[][4] = {
		"GUU",
		"GUC",
		"GUA",
		"GUG",
		"GUN",
		"GTT",
		"GTC",
		"GTA",
		"GTG",
		"GTN",
	};

	assert(all_encode(codons, arrend(codons), expect));
}

void test_encode_d(void)
{
	const geneie_code expect = GENEIE_CODE_ASPARTIC_ACID;
	geneie_code codons[][4] = {
		"GAU",
		"GAT",
		"GAC",
		"GAY",
	};

	assert(all_encode(codons, arrend(codons), expect));
}

void test_encode_e(void)
{
	const geneie_code expect = GENEIE_CODE_GLUTAMIC_ACID;
	geneie_code codons[][4] = {
		"GAA",
		"GAG",
		"GAR",
	};

	assert(all_encode(codons, arrend(codons), expect));
}

void test_encode_g(void)
{
	const geneie_code expect = GENEIE_CODE_GLYCINE;
	geneie_code codons[][4] = {
		"GGU",
		"GGT",
		"GGA",
		"GGG",
		"GGN",
	};

	assert(all_encode(codons, arrend(codons), expect));
}

int main()
{
	test_a();
	test_c();
	test_g();
	test_tu();
	test_y();
	test_s();
	test_w();
	test_k();
	test_m();
	test_b();
	test_d();
	test_h();
	test_v();
	test_n();

	test_encode_a();
	test_encode_l();
	test_encode_s();
	test_encode_y();
	test_encode_0();
	test_encode_c();
	test_encode_w();
	test_encode_p();
	test_encode_h();
	test_encode_q();
	test_encode_r();
	test_encode_i();
	test_encode_m();
	test_encode_t();
	test_encode_n();
	test_encode_k();
	test_encode_v();
	test_encode_d();
	test_encode_e();
	test_encode_g();
}
