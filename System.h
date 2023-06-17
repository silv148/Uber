#pragma once
#include "Container.hpp"
#include "Client.h"
#include "Order.h"
#include "Vector.hpp"

const short BUFF_MAX_SIZE = 1024;
const double EPSILON = 0.000001;

class System {
private:
	Container<User> users;
	Container<Order> orders;
	Container<Order> finishedOrders;
	User* loggedUser = nullptr;

	static Driver* findNextDriver(Vector<Driver>& drivers, const Driver* driver);
	static void sortDriversByDistance(const Order* order, Vector<Driver>& drivers);
	Driver& getClosestDriver(Order* order);

public:
	static void printRules();
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
	void checkOrder(size_t orderId);
	void cancelOrder(size_t orderId);

	void checkMessages() const;
	void acceptOrder(size_t orderId, unsigned minutes);
	void declineOrder(size_t orderId);
	void finishOrder(size_t orderId);
};

