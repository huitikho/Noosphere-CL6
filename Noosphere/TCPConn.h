#ifndef TCPCONN_H
#define TCPCONN_H
#include <windows.h>
#include <iostream>
#include <vector>
#include <map>
#include "Converter.h"

#include <string.h>

using namespace std;

#define TCP_MSG_BUFF_SIZE 1024

class TCPConn
{
public:

	char* msg = new char[10000];

	TCPConn(const char* ip, int port)
	{
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		m_sockAddr.sin_family = AF_INET;
		m_sockAddr.sin_addr.s_addr = inet_addr(ip);
		m_sockAddr.sin_port = htons(port);

		if ((m_sktHandle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		{
			//close(m_sktHandle);
			WSACleanup();
			cout << "[ERROR]: TCP Socket Init Failure" << endl;
			exit(1);
		}

		if (connect(m_sktHandle, (struct sockaddr*)&m_sockAddr, sizeof(m_sockAddr)) < 0)
		{
			//close(m_sktHandle);
			WSACleanup();
			cout << "[ERROR]: TCP Socket Connection Failure: " << ip << " " << port << " " << WSAGetLastError() << endl;
			exit(1);
		}
		//cout << "TCP Socket Init Done !" << endl;
	}

	string Receive(short& len)
	{
		int byteSize = TCP_MSG_BUFF_SIZE;
		
		byteSize = recv(m_sktHandle, msg, byteSize, 0);
		
		//			cout << "byteSize " << len << endl;

		if (byteSize < 0)
		{
			cout << "[ERROR]: TCP Socket Recv Error: " << WSAGetLastError() << endl;
			exit(1);
		}

		return msg;
	}

}

