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

void test_ref_from_sequence()
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

void test_sequence_from_ref()
{
	{
		struct geneie_sequence_ref
			string_ref = ref_from_literal(VALID_NUCLEIC_CHARS);

		struct geneie_sequence
			sequence = sequence_from_ref(string_ref);

		assert(geneie_sequence_valid(sequence));
		assert(sequence.length == string_ref.length);
		assert(!memcmp(sequence.codes, string_ref.codes, string_ref.length));
	}

	{
		struct geneie_sequence_ref invalid = { 0 };

		struct geneie_sequence
			sequence = sequence_from_ref(invalid);

		assert(!geneie_sequence_valid(sequence));
	}
}

void test_dna_to_premrna()
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

void test_splice()
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

int main()
{
	test_ref_from_sequence();
	test_sequence_from_ref();
	test_dna_to_premrna();
	test_splice();
}
