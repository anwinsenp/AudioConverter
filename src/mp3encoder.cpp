#include "mp3encoder.h"

#include <iostream>
#include <lame.h>

class String
{
public:
    String(const std::string &str) :
        m_str(str)
    {}

    bool endsWith(const std::string &endStr)
    {
        if(endStr.length() < m_str.length())
            return (m_str.compare(m_str.length() - endStr.length(),
                                  endStr.length(), endStr) == 0);
        return false;
    }

private:
    std::string m_str;
};

Settings::Settings()
{
    channels = Encoder::ECSTEREO;
    abrBitrate = Encoder::BR128kbps;
    cbrBitrate = Encoder::BR128kbps;
    quality = 2;
    mode = Encoder::EMCBR;
    resampleFrequency = Encoder::SR44khz;
    inSamplerate = Encoder::SR44khz;
}

MP3Encoder::MP3Encoder()
{
}

bool MP3Encoder::encode(const std::string &inputFilename,
                        const std::string &outputFilename)
{
    Settings settings;
    return this->encode(inputFilename, outputFilename, settings);
}

bool MP3Encoder::encode(const std::string &inputFilename,
                        const std::string &outputFilename,
                        const Settings &settings)
{

    String input(inputFilename);
    String output(outputFilename);
    if(!input.endsWith(".wav") || !output.endsWith(".mp3"))
        return false;

    std::cout << "======= Encoding " << inputFilename << " to "
              << outputFilename << std::endl << "-" << std::endl;

    lame_global_flags*	globalFlags = nullptr;
    globalFlags = lame_init();
    lame_set_in_samplerate(globalFlags, settings.inSamplerate);
    lame_set_mode(globalFlags, JOINT_STEREO);
    lame_set_num_channels(globalFlags, 2);

    //VbrTag
    lame_set_bWriteVbrTag(globalFlags, 1);
    lame_set_VBR(globalFlags, vbr_off);

    lame_set_quality(globalFlags, settings.quality);
    lame_set_brate(globalFlags, settings.cbrBitrate);
    lame_set_out_samplerate(globalFlags, settings.resampleFrequency);
    lame_set_findReplayGain(globalFlags, 1);

    if(lame_init_params(globalFlags) == -1)
    {
        std::cout << "FATAL ERROR: parameters failed to initialize properly in lame. Aborting!" << std::endl;
        return false;
    }
    else
    {
        int read = 0;
        int write = 0;
        long pcmTotalSize = 0;
        long cumulativeRead = 0;

        FILE *pcm = fopen(inputFilename.c_str(), "rb");
        FILE *mp3 = fopen(outputFilename.c_str(), "wb");

        if(pcm == nullptr)
        {
            std::cout << "FATAL ERROR: file '%s' can't be open for read. Aborting!" << std::endl;
            return false;
        }

        fseek(pcm, 0, SEEK_END);
        pcmTotalSize = ftell(pcm);
        fseek(pcm, 0, SEEK_SET);

        if(mp3 == nullptr)
        {
            std::cout << "FATAL ERROR: file '%s' can't be open for write. Aborting!" << std::endl;
            return false;
        }

        unsigned char* buffer = new unsigned char[LAME_MAXMP3BUFFER];
        short int pcmBuffer[pcmSize*2];
        unsigned char mp3Buffer[mp3Size];


        long audio_pos=ftell(mp3); //store beginning of audio data
        do
        {
            read = fread(pcmBuffer, 2 * sizeof(short int), pcmSize, pcm);
            cumulativeRead += (long)read * 2 * sizeof(short int);
            if(read == 0)
            {
                write = lame_encode_flush(globalFlags, mp3Buffer, mp3Size);
            }
            else
            {
                write = lame_encode_buffer_interleaved(globalFlags, pcmBuffer, read, mp3Buffer, mp3Size);
            }
            fwrite(mp3Buffer, write, sizeof(char), mp3);

        }while(read != 0);

        delete [] buffer;
        fclose(mp3);
        fclose(pcm);
        lame_close(globalFlags);
        std::cout << "Encoding Completed!" << std::endl;
        return true;
    }
}
