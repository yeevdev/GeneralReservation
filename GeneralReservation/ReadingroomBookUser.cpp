#include "ReadingroomBookUser.h"

ReadingroomBookUser::ReadingroomBookUser(string id, string password, string name) : User(id, password, name) {
	this->age = 0;
}

void ReadingroomBookUser::setAge(int age) {
	this->age = age;
}

int ReadingroomBookUser::getAge() {
	return this->age;
}

void ReadingroomBookUser::setPASSWORD(string password) {
	this->password = password;
}

bool ReadingroomBookUser::isSet() {
	return (this->password == "") ? false : true;
}

string ReadingroomBookUser::getGender() {
	return this->gender;
}

void ReadingroomBookUser::setGender(string gender) {
	this->gender = gender;
}
