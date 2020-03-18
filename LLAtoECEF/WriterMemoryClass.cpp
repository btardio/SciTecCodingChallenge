#include <iostream>
#include <cstdlib>
#include <cstring>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

#include "LLAtoECEF.hpp"

#define MAX_FILE_LENGTH 20000
#define END_PADDING 10

using namespace std;
using namespace curlpp::options;

// Helper Class for reading result from remote host
WriterMemoryClass::WriterMemoryClass() {
	this->m_pBuffer = NULL;
	this->m_pBuffer = (char*) malloc(MAX_FILE_LENGTH * sizeof(char));
	this->m_Size = 0;
}

WriterMemoryClass::~WriterMemoryClass() {
	if (this->m_pBuffer)
		free(this->m_pBuffer);
}

void WriterMemoryClass::Reset(){
	delete this->m_pBuffer;
	this->m_Size = 0;
	this->m_pBuffer = NULL;

}

void* WriterMemoryClass::Realloc(void *ptr, size_t size) {
	if (ptr)
		return realloc(ptr, size + END_PADDING);
	else
		return malloc(size + END_PADDING);
}

// Callback must be declared static, otherwise it won't link...
size_t WriterMemoryClass::WriteMemoryCallback(char *ptr, size_t size,
		size_t nmemb) {
	// Calculate the real size of the incoming buffer
	size_t realsize = size * nmemb;

	// (Re)Allocate memory for the buffer
	m_pBuffer = (char*) Realloc(m_pBuffer, m_Size + realsize);

	memset(m_pBuffer, '0', m_Size + realsize + END_PADDING);

	// Test if Buffer is initialized correctly & copy memory
	if (m_pBuffer == NULL) {
		realsize = 0;
	}

	memcpy(&(m_pBuffer[m_Size]), ptr, realsize);
	memcpy(&(m_pBuffer[m_Size+realsize-1]), "\0", 1);
	m_Size += realsize;

	// return the real size of the buffer...
	return realsize;
}

void WriterMemoryClass::print() {
	std::cout << "Size: " << m_Size << std::endl;
	std::cout << "Content: " << std::endl << m_pBuffer << std::endl;
}

std::string WriterMemoryClass::getCopyOfBufferAsString(){
	return std::string(this->m_pBuffer);
}

