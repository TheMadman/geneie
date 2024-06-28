#include <geneie.h>

#include <ctype.h>

// Convenience definitions for geneie functions
#define valid geneie_sequence_ref_valid
#define index geneie_sequence_ref_index
#define trunc geneie_sequence_ref_trunc
typedef struct geneie_sequence_ref seq_r;

/*
 * This is our custom function for detecting whitespace.
 *
 * This function acts as a way to communicate to
 * geneie_sequence_tools_splice() what the next part
 * of the sequence to remove should be.
 *
 * geneie_sequence_tools_splice() will call this
 * function from the beginning of the sequence. If this
 * function returns a sequence to splice,
 * geneie_sequence_tools_splice() will call this function
 * again, with the part of the sequence _after_ the
 * splice.
 *
 * The basic way it works is:
 * - Skip all characters that aren't whitespace;
 * - Count the number of whitespace characters are
 *   in a row;
 * - truncate the result to the length of the
 *   whitespace and return it.
 *
 * geneie_sequence_tools_splice() will stop calling
 * this function after it returns the null sequence,
 * indicated by return (seq_r) { 0 }.
 */
static seq_r splice_whitespace(seq_r ref, void *_)
{
	// The param is unused
	(void)_;
	for (; valid(ref); ref = index(ref, 1)) {
		if (!isspace(ref.codes[0]))
			continue;

		ssize_t whitespace_length = 0;
		seq_r result = ref;
		for (; valid(ref); ref = index(ref, 1)) {
			if (isspace(ref.codes[0]))
				whitespace_length++;
			else
				break;
		}

		return trunc(result, whitespace_length);
	}

	return (seq_r) { 0 };
}

/*
 * And here is the actual usage of geneie_sequence_tools_splice().
 *
 * In this case, we don't need to store any state for future
 * calls, so we just pass NULL as the additional parameter.
 */
seq_r geneie_sequence_tools_clean_whitespace(seq_r reference)
{
	return geneie_sequence_tools_splice(
		reference,
		splice_whitespace,
		NULL
	);
}

