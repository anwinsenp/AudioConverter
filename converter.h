#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>

class Converter
{
public:
    Converter();

    int convertToMP3(const std::string &path);
};

#endif // CONVERTER_H
