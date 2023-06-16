#pragma once
#include "User.h"
#include "Address.h"
#include "Container.hpp"

class Client : public User {
public:
	Client() = default;
	Client(const MyString& username,
		const MyString& password,
		const MyString& firstName,
		const MyString& lastName);

	double pay(size_t orderId, double amount);
	void addMoney(double amount);
};

