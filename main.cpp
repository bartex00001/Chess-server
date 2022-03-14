#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <windows.h>
#include "client.h"
int main()
{	/*
	int connectionstatus = 0;
	sf::Packet initpacket;
	sf::UdpSocket socket1;
	unsigned int receivingport = 57000;
	unsigned short senderport;
	sf::IpAddress senderip;
	if (socket1.bind(receivingport) != sf::Socket::Done) {
		std::cout << "Failed to bind a socket!" << std::endl;
		exit(4);
	}
	if (socket1.receive(initpacket, senderip, senderport) != sf::Socket::Done) {
		std::cout << "Failed to recieve initialization packet!" << std::endl;
		exit(2);
	}
	initpacket >> connectionstatus;
	std::cout << connectionstatus << std::endl;
	std::cout << senderip<<"||"<<senderport<<std::endl;
	if (connectionstatus == 1) {
		connectionstatus = 2;
		initpacket.clear();
		initpacket << connectionstatus;
		if (socket1.send(initpacket, senderip, senderport) != sf::Socket::Done) {
			std::cout << "Failed to send connection initialization packet!" << std::endl;
			exit(2);
		}
	}
	system("pause"); */


	client c1, c2;
	sf::UdpSocket socket;
	const unsigned short receivingport = 57000;
	unsigned short senderport;
	sf::IpAddress senderip;
	int connection=0; //0 brak 4obaj

	if (socket.bind(receivingport) != sf::Socket::Done) {
		std::cout << "Failed to bind a socket!" << std::endl;
		exit(4);
	}

	if (socket.receive(c1.pack,senderip,senderport) != sf::Socket::Done) {
		std::cout << "Failed to recieve initialization packet 1!" << std::endl;
		exit(2);
	}
	c1.pack >> connection;
	if (connection == 1) {
		c1.setIP(senderip);
		c1.setPort(senderport);
		c1.setconnstatus(2);
		c1.setcolor(true);
		c1.pack.clear();
		c1.pack << c1.getconnstatus() << c1.getcolor();
		if (socket.send(c1.pack, c1.getIP(), c1.getPort()) != sf::Socket::Done) {
			std::cout << "Failed to send initialization packet 1!" << std::endl;
			exit(2);
		}
		c1.pack.clear();
		connection = 0;
		std::cout << "Connected to client 1" << std::endl;
	}

	if (socket.receive(c2.pack, senderip, senderport) != sf::Socket::Done) {
		std::cout << "Failed to recieve initialization packet 2!" << std::endl;
		exit(2);
	}
	c2.pack >> connection;
	if (connection == 1) {
		c2.setIP(senderip);
		c2.setPort(senderport);
		c2.setconnstatus(2);
		c2.setcolor(false);
		c2.pack.clear();
		c2.pack << c2.getconnstatus()<<c2.getcolor();
		if (socket.send(c2.pack, c2.getIP(), c2.getPort()) != sf::Socket::Done) {
			std::cout << "Failed to send initialization packet 2!" << std::endl;
			exit(2);
		}
		connection = 4;
		std::cout << "Connected to client 2" << std::endl;
	}



	bool move = true;
	c1.pack << move;
	if (socket.send(c1.pack, c1.getIP(), c1.getPort()) != sf::Socket::Done) {
		std::cout << "nigger!" << std::endl;
	}
	c1.pack.clear();
	if (socket.receive(c1.pack, senderip, senderport) != sf::Socket::Done) {
		std::cout << "niggerrr!" << std::endl;
	}
	unsigned short a=0;
	float b=0, c=0;
	c1.pack >> a>>b>>c;
	std::cout << a << b << c;
	c1.pack.clear();
	c1.pack << move;
	if (socket.send(c1.pack, c1.getIP(), c1.getPort()) != sf::Socket::Done) {
		std::cout << "nigger2!" << std::endl;
	}


	/*
	sf::SocketSelector selec;
	selec.add(socket);

	while (true) {
		
		if (selec.wait()) {
			if (selec.isReady(socket)) {

			}
		}
		

	}//while
	*/

	return 0;
}