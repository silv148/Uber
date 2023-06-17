#include <iostream>
#include "System.h"
//#include "Client.h"

int main() {
	/*Client client("kolyo", "password", "Kolyo", "Kolev");
	Order order = client.makeOrder(Address("address1", 3, 5), Address("address2", 7, 8));
	Client cl2("dimo", "passw0rd", "Dimo", "Dimchev");
	Order order2 = client.makeOrder(Address("add1", 5, 3), Address("add2", 7, 8), 4);
	Order order3 = cl2.makeOrder(Address("address3", 3, 5), Address("address4", 17, 88));
	std::cout << order.getClient().getUsername() << std::endl;
	std::cout << order2.getClient().getUsername() << std::endl;
	std::cout << order3.getClient().getUsername() << std::endl;
	Driver driver("simo", "simo1234", "Simo", "Simov", "carNum", "phoneNum");
	order.setDriver(&driver);
	std::cout << order.getDriver().getUsername() << std::endl;*/
	System system;

	system.registerUser("client", "kolyo", "password", "Kolyo", "Kolev");
	std::cout << std::endl;

	system.registerUser("driver", "pe6o", "pe6opass", "Petar", "Petrov");
	std::cout << std::endl;

	system.loginUser("kolyo", "password"); 
	std::cout << std::endl;

	system.createOrder(Address("1", 1, 1), Address("2", 2, 2), 3);
	std::cout << std::endl;
	system.logoutUser();
	std::cout << std::endl;
	system.loginUser("pe6o", "pe6opass");
	std::cout << std::endl;
	size_t orderId = 0;
	std::cin >> orderId;
	system.acceptOrder(orderId, 10);
	std::cout << std::endl;
	system.logoutUser();
	std::cout << std::endl;
	system.loginUser("kolyo", "password");
	std::cout << std::endl;
	system.checkOrder(orderId);
	std::cout << std::endl;
	system.logoutUser();
}