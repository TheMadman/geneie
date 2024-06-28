\page splice_simple A simple example using the geneie_sequence_tools_splice() function

RNA Splicing is, potentially, one of the most complex things that happens in the gene processing. Whether splicing happens, and how that splicing happens, varies from organism to organism. The splicing function that geneie provides takes, as one of its arguments, a function which tells it _what the next thing to splice is_.

A simple example of the splice function in action is an implementation of the geneie_sequence_tools_clean_whitespace() function, which doesn't require an additional parameter:

\include clean_whitespace.c

