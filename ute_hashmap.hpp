#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string_view>
#include <type_traits>
#include <utility>
#include <stdexcept>

namespace ute
{

constexpr uint64_t
fnv1a (const std::string_view str) noexcept
{
  uint64_t hash = 14695981039346656037ULL;
  for (char const c : str)
    {
      hash = (hash ^ static_cast<uint64_t> (c))
             * static_cast<uint64_t> (1099511628211ULL);
    }
  return hash;
}

template <typename K>
constexpr uint64_t
hash_key (const K &key) noexcept
{
  if constexpr (std::is_integral_v<K>)
    {
      return static_cast<uint64_t> (key);
    }
  else if constexpr (std::is_same_v<K, std::string_view>)
    {
      return fnv1a (key);
    }
  else
    {
      static_assert (sizeof (K) == 0, "unsupported key type");

      std::unreachable ();
    }
}

template <typename K, typename V, std::size_t N> class hashmap
{
  struct entry
  {
    K key;
    V value;
    bool occupied = false;
  };

  std::array<entry, N> table{};

  static consteval std::size_t
  find_slot (const std::array<entry, N> &table, const K &key,
             const uint64_t hash)
  {
    for (std::size_t i = 0; i < N; ++i)
      {
        std::size_t idx = (hash + i) % N;
        if (!table[idx].occupied || table[idx].key == key)
          {
            return idx;
          }
      }
    return N; // Not found
  }

public:
  constexpr explicit hashmap (const std::array<std::pair<K, V>, N> &items)
  {
    for (const auto &[k, v] : items)
      {
        uint64_t h = hash_key (k);
        std::size_t idx = find_slot (table, k, h);
        if (idx == N)
          {
            throw std::runtime_error("Hashmap: Table full or duplicate key");
          }
        table[idx] = entry{ k, v, true };
      }
  }

  constexpr std::optional<V>
  get (const K &key) const noexcept
  {
    const uint64_t h = hash_key (key);
    for (std::size_t i = 0; i < N; ++i)
      {
        std::size_t idx = (h + i) % N;
        if (!table.at (idx).occupied)
          {
            return std::nullopt;
          }
        if (table.at (idx).key == key)
          {
            return table.at (idx).value;
          }
      }
    return std::nullopt;
  }

  constexpr const V &
  at (const K &key) const
  {
    auto v = get (key);
    if (!v)
      {
        throw std::out_of_range("Key not found");
      }
    return *v;
  }
};

} // namespace ct