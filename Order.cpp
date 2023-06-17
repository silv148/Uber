#include "Order.h"

Order::Order(const User* client, const Address& start, const Address& dest, size_t passengersCount) {
	setOrder(client, start, dest, passengersCount);
}

void Order::setMinutes(unsigned minutes) {
	this->minutes = minutes;
}

void Order::setDriver(Driver* driver) {
	this->driver = driver;
}

void Order::setOrder(const User* client,
					const Address& start,
					const Address& dest,
					size_t passengersCount) 
{
	this->client = client;
	this->start = start;
	this->dest = dest;
	this->passengersCount = passengersCount;

}

void Order::printOrderForDriver() {
	std::cout << client->getFirstName() << " " << client->getLastName()
		<< " has made an order from: " << std::endl;
	start.printAddress();
	std::cout << "To: " << std::endl;
	dest.printAddress();
	std::cout << "Order ID: " << id << std::endl;
}

void Order::printOrderForClient() {
	std::cout << std::endl;
	if (hasDriver())
		std::cout << "Order ID: " << id << std::endl
			<< "Your order has been accepted by:" << std::endl
			<< driver->getFirstName() << " " << driver->getLastName()
			<< " with username: " << driver->getUsername() << std::endl
			<< "Car number: " << driver->getCarNumber() << std::endl
			<< "Phone number: " << driver->getPhoneNumber() << std::endl
			<< "Driver\'s rating: " << std::setprecision(1) << driver->getRating() << std::endl << std::endl
			<< "Your driver will arrive within " << minutes << " minutes!" << std::endl;
	else
		std::cout << "Your order has not been accepted yet:(";
}

bool Order::hasDriver() const {
	return driver;
}

const User& Order::getClient() const {
	return *client;
}

const Driver& Order::getDriver() const {
	return *driver;
}

Driver& Order::getDriver() {
	return *driver;
}

unsigned Order::getMinutes() const {
	return minutes;
}

size_t Order::getId() const {
	return id;
}

size_t Order::getPassengersCount() const {
	return passengersCount;
}

Address Order::getStart() const {
	return start;
}

Address Order::getDest() const {
	return dest;
}

void Order::finishOrder() {
	isFinished = true;
	driver->setAvailability(true);
}
