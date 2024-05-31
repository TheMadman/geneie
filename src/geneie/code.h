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
 * \brief The type for storing IUPAC nucleic acid codes.
 */
typedef char geneie_code;
// Unambiguous codes
#define GENEIE_CODE_ADENINE 'A'
#define GENEIE_CODE_CYTOSINE 'C'
#define GENEIE_CODE_GUANINE 'G'
#define GENEIE_CODE_THYMINE 'T'
#define GENEIE_CODE_URACIL 'U'

// Ambiguous codes
#define GENEIE_CODE_PURINE 'R'
#define GENEIE_CODE_PYRIMDINE 'Y'
#define GENEIE_CODE_KETO 'K'
#define GENEIE_CODE_AMINO 'M'
#define GENEIE_CODE_STRONG 'S'
#define GENEIE_CODE_WEAK 'W'
#define GENEIE_CODE_NOT_A 'B'
#define GENEIE_CODE_NOT_C 'D'
#define GENEIE_CODE_NOT_G 'H'
#define GENEIE_CODE_NOT_TU 'V'
#define GENEIE_CODE_ANY 'N'

// Special codes
#define GENEIE_CODE_MASKED 'X'
#define GENEIE_CODE_GAP '-'

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
