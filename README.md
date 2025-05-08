this is a header-only, compile-time hashmap implementation using c++23 features. it supports string and integral keys, and is designed to be used in constexpr contexts.

## features

- header-only, no external dependencies
- compile-time construction and lookup
- supports string and integral keys
- throws at compile time if duplicate keys or table is full

## usage

include the header in your project:

```cpp
#include "include/ute_hashmap.hpp"
```

example:

```cpp
constexpr auto my_map = ute::hashmap<std::string_view, int, 3>({
    std::make_pair("foo", 1),
    std::make_pair("bar", 2),
    std::make_pair("baz", 3)
});

constexpr auto v = my_map.get("bar");
static_assert(v && *v == 2);
```

## building and testing

to build and run the tests, use cmake:

```sh
cmake -B build
cmake --build build
./build/test_ute_hashmap
``` 
