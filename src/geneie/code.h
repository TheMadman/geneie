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
 * \brief The type for storing IUPAC nucleic acid codes
 * 	and IUPAC amino acid codes.
 */
typedef char geneie_code;

// Nucleic acid codes
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

// Amino acid codes
#define GENEIE_CODE_ALANINE 'A'
#define GENEIE_CODE_CYSTEINE 'C'
#define GENEIE_CODE_ASPARTIC_ACID 'D'
#define GENEIE_CODE_GLUTAMIC_ACID 'E'
#define GENEIE_CODE_PHENYLALANINE 'F'
#define GENEIE_CODE_GLYCINE 'G'
#define GENEIE_CODE_HISTIDINE 'H'
#define GENEIE_CODE_ISOLEUCINE 'I'
#define GENEIE_CODE_LYSINE 'K'
#define GENEIE_CODE_LEUCINE 'L'
#define GENEIE_CODE_METHIONINE 'M'
#define GENEIE_CODE_ASPARAGINE 'N'
#define GENEIE_CODE_PROLINE 'P'
#define GENEIE_CODE_GLUTAMINE 'Q'
#define GENEIE_CODE_ARGININE 'R'
#define GENEIE_CODE_SERINE 'S'
#define GENEIE_CODE_THREONINE 'T'
#define GENEIE_CODE_VALINE 'V'
#define GENEIE_CODE_TRYPTOPHAN 'W'
#define GENEIE_CODE_TYROSINE 'Y'

/**
 * \brief Checks if a given null-terminated character string contains
 * 	exclusively valid neucleic acid codes.
 *
 * \param string The string to test.
 *
 * \returns true if the seqeunce is valid, false otherwise.
 */
bool geneie_code_nucleic_string_valid(const char *string);

/**
 * \brief Checks if a given character is a valid nucleic acid character.
 *
 * \param character The character to test.
 *
 * \returns true if the character is valid, false otherwise.
 */
bool geneie_code_nucleic_char_valid(char character);

/**
 * \brief Checks if a given null-terminated string contains
 * 	exclusively valid amino acid codes.
 *
 * \param string The string to test.
 *
 * \returns true if the sequence is valid, false otherwise.
 */
bool geneie_code_amino_string_valid(const char *string);

/**
 * \brief Checks if a given character is a valid amino acid character.
 *
 * \param character The character to test.
 *
 * \returns true if the character is valid, false otherwise.
 */
bool geneie_code_amino_char_valid(char character);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // GENEIE_CODE_H
