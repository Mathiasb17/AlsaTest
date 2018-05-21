#include <wiringPi.h>
#include <pcf8591.h>
#include <stdio.h>
#include <cstdlib>

#include <cstdio>
#include <unistd.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <iostream>

#define address 0x48  		//pcf8591 default address
#define pinbase 64			//any number above 64
#define A0 pinbase + 0
#define A1 pinbase + 1
#define A2 pinbase + 2
#define A3 pinbase + 3

int main(void){
	int value;
	float voltage;
	wiringPiSetup();
	pcf8591Setup(pinbase,address);

	int old = 0;


	int sock;
	struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_port = htons(1337);
	inet_pton(AF_INET, "192.168.1.13", &server.sin_addr);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	connect(sock, (struct sockaddr *)&server, sizeof(struct sockaddr_in));

	while(1){
		value = analogRead(A0);  //read A0 pin
		analogWrite(pinbase+0,value);
		voltage = (float)value / 255.0 * 3.3;  // calculate voltage
		int percent = (int)(value/255.0 * 100.0);

		if(percent != old)
		{
			//printf("ADC value : %d  ,\tVoltage : %.2fV\n",value,voltage);

			std::string msg = "VOLUME "+ std::to_string(percent);

			std::cout << msg << std::endl;

			send(sock, msg.c_str(), msg.length(), 0);

			old = percent;
		}
		else
		{

		}

		//		system();
		delay(200);
	}

	close(sock);
}
