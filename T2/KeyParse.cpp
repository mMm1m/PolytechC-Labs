#include "KeyParse.h"
#include <iostream>
#include "StreamGuard.h"

bool golchanskiy::istreamSentry(std::istream& in)
{
  std::istream::sentry sentry(in);
  if (!sentry)
    return false;
  return true;
}

bool golchanskiy::ostreamSentry(std::ostream& out)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
    return false;
  return true;
}

std::istream& golchanskiy::operator>>(std::istream& in, Delimeter_IO&& data)
{
  if (!istreamSentry(in))
    return in;
  char c = '0';
  in >> c;
  if (in && (c != data.exp_))
    in.setstate(std::ios::failbit);
  return in;
}

std::istream& golchanskiy::operator>>(std::istream& in, String_IO&& data)
{
  if (!istreamSentry(in))
    return in;
  return std::getline(in >> Delimeter_IO{'"'}, data.ref_, '"');
}

std::istream& golchanskiy::operator>>(std::istream& in, ULL_IO&& data)
{
  if (!istreamSentry(in))
    return in;
  unsigned long long value = 0;
  in >> value;
  char x = in.get();
  if (x == 'u')
    in >> Delimeter_IO{'l'} >> Delimeter_IO{'l'};
  else if (x == 'U')
    in >> Delimeter_IO{'L'} >> Delimeter_IO{'L'};
  else
    return in;
  if (in)
    data.ref_ = value;
  return in;
}

std::istream& golchanskiy::operator>>(std::istream& in, LL_IO&& data)
{
  if (!istreamSentry(in))
    return in;
  long long input = 0;
  in >> input;
  char l = in.peek();
  if (l == 'l')
    in >> Delimeter_IO{'l'} >> Delimeter_IO{'l'};
  else if (l == 'L')
    in >> Delimeter_IO{'L'} >> Delimeter_IO{'L'};
  else
    in.setstate(std::ios::failbit);
  if (in)
    data.ref_ = input;
  return in;
}

std::ostream& golchanskiy::operator<<(std::ostream& out, const ULL_IO& data)
{
  if (!ostreamSentry(out))
    return out;
  golchanskiy::StreamGuard StreamGuard(out);
  out << data.ref_ << "ull";
  return out;
}

std::ostream& golchanskiy::operator<<(std::ostream& out, const String_IO& data)
{
  if (!ostreamSentry(out))
    return out;
  return out << '"' << data.ref_ << '"';
}

std::ostream& golchanskiy::operator<<(std::ostream& out, const LL_IO& data)
{
  if (!ostreamSentry(out))
    return out;
  golchanskiy::StreamGuard StreamGuard(out);
  out << "(:N " << data.ref_ << ":D " << data.ref_ << ":)";
  return out;
}

golchanskiy::String_IO::String_IO(std::string& s):
  ref_(s)
{}

golchanskiy::String_IO::String_IO(const std::string& s):
  ref_(const_cast< std::string& >(s))
{}

golchanskiy::ULL_IO::ULL_IO(unsigned long long int& s):
  ref_(s)
{}

golchanskiy::ULL_IO::ULL_IO(const unsigned long long int& s):
  ref_(const_cast< unsigned long long& >(s))
{}
