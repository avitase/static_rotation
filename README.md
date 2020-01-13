# `static_rotation`
`static_rotation` is a [header-only](static_rotation.hpp) library that uses template meta programming to generate all rotations of a given integer sequence at compile-time. 

## Example
The snippet below generates all rotations of the sequence `(0,1,2,3)` and stores them in a `std::array<std::size_t, 16>`:
```
#include "static_rotation.hpp"
#include <iostream>

int main() {
    using namespace static_rotation;
    using R = IndexRotations<4>;
    constexpr auto values = R::values;

    for (int i = 0; i < values.size(); i++) {
        std::cout << values[i];
        std::cout << (i % R::seq_length  == R::seq_length - 1 ? '\n' : ' ');
    }

}
```
The output of this snippet is
```
0 1 2 3
1 2 3 0
2 3 0 1
3 0 1 2
```
You can run the snippet on Compiler Explorer: [godbolt.org/z/uNmXFr](https://godbolt.org/z/uNmXFr)

`IndexRotations<N>` generates the rotations for an index sequence `(0, 1, 2, ..., N)`. If you need the rotations for arbitrary sequences you may use `Rotations` directly, e.g.
```
Rotations<int, 4, 8, 15, 16, 23, 42>;
```
see [godbolt.org/z/fWeikA](https://godbolt.org/z/fWeikA) for a complete example.
For more details and a richer documentation take a look at [static_rotation.hpp](static_rotation.hpp).

## Installatation
This library is header-only and including [static_rotation.hpp](static_rotation.hpp) is sufficient.

## Requirements
The library uses `C++17` features. No external libraries are needed.
