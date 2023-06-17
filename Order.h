#pragma once
#include "Driver.h"
#include "Client.h"
#include <ctime> 
#include <iomanip>

class Order {
private:
	bool isFinished = false;
	unsigned minutes = 0;
	size_t id = static_cast<size_t> (time(NULL));
	size_t passengersCount = 0;
	double price = 0;
	Address start;
	Address dest;
	Client* client = nullptr;
	Driver* driver = nullptr;

	void setOrder(User* client,
		const Address& start,
		const Address& dest,
		size_t passengersCount);
public:
	Order() = default;

	Order(User* client,
		const Address& start,
		const Address& dest,
		size_t passengersCount);


	void setMinutes(unsigned minutes);
	void setDriver(Driver* driver);
	void setPrice(double amount);

	void printOrderForDriver();
	void printOrderForClient();

	bool hasDriver() const;

	const Client& getClient() const;
	Client& getClient();
	Driver& getDriver();
	const Driver& getDriver() const;
	unsigned getMinutes() const;
	size_t getId() const;
	size_t getPassengersCount() const;
	Address getStart() const;
	Address getDest() const;
	double getPrice() const;
	void finishOrder();
};
