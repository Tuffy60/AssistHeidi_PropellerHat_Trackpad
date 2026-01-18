param()

$envName = 'FABI_RP2040'
& "C:\Users\User\.platformio\penv\Scripts\platformio.exe" run -e $envName
if ($LASTEXITCODE -ne 0) { Write-Error "PlatformIO build failed (exit code $LASTEXITCODE)."; exit $LASTEXITCODE }

$buildDir = Join-Path -Path (Get-Location) -ChildPath ".pio\build\$envName"
if (-not (Test-Path $buildDir)) { Write-Error "Build directory not found: $buildDir"; exit 2 }

$bin = Get-ChildItem -Path $buildDir -Filter *.bin -Recurse | Select-Object -First 1
if (-not $bin) { Write-Error "No .bin file found in $buildDir."; exit 3 }

Write-Output "Found binary: $($bin.FullName)"

$python = "python"
$script = Join-Path -Path (Get-Location) -ChildPath "tools\uf2conv.py"
if (-not (Test-Path $script)) { Write-Error "UF2 converter not found: $script"; exit 4 }

$outUf2 = Join-Path -Path (Get-Location) -ChildPath "firmware.uf2"
& $python $script $bin.FullName $outUf2 --base 0x10000000 --family 0xE48BFF56
if ($LASTEXITCODE -ne 0) { Write-Error "UF2 conversion failed (exit code $LASTEXITCODE)."; exit $LASTEXITCODE }

Write-Output "Created UF2: $outUf2"
