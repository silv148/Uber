#include "ManageSystem.h"
#include <fstream>

void SystemManager::run() {
	System system;
	readFromFile(system);

	system.printRules();

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
		else if (command == "rate_driver")
			rate(system);
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
	
	saveToFile(system);
}

void SystemManager::registerNewUser(System& system) {
	MyString role;
	MyString username;
	MyString password;
	MyString firstName;
	MyString lastName;

	do {
		std::cin >> role;
		std::cin >> username;
		std::cin >> password;
		std::cin >> firstName;
		std::cin >> lastName;
	} while(!system.registerUser(role, username, password, firstName, lastName));
}

void SystemManager::loginUser(System& system) {
	MyString username;
	MyString password;
	do {
		std::cin >> username;
		std::cin >> password;
	} while(!system.loginUser(username, password));
}

void SystemManager::logoutUser(System& system) {
	system.logoutUser();
}

void SystemManager::createOrder(System& system) {
	MyString startAddressName;
	int x1 = 0;
	int y1 = 0;
	char startAdditionalInfo[1024];

	MyString destAddressName;
	int x2 = 0;
	int y2 = 0;
	char destAdditionalInfo[1024];

	unsigned passengersCount = 0;

	std::cin >> startAddressName >> x1 >> y1;
	std::cin.getline(startAdditionalInfo, 1024);

	std::cin >> destAddressName >> x2 >> y2;
	std::cin.getline(destAdditionalInfo, 1024);

	std::cin >> passengersCount;

	
	system.createOrder(Address(startAddressName, x1, y1, startAdditionalInfo),
						Address(destAddressName, x2, y2, destAdditionalInfo),
						passengersCount);
}

void SystemManager::checkOrder(System& system) {
	size_t orderId = 0;
	std::cin >> orderId;
	system.checkOrder(orderId);
}

void SystemManager::cancelOrder(System& system) {
	size_t orderId = 0;
	std::cin >> orderId;
	system.cancelOrder(orderId);
}

void SystemManager::pay(System& system) {
	size_t orderId = 0;
	double amount = 0.0;

	std::cin >> orderId >> amount;
	system.pay(orderId, amount);
}

void SystemManager::rate(System& system) {
	MyString driverUsername;
	unsigned rating = 0;

	std::cin >> driverUsername >> rating;
	system.rateDriver(driverUsername, rating);
}

void SystemManager::addMoney(System& system) {
	double amount = 0.0;

	std::cin >> amount;
	system.addMoney(amount);
}

void SystemManager::changeAddress(System& system) {
	MyString destAddressName;
	int x = 0;
	int y = 0;
	char destAdditionalInfo[1024];

	std::cin >> destAddressName >> x >> y;
	std::cin.getline(destAdditionalInfo, 1024);

	system.changeAddress(Address(destAddressName, x, y, destAdditionalInfo));
}

void SystemManager::checkMessages(System& system) {
	system.checkMessages();
}

void SystemManager::acceptOrder(System& system) {
	size_t orderId = 0;
	unsigned min = 0;

	std::cin >> orderId >> min;

	system.acceptOrder(orderId, min);
}

void SystemManager::declineOrder(System& system) {
	size_t orderId = 0;
	std::cin >> orderId;

	system.declineOrder(orderId);
}

void SystemManager::finishOrder(System& system) {
	size_t orderId = 0;
	std::cin >> orderId;

	system.finishOrder(orderId);
}

void SystemManager::acceptPayment(System& system) {
	size_t orderId;
	double amount = 0;

	std::cin >> orderId;
	std::cin >> amount;

	system.acceptPayment(orderId, amount);
}

void SystemManager::readFromFile(System& system) {
	std::ifstream inFile("file.txt");
	if (!inFile) {
		std::cerr << "Error";
		return;
	}
	system.readFromFile(inFile);
	inFile.close();

}

void SystemManager::saveToFile(System& system) {
	std::ofstream outFile("file.txt");

	if (!outFile) {
		std::cout << "Problem with oppening file ";
		return;
	}

	system.saveToFile(outFile);
	outFile.close();
}

