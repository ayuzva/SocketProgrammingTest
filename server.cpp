#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <cassert>
#include <tchar.h>
#include <string>

#define PORT 8080
using namespace std;


void server(void) {
	
	int server_fd, new_socket, valread,err;
	const char opt = (char)1;//optval parameter should point to nonzero int
	struct sockaddr_in address; //formatting for address
	char buffer[1024] = { 0 }; //
	int addrlen = sizeof(address);
	WSADATA wsaData;
	string hello = "Hello from server";
	string message;

	cout << "Server started" << endl;

	WSAStartup(MAKEWORD(2,2),&wsaData);//should also be in client if ran on different computers probably

	//configure IPV4, TCP, on port 0
	if ((server_fd = socket(AF_INET,SOCK_STREAM,0)) == 0) {
		cout << "socket failed" << endl;
	}

	//sets socket options
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
		err = WSAGetLastError();
		cout << "setsockopt failed" << endl;
	}

	InetPton(AF_INET, _T("169.168.0.2"), &address.sin_addr.s_addr);//convert ip from string to binary representation

	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);

	//associating local address with socket
	if (bind(server_fd, (struct sockaddr*) & address, sizeof(address)) < 0) {
		cout << "binding failed" << endl;
	}

	//server waits fo client to make connection. 2nd parameter is the number of pending connections in the queue
	if (listen(server_fd, 3) < 0) {
		cout << "listen failed" << endl;
	}

	//permit incoming connection to the socket. extracts first connection of queue
	if ((new_socket = accept(server_fd,(struct sockaddr*)&address,&addrlen)) < 0) {
		cout << "accept failed" << endl;
	}

	/*//used to read incoming data
	valread = recv(new_socket, buffer, 1024, 0);//equivalent to read()
	cout << buffer << endl;
	send(new_socket,&hello[0],sizeof(hello),0);*/
	
	while(message != "q") {//to quit
		getline(cin, message);
		send(new_socket, &message[0], sizeof(message), 0);
		//used to read incoming data
		valread = recv(new_socket, buffer, 1024, 0);//equivalent to read()
		cout << buffer << endl;
	}
	return;
}