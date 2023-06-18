#pragma once
#include "User.h"
#include "Address.h"

class Client : public User {
public:
	Client() = default;
	Client(const MyString& username,
		const MyString& password,
		const MyString& firstName,
		const MyString& lastName);

	double pay(double amount);
	void addMoney(double amount);

	User* clone() const override;
	void saveToFile(std::ofstream& file) override;
	void readFromFile(std::istream& file) override;
	static void splitString(const char* buff, size_t& buffInd, MyString& str);
	
};

