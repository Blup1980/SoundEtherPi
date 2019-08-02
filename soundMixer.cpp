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
    string csetArg;
    string volArg;
    if ((volume[0] != volumeLeftIn) || (volume[1] != volumeRightIn)) {
        volume[0] = volumeLeftIn;
        volume[1] = volumeRightIn;
        csetArg = boost::str(boost::format("iface=MIXER,name='sound%1%'") % (playerNb + 1));
        volArg = boost::str(boost::format("%1%,%2%") % static_cast<int>(volumeLeftIn) % static_cast<int>(volumeRightIn));
        amixer = boost::process::child(amixerPath,"cset",csetArg,volArg);
        while (amixer.running());
        amixer.wait();
    }
}

