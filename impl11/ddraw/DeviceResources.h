// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt

#pragma once

class PrimarySurface;
class DepthSurface;
class BackbufferSurface;
class FrontbufferSurface;
class OffscreenSurface;
class Direct3DExecuteBuffer;
class Direct3DTexture;

struct Float4
{
	float x, y, z, w;
};

class DeviceResources;

class StereoContext
{
public:
	StereoContext(DeviceResources* owner);

	void OnBeginFrame();
	void OnChangeDepthState(const D3D11_DEPTH_STENCIL_DESC& depthDesc);
	void OnDrawTriangles(const D3DTLVERTEX* vertices, const _D3DTRIANGLE* triangles, WORD triangleCount,
		ID3D11PixelShader* currentPixelShader, Direct3DTexture* currentTexture);
	void OnEndScene();

	float clearPackedDepth[4];

private:
	DeviceResources* _owner;

	// stereo fix
	bool _depthWriteEnabled;
	bool _depthTestEnabled;

	float _frameConvergence;
	float _frameSeparation;

	bool _startedHUD = false;
	bool _startedCrosshair = false;
	bool _startedDepthUse = false;
	bool _isFirstDrawCall = true;
	bool _isMapMode = false;

	friend class DeviceResources;
};


class DeviceResources
{
public:
	DeviceResources();
	~DeviceResources();

	HRESULT Initialize();

	HRESULT OnSizeChanged(HWND hWnd, DWORD dwWidth, DWORD dwHeight);

	HRESULT LoadMainResources();

	HRESULT LoadResources();

	HRESULT RenderMain(char* buffer, DWORD width, DWORD height, DWORD bpp, bool useColorKey = true);

	HRESULT RetrieveBackBuffer(char* buffer, DWORD width, DWORD height, DWORD bpp);

	UINT GetMaxAnisotropy();

	void CheckMultisamplingSupport();

	void DefaultSurfaceDesc(LPDDSURFACEDESC, DWORD caps);

	void ResolveBackBuffer();

	void SetViewport(DWORD width, DWORD height);

	DWORD _displayWidth;
	DWORD _displayHeight;
	DWORD _displayBpp;

	D3D_DRIVER_TYPE _d3dDriverType;
	D3D_FEATURE_LEVEL _d3dFeatureLevel;
	ComPtr<ID3D11Device> _d3dDevice;
	ComPtr<ID3D11DeviceContext> _d3dDeviceContext;
	ComPtr<IDXGISwapChain> _swapChain;
	ComPtr<IDXGIOutput> _output;
	ComPtr<ID3D11Texture2D> _backBuffer;
	ComPtr<ID3D11RenderTargetView> _backBufferRTV;
	ComPtr<ID3D11Texture2D> _offscreenBuffer;
	ComPtr<ID3D11RenderTargetView> _offscreenBufferRTV;
	ComPtr<ID3D11RenderTargetView> _offscreenBufferColorRTV;
	ComPtr<ID3D11RenderTargetView> _offscreenBufferDepthRTV;
	ComPtr<ID3D11Texture2D> _depthStencil;
	ComPtr<ID3D11DepthStencilView> _depthStencilDSV;
	ComPtr<ID3D11ShaderResourceView> _packedLinearDepthSRV;

	ComPtr<ID3D11Texture2D> _unpackedLinearDepth;
	ComPtr<ID3D11RenderTargetView> _unpackedLinearDepthRTV;
	ComPtr<ID3D11ShaderResourceView> _unpackedLinearDepthSRV;

	ComPtr<ID3D11VertexShader> _mainVertexShader;
	ComPtr<ID3D11InputLayout> _mainInputLayout;
	ComPtr<ID3D11GeometryShader> _mainGeometryShader;
	ComPtr<ID3D11PixelShader> _mainPixelShader;
	ComPtr<ID3D11RasterizerState> _mainRasterizerState;
	ComPtr<ID3D11SamplerState> _mainSamplerState;
	ComPtr<ID3D11BlendState> _mainBlendState;
	ComPtr<ID3D11DepthStencilState> _mainDepthState;
	ComPtr<ID3D11Buffer> _mainVertexBuffer;
	ComPtr<ID3D11Buffer> _mainIndexBuffer;
	ComPtr<ID3D11Texture2D> _mainDisplayTexture;
	ComPtr<ID3D11ShaderResourceView> _mainDisplayTextureView;

	ComPtr<ID3D11VertexShader> _vertexShaderUnpackDepth;
	ComPtr<ID3D11PixelShader> _pixelShaderUnpackDepth;

	ComPtr<ID3D11VertexShader> _vertexShader;
	ComPtr<ID3D11InputLayout> _inputLayout;
	ComPtr<ID3D11GeometryShader> _geometryShader;
	ComPtr<ID3D11PixelShader> _pixelShaderTexture;
	ComPtr<ID3D11PixelShader> _pixelShaderAtestTexture;
	ComPtr<ID3D11PixelShader> _pixelShaderAtestTextureNoAlpha;
	ComPtr<ID3D11PixelShader> _pixelShaderSolid;
	ComPtr<ID3D11RasterizerState> _rasterizerState;
	ComPtr<ID3D11Buffer> _vsConstantBuffer;
	ComPtr<ID3D11Buffer> _gsConstantBuffer;


	BOOL _useAnisotropy;
	BOOL _useMultisampling;
	DXGI_SAMPLE_DESC _sampleDesc;
	UINT _backbufferWidth;
	UINT _backbufferHeight;
	DXGI_RATIONAL _refreshRate;

	float clearColor[4];
	bool clearColorSet;
	float clearDepth;
	bool clearDepthSet;
	bool sceneRendered;
	bool sceneRenderedEmpty;
	bool inScene;
	bool inSceneBackbufferLocked;

	PrimarySurface* _primarySurface;
	DepthSurface* _depthSurface;
	BackbufferSurface* _backbufferSurface;
	FrontbufferSurface* _frontbufferSurface;
	OffscreenSurface* _offscreenSurface;

	// stereo
	bool _isStereoEnabled;
	void* _stereoHandle;
	StereoContext _stereoContext;
};
