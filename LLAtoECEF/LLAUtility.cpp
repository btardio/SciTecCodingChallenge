#include <math.h>
#include "LLAtoECEF.hpp"

std::vector<double> LLAUtility::pointToECEF(double lat, double lon, double alt) {

	std::vector<double> vec_ecef;

	double rad_lat = lat * (M_PI / 180.0);
	double rad_lon = lon * (M_PI / 180.0);

	double a = 6378137.0;
	double finv = 298.257223563;
	double f = 1 / finv;
	double e2 = 1 - (1 - f) * (1 - f);
	double v = a / sqrt(1 - e2 * sin(rad_lat) * sin(rad_lat));

	double x = (v + alt) * cos(rad_lat) * cos(rad_lon);
	double y = (v + alt) * cos(rad_lat) * sin(rad_lon);
	double z = (v * (1 - e2) + alt) * sin(rad_lat);

	vec_ecef.push_back(x);
	vec_ecef.push_back(y);
	vec_ecef.push_back(z);

	return vec_ecef;
}
