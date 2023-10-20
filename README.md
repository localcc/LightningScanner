# LightningScanner

A lightning-fast memory pattern scanner, capable of scanning gigabytes of data per second.

## Examples

Here's an example of how to find an IDA-style memory pattern inside of a binary.

```cpp
#include <LightningScanner/LightningScanner.hpp>

using namespace LightningScanner;

int main() {
	void* binary = ...;
	size_t binarySize = ...;

	const auto scanner = Scanner("48 89 5c 24 ?? 48 89 6c");
	uint8_t* result = scanner.Find(binary, binarySize).Get<uint8_t>();
	...
}
```

## Docs

Docs can be found [here](https://localcc.github.io/LightningScanner/).