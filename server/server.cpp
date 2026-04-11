#include <iostream>
#include <memory>
#include <functional>
#include <ctime>
#include <boost/asio.hpp>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using boost::asio::ip::tcp;

int main() {
	boost::asio::io_context io;

tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 8080));
std::cout << "Server started on port 8080...";

std::vector<json> orders;
int orderID = 1;


std::function<void()> do_accept;

do_accept = [&]() {
	auto socket = std::make_shared<tcp::socket>(io);

acceptor.async_accept(*socket, [&, socket](boost::system::error_code ec) {
	if (!ec) {
		std::cout << "Client connected!\n";
		

		auto buffer = std::make_shared<std::vector<char>>(1024);

		socket->async_read_some(boost::asio::buffer(*buffer),
		[&, socket, buffer](boost::system::error_code ec, size_t length) {
	if (!ec) {
		try {
		std::string received(buffer->data(), length);
		json order;
	
		order = json::parse(received); 

std::string item = order["item"];
int quantity = order["quantity"];


std::vector<std::string> menu ={
"Burger",
"Pizza",
"Noodles",
"Pasta",
"Chicken",
"Fish",
"Meat",
"Shawerma",
"Fries",
"Salad",
"Cake",
"Soda",
"Water"
};

if (std::find(menu.begin(), menu.end(), item) == menu.end()) {

 json response;
                response["status"] = "error";

                boost::asio::async_write(*socket,  boost::asio::buffer(response.dump()),
                [socket](boost::system::error_code ec, std::size_t) {}
);
return;
}


if (!order.contains("item") || !order.contains("quantity"))
 {
		json response;
		response["status"] = "error";

		boost::asio::async_write(*socket,  boost::asio::buffer(response.dump()),
                [socket](boost::system::error_code ec, std::size_t) {}
);
return;
}




std::cout << "Order recieved. \n";


if (quantity <= 0) {

		 json response;
                response["status"] = "error";

                boost::asio::async_write(*socket,  boost::asio::buffer(response.dump()),
                [socket](boost::system::error_code ec, std::size_t) {}
);
return;
}











bool valid = false;

for (const auto& m : menu) {
if (m == item) {
	valid = true;
break;
}}

order["time"] = (long)time(nullptr);
orders.push_back(order);


std::cout << "\n ====================== \n";
std::cout << "  New Order #" << orderID << "\n ";
std::cout << "\n ====================== \n";

std::cout << "Item : " << order["item"].get<std::string>() << std::endl;
std::cout << "Quantity : " << order["quantity"] << std::endl;

std::cout << "\nAll Orders:\n";
std::string status;
for (const auto& o : orders) {

long now = time(nullptr);
long orderTime = o["time"].get<long>();
long diff =  now - orderTime;


		if (diff < 10)
			status = "Preparing";
		else if (diff < 20)
			status = "Cooking";
		else 
			status = "Ready";
		std::cout << "- " << o["item"].get<std::string>() << " x" << o["quantity"] << " (" << status << " )" << std::endl; }


json response;
response["status"] = status;

boost::asio::async_write(*socket, 
                boost::asio::buffer(response.dump()),
                [socket](boost::system::error_code ec, std::size_t) {
                        if (ec){
                                std::cout << "Write error: " << ec.message();
}
}
);

orderID++;
}
catch (...) {
	std::cout << "Invalid JSON received\n" ; }
} 
	} 
		);
			}
do_accept();
});
};
do_accept();
io.run();
return 0;
}

