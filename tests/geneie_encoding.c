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

	ref result = geneie_encode_get_valid_codes(a);

	assert(matches(result, expectation));
}

void test_c(void)
{
	ref c = ref("C");
	const ref expectation = ref("C");

	ref result = geneie_encode_get_valid_codes(c);

	assert(matches(result, expectation));
}

void test_g(void)
{
	ref g = ref("G");
	const ref expectation = ref("G");

	ref result = geneie_encode_get_valid_codes(g);

	assert(matches(result, expectation));
}

void test_tu()
{
	const ref expectation = ref("TU");

	{
		ref tu = ref("TU");

		ref result = geneie_encode_get_valid_codes(tu);

		assert(matches(result, expectation));
	}

	{
		ref t = ref("T");

		ref result = geneie_encode_get_valid_codes(t);

		assert(matches(result, expectation));
	}

	{
		ref u = ref("U");

		ref result = geneie_encode_get_valid_codes(u);

		assert(matches(result, expectation));
	}
}

void test_r(void)
{
	const ref expectation = ref("AGR");

	{
		ref ag = ref("AG");

		ref result = geneie_encode_get_valid_codes(ag);

		assert(matches(result, expectation));
	}

	{
		ref r = ref("R");

		ref result = geneie_encode_get_valid_codes(r);

		assert(matches(result, expectation));
	}

	{
		ref agr = ref("AGR");

		ref result = geneie_encode_get_valid_codes(agr);

		assert(matches(result, expectation));
	}
}

void test_y(void)
{
	const ref expectation = ref("CTUY");

	{
		ref test = ref("CT");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("CU");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("CTU");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("Y");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("CTUY");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}
}

void test_s(void)
{
	const ref expectation = ref("GCS");

	{
		ref test = ref("GC");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("S");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("GCS");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}
}

void test_w(void)
{
	const ref expectation = ref("ATUW");

	{
		ref test = ref("AT");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("AU");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("ATU");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("W");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("ATUW");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

}

void test_k(void)
{
	ref expectation = ref("GTUK");

	{
		ref test = ref("GT");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("GU");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("GTU");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("K");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("GTK");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("GUK");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("GTUK");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}
}

void test_m(void)
{
	ref expectation = ref("ACM");

	{
		ref test = ref("AC");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("M");

		ref result = geneie_encode_get_valid_codes(test);

		assert(matches(result, expectation));
	}

	{
		ref test = ref("ACM");

		ref result = geneie_encode_get_valid_codes(test);

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
		ref result = geneie_encode_get_valid_codes(*code);

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
		ref result = geneie_encode_get_valid_codes(*code);

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
		ref result = geneie_encode_get_valid_codes(*code);

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
		ref result = geneie_encode_get_valid_codes(*code);

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
		ref result = geneie_encode_get_valid_codes(*code);

		assert(matches(result, expectation));
	}
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
}
