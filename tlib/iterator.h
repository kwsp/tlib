#ifndef TLIB_ITERATOR_H
#define TLIB_ITERATOR_H

#include <iterator>

namespace tlib {

template <typename T> struct SequenceIterator {
  using iterator_category = std::random_access_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;

  SequenceIterator(pointer ptr) : m_ptr(ptr){};

  reference operator*() { return *m_ptr; }
  pointer operator->() { return m_ptr; }
  SequenceIterator &operator++() {
    m_ptr++;
    return *this;
  }

  SequenceIterator operator++(int) {
    SequenceIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  friend bool operator==(const SequenceIterator x, const SequenceIterator y) {
    return x.m_ptr == y.m_ptr;
  }
  friend bool operator!=(const SequenceIterator x, const SequenceIterator y) {
    return x.m_ptr != y.m_ptr;
  }
  friend bool operator>(const SequenceIterator x, const SequenceIterator y) {
    return x.m_ptr > y.m_ptr;
  }
  friend bool operator>=(const SequenceIterator x, const SequenceIterator y) {
    return x.m_ptr >= y.m_ptr;
  }
  friend bool operator<(const SequenceIterator x, const SequenceIterator y) {
    return x.m_ptr < y.m_ptr;
  }
  friend bool operator<=(const SequenceIterator x, const SequenceIterator y) {
    return x.m_ptr <= y.m_ptr;
  }

private:
  pointer m_ptr;
};

} // namespace tlib
#endif // TLIB_ITERATOR_H
