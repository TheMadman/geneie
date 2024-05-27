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

#define VALID_CHARS "ACGTURYKMSWBDHVNX-"

void test_from_literal_success()
{
	struct geneie_sequence_ref
		result = geneie_sequence_ref_from_literal(VALID_CHARS);

	assert(geneie_sequence_ref_valid(result));
}

void test_from_literal_fail()
{
	struct geneie_sequence_ref
		result = geneie_sequence_ref_from_literal("Camel");

	assert(!geneie_sequence_ref_valid(result));
}

void test_from_string_success()
{
	struct geneie_sequence_ref
		result = geneie_sequence_ref_from_string(VALID_CHARS);

	assert(geneie_sequence_ref_valid(result));
}

void test_from_string_fail()
{
	struct geneie_sequence_ref
		result = geneie_sequence_ref_from_string("Camel");

	assert(!geneie_sequence_ref_valid(result));
}

int main()
{
	test_from_literal_success();
	test_from_literal_fail();
	test_from_string_success();
	test_from_string_fail();
}

