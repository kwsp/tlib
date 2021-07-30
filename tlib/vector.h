#ifndef TLIB_VECTOR_H
#define TLIB_VECTOR_H

#include <initializer_list>
#include <stdexcept>

#include "tlib/iterator.h"

#define _MIN_SZ 8

namespace tlib {

template <typename T> class Vector {
private:
  T *m_buf;   // pointer to first element
  T *m_space; // pointer to first unused element
  T *m_last;  // pointer to last slot (one past allocated space)

public:
  using Iterator = SequenceIterator<T>;

  // Default constructor
  Vector() : Vector(_MIN_SZ) { m_space = m_buf; }

  // Size constructor
  Vector(std::size_t p_sz) {
    m_buf = new T[p_sz];
    m_space = m_last = m_buf + p_sz;
  }

  // Default value constructor
  Vector(std::size_t p_sz, const T &p_val) {
    m_buf = new T[p_sz];
    m_space = m_buf;
    m_last = m_buf + p_sz;
    for (auto i = 0; i < p_sz; ++i) {
      *m_space = p_val;
      ++m_space;
    }
  };

  // Initializer list
  Vector(std::initializer_list<T> p_lst) {
    m_buf = new T[p_lst.size()];
    m_space = m_buf;
    m_last = m_buf + p_lst.size();
    for (const T &val : p_lst) {
      *m_space = val;
      ++m_space;
    }
  };

  // Copy constructor
  Vector(const Vector &p_copy_src) {
    m_buf = new T[p_copy_src.size()];
    m_space = m_buf;
    m_last = m_buf + p_copy_src.size();
    for (auto i = 0; i < p_copy_src.size(); i++) {
      *m_space = p_copy_src[i];
      ++m_space;
    }
  };

  // Copy assignment
  Vector &operator=(const Vector &p_copy_src) {
    if (this != &p_copy_src) {
      if (m_buf)
        delete[] m_buf;
      m_buf = new T[p_copy_src.size()];
      m_space = m_buf;
      m_last = m_buf + p_copy_src.size();
      for (int i = 0; i < p_copy_src.size(); i++) {
        *m_space = p_copy_src[i];
        ++m_space;
      }
    }
    return *this;
  }

  // Move constructor
  Vector(Vector &&v) : m_buf(v.m_buf), m_space(v.m_space), m_last(v.m_last) {
    v.m_buf = v.m_space = v.m_last = nullptr;
  }

  // Move assignment
  Vector &operator=(Vector &&p_move_src) {
    if (this != &p_move_src) {
      if (m_buf)
        delete[] m_buf;

      m_buf = p_move_src.m_buf;
      m_space = p_move_src.m_space;
      m_last = p_move_src.m_last;

      p_move_src.m_buf = p_move_src.m_space = p_move_src.m_last = nullptr;
    }
    return *this;
  }

  // Destructor
  ~Vector() { delete[] m_buf; };

  // Capacity
  inline bool empty() const noexcept { return size() == 0; }

  std::size_t size() const noexcept { return m_space - m_buf; }

  std::size_t capacity() const noexcept { return m_last - m_buf; }

  void resize(std::size_t p_sz) {
    reserve(p_sz);
    m_space = m_buf + p_sz;
  }

  void reserve(std::size_t p_sz) { // Increase capacity to newsz
    if (p_sz > capacity()) {
      auto *new_buf = new T[p_sz];
      for (int i = 0; i < size(); i++)
        new_buf[i] = m_buf[i];
      m_space = new_buf + size();
      m_last = new_buf + p_sz;
      delete[] m_buf;
      m_buf = new_buf;
    }
  }

  void shrink_to_fit() {
    if (capacity() > size())
      resize(size());
  };

  // Element access
  T &operator[](std::size_t p_i) {
    if (p_i < size())
      return m_buf[p_i];
    throw std::out_of_range("Out of range");
  }
  const T &operator[](std::size_t p_i) const {
    if (p_i < size())
      return m_buf[p_i];
    throw std::out_of_range("Out of range");
  }
  T &at(std::size_t p_i) { return operator[](p_i); }
  const T &at(std::size_t p_i) const { return operator[](p_i); }

  T &front() {
    if (empty())
      throw std::out_of_range("Empty");
    return *m_buf;
  }

  T &back() {
    if (empty())
      throw std::out_of_range("Empty");
    return *(m_space - 1);
  }

  // Modifiers
  void push_back(const T &el) {
    if (size() + 1 > capacity()) {
      reserve(size() == 0 ? _MIN_SZ : size() * 2);
    }
    new (m_space) T{el};
    m_space++;
  }

  void pop_back() {
    if (empty())
      throw std::out_of_range("Empty");
    m_space--;
  }

  T *data() const { return m_buf; }

  // Iterator
  Iterator begin() { return Iterator(m_buf); }
  // Iterator begin() const { return Iterator(elem); }
  Iterator end() { return Iterator(m_space); }
  // Iterator end() const { return Iterator(space); }
};

} // namespace tlib

#endif // TLIB_VECTOR_H
