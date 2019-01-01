#include "directory.h"
#include <dirent.h>

Directory::Directory()
{
}

std::vector<std::string> Directory::entries(char *directory)
{
    DIR *dir = opendir(directory);
    dirent *entry;
    std::vector<std::string> entries;
    while ((entry = readdir(dir)))
        entries.push_back(entry->d_name);

    closedir(dir);
    return entries;
}
