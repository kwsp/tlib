#ifndef TLIB_VECTOR_H
#define TLIB_VECTOR_H

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>

#define _MIN_SZ 8

namespace tlib {

template <typename T> class Vector {
public:
  // Construct/copy/destroy
  Vector(std::size_t sz) : elem(new T[sz]) { space = last = elem + sz; }
  Vector() : Vector(_MIN_SZ) { space = elem; }
  Vector(std::size_t sz, const T &val) : elem(new T[sz]) {
    space = elem;
    last = elem + sz;
    for (auto i = 0; i < sz; ++i) {
      new (space) T{val};
      ++space;
    }
  };

  Vector(std::initializer_list<T> lst) : elem(new T[lst.size()]) {
    space = elem;
    last = elem + lst.size();
    for (const T &val : lst) {
      new (space) T{val};
      ++space;
    }
  };

  // Copy constructor
  Vector(const Vector &v) : elem(new T[v.size()]) {
    space = elem;
    last = elem + v.size();
    for (int i = 0; i < v.size(); i++) {
      new (space) T{v[i]};
      ++space;
    }
  };

  // Copy assignment
  Vector &operator=(const Vector &v) {
    auto *ptr = new T[v.size()];
    space = ptr;
    for (int i = 0; i < v.size(); i++) {
      new (space) T{v[i]};
      ++space;
    }
    delete[] elem;
    elem = ptr;
    last = space;
    return *this;
  }

  // Move constructor
  Vector(Vector &&v) : elem(v.elem), space(v.space), last(v.last) {
    v.elem = v.space = v.last = nullptr;
  }

  // Move assignment
  Vector &operator=(Vector &&v) { return Vector(v); }

  ~Vector() { delete[] elem; };

  // Capacity
  bool empty() const noexcept { return size() == 0; }
  std::size_t size() const noexcept { return space - elem; }
  std::size_t capacity() const noexcept { return last - elem; }
  void resize(std::size_t sz) {
    reserve(sz);
    space = elem + sz;
  }

  void reserve(std::size_t newsz) { // Increase capacity to sz
    if (newsz > capacity()) {
      auto *new_ptr = new T[newsz];
      for (int i = 0; i < size(); i++)
        new_ptr[i] = elem[i];
      space = new_ptr + size();
      last = new_ptr + newsz;
      delete[] elem;
      elem = new_ptr;
    }
  }

  void shrink_to_fit() {
    if (capacity() > size()) {
      resize(size());
    }
  };

  // Element access
  T &at(std::size_t n) {
    if (n > size())
      throw std::out_of_range("Out of range");
    return elem[n];
  }
  const T &at(std::size_t n) const {
    if (n > size())
      throw std::out_of_range("Out of range");
    return elem[n];
  }

  T &operator[](std::size_t n) { return at(n); }
  const T &operator[](std::size_t n) const { return at(n); }
  T &front() {
    if (empty())
      throw std::out_of_range("Empty");

    return *elem;
  }
  T &back() {
    if (empty())
      throw std::out_of_range("Empty");

    return *(space - 1);
  }

  // Modifiers
  void push_back(const T &el) {
    if (size() + 1 > capacity()) {
      reserve(size() == 0 ? _MIN_SZ : size() * 2);
    }
    new (space) T{el};
    space++;
  }
  void pop_back() { space--; }

  T *data() const { return elem; }

private:
  T *elem;  // pointer to first element
  T *space; // pointer to first unused element
  T *last;  // pointer to last slot (one past allocated space)
};

template <typename T> class VectorIterator {
public:
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using iterator_category = std::input_iterator_tag;

  VectorIterator() {}
  VectorIterator(Vector<T> v);

private:
};

} // namespace tlib

#endif // TLIB_VECTOR_H
