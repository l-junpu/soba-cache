#ifndef SOBA_SERVER_H
#define SOBA_SERVER_H

#include <atomic>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "Cache.h"

#pragma comment(lib, "Ws2_32.lib")

namespace soba
{
	class TcpServer
	{
	public:

		using HandleUserRequest = void(*)(SOCKET ClientSocket);

		TcpServer(HandleUserRequest requestHandler);

		// Accept Client Connections & Create a Thread for each of them
		bool InitializeAndAcceptConnections(Cache* cache);

		// Operate and Listen to Inputs
		void Run();

	private:

		// Initialize Windows Sockets DLL
		bool InitializeWSAStartup();

		// Create Server Socket
		bool CreateServerSocket();

		// Listen to Connections
		bool ListenToConnections();

		

	private:

		// need a fn ptr here to point to my controller's redis class

		addrinfo*        m_Socket;
		SOCKET           m_ServerSocket;
		std::atomic_bool m_ActiveServer;


		HandleUserRequest m_HandleUserRequest;
	};
}

#endif