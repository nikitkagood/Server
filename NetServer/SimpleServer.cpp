#include <iostream>
#include <olc_net.h>
//#include <nlohmann/json.hpp>

using namespace std;

//enum class CustomMsgTypes : uint32_t
//{
//	ServerAccept,
//	ServerDeny,
//	ServerPing,
//	MessageAll,
//	ServerMessage,
//};

enum class Commands : uint32_t
{
	Authorize,
	ServerDeny,
	OK,
	PlayerList,
	MessageAll,
	ServerMessage,
};

class CustomServer : public olc::net::server_interface<Commands>
{
public:
	CustomServer(uint16_t nPort) : olc::net::server_interface<Commands>(nPort)
	{

	}

protected:
	virtual bool OnClientConnect(std::shared_ptr<olc::net::connection<Commands>> client)
	{
		//olc::net::message<Commands> msg;
		//msg.header.id = Commands::ServerAccept;
		//client->Send(msg);
		return true;
	}

	// Called when a client appears to have disconnected
	virtual void OnClientDisconnect(std::shared_ptr<olc::net::connection<Commands>> client)
	{
		std::cout << "Removing client [" << client->GetID() << "]\n";
	}

	// Called when a message arrives
	virtual void OnMessage(std::shared_ptr<olc::net::connection<Commands>> client, olc::net::message<Commands>& msg)
	{
		//switch (msg.header.id)
		//{
		//case CustomMsgTypes::ServerPing:
		//{
			//std::cout << "[" << client->GetID() << "]: Server Ping\n";

			//// Simply bounce message back to client
			//client->Send(msg);
		//}
		//break;

		//case CustomMsgTypes::MessageAll:
		//{
			//std::cout << "[" << client->GetID() << "]: Message All\n";

			// Construct a new message and send it to all clients
			//olc::net::message<CustomMsgTypes> msg;
			//msg.header.id = CustomMsgTypes::ServerMessage;
			//msg << client->GetID();
			//MessageAll(msg, client);
		//}
		//break;
		//}
	}
};

int main()
{
	CustomServer server(8005); 
	server.Start();

	while (1)
	{
		server.Update(-1, true);
	}
	


	return 0;
}