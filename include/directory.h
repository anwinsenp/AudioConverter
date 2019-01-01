#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <vector>
#include <string>

class Directory
{
public:
    Directory();

    static std::vector<std::string> entries(char *directory);
};

#endif // DIRECTORY_H
