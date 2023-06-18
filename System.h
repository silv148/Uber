#pragma once
#include "Client.h"
#include "Order.h"
#include "Vector.hpp"

const short BUFF_MAX_SIZE = 1024;
const double EPSILON = 0.000001;

class System {
private:
	Vector<User*> users;
	Vector<Order*> orders;
	Vector<Order*> finishedOrders;
	User* loggedUser = nullptr;

	static Driver& findNextDriver(Vector<Driver*>& drivers, const Driver* driver);
	static void sortDriversByDistance(const Order* order, Vector<Driver*>& drivers);
	Driver& getClosestDriver(Order* order);

public:
	System() = default;
	System(const System & other) = delete;
	System& operator=(const System & other) = delete;
	~System();

	static void printRules();
	static void printCommandsForClients();
	static void printCommandsForDrivers();
	void printUsers();
	void printOrders();

	bool registerUser(const MyString& role, 
					  const MyString& username,
					  const MyString& password,
					  const MyString& firstName,
					  const MyString& lastName);

	bool loginUser(const MyString& username, const MyString& password);
	void logoutUser();
	User* getUserByUsername(const MyString& username);
	 
	void createOrder(const Address& currentAddres,
						   const Address& destination,
						   size_t passengersCount = 1);
	void rateDriver(const MyString& driverName, const unsigned rating);
	void checkOrder(size_t orderId) const;
	void cancelOrder(size_t orderId);
	void addMoney(double amount);
	void pay(size_t orderId, double amount);

	void changeAddress(const Address& address);
	void checkMessages();
	void acceptOrder(size_t orderId, unsigned minutes);
	void declineOrder(size_t orderId);
	void finishOrder(size_t orderId);
	void acceptPayment(size_t orderId, double amount);
};

