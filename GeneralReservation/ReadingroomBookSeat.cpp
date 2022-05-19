#include "ReadingroomBookSeat.h"

ReadingroomBookSeat::ReadingroomBookSeat() {
	//this->customerID = "";

	for (int i = 0; i < 14; i++) {
		reservedTime[i] = "";
	}
	//this->reserved = false;
}

void ReadingroomBookSeat::reserve(string id, int start, int end) {
	for (int i = start - 9; i <= end - 10; i++) {
		this->reservedTime[i] = id;
	}
}

void ReadingroomBookSeat::cancel(string id) {
	for (auto& time : this->reservedTime) {
		if (time == id) {
			time = "";
		}
	}
}

bool ReadingroomBookSeat::isReserved(int time) {
	if (this->reservedTime[time - 1] == "") {
		return false;
	}
	else {
		return true;
	}
}

string ReadingroomBookSeat::getCustomerID(int time) {
	return this->reservedTime[time - 1];
}