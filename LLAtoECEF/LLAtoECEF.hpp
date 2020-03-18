#ifndef WRITER_MEMORY_CLASS_H
#define WRITER_MEMORY_CLASS_H

#include <iostream>
#include <vector>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>

class WriterMemoryClass {
public:
	// Helper Class for reading result from remote host
	WriterMemoryClass();

	~WriterMemoryClass();

	void Reset();

	void* Realloc(void *ptr, size_t size);

	// Callback must be declared static, otherwise it won't link...
	size_t WriteMemoryCallback(char *ptr, size_t size, size_t nmemb);

	void print();

	std::string getCopyOfBufferAsString();

	// Public member vars
	char *m_pBuffer;
	size_t m_Size;
};

class SolrRequestClass {
public:

	static void createRequestor(curlpp::Easy *request,
			WriterMemoryClass *mWriterChunk);
	static std::string makeRequest(curlpp::Easy *request,
			WriterMemoryClass *mWriterChunk, std::string url);

};

// base
class LLAClass {
public:
	enum proj {
		LLA, ECEF, UNDEF
	};

	LLAClass();

	LLAClass(enum LLAClass::proj);

	virtual void PointFromString(std::string) = 0;
	virtual void PointFromVector(double, std::vector<double>) = 0;

	void setXYZ(double, std::vector<double>);

	void Print() const;

	double X() const;
	double Y() const;
	double Z() const;

	double calculateDistanceFromPreviousPoint(LLAClass*);

	double calculateTimeFromPreviousPoint(LLAClass*);

	double calculateVelocity(LLAClass*);

	enum LLAClass::proj getProj();

	double getTime();

	virtual ~LLAClass();

private:
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;

	double time = 0.0;

protected:
	proj p;
};

class LLASolrClass: public LLAClass {
private:
	void PointFromVector(double, std::vector<double>);
public:

	LLASolrClass();
	LLASolrClass(double, std::vector<double>, enum LLAClass::proj);
	LLASolrClass(std::string, enum LLAClass::proj);

	void PointFromString(std::string);
};

class LLACSVClass: public LLAClass {
private:
	std::vector<double> csvRowToVector(std::string s);

	void PointFromVector(double, std::vector<double>);
public:

	LLACSVClass();
	LLACSVClass(double, double, double, double, enum LLAClass::proj);
	LLACSVClass(double, std::vector<double>, enum LLAClass::proj);
	LLACSVClass(std::string, enum LLAClass::proj);

	void PointFromString(std::string);

};

class LLAUtility {
public:
	static std::vector<double> pointToECEF(double lat, double lon, double alt);
};

#endif
