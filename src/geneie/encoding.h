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

#ifndef GENEIE_ENCODING_H
#define GENEIE_ENCODING_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \file
 */

#include "sequence_ref.h"

/**
 * \brief For a given list of codes, returns
 * 	a list of codes that will match, including
 * 	ambiguous codes.
 *
 * For example, passing "UC" will return "CTUY". Passing
 * "UCAG" will return a list including every ambiguous
 * code, except '-'.
 *
 * Passing ambiguous codes will also produce complete
 * codes: passing "Y" will return "CTUY", as above.
 * Passing "YR" will return every ambiguous code.
 *
 * For the purposes of this function, "T" and "U" are
 * treated as synonyms: for this reason, passing "U"
 * or "T" will return both codes, "TU". This applies to
 * ambiguous codes as well, as described above.
 *
 * The geneie_sequence_ref returned references static
 * memory and should _not_ be mutated.
 *
 * \param codes A list of the codes you want valid codes
 * 	for.
 *
 * \returns The codes that will match the given codes.
 */
struct geneie_sequence_ref geneie_encoding_get_valid_codes(
	struct geneie_sequence_ref codes
);

/**
 * \brief This function encodes a single codon from
 * 	codon into a single amino acid character given
 * 	by amino_out.
 *
 * If the codon contains a gap of indeterminate length,
 * or an ambiguous code that does not resolve to a single
 * amino acid unambiguously, then the encoding will fail
 * and nothing will be written to amino_out.
 *
 * If either the codon or the amino_out are not long
 * enough, the encoding will fail and nothing will be
 * written to amino_out.
 *
 * \param codon The codon to encode an amino acid for.
 * \param amino_out The location to write a single amino
 * 	character to.
 *
 * \returns True if the encoding was successful, false
 * 	otherwise. If the encoding failed, amino_out
 * 	is left unchanged.
 */
bool geneie_encoding_one_codon(
	struct geneie_sequence_ref codon,
	struct geneie_sequence_ref amino_out
);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // GENEIE_ENCODING_H
