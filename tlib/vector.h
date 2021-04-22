#ifndef TLIB_VECTOR_H
#define TLIB_VECTOR_H

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <exception>
#include <initializer_list>
#include <iostream>

#define _MIN_SZ 4

namespace tlib {

template <typename T> class Vector {
public:
  using size_type = std::size_t;
  using value_type = T;
  using const_reference = const T &;
  using reference = T &;
  using pointer = T *;

  // Construct/copy/destroy
  Vector(size_type sz) : sz(sz), cap(sz), elem(new value_type[sz]) {}
  Vector() : Vector(_MIN_SZ) { sz = 0; }
  Vector(size_type sz, const_reference v) : Vector(sz) {
    for (size_type i = 0; i < sz; i++) {
      elem[i] = v;
    }
  };

  Vector(std::initializer_list<value_type> lst)
      : elem(new value_type[lst.size()]), sz(lst.size()) {
    std::copy(lst.begin(), lst.end(), elem);
  };

  // Copy constructor
  Vector(const Vector &v)
      : sz(v.size()), cap(v.size()), elem(new value_type[v.size()]) {
    for (int i = 0; i < sz; i++) {
      elem[i] = v[i];
    }
  };

  // Move constructor
  Vector(Vector &&v) : sz(v.size()), cap(v.size()) {
    elem = v.elem;
    v.elem = nullptr;
  }

  // Copy assignment
  Vector &operator=(const Vector &v) { return Vector(v); }

  // Move assignment
  Vector &operator=(Vector &&v) { return Vector(v); }

  ~Vector() { delete[] elem; };

  // Capacity
  bool empty() const noexcept { return size() == 0; }
  size_type size() const noexcept { return sz; }
  size_type capacity() const noexcept { return cap; }
  void resize(size_type sz) {
    reserve(sz);
    this->sz = sz;
  }
  void reserve(size_type sz) {
    if (sz > cap) {
      _resize(sz);
    }
  }
  void shrink_to_fit() {
    if (cap > sz) {
      _resize(sz);
    }
  };

  void _resize(size_type sz) {
    auto *new_ptr = new value_type[sz];
    std::copy(elem, elem + sz, new_ptr);
    delete[] elem;
    elem = new_ptr;
    cap = sz;
  }

  void _copy(value_type *from, value_type *to){

  };

  // Element access
  reference operator[](size_type n) { return elem[n]; }
  const_reference operator[](size_type n) const { return elem[n]; }
  reference front() {
    if (empty())
      throw "Empty";

    return elem[0];
  }
  reference back() {
    if (empty())
      throw "Empty";

    return elem[sz - 1];
  }

  // Modifiers
  void push_back(const_reference el) {
    if (sz + 1 >= cap) {
      reserve(cap * _factor);
    }
    elem[sz++] = el;
  }
  void pop_back() { sz--; }

  value_type *data() const { return elem; }

private:
  size_type sz;
  size_type cap;
  const size_type _factor = 2;

  value_type *elem;
};

} // namespace tlib

#endif // TLIB_VECTOR_H
