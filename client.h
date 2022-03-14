#pragma once
#include <SFML/Network.hpp>
class client
{public:
	sf::IpAddress getIP();
	void setIP(sf::IpAddress ip);
	unsigned short getPort();
	void setPort(unsigned short prt);
	int  getconnstatus();
	void setconnstatus(int conn);
	bool getcolor();
	void setcolor(bool white);
	
	sf::Packet pack;
private:
	sf::IpAddress IP;
	unsigned short port;
	int connectionstatus;
	bool iswhite;
};

