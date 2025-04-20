// Copyright 2025 Matheus Vilano
// SPDX-License-Identifier: Apache-2.0

#ifndef OhFiFX_H
#define OhFiFX_H

#include "OhFiFXParams.h"

/// @brief SoundEngine Plugin (in-place).
/// @see https://www.audiokinetic.com/library/edge/?source=SDK&id=soundengine__plugins__effects.html
class OhFiFX
    : public AK::IAkInPlaceEffectPlugin
{
public:
    /// @brief Default constructor.
    OhFiFX() = default;

    /// @brief Default destructor.
    ~OhFiFX() = default;

    /// @brief Plug-in initialization.
    /// Prepares the plug-in for data processing, allocates memory and sets up the initial conditions.
    /// @param in_pAllocator The memory allocator.
    /// @param in_pContext The plugin context.
    /// @param in_pParams The plugin parameters.
    /// @param in_rFormat The audio buffer format.
    /// @return AK_SUCCESS, if the operation succeeded.
    AKRESULT Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkEffectPluginContext* in_pContext,
                  AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat) override;

    /// Release the resources upon termination of the plug-in.
    /// @param in_pAllocator The memory allocator.
    /// @return AK_SUCCESS, if the operation succeeded.
    AKRESULT Term(AK::IAkPluginMemAlloc* in_pAllocator) override;

    /// @brief The reset action should perform any actions required to reinitialize the
    /// state of the plug-in to its original state (e.g. after Init() or on effect bypass).
    /// @return AK_SUCCESS, if the operation succeeded.
    AKRESULT Reset() override;

    /// @brief Plug-in information query mechanism used when the sound engine requires
    /// information about the plug-in to determine its behavior.
    /// @param out_rPluginInfo Plugin info structure.
    /// @return AK_SUCCESS, if the operation succeeded.
    AKRESULT GetPluginInfo(AkPluginInfo& out_rPluginInfo) override;

    /// @brief Effect plug-in DSP execution.
    /// @param io_pBuffer The current audio buffer.
    void Execute(AkAudioBuffer* io_pBuffer) override;

    /// @brief Skips execution of some frames, when the voice is virtual playing from elapsed time.
    /// This can be used to simulate processing that would have taken place (e.g. update internal state).
    /// Return AK_DataReady or AK_NoMoreData, depending if there would be audio output or not at that point.
    /// @param in_uFrames The amount of audio frames to skip.
    /// @return AK_SUCCESS, if the operation succeeded.
    AKRESULT TimeSkip(AkUInt32 in_uFrames) override;

private:
    /// @brief The structure containing all parameters for this plugin.
    OhFiFXParams* m_pParams = nullptr;

    /// @brief The plugin memory allocator.
    AK::IAkPluginMemAlloc* m_pAllocator = nullptr;

    /// @brief The effect plugin context.
    AK::IAkEffectPluginContext* m_pContext = nullptr;
};

#endif // OhFiFX_H
