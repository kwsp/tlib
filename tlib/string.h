#ifndef TLIB_STRING_H
#define TLIB_STRING_H

#include <cstring>
#include <stdexcept>

namespace tlib {

class String {
private:
  char *m_buf;
  String() : m_buf(nullptr){}; // Private default constructor

public:
  // Constructor
  String(const char *p_src) {
    if (p_src) {
      m_buf = new char[std::strlen(p_src) + 1];
      std::strcpy(m_buf, p_src);
    } else
      m_buf = nullptr;
  };

  // Move constructor
  String(String &&p_move_src) {
    if (p_move_src.m_buf) {
      m_buf = p_move_src.m_buf;
      p_move_src.m_buf = nullptr;
    } else
      m_buf = nullptr;
  };

  // Move assignment operator
  String &operator=(String &&p_move_src) {
    if (this != &p_move_src && p_move_src.m_buf) {
      if (m_buf)
        delete[] m_buf; // free own buf

      m_buf = p_move_src.m_buf;   // move resource
      p_move_src.m_buf = nullptr; // free source
    }
    return *this;
  }

  // Copy constructor
  String(const String &p_copy_src) {
    if (p_copy_src.m_buf) {
      m_buf = new char[std::strlen(p_copy_src.m_buf) + 1];
      std::strcpy(m_buf, p_copy_src.m_buf);
    } else
      m_buf = nullptr;
  }

  // Copy assignment operator
  String &operator=(const String &p_copy_src) {
    if (this != &p_copy_src && p_copy_src.m_buf) {
      if (m_buf)
        delete[] m_buf; // free own buffer

      m_buf = new char[std::strlen(p_copy_src.m_buf) + 1];
      std::strcpy(m_buf, p_copy_src.m_buf);
    }

    return *this;
  }

  // Destructor
  ~String() {
    if (m_buf)
      delete[] m_buf;
  }

  // Get size
  int size() const {
    if (m_buf)
      return std::strlen(m_buf);
    return 0;
  }

  // Casting operator
  operator const char *() { return m_buf; }

  // Equality
  bool operator==(const String &p_other) const {
    return std::strcmp(m_buf, p_other.m_buf) == 0;
  }
  bool operator!=(const String &p_other) const { return !operator==(p_other); }

  bool operator==(const char *p_cstr) const {
    return std::strcmp(m_buf, p_cstr) == 0;
  }
  bool operator!=(const char *p_cstr) const { return !operator==(p_cstr); }

  // Concatenation
  String operator+(const String &p_other) {
    String res;
    if (p_other.m_buf) {
      res.m_buf = new char[std::strlen(m_buf) + std::strlen(p_other.m_buf) + 1];
      std::strcpy(res.m_buf, m_buf);
      std::strcat(res.m_buf, p_other.m_buf);
    }

    return res;
  }

  // Subscript operator
  char &operator[](int i) {
    if (i < size()) {
      return m_buf[i];
    } else
      throw std::out_of_range("Out of range");
  }
};

} // namespace tlib

#endif // TLIB_STRING_H
