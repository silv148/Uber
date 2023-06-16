#pragma once
#include "MyString.h"

class Address {
private:
    struct Point
    {
        int x = 0;
        int y = 0;
        Point() = default;
        Point(int x, int y) : x(x), y(y) {}
        double getDist(const Point& other) const;
    } point;

	MyString addressName = "";
	MyString additionalInfo = "";

public:

    Address() = default;

    Address(const MyString& addressName,
            int x,
            int y,
            const MyString& additionalInfo = "");

    void setAddress(const MyString& addressName,
                    int x,
                    int y,
                    const MyString& additionalInfo = "");

    double getDist(const Address& other) const;
    const Point& getPoint() const;
    const MyString& getName() const;
    const MyString& getAdditionalInfo() const;

    void printAddress();
};

