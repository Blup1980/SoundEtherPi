#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <bcm2835.h>
#include <string.h>
#include <boost/process.hpp>

#include "EtherBerry.h"

using namespace boost::process;
namespace bp = boost::process; 


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


    bp::child c(bp::search_path("aplay"), "~/sounds/casiers.wav");

    while( c.running() )
	printf("running\n");

    c.wait();
    printf("%d\n",c.exit_code());


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

