// Copyright 2025 Matheus Vilano
// SPDX-License-Identifier: Apache-2.0

#ifndef OhFiFXParams_H
#define OhFiFXParams_H

#include <AK/SoundEngine/Common/IAkPlugin.h>
#include <AK/Plugin/PluginServices/AkFXParameterChangeHandler.h>

// Add parameters IDs here, those IDs should map to the AudioEnginePropertyID attributes in the xml property definition.

/// @brief BitDepth parameter ID.
static const AkPluginParamID LONY_OHFIFXPARAM_BITDEPTH_ID = 0;

/// @brief DownsampleFactor parameter ID.
static const AkPluginParamID LONY_OHFIFXPARAM_DOWNSAMPLEFACTOR_ID = 1;

/// @brief WetDryMix parameter ID.
static const AkPluginParamID LONY_OHFIFXPARAM_WETDRYMIX_ID = 2;

/// @brief The total amount of parameters.
static const AkUInt32 NUM_PARAMS = 3;

#define OHFIFXPARAM_BITDEPTH_DEF (24)  // Units
#define OHFIFXPARAM_DOWNSAMPLEFACTOR_DEF (1)  // Multiplier
#define OHFIFXPARAM_WETDRYMIX_DEF (100.0f)  // Percentage

/// @brief Structure containing parameters that support RTPCs.
struct OhFiRTPCParams
{
    AkUInt8 ubBitDepth;
    AkUInt8 ubDownsampleFactor;
    AkReal32 fWetDryMix;
};

/// @brief Structure containing parameters that do NOT support RTPCs.
struct OhFiNonRTPCParams
{
};

/// @brief Structure
struct OhFiFXParams
    : public AK::IAkPluginParam
{
    /// @brief Default constructor.
    OhFiFXParams() = default;

    /// @brief Copy constructor.
    /// @param in_rParams The parameters to copy.
    OhFiFXParams(const OhFiFXParams& in_rParams);

    /// @brief Default constructor.
    ~OhFiFXParams() = default;

    /// @brief Create a duplicate of the parameter node instance in its current state.
    /// @param in_pAllocator Memory allocator.
    /// @return The plugin parameter.
    IAkPluginParam* Clone(AK::IAkPluginMemAlloc* in_pAllocator) override;

    /// @brief Initialize the plug-in parameter node interface.
    /// Initializes the internal parameter structure to default values or with the provided parameter block if it is valid.
    /// @param in_pAllocator Memory allocator.
    /// @param in_pParamsBlock Pointer to block of parameters.
    /// @param in_ulBlockSize The block size.
    /// @return AK_SUCCESS if initialization succeeded.
    AKRESULT Init(AK::IAkPluginMemAlloc* in_pAllocator, const void* in_pParamsBlock, AkUInt32 in_ulBlockSize) override;

    /// @brief Called by the sound engine when a parameter node is terminated.
    /// @param in_pAllocator Memory allocator.
    /// @return AK_SUCCESS if the operation succeeded.
    AKRESULT Term(AK::IAkPluginMemAlloc* in_pAllocator) override;

    /// @brief Set all plug-in parameters at once using a parameter block.
    /// @param in_pParamsBlock Pointer to block of parameters.
    /// @param in_ulBlockSize The block size.
    /// @return AK_SUCCESS if the operation succeeded.
    AKRESULT SetParamsBlock(const void* in_pParamsBlock, AkUInt32 in_ulBlockSize) override;

    /// @brief Update a single parameter at a time and perform the necessary actions on the parameter changes.
    /// @param in_paramID The ID of the parameter.
    /// @param in_pValue The value of the parameter.
    /// @param in_ulParamSize The size of the parameter.
    /// @return AK_SUCCESS if the operation succeeded.
    AKRESULT SetParam(AkPluginParamID in_paramID, const void* in_pValue, AkUInt32 in_ulParamSize) override;

    /// @brief Handler for accessing changes in parameters.
    AK::AkFXParameterChangeHandler<NUM_PARAMS> m_paramChangeHandler;

    /// @brief Parameters with support for RTPCs.
    OhFiRTPCParams RTPC;

    /// @brief Parameters with NO support for RTPCs.
    OhFiNonRTPCParams NonRTPC;
};

#endif // OhFiFXParams_H
