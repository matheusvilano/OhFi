#!/usr/bin/env bash

# Change working directory to the script's location
cd "$(dirname "$0")" || exit 1

# Auto-detect the most recent Wwise installation
wwise_base="/Applications/Audiokinetic"
latest_version=$(ls "$wwise_base" | sort -Vr | head -n 1)
wwise_root="$wwise_base/$latest_version"

# Verify the detected Wwise folder exists
if [ ! -d "$wwise_root" ]; then
  echo "Could not find Wwise installation in $wwise_base"
  exit 1
fi

echo "Using Wwise root: $wwise_root"

# Prompt for Wwise version number
read -p "Enter Wwise version number (e.g. 2022.1.0.1): " version
echo
echo "Running Wwise plugin build and packaging for version $version"
echo

python3 "$wwise_root/Scripts/Build/Plugins/wp.py" premake Mac

python3 "$wwise_root/Scripts/Build/Plugins/wp.py" build -c Release -x arm64 Mac
python3 "$wwise_root/Scripts/Build/Plugins/wp.py" build -c Release -x x86_64 Mac

python3 "$wwise_root/Scripts/Build/Plugins/wp.py" package --version "$version" Mac

python3 "$wwise_root/Scripts/Build/Plugins/wp.py" generate-bundle --version "$version"

mkdir -p Bundle
cp -f bundle.json Bundle/
cp -f *.tar.xz Bundle/

echo
read -p "Press Enter to continue..."
