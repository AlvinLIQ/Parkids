#include "DrnD2D.h"


using namespace Microsoft::WRL;

DrnD2D::DrnD2D(HWND Hwnd)
{
    hwnd = Hwnd;
	InitD2D();
}

DrnD2D::~DrnD2D()
{
    
}

void DrnD2D::InitD2D()
{
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1
    };
    D3D_FEATURE_LEVEL m_featureLevels;
    D3D11CreateDevice(
        nullptr, D3D_DRIVER_TYPE_HARDWARE,
        0, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        featureLevels, ARRAYSIZE(featureLevels),
        D3D11_SDK_VERSION, d3dDevice.GetAddressOf(),
        &m_featureLevels, d3dContext.GetAddressOf());

    d3dDevice.As(&dxgiDevice);
    dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf());
    dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf()));
    
    swapChainDesc.Width = 0;                           // use automatic sizing
    swapChainDesc.Height = 0;
    swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // this is the most common swapchain format
    swapChainDesc.Stereo = false;
    swapChainDesc.SampleDesc.Count = 1;                // don't use multi-sampling
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2;                     // use double buffering to enable flip
    swapChainDesc.Scaling = DXGI_SCALING_NONE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // all apps must use this SwapEffect
    swapChainDesc.Flags = 0;

    dxgiFactory->CreateSwapChainForHwnd(d3dDevice.Get(), hwnd, &swapChainDesc, nullptr, nullptr, dxgiSwapChain.GetAddressOf());

    D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, d2dFactory.GetAddressOf());
    d2dFactory->CreateDevice(dxgiDevice.Get(), d2dDevice.GetAddressOf());
    d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, d2dContext.GetAddressOf());

    SetTargetBitmap();

    CoInitialize(NULL);
    CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory));

	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(wrtFactory), reinterpret_cast<IUnknown**>(wrtFactory.GetAddressOf()));
    wrtFactory->GetSystemFontCollection(&fonts);
	wrtFactory->CreateTextFormat(L"Source Code Variable", fonts.Get(), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 18, L"", &txtFormat);

}

void DrnD2D::SetTargetBitmap()
{
    dxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiSurface));

    D2D1_PIXEL_FORMAT pixelFormat = D2D1::PixelFormat(
        DXGI_FORMAT_B8G8R8A8_UNORM,
        D2D1_ALPHA_MODE_PREMULTIPLIED
    );
    D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
        pixelFormat, 96, 96);

    ComPtr<ID2D1Bitmap1> d2dBitmap;
    d2dContext->CreateBitmapFromDxgiSurface(dxgiSurface.Get(), &bitmapProperties, &d2dBitmap);
    d2dContext->SetTarget(d2dBitmap.Get());
}