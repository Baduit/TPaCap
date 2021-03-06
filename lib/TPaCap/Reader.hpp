#pragma once

#include <cstddef>
#include <vector>

namespace TPaCap
{

template <typename T> // concept Integral???
void swap(T& value)
{
	std::byte* buffer = reinterpret_cast<std::byte*>(&value);
	std::reverse(buffer, buffer + sizeof(T));
}

struct NonOwningBuffer
{
	std::byte* data;
	std::size_t size;
};

class Reader
{
	public:
		bool need_swaping_endianess = false;

		template<typename T> // replace typename by integral concept?
		constexpr T	read(std::byte*& buffer, std::size_t& buffer_size)
		{
			T value{};
			std::memcpy(&value, buffer, sizeof(T));
			if (need_swaping_endianess)
				swap(value);
			buffer += sizeof(T);
			buffer_size -= sizeof(T);
			return value;
		}

		template <typename OutputContainer = std::vector<std::byte>> // TODO conceptify it as contiguous range
		OutputContainer read(std::byte*& buffer, std::size_t& buffer_size, std::size_t nb_byte)
		{
			using DataPtr = decltype(std::declval<OutputContainer>().data());
			OutputContainer result_buffer(reinterpret_cast<DataPtr>(buffer), reinterpret_cast<DataPtr>(buffer) + nb_byte);
			buffer += nb_byte;
			buffer_size -= nb_byte;
			return result_buffer;
		}

		template<std::size_t drop_size>
		constexpr void drop(std::byte*& buffer, std::size_t& buffer_size)
		{
			buffer += drop_size;
			buffer_size -= drop_size;
		}

		void drop(std::byte*& buffer, std::size_t& buffer_size, std::size_t drop_size)
		{
			buffer += drop_size;
			buffer_size -= drop_size;
		}
};

} // namespace TPaCap
