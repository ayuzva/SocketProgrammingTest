#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <cassert>
#include <tchar.h>
#include <string>

#define PORT 8080
using namespace std;


void client(void) {
	int sock, valread;
	struct sockaddr_in serv_addr;
	string hello = "Hello from client";
	char buffer[1024] = { 0 };
	WSADATA wsaData;
	string message;

	cout << "Client started" << endl;
		
	WSAStartup(MAKEWORD(2, 2), &wsaData);//should also be in client if ran on different computers probably

	//configure IPV4, TCP, on port 0
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		cout << "socket failed: "<<sock<< endl;
	}

	InetPton(AF_INET,_T("169.168.0.2"), &serv_addr.sin_addr.s_addr);//convert ip from string to binary representation

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if (connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
		cout << "connection failed" << endl;
	}

	/*send(sock, &hello[0], sizeof(hello), 0);
	valread = recv(sock, buffer, 1024, 0);
	cout << buffer << endl;*/

	while (message != "q") {//to quit
		getline(cin, message);
		send(sock, &message[0], sizeof(message), 0);
		//used to read incoming data
		valread = recv(sock, buffer, 1024, 0);//equivalent to read()
		cout << buffer << endl;
	}
	return;
}
