#pragma once

/// <summary>
/// (Singleton) Creates and Manages Device, DeviceContext, SwapChain, Viewport, RenderTargetView. 
/// Generated as program start and Callable from everywhere.
/// </summary>
class Graphics
{
	DECLARE_SINGLETON(Graphics);

public:
	void Begin();
	void End();

public: // Getter
	ComPtr<ID3D11Device> GetDevice() const { return m_device; }
	ComPtr<ID3D11DeviceContext> GetDC() const { return m_deviceContext; }
	Color GetClearColor() { return m_initBackground; }

public: // Setter
	void SetViewport(const float& width, const float& height);
	void SetViewport();
	void SetBackBufferToRTV();
	void CreateRenderTargetView();
	void Resize(const float& width, const float& height);

private:
	void CreateSwapChain();

private:
	ComPtr<ID3D11Device> m_device = nullptr;
	ComPtr<ID3D11DeviceContext> m_deviceContext = nullptr;
	ComPtr<IDXGISwapChain> m_swapChain = nullptr;
	ComPtr<ID3D11RenderTargetView> m_rtv = nullptr;
	D3D11_VIEWPORT m_viewport = { 0 };
	Color m_initBackground = { 0.3f,0.3f,0.3f,1.0f };
};