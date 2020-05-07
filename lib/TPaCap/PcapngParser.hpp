#pragma once

#include <vector>
#include <cstddef>
#include <cstring>

#include "BlockFactory.hpp"
#include "Reader.hpp"

namespace TPaCap
{

class PcapngParser
{
	public:
		void operator()(NonOwningBuffer buffer) // later use contiguous range instead, but genericity is for later
		{
			while (buffer.size >= MINIMUM_BLOCK_SIZE)
			{
				auto code = reader.read<uint32_t>(buffer.data, buffer.size);
				auto block = factory.create(code, buffer, reader);
				std::cout << block << std::endl;
			}
		}

	private:
		Reader reader;
		Block::Factory factory;


};

} // namespace TPaCap
