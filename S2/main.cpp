#include <iostream>
#include <fstream>
#include <string>
#include "Commands.h"
#include "getParts.h"
#include "Errors.h"

namespace golchanskiy
{
    std::ostream &printInvalidCommand(std::ostream &out)
    {
        return out << "<INVALID COMMAND>\n";
    };
}
int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::cerr << "Can't read file!\n" << std::endl;
        return 1;
    }
    std::ifstream in_stream(argv[1]);
    if (!in_stream.good())
    {
        std::cerr << "Unable to read the file!\n" << std::endl;
        return 1;
    }
    try
    {
        auto data = golchanskiy::getDicts(in_stream);
        in_stream.close();
        std::istream& in = std::cin;
        while (!in.eof())
        {
            try
            {
                auto words = golchanskiy::getWords(in, '\n');
                if (words.isEmpty())
                    continue;
                if (words.getSize() < 2)
                    throw std::invalid_argument("You need more args!\n");
                auto wordsIterator = words.cbegin();
                std::string command = *(wordsIterator++);
                std::string name = *(wordsIterator++);
                if (command == "print")
                {
                    golchanskiy::print(std::cout, name, data);
                    continue;
                }
                if (words.getSize() < 4)
                    throw std::invalid_argument("You need less args!\n");
                std::string lhs = *(wordsIterator++);
                std::string rhs = *wordsIterator;
                if (command == "complement")
                    data.push(name, golchanskiy::complement(lhs, rhs, data));
                else if (command == "intersect")
                    data.push(name, golchanskiy::intersect(lhs, rhs, data));
                else if (command == "union")
                    data.push(name, golchanskiy::unite(lhs, rhs, data));
                else
                    throw std::invalid_argument("Unknown command!\n");
            }
            catch (const std::invalid_argument&)
            {
                golchanskiy::printInvalidCommand(std::cout);
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 2;
    }
    return 0;
}

