# Lony OhFi

OhFi is a Wwise effect plugin capable of Bitcrushing and Downsampling.

## Supported Versions

This project uses C++17 features, so only Wwise versions **2024.0** and above are supported.

## Features

### Input
- Signal flow manipulation (series vs. parallel)
- LFE toggle

### Bitcrusher
- Bit depth manipulation
- Dithering
- FX mix control

### Downsampler
- Downsampling factor
- Interpolation
- FX mix control

### Output
- Gain reduction
- FX mix control

## Installing

Pre-made bundles are available, but only for some versions of Wwise. If a bundle is not available for your target version, [you can package one yourself](#building)—but be sure to check the [Releases](https://github.com/matheusvilano/OhFi/releases) page first.

If your bundle is compressed (e.g., a ZIP file), extract it first. Then open the Wwise Launcher, select the **Plug-ins** tab, and click **Add from directory**. Select the extracted folder, and the plugin should begin installing. Once complete, you can open Wwise and start using OhFi. For more details, see the [official docs](https://www.audiokinetic.com/en/public-library/Launcher_2024.1.0.4408/?source=InstallGuide&id=installing_plugins) by Audiokinetic.

## Integrating

If you’re using OhFi in a project (e.g., Unreal, Unity, etc.), you’ll need to add the plugin to your project like any other Wwise plugin. [For Unreal and Unity, this process can be automated via the Wwise Launcher](https://www.audiokinetic.com/en/public-library/Launcher_2024.1.0.4408/?source=InstallGuide&id=unity_unreal_integrations_plugins).

## Building

If a pre-made bundle is not available for your target Wwise version, you can create one yourself. This process requires at least **a Windows machine with Python 3 installed**, but you may also need access to other systems (e.g., macOS) depending on your platform targets.

At the root of the repository, you’ll find a script called `build.bat`. On **Windows**, assuming you have **Visual Studio 2022** and **C++ dependencies** installed, run `build.bat` to:

1. Generate Visual Studio solutions and projects  
2. Compile and link the C++ code  
3. Package all necessary files

Then, run `bundle.bat` to create a new bundle. Once complete, you’ll see a `Bundle` folder in the repo root containing everything needed to install OhFi.

To build for **macOS**, run `build.sh` on a macOS machine or virtual machine. This script mirrors `build.bat` but is adapted for macOS. Similarly, `bundle.sh` is equivalent to `bundle.bat`. For other platforms, refer to the [Audiokinetic documentation](https://www.audiokinetic.com/en/public-library/2024.1.4_8780/?source=SDK&id=goingfurther_newplugins.html).

**Note**: Whenever prompted from a Wwise/plugin version, user the format `year.major.minor.build` (e.g., `2024.1.4.2`). The section `build` can be any number (up to 4 digits).
