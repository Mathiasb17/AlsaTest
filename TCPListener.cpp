#include "TCPListener.h"

//==================================================================================================== 
//==================================================================================================== 
//==================================================================================================== 
TCPListener::TCPListener(std::string inet_addr, std::string inet_port):
	m_inetAddr(inet_addr),
	m_inetPort(inet_port)
{
	_init();
}

//==================================================================================================== 
//==================================================================================================== 
//==================================================================================================== 
TCPListener::~TCPListener ()
{
	_end();
}

//==================================================================================================== 
//==================================================================================================== 
//==================================================================================================== 
void TCPListener::_init()
{
	m_lsi = new LinuxSoundInterface();

	m_servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&m_servAddr, 0, sizeof(m_servAddr));  
	m_servAddr.sin_family = AF_INET; //IPV4
	m_servAddr.sin_addr.s_addr = inet_addr(m_inetAddr.c_str());
	m_servAddr.sin_port = htons(std::stoi(m_inetPort));

	bind(m_servSock, (struct sockaddr*)&m_servAddr, sizeof(m_servAddr));

	listen(m_servSock, 5);

	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size = sizeof(clnt_addr);

	m_clientSock = accept(m_servSock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
}

//==================================================================================================== 
//==================================================================================================== 
//==================================================================================================== 
void TCPListener::_end()
{
	delete m_lsi;
	memset(&m_servAddr, 0, sizeof(struct sockaddr_in));
	close(m_clientSock);
	close(m_servSock);
}

//==================================================================================================== 
//==================================================================================================== 
//==================================================================================================== 
void TCPListener::loop()
{
	while(true)
	{
		char buffer[TCP_MESSAGE_LEN];
		int strLen = recv(m_clientSock, buffer, TCP_MESSAGE_LEN, 0);

		std::string msg(buffer, strLen);

		int volume = 0;

		if (strLen > 0) 
		{
			sscanf(msg.c_str(), "VOLUME %d", &volume);
			std::cout << "volume change request : " << volume << std::endl;
			m_lsi->volumeSetValue(volume);
		}
		else //size 0 : client disconnected
		{
			std::cout << "client disconnected" << std::endl;
			break;
		}
	}
}
