#pragma once
#include "User.h"
#include "Address.h"

class Driver : public User {
private:
	MyString carNumber = "";
	MyString phoneNumber = "";
	Address address;

	struct Rating {
		unsigned ratingSum = 0;
		unsigned ratingCount = 0;
	} rating;

	bool available = true;

public:
	Driver();
	Driver(const MyString& username,
		const MyString& password,
		const MyString& firstName,
		const MyString& lastName,
		const MyString& carNumber,
		const MyString& phoneNumber);

	const MyString& getCarNumber() const;
	const MyString& getPhoneNumber() const;

	double getRating() const;
	const Address& getAddress() const;
	void rate(unsigned short rating);

	const bool isAvailable() const;

	void setAvailability(bool available);
	void changeAddress(const Address& newAddress);
	void acceptPayment(double amount);

	User* clone() const override;
};

