#pragma once

#include <vector>
#include <variant>
#include <cstdint>
#include <cstddef>

#include "Option.hpp"

namespace TPaCap
{

constexpr uint32_t MAGIC_NUMBER = 0x1A2B3C4D;
constexpr uint32_t REVERSED_MAGIC_NUMBER = 0x4D3C2B1A;


namespace Block
{

struct SectionHeader
{
	static constexpr uint32_t code = 0x0A0D0D0A;
	uint32_t magic_number;
	uint16_t major_version;
	uint16_t minor_version;
	int64_t section_length;
	std::vector<Option> options;
};

struct InterfaceDescription
{
	static constexpr uint32_t code = 0x00000001;
	uint16_t link_type;
	uint32_t max_packet_lenght;
	uint32_t id;
	std::vector<Option> options;
};

struct EnhancedPacket
{
	static constexpr uint32_t code = 0x00000006;
	uint32_t interface_id;
	uint64_t timestamp;
	uint32_t original_packet_length;
	std::vector<std::byte> data; // its size is captured_packet_length
	std::vector<Option> options;
};

struct SimplePacket
{
	static constexpr uint32_t code = 0x00000003;
	uint32_t original_packet_length;
	std::vector<std::byte> data;
	std::vector<Option> options;
};

struct NameResolution
{
	struct Record
	{

	};

	static constexpr uint32_t code = 0x00000004;
	std::vector<Record> records;
	std::vector<Option> options;
};

struct InterfaceStatistics
{
	static constexpr uint32_t code = 0x00000005;
	uint32_t interface_id;
	uint64_t timestamp;
	std::vector<Option> options;
};

struct SystemdJournalExport
{
	static constexpr uint32_t code = 0x00000009;
	std::byte* journal_entry; // Better type later
};

struct DecryptionSecrets
{
	static constexpr uint32_t code = 0x0000000A;
	uint32_t secret_type;
	std::vector<std::byte> secret; // later it this part will be parsed
	std::vector<Option> options;
};

struct Custom
{
	// Later make a structure with clever tricks to avoid this monstruosity
	static constexpr uint32_t code = 0x00000BAD;
	static constexpr uint32_t code2 = 0x40000BAD; 
	int32_t private_enterprise_number;
	std::vector<std::byte> custom_data;
	std::vector<Option> options;
};

using Block =
	std::variant
	<
		SectionHeader,
		InterfaceDescription,
		EnhancedPacket,
		SimplePacket,
		NameResolution,
		InterfaceStatistics,
		SystemdJournalExport,
		DecryptionSecrets,
		Custom
	>;

} // namespace Block


} // namespace TPaCap
