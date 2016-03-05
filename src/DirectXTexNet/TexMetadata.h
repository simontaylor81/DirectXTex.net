#pragma once

using namespace System;

namespace DirectXTexNet
{

// Managed mirror of DirectX::TEX_DIMENSION
public enum class TexDimension : UInt32
{
	Texture1D = 2,
	Texture2D = 3,
	Texture3D = 4,
};


// Managed mirror of DirectX::TexMetadata
public value struct TexMetadata
{
	size_t			width;
	size_t			height;     // Should be 1 for 1D textures
	size_t			depth;      // Should be 1 for 1D or 2D textures
	size_t			arraySize;  // For cubemap, this is a multiple of 6
	size_t			mipLevels;
	UInt32			miscFlags;
	UInt32			miscFlags2;
	UInt32			format;		// DXGI_FORMAT
	TexDimension	dimension;

internal:
	TexMetadata(DirectX::TexMetadata native)
		: width(native.width)
		, height(native.height)
		, depth(native.depth)
		, arraySize(native.arraySize)
		, mipLevels(native.mipLevels)
		, miscFlags(native.miscFlags)
		, miscFlags2(native.miscFlags2)
		, format(native.format)
		, dimension((TexDimension)native.dimension)
	{
	}
};

}
