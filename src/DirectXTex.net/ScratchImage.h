// DirectXTexSharp.h

#pragma once

using namespace System;

// Forward decls.
namespace DirectX
{
	class ScratchImage;
}

namespace DirectXTexNet
{

// Mirror of DirectXTex ScratchImage class.
public ref class ScratchImage : public IDisposable
{
public:
	// Create a D3D11 texture from the image.
	IntPtr CreateTexture(IntPtr device);

	// Generate mipmaps for this image.
	void GenerateMipMaps();

	// Create an empty mip chain for this image.
	void CreateEmptyMipChain();

	~ScratchImage();

internal:
	ScratchImage();

	DirectX::ScratchImage* GetScratchImage() { return scratchImage_; }

private:
	DirectX::ScratchImage* scratchImage_;
};

}
