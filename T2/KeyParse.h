#ifndef T2_KEYSPARSE_H
#define T2_KEYSPARSE_H

#include <string>

namespace golchanskiy {
  bool istreamSentry(std::istream&);
  bool ostreamSentry(std::ostream&);
  struct Delimeter_IO
  {
    char exp_;
  };

  struct String_IO
  {
    std::string& ref_;
    explicit String_IO(std::string&);
    explicit String_IO(const std::string&);
  };

  struct LL_IO
  {
    long long& ref_;
    LL_IO(long long& v);
    LL_IO(const long long& v);
  };

  struct ULL_IO
  {
    unsigned long long& ref_;
    explicit ULL_IO(unsigned long long&);
    explicit ULL_IO(const unsigned long long&);
  };

  std::istream& operator>>(std::istream&, Delimeter_IO&&);
  std::istream& operator>>(std::istream& in, LL_IO&& dest);
  std::istream& operator>>(std::istream&, String_IO&&);
  std::istream& operator>>(std::istream&, ULL_IO&&);
  std::ostream& operator<<(std::ostream& out, const LL_IO& source);
  std::ostream& operator<<(std::ostream&, const String_IO&);
  std::ostream& operator<<(std::ostream&, const ULL_IO&);
}

#endif
