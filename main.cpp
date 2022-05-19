#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <windows.h>
#include "client.h"
int main()
{

	client c1, c2;
	sf::UdpSocket socket;
	const unsigned short receivingport = 57000;
	unsigned short senderport;
	sf::IpAddress senderip;
	int connection=0; //0 brak 4 obaj
	bool gamestarted = false;

	if (socket.bind(receivingport) != sf::Socket::Done) {
		std::cout << "Failed to bind a socket!" << std::endl;
		exit(4);
	}
	//klient 1
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

	//klient 2
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

	if (connection == 4) {
		gamestarted = true;
		c1.pack.clear();
		c1.pack << gamestarted;
		if (socket.send(c1.pack, c1.getIP(), c1.getPort()) != sf::Socket::Done) {
			std::cout << "Failed to send ready packet 1!" << std::endl;
			exit(2);
		}
		c1.pack.clear();

		c2.pack.clear();
		c2.pack << gamestarted;
		if (socket.send(c2.pack, c2.getIP(), c2.getPort()) != sf::Socket::Done) {
			std::cout << "Failed to send ready packet 2!" << std::endl;
			exit(2);
		}
		c2.pack.clear();
	}

	c1.pack.clear();
	if (socket.receive(c1.pack, senderip, senderport) != sf::Socket::Done) {
		std::cout << "Failed to recieve move from c1!" << std::endl;
		exit(2);
	}

	c1.pack.clear();
	c1.isMoveValue = true;
	c1.pack << c1.isMoveValue;
	if (socket.send(c1.pack, c1.getIP(), c1.getPort()) != sf::Socket::Done) {
		std::cout << "Failed to conf packet 1!" << std::endl;
		exit(2);
	}
	c1.pack.clear();



	c2.pack.clear();
	if (socket.receive(c2.pack, senderip, senderport) != sf::Socket::Done) {
		std::cout << "Failed to recieve move from c2!" << std::endl;
		exit(2);
	}
	int id = 0;
	float x = 0, y = 600;
	c2.pack << id << x << y;
	if (socket.send(c2.pack, c2.getIP(), c2.getPort()) != sf::Socket::Done) {
		std::cout << "Failed to move 2" << std::endl;
		exit(2);
	}
	c2.pack.clear();

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