#include "System.h"
#include <sstream>

Driver* System::findNextDriver(Vector<Driver>& drivers, const Driver* driver) {
	if (drivers.getSize() == 0)
		return nullptr;

	for (size_t i = 0; i < drivers.getSize() - 1; i++)
		if (drivers[i].getUsername() == driver->getUsername())
			return &drivers[i + 1];

	return nullptr;
}

void System::sortDriversByDistance(const Order* order, Vector<Driver>& drivers) {
	for (size_t i = 0; i < drivers.getSize(); i++)
		for(size_t j = i + 1; j < drivers.getSize(); j++)
			if (order->getStart().getDist(drivers[i].getAddress()) - order->getStart().getDist(drivers[j].getAddress()) > EPSILON)
				std::swap(drivers[i], drivers[j]);
}

Driver& System::getClosestDriver(Order* order) {
	static Driver* closestDriver = nullptr;

	static Vector<Driver> drivers;
	for (size_t i = 0; i < users.getCount(); i++)
		if (users[i]->userIsDriver() && dynamic_cast<Driver*>(users[i])->isAvailable())
			drivers.pushBack(*dynamic_cast<Driver*>(users[i]));

	sortDriversByDistance(order, drivers);

	if(order->hasDriver())
		closestDriver = findNextDriver(drivers, &order->getDriver());

	else
		closestDriver = &drivers[0];
	return *closestDriver;
}

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

		static User* user = nullptr;
		//role.toLower();
		if (role == "client")
			user = new Client(username, password, firstName, lastName);
		else if (role == "driver") {
			MyString carNum;
			MyString phone;
			std::cin >> carNum >> phone;
			user = new Driver(username, password, firstName, lastName, carNum, phone);
		}
		std::cout << "New user added to the system: " << user->getUsername() << std::endl;
		users.addElemenet(*user);

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
	static User* user = nullptr;
	user = getUserByUsername(username);

	if (user->getPassword() == password) {
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

		static Order* order = nullptr;
		order = new Order(loggedUser, currentAddres, destination, passengersCount);

		static Driver* driver = nullptr;
		driver = &getClosestDriver(order);
		order->setDriver(driver);
		std::cout << order->getDriver().getUsername();
		std::cout << order->getId()  << std::endl << order->getDriver().getUsername();
		orders.addElemenet(*order);

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

		for (size_t i = 0; i < finishedOrders.getCount(); i++)
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

		for (size_t i = 0; i < orders.getCount(); i++) {
			if (orders[i]->getClient().getUsername() == loggedUser->getUsername()
				&& orders[i]->getId() == orderId) {
				orders.removeElement(orderId);
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

		Driver* driver = dynamic_cast<Driver*>(loggedUser);
		if(!driver->isAvailable())
			throw std::logic_error("You cannot accept other orders yet!");

		for (size_t i = 0; i < orders.getCount(); i++) {
			if (orders[i]->getId() == orderId) {
				orders[i]->setDriver(driver);
				orders[i]->setMinutes(minutes);
				driver->changeAddress(orders[i]->getStart());
				driver->setAvailability(false);
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

void System::declineOrder(size_t orderId) {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (!loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for clients!");

		for (size_t i = 0; i < orders.getCount(); i++) {
			if (orders[i]->getId() == orderId) {
				static Driver* driver = nullptr;
				driver = &getClosestDriver(orders[i]);
				orders[i]->setDriver(driver);
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


void System::finishOrder(size_t orderId) {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (!loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for clients!");

		for (size_t i = 0; i < orders.getCount(); i++) {
			if (orders[i]->getId()) {
				if (orderId && orders[i]->getDriver().getUsername() == loggedUser->getUsername()) {
					orders[i]->getDriver().changeAddress(orders[i]->getDest());
					orders[i]->finishOrder();
					finishedOrders.addElemenet(*orders[i]);
					orders.removeElement(i);
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
