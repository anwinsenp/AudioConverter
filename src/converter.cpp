#include "converter.h"
#include "mp3encoder.h"
#include "directory.h"

#include <pthread.h>
#include <iostream>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

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
    pthread_mutex_lock(&mutex1);
    ThreadData *thData = static_cast<ThreadData*>(data);
    if(thData->encoder)
        thData->encoder->encode(thData->isEncoded,
                                thData->inputFilename,
                                thData->outputFilename,
                                thData->quality);
    pthread_mutex_unlock(&mutex1);
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
    unsigned int threadCount = 4; // need to updated based on hardware concurrency
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
            data->inputFilename = inputFilename;
            data->outputFilename = outputFilename;
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
