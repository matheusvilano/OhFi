@echo off
setlocal

REM Change working directory to the script location
cd /d "%~dp0"

REM Prompt for Wwise version number
set /p version=Enter Wwise version number (e.g. 2024.1.4.0): 

echo.
echo Running Wwise plugin build and packaging for version %version%
echo.

python "%WWISEROOT%\Scripts\Build\Plugins\wp.py" premake Authoring
python "%WWISEROOT%\Scripts\Build\Plugins\wp.py" premake Windows_vc170

python "%WWISEROOT%\Scripts\Build\Plugins\wp.py" build -c Release -x x64 -t vc170 Authoring
python "%WWISEROOT%\Scripts\Build\Plugins\wp.py" build -c Release -x x64 -t vc170 Windows_vc170

python "%WWISEROOT%\Scripts\Build\Plugins\wp.py" package --version %version% Authoring
python "%WWISEROOT%\Scripts\Build\Plugins\wp.py" package --version %version% Windows_vc170

mkdir Bundle 2>nul
copy /y bundle.json Bundle\
copy /y *.tar.xz Bundle\

echo.
pause
