#include <iostream>
#include <optional>
#include <filesystem>
#include <fstream>

#include <TPaCap/TPaCap.hpp>

namespace fs = std::filesystem;

inline std::optional<std::string>		readAllContent(std::string_view filename)
{
	std::ifstream	file(filename.data(), std::ios_base::binary);
	if (!file)
		return {};

	auto file_size = fs::file_size(filename);

	std::string file_content;
	file_content.resize(file_size);
	file.read(file_content.data(), static_cast<std::streamsize>(file_size));
	return file_content;
}

int main(int argc, char** argv)
{
    std::cout << "Hello, World !" << std::endl;

    if (argc >= 2)
    {
        auto file_content = readAllContent(argv[1]);
        if (!file_content)
        {
            std::cout << "This file does not exist" << std::endl;
            return EXIT_FAILURE;
        }
        TPaCap::PcapngParser parser;
        TPaCap::NonOwningBuffer buffer;
        buffer.data = reinterpret_cast<std::byte*>(file_content->data());
        buffer.size = file_content->size();

        try
        {
            parser(buffer);
        }
        catch (std::runtime_error& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    else
    {
        std::cout << "Give me a file to eat" << std::endl;
    }

    std::cout << "Bye, World !" << std::endl;
}
