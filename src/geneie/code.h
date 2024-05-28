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

#ifndef GENEIE_CODE_H
#define GENEIE_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/**
 * \file
 */

/**
 * \brief The IUPAC nucleic acid codes.
 */
enum GENEIE_CODE {
	// Unambiguous codes
	GENEIE_CODE_ADENINE = 'A',
	GENEIE_CODE_CYTOSINE = 'C',
	GENEIE_CODE_GUANINE = 'G',
	GENEIE_CODE_THYMINE = 'T',
	GENEIE_CODE_URACIL = 'U',

	// Ambiguous codes
	GENEIE_CODE_PURINE = 'R',
	GENEIE_CODE_PYRIMDINE = 'Y',
	GENEIE_CODE_KETO = 'K',
	GENEIE_CODE_AMINO = 'M',
	GENEIE_CODE_STRONG = 'S',
	GENEIE_CODE_WEAK = 'W',
	GENEIE_CODE_NOT_A = 'B',
	GENEIE_CODE_NOT_C = 'D',
	GENEIE_CODE_NOT_G = 'H',
	GENEIE_CODE_NOT_TU = 'V',
	GENEIE_CODE_ANY = 'N',

	// Special codes
	GENEIE_CODE_MASKED = 'X',
	GENEIE_CODE_GAP = '-',
};

/**
 * \brief Checks if a given null-terminated character string contains
 * 	exclusively valid sequence codes.
 *
 * \param string The string to test.
 *
 * \returns true if the seqeunce is valid, false otherwise.
 */
bool geneie_code_string_valid(const char *string);

/**
 * \brief Checks if a given character is a valid sequence character.
 *
 * \param character The character to test.
 *
 * \returns true if the character is valid, false otherwise.
 */
bool geneie_code_char_valid(char character);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // GENEIE_CODE_H
