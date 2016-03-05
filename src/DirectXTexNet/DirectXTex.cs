using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace DirectXTexNet
{
	public static class DirectXTex
	{
		public static IScratchImage LoadFromDDSFile(string filename)
		{
			return Impl.DirectXTex.LoadFromDDSFile(filename);
		}

		public static IScratchImage LoadFromWICFile(string filename)
		{
			return Impl.DirectXTex.LoadFromWICFile(filename);
		}

		public static IScratchImage LoadFromTGAFile(string filename)
		{
			return Impl.DirectXTex.LoadFromTGAFile(filename);
		}

		public static IScratchImage Create2D(IntPtr data, int pitch, int width, int height, uint format)
		{
			return Impl.DirectXTex.Create2D(data, pitch, width, height, format);
		}

		static DirectXTex()
		{
			AppDomain.CurrentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;
		}

		// Custom assembly resolver to find the architecture-specific implementation assembly.
		private static Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
		{
			if (args.Name.StartsWith("DirectXTexNetImpl", StringComparison.OrdinalIgnoreCase))
			{
				var path = Path.Combine(
					Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location),    // Our path
					Environment.GetEnvironmentVariable("PROCESSOR_ARCHITECTURE"),		// x86 or x64
					"DirectXTexNetImpl.dll");

				return Assembly.LoadFile(path);
			}
			return null;
		}
	}
}
