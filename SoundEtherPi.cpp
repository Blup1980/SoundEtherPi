#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <bcm2835.h>
#include <string.h>
#include <boost/process.hpp>

#include "EtherBerry.h"
#include "soundPlayer.hpp"
#include "soundMixer.hpp"


#define STATUS_PLAYING 0x01
#define STATUS_LAUNCHED 0x02

#define CMD_PLAY       0x01
#define CMD_LOOP       0x02

#define SOUND_CHANNELS 5

using namespace boost::process;
namespace bp = boost::process; 

EtherBerry  ETHB;
bool EtherBerryInit=false;


boost::filesystem::path toFileName( uint16_t soundNb )
{
    boost::filesystem::path soundPath("/home/pi/sounds/" + std::to_string(soundNb) + ".wav");
    return soundPath ;
}


int main()
{       
    soundPlayer* players[SOUND_CHANNELS];
    soundMixer* mixers[SOUND_CHANNELS];


    uint8_t *statusPtr[SOUND_CHANNELS];
    uint8_t *cmdPtr[SOUND_CHANNELS];
    uint16_t *soundNbPtr[SOUND_CHANNELS];
    uint8_t *volumeLeft[SOUND_CHANNELS];
    uint8_t *volumeRight[SOUND_CHANNELS];

    
    for (uint8_t i=0; i<SOUND_CHANNELS ; i++) {
        players[i] = new soundPlayer(i);
        mixers[i] = new soundMixer(i);
    }

    statusPtr[0] = &ETHB.BufferIn.Cust.sound1_status;
    statusPtr[1] = &ETHB.BufferIn.Cust.sound2_status;
    statusPtr[2] = &ETHB.BufferIn.Cust.sound3_status;
    statusPtr[3] = &ETHB.BufferIn.Cust.sound4_status;
    statusPtr[4] = &ETHB.BufferIn.Cust.sound5_status;
    
    cmdPtr[0] = &ETHB.BufferOut.Cust.sound1_cmd; 
    cmdPtr[1] = &ETHB.BufferOut.Cust.sound2_cmd; 
    cmdPtr[2] = &ETHB.BufferOut.Cust.sound3_cmd; 
    cmdPtr[3] = &ETHB.BufferOut.Cust.sound4_cmd; 
    cmdPtr[4] = &ETHB.BufferOut.Cust.sound5_cmd; 

    volumeLeft[0] = &ETHB.BufferOut.Cust.sound1_left_volume;
    volumeLeft[1] = &ETHB.BufferOut.Cust.sound2_left_volume;
    volumeLeft[2] = &ETHB.BufferOut.Cust.sound3_left_volume;
    volumeLeft[3] = &ETHB.BufferOut.Cust.sound4_left_volume;
    volumeLeft[4] = &ETHB.BufferOut.Cust.sound5_left_volume;

    volumeRight[0] = &ETHB.BufferOut.Cust.sound1_right_volume;
    volumeRight[1] = &ETHB.BufferOut.Cust.sound2_right_volume;
    volumeRight[2] = &ETHB.BufferOut.Cust.sound3_right_volume;
    volumeRight[3] = &ETHB.BufferOut.Cust.sound4_right_volume;
    volumeRight[4] = &ETHB.BufferOut.Cust.sound5_right_volume;

    soundNbPtr[0] = &ETHB.BufferOut.Cust.sound1_nb;
    soundNbPtr[1] = &ETHB.BufferOut.Cust.sound2_nb;
    soundNbPtr[2] = &ETHB.BufferOut.Cust.sound3_nb;
    soundNbPtr[3] = &ETHB.BufferOut.Cust.sound4_nb;
    soundNbPtr[4] = &ETHB.BufferOut.Cust.sound5_nb;

    //---- initialize the EtherBerry board -----

    if (ETHB.Init() == true) {
        printf("Etherberry v1.6  inizialized\n");
        EtherBerryInit=true;
    } else {                            
        printf("inizialization failed\n");        // the EtherBerry board was not recognized
    }            

    if (!EtherBerryInit) exit(1);                                                   


    while (1)
    {
        for( uint8_t i=0; i < SOUND_CHANNELS; i++) {
            mixers[i]->setVolume(*volumeLeft[i], *volumeRight[i]);
            players[i]->worker();
            if (players[i]->isRunning() )
                *statusPtr[i] |= STATUS_PLAYING;
            else
                *statusPtr[i] &= ~STATUS_PLAYING;

            
            if (players[i]->isLaunched() )
                *statusPtr[i] |= STATUS_LAUNCHED;
            else
                *statusPtr[i] &= ~STATUS_LAUNCHED;

            // printf("command %d = %d\n",i,*cmdPtr[i]);

            if (*cmdPtr[i] & CMD_PLAY) {
                // printf("requested to play ptr %u \n",i);
                players[i]->play( toFileName(*soundNbPtr[i]), *cmdPtr[i] & CMD_LOOP );
              
            } else {
                players[i]->stop();   
            }
        }


        if (EtherBerryInit){
           ETHB.MainTask();
        }
        
        usleep(100000);
    }
 
}

