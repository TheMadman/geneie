set(SOURCES
	code.c
	encoding.c
	sequence_ref.c
	sequence.c
	sequence_tools.c
)

add_library(geneie SHARED ${SOURCES})
add_library(geneiestatic STATIC ${SOURCES})

target_include_directories(geneie
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>)
target_include_directories(geneiestatic
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>)

install(TARGETS geneie geneiestatic
	DESTINATION lib)
install(FILES geneie.h DESTINATION include)
install(DIRECTORY geneie DESTINATION include)
