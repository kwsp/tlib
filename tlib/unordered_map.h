#ifndef TLIB_UNORDERED_MAP_H
#define TLIB_UNORDERED_MAP_H

#include <cstddef>
#include <functional>
#include <iterator>

namespace tlib {

template <typename Key, typename T, typename Hash = std::hash<Key>,
          typename Pred = std::equal_to<Key>>
class UnorderedMap {
public:
  struct iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using reference = T &;
    using pointer = T *;
  };

  // construct/move/copy
  UnorderedMap();
  UnorderedMap(const UnorderedMap &mp);
  UnorderedMap(UnorderedMap &&mp);
  UnorderedMap &operator=(const UnorderedMap &mp);
  UnorderedMap &operator=(UnorderedMap &&mp);
  ~UnorderedMap();

  // element access
  T &operator[](Key key);
  T &at(Key key);

  // modifiers
  void insert(Key key, T val);
  void erase(Key key);
  void clear();
  void swap(UnorderedMap &other);

  // lookup
  T find(Key key);
  int count(Key key) const;

  // capacity
  bool empty() const;
  std::size_t size() const;

  // bucket
  std::size_t bucket_count() const;
  std::size_t bucket_size(std::size_t n) const;

  // hash policy
  int load_factor();
  void rehash(std::size_t n_buckets);
  void reserve(std::size_t sz);

  // observers
  Hash hash_function();
  bool key_eq(Key k1, Key k2);

  // iterator
  iterator begin();
  iterator end();
};
} // namespace tlib
#endif
