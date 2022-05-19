#include "client.h"
sf::IpAddress client::getIP() {
	return(IP);
}

unsigned short client::getPort() {
	return(port);
}

void client::setIP(sf::IpAddress ip) {
	IP = ip;
}

void client::setPort(unsigned short prt) {
	port = prt;
}

void client::setconnstatus(int conn) {
	connectionstatus = conn;
}

int client::getconnstatus() {
	return(connectionstatus);
}

bool client::getcolor() {
	return(iswhite);
}

void client::setcolor(bool white) {
	iswhite = white;
}
