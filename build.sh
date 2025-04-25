#!/bin/bash

# Change to the 'wwise' directory relative to the script's location
cd "$(dirname "$0")" || exit 1

# Prompt for Wwise version number
read -p "Enter Wwise version number (e.g. 2022.1.0.1): " version
echo
echo "Running Wwise plugin build and packaging for version $version"
echo

python "$WWISEROOT/Scripts/Build/Plugins/wp.py" premake Authoring
python "$WWISEROOT/Scripts/Build/Plugins/wp.py" premake Mac

python "$WWISEROOT/Scripts/Build/Plugins/wp.py" build -c Release -x x64 -t clang Authoring
python "$WWISEROOT/Scripts/Build/Plugins/wp.py" build -c Release -x x64 -t clang Mac

python "$WWISEROOT/Scripts/Build/Plugins/wp.py" package --version "$version" Authoring
python "$WWISEROOT/Scripts/Build/Plugins/wp.py" package --version "$version" Mac

python "$WWISEROOT/Scripts/Build/Plugins/wp.py" generate-bundle --version "$version"

mkdir -p Bundle
cp -f bundle.json Bundle/
cp -f *.tar.xz Bundle/

echo
read -p "Press Enter to continue..."
