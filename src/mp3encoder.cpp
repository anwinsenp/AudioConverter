#include "mp3encoder.h"

#include <iostream>

MP3Encoder::MP3Encoder()
{
}

void MP3Encoder::encode(bool &isEncoded,
                        const std::string &inputFilename,
                        const std::string &outputFilename,
                        int quality)
{

    std::cout << "======= Encoding " << inputFilename << " to "
              << outputFilename << std::endl << "-" << std::endl;
    isEncoded = true;
}
