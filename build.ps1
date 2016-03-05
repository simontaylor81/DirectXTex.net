# Build platforms & configs required to build the nuget package.
$config = 'Release'
$platforms = 'x86', 'x64'

echo $psversiontable

# Hook up AppVeyor logger if it exists.
if (Test-Path 'C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll')
{
	$loggerParam = '/logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"'
}

foreach ($platform in $platforms)
{
	& msbuild 'DirectXTexNet.sln' "/property:Configuration=$config" "/property:Platform=$platform" '/verbosity:Minimal' '--%' $loggerParam
	if (!$?)
	{
		throw "Build failed"
	}
}
