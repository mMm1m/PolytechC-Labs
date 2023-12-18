#include <iostream>
#include <fstream>
#include <string>
#include "GetFunctions.h"
#include "Commands_S3.h"
#include "Messages.h"

namespace golchanskiy
{
    std::ostream& printEmpty(std::ostream& out)
    {
        out << "<Empty>" << std::endl;
        return out;
    }
    std::ostream& printInvalidCommand(std::ostream& out)
    {
        out << "<Invalid>" << std::endl;
        return out;
    }
}
int main(int argc, char** argv)
{
    if (argc == 1)
    {
        std::cerr << "No file to read" << std::endl;
        return 1;
    }
    std::ifstream fin(argv[1]);
    if (!fin.good())
    {
        std::cerr << "Unable to read the file" << std::endl;
        return 1;
    }
    try
    {
        auto lists = golchanskiy::getLists(fin);
        fin.close();
        while (!std::cin.eof())
        {
            auto words = golchanskiy::getWords(std::cin, '\n');
            if (words.isEmpty())
                continue;
            auto word_ = words.begin();
            std::string command = *(words.begin()++);
            try {
                if ((command == "print") && (words.getSize() == 2))
                    golchanskiy::print(std::cout, *words.begin(), lists);
                else if ((command == "replace") && (words.getSize() == 4))
                {
                    std::string dest = *(words.begin()++);
                    long long first = std::stoll(*(words.begin()++));
                    if (std::isdigit(words.begin()->front()))
                    {
                        long long second = std::stoll(*words.begin());
                        golchanskiy::replace(dest, first, second, lists);
                    }
                    else
                    {
                        std::string secondName = *words.begin();
                        golchanskiy::replace(dest, first, secondName, lists);
                    }
                }
                else if ((command == "remove") && (words.getSize() == 3))
                {
                    std::string dest = *(words.begin()++);
                    if (std::isdigit(words.begin()->front()))
                    {
                        long long elem = std::stoll(*words.begin());
                        golchanskiy::remove(dest, elem, lists);
                    }
                    else
                    {
                        std::string listName = *words.begin();
                        golchanskiy::remove(dest, listName, lists);
                    }
                }
                else if ((command == "concat") && (words.getSize() > 3))
                {
                    std::string name = *(words.begin()++);
                    auto begin = words.begin();
                    words.erase(begin, word_);
                    lists.push(name, golchanskiy::concat(words, lists));
                }
                else if ((command == "equal") && (words.getSize() > 2))
                {
                    words.popFront();
                    if (golchanskiy::equal(words, lists))
                        golchanskiy::printTrue(std::cout);
                    else
                        golchanskiy::printFalse(std::cout);
                }
                else
                    throw std::invalid_argument("Unknown command");
            }
            catch (const std::invalid_argument &)
            {
                golchanskiy::printInvalidCommand(std::cout);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 2;
    }
    return 0;
}

