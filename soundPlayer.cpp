#include <iostream>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include "soundPlayer.hpp"


using namespace boost::process;
using namespace boost::filesystem;

using namespace std;


soundPlayer::soundPlayer(uint8_t channelNbIn){
    aplayPath = boost::process::search_path("aplay");
    channelNb = channelNbIn;
}

void soundPlayer::play(boost::filesystem::path soundFile, bool playInLoop) {
    if ( launched == false ) { 
        sound = soundFile;
        string channelArg = str(boost::format("-Dsound%d") % static_cast<int>(channelNb + 1));
        player = boost::process::child(aplayPath, channelArg, soundFile);
        loop = playInLoop;
        launched = true;   
    }
}


void soundPlayer::stop(){
    if( player != NULL) {
        player.terminate();
    }
    launched = false;
}

bool soundPlayer::isRunning(){
    if(player != NULL){
        return player.running();
    } else {
        return false;
    }
}

bool soundPlayer::isLaunched(){
    return launched;
}

void soundPlayer::worker() {
    if (launched == true) {
        if( isRunning() != true ){
            if( loop ) {
                launched = false;
                play(sound, loop);
            } else {
                player.wait();
            }
        }
    }
}

