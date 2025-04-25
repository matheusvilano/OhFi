# Lony OhFi
A Wwise effect plugin capable of Bitcrushing and Downsampling.

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
Pre-made bundles are available, but only for some versions of Wwise. If a bundle is not available for your target version of Wwise, you can create one yourself.

### Building
At the root of the repository, you will see a Bash script called `build.bat`. Assuming you have **Visual Studio 2022** and **C++ Dependencies** installed, running `build.bat` will (1) create Visual Studio solutions and projects, (2) compile and link C++ code, and (3) package all necessary files into a new bundle. When running `build.bat`, you will get a prompt for a Wwise version and plugin build number, in the format `year.major.minor.build` (e.g. `2024.1.4.2`), where `build` can be any number (up to 4 digits).

### Installing
Once done, you will see a `Bundle` folder in your local repo root. That folder contains all the necessary files to install OhFi. Open the Wwise Launcher, select the "**Plug-ins**" tab, then click "**Add from directory**". Select the `Bundle` folder and the plugin should start installing. Once done, you may open Wwise and start using OhFi!

### Integrating
If you are going to use OhFi with a project (e.g. in Unreal, Unity, etc), you will need to add OhFi to your project, just like you would with any other plugin. As usual, you should use the Wwise Launcher to do that.
