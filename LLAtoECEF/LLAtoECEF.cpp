#include <iostream>
#include <fstream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

#include "LLAtoECEF.hpp"

#define MAX_FILE_LENGTH 20000

using namespace std;
using namespace curlpp::options;

int main(int argc, char **argv) {
	cout << "Hello world\n";

	WriterMemoryClass mWriterChunk;
	curlpp::Easy request;

	SolrRequestClass::createRequestor(&request, &mWriterChunk);

	int i = 0;

	std::ifstream infile("../SciTec_code_problem_data.csv");

	LLASolrClass *llasolrLLA_previous = new LLASolrClass();
	LLASolrClass *llasolrECEF_previous = new LLASolrClass();
	LLACSVClass *llacsvLLA_previous = new LLACSVClass();
	LLACSVClass *llacsvECEF_previous = new LLACSVClass();

	for (std::string line; getline(infile, line);) {

		std::string url =
				"http://127.0.0.1:8983/solr/gettingstarted/select?q=id%3A"
						+ std::to_string(i);

		std::string solrline = SolrRequestClass::makeRequest(&request,
				&mWriterChunk, url);

		LLASolrClass *llasolrLLA = new LLASolrClass(solrline, LLAClass::LLA);
		LLASolrClass *llasolrECEF = new LLASolrClass(solrline, LLAClass::ECEF);

		LLACSVClass *llacsvLLA = new LLACSVClass(line, LLAClass::LLA);
		LLACSVClass *llacsvECEF = new LLACSVClass(llacsvLLA->getTime(),
				LLAUtility::pointToECEF(llacsvLLA->X(), llacsvLLA->Y(),
						llacsvLLA->Z()), LLAClass::ECEF);

		cout << std::endl << std::endl << "Point #" << std::to_string(i)
				<< std::endl;

		llacsvLLA->Print();
		llacsvECEF->Print();

		llasolrLLA->Print();
		llasolrECEF->Print();

		cout << "DistanceECEF: "
				<< llacsvECEF->calculateDistanceFromPreviousPoint(
						(LLAClass*) llacsvECEF_previous) << std::endl;
		cout << "DistanceECEF: "
				<< llasolrECEF->calculateDistanceFromPreviousPoint(
						(LLAClass*) llasolrECEF_previous) << std::endl;

		cout << "DistanceLLA: "
				<< llacsvLLA->calculateDistanceFromPreviousPoint(
						(LLAClass*) llacsvLLA_previous) << std::endl;
		cout << "DistanceLLA: "
				<< llasolrLLA->calculateDistanceFromPreviousPoint(
						(LLAClass*) llasolrLLA_previous) << std::endl;

		cout << "Time: "
				<< llacsvLLA->calculateTimeFromPreviousPoint(
						(LLAClass*) llacsvLLA_previous) << std::endl;

		cout << "VelocityECEF: "
				<< llacsvECEF->calculateVelocity(
						(LLAClass*) llacsvECEF_previous) << std::endl;
		cout << "VelocityECEF: "
				<< llasolrECEF->calculateVelocity(
						(LLAClass*) llasolrECEF_previous) << std::endl;

		cout << "VelocityLLA: "
				<< llacsvLLA->calculateVelocity((LLAClass*) llacsvLLA_previous)
				<< std::endl;
		cout << "VelocityLLA: "
				<< llasolrLLA->calculateVelocity(
						(LLAClass*) llasolrLLA_previous) << std::endl;

		delete llasolrLLA_previous;
		delete llasolrECEF_previous;
		delete llacsvLLA_previous;
		delete llacsvECEF_previous;

		llasolrLLA_previous = llasolrLLA;
		llasolrECEF_previous = llasolrECEF;
		llacsvLLA_previous = llacsvLLA;
		llacsvECEF_previous = llacsvECEF;

		i++;

	}
}
