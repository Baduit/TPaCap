#pragma once

#include <stdexcept>
#include <string>

#include "Blocks.hpp"
#include "Reader.hpp"
#include "BlockToStream.hpp"
#include "NumberTypes.hpp"

namespace TPaCap
{

namespace Block
{

class Factory
{
	public:
		Block create(uint32_t code, NonOwningBuffer& buffer, Reader& reader)
		{
			switch (code)
			{
				case SectionHeader::code:
				{
					return create_section_header(buffer, reader);
				}
				case InterfaceDescription::code:
				{
					return create_interface_description(buffer, reader);
				}
				case EnhancedPacket::code:
				{
					return create_enhanced_packet(buffer, reader);
				}
				case SimplePacket::code:
				{
					return create_simple_packet(buffer, reader);
				}
				case NameResolution::code:
				{
					return create_name_resolution(buffer, reader);
				}
				case InterfaceStatistics::code:
				{
					return create_interface_statistics(buffer, reader);
				}
				case SystemdJournalExport::code:
				{
					return create_systemd_journal_export(buffer, reader);
				}
				case DecryptionSecrets::code:
				{
					return create_description_secret(buffer, reader);
				}
				case Custom::code:
				case Custom::code2:
				{
					return create_custom(buffer, reader);
				}
				
				default:
				{
					throw std::runtime_error("Unknown block code: " + std::to_string(code));
					break;
				}
			}
		}
	private:
		template <typename B>
		void read_options(B& block, NonOwningBuffer& buffer, Reader& reader, std::size_t options_length)
		{
			// TODO, for now it just read it but it does not parse it
			reader.read(buffer.data, buffer.size, options_length);
		}

		constexpr void read_block_size_at_the_end(NonOwningBuffer& buffer, Reader& reader, std::size_t block_size_at_the_beginning)
		{
			auto block_size_at_the_end = reader.read<uint32_t>(buffer.data, buffer.size);
			if (block_size_at_the_beginning != block_size_at_the_end)
				throw std::runtime_error("Mismatch block size");
		}

		template <typename T> // TODO: use integral concept
		constexpr T pad_value(T value, T padding_size)
		{
			return value + (padding_size - value % padding_size);
		}

		SectionHeader create_section_header(NonOwningBuffer& buffer, Reader& reader)
		{
			SectionHeader block{};

			auto block_size = reader.read<uint32_t>(buffer.data, buffer.size);
			auto old_buffer_size = buffer.size;

			block.magic_number = reader.read<uint32_t>(buffer.data, buffer.size);
			if (block.magic_number == REVERSED_MAGIC_NUMBER)
			{
				reader.need_swaping_endianess = true;
				swap(block_size);
			}
			else
			{
				reader.need_swaping_endianess = false;
			}

			block.major_version = reader.read<uint16_t>(buffer.data, buffer.size);
			block.minor_version = reader.read<uint16_t>(buffer.data, buffer.size);
			block.section_length = reader.read<int64_t>(buffer.data, buffer.size);

			read_options(block, buffer, reader, block_size - MINIMUM_BLOCK_SIZE - (old_buffer_size - buffer.size));
			read_block_size_at_the_end(buffer, reader, block_size);

			_next_interface_description_id = 0;

			return block;
		}

		InterfaceDescription create_interface_description(NonOwningBuffer& buffer, Reader& reader)
		{
			InterfaceDescription block{};

			auto block_size = reader.read<uint32_t>(buffer.data, buffer.size);
			auto old_buffer_size = buffer.size;

			block.link_type = reader.read<uint16_t>(buffer.data, buffer.size);
			reader.drop<sizeof(uint16_t)>(buffer.data, buffer.size);
			block.max_packet_lenght = reader.read<uint32_t>(buffer.data, buffer.size);

			read_options(block, buffer, reader, block_size - MINIMUM_BLOCK_SIZE - (old_buffer_size - buffer.size));
			read_block_size_at_the_end(buffer, reader, block_size);

			block.id = _next_interface_description_id++;

			return block;
		}

		EnhancedPacket create_enhanced_packet(NonOwningBuffer& buffer, Reader& reader)
		{
			EnhancedPacket block{};

			auto block_size = reader.read<uint32_t>(buffer.data, buffer.size);
			auto old_buffer_size = buffer.size;

			block.interface_id = reader.read<uint32_t>(buffer.data, buffer.size);

			uint64_t high_ts = reader.read<uint32_t>(buffer.data, buffer.size);
			uint64_t low_ts = reader.read<uint32_t>(buffer.data, buffer.size);
			block.timestamp = (high_ts << 32) | low_ts;

			block.original_packet_length = reader.read<uint32_t>(buffer.data, buffer.size);

			auto captured_packet_length = reader.read<uint32_t>(buffer.data, buffer.size);
			block.data = reader.read(buffer.data, buffer.size, captured_packet_length);

			read_options(block, buffer, reader, block_size - MINIMUM_BLOCK_SIZE - (old_buffer_size - buffer.size));
			read_block_size_at_the_end(buffer, reader, block_size);

			return block;
		}

		SimplePacket create_simple_packet(NonOwningBuffer& buffer, Reader& reader)
		{
			SimplePacket block{};

			auto block_size = reader.read<uint32_t>(buffer.data, buffer.size);
			auto old_buffer_size = buffer.size;

			block.original_packet_length = reader.read<uint32_t>(buffer.data, buffer.size);
			block.data = reader.read(buffer.data, buffer.size, block_size - MINIMUM_BLOCK_SIZE - (old_buffer_size - buffer.size));

			read_block_size_at_the_end(buffer, reader, block_size);

			return block;
		}

		NameResolution create_name_resolution(NonOwningBuffer& buffer, Reader& reader)
		{
			NameResolution block{};

			auto block_size = reader.read<uint32_t>(buffer.data, buffer.size);

			while (true)
			{
				auto record_code = reader.read<uint16_t>(buffer.data, buffer.size);
				auto record_size = reader.read<uint16_t>(buffer.data, buffer.size);
				if (record_code == NameResolution::EndRecord::code)
					break;
				if (record_code == NameResolution::IPV4Record::code)
					block.records.push_back(NameResolution::IPV4Record{reader.read<std::string>(buffer.data, buffer.size, pad_value(record_size, 32_u16))}); // TODO: create a padding method
				else if (record_code == NameResolution::IPV6Record::code)
					block.records.push_back(NameResolution::IPV6Record{reader.read<std::string>(buffer.data, buffer.size, pad_value(record_size, 32_u16))}); // TODO: create a padding method
				else
					throw std::runtime_error("Unknown record code.");
			}
			
				
			// Todo: this is temporary
			reader.read(buffer.data, buffer.size, block_size - MINIMUM_BLOCK_SIZE);
			read_block_size_at_the_end(buffer, reader, block_size);

			return block;
		}

		InterfaceStatistics create_interface_statistics(NonOwningBuffer& buffer, Reader& reader)
		{
			InterfaceStatistics block{};
			
			auto block_size = reader.read<uint32_t>(buffer.data, buffer.size);
			auto old_buffer_size = buffer.size;

			block.interface_id = reader.read<uint32_t>(buffer.data, buffer.size);

			uint64_t high_ts = reader.read<uint32_t>(buffer.data, buffer.size);
			uint64_t low_ts = reader.read<uint32_t>(buffer.data, buffer.size);
			block.timestamp = (high_ts << 32) | low_ts; 

			read_options(block, buffer, reader, block_size - MINIMUM_BLOCK_SIZE - (old_buffer_size - buffer.size));
			read_block_size_at_the_end(buffer, reader, block_size);

			return block;
		}

		SystemdJournalExport create_systemd_journal_export(NonOwningBuffer& buffer, Reader& reader)
		{
			SystemdJournalExport block{};
			
			auto block_size = reader.read<uint32_t>(buffer.data, buffer.size);

			block.journal_entry = reader.read(buffer.data, buffer.size, block_size - MINIMUM_BLOCK_SIZE);

			read_block_size_at_the_end(buffer, reader, block_size);

			return block;
		}

		DecryptionSecrets create_description_secret(NonOwningBuffer& buffer, Reader& reader)
		{
			DecryptionSecrets block{};
			
			auto block_size = reader.read<uint32_t>(buffer.data, buffer.size);
			auto old_buffer_size = buffer.size;

			block.secret_type = reader.read<uint32_t>(buffer.data, buffer.size);


			auto secret_size = reader.read<uint32_t>(buffer.data, buffer.size);
			block.secret = reader.read(buffer.data, buffer.size, secret_size);

			read_options(block, buffer, reader, block_size - MINIMUM_BLOCK_SIZE - (old_buffer_size - buffer.size));
			read_block_size_at_the_end(buffer, reader, block_size);

			return block;
		}

		Custom create_custom(NonOwningBuffer& buffer, Reader& reader)
		{
			Custom block{};
			
			auto block_size = reader.read<uint32_t>(buffer.data, buffer.size);
			auto old_buffer_size = buffer.size;

			block.private_enterprise_number = reader.read<uint32_t>(buffer.data, buffer.size);

			// Option datas are for now in the custom data because it is not possible to know where it begins...
			block.custom_data = reader.read(buffer.data, buffer.size, block_size - MINIMUM_BLOCK_SIZE - (old_buffer_size - buffer.size));

			read_block_size_at_the_end(buffer, reader, block_size);

			return block;
		}

	private:
		unsigned int _next_interface_description_id = 0;
};

} // namespace Block


} // namespace TPaCap
