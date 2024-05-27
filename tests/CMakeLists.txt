function(testcase target)
	add_executable(test_${target} ${target}.c)
	target_link_libraries(test_${target} geneie)
	add_test(NAME ${target} COMMAND test_${target})
endfunction()

testcase(geneie_sequence)
testcase(geneie_sequence_ref)
