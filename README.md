# Lony OhFi
OhFi is a Wwise effect plugin capable of Bitcrushing and Downsampling.

## Supported Versions
This project uses C++17 features, so only versions `2024.0` and above are supported.

## Features

### Input
- Signal flow manipulation (series vs parallel)
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

## Setup
Pre-made bundles are available, but only for some versions of Wwise. If a bundle is not available for your target version of Wwise, you can create one yourself - but make sure to check the [Releases](https://github.com/matheusvilano/OhFi/releases) page first.

### Building
At the root of the repository, you will see a Bash script called `build.bat`. Assuming you have **Visual Studio 2022** and **C++ Dependencies** installed, running `build.bat` will (1) create Visual Studio solutions and projects, (2) compile and link C++ code, and (3) package all necessary files into a new bundle. When running `build.bat`, you will get a prompt for a Wwise version and plugin build number, in the format `year.major.minor.build` (e.g. `2024.1.4.2`), where `build` can be any number (up to 4 digits). Once done, you will see a `Bundle` folder in your local repo root, containing all the necessary files to install OhFi.

### Installing
If your bundle is compressed (e.g. as a ZIP), extract it first. Then, open the Wwise Launcher, select the "**Plug-ins**" tab, then click "**Add from directory**". Select the bundle's folder and the plugin should start installing. Once done, you may open Wwise and start using OhFi! If you need more information, see the [official docs](https://www.audiokinetic.com/en/public-library/Launcher_2024.1.0.4408/?source=InstallGuide&id=installing_plugins) by Audiokinetic.

### Integrating
If you are going to use OhFi with a project (e.g. in Unreal, Unity, etc), you will need to add OhFi to your project, just like you would with any other plugin. [For Unreal and Unity, that process can be automated via the Wwise Launcher](https://www.audiokinetic.com/en/public-library/Launcher_2024.1.0.4408/?source=InstallGuide&id=unity_unreal_integrations_plugins).
