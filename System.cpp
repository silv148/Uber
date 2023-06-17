#include "System.h"
#include <sstream>

Driver& System::findNextDriver(Vector<Driver*>& drivers, const Driver* driver) {
	if (drivers.getSize() == 0)
		throw std::logic_error("There are no available drivers!");

	for (size_t i = 0; i < drivers.getSize() - 1; i++) {
		if (drivers[i]->getUsername() == driver->getUsername()) {
			return *(drivers[i + 1]);
		}
	}

	throw std::logic_error("There are no available drivers!");
}

void System::sortDriversByDistance(const Order* order, Vector<Driver*>& drivers) {
	for (size_t i = 0; i < drivers.getSize(); i++) {
		for (size_t j = i + 1; j < drivers.getSize(); j++) {
			if (order->getStart().getDist(drivers[i]->getAddress()) - order->getStart().getDist(drivers[j]->getAddress()) > EPSILON) {
				std::swap(drivers[i], drivers[j]);
			}
		}
	}
}

Driver& System::getClosestDriver(Order* order) {
	Vector<Driver*> drivers;

	for (size_t i = 0; i < users.getSize(); i++) {
		if (users[i]->userIsDriver()) {
			Driver* driver = static_cast<Driver*>(users[i]);
			driver->isAvailable() ? std::cout <<"yes" << std::endl : std::cout << "no" << std::endl;
			if (driver->isAvailable()) {
				drivers.pushBack(driver);
				std::cout << drivers[drivers.getSize() - 1]->getUsername() << std::endl;
			}
		}
	}

	sortDriversByDistance(order, drivers);

	try {
		if (order->hasDriver()) {
			return findNextDriver(drivers, &order->getDriver());
		}
		else {
			return *drivers[0];
		}
	}
	catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error." << std::endl;
	}

	// Return a default driver or handle the error case appropriately
	static Driver defaultDriver;
	return defaultDriver;
}

System::~System() {
	delete loggedUser;
}

void System::printUsers() {
	for (size_t i = 0; i < users.getSize(); i++)
		std::cout << users[i]->getUsername() << std::endl;
}

void System::printOrders() {
	for (size_t i = 0; i < orders.getSize(); i++) {
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

		//role.toLower();

		if (role == "client") {
			users.pushBack(new Client(username, password, firstName, lastName));
		}
		else if (role == "driver") {
			MyString carNum;
			MyString phone;
			std::cin >> carNum >> phone;
			users.pushBack(new Driver(username, password, firstName, lastName, carNum, phone));
		}
		std::cout << "New user added to the system: " << users[users.getSize()-1]->getUsername() << std::endl;

		for (size_t i = 0; i < users.getSize(); i++)
			std::cout << users[i]->getUsername();

		return true;
	}
	catch (const std::logic_error& e) {
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
	User* user = getUserByUsername(username);

	if (user) {
		if (user->getPassword() == password) {
			loggedUser = user;
			std::cout << "Login successful. Welcome, " << user->getUsername() << "!" << std::endl;
			return true;
		}
	}
	else 
		std::cout << "Invalid username." << std::endl;

	std::cout << "Invalid password." << std::endl;
	delete user;
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
	for (size_t i = 0; i < users.getSize(); i++) {
		
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

		static Order order;
		order = Order(loggedUser, currentAddres, destination, passengersCount);
		static Driver driver;

		driver = getClosestDriver(&order);
		order.setDriver(&driver);
		std::cout << order.getId() << std::endl << order.getDriver().getUsername() << std::endl;
		orders.pushBack(&order);

	}
	catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	}
	catch (const std::exception& e) {
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

		for (size_t i = 0; i < finishedOrders.getSize(); i++)
			if (finishedOrders[i]->getClient().getUsername() == loggedUser->getUsername())
				if (finishedOrders[i]->getDriver().getUsername() == driverUsername)
					finishedOrders[i]->getDriver().rate(rating);
	}
	catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	}
	catch (const std::exception& e) {
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

		if (loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for drivers!");

		bool hasOrders = false;

		for (size_t i = 0; i < orders.getSize(); i++) {
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
	catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	}
	catch (const std::exception& e) {
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

		for (size_t i = 0; i < orders.getSize(); i++) {
			if (orders[i]->getClient().getUsername() == loggedUser->getUsername()
				&& orders[i]->getId() == orderId) {
				orders.popAt(i);
				return;
			}
		}
		std::cout << "You have no orders with such ID";
	}
	catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	}
	catch (const std::exception& e) {
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

		if (!loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for clients!");

		bool hasMessages = false;
		for (size_t i = 0; i < orders.getSize(); i++) {
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
	catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}

void System::acceptOrder(size_t orderId, unsigned minutes) {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (!loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for clients!");

		static Driver driver;
		driver = dynamic_cast<Driver&>(*loggedUser);
		if(!driver.isAvailable())
			throw std::logic_error("You cannot accept other orders yet!");

		for (size_t i = 0; i < orders.getSize(); i++) {
			if (orders[i]->getId() == orderId) {
				orders[i]->setDriver(&driver);
				orders[i]->setMinutes(minutes);
				driver.changeAddress(orders[i]->getStart());
				driver.setAvailability(false);
				std::cout << "Order " << orders[i]->getId() << " has been successfully accepted!";
				return;
			}
		}

		throw std::logic_error("There is no order with this ID");
	}
	catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}

//void System::declineOrder(size_t orderId) {
//	try {
//		if (!loggedUser)
//			throw std::logic_error("Log in to have access to the system!");
//
//		if (!loggedUser->userIsDriver())
//			throw std::logic_error("This is an invalid command for clients!");
//
//		for (size_t i = 0; i < orders.getSize(); i++) {
//			if (orders[i]->getId() == orderId) {
//				static Driver* driver = nullptr;
//				driver = &getClosestDriver(orders[i]);
//				orders[i]->setDriver(driver);
//				return;
//			}
//		}
//
//		throw std::logic_error("There is no order with this ID");
//	}
//	catch (const std::logic_error& e) {
//		std::cout << e.what() << std::endl;
//	}
//	catch (const std::exception& e) {
//		std::cout << e.what() << std::endl;
//	}
//	catch (...) {
//		std::cout << "Unknown error." << std::endl;
//	}
//}


void System::finishOrder(size_t orderId) {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (!loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for clients!");

		for (size_t i = 0; i < orders.getSize(); i++) {
			if (orders[i]->getId()) {
				if (orderId && orders[i]->getDriver().getUsername() == loggedUser->getUsername()) {
					orders[i]->getDriver().changeAddress(orders[i]->getDest());
					orders[i]->finishOrder();
					finishedOrders.pushBack(orders[i]);
					orders.popAt(i);
				} 
				else throw std::logic_error("You have no rights over this order!");
			}
			else throw std::logic_error("There is no order with this ID!");
		}
	}
	catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}
