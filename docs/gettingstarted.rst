Getting Started
===============

CMake
-----

Clone the repo into your vendor directory, and add it into your CMakeLists.txt file.

.. code-block:: cmake

	add_subdirectory("vendor/LightningScanner")

	target_link_libraries(YourPoject PRIVATE LightningScanner)


Code examples
~~~~~~~~~~~~~

.. code-block:: cpp

	#include <LightningScanner/LightningScanner.hpp>

	using namespace LightningScanner;

	int main() {
		void* binary = ...;
		size_t binarySize = ...;

		const auto scanner = Scanner("48 89 5c 24 ?? 48 89 6c");
		uint8_t* result = scanner.Find(binary, binarySize).Get<uint8_t>();
		...
	}
