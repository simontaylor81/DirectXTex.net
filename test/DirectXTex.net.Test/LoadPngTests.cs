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
		[Test]
		public void LoadPng()
		{
			var path = GetImagePath("ThisIsATest.png");

			var image = DirectXTex.LoadFromWICFile(GetImagePath("ThisIsATest.png"));
			var bytes = image.GetRawBytes(0, 0);

			var expected = new Bitmap(path).GetRawBytesRGBA();
			Assert.That(bytes, Is.EqualTo(expected));
		}

		// Assembly is in bin/<config>/
		private string GetImagePath(string filename) =>
			Path.Combine(
				Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location),
				"../../Images",
				filename);
	}
}
