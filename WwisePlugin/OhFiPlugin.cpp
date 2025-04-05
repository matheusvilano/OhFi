// Copyright 2025 Matheus Vilano
// SPDX-License-Identifier: Apache-2.0

#include "OhFiPlugin.h"
#include "../SoundEnginePlugin/OhFiFXFactory.h"

const char* const szBitDepth = "BitDepth";
const char* const szDownsampleFactor = "DownsampleFactor";
const char* const szWetDryMix = "WetDryMix";

bool OhFiPlugin::GetBankParameters(const GUID & in_guidPlatform, AK::Wwise::Plugin::DataWriter& in_dataWriter) const
{
    in_dataWriter.WriteReal32(m_propertySet.GetUInt8(in_guidPlatform, szBitDepth));
    in_dataWriter.WriteReal32(m_propertySet.GetUInt8(in_guidPlatform, szDownsampleFactor));
    in_dataWriter.WriteReal32(m_propertySet.GetReal32(in_guidPlatform, szWetDryMix));
    return true;
}

DEFINE_AUDIOPLUGIN_CONTAINER(OhFi);  // Create a PluginContainer structure that contains the info for our plugin
EXPORT_AUDIOPLUGIN_CONTAINER(OhFi);  // This is a DLL, we want to have a standardized name

// Plug-In Container, Authoring Plug-In, SoundEngine Plug-In
ADD_AUDIOPLUGIN_CLASS_TO_CONTAINER(OhFi, OhFiPlugin, OhFiFX);

DEFINE_PLUGIN_REGISTER_HOOK;
DEFINEDUMMYASSERTHOOK;  // Placeholder assert hook for Wwise plug-ins using AKASSERT (cassert used by default)
