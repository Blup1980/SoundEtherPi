#ifndef SOUNDMIXER_H
#define SOUNDMIXER_H

#define PLAYERCOUNT 5

#include <boost/format.hpp>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>

class soundMixer
{
    public:

    soundMixer(uint8_t playerNb);

    void setVolume(uint8_t volumeLeftIn, uint8_t volumeRightIn);

    private:
    uint8_t volume[2];
    uint8_t playerNb;
    boost::process::child amixer;
    boost::filesystem::path amixerPath;
};

#endif
