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

void test_ref_from_sequence()
{
	struct geneie_sequence
		sequence = from_string(VALID_CHARS);

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
			string_ref = ref_from_literal(VALID_CHARS);

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

int main()
{
	test_ref_from_sequence();
	test_sequence_from_ref();
}
