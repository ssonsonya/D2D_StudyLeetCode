#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics()
{
	CreateSwapChain();
}

Graphics::~Graphics()
{
	// ComPtr auto release
}

void Graphics::Begin()
{
	SetViewport();
	SetBackBufferToRTV();
}

void Graphics::End()
{
	HRESULT hr = m_swapChain->Present(1, 0);
	CHECK(hr);
}

void Graphics::SetViewport(const float& width, const float& height)
{
	m_viewport.TopLeftX = 0.0f;
	m_viewport.TopLeftY = 0.0f;
	m_viewport.Width = width;
	m_viewport.Height = height;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
}

void Graphics::SetViewport()
{
	m_deviceContext->RSSetViewports(1, &m_viewport);
}

void Graphics::SetBackBufferToRTV()
{
	m_deviceContext->OMSetRenderTargets(1, m_rtv.GetAddressOf(), nullptr);
	m_deviceContext->ClearRenderTargetView(m_rtv.Get(), m_initBackground);
}

void Graphics::CreateRenderTargetView()
{
	ComPtr<ID3D11Texture2D> backBuffer = nullptr;

	HRESULT hr = m_swapChain->GetBuffer
	(
		0,
		__uuidof(ID3D11Texture2D),
		(void**)&backBuffer
	);
	CHECK(hr);

	hr = m_device->CreateRenderTargetView
	(
		backBuffer.Get(),
		nullptr,
		&m_rtv
	);
	CHECK(hr);
}

void Graphics::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

	//BufferDesc
	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//SampleDesc - Image Quality Level
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	//SwapChain Buffer
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 1;

	//Window Settings
	desc.OutputWindow = g_handle;
	desc.Windowed = true;

	//SwapEffect
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	vector<D3D_FEATURE_LEVEL> featureLevel
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	D3D_FEATURE_LEVEL currentFeature;

	//Create!
	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		featureLevel.data(),
		(UINT)featureLevel.size(),
		D3D11_SDK_VERSION,
		&desc,
		&m_swapChain,
		&m_device,
		&currentFeature,
		&m_deviceContext
	);
	CHECK(hr);

	//Set Swap Chain Buffer's Initial Size
	Resize(g_winWidth, g_winHeight);
}

/// <summary>
/// Deletes RenderTargetView and Resets BackBuffer, Viewport.
/// Called every WM_SIZE message recieved.
/// </summary>
/// <param name="width">LOWORD of WM_SIZE msg</param>
/// <param name="height">HIWORD of WM_SIZE msg</param>
void Graphics::Resize(const float& width, const float& height)
{
	//Delete Surface
	m_rtv.Reset();

	//Resize Buffer
	HRESULT hr = m_swapChain->ResizeBuffers
	(
		0,
		(UINT)width,
		(UINT)height,
		DXGI_FORMAT_UNKNOWN,
		0
	);
	CHECK(hr);

	//Re-Create RTV
	CreateRenderTargetView();

	//Re-SetViewport
	SetViewport(width, height);

	cout << "\n [ Graphics ] Window resized\n X : " << width << " , Y : " << height << '\n';
}

