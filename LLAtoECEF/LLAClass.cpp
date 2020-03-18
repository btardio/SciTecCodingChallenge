#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
#include "LLAtoECEF.hpp"

double LLAClass::X() const {
	return this->x;
}
double LLAClass::Y() const {
	return this->y;
}
double LLAClass::Z() const {
	return this->z;
}

void LLAClass::Print() const {
	std::cout << std::fixed << std::setprecision(10) << "LLA @ " << this->time
			<< " : " << this->x << "," << this->y << "," << this->z
			<< std::endl;

}

double LLAClass::calculateDistanceFromPreviousPoint(LLAClass *point) {
	return pow(
			pow(point->x - this->x, 2) + pow(point->y - this->y, 2)
					+ pow(point->z - this->z, 2), 0.5);
}


double LLAClass::calculateVelocity(LLAClass *p) {
	double d = calculateDistanceFromPreviousPoint(p);

	double t = calculateTimeFromPreviousPoint(p);

	return abs(d / t);
}

double LLAClass::calculateTimeFromPreviousPoint(LLAClass *p) {
	return p->time - this->time;
}

void LLAClass::setXYZ(double time, std::vector<double> point) {

	this->time = time;

	this->x = point[0];
	this->y = point[1];
	this->z = point[2];

}

double LLAClass::getTime(){
	return this->time;
}

LLAClass::LLAClass(){
	this->p = UNDEF;
}

LLAClass::LLAClass(enum LLAClass::proj p) {
	this->p = p;
}

LLAClass::~LLAClass() {
}

enum LLAClass::proj LLAClass::getProj(void) {
	return this->p;
}
