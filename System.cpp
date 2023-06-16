#include "System.h"
#include <sstream>

void System::printUsers() {
	for (size_t i = 0; i < users.getCount(); i++)
		std::cout << users[i]->getUsername() << std::endl;
}

void System::printOrders() {
	for (size_t i = 0; i < orders.getCount(); i++) {
		std::cout << std::endl << orders[i]->getId() << " -- "
			<< orders[i]->getClient().getUsername() << " -- "
			<< orders[i]->getDriver().getUsername() << " -- "
			<< orders[i]->getDest().getName() << std::endl;
	}
}

bool System::registerUser(const MyString& role,
						const MyString& username,
						const MyString& password,
						const MyString& firstName,
						const MyString& lastName) 
{
	try {
		if (getUserByUsername(username))
			throw std::logic_error("Username already exists. Please choose a different username.");

		User* user = nullptr;
		if (role == "client")
			user = new Client(username, password, firstName, lastName);
		else {
			MyString carNum;
			MyString phone;
			std::cin >> carNum >> phone;
			user = new Driver(username, password, firstName, lastName, carNum, phone);
		}

		users.addElemenet(*user);
		return true;
	}
	catch (std::logic_error e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}

bool System::loginUser(const MyString& username, const MyString& password) {
	static User* user = getUserByUsername(username);
	if (user && user->getPassword() == password) {
		loggedUser = user;
		std::cout << "Login successful. Welcome, " << user->getUsername() << "!" << std::endl;
		return true;
	}

	std::cout << "Invalid username or password." << std::endl;
	return false;
}

void System::logoutUser() {
	if (loggedUser) {
		std::cout << "Logout successful. Goodbye, " << loggedUser->getUsername() << std::endl;
		loggedUser = nullptr;
	}
	else
		std::cout << "No user is currently logged in." << std::endl;
}

User* System::getUserByUsername(const MyString& username) {
	for (size_t i = 0; i < users.getCount(); i++) {
		if (users[i]->getUsername() == username) {
			return users[i];
		}
	}
	return nullptr;
}

void System::createOrder(const Address& currentAddres, 
								const Address& destination, 
								size_t passengersCount) 
{
	try{
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (loggedUser->userIsDriver())
			throw std::logic_error("A driver cannot create orders!");

		static Order* order = new Order(loggedUser, currentAddres, destination, passengersCount);
		orders.addElemenet(*order);
	}
	catch (std::logic_error e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}

void System::rateDriver(const MyString& driverUsername, const unsigned rating) {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for drivers!");

		for (size_t i = 0; i < finishedOrders.getCount(); i++)
			if (finishedOrders[i]->getClient().getUsername() == loggedUser->getUsername())
				if (finishedOrders[i]->getDriver().getUsername() == driverUsername)
					finishedOrders[i]->getDriver().rate(rating);
	}
	catch (std::logic_error e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}

void System::checkOrder(size_t orderId) {
	try{
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (loggedUser->userIsDriver()) {
			throw std::logic_error("This is an invalid command for drivers!");
		}

		bool hasOrders = false;

		for (size_t i = 0; i < orders.getCount(); i++) {
			if (orders[i]->getClient().getUsername() == loggedUser->getUsername()
				&& orders[i]->getId() == orderId) {
				orders[i]->printOrderForClient();
				std::cout << std::endl
					<< "---------------------------------------------------------------------------------"
					<< std::endl;
				hasOrders = true;
			}
		}
		if(!hasOrders)
		 std::cout << "You have no orders with such ID";
	}
	catch (std::logic_error e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}

void System::cancelOrder(size_t orderId) {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (loggedUser->userIsDriver()) {
			throw std::logic_error("This is an invalid command for drivers!");
		}

		for (size_t i = 0; i < orders.getCount(); i++) {
			if (orders[i]->getClient().getUsername() == loggedUser->getUsername()
				&& orders[i]->getId() == orderId) {
				delete orders[orderId];
				orders[orderId] = nullptr;
				return;
			}
		}
		std::cout << "You have no orders with such ID";
	}
	catch (std::logic_error e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}

void System::checkMessages() const {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (!loggedUser->userIsDriver()) {
			throw std::logic_error("This is an invalid command for clients!");
		}

		bool hasMessages = false;
		for (size_t i = 0; i < orders.getCount(); i++) {
			if (&orders[i]->getDriver() && orders[i]->getDriver().getUsername() == loggedUser->getUsername()) {
				std::cout << orders[i]->getClient().getFirstName() << " " << orders[i]->getClient().getLastName() 
					<< " has made an order from: " << std::endl;
				orders[i]->getStart().printAddress();
				std::cout << "To: " << std::endl;
				orders[i]->getDest().printAddress();
				std::cout << std::endl
					<< "---------------------------------------------------------------------------------"
					<< std::endl;
				hasMessages = true;
			}
		}
		if(!hasMessages)
			std::cout << "You have no new messages!";
	}
	catch (std::logic_error e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}
