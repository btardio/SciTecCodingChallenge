#include <iostream>
#include <vector>

#include <math.h>

#include <boost/tokenizer.hpp>

#include "LLAtoECEF.hpp"



std::vector<double> LLACSVClass::csvRowToVector(std::string s) {
	using namespace boost;

	std::vector<double> vec_tokens;

	typedef boost::tokenizer<boost::char_separator<char>> myTokenizer;

	boost::char_separator<char> separator(",");

	myTokenizer tokens(s, separator);

	myTokenizer::iterator itr = tokens.begin();

	for (; itr != tokens.end(); ++itr) {

		vec_tokens.push_back(stod(itr.current_token()));

	}

	return vec_tokens;
}

void LLACSVClass::PointFromVector(double time, std::vector<double> point) {
	this->setXYZ(time, point);
}

void LLACSVClass::PointFromString(std::string line) {
	std::vector<double> point = csvRowToVector(line);

	double time = point[0];

	point.erase(point.begin());

	this->PointFromVector(time, point);

}

LLACSVClass::LLACSVClass() {
}
LLACSVClass::LLACSVClass(double t, double x, double y, double z, enum LLAClass::proj p) :
	LLAClass(p){
	std::vector<double> v;
	v.push_back(x);
	v.push_back(y);
	v.push_back(z);
	this->setXYZ(t, v);
}

LLACSVClass::LLACSVClass(double d, std::vector<double> vec,
		enum LLAClass::proj p) :
		LLAClass(p) {
	this->PointFromVector(d, vec);
}
LLACSVClass::LLACSVClass(std::string line, enum LLAClass::proj p) :
		LLAClass(p) {
	this->PointFromString(line);
}

