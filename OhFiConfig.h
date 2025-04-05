// Copyright 2025 Matheus Vilano
// SPDX-License-Identifier: Apache-2.0

#ifndef OhFiConfig_H
#define OhFiConfig_H

// NB: In order to properly change the CompanyID / PluginID, you must change them:
// - In this file;
// - In the xml file located in the WwisePlugin directory;
// - In the xml file located in the FactoryAssets directory.

/// @brief Config specs for the plugin.
namespace OhFiConfig
{
    static const unsigned short CompanyID = 64;
    static const unsigned short PluginID = 24955;
}

#endif // OhFiConfig_H
