using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DirectXTex.net.Test.Util;
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
				var bytes = image.GetRawBytes(0, 0);

				// Load the same image with System.Drawing.
				using (var expected = new Bitmap(path))
				{
					// Assert that they match.
					Assert.That(bytes, Is.EqualTo(expected.GetRawBytesRGBA()));
				}
			}
		}

		// Test for WIC loading path, which we can compare to the result of loading using System.Drawing.
		[Test]
		public void LoadTga()
		{
			var path = GetImagePath("ThisIsATest.tga");
			var refPath = GetImagePath("ThisIsATest.png");

			// Load image with DirectXTex.
			using (var image = DirectXTex.LoadFromTGAFile(path))
			{
				var bytes = image.GetRawBytes(0, 0);

				// Can't load a tga with System.Drawing, so load an identical png.
				using (var expected = new Bitmap(refPath))
				{
					// Assert that they match.
					Assert.That(bytes, Is.EqualTo(expected.GetRawBytesRGBA()));
				}
			}
		}

		// Assembly is in bin/<config>/
		private string GetImagePath(string filename) =>
			Path.Combine(
				Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location),
				"../../Images",
				filename);
	}
}
