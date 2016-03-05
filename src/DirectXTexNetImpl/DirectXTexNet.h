// DirectXTexNet.h

#pragma once

using namespace System;

namespace DirectXTexNet
{
namespace Impl
{
	// Forward decl.
	//ref class ScratchImage;

	// Static class containing the global functions for file handling.
	public ref class DirectXTex
	{
	public:

		static IScratchImage^ LoadFromDDSFile(String^ filename);
		static IScratchImage^ LoadFromWICFile(String^ filename);
		static IScratchImage^ LoadFromTGAFile(String^ filename);

		static IScratchImage^ Create2D(IntPtr data, int pitch, int width, int height, unsigned int format);
	};
}
}
