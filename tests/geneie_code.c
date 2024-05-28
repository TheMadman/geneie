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
#include "geneie/code.h"

#define VALID_CHARS "ACGTURYKMSWBDHVNX-"

static bool in(char c, const char *str)
{
	for (; *str; str++)
		if (c == *str)
			return true;
	return false;
}

void test_char_valid_success()
{
	for (const char *current = VALID_CHARS; *current; current++) {
		assert(geneie_code_char_valid(*current));
	}
}

void test_char_valid_fail()
{
	// just testing the ASCII printable character range for now
	for (char current = ' '; current != '~'; current++)
		if (!in(current, VALID_CHARS))
			assert(!geneie_code_char_valid(current));
}

void test_string_valid_success()
{
	assert(geneie_code_string_valid(VALID_CHARS));
}

void test_string_valid_fail()
{
	assert(!geneie_code_string_valid("Camel"));
}

int main()
{
	test_char_valid_success();
	test_char_valid_fail();
	test_string_valid_success();
	test_string_valid_fail();
}
