#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <vector>
#include <string>

class Directory
{
public:
    Directory();

    static std::vector<std::string> entries(
            const std::string &directory,
            const std::vector<std::string> &filters
            = std::vector<std::string>());
};

#endif // DIRECTORY_H
