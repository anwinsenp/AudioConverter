#include "directory.h"
#include <dirent.h>

Directory::Directory()
{
}

std::vector<std::string> Directory::entries(const std::string &directory,
                                            const std::vector<std::string> &filters)
{
    DIR *dir = opendir(directory.c_str());
    dirent *entry;
    std::vector<std::string> entries;
    while ((entry = readdir(dir))) {
        bool isIgnored = false;
        std::string entryName = entry->d_name;
        for(unsigned int i=0; i<filters.size(); i++)
            if(entryName.compare(filters[i]) == 0) {
                isIgnored = true;
                break;
            }

        if(!isIgnored)
            entries.push_back(entry->d_name);
    }

    closedir(dir);
    return entries;
}
