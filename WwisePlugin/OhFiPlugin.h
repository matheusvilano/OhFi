// Copyright 2025 Matheus Vilano
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <AK/Wwise/Plugin.h>

/// @brief BitDepth parameter name.
extern const char* const szBitDepth;

/// @brief DownsampleFactor parameter name.
extern const char* const szDownsampleFactor;

/// @brief WetDryMix parameter name.
extern const char* const szWetDryMix;

/// OhFi Authoring Plugin
class OhFiPlugin final : public AK::Wwise::Plugin::AudioPlugin
{
public:
    /// @brief Default constructor.
    OhFiPlugin() = default;
    
    /// @brief Default destructor.
    ~OhFiPlugin() = default;

    /// @brief This function is called by Wwise to obtain parameters that will be written to a bank.
    /// Because these can be changed at run-time, the parameter block should stay relatively small.
    /// Larger data should be put in the Data Block.
    /// @param in_guidPlatform The platform GUID.
    /// @param in_dataWriter Utility object for writing parameter information to a bank.
    bool GetBankParameters(const GUID& in_guidPlatform, AK::Wwise::Plugin::DataWriter& in_dataWriter) const override;
};

DECLARE_AUDIOPLUGIN_CONTAINER(OhFi);	// Exposes our PluginContainer structure that contains the info for our plugin
