#include "ute_hashmap.hpp"
#include <iostream>
#include <cassert>

constexpr auto str_map = ute::hashmap<std::string_view, int, 3>({
    std::pair{"foo", 1},
    std::pair{"bar", 2},
    std::pair{"baz", 3},
});

constexpr auto int_map = ute::hashmap<int, const char*, 3>({
    std::pair{1, "one"},
    std::pair{2, "two"},
    std::pair{3, "three"},
});
namespace
{
constexpr void compile_time_tests() {
  static_assert(str_map.get("foo") && *str_map.get("foo") == 1);
  static_assert(str_map.get("bar") && *str_map.get("bar") == 2);
  static_assert(str_map.get("baz") && *str_map.get("baz") == 3);
  static_assert(!str_map.get("qux"));

  constexpr auto v1 = int_map.get(1);
  static_assert(v1 && std::string_view(*v1) == "one");
  constexpr auto v2 = int_map.get(2);
  static_assert(v2 && std::string_view(*v2) == "two");
  constexpr auto v3 = int_map.get(3);
  static_assert(v3 && std::string_view(*v3) == "three");
  static_assert(!int_map.get(4));
  static_assert(str_map.get("foo") && *str_map.get("foo") == 1);
  static_assert(str_map.get("bar") && *str_map.get("bar") == 2);
  static_assert(str_map.get("baz") && *str_map.get("baz") == 3);
  static_assert(!str_map.get("qux"));
  static_assert(!int_map.get(4));
}
}

int main() {
    compile_time_tests();

    // Runtime checks
    assert(int_map.get(1) && std::string_view(int_map.at(1)) == "one");
    assert(int_map.get(2) && std::string_view(int_map.at(2)) == "two");
    assert(int_map.get(3) && std::string_view(int_map.at(3)) == "three");

    std::cout << "All ute::hashmap tests passed!\n";
    return 0;
} 