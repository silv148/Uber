#include "ManageSystem.h"

void run() {
	System system;

	MyString command;
	std::cin >> command;
	command.toLower();
	while (command != "quit") {
		if (command == "register")
			registerNewUser(system);
		else if (command == "login")
			loginUser(system);
		else if (command == "logout")
			logoutUser(system);
		else if (command == "create_order")
			createOrder(system);
		else if (command == "check_order")
			checkOrder(system);
		else if (command == "cancel_order")
			cancelOrder(system);
		else if (command == "pay")
			pay(system);
		else if (command == "add_money")
			addMoney(system);
		else if (command == "change_address")
			changeAddress(system);
		else if (command == "check_messages")
			checkMessages(system);
		else if (command == "accept_order")
			acceptOrder(system);
		else if (command == "decline_order")
			declineOrder(system);
		else if (command == "finish_order")
			finishOrder(system);
		else if (command == "accept_payment")
			acceptPayment(system);
		else
			std::cout << "Invalid command!";

		std::cin >> command;
		command.toLower();
	}
}

void registerNewUser(System& system) {
	MyString role;
	MyString username; 
	MyString password;
	MyString firstName;
	MyString lastName;

	std::cin >> role;
	std::cin >> username;
	std::cin >> password;
	std::cin >> firstName;
	std::cin >> lastName;

	system.registerUser(role, username, password, firstName, lastName);
}

void loginUser(System& system) {
	MyString username;
	MyString password;

	std::cin >> username;
	std::cin >> password;

	system.loginUser(username, password);
}

void logoutUser(System& system) {
	system.logoutUser();
}

void createOrder(System& system) {
}

void checkOrder(System& system) {
	size_t orderId = 0;
	std::cin >> orderId;
	system.checkOrder(orderId);
}

void cancelOrder(System& system) {
	size_t orderId = 0;
	std::cin >> orderId;
	system.cancelOrder(orderId);
}

void pay(System& system) {
	size_t orderId = 0;
	double amount = 0.0;

	std::cin >> orderId >> amount;
	system.pay(orderId, amount);
}

void rate(System& system) {
	MyString driverUsername;
	unsigned rating = 0;

	std::cin >> driverUsername >> rating;
	system.rateDriver(driverUsername, rating);
}

void addMoney(System& system) {
	double amount = 0.0;

	std::cin >> amount;
	system.addMoney(amount);
}

void changeAddress(System& system) {

}

void checkMessages(System& system) {
	system.checkMessages();
}

void acceptOrder(System& system) {
	size_t orderId = 0;
	unsigned min = 0;

	std::cin >> orderId >> min;

	system.acceptOrder(orderId, min);
}

void declineOrder(System& system) {
	size_t orderId = 0;
	std::cin >> orderId;

	system.declineOrder(orderId);
}

void finishOrder(System& system) {
	size_t orderId = 0;
	std::cin >> orderId;

	system.finishOrder(orderId);
}

void acceptPayment(System& system) {
}

