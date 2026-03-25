#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


using boost::asio::ip::tcp;

int main() {
	boost::asio::io_context io;

tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 8080));

std::cout << "Server started on port 8080....." << std::endl;


std::vector<json> orders;
int orderID = 1;


while (true) {
	tcp::socket socket(io);

acceptor.accept(socket);

char data[1024];
size_t length = socket.read_some(boost::asio::buffer(data));

std::string received(data, length);


json order = json::parse(received);
order["status"] = "Preparing now";

orders.push_back(order);


std::cout << "\n ====================== \n";
std::cout << " New Order #" << orderID << "\n ";
std::cout << "\n ====================== \n";

std::cout << "Item : " << order["item"].get<std::string>() << std::endl;
std::cout << "Quantity : " << order["quantity"] << std::endl;
std::cout << "Status: " << order["status"] << std::endl;

std::cout << "\nAll Orders:\n";
for (const auto& o : orders) {
	std::cout << "-  " << o["item"].get<std::string>()  << " x" << o["quantity"] << "(" << o["status"] << ")" << std::endl;
}

std::cout << std::endl;
orderID++;

std::string response = " Order received. Status: Preparing "; 
boost::asio::write(socket, boost::asio::buffer(response));


}
return 0;

}
