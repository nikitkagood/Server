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

//Json in C++ example
//json j2 = {
//  {"pi", 3.141},
//  {"happy", true},
//  {"name", "Niels"},
//  {"nothing", nullptr},
//  {"answer", {
//	{"everything", 42}
//  }},
//  {"list", {1, 0, 2}},
//  {"object", {
//	{"currency", "USD"},
//	{"value", 42.99}
//  }}
//};

class CustomClient : public olc::net::client_interface<Commands>
{
public:
	//void PingServer()	
	//{
	//	olc::net::message<CustomMsgTypes> msg;
	//	msg.header.id = CustomMsgTypes::ServerPing;

	//	// Caution with this...
	//	std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();		

	//	msg << timeNow;
	//	Send(msg);
	//}

	//void MessageAll()
	//{
	//	olc::net::message<CustomMsgTypes> msg;
	//	msg.header.id = CustomMsgTypes::MessageAll;		
	//	SendJson(msg);
	//}

	void Authorize()
	{
		json j
		{
			{"command", "Authorize"},
			{"data", {"name", "PlayerName"}}
		};
		SendJson(j);
	}

	void send_state() 
	{
		//asio::ip::tcp::socket socket();
		shared_ptr<asio::ip::tcp::socket> socket_ptr;

		string state;
		//socket_ptr->write_some(state);
		//socket_ptr->read_some(state);
	}

	//TcpPlayer::send_state() 
	//{
	//	tcp_socket->write(state: String)
	//		tcp_socket->read(state: String)
	//}

	void bet(int ammount)
	{
		//10 is minimal bet
		json j{ 
			{"command", "OK"}, 
			{"data", {"bet", ammount} }
		};
		SendJson(j);
	}

	void insurance()
	{
		bool decision = false;
		//CheckDescinion
		json j{ 
			{"command", "OK"}, 
			{"data" , {"insurance", decision} }
		};
		SendJson(j);
	}

	void GameDecision()
	{
		//Hit, Stand, Double
		string decision;
		json j{ 
			{"command", "OK"}, 
			{"data", { "action", decision }} 
		};
		SendJson(j);
	}

	//void to_json(json& j, const CustomMsgTypes& msg) {
	//	//j = json{ {"name", p.name}, {"address", p.address}, {"age", p.age} };
	//	j = json{ "command", "Authorize", "data" {"name", "PlayerName"} };

	//}

	//void from_json(const json& j, person& p) {
	//	j.at("name").get_to(p.name);
	//	j.at("address").get_to(p.address);
	//	j.at("age").get_to(p.age);
	//}
};

int main()
{
	SetConsoleTitle(L"Blackjack by Nikita Belov");
	setlocale(0, "");

	CustomClient c;
	c.Connect("127.0.0.1", 8005);

	c.Authorize();

	//Server:
	//{
	//	"command": "OK",
	//		"data" : {
	//		"name": "PlayerName",
	//			"id" : "UniqueId", (Guid ? )
	//			"Bank" : 1000
	//	}
	//}
	//Or:
	//{
	//	"command": "Error",
	//		"data" : {
	//		"description": "desc"
	//	}
	//}
	//c.send_state();
	//Server: send to client cout << Player list ?
	//Server:
	//{
	//	"command": "Bet", // Валидация, что выйгрыш может быть выключен
	//		"timeout" : 600,
	//		"data" : {
	//		"min": 10,
	//			"max" : 100
	//	}
	//}
	//c.bet(20);
	//Server gives the cards

	//Server (optional):
	//{
	//	"command": "Insurance", //Игра проверит достаточно ли средств для страховки
	//		"data" : { }
	//}
	//c.insurance();
	//Server
	//Hit, Stand, Double
	//{
	//	"command": "RequestAction",
	//	"data" : { }
	//}
	//Server give card





	bool bQuit = false;
	while (!bQuit)
	{
		if (c.IsConnected())
		{
			//if (!c.Incoming().empty())
			//{
			//	//auto msg = c.Incoming().pop_front().msg;
			//	//auto msg = c.Incoming().pop_front().msg;

			//	////switch (msg.header.id)
			//	//Commands command;
			//	//switch (command)
			//	//{
			//	//case Commands::Authorize:
			//	//{
			//	//	// Server has responded to a ping request				
			//	//	std::cout << "Server Accepted Connection\n";
			//	//}
			//	//break;
			//	//}


			//}
		}
		else
		{
			std::cout << "Server Down\n";
			bQuit = true;
		}

	}

	return 0;
}