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

#ifndef GENEIE_SEQUENCE_TOOLS_H
#define GENEIE_SEQUENCE_TOOLS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sequence.h"
#include "sequence_ref.h"

/**
 * \file
 */

/**
 * \brief Creates a reference from a sequence.
 *
 * Using a reference that references a sequence that
 * has been freed is undefined behaviour.
 *
 * \param sequence The sequence to create a reference for.
 *
 * \returns A reference to the sequence, or an invalid
 * 	reference if sequence is NULL.
 */
struct geneie_sequence_ref
geneie_sequence_tools_ref_from_sequence(struct geneie_sequence *sequence);

/**
 * \brief Allocates a new sequence object from a
 * 	given sequence reference.
 *
 * If the reference doesn't pass geneie_sequence_ref_valid(),
 * a NULL pointer is returned.
 *
 * A NULL pointer is also returned if allocation failed.
 *
 * \param reference The reference to create a copy from.
 *
 * \returns A pointer to the newly allocated sequence, or
 * 	NULL if an error occurred.
 */
struct geneie_sequence *
geneie_sequence_tools_sequence_from_ref(struct geneie_sequence_ref reference);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // GENEIE_SEQUENCE_TOOLS_H
