#include <iostream>

#include "common.h"
#include "LinuxSoundInterface.h"
#include "TCPListener.h"

int main(int argc, char *argv[])
{
	UNUSED(argc);
	UNUSED(argv);

	//LinuxSoundInterface *lsi = new LinuxSoundInterface(); 
	//lsi->volumeSetValue(85);
	
	while(1)
	{
		TCPListener *listener = new TCPListener("192.168.1.13", "1337");
		listener->loop();
		//listener->~TCPListener();
	}

	return 0;
}
