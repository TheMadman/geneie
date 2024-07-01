#include <stdio.h>
#include <errno.h>
#include <limits.h>

#include <geneie.h>

/*
 * This example shows another use of geneie_sequence_ref,
 * using the geneie_sequence_tools_encode function to
 * encode a large sequence in-place.
 *
 * We use a geneie_sequence to allocate memory, populate
 * it with data from a file, then create a reference to
 * it for processing.
 */

typedef struct geneie_sequence seq_t;
typedef struct geneie_sequence_ref ref_t;
typedef struct geneie_sequence_tools_ref_pair pair_t;

/*
 * Moved the processing to a separate function, so even if an
 * error is returned here, we can fclose() the file safely
 * in main().
 */
int process_file(FILE *file)
{
	/*
	 * Most of this is just getting an amount of memory
	 * to allocate for this file.
	 */
	if (fseek(file, 0, SEEK_END))
		return errno;

	long length = ftell(file);

	if (length < 0)
		return errno;

	rewind(file);

	/*
	 * geneie_sequence_alloc() will allocate length memory,
	 * creating (and preserving) a null terminator for
	 * convenience.
	 */
	seq_t store = geneie_sequence_alloc(length);
	if (!geneie_sequence_valid(store))
		return errno;

	size_t read_amount = fread(store.codes, 1, (size_t)length, file);

	if (ferror(file)) {
		geneie_sequence_free(store);
		return ferror(file);
	}

	/*
	 * Most processing isn't performed against geneie_sequence
	 * objects directly, instead it happens through a reference.
	 *
	 * This helps to simplify resource management - references
	 * are never allocated and never freed; each sequence should
	 * have been allocated, and each must be passed to
	 * geneie_sequence_free().
	 */
	ref_t ref = geneie_sequence_tools_ref_from_sequence(store);
	// only consider read amount
	ref = geneie_sequence_ref_trunc(ref, (ssize_t)read_amount);
	// clean whitespace
	ref = geneie_sequence_tools_clean_whitespace(ref);

	/*
	 * Finally, encode the data in-place.
	 *
	 * In-place encoding avoids the cost of allocating and copying
	 * potentially huge amounts of data, at the cost of (obviously)
	 * destroying the original data stored in the sequence.
	 *
	 * This function returns a pair of geneie_sequence_ref objects:
	 * the first is the a sequence containing the amino acids that
	 * could be encoded; the second contains the remainder of the
	 * DNA/mRNA sequence, starting from the first codon that failed.
	 */
	pair_t pair = geneie_sequence_tools_encode(ref);

	if (pair.refs[0].length > INT_MAX)
		printf("Encoded output too long for printf");
	else if (pair.refs[0].length == 0)
		printf("No DNA/mRNA encoded\n");
	else
		/*
		 * The %.*s syntax here allows us to print only the
		 * characters in the sequence. To learn more, check
		 * the Precision section of the printf man page.
		 */
		printf("Encoded output: %.*s\n", (int)pair.refs[0].length, pair.refs[0].codes);

	if (pair.refs[1].length > INT_MAX)
		printf("Remaining DNA/mRNA too long for printf");
	else if (pair.refs[1].length == 0)
		printf("All DNA/mRNA encoded\n");
	else
		printf("Remaining DNA/mRNA: %.*s\n", (int)pair.refs[1].length, pair.refs[1].codes);

	geneie_sequence_free(store);
	return 0;
}

/*
 * All this main function does is check if a filename was given
 * as an argument, try to open the file, handle errors, then pass
 * the file on to process_file.
 *
 * Finally, it safely closes the file and returns the result
 * of process_file.
 */
int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;

	FILE *file = fopen(argv[1], "r");
	if (!file)
		return errno;

	int return_value = process_file(file);
	fclose(file);
	return return_value;
}
