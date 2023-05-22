find_package(Sphinx REQUIRED)

set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs/doxygen)

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

get_target_property(LightningScanner_PUBLIC_HEADER_DIR LightningScanner INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE LightningScanner_PUBLIC_HEADERS ${LightningScanner_PUBLIC_HEADER_DIR}/*.hpp)

set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/docs/sphinx)
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

# Build docs with sphinx
# Docs get rebuild when:
#  - Doc files change
#  - Sphinx config changes
set(DOCS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/index.rst ${CMAKE_CURRENT_SOURCE_DIR}/gettingstarted.rst)

add_custom_command(OUTPUT ${SPHINX_INDEX_FILE}
	COMMAND ${CMAKE_COMMAND} -E env DOXYGEN_OUTPUT_DIR=${DOXYGEN_OUTPUT_DIR} ${SPHINX_EXECUTABLE} -b html ${SPHINX_SOURCE} ${SPHINX_BUILD}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	DEPENDS ${DOCS_FILES} ${DOXYGEN_INDEX_FILE} ${DOXYGEN_OUTPUT_DIR} ${LightningScanner_PUBLIC_HEADERS}
	MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
	COMMENT "Generting docs with sphinx")

add_custom_target(Sphinx ALL DEPENDS ${SPHINX_INDEX_FILE})