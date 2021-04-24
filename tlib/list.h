#ifndef TLIB_LIST_H
#define TLIB_LIST_H

#include <cstddef>
#include <initializer_list>
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
    ListItem(const T &val, ListItem *prev, ListItem *next)
        : data{new T{val}}, prev(prev), next(next) {}

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

  // Construct/copy/destroy
  List() : _size(0), head(nullptr), tail(nullptr) {}
  List(std::size_t sz) : _size(sz) {
    auto it = head = new ListItem();
    while (--sz) {
      it->next = new ListItem();
      it->next->prev = it;
      it = it->next;
    }
    tail = it;
  }

  List(std::initializer_list<T> lst) : _size(lst.size()) {
    auto il_iter = lst.begin();
    auto it = head = new ListItem(*il_iter);
    while (++il_iter != lst.end()) {
      it->next = new ListItem(*il_iter);
      it->next->prev = it;
      it = it->next;
    }
    tail = it;
  }

  // Copy constructor TODO
  List(const List &lst) : _size(lst.size()) {}

  // Copy assignment

  // Move constructor
  // Move assignment

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
    if (tail == nullptr) {
      head = tail = new ListItem(val);
    } else {
      tail->next = new ListItem(val);
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
      head = tail = new ListItem(val);
    } else {
      head->prev = new ListItem(val);
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
  void resize(std::size_t newsz);
  void swap(List other);

private:
  std::size_t _size;
  ListItem *head;
  ListItem *tail;
};

} // namespace tlib

#endif // TLIB_LIST_H
