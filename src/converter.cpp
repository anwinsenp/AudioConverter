#include "converter.h"
#include "mp3encoder.h"
#include "directory.h"

#include <pthread.h>
#include <iostream>

#include <sys/utsname.h>

#ifdef _WIN32
#include <sysinfoapi.h>
#else
#include <unistd.h>
#endif

unsigned int numCPUs()
{
    int numCPU = 4;
#ifdef _WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    numCPU = sysinfo.dwNumberOfProcessors;
#else
    numCPU = sysconf(_SC_NPROCESSORS_ONLN);
#endif
    return numCPU;
}

struct ThreadData {
    ThreadData() :
        encoder(nullptr)
    {}

    MP3Encoder *encoder;
    std::string outputFilename;
    std::string inputFilename;
    int quality;
    bool isEncoded;
    char Padding[3];
};

void *encode(void *data) {
    ThreadData *thData = static_cast<ThreadData*>(data);
    if(thData->encoder)
        thData->isEncoded = thData->encoder->encode(
                    thData->inputFilename,
                    thData->outputFilename);
}

Converter::Converter()
{
}

int Converter::convertToMP3(const std::string &path)
{
    std::vector<std::string> filters;
    filters.push_back(".");
    filters.push_back("..");
    std::vector<std::string> entries = Directory::entries(path, filters);

    std::vector<ThreadData*> threadDatas;
    unsigned int threadCount = numCPUs();
    std::vector<pthread_t> threads;

    while(entries.size()) {
        if(threads.size() < threadCount) {
            std::string inputFilename = entries.back();
            entries.pop_back();
            std::string outputFilename;
            if(inputFilename.size() > 4)
                outputFilename = inputFilename.substr(
                            0, inputFilename.size()-4) + ".mp3";
            else
                outputFilename = inputFilename + "out.mp3";

            ThreadData *data = new ThreadData;
            data->encoder = new MP3Encoder;
            data->isEncoded = false;
            data->inputFilename = path + '/' + inputFilename;
            data->outputFilename = path + '/' + outputFilename;
            data->quality = 2;
            threadDatas.push_back(data);
            pthread_t thread;
            int ret = pthread_create(&thread, nullptr, encode, static_cast<void*>(data));
            if(ret)
                std::cerr << "Erro Pthread creation return code: " << ret << std::endl;
            else
                threads.push_back(thread);

        } else {
            for(unsigned int i=0; i<threads.size(); i++)
                pthread_join(threads[i], nullptr);

            threads.clear();
        }
    }

    for(unsigned int i=0; i<threads.size(); i++)
        pthread_join(threads[i], nullptr);

    threads.clear();

    int converted = 0;
    while(threadDatas.size()) {
        ThreadData *data = threadDatas.back();
        if(data->encoder)
            delete data->encoder;
        if(data->isEncoded)
            converted++;
        threadDatas.pop_back();
    }

    return converted;
}
