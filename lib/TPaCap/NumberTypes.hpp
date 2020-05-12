#pragma once

#include <cstdint>
#include <limits>
#include <stdexcept>

namespace TPaCap
{

constexpr uint8_t operator""_u8 (unsigned long long int value)
{
	if (value >= std::numeric_limits<uint8_t>::max())
		throw std::overflow_error("Value too high in literal");
	return static_cast<uint8_t>(value);
}

constexpr uint16_t operator""_u16 (unsigned long long int value)
{
	if (value >= std::numeric_limits<uint16_t>::max())
		throw std::overflow_error("Value too high in literal");
	return static_cast<uint16_t>(value);
}

constexpr uint32_t operator""_u32 (unsigned long long int value)
{
	if (value >= std::numeric_limits<uint32_t>::max())
		throw std::overflow_error("Value too high in literal");
	return static_cast<uint32_t>(value);
}

constexpr uint64_t operator""_u64 (unsigned long long int value)
{
	if (value >= std::numeric_limits<uint64_t>::max())
		throw std::overflow_error("Value too high in literal");
	return static_cast<uint64_t>(value);
}

constexpr int8_t operator""_i8 (unsigned long long int value)
{
	if (value >= std::numeric_limits<int8_t>::max())
		throw std::overflow_error("Value too high in literal");
	return static_cast<int8_t>(value);
}

constexpr int16_t operator""_i16 (unsigned long long int value)
{
	if (value >= std::numeric_limits<int16_t>::max())
		throw std::overflow_error("Value too high in literal");
	return static_cast<int16_t>(value);
}

constexpr int32_t operator""_i32 (unsigned long long int value)
{
	if (value >= std::numeric_limits<int32_t>::max())
		throw std::overflow_error("Value too high in literal");
	return static_cast<int32_t>(value);
}

constexpr int64_t operator""_i64 (unsigned long long int value)
{
	if (value >= static_cast<unsigned long long int>(std::numeric_limits<int64_t>::max()))
		throw std::overflow_error("Value too high in literal");
	return static_cast<int64_t>(value);
}

} // namespace TPaCap
