using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DirectXTexNet
{
	public static class DirectXTex
	{
		static DirectXTex()
		{
			AppDomain.CurrentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;
		}

		public static IScratchImage LoadFromDDSFile(string filename)
		{
			throw new NotImplementedException();
		}

		public static IScratchImage LoadFromWICFile(string filename)
		{
			return Impl.DirectXTex.LoadFromWICFile(filename);

			//throw new NotImplementedException();
		}

		private static System.Reflection.Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
		{
			return null;
		}

		public static IScratchImage LoadFromTGAFile(string filename)
		{
			throw new NotImplementedException();
		}

		public static IScratchImage Create2D(IntPtr data, int pitch, int width, int height, uint format)
		{
			throw new NotImplementedException();
		}
	}
}
