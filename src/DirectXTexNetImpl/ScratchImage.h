// DirectXTexSharp.h

#pragma once

#include "TexMetadata.h"

using namespace System;

// Forward decls.
namespace DirectX
{
	class ScratchImage;
}

namespace DirectXTexNet
{
namespace Impl
{

// Mirror of DirectXTex ScratchImage class.
public ref class ScratchImage : public IScratchImage
{
public:
	// Create a D3D11 texture from the image.
	virtual IntPtr CreateTexture(IntPtr device);

	// Get image meta-data.
	property TexMetadata MetaData
	{
		virtual TexMetadata get();
	}

	// Get the raw bytes for a sub-image.
	virtual array<byte>^ GetRawBytes(UInt32 arrayItem, UInt32 mip);

	// Generate mipmaps for this image.
	virtual void GenerateMipMaps();

	// Create an empty mip chain for this image.
	virtual void CreateEmptyMipChain();

	~ScratchImage();

internal:
	ScratchImage();

	DirectX::ScratchImage* GetScratchImage() { return scratchImage_; }

private:
	DirectX::ScratchImage* scratchImage_;
};

}
}
