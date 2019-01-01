#include "converter.h"

#include <iostream>

int main(int argc, char *argv[])
{
    std::string errorMessage = "Please provide a direcotry with valid wav files!";
    if(argc < 2) {
        std::cerr << errorMessage << std::endl;
        return 0;
    }

    Converter converter;
    int converted = converter.convertToMP3(argv[1]);
    if(!converted)
        std::cout << errorMessage << std::endl;
    else
        std::cout << "Converted " << converted << " wav files to MP3" << std::endl;

    return 0;
}
