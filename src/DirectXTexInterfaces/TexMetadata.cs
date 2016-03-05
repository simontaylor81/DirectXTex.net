using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DirectXTexNet
{
	// Managed mirror of DirectX::TEX_DIMENSION
	public enum TexDimension : uint
	{
		Texture1D = 2,
		Texture2D = 3,
		Texture3D = 4,
	}

	// Managed mirror of DirectX::TexMetadata
	public struct TexMetadata
	{
		public uint width;
		public uint height;		// Should be 1 for 1D textures
		public uint depth;		// Should be 1 for 1D or 2D textures
		public uint arraySize;	// For cubemap, this is a multiple of 6
		public uint mipLevels;
		public uint miscFlags;
		public uint miscFlags2;
		public uint format;		// DXGI_FORMAT
		public TexDimension dimension;
	}
}
