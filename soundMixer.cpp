#include <iostream>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>
#include "soundMixer.hpp"

using boost::format;
using namespace boost::process;
using namespace boost::filesystem;
using namespace std;


soundMixer::soundMixer(uint8_t nb){
    amixerPath = boost::process::search_path("amixer");
    playerNb = nb;
}


void soundMixer::setVolume(uint8_t volumeLeftIn, uint8_t volumeRightIn) {
    string cmdStr;
    if ((volume[0] != volumeLeftIn) || (volume[1] != volumeRightIn)) {
        volume[0] = volumeLeftIn;
        volume[1] = volumeRightIn;
        boost::format mixer_format("-c 1 cset iface=MIXER,name='sound%1%' %2%,%3%");
        cmdStr = boost::str(mixer_format % (playerNb + 1) % static_cast<int>(volumeLeftIn) % static_cast<int>(volumeRightIn)); 
	amixer = boost::process::child(amixerPath, cmdStr);
        cout << cmdStr << "\n";
        while (amixer.running());
        amixer.wait();
    }
}

