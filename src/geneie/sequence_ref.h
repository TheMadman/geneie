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

#ifndef GENEIE_SEQUENCE_REF_H
#define GENEIE_SEQUENCE_REF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <stdbool.h>
#include <stddef.h>

#include "code.h"

/**
 * \file
 */

/**
 * \brief Represents a DNA, mRNA, etc. sequence.
 *
 * These sequence objects are non-owning - that is,
 * when you construct these objects with a string,
 * they do not allocate new memory, copy data and
 * store a new string. They simply refer back to
 * the string you pass them.
 */
struct geneie_sequence_ref {

	/**
	 * \brief The length of the gene sequence.
	 *
	 * &codes[length] returns one pointer past the end
	 * of the data.
	 */
	ssize_t length;

	/**
	 * \brief The beginning of the gene sequence.
	 */
	geneie_code *const codes;
};

/**
 * \brief Constructs a geneie_sequence_ref from a C string literal.
 *
 * \param string_literal A C string literal, such as `"ACGT"`.
 * 	For dynamic strings (e.g. read from a file), use
 * 	geneie_sequence_ref_from_string().
 *
 * \returns A new object on succes, or an object that fails a
 * 	geneie_sequence_valid() call on error.
 */
#define geneie_sequence_ref_from_literal(string_literal) \
((struct geneie_sequence_ref) { \
	sizeof(string_literal) - 1, \
	geneie_code_string_valid(string_literal) ? \
		(geneie_code *const)string_literal : \
		NULL, \
})

/**
 * \brief Constructs a geneie_sequence_strand from a null-terminated
 * 	character array.
 *
 * If the string contains characters that aren't valid sequence codes,
 * an error object is returned.
 *
 * \param string The string to construct a sequence from.
 *
 * \returns A new object on success, or an object which fails a
 * 	geneie_sequence_valid() call on error.
 */
struct geneie_sequence_ref geneie_sequence_ref_from_string(char *string);

/**
 * \brief Checks if the given object is valid to use.
 *
 * \param sequence The sequence to test.
 *
 * \returns true if the sequence is valid, false otherwise.
 */
bool geneie_sequence_ref_valid(struct geneie_sequence_ref sequence);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // GENEIE_SEQUENCE_REF_H
