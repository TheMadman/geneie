\mainpage

## The Basics

The full library can be accessed by doing `#include <geneie.h>` and linking
against `geneie`, such as with `-lgeneie` for GCC/Clang.

The two main structures of geneie are the geneie\_sequence\_ref and the
geneie\_sequence.

geneie\_sequence\_ref objects _refer_ to some data stored somewhere else,
such as a static geneie\_code array. geneie\_sequence objects allocate memory
and create copies of the data, and must be freed with geneie\_sequence\_free().

Most of the API for processing sequences takes geneie\_sequence\_ref%s, and
processes them in-place. Therefore:
- Huge sequences (in the megabytes) can be processed without expensive
  allocations and copies being made; however,
- processing the data can be destructive and irriversable.

If you need to keep a copy of the original data around, you can:
- create a geneie\_sequence which is a copy of a
  geneie\_sequence\_ref using geneie\_sequence\_tools\_sequence\_from\_ref();
- create a new geneie\_sequence\_ref, referencing the geneie\_sequence,
  using geneie\_sequence\_tools\_ref\_from\_sequence(); and finally,
- perform the processing on the new reference object.

I know this is a wordy process: more convenient functions are planned.

For usage examples, consider:
- \ref simple_example "An example of encoding codons one-by-one"
- \ref large_encoding_example "A larger example, loading a file into memory in one read and performing encoding on the whole contents at once"
- \ref splice_simple "A simple example of geneie_sequence_tools_splice() usage"
