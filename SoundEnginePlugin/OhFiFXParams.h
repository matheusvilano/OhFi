// Copyright 2025 Matheus Vilano
// SPDX-License-Identifier: Apache-2.0

#ifndef OhFiFXParams_H
#define OhFiFXParams_H

#include <AK/SoundEngine/Common/IAkPlugin.h>
#include <AK/Plugin/PluginServices/AkFXParameterChangeHandler.h>

// Add parameters IDs here, those IDs should map to the AudioEnginePropertyID attributes in the xml property definition.

static const AkPluginParamID LONY_OHFIFXPARAM_INPUT_SIGNALFLOW_ID = 0;
static const AkPluginParamID LONY_OHFIFXPARAM_INPUT_PROCESSLFE_ID = 1;
static const AkPluginParamID LONY_OHFIFXPARAM_BITCRUSHER_BITDEPTH_ID = 2;
static const AkPluginParamID LONY_OHFIFXPARAM_BITCRUSHER_APPLYDITHER = 3;
static const AkPluginParamID LONY_OHFIFXPARAM_BITCRUSHER_WETDRYMIX = 4;
static const AkPluginParamID LONY_OHFIFXPARAM_DOWNSAMPLER_FACTOR_ID = 5;
static const AkPluginParamID LONY_OHFIFXPARAM_DOWNSAMPLER_INTERPOLATION_ID = 6;
static const AkPluginParamID LONY_OHFIFXPARAM_DOWNSAMPLER_WETDRYMIX_ID = 7;
static const AkPluginParamID LONY_OHFIFXPARAM_OUTPUT_GAINREDUCTION_ID = 8;
static const AkPluginParamID LONY_OHFIFXPARAM_OUTPUT_WETDRYMIX_ID = 9;
static const AkUInt32 NUM_PARAMS = 10; // Total amount of parameters.

/// @brief The signal flow. In other words, the order in which to process the different stages of the FX.
enum ESignalFlow
{
    /// @brief Bitcrushing and Downsampling happen in parallel. Both signals then get summed.
    SIGNALFLOW_PARALLEL = 0,

    /// @brief Bitcrushing first, then Downsampling.
    SIGNALFLOW_SERIES_BIDO = 1,

    /// @brief Downsampling first, then Bitcrushing.
    SIGNALFLOW_SERIES_DOBI = 2,
};

#define OHFIFXPARAM_INPUT_PROCESSLFE_DEF (false)                  // Flag
#define OHFIFXPARAM_INPUT_SIGNALFLOW_DEF (SIGNALFLOW_SERIES_BIDO) // Enumeration
#define OHFIFXPARAM_BITCRUSHER_BITDEPTH_DEF (24)                  // Units
#define OHFIFXPARAM_BITCRUSHER_APPLYDITHER_DEF (false)            // Flag
#define OHFIFXPARAM_BITCRUSHER_WETDRYMIX_DEF (100)                // Percentage
#define OHFIFXPARAM_DOWNSAMPLER_FACTOR_DEF (1)                    // Multiplier
#define OHFIFXPARAM_DOWNSAMPLER_INTERPOLATION_DEF (true)          // Flag
#define OHFIFXPARAM_DOWNSAMPLER_WETDRYMIX_DEF (100)               // Percentage
#define OHFIFXPARAM_OUTPUT_GAINREDUCTION_DEF (0.f)                // Decibels
#define OHFIFXPARAM_OUTPUT_WETDRYMIX_DEF (100.f)                  // Percentage

/// @brief Structure containing parameters that support RTPCs.
struct OhFiRTPCParams
{
    /// @brief Input game parameters.
    struct Input
    {
        /// @brief Whether to process the LFE channel.
        bool bProcessLfe;

        /// @brief The signal flow type to use.
        ESignalFlow eSignalFlow;

    } sInput;

    /// @brief Bitcrusher game parameters.
    struct Bitcrusher
    {
        /// @brief The bit depth used at the Bitcrushing stage.
        AkReal32 fBitDepth;

        /// @brief Whether to apply a dither at the Bitcrushing stage.
        bool bApplyDither;

        /// @brief The "intensity" of the Bitcrushing stage, in percentage.
        AkReal32 fWetDryMix;

    } sBitcrusher;

    /// @brief Downsampler game parameters.
    struct Downsampler
    {
        /// @brief The downsample factor used at the Downsampling stage. Example: `2` means "keep only every other sample".
        AkReal32 fFactor;

        /// @brief Whether to apply frame interpolation at the Downsampling stage.
        bool bInterpolation;

        /// @brief The "intensity" of the Downsampling stage, in percentage.
        AkReal32 fWetDryMix;

    } sDownsampler;

    /// @brief Output game parameters.
    struct Output
    {
        /// @brief Useful in case the FX drastically changes the loudness of the sound. Value is negative, in DB.
        AkReal32 fGainReduction;

        /// @brief The "intensity" of the FX. `100` means the FX output will be 100% of the "resulted" signal.
        AkReal32 fWetDryMix;

    } sOutput;
};

/// @brief Structure containing parameters that do NOT support RTPCs.
struct OhFiNonRTPCParams
{
    /// @brief Input game parameters.
    struct Input
    {
        // None.

    } sInput;

    /// @brief Bitcrusher non-game parameters.
    struct Bitcrusher
    {
        // None.

    } sBitcrusher;

    /// @brief Downsampler non-game parameters.
    struct Downsampler
    {
        /// @brief The sample (frame) currently held. Used for downsampling via sample-and-hold.
        AkReal32 fHeldSample = 0.f;

        /// @brief The amount of samples (frames) processed in the current batch. Used for downsampling via sample-and-hold.
        AkReal32 fSampleCounter = 0.f;

    } sDownsampler;

    /// @brief Output game parameters.
    struct Output
    {
        // None.

    } sOutput;
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
    IAkPluginParam *Clone(AK::IAkPluginMemAlloc* in_pAllocator) override;

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
