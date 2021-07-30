#ifndef TLIB_LIST_H
#define TLIB_LIST_H

#include <initializer_list>
#include <iterator>
#include <stdexcept>

namespace tlib {

template <typename T> class List {
public:
  struct ListItem {
    T m_data;
    ListItem *m_prev;
    ListItem *m_next;

    // Default constructor
    ListItem() : m_data(T()), m_prev(nullptr), m_next(nullptr) {}
    // Value constructor
    ListItem(const T &p_val)
        : m_data(p_val), m_prev(nullptr), m_next(nullptr) {}

    // Copy constructor
    ListItem(const ListItem &p_other) = delete;
    // Copy assignment
    ListItem &operator=(const ListItem &p_other) = delete;
    // Move constructor
    ListItem(ListItem &&p_move_src)
        : m_data(std::move(p_move_src.m_data)), m_prev(p_move_src.m_prev),
          m_next(p_move_src.m_next) {
      p_move_src.m_prev = p_move_src.m_next = nullptr;
    }
    // Move assignment
    ListItem &operator=(ListItem &&p_move_src) {
      if (this != &p_move_src) {
        m_data = std::move(p_move_src.m_data);
        m_prev = p_move_src.m_prev;
        m_next = p_move_src.m_next;

        p_move_src.m_next = p_move_src.m_prev = nullptr;
      }
      return *this;
    }

    ~ListItem() {}
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

    reference operator*() { return m_ptr->m_data; }
    const_reference operator*() const { return m_ptr->m_data; }
    pointer operator->() { return &(m_ptr->m_data); }
    const_pointer operator->() const { return &(m_ptr->m_data); }
    ListIterator &operator++() {
      m_ptr = m_ptr->m_next;
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

private:
  std::size_t m_size;
  item *m_head;
  item *m_tail;

public:
  // Construct/copy/destroy
  List() : m_size(0), m_head(nullptr), m_tail(nullptr) {}
  List(std::size_t sz) : m_size(sz) {
    auto it = m_head = new item();
    while (--sz) {
      it->m_next = new item();
      it->m_next->m_prev = it;
      it = it->m_next;
    }
    m_tail = it;
  }
  List(std::size_t sz, const T &val) : m_size(sz) {
    auto it = m_head = new item(val);
    while (--sz) {
      it->m_next = new item(val);
      it->m_next->m_prev = it;
      it = it->m_next;
    }
    m_tail = it;
  }

  List(std::initializer_list<T> lst) : m_size(lst.size()) {
    auto il_iter = lst.begin();
    auto it = m_head = new item(*il_iter);
    while (++il_iter != lst.end()) {
      it->m_next = new item(*il_iter);
      it->m_next->m_prev = it;
      it = it->m_next;
    }
    m_tail = it;
  }

  // Copy constructor
  List(const List &lst) : m_size(0) {
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
  List(List &&lst)
      : m_size(lst.m_size), m_head(lst.m_head), m_tail(lst.m_tail) {
    lst.m_size = 0;
    lst.m_head = lst.m_tail = nullptr;
  }
  // Move assignment
  List &operator=(List &&lst) { return List(lst); }

  ~List() { erase(); }

  // Capacity
  inline bool empty() const noexcept { return m_size == 0; }
  std::size_t size() const noexcept { return m_size; }

  // Element access
  T &at(std::size_t p_i) {
    if (p_i > m_size)
      throw std::out_of_range("Out of range");

    if (p_i > (m_size / 2)) {
      auto it = m_tail;
      while (++p_i < m_size) {
        it = it->m_prev;
      }
      return it->m_data;
    } else {
      auto it = m_head;
      while (p_i--) {
        it = it->m_next;
      }
      return it->m_data;
    }
  };

  T &front() { return m_head->m_data; }

  T &back() { return m_tail->m_data; }

  // Modifiers
  void clear();
  void insert();
  void erase() {
    while (m_size != 0) {
      pop_back();
    }
  }

  void push_back(const T &val) {
    if (m_size == 0) {
      m_head = m_tail = new item(val);
    } else {
      m_tail->m_next = new item(val);
      m_tail->m_next->m_prev = m_tail;
      m_tail = m_tail->m_next;
    }
    ++m_size;
  }

  void pop_back() {
    if (m_size == 0)
      throw std::out_of_range("Empty list");
    if (m_size == 1) {
      delete m_tail;
      m_head = m_tail = nullptr;
    } else {
      auto tmp = m_tail->m_prev;
      delete m_tail;
      m_tail = tmp;
    }
    --m_size;
  }

  void push_front(const T &val) {
    if (m_head == nullptr) {
      m_head = m_tail = new item(val);
    } else {
      m_head->m_prev = new item(val);
      m_head->m_prev->m_next = m_head;
      m_head = m_head->m_prev;
    }
    ++m_size;
  }

  void pop_front() {
    if (m_size == 0)
      throw std::out_of_range("Empty list");
    if (m_size == 1) {
      delete m_head;
      m_head = m_tail = nullptr;
    } else {
      auto tmp = m_head->m_next;
      delete m_head;
      m_head = tmp;
    }
    --m_size;
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

  iterator begin() { return iterator(m_head); }
  iterator begin() const { return iterator(m_head); }
  iterator end() { return iterator(nullptr); }
  iterator end() const { return iterator(nullptr); }
};

} // namespace tlib

#endif // TLIB_LIST_H
