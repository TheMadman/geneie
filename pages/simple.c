#include <stdio.h>

#include <geneie.h>

typedef struct geneie_sequence_ref ref;

/*
 * This simple program takes a text file from standard
 * input, checks if the characters are valid DNA/mRNA
 * nucleotide codes, encodes codons into single-letter
 * amino acid codes, and prints the result to stdout.
 *
 * This shows a few different ways to build a geneie_sequence_ref,
 * which is a structure that uses memory created somewhere
 * else. Most of the APIs in geneie use the geneie_sequence_ref,
 * in order to avoid lots of allocations of potentially
 * huge amounts of memory.
 */
int main()
{
	for (;;) {
		// three characters for the codon, plus a null terminator
		char codon_store[4] = { 0 };
		char *codon_end = &codon_store[3];

		for (char *current = codon_store; current < codon_end; current++) {
			const int input = getchar();

			if (input == EOF)
				return 0;

			*current = (char)input;
		}

		// In this case, you _could_ opt to use
		// geneie_sequence_ref_from_literal(), since the buffer is
		// static. However, ref_from_string() will work for all
		// null-terminated strings, including those allocated dynamically.
		ref codon = geneie_sequence_ref_from_string(codon_store);

		// geneie_sequence_ref_from_string() and _from_literal() will
		// check if the passed string consists of valid nucleotide codes.
		//
		// If the string contains invalid codes, it will fail a call to
		// geneie_sequence_ref_valid().
		//
		// Valid nucleotide codes include the ambiguous nucleotide codes
		// specified by the IUPAC.
		if (!geneie_sequence_ref_valid(codon))
			return 1;

		char amino_store[1] = { 0 };

		// This call, by contrast, doesn't check for valid codes.
		// This is fine here, since we are using this reference as an
		// out parameter for an amino acid code.
		ref amino = geneie_sequence_ref_from_array_unsafe(amino_store);

		// If the encoding was successful, print the amino code
		if (geneie_encoding_one_codon(codon, amino))
			putchar(amino_store[0]);
		// Otherwise, return an error.
		// Encoding can fail if we can't determine what amino acid
		// the codon can encode to.
		else
			return 1;
	}
}
