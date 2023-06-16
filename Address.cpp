#include "Address.h"

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
