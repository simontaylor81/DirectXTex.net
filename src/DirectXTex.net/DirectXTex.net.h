// DirectXTex.net.h

#pragma once

using namespace System;

namespace DirectXTexNet
{
	// Forward decl.
	ref class ScratchImage;

	// Static class containing the global functions for file handling.
	public ref class DirectXTex
	{
	public:

		static ScratchImage^ LoadFromDDSFile(String^ filename);
		static ScratchImage^ LoadFromWICFile(String^ filename);
		static ScratchImage^ LoadFromTGAFile(String^ filename);

		static ScratchImage^ Create2D(IntPtr data, int pitch, int width, int height, unsigned int format);
	};
}
