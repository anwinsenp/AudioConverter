#ifndef ENCODER_H
#define ENCODER_H

#include <string>

/// Reference https://github.com/zyfu0000/lameHelper

struct Settings;
class Encoder
{
public:
    enum Mode
    {
            EMABR,
            EMCBR,
            EMVBR
    };

    enum Channels
    {
            ECMONO,
            ECSTEREO
    };

    enum Bitrate
    {
            BR8kbps = 8,
            BR16kbps = 16,
            BR24kbps = 24,
            BR32kbps = 32,
            BR40kbps = 40,
            BR48kbps = 48,
            BR56kbps = 56,
            BR64kbps = 64,
            BR80kbps = 80,
            BR96kbps = 96,
            BR112kbps = 112,
            BR128kbps = 128,
            BR144kbps = 144,
            BR160kbps = 160,
            BR192kbps = 192,
            BR224kbps = 224,
            BR256kbps = 256,
            BR320kbps = 320
    };

    enum Samplerate
    {
            SR8khz = 8000,
            SR11khz = 11025,
            SR12khz = 12000,
            SR16khz = 16000,
            SR22khz = 22050,
            SR24khz = 24000,
            SR32khz = 32000,
            SR44khz = 44100,
            SR48khz = 48000
    };

    virtual bool encode(const std::string &inputFilename,
                        const std::string &outputFilename) = 0;
    virtual bool encode(const std::string &inputFilename,
                        const std::string &outputFilename,
                        const Settings &settings) = 0;
};

struct Settings{
        Encoder::Channels channels;
        Encoder::Bitrate abrBitrate;
        Encoder::Bitrate cbrBitrate;
        int quality;
        Encoder::Mode mode;
        Encoder::Samplerate resampleFrequency;
        Encoder::Samplerate inSamplerate;

        //The constructor; used to set default values
        Settings();
};

#endif // ENCODER_H
