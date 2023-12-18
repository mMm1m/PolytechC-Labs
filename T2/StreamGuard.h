#ifndef T2_STREAMGUARD_H
#define T2_STREAMGUARD_H

#include <ios>

namespace golchanskiy {

  class StreamGuard {
    public:
    StreamGuard() = delete;

    StreamGuard(const StreamGuard&) = delete;

    explicit StreamGuard(std::basic_ios< char >& s);

    ~StreamGuard();

    private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };

}
#endif
