#include "Order.h"

Order::Order(const Order& other) {
	copyFrom(other);
}

Order& Order::operator=(const Order& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Order::~Order() {
	free();
}

Order::Order(Client* client, const Address& start, const Address& dest, size_t passengersCount) {
	setOrder(client, start, dest, passengersCount);
}

void Order::setMinutes(unsigned minutes) {
	this->minutes = minutes;
}

void Order::setDriver(Driver* driver) {
	this->driver = driver;
}

void Order::setClient(Client* client) {
	this->client = client;
}

void Order::setPrice(double amount) {
	this->price = amount;
}

void Order::setOrder(Client* client,
					const Address& start,
					const Address& dest,
					size_t passengersCount) 
{
	this->client = client;
	this->start = start;
	this->dest = dest;
	this->passengersCount = passengersCount;

}

void Order::copyFrom(const Order& other) {
	id = other.getId();
	minutes = other.getMinutes();
	passengersCount = other.getPassengersCount();
	price = other.price;
	start = other.getStart();
	dest = other.getDest();
	client = &other.getClient();
	driver = &other.getDriver();
	isFinished = other.isFinished;
}

void Order::free() {
	delete client;
	delete driver;
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
	if (hasDriver() && driver->isAvailable())
		std::cout << "Order ID: " << id << std::endl
		<< "Your order is still in process!" << std::endl;

	else if(hasDriver() && !driver->isAvailable())
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

Client& Order::getClient() const {
	return *client;
}

Client& Order::getClient() {
	return *client;
}

Driver& Order::getDriver() const {
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

double Order::getPrice() const {
	return price;
}

bool Order::isCancelled() const {
	return cancelled;
}

void Order::finishOrder() {
	isFinished = true;
	driver->setAvailability(true);
}

void Order::cancelOrder() {
	cancelled = true;
}
