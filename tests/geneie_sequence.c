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
#include "geneie/sequence.h"

#include <string.h>

#define VALID_CHARS "ACGTURYKMSWBDHVNX-"

static bool in(char c, const char *str)
{
	for (; *str; str++)
		if (c == *str)
			return true;
	return false;
}

void test_alloc_success()
{
	{
		struct geneie_sequence *result = geneie_sequence_alloc(1);

		assert(result);

		geneie_sequence_free(result);
	}
	{
		struct geneie_sequence *result = geneie_sequence_alloc(0);

		// 0 size should return a pointer to a ssize_t
		assert(result);

		geneie_sequence_free(result);
	}
}

// cba with stubbing out malloc or something right now
// void test_alloc_fail()

void test_from_string_success()
{
	struct geneie_sequence *result = geneie_sequence_from_string(VALID_CHARS);

	assert(result);

	// length shouldn't consider the null pointer
	assert(result->length == sizeof(VALID_CHARS) - 1);

	geneie_sequence_free(result);
}

void test_from_string_fail()
{
	struct geneie_sequence *result = geneie_sequence_from_string("Camel");

	assert(!result);
}

void test_copy_success()
{
	struct geneie_sequence *result = geneie_sequence_from_string(VALID_CHARS);

	assert(result);

	struct geneie_sequence *copy = geneie_sequence_copy(result);

	assert(copy->length == result->length);
	assert(!memcmp(copy->codes, result->codes, copy->length));

	geneie_sequence_free(result);
	geneie_sequence_free(copy);
}

void test_char_valid_success()
{
	for (const char *current = VALID_CHARS; *current; current++) {
		assert(geneie_sequence_char_valid(*current));
	}
}

void test_char_valid_fail()
{
	// just testing the ASCII printable character range for now
	for (char current = ' '; current != '~'; current++)
		if (!in(current, VALID_CHARS))
			assert(!geneie_sequence_char_valid(current));
}

void test_string_valid_success()
{
	assert(geneie_sequence_string_valid(VALID_CHARS));
}

void test_string_valid_fail()
{
	assert(!geneie_sequence_string_valid("Camel"));
}

int main()
{
	test_alloc_success();
	test_from_string_success();
	test_from_string_fail();
	test_char_valid_success();
	test_char_valid_fail();
	test_string_valid_success();
	test_string_valid_fail();
}
