\page large_encoding_example An example for loading a large file into memory and encoding the entire contents at once

This code is an example of a program which, instead of reading three characters at a time and writing a character out, takes a file name as an argument and attempts to process the whole file contents in-memory in one pass.

As long as you have enough memory for the file, large genomes can be loaded and processed in a single step. While this version of the program doesn't _print_ character amounts too high for printf, the whole file will still be processed.

If built with `-DBUILD_EXAMPLES=True`, this program should be under `pages/large_file_encoding`. Try running it passing a file with a complete DNA/mRNA sequence, a file with a gap '-' somewhere in the middle, and a sequence that starts with a gap '-'.

Finally, to see an amusing but harmless bug, try running the program with an empty file.

\include large_file_encoding.c
