#include <iostream>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
using json=nlohmann::json;


using boost::asio::ip::tcp;

int main() {
	try {
		boost::asio::io_context io;
		tcp::socket socket(io);

		socket.connect(tcp::endpoint(boost::asio::ip::make_address("127.0.0.1"), 8080));

std::cout << "Connected to server!" <<  std::endl;

json order;
order["type"] = "order";
order["item"] = "burger";
order["quantity"] = 2;

std::string message = order.dump();


boost::asio::write(socket, boost::asio::buffer(message));

char reply[1024];
size_t length = socket.read_some(boost::asio::buffer(reply));

std::cout << "Server says: " << std::string(reply, length) << std::endl;

}catch (std::exception& e) {
std::cerr << "Error: " << e.what() << std::endl;
}

return 0; 
}
