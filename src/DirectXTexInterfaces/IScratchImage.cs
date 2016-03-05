using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DirectXTexNet
{
	public interface IScratchImage : IDisposable
	{
		// Create a D3D11 texture from the image.
		IntPtr CreateTexture(IntPtr device);

		// Get image meta-data.
		TexMetadata MetaData { get; }

		// Get the raw bytes for a sub-image.
		byte[] GetRawBytes(uint arrayItem, uint mip);

		// Generate mipmaps for this image.
		void GenerateMipMaps();

		// Create an empty mip chain for this image.
		void CreateEmptyMipChain();
	}
}
