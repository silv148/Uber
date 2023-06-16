#pragma once
#include "Driver.h"
#include <ctime>    

class Order {
private:
	bool isFinished = false;
	unsigned minutes = 0;
	size_t id = static_cast<size_t> (time(NULL));
	size_t passengersCount = 0;
	Address start;
	Address dest;
	const User* client = nullptr;
	Driver* driver = nullptr;

	void setOrder(const User* client,
		const Address& start,
		const Address& dest,
		size_t passengersCount);
public:
	Order() = default;

	Order(const User* client,
		const Address& start,
		const Address& dest,
		size_t passengersCount);


	void setMinutes(unsigned minutes);
	void setDriver(Driver* driver);

	void printOrderForDriver();
	void printOrderForClient();

	const User& getClient() const;
	Driver& getDriver();
	const Driver& getDriver() const;
	unsigned getMinutes() const;
	size_t getId() const;
	size_t getPassengersCount() const;
	Address getStart() const;
	Address getDest() const;
	void finishOrder();
};
