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
	while (!system.registerUser("client", "kolyo", "password", "Kolyo", "Kolev")) {
		system.registerUser("client", "kolyo", "password", "Kolyo", "Kolev");
	}
	while (!system.loginUser("kolyo", "password"))
		system.loginUser("kolyo", "password");
	
	system.logoutUser();
}