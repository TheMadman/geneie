# Note: I haven't checked the minimum version
# for the features I actually use, this is just
# the version installed on my systems
cmake_minimum_required(VERSION 3.21)

project(Geneie VERSION 0.1)

add_subdirectory(src)

if (BUILD_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif()
