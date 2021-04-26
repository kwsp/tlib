#ifndef TLIB_LIST_H
#define TLIB_LIST_H

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

namespace tlib {

template <typename T> class List {
public:
  struct ListItem {
    T *data;
    ListItem *prev;
    ListItem *next;

    ListItem() : data(new T{}), prev(nullptr), next(nullptr) {}
    ListItem(const T &val) : data(new T{val}), prev(nullptr), next(nullptr) {}

    // Copy constructor
    ListItem(const ListItem &v) = delete;
    // Copy assignment
    ListItem &operator=(const ListItem &v) = delete;
    // Move constructor
    ListItem(ListItem &&v) : data(data), prev(prev), next(next) {
      v.data = nullptr;
    }
    // Move assignment
    ListItem &operator=(ListItem &&v) { return ListItem{v}; }

    ~ListItem() { delete data; }
  };

  struct ListIterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;

    ListIterator(ListItem *ptr) : m_ptr(ptr){};

    reference operator*() { return *(m_ptr->data); }
    const_reference operator*() const { return *(m_ptr->data); }
    pointer operator->() { return m_ptr->data; }
    const_pointer operator->() const { return m_ptr->data; }
    ListIterator &operator++() {
      m_ptr = m_ptr->next;
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator==(const ListIterator x, const ListIterator y) {
      return x.m_ptr == y.m_ptr;
    }
    friend bool operator!=(const ListIterator x, const ListIterator y) {
      return x.m_ptr != y.m_ptr;
    }

  private:
    ListItem *m_ptr;
  };

  using item = ListItem;
  using iterator = ListIterator;

  // Construct/copy/destroy
  List() : _size(0), head(nullptr), tail(nullptr) {}
  List(std::size_t sz) : _size(sz) {
    auto it = head = new item();
    while (--sz) {
      it->next = new item();
      it->next->prev = it;
      it = it->next;
    }
    tail = it;
  }
  List(std::size_t sz, const T &val) : _size(sz) {
    auto it = head = new item(val);
    while (--sz) {
      it->next = new item(val);
      it->next->prev = it;
      it = it->next;
    }
    tail = it;
  }

  List(std::initializer_list<T> lst) : _size(lst.size()) {
    auto il_iter = lst.begin();
    auto it = head = new item(*il_iter);
    while (++il_iter != lst.end()) {
      it->next = new item(*il_iter);
      it->next->prev = it;
      it = it->next;
    }
    tail = it;
  }

  // Copy constructor
  List(const List &lst) : _size(0) {
    for (const auto &v : lst) {
      push_back(v);
    }
  }

  // Copy assignment
  List &operator=(const List &lst) {
    erase();
    for (const auto &v : lst) {
      push_back(v);
    }
    return *this;
  }

  // Move constructor
  List(List &&lst) : _size(lst._size), head(lst.head), tail(lst.tail) {
    lst._size = 0;
    lst.head = lst.tail = nullptr;
  }
  // Move assignment
  List &operator=(List &&lst) { return List(lst); }

  ~List() { erase(); }

  // Capacity
  inline bool empty() const noexcept { return _size == 0; }
  std::size_t size() const noexcept { return _size; }

  // Element access
  T &at(std::size_t n) {
    if (n > _size)
      throw std::out_of_range("Out of range");
    if (n > (_size / 2)) {
      auto it = tail;
      while (++n < _size) {
        it = it->prev;
      }
      return *(it->data);
    } else {
      auto it = head;
      while (n--) {
        it = it->next;
      }
      return *(it->data);
    }
  };

  T &front() { return *(head->data); }

  T &back() { return *(tail->data); }

  // Modifiers
  void clear();
  void insert();
  void erase() {
    while (_size != 0) {
      pop_back();
    }
  }

  void push_back(const T &val) {
    if (_size == 0) {
      head = tail = new item(val);
    } else {
      tail->next = new item(val);
      tail->next->prev = tail;
      tail = tail->next;
    }
    ++_size;
  }

  void pop_back() {
    if (_size == 0)
      throw std::out_of_range("Empty list");
    if (_size == 1) {
      delete tail;
      head = tail = nullptr;
    } else {
      auto tmp = tail->prev;
      delete tail;
      tail = tmp;
    }
    --_size;
  }

  void push_front(const T &val) {
    if (head == nullptr) {
      head = tail = new item(val);
    } else {
      head->prev = new item(val);
      head->prev->next = head;
      head = head->prev;
    }
    ++_size;
  }

  void pop_front() {
    if (_size == 0)
      throw std::out_of_range("Empty list");
    if (_size == 1) {
      delete head;
      head = tail = nullptr;
    } else {
      auto tmp = head->next;
      delete head;
      head = tmp;
    }
    --_size;
  }

  void resize(std::size_t newsz) {
    if (newsz < 0)
      return;
    if (newsz > size()) {
      while (newsz != size())
        push_back(T{});
    } else if (newsz < size()) {
      while (newsz != size())
        pop_back();
    }
  };
  void swap(List other);

  iterator begin() { return iterator(head); }
  iterator begin() const { return iterator(head); }
  iterator end() { return iterator(nullptr); }
  iterator end() const { return iterator(nullptr); }

private:
  std::size_t _size;
  item *head;
  item *tail;
};

} // namespace tlib

#endif // TLIB_LIST_H
