#ifndef MP3ENCODER_H
#define MP3ENCODER_H

#include "encoder.h"

#include <string>

class MP3Encoder : virtual public Encoder
{
public:
    MP3Encoder();

    bool encode(const std::string &inputFilename,
                const std::string &outputFilename);
    bool encode(const std::string &inputFilename,
                const std::string &outputFilename,
                const Settings &settings); // recommended quality good

private:
    static const int pcmSize = 4096;
    static const int mp3Size = 4096;
};

#endif // MP3ENCODER_H
