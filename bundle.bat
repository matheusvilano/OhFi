@echo off
setlocal

REM Change working directory to the script location
cd /d "%~dp0"

REM Prompt for Wwise version number
set /p version=Enter Wwise version number (e.g. 2022.1.0.1): 

echo.
echo Running Wwise plugin build and packaging for version %version%
echo.

python "%WWISEROOT%\Scripts\Build\Plugins\wp.py" generate-bundle --version %version%

mkdir Bundle 2>nul
copy /y bundle.json Bundle\
copy /y *.tar.xz Bundle\

echo.
pause
