#include "LLAtoECEF.hpp"

#include <iostream>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

void SolrRequestClass::createRequestor(curlpp::Easy *request, WriterMemoryClass *mWriterChunk) {

	try {
		//curlpp::Cleanup cleaner;

		// Set the writer callback to enable cURL
		// to write result in a memory area
		using namespace std::placeholders;

		// note: remember that the first parameter in a class method is the instance of the class
		curlpp::types::WriteFunctionFunctor functor = std::bind(
				&WriterMemoryClass::WriteMemoryCallback, mWriterChunk, _1, _2,
				_3);

		curlpp::options::WriteFunction *test =
				new curlpp::options::WriteFunction(functor);
		request->setOpt(test);

	} catch (curlpp::LogicError &e) {
		std::cout << e.what() << std::endl;
	}

	catch (curlpp::RuntimeError &e) {
		std::cout << e.what() << std::endl;
	}

}

std::string SolrRequestClass::makeRequest(curlpp::Easy *request, WriterMemoryClass *mWriterChunk, std::string url){

	mWriterChunk->Reset();

	curlpp::options::Url *myUrl;

	myUrl = new curlpp::options::Url(url);

	// Setting the URL to retrive.
	request->setOpt(*myUrl);
	request->perform();

	return mWriterChunk->getCopyOfBufferAsString();

}
