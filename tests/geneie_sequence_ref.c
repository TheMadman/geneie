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
#include "geneie/sequence_ref.h"

#define VALID_NUCLEIC_CHARS "ACGTURYKMSWBDHVNX-"

void test_from_literal_success()
{
	struct geneie_sequence_ref
		result = geneie_sequence_ref_from_literal(VALID_NUCLEIC_CHARS);

	assert(geneie_sequence_ref_valid(result));
}

void test_from_literal_fail()
{
	struct geneie_sequence_ref
		result = geneie_sequence_ref_from_literal("<html>");

	assert(!geneie_sequence_ref_valid(result));
}

void test_from_string_success()
{
	struct geneie_sequence_ref
		result = geneie_sequence_ref_from_string(VALID_NUCLEIC_CHARS);

	assert(geneie_sequence_ref_valid(result));
}

void test_from_string_fail()
{
	struct geneie_sequence_ref
		result = geneie_sequence_ref_from_string("<html>");

	assert(!geneie_sequence_ref_valid(result));
}

void test_equal_success()
{
	struct geneie_sequence_ref
		first = geneie_sequence_ref_from_string(VALID_NUCLEIC_CHARS),
		second = geneie_sequence_ref_from_string(VALID_NUCLEIC_CHARS);

	assert(geneie_sequence_ref_equal(first, second));
}

void test_equal_fail()
{
	{
		// different lengths
		struct geneie_sequence_ref
			first = geneie_sequence_ref_from_string(VALID_NUCLEIC_CHARS),
			second = geneie_sequence_ref_from_string("AACGTAG");

		assert(!geneie_sequence_ref_equal(first, second));
	}

	{
		// same lengths
		struct geneie_sequence_ref
			first = geneie_sequence_ref_from_string("ACGT"),
			second = geneie_sequence_ref_from_string("ACGU");

		assert(!geneie_sequence_ref_equal(first, second));
	}
}

void test_index()
{
	struct geneie_sequence_ref
		start = geneie_sequence_ref_from_string(VALID_NUCLEIC_CHARS),
		result = geneie_sequence_ref_index(start, 4);

	assert(result.length == start.length - 4);
	assert(result.codes == &start.codes[4]);
}

int main()
{
	test_from_literal_success();
	test_from_literal_fail();
	test_from_string_success();
	test_from_string_fail();
	test_equal_success();
	test_equal_fail();
	test_index();
}

