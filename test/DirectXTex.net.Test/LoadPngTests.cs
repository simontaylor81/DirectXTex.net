using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DirectXTexNet.Test.Util;
using NUnit.Framework;

namespace DirectXTexNet.Test
{
	public class LoadPngTests
	{
		// Test for WIC loading path, which we can compare to the result of loading using System.Drawing.
		[TestCase("ThisIsATest.png")]
		[TestCase("ThisIsATest.bmp")]
		[TestCase("ThisIsATest.jpg")]
		public void LoadWIC(string filename)
		{
			var path = GetImagePath(filename);

			// Load image with DirectXTex.
			using (var image = DirectXTex.LoadFromWICFile(path))
			{
				// Load the same image with System.Drawing.
				using (var expected = new Bitmap(path))
				{
					// Assert that they match.
					AssertEqual(image, expected);
				}
			}
		}

		// Test for TGA loading path.
		[Test]
		public void LoadTga()
		{
			var path = GetImagePath("ThisIsATest.tga");
			var refPath = GetImagePath("ThisIsATest.png");

			// Load image with DirectXTex.
			using (var image = DirectXTex.LoadFromTGAFile(path))
			{
				// Can't load a tga with System.Drawing, so load an identical png.
				using (var expected = new Bitmap(refPath))
				{
					// Assert that they match.
					AssertEqual(image, expected);
				}
			}
		}

		// Test for DDS loading path.
		[Test]
		public void LoadDds()
		{
			var path = GetImagePath("ThisIsATest.dds");
			var refPath = GetImagePath("ThisIsATest.png");

			// Load image with DirectXTex.
			using (var image = DirectXTex.LoadFromDDSFile(path))
			{
				// Can't load a dds with System.Drawing, so load an identical png.
				using (var expected = new Bitmap(refPath))
				{
					// Assert that they match.
					AssertEqual(image, expected);
				}
			}
		}

		private void AssertEqual(ScratchImage image, Bitmap expected)
		{
			// Check various meta-data.
			var metaData = image.MetaData;
			Assert.AreEqual(expected.Width, metaData.width);
			Assert.AreEqual(expected.Height, metaData.height);
			Assert.AreEqual(1, metaData.depth);
			Assert.AreEqual(TexDimension.Texture2D, metaData.dimension);
			Assert.AreEqual(1, metaData.arraySize);
			Assert.AreEqual(1, metaData.mipLevels);

			// DXGI_FORMAT_R8G8B8A8_UNORM or DXGI_FORMAT_R8G8B8A8_UNORM_SRGB
			Assert.That(metaData.format, Is.EqualTo(28).Or.EqualTo(29));

			// Check raw contents match.
			var bytes = image.GetRawBytes(0, 0);
			Assert.That(bytes, Is.EqualTo(expected.GetRawBytesRGBA()));
		}

		// Assembly is in bin/<platform>/<config>/
		private string GetImagePath(string filename) =>
			Path.Combine(
				Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location),
				"../../../Images",
				filename);
	}
}
