#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <bcm2835.h>
#include <string.h>


#include "EtherBerry.h"


EtherBerry  ETHB;
bool EtherBerryInit=false;

int main()
{         

    char str1[80];    
    unsigned char counter = 0;  
    
    //---- initialize the EtherBerry board -----

    if (ETHB.Init() == true) {
        printf("Etherberry v1.6  inizialized\n");
        EtherBerryInit=true;
    } else {                            
        printf("inizialization failed\n");        // the EtherBerry board was not recognized
    }            

    if (!EtherBerryInit) exit(1);                                                   

    system("aplay ../casiers.wav","r");

    pclose(handle);

    while (1)
    {

	ETHB.BufferIn.Cust.sound3_status = counter++;
	printf("counter :%d\n",counter);

        if (EtherBerryInit){
           ETHB.MainTask();            // execute the EtherBerry task
	}
        
	usleep(100000);                                         // delay of 100mS
    }
 
}

