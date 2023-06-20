#include "Address.h"
#include <fstream>

double Address::Point::getDist(const Point& other) const {
	int dx = x - other.x;
	int dy = y - other.y;
	return sqrt(dx * dx + dy * dy);
}

Address::Address(const MyString& addressName, int x, int y, const MyString& additionalInfo) {
	setAddress(addressName, x, y, additionalInfo);
}

void Address::setAddress(const MyString& addressName, int x, int y, const MyString& additionalInfo) {
	this->addressName = addressName;
	point.x = x;
	point.y = y;
	this->additionalInfo = additionalInfo;
}

double Address::getDist(const Address& other) const {
	return point.getDist(other.getPoint());
}

const Address::Point& Address::getPoint() const {
	return point;
}

const MyString& Address::getName() const {
	return addressName;
}

const MyString& Address::getAdditionalInfo() const {
	return additionalInfo;
}

void Address::printAddress() {
	std::cout << addressName << " " << point.x << " " << point.y
		<< " " << additionalInfo << std::endl;
}

void Address::saveToFile(std::ofstream& file) {
	addressName == "\0" ? file << "//" : file << addressName;
	file << " " << point.x << " " << point.y << " ";
	file << additionalInfo << " " << "//";
}

void Address::readFromFile(std::ifstream& file) {
	file >> addressName >> point.x >> point.y;
	MyString next;
	file >> next;
	while(next!="//") {
		additionalInfo += next;
		file >> next;
	}
}
