#include "Driver.h"
#include <fstream>

Driver::Driver() : User() {
	isDriver = true;
}

Driver::Driver(const MyString& username,
	const MyString& password,
	const MyString& firstName,
	const MyString& lastName,
	const MyString& carNumber,
	const MyString& phoneNumber) : User(username, password, firstName, lastName), carNumber(carNumber), phoneNumber(phoneNumber) 
{
	isDriver = true;
}

const MyString& Driver::getCarNumber() const {
	return carNumber;
}

const MyString& Driver::getPhoneNumber() const {
	return phoneNumber;
}

void Driver::rate(unsigned short rating) {
	this->rating.ratingCount++;
	this->rating.ratingSum += rating;
}

const bool Driver::isAvailable() const {
	return available;
}

double Driver::getRating() const {
	double toReturn = 0.0;
	rating.ratingCount > 0 ? toReturn = (double)rating.ratingSum / rating.ratingCount : toReturn;
	return toReturn;
}

const Address& Driver::getAddress() const {
	return address;
}

void Driver::setAvailability(bool available) {
	this->available = available;
}

void Driver::changeAddress(const Address& newAddress) {
	address = newAddress;
}

void Driver::acceptPayment(double amount) {
	accountBalance += amount;
	available = true;
}

User* Driver::clone() const {
	return new Driver(*this);
}

void Driver::saveToFile(std::ofstream& file) {
	file << username.c_str() << " " << password.c_str() << " " << firstName.c_str() << " " << lastName.c_str() << " " << carNumber << " " << phoneNumber << " ";
	address.saveToFile(file);
	file << " " << rating.ratingSum << " " << rating.ratingCount << " " << accountBalance << " " << isDriver << " " << available;
}

void Driver::readFromFile(std::ifstream& file) {
	file >> username >> password >> firstName >> lastName >> carNumber >> phoneNumber;
	MyString addressName;
	int x, y;
	address.readFromFile(file);
	file >> rating.ratingSum >> rating.ratingCount >> accountBalance >> isDriver >> available;
}

void Driver::splitString(const char* buff, size_t& buffInd, MyString& str) {
	size_t curInd = 0;
	while (buff[buffInd] != ',')
		str[curInd++] = buff[buffInd++];

	buffInd++;
}
