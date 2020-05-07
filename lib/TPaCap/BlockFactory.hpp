#pragma once

#include <stdexcept>
#include <string>

#include "Blocks.hpp"

namespace TPaCap
{

namespace Block
{

class Factory
{
	public:
		Block create(uint32_t code, const std::vector<std::byte>& buffer)
		{
			switch (code)
			{
				case SectionHeader::code:
				{
					return create_section_header(buffer);
				}
				case InterfaceDescription::code:
				{
					return create_interface_description(buffer);
				}
				case EnhancedPacket::code:
				{
					return create_enhanced_packet(buffer);
				}
				case SimplePacket::code:
				{
					return create_simple_packet(buffer);
				}
				case NameResolution::code:
				{
					return create_name_resolution(buffer);
				}
				case InterfaceStatistics::code:
				{
					return create_interface_statistics(buffer);
				}
				case SystemdJournalExport::code:
				{
					return create_systemd_journal_export(buffer);
				}
				case DecryptionSecrets::code:
				{
					return create_description_secret(buffer);
				}
				case Custom::code:
				case Custom::code2:
				{
					return create_custom(buffer);
				}
				
				default:
				{
					throw std::runtime_error("Unknown block code: " + std::to_string(code));
					break;
				}
			}
		}
	private:
		SectionHeader create_section_header(const std::vector<std::byte>& buffer)
		{
			SectionHeader block;
			return block;
		}

		InterfaceDescription create_interface_description(const std::vector<std::byte>& buffer)
		{
			InterfaceDescription block;
			return block;
		}

		EnhancedPacket create_enhanced_packet(const std::vector<std::byte>& buffer)
		{
			EnhancedPacket block;
			return block;
		}

		SimplePacket create_simple_packet(const std::vector<std::byte>& buffer)
		{
			SimplePacket block;
			return block;
		}

		NameResolution create_name_resolution(const std::vector<std::byte>& buffer)
		{
			NameResolution block;
			return block;
		}

		InterfaceStatistics create_interface_statistics(const std::vector<std::byte>& buffer)
		{
			InterfaceStatistics block;
			return block;
		}

		SystemdJournalExport create_systemd_journal_export(const std::vector<std::byte>& buffer)
		{
			SystemdJournalExport block;
			return block;
		}

		DecryptionSecrets create_description_secret(const std::vector<std::byte>& buffer)
		{
			DecryptionSecrets block;
			return block;
		}

		Custom create_custom(const std::vector<std::byte>& buffer)
		{
			Custom block;
			return block;
		}
};

} // namespace Block


} // namespace TPaCap
