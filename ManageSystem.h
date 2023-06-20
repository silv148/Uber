#pragma once
#include "System.h"
//github: https://github.com/silv148/Uber

class SystemManager {
private:
	void registerNewUser(System& system);
	void loginUser(System& system);
	void logoutUser(System& system);

	void createOrder(System& system);
	void checkOrder(System& system);
	void cancelOrder(System& system);
	void pay(System& system);
	void rate(System& system);
	void addMoney(System& system);

	void changeAddress(System& system);
	void checkMessages(System& system);
	void acceptOrder(System& system);
	void declineOrder(System& system);
	void finishOrder(System& system);
	void acceptPayment(System& system);

	void readFromFile(System& system);
	void saveToFile(System& system);

public:
	void run();
};