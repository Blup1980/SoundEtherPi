#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include<boost/process.hpp>
#include<boost/filesystem.hpp>

class soundPlayer
{
    public:

    soundPlayer();

    void play(boost::filesystem::path soundFile, bool playInLoop);
    void stop();
    bool isRunning();
    void worker();
    bool hasNeverPlayed();

    private:
    boost::filesystem::path sound;
    boost::process::child player;
    bool launched = false;
    bool loop = false;
    boost::filesystem::path aplayPath;
};

#endif
