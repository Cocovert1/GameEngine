#pragma once

#include <vector>
#include <string>

namespace Bengine {

	class IOManager
	{
	public:
		//a static method can only be called once. This class is a static class, meaning we only need to make one instance of IOManager
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};
}

