#include<iostream>
#include<boost/process.hpp>
#include<boost/filesystem.hpp>
#include "soundPlayer.hpp"


using namespace boost::process;
using namespace boost::filesystem;

using namespace std;


soundPlayer::soundPlayer(){
    aplayPath = boost::process::search_path("aplay");
}

void soundPlayer::play(boost::filesystem::path soundFile, bool playInLoop) {
    if ( launched == false ) { 
        sound = soundFile;
        player = boost::process::child(aplayPath, sound);
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

