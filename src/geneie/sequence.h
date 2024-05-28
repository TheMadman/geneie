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

#ifndef GENEIE_SEQUENCE_H
#define GENEIE_SEQUENCE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <stdbool.h>

/**
 * \file
 */

/**
 * \brief The IUPAC nucleic acid codes.
 */
enum GENEIE_SEQUENCE_CODE {
	// Unambiguous codes
	GENEIE_SEQUENCE_ADENINE = 'A',
	GENEIE_SEQUENCE_CYTOSINE = 'C',
	GENEIE_SEQUENCE_GUANINE = 'G',
	GENEIE_SEQUENCE_THYMINE = 'T',
	GENEIE_SEQUENCE_URACIL = 'U',

	// Ambiguous codes
	GENEIE_SEQUENCE_PURINE = 'R',
	GENEIE_SEQUENCE_PYRIMDINE = 'Y',
	GENEIE_SEQUENCE_KETO = 'K',
	GENEIE_SEQUENCE_AMINO = 'M',
	GENEIE_SEQUENCE_STRONG = 'S',
	GENEIE_SEQUENCE_WEAK = 'W',
	GENEIE_SEQUENCE_NOT_A = 'B',
	GENEIE_SEQUENCE_NOT_C = 'D',
	GENEIE_SEQUENCE_NOT_G = 'H',
	GENEIE_SEQUENCE_NOT_TU = 'V',
	GENEIE_SEQUENCE_ANY = 'N',

	// Special codes
	GENEIE_SEQUENCE_MASKED = 'X',
	GENEIE_SEQUENCE_GAP = '-',
};

/**
 * \brief Represents a DNA, mRNA, etc. sequence.
 *
 * These objects are intended to always be heap-allocated.
 * Constructing these objects from strings, from
 * geneie_sequence_ref objects, or from each other,
 * will always allocate on the heap.
 *
 * You must pass these to geneie_sequence_free() when
 * finished with them.
 */
struct geneie_sequence {
	/**
	 * \brief The length of the gene sequence.
	 *
	 * &codes[length] returns one pointer past the end
	 * of the data.
	 */
	ssize_t length;

	/**
	 * \brief The beginning of the gene sequence.
	 *
	 * Gene sequences in this object are NOT null-terminated.
	 */
	enum GENEIE_SEQUENCE_CODE codes[];
};

/**
 * \brief Allocates uninitialized memory for a geneie_sequence
 * 	object and initializes its `length` member.
 *
 * The resulting object can store `length` acid codes.
 *
 * This object must be passed to geneie_sequence_free() when
 * finished.
 *
 * \param length The amount of codes to allocate memory for.
 *
 * \returns A pointer to a newly-allocated object, or NULL
 * 	if allocation failed.
 */
struct geneie_sequence *geneie_sequence_alloc(ssize_t length);

/**
 * \brief Constructs a new geneie_sequence from the given string.
 *
 * If the string is not a valid sequence, then the function returns
 * a NULL pointer.
 *
 * \param string The string to make a sequence from.
 *
 * \returns A newly constructed geneie_sequence object, or NULL
 * 	if there was an error.
 */
struct geneie_sequence *geneie_sequence_from_string(const char *string);

/**
 * \brief Constructs a geneie_sequence that is a copy of the given
 * 	sequence.
 *
 * \param other The sequence object to copy.
 *
 * \returns A newly constructed geneie_sequence object, or NULL
 * 	if allocation failed.
 */
struct geneie_sequence *geneie_sequence_copy(struct geneie_sequence *other);

/**
 * \brief Frees a given geneie_sequence.
 *
 * \param sequence The sequence to free.
 */
void geneie_sequence_free(struct geneie_sequence *sequence);

/**
 * \brief Checks if a given null-terminated character string contains
 * 	exclusively valid sequence codes.
 *
 * \param string The string to test.
 *
 * \returns true if the seqeunce is valid, false otherwise.
 */
bool geneie_sequence_string_valid(const char *string);

/**
 * \brief Checks if a given character is a valid sequence character.
 *
 * \param character The character to test.
 *
 * \returns true if the character is valid, false otherwise.
 */
bool geneie_sequence_char_valid(char character);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // GENEIE_SEQUENCE_H
