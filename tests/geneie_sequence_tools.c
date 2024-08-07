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
#include "geneie/sequence_tools.h"

#include <string.h>

#define from_string geneie_sequence_from_string
#define ref_from_sequence geneie_sequence_tools_ref_from_sequence
#define sequence_from_ref geneie_sequence_tools_sequence_from_ref
#define ref_from_literal geneie_sequence_ref_from_literal
#define ref_from_string geneie_sequence_ref_from_string

typedef struct geneie_sequence_ref ref;
typedef struct geneie_sequence_tools_ref_pair ref_pair;

void test_ref_from_sequence(void)
{
	struct geneie_sequence
		sequence = from_string(VALID_NUCLEIC_CHARS);

	assert(geneie_sequence_valid(sequence));

	struct geneie_sequence_ref
		reference = ref_from_sequence(sequence);

	assert(reference.length == sequence.length);
	assert(reference.codes == sequence.codes);

	geneie_sequence_free(sequence);
}

void test_sequence_from_ref(void)
{
	{
		struct geneie_sequence_ref
			string_ref = ref_from_literal(VALID_NUCLEIC_CHARS);

		struct geneie_sequence
			sequence = sequence_from_ref(string_ref);

		assert(geneie_sequence_valid(sequence));
		assert(sequence.length == string_ref.length);
		assert(!memcmp(sequence.codes, string_ref.codes, (size_t)string_ref.length));

		geneie_sequence_free(sequence);
	}

	{
		struct geneie_sequence_ref invalid = { 0 };

		struct geneie_sequence
			sequence = sequence_from_ref(invalid);

		assert(!geneie_sequence_valid(sequence));
	}
}

void test_dna_to_premrna(void)
{
	{
		char dna[] = "ACGTRYKMSWBDHVNX-";

		struct geneie_sequence_ref
			reference = ref_from_string(dna);

		geneie_sequence_tools_dna_to_premrna(reference);

		assert(!strcmp(dna, "ACGURYKMSWBDHVNX-"));
	}

	{
		char dna[] = "ACGURYKMSWBDHVNX-";

		struct geneie_sequence_ref
			reference = ref_from_string(dna);

		geneie_sequence_tools_dna_to_premrna(reference);

		// should've done nothing

		assert(!strcmp(dna, "ACGURYKMSWBDHVNX-"));
	}
}

void test_clean_whitespace(void)
{
	{
		char dna[] = "ACGTRYKMSWBDHVNX-";

		struct geneie_sequence_ref
			reference = ref_from_literal(dna);

		struct geneie_sequence_ref
			result = geneie_sequence_tools_clean_whitespace(reference);

		// Should have done nothing
		assert(geneie_sequence_ref_equal(reference, result));
	}

	{
		char dna[] = "ACGTRY\nKMSWBD  HVNX-";

		struct geneie_sequence_ref
			reference = ref_from_literal(dna);

		assert(geneie_sequence_ref_valid(reference));

		struct geneie_sequence_ref
			result = geneie_sequence_tools_clean_whitespace(reference);

		struct geneie_sequence_ref
			expected = ref_from_literal("ACGTRYKMSWBDHVNX-");

		assert(geneie_sequence_ref_equal(result, expected));
	}
}

struct geneie_sequence_ref splice_G(struct geneie_sequence_ref strand, void *param)
{
	(void)param;
	ssize_t length = strand.length;
	geneie_code *current = strand.codes;

	for (; length; current++, length--)
		if (*current == GENEIE_CODE_GUANINE)
			return (struct geneie_sequence_ref) {
				1,
				current,
			};

	return (struct geneie_sequence_ref) { 0 };
}

void test_splice(void)
{
	{
		char dna[] = VALID_NUCLEIC_CHARS;

		struct geneie_sequence_ref sequence = ref_from_string(dna);

		const ssize_t original_length = sequence.length;

		struct geneie_sequence_ref new_sequence = geneie_sequence_tools_splice(sequence, &splice_G, NULL);

		assert(new_sequence.length == original_length - 1);

		struct geneie_sequence_ref expected = ref_from_literal("ACTURYKMSWBDHVNX-");

		assert(geneie_sequence_ref_equal(expected, new_sequence));
	}

	{
		char dna[] = "GGGUGGGA";

		struct geneie_sequence_ref sequence = ref_from_string(dna);

		struct geneie_sequence_ref new_sequence = geneie_sequence_tools_splice(sequence, &splice_G, NULL);

		assert(new_sequence.length == 2);
		assert(geneie_sequence_ref_equal(ref_from_literal("UA"), new_sequence));
	}
}

void test_encode(void)
{
	{
		char buffer[] = "AUGUAUUAA";
		ref input = ref_from_literal(buffer);

		ref expected_aminos = ref_from_literal("MY\0");

		ref_pair result = geneie_sequence_tools_encode(input);

		assert(geneie_sequence_ref_equal(expected_aminos, result.refs[0]));

		assert(result.refs[1].length == 0);
	}

	{
		char buffer[] = "AUG UA UU AA";
		ref input = ref_from_literal(buffer);

		ref expected_aminos = ref_from_literal("MY\0");

		ref_pair result = geneie_sequence_tools_encode(input);

		assert(geneie_sequence_ref_equal(expected_aminos, result.refs[0]));

		assert(result.refs[1].length == 0);
	}

	{
		char buffer[] = "AUGUAU-UAA";
		ref input = ref_from_literal(buffer);

		ref expected_aminos = ref_from_literal("MY");
		ref expected_nucleotides = ref_from_literal("-UAA");

		ref_pair result = geneie_sequence_tools_encode(input);

		assert(geneie_sequence_ref_equal(expected_aminos, result.refs[0]));
		assert(geneie_sequence_ref_equal(expected_nucleotides, result.refs[1]));
	}
}

int main()
{
	test_ref_from_sequence();
	test_sequence_from_ref();
	test_dna_to_premrna();
	test_splice();
	test_encode();
}
