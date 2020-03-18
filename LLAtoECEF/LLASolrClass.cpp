#include <iostream>
#include <vector>
#include "json/json.h"
#include "LLAtoECEF.hpp"

void LLASolrClass::PointFromVector(double time, std::vector<double> point) {
	this->setXYZ(time, point);
}

void LLASolrClass::PointFromString(std::string line) {
	std::vector<double> point;

	JSONCPP_STRING err;
	Json::Value root;

	const auto rawJsonLength = static_cast<int>(line.length());

	Json::CharReaderBuilder builder;
	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(line.c_str(), line.c_str() + rawJsonLength, &root,
			&err)) {
		std::cout << "error" << std::endl;
		exit(0);
	}

	Json::Value response = root["response"]["docs"][0];

	if (this->p == LLAClass::proj::ECEF) {
		Json::Value xyzECEF_0_d = response["xyzECEF_0_d"];
		Json::Value xyzECEF_1_d = response["xyzECEF_1_d"];
		Json::Value xyzECEF_2_d = response["xyzECEF_2_d"];
		point.push_back(xyzECEF_0_d.asDouble());
		point.push_back(xyzECEF_1_d.asDouble());
		point.push_back(xyzECEF_2_d.asDouble());

	} else {
		Json::Value xyzLLA_0_d = response["xyzLLA_0_d"];
		Json::Value xyzLLA_1_d = response["xyzLLA_1_d"];
		Json::Value xyzLLA_2_d = response["xyzLLA_2_d"];
		point.push_back(xyzLLA_0_d.asDouble());
		point.push_back(xyzLLA_1_d.asDouble());
		point.push_back(xyzLLA_2_d.asDouble());
	}

	double time = response["time"].asDouble();

	this->PointFromVector(time, point);

}

LLASolrClass::LLASolrClass() {
}
LLASolrClass::LLASolrClass(double d, std::vector<double> vec,
		enum LLAClass::proj p) :
		LLAClass(p) {
	this->PointFromVector(d, vec);
}
LLASolrClass::LLASolrClass(std::string s, enum LLAClass::proj p) :
		LLAClass(p) {

	this->PointFromString(s);

}

