#include "Messages.h"

namespace golchanskiy
{
    std::ostream& printTrue(std::ostream& out)
    {
        out << "<TRUE>" << std::endl;
        return out;
    }
    std::ostream& printFalse(std::ostream& out)
    {
        out << "<FALSE>" << std::endl;
        return out;
    }
}

