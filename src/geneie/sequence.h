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

#include "code.h"

/**
 * \file
 */

/**
 * \brief Represents a sequence of codes, defined in code.h.
 *
 * These objects are intended to always be heap-allocated.
 * Constructing these objects from strings, from
 * geneie_sequence_ref objects, or from each other,
 * will always allocate on the heap.
 *
 * You must pass these to geneie_sequence_free() when
 * finished with them.
 *
 * \sa GENEIE_SEQUENCE_WITH
 */
struct geneie_sequence {
	/**
	 * \brief The length of the gene sequence.
	 *
	 * &codes[length] returns a pointer to a null
	 * terminator.
	 */
	ssize_t length;

	/**
	 * \brief The beginning of the gene sequence.
	 *
	 * A null terminator is added automatically. This
	 * library will ignore the null terminator for
	 * processing.
	 */
	geneie_code *codes;
};

/**
 * \public \memberof geneie_sequence
 * \brief Returns whether this is a valid geneie_sequence
 * 	object.
 *
 * \param sequence The sequence to test.
 *
 * \returns True if the sequence is safe to use, false otherwise.
 */
bool geneie_sequence_valid(struct geneie_sequence sequence);

/**
 * \public \memberof geneie_sequence
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
 * \sa GENEIE_SEQUENCE_WITH
 */
struct geneie_sequence geneie_sequence_alloc(ssize_t length);

/**
 * \public \memberof geneie_sequence
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
struct geneie_sequence geneie_sequence_from_string(const char *string);

/**
 * \public \memberof geneie_sequence
 * \brief Constructs a geneie_sequence that is a copy of the given
 * 	sequence.
 *
 * \param other The sequence object to copy.
 *
 * \returns A newly constructed geneie_sequence object, or NULL
 * 	if allocation failed.
 */
struct geneie_sequence geneie_sequence_copy(struct geneie_sequence other);

/**
 * \public \memberof geneie_sequence
 * \brief Frees a given geneie_sequence.
 *
 * \param sequence The sequence to free.
 */
void geneie_sequence_free(struct geneie_sequence sequence);

/**
 * \brief Provides a context-manager-esque interface for
 * 	a sequence.
 *
 * This allocates a sequence, checks if it's valid, runs
 * your block of code, then frees when control leaves the block.
 *
 * If allocation fails, the code block is skipped.
 *
 * Usage is as follows:
 *
 * \code
 * GENEIE_SEQUENCE_WITH(my_sequence, 1024) {
 * 	// `my_sequence` is now a struct geneie_sequence
 * 	// and can be used normally
 * 	struct geneie_sequence_ref ref = geneie_sequence_tools_ref_from_sequence(my_sequence);
 * 	// etc.
 *
 * 	// Using `break` and (most) `return` statements
 * 	// from here will result in a leak; to finish
 * 	// early and still clean up, use `continue`.
 * 	if (some_error)
 * 		continue;
 *
 * 	// The only thing you can return that won't leak
 * 	// `my_sequence` is `my_sequence`.
 * 	return my_sequence;
 * }
 * \endcode
 *
 * \param NAME The name to give the sequence variable.
 * \param LENGTH The length of the sequence to allocate.
 */
#define GENEIE_SEQUENCE_WITH(NAME, LENGTH) \
for ( \
	struct geneie_sequence NAME = geneie_sequence_alloc(LENGTH); \
	geneie_sequence_valid(NAME); \
	geneie_sequence_free(NAME), NAME = (struct geneie_sequence){ 0 } \
)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // GENEIE_SEQUENCE_H
