#pragma once
#include "Container.hpp"
#include "Client.h"
#include "Order.h"

const short BUFF_MAX_SIZE = 1024;

class System {
private:
	Container<User> users;
	Container<Order> orders;
	Container<Order> finishedOrders;
	User* loggedUser;

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
	void declineOrder(size_t orderId) const;
	void finishOrder(size_t orderId);
};

