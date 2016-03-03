// This is the main DLL file.

#include "stdafx.h"

#include "DirectXTex.net.h"
#include "ScratchImage.h"

using namespace System::Runtime::InteropServices;

namespace DirectXTexNet
{

//--------------------------------------------------------------------------------------------------
// Load an image from a DDS file.
//--------------------------------------------------------------------------------------------------
ScratchImage^ DirectXTex::LoadFromDDSFile(String^ filename)
{
	// Get C rep of filename string.
	pin_ptr<const wchar_t> filenameCStr = PtrToStringChars(filename);

	auto image = gcnew ScratchImage();
	auto hr = DirectX::LoadFromDDSFile(filenameCStr, DirectX::DDS_FLAGS_NONE, nullptr, *image->GetScratchImage());

	// Throw on failure.
	Marshal::ThrowExceptionForHR(hr);

	return image;
}


//--------------------------------------------------------------------------------------------------
// Load an image from a file using WIC.
//--------------------------------------------------------------------------------------------------
ScratchImage^ DirectXTex::LoadFromWICFile(String^ filename)
{
	// Get C rep of filename string.
	pin_ptr<const wchar_t> filenameCStr = PtrToStringChars(filename);

	auto image = gcnew ScratchImage();
	auto hr = DirectX::LoadFromWICFile(filenameCStr, DirectX::WIC_FLAGS_NONE, nullptr, *image->GetScratchImage());

	// Throw on failure.
	Marshal::ThrowExceptionForHR(hr);

	return image;
}


//--------------------------------------------------------------------------------------------------
// Load an image from a TGA file.
//--------------------------------------------------------------------------------------------------
ScratchImage^ DirectXTex::LoadFromTGAFile(String^ filename)
{
	// Get C rep of filename string.
	pin_ptr<const wchar_t> filenameCStr = PtrToStringChars(filename);

	auto image = gcnew ScratchImage();
	auto hr = DirectX::LoadFromTGAFile(filenameCStr, nullptr, *image->GetScratchImage());

	// Throw on failure.
	Marshal::ThrowExceptionForHR(hr);

	return image;
}

//--------------------------------------------------------------------------------------------------
// Create a 2D texture from raw pixel data.
//--------------------------------------------------------------------------------------------------
ScratchImage^ DirectXTex::Create2D(IntPtr data, int pitch, int width, int height, unsigned int format)
{
	// Construct Image representation.
	DirectX::Image image;
	image.width = width;
	image.height = height;
	image.format = static_cast<DXGI_FORMAT>(format);
	image.rowPitch = pitch;
	image.slicePitch = 0;
	image.pixels = static_cast<uint8_t*>(data.ToPointer());

	// Create scrath image from the Image.
	auto result = gcnew ScratchImage();
	auto hr = result->GetScratchImage()->InitializeFromImage(image);

	// Throw on failure.
	Marshal::ThrowExceptionForHR(hr);

	return result;
}

}