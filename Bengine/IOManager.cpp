#include "IOManager.h"

#include <fstream>

namespace Bengine {

	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
		//we read the files in binary
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		//find size of the file
		file.seekg(0, std::ios::end); //seek or move to the end of the file
		int fileSize = file.tellg(); //checks how many bytes before current location
		file.seekg(0, std::ios::beg); //go back at the beggining to read the file
		fileSize -= file.tellg(); //disregard file header

		buffer.resize(fileSize);

		//first param of fnc is a char*, an array of char. vector<unsigned char> is a wrapper around an array of unsigned char
		//so to get that array of char, we can call the address(first element in buffer) which is
		//a pointer to a char that is beggining the array
		//we cast it to a char* since the fnc wants a char* not a unsigned char*, but its same thing in our case
		file.read((char*)&(buffer[0]), fileSize);
		file.close();

		return true;
	}
}