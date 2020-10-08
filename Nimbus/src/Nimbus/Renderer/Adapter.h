#pragma once
namespace Nimbus
{
	class AdapterData
	{
	public:
		AdapterData(IDXGIAdapter* pAdapter);
		IDXGIAdapter* pAdapter = nullptr;
		DXGI_ADAPTER_DESC description;
	};

	class Adapter
	{
	public:
		static std::vector<AdapterData> GetAdapterData();
	private:
		static std::vector<AdapterData> adapters;
	};
}