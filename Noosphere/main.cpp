#include <iostream>
#include <time.h>

#include "TCPConn.h"

using namespace std;

int main()
{

	// Build up the TCP Connection //

	TCPConn* tcpConn = new TCPConn(IPAddress, Port);

	string msg;

	short len;

	// Retrieve the message for analyzing the traffic and intrusion detection

	msg = tcpConn->Receive(len);



}

