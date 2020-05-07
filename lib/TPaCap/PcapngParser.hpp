#pragma once

#include <vector>
#include <cstddef>
#include <cstring>

namespace TPaCap
{

class PcapngParser
{
	public:
		void operator()(const std::vector<std::byte>& buffer) // later use contiguous range instead, but genericity is for later
		{

		}

	private:
		// Maybe this method should be in an other class
		template<typename T> // replace typename by integral concept?
		T	read(std::byte*& buffer)
		{
			T value{};
			// Later handle endianess
			std::memcpy(&value, buffer, sizeof(T));
			buffer += sizeof(T);
			return value;
		}

		std::vector<std::byte> read(std::byte*& buffer, std::size_t nb_byte)
		{
			std::vector<std::byte> result_buffer(buffer, buffer + nb_byte);
			buffer += nb_byte;
			return result_buffer;
		}


};

} // namespace TPaCap
