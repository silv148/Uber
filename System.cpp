#include "System.h"
#include <sstream>
#include <algorithm>
#include <fstream>

namespace {
	template <typename T, typename Compare>
	void selectionSort(Vector<T>& vec, Compare comp) {
		for (size_t i = 0; i < vec.getSize() - 1; ++i) {
			size_t minIndex = i;
			for (size_t j = i + 1; j < vec.getSize(); ++j) {
				if (comp(vec[j], vec[minIndex])) {
					minIndex = j;
				}
			}
			if (minIndex != i) {
				std::swap(vec[i], vec[minIndex]);
			}
		}
	}
}

void System::saveToFile(std::ofstream& file) {
	file << clients.getSize() << std::endl;
	for (size_t i = 0; i < clients.getSize(); i++) {
		clients[i]->saveToFile(file);
		file << std::endl;
	}

	file << drivers.getSize() << std::endl;
	for (size_t i = 0; i < drivers.getSize(); i++) {
		drivers[i]->saveToFile(file);
		file << std::endl;
	}

	file << orders.getSize() << std::endl;
	for (size_t i = 0; i < orders.getSize(); i++) {
		orders[i]->saveToFile(file);
		file << std::endl;
	}

	file << finishedOrders.getSize() << std::endl;
	for (size_t i = 0; i < finishedOrders.getSize(); i++) {
		finishedOrders[i]->saveToFile(file);
		file << std::endl;
	}
}

void System::readFromFile(std::istream& file) {
	size_t clientsSize = 0, driversSize = 0, ordersSize = 0, finishedOrdersSize = 0;

	file >> clientsSize;
	for (size_t i = 0; i < clientsSize; i++)
		clients[i]->readFromFile(file);

	file >> driversSize ;
	for (size_t i = 0; i < driversSize; i++)
		drivers[i]->readFromFile(file);

	file >> ordersSize;
	for (size_t i = 0; i < ordersSize; i++)
		clients[i]->readFromFile(file);

	file >> finishedOrdersSize;
	for (size_t i = 0; i < finishedOrdersSize; i++)
		clients[i]->readFromFile(file);
}

Driver& System::findNextDriver(Vector<Driver*>& drivers, const Driver* driver) {
	if (drivers.getSize() == 0)
		throw std::logic_error("There are no available drivers!");

	for (size_t i = 0; i < drivers.getSize() - 1; i++)
		if (drivers[i]->getUsername() == driver->getUsername() && drivers[i+1]->isAvailable())
			return *(drivers[i + 1]);

	throw std::logic_error("There are no available drivers!");
}

void System::sortDriversByDistance(const Order* order, Vector<Driver*>& drivers) {
	selectionSort(drivers, [&](Driver* a, Driver* b) {
		return order->getStart().getDist(a->getAddress()) < order->getStart().getDist(b->getAddress());
		});
}

Driver& System::getClosestDriver(Order* order) {
	try {
		if (drivers.getSize() == 0)
			throw std::logic_error("There are no availabe drivers!");

		sortDriversByDistance(order, drivers);

		if (order->hasDriver())
			return findNextDriver(drivers, &order->getDriver());
		else
			return *drivers[0];

	} catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}

System::System() {
	std::ifstream inFile("file.txt");
	if (!inFile) {
		std::cout << "Error";
		return;
	}
	readFromFile(inFile);
	inFile.close();
}

System::~System() {
	std::ofstream outFile("file.txt");
	
	if (!outFile) {
		std::cout << "Problem with oppening file ";
		return;
	}
	
	saveToFile(outFile);
	outFile.close();

	for (size_t i = 0; i < clients.getSize(); i++)
		delete clients[i];

	for (size_t i = 0; i < drivers.getSize(); i++)
		delete drivers[i];

	for (size_t i = 0; i < orders.getSize(); i++)
		delete orders[i];
	
	for (size_t i = 0; i < finishedOrders.getSize(); i++)
		delete finishedOrders[i];

	delete loggedUser;
}

void System::printRules() {
	std::cout << "Welcome to Uber!" << std::endl << std::endl
		<< "---------------How to register to the System---------------" << std::endl << std::endl
		<< "For Clients: " << std::endl
		<< "If you are new to our System, you can register as follows: " << std::endl
		<< "register <role> <username> <password> <first_name> <last_name>" << std::endl << std::endl
		<< "For Drivers: " << std::endl
		<< "If you are new to our System, you can register as follows: " << std::endl
		<< "register <role> <username> <password> <first_name> <last_name> <car_number> <phone_number>" << std::endl << std::endl
		<< "If you already have an account, you can log in as follows:" << std::endl
		<< "login <username> <password>" << std::endl << std::endl
		<< "You can log out by entering:" << std::endl
		<< "logout" << std::endl
		<< "Be mindful that the console will be cleared after you log out!" << std::endl << std::endl
		<< "To quit the program enter command <quit>!" << std::endl << std::endl;

}

void System::printCommandsForClients() {
	std::cout
		<< "Here is a guide with all allowed commands you can use in our System:" << std::endl << std::endl
		<< "1. create_order <address_start_name, x, y, additional_info> " << std::endl
		<< "<address_destination_name, x, y, additional_info> " << std::endl 
		<< "<passengers_count>" << std::endl
		<< "	     *Note that coordinates are whole numbers!" << std::endl << std::endl
		<< "2. check_order <ID> " << std::endl
		<< "         *ID is a whole number which you will recieve rignt after creating an order" << std::endl << std::endl
		<< "3. cancel_order <ID> " << std::endl << std::endl
		<< "4. pay <order_ID> <amount>" << std::endl
		<< "5. add_money <amount>" << std::endl
		<< "         *Note that you start with an empty bank account!" << std::endl << std::endl
		<< "Have fun using our system :)" << std::endl << std::endl;
}

void System::printCommandsForDrivers() {
	std::cout 
		<< "Here is a guide with all allowed commands you can use in our System:" << std::endl << std::endl
		<< "1. change_address  <address_start_name, x, y, additional_info>" << std::endl
		<< "2. check_messages" << std::endl
		<< "	     *Shows all orders which have been sent to you" << std::endl << std::endl
		<< "3. accept_order <id> <minutes>" << std::endl
		<< "         *You cannot accept other orders until finishing the order you have accepted" << std::endl << std::endl
		<< "4. decline_order <ID> " << std::endl
		<< "5. finish_order <id> " << std::endl
		<< "         *It automatically changes your address to order\'s destination!" << std::endl << std::endl
		<< "6. accept_payment <id> <amount>" << std::endl
		<< "         *Note that you start with an empty bank account!" << std::endl << std::endl
		<< "Have fun using our system :)" << std::endl << std::endl;
}

bool System::registerUser(const MyString& role,
						const MyString& username,
						const MyString& password,
						const MyString& firstName,
						const MyString& lastName) 
{
	try {
		if (loggedUser)
			throw std::logic_error("You cannot register from someone\'s profile!");

		if (getClientByUsername(username) || getDriverByUsername(username))
			throw std::logic_error("Username already exists. Please choose a different username.");

		if (role == "client") {
			clients.pushBack(new Client(username, password, firstName, lastName));
			system("cls");
			printRules();
			std::cout << "New user added to the system: " << clients[clients.getSize() - 1]->getUsername() << std::endl;

		}
		else if (role == "driver") {
			MyString carNum;
			MyString phone;
			std::cin >> carNum >> phone;
			drivers.pushBack(new Driver(username, password, firstName, lastName, carNum, phone));
			system("cls");
			printRules();
			std::cout << "New user added to the system: " << drivers[drivers.getSize() - 1]->getUsername() << std::endl;
		}
		else throw std::logic_error("There in no such role!");
		
		return true;

	} catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
		return false;
	} catch (std::exception e) {
		std::cout << e.what() << std::endl;
		return false;
	} catch (...) {
		std::cout << "Unknown error." << std::endl;
		return false;
	}
}

bool System::loginUser(const MyString& username, const MyString& password) {
	try {
		if (loggedUser)
			throw std::logic_error("You cannot login from someone\'s profile!");

		if (getClientByUsername(username)) {
			if (getClientByUsername(username)->getPassword() == password) {
				loggedUser = getClientByUsername(username);
				system("cls");
				std::cout << "Login successful. Welcome, " << username << "!" << std::endl << std::endl;
				printCommandsForClients();

				return true;
			}
			else {
				throw std::logic_error("Invalid password");
				return false;
			}
		}
		if (getDriverByUsername(username)) {
			if (getDriverByUsername(username)->getPassword() == password) {
				loggedUser = getDriverByUsername(username);
				system("cls");
				std::cout << "Login successful. Welcome, " << username << "!" << std::endl << std::endl;
				printCommandsForDrivers();

				return true;
			}
			else {
				throw std::logic_error("Invalid password");
				return false;
			}
		}

		throw std::logic_error("No user with this username and password exists!");
		return false;

	} catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
		return false;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return false;
	} catch (...) {
		std::cout << "Unknown error." << std::endl;
		return false;
	}
}

void System::logoutUser() {
	try{
		std::cout << loggedUser->getUsername() << std::endl;

		if (!loggedUser)
			throw std::logic_error("No user is currently logged in!");

		loggedUser = nullptr;
		system("cls");
		printRules();
	} catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}

Client* System::getClientByUsername(const MyString& username) {
	try{
		for (size_t i = 0; i < clients.getSize(); i++) 
		if (clients[i]->getUsername() == username) 
			return clients[i];

		throw std::logic_error("No client with this username was found");

	} catch (const std::logic_error& e) {
		return nullptr;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}

Driver* System::getDriverByUsername(const MyString& username) {
	try {
		for (size_t i = 0; i < drivers.getSize(); i++)
			if (drivers[i]->getUsername() == username)
				return drivers[i];

		throw std::logic_error("No driver with this username was found");

	} catch (const std::logic_error& e) {
		return nullptr;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}

void System::createOrder(const Address& currentAddress, const Address& destination, size_t passengersCount) {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (loggedUser->userIsDriver())
			throw std::logic_error("A driver cannot create orders!");

		if (!getClientByUsername(loggedUser->getUsername()))
			throw std::logic_error("Failed to retrieve client information!");

		orders.pushBack(new Order(getClientByUsername(loggedUser->getUsername()), currentAddress, destination, passengersCount));
		orders[orders.getSize() - 1]->setDriver(&getClosestDriver(orders[orders.getSize() - 1]));
		std::cout <<"Your order with ID: " << orders[orders.getSize() - 1]->getId() << 
			" has been successfully created!" << std::endl << std::endl;

	} catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
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
				if (finishedOrders[i]->getDriver().getUsername() == driverUsername) {
					finishedOrders[i]->getDriver().rate(rating);
					std::cout << "You have successfully rated driver " << finishedOrders[i]->getDriver().getUsername();
					return;
				}

		throw std::logic_error("You cannot rate this driver!");

	} catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}

void System::checkOrder(size_t orderId) const {
	try{
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for drivers!");

		bool hasOrders = false;

		for (size_t i = 0; i < orders.getSize(); i++) {
			if (orders[i]->getClient().getUsername() == loggedUser->getUsername()
				&& orders[i]->getId() == orderId) {
				std::cout << std::endl
					<< "---------------------------------------------------------------------------------"
					<< std::endl;
				orders[i]->printOrderForClient();
				std::cout << std::endl
					<< "---------------------------------------------------------------------------------"
					<< std::endl;
				hasOrders = true;
			}
		}
		if(!hasOrders)
		 std::cout << "You have no orders with such ID";

	} catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}

void System::cancelOrder(size_t orderId) {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for drivers!");

		for (size_t i = 0; i < orders.getSize(); i++) {
			if (orders[i]->getClient().getUsername() == loggedUser->getUsername()
				&& orders[i]->getId() == orderId) {
				orders[i]->cancelOrder();
				std::cout << "Your order with ID: " << orders[i]->getId() << " has been canceled successfully!" << std::endl;
				return;
			}
		}
		throw std::logic_error("You have no orders with such ID");

	} catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}

void System::addMoney(double amount) {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for drivers!");

		if (!getClientByUsername(loggedUser->getUsername()))
			throw std::logic_error("Failed to retrieve client information!");

		if (amount <= 0)
			throw std::logic_error("You cannot add this sum to you bank account!");

		getClientByUsername(loggedUser->getUsername())->addMoney(amount);
		std::cout << "You have added money to your account successfully!" << std::endl;

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

void System::pay(size_t orderId, double amount) {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for drivers!");

		if (amount <= 0)
			throw std::logic_error("Amount shoud not be a negative number!");

		bool orderFound = false;
		for (size_t i = 0; i < finishedOrders.getSize(); i++) {
			if (finishedOrders[i]->getId() == orderId) {
				if (finishedOrders[i]->getClient().getUsername() == loggedUser->getUsername()) {
					finishedOrders[i]->setPrice(amount);
					finishedOrders[i]->getClient().pay(amount);
					orderFound = true;
					std::cout << "You have paid successfully!" << std::endl;
					return;
				}
				else throw std::logic_error("You have no rights over this order!");
			}
		}

		if (!orderFound)
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

void System::changeAddress(const Address& address) {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (!loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for clients!");

		if (!getDriverByUsername(loggedUser->getUsername()))
			throw std::logic_error("There is no driver with such username!");

		getDriverByUsername(loggedUser->getUsername())->changeAddress(address);
		std::cout << "You have changed your address successfully!" << std::endl;


	} catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}

void System::checkMessages() {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (!loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for clients!");

		std::cout << std::endl;
		bool hasMessages = false;
		for (size_t i = 0; i < orders.getSize(); i++) {
			if (&orders[i]->getDriver() && orders[i]->getDriver().getUsername() == loggedUser->getUsername()) {
				if (orders[i]->isCancelled()) {
					std::cout << orders[i]->getClient().getFirstName() << " " << orders[i]->getClient().getLastName()
						<< " has cancelled order " << orders[i]->getId() << " from: " << std::endl;
					orders[i]->getStart().printAddress();
					std::cout << "To: " << std::endl;
					orders[i]->getDest().printAddress();
					std::cout << std::endl
						<< "---------------------------------------------------------------------------------"
						<< std::endl;
					hasMessages = true;
					orders.popAt(i);
				}
				else {
					std::cout << orders[i]->getClient().getFirstName() << " " << orders[i]->getClient().getLastName()
						<< " has made an order from: " << std::endl;
					orders[i]->getStart().printAddress();
					std::cout << "To: " << std::endl;
					orders[i]->getDest().printAddress();
					std::cout << std::endl 
						<<"Order ID: " << orders[i]->getId()
						<< "---------------------------------------------------------------------------------"
						<< std::endl;
					hasMessages = true;
				}
			}
		}

		if (!hasMessages)
			std::cout << "You have no new messages!";

	} catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}

void System::acceptOrder(size_t orderId, unsigned minutes) {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (!loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for clients!");

		for (size_t i = 0; i < orders.getSize(); i++) {
			if (orders[i]->getId() == orderId && !orders[i]->isCancelled()) {
				if (loggedUser->getUsername() == orders[i]->getDriver().getUsername() && orders[i]->getDriver().isAvailable()) {
					orders[i]->setMinutes(minutes);
					orders[i]->getDriver().setAvailability(false);

					std::cout << "Order " << orders[i]->getId() << " has been successfully accepted!" <<std::endl;
					return;
				}
				else throw std::logic_error("You have no rights over this order!");
			}
			else if(orders[i]->getId() == orderId) {
				std::cout << orders[i]->getClient().getFirstName() << " " << orders[i]->getClient().getLastName()
					<< " has cancelled order " << orders[i]->getId() << " from: " << std::endl;
				orders[i]->getStart().printAddress();
				std::cout << "To: " << std::endl;
				orders[i]->getDest().printAddress();
				std::cout << std::endl
					<< "---------------------------------------------------------------------------------"
					<< std::endl;
				orders.popAt(i);
			}
		}

		throw std::logic_error("There is no order with this ID");

	} catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
		return;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return;
	} catch (...) {
		std::cout << "Unknown error." << std::endl;
		return;
	}
}


void System::declineOrder(size_t orderId) {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (!loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for clients!");

		for (size_t i = 0; i < orders.getSize(); i++) {
			if (orders[i]->getId() == orderId) {
				if (orders[i]->getDriver().getUsername() == loggedUser->getUsername()) {
					orders[i]->setDriver(&getClosestDriver(orders[i]));
					std::cout << "You have declined this order successfully!" << std::endl;
					return;
				}
				else throw std::logic_error("You have no rights over this order!");
			}
		}

		throw std::logic_error("There is no order with this ID");

	} catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
		return;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return;
	} catch (...) {
		std::cout << "Unknown error." << std::endl;
		return;
	}
}

void System::finishOrder(size_t orderId) {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (!loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for clients!");

		for (size_t i = 0; i < orders.getSize(); i++) {
			if (orders[i]->getId() == orderId && !orders[i]->isCancelled()) {
				if (orders[i]->getDriver().getUsername() == loggedUser->getUsername()) {
					orders[i]->getDriver().changeAddress(orders[i]->getDest());
					orders[i]->finishOrder();
					finishedOrders.pushBack(orders[i]);
					orders.popAt(i);
					std::cout << "You have finished this order successfully!" << std::endl;
					return;
				}
				else throw std::logic_error("You have no rights over this order!");
			}
			else if (orders[i]->getId() == orderId && orders[i]->isCancelled()) {
				std::cout << orders[i]->getClient().getFirstName() << " " << orders[i]->getClient().getLastName()
					<< " has cancelled order " << orders[i]->getId() << " from: " << std::endl;
				orders[i]->getStart().printAddress();
				std::cout << "To: " << std::endl;
				orders[i]->getDest().printAddress();
				std::cout << std::endl
					<< "---------------------------------------------------------------------------------"
					<< std::endl;
				orders.popAt(i);
				return;
			}
		}

		throw std::logic_error("There is no order with this ID!");

	} catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
		return;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return;
	} catch (...) {
		std::cout << "Unknown error." << std::endl;
		return;
	}
}

void System::acceptPayment(size_t orderId, double amount) {
	try {
		if (!loggedUser)
			throw std::logic_error("Log in to have access to the system!");

		if (!loggedUser->userIsDriver())
			throw std::logic_error("This is an invalid command for clients!");

		for (size_t i = 0; i < finishedOrders.getSize(); i++)
			if (finishedOrders[i]->getId() == orderId)
				if (finishedOrders[i]->getDriver().getUsername() == loggedUser->getUsername()) {
					finishedOrders[i]->getDriver().acceptPayment(amount);
					std::cout << "You have accepted successfully!" << std::endl;
				}
				else throw std::logic_error("You have no rights over this order!");
		
		throw std::logic_error("There is no order with this ID!");

	} catch (const std::logic_error& e) {
		std::cout << e.what() << std::endl;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "Unknown error." << std::endl;
	}
}
