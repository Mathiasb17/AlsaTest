#ifndef TCPLISTENER_H_OEEY6KSH
#define TCPLISTENER_H_OEEY6KSH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>
#include <string>

#include "LinuxSoundInterface.h"

#define TCP_MESSAGE_LEN 2048

class TCPListener
{
public:
	TCPListener(std::string inet_addr, std::string inet_port);
	virtual ~TCPListener ();

	void _init();
	void _end();

	void loop();

private:
	LinuxSoundInterface *m_lsi;

	std::string m_inetAddr;
	std::string m_inetPort;

	int m_servSock;
	int m_clientSock;

	struct sockaddr_in m_servAddr;
};

#endif /* end of include guard: TCPLISTENER_H_OEEY6KSH */
