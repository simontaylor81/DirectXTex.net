// This is the main DLL file.

#include "stdafx.h"
#include "ScratchImage.h"

using namespace System::Runtime::InteropServices;

namespace DirectXTexNet
{
namespace Impl
{

//--------------------------------------------------------------------------------------------------
// ScratchImage implementation.
//--------------------------------------------------------------------------------------------------

ScratchImage::ScratchImage()
{
	scratchImage_ = new DirectX::ScratchImage();
}

ScratchImage::~ScratchImage()
{
	delete scratchImage_;
}

IntPtr ScratchImage::CreateTexture(IntPtr device)
{
	// Get internal device pointer.
	auto deviceRaw = static_cast<ID3D11Device*>(device.ToPointer());

	// Create the texture.
	ID3D11Resource* texture = nullptr;
	HRESULT hr = DirectX::CreateTexture(
		deviceRaw,
		scratchImage_->GetImages(),
		scratchImage_->GetImageCount(),
		scratchImage_->GetMetadata(),
		&texture);

	// Throw on failure.
	Marshal::ThrowExceptionForHR(hr);

	// Convert back to SlimDX type.
	return IntPtr(texture);
}

// Get image meta data.
TexMetadata ScratchImage::MetaData::get()
{
	return TexMetadataFromNative(scratchImage_->GetMetadata());
}


// Get the raw bytes for a sub-image.
array<byte>^ ScratchImage::GetRawBytes(UInt32 arrayItem, UInt32 mip)
{
	auto metaData = scratchImage_->GetMetadata();

	if (arrayItem < 0 || arrayItem >= metaData.arraySize)
	{
		throw gcnew ArgumentException("Array item index out of bounds", "arrayItem");
	}
	if (mip < 0 || mip >= metaData.mipLevels)
	{
		throw gcnew ArgumentException("Mip index out of bounds", "mip");
	}

	auto image = scratchImage_->GetImage(mip, arrayItem, 0);
	if (image == nullptr)
	{
		throw gcnew ArgumentException("Could not find image with the given parameters.");
	}

	const int rowSize = int(image->width) * int(DirectX::BitsPerPixel(image->format)) / 8;
	const int sizeInBytes = int(image->height) * rowSize;
	auto result = gcnew array<byte>(sizeInBytes);

	// Copy row by row.
	int destIndex = 0;
	for (size_t y = 0; y < image->height; y++)
	{
		uint8_t* src = image->pixels + y * image->rowPitch;
		Marshal::Copy(IntPtr(src), result, destIndex, rowSize);
		destIndex += rowSize;
	}

	return result;
}

void ScratchImage::GenerateMipMaps()
{
	auto metaData = scratchImage_->GetMetadata();
	
	// Skip images that already have mipmaps.
	if (metaData.mipLevels > 1)
	{
		return;
	}

	// We can't generate mips for compressed formats, so skip those.
	if (DirectX::IsCompressed(metaData.format))
	{
		return;
	}

	auto newScratchImage = new DirectX::ScratchImage();
	try
	{
		auto hr = DirectX::GenerateMipMaps(scratchImage_->GetImages(), scratchImage_->GetImageCount(),
			metaData, (DWORD)DirectX::TEX_FILTER_FANT, 0, *newScratchImage);

		Marshal::ThrowExceptionForHR(hr);

		// Replace existing scratch image with the new one with mips.
		delete scratchImage_;
		scratchImage_ = newScratchImage;
		newScratchImage = nullptr;
	}
	finally
	{
		// Free new scratch image if we didn't use it.
		delete newScratchImage;
	}

}

void ScratchImage::CreateEmptyMipChain()
{
	auto metaData = scratchImage_->GetMetadata();

	// Skip images that already have mipmaps.
	if (metaData.mipLevels > 1)
	{
		return;
	}

	// We can't generate mips for compressed formats, so skip those.
	if (DirectX::IsCompressed(metaData.format))
	{
		return;
	}

	auto newScratchImage = new DirectX::ScratchImage();
	try
	{
		HRESULT hr;
		if (metaData.miscFlags & DirectX::TEX_MISC_TEXTURECUBE)
		{
			hr = newScratchImage->InitializeCube(metaData.format, metaData.width, metaData.height, metaData.arraySize / 6, 0);
		}
		else
		{
			hr = newScratchImage->Initialize2D(metaData.format, metaData.width, metaData.height, metaData.arraySize, 0);
		}
			
		Marshal::ThrowExceptionForHR(hr);

		// Copy each array entry.
		for (size_t item = 0; item < metaData.arraySize; item++)
		{
			hr = DirectX::CopyRectangle(
				*scratchImage_->GetImage(0, item, 0),
				DirectX::Rect(0, 0, metaData.width, metaData.height),
				*newScratchImage->GetImage(0, item, 0),
				0,	// Filter -- not needed since source and dest format are the same.
				0, 0);
			Marshal::ThrowExceptionForHR(hr);

			// Zero out mipchain.
			for (size_t mip = 1; mip < newScratchImage->GetMetadata().mipLevels; mip++)
			{
				auto* image = newScratchImage->GetImage(mip, item, 0);
				auto* data = image->pixels;
				auto size = image->rowPitch * image->height;
				ZeroMemory(data, size);
			}
		}

		// Replace existing scratch image with the new one (the one with mips).
		delete scratchImage_;
		scratchImage_ = newScratchImage;
		newScratchImage = nullptr;
	}
	finally
	{
		// Free new scratch image if we didn't use it.
		delete newScratchImage;
	}
}

}
}
