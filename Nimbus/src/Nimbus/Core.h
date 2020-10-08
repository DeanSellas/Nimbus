#pragma once

namespace Nimbus
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
	class StringConverter
	{
	public:
		static std::wstring StringToWide(std::string str) { return std::wstring(str.begin(), str.end()); }
	};
}

