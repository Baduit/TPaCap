#pragma

#include <string>
#include <string_view>

namespace TPaCap
{

namespace IpAddr
{

class IpV4
{
	public:
		IpV4() = default;

		IpV4(const IpV4&) = default;
		IpV4& operator=(const IpV4&) = default;

		IpV4(IpV4&&) = default;
		IpV4& operator=(IpV4&&) = default;

		IpV4(std::string_view addr):
			_addr(addr)
		{}

		IpV4(std::string&& addr):
			_addr(std::move(addr))
		{}

		~IpV4() = default;

		std::string_view get_addr_as_string() const
		{
			return _addr;
		}

	private:
		std::string _addr = "0.0.0.0"; // Use std::array<uint8_t, 4> ?
};

class IpV6
{
	public:
		IpV6() = default;

		IpV6(const IpV6&) = default;
		IpV6& operator=(const IpV6&) = default;

		IpV6(IpV6&&) = default;
		IpV6& operator=(IpV6&&) = default;

		IpV6(std::string_view IpV6):
			_addr(IpV6)
		{}

		IpV6(std::string&& addr):
			_addr(std::move(addr))
		{}

		~IpV6() = default;

		std::string_view get_addr_as_string() const
		{
			return _addr;
		}

	private:
		std::string _addr = "::/0"; // use static_string ?
};

} // namespace IpAddr


} // namespace TPaCap
