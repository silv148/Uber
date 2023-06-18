#pragma once
#include "Driver.h"
#include "Client.h"
#include <ctime> 
#include <iomanip>

class Order {
private:
	bool isFinished = false;
	bool cancelled = false;
	unsigned minutes = 0;
	size_t id = static_cast<size_t> (time(NULL));
	size_t passengersCount = 0;
	double price = 0;
	Address start;
	Address dest;
	Client* client = nullptr;
	Driver* driver = nullptr;

	void setOrder(Client* client,
		const Address& start,
		const Address& dest,
		size_t passengersCount);

	void copyFrom(const Order& other);
	void free();
public:
	Order() = default;
	Order(const Order& other);
	Order& operator=(const Order& other);
	~Order();

	Order(Client* client,
		const Address& start,
		const Address& dest,
		size_t passengersCount);


	void setMinutes(unsigned minutes);
	void setDriver(Driver* driver);
	void setClient(Client* client);
	void setPrice(double amount);

	void printOrderForDriver();
	void printOrderForClient();

	bool hasDriver() const;

	Client& getClient() const;
	Client& getClient();
	Driver& getDriver();
	Driver& getDriver() const;
	unsigned getMinutes() const;
	size_t getId() const;
	size_t getPassengersCount() const;
	Address getStart() const;
	Address getDest() const;
	double getPrice() const;
	bool isCancelled() const;
	
	void finishOrder();
	void cancelOrder();

	void saveToFile(std::ofstream& file);

	void readFromFile(std::istream& file);

};
