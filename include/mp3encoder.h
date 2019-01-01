#ifndef MP3ENCODER_H
#define MP3ENCODER_H

#include <string>

class MP3Encoder
{
public:
    MP3Encoder();

    void encode(bool &isEncoded,
                const std::string &inputFilename,
                const std::string &outputFilename,
                int quality = 2); // recommended quality good
};

#endif // MP3ENCODER_H
