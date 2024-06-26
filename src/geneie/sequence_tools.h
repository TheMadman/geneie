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
geneie_sequence_tools_ref_from_sequence(struct geneie_sequence sequence);

/**
 * \brief Allocates a new sequence object from a
 * 	given sequence reference.
 *
 * If the reference doesn't pass geneie_sequence_ref_valid(),
 * an invalid sequence is returned.
 *
 * An invalid sequence is also returned if allocation failed.
 *
 * \param reference The reference to create a copy from.
 *
 * \returns The newly constructed geneie sequence, or
 * 	a sequence failing geneie_sequence_valid() on failure.
 */
struct geneie_sequence
geneie_sequence_tools_sequence_from_ref(struct geneie_sequence_ref reference);

/**
 * \brief Removes any whitespace characters from the sequence.
 *
 * This can occur from e.g. initializing a sequence from
 * file contents.
 *
 * \param reference A reference to the sequence to clean.
 *
 * \returns A reference with the new length.
 */
struct geneie_sequence_ref
geneie_sequence_tools_clean_whitespace(struct geneie_sequence_ref reference);

/**
 * \brief Performs an in-place translation of a
 * 	DNA sequence to a pre-mRNA sequence.
 *
 * Ambiguous nucleotide codes, amino acid codes and gaps are left
 * untouched. Otherwise, all T codes are transformed into U codes.
 *
 * \param reference The sequence reference to modify.
 */
void geneie_sequence_tools_dna_to_premrna(struct geneie_sequence_ref reference);

/**
 * \brief The function signature for a splicer.
 *
 * A splicer is a function which takes a pre-mRNA
 * sequence and returns, as a sequence, the first
 * part that should be spliced, or a reference
 * with zero length if there is nothing to splice.
 */
typedef struct geneie_sequence_ref
	geneie_sequence_tools_splicer(
		struct geneie_sequence_ref strand,
		void *param
	);

/**
 * \brief Splices a pre-mRNA sequence into a mature
 * 	mRNA sequence.
 *
 * Takes a geneie_sequence_tools_splicer callback, which
 * can be called multiple times: first with the full
 * sequence, then, if there was a sequence to splice,
 * with the remainder of the original sequence, and
 * so on, until there is nothing left to splice.
 *
 * Then, the original sequence is modified in-place
 * to remove the parts of the sequence that are to
 * be spliced.
 *
 * A new sequence, containing the final length, is
 * returned. The original reference is invalid and should
 * not be used anymore.
 *
 * \param strand The strand of pre-mRNA to splice.
 * \param splicer_func A function which analyses the
 * 	strand for a section to splice.
 * \param param An optional parameter. This will be passed
 * 	to the splicer_func on each call. This provides
 * 	a way to track state between calls to splicer_func.
 *
 * \returns A new reference, containing the correct
 * 	length, after splicing.
 */
struct geneie_sequence_ref geneie_sequence_tools_splice(
	struct geneie_sequence_ref strand,
	geneie_sequence_tools_splicer *splicer_func,
	void *param
);

/**
 * \brief Provides a pair of references.
 */
struct geneie_sequence_tools_ref_pair {
	struct geneie_sequence_ref refs[2];
};

/**
 * \brief Encodes mRNA sequences into amino acid sequences
 * 	in-place.
 *
 * Stops when one of the following conditions are met:
 *
 * - A codon encodes to a stop sequence
 * - A codon contains ambiguous mRNA codes that do not
 *   resolve unambiguously to a single amino acid
 * - A codon contains a gap of indeterminate length
 *
 * \param strand The mRNA strand to encode.
 *
 * \returns A pair of new references, the first containing
 * 	the encoded amino acid sequence and the second
 * 	containing the remaining strand.
 */
struct geneie_sequence_tools_ref_pair geneie_sequence_tools_encode(
	struct geneie_sequence_ref strand
);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // GENEIE_SEQUENCE_TOOLS_H
