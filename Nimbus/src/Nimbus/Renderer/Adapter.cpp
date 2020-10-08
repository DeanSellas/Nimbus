#include "pch.h"
#include "Adapter.h"
namespace Nimbus
{
	std::vector<AdapterData> Adapter::adapters;

	std::vector<AdapterData> Adapter::GetAdapterData() {
		if(adapters.size() > 0)
		{
			return adapters;
		}

		Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;

		// Create a DXGI Factory
		HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));
		if(FAILED(hr))
		{

			NIM_CORE_LOG->error("Failed to create DXGIFactory");
			exit(-1);
		}

		IDXGIAdapter* pAdapter;
		UINT index = 0;
		while(SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
		{
			adapters.push_back(AdapterData(pAdapter));
			index++;
		}
		return adapters;
	}

	AdapterData::AdapterData(IDXGIAdapter* pAdapter) {
		this->pAdapter = pAdapter;
		HRESULT hr = pAdapter->GetDesc(&description);
		if(FAILED(hr))
		{
			NIM_CORE_LOG->error("Failed to get description for IDXGI Adapter");
		}
	}
}
