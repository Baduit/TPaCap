#pragma once

#include <fstream>

#include "Blocks.hpp"

namespace TPaCap
{

namespace Block
{

inline std::ostream& operator<<(std::ostream& os, const SectionHeader& b)
{
	os
		<< "[" << "SectionHeader" << "]"
		<< "{\n"
		<< "\t" << "magic_number: " << b.magic_number << "\n"
		<< "\t" << "major_version: " << b.major_version << "\n"
		<< "\t" << "minor_version: " << b.minor_version << "\n"
		<< "\t" << "section_length: " << b.section_length << "\n"
		<< "}" << std::endl;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const InterfaceDescription& b)
{
	os
		<< "[" << "InterfaceDescription" << "]"
		<< "{\n"
		<< "\t" << "link_type: " << b.link_type << "\n"
		<< "\t" << "max_packet_lenght: " << b.max_packet_lenght << "\n"
		<< "\t" << "id: " << b.id << "\n"
		<< "}" << std::endl;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const EnhancedPacket& b)
{
	os
		<< "[" << "EnhancedPacket" << "]"
		<< "{\n"
		<< "\t" << "interface_id: " << b.interface_id << "\n"
		<< "\t" << "timestamp: " << b.timestamp << "\n"
		<< "\t" << "original_packet_length: " << b.original_packet_length << "\n"
		<< "\t" << "data.size: " << b.data.size() << "\n"
		<< "}" << std::endl;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const SimplePacket& b)
{
	os
		<< "[" << "SimplePacket" << "]"
		<< "{\n"
		<< "\t" << "original_packet_length: " << b.original_packet_length << "\n"
		<< "\t" << "data.size: " << b.data.size() << "\n"
		<< "}" << std::endl;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const NameResolution& b)
{
	os
		<< "[" << "NameResolution" << "]"
		<< "{\n"
		<< "}" << std::endl;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const InterfaceStatistics& b)
{
	os
		<< "[" << "InterfaceStatistics" << "]"
		<< "{\n"
		<< "\t" << "interface_id: " << b.interface_id << "\n"
		<< "\t" << "timestamp: " << b.timestamp << "\n"
		<< "}" << std::endl;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const SystemdJournalExport& b)
{
	os
		<< "[" << "SystemdJournalExport" << "]"
		<< "{\n"
		<< "\t" << "journal_entry.size: " << b.journal_entry.size() << "\n"
		<< "}" << std::endl;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const DecryptionSecrets& b)
{
	os
		<< "[" << "DecryptionSecrets" << "]"
		<< "{\n"
		<< "\t" << "secret_type: " << b.secret_type << "\n"
		<< "\t" << "secret.size: " << b.secret.size() << "\n"
		<< "}" << std::endl;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const Custom& b)
{
	os
		<< "[" << "Custom" << "]"
		<< "{\n"
		<< "\t" << "private_enterprise_number: " << b.private_enterprise_number << "\n"
		<< "\t" << "custom_data.size: " << b.custom_data.size() << "\n"
		<< "}" << std::endl;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const Block& block)
{
	std::visit(
		[&](const auto& b)
		{
			os << b;
		}, block
	);
	return os;
}

} // namespace Block


} // namespace TPaCap
