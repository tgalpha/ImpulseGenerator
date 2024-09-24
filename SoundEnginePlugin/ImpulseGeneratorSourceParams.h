/*******************************************************************************
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

Apache License Usage

Alternatively, this file may be used under the Apache License, Version 2.0 (the
"Apache License"); you may not use this file except in compliance with the
Apache License. You may obtain a copy of the Apache License at
http://www.apache.org/licenses/LICENSE-2.0.

Unless required by applicable law or agreed to in writing, software distributed
under the Apache License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
OR CONDITIONS OF ANY KIND, either express or implied. See the Apache License for
the specific language governing permissions and limitations under the License.

  Copyright (c) 2021 Audiokinetic Inc.
*******************************************************************************/
// [wp-enhanced template] **Do not delete this line**

#ifndef ImpulseGeneratorSourceParams_H
#define ImpulseGeneratorSourceParams_H

#include <AK/SoundEngine/Common/IAkPlugin.h>
#include <AK/Plugin/PluginServices/AkFXParameterChangeHandler.h>

// Add parameters IDs here, those IDs should map to the AudioEnginePropertyID
// attributes in the xml property definition.
// [ParameterID]
static constexpr AkPluginParamID PARAM_DURATION_ID = 0;
static constexpr AkPluginParamID PARAM_GAIN_ID = 1;
static constexpr AkUInt32 NUM_PARAMS = 2;
// [/ParameterID]

// [InnerTypes]
// [/InnerTypes]

struct ImpulseGeneratorInnerTypeParams
{
    // [InnerTypeDeclaration]
    // [/InnerTypeDeclaration]
};

struct ImpulseGeneratorRTPCParams
{
    // [RTPCDeclaration]
    AkReal32 fDuration;
    AkReal32 fGain;
    // [/RTPCDeclaration]
};

struct ImpulseGeneratorNonRTPCParams
{
    // [NonRTPCDeclaration]
    // [/NonRTPCDeclaration]
};

struct ImpulseGeneratorSourceParams
    : public AK::IAkPluginParam
{
    ImpulseGeneratorSourceParams();
    ImpulseGeneratorSourceParams(const ImpulseGeneratorSourceParams& in_rParams);

    ~ImpulseGeneratorSourceParams();

    /// Create a duplicate of the parameter node instance in its current state.
    IAkPluginParam* Clone(AK::IAkPluginMemAlloc* in_pAllocator) override;

    /// Initialize the plug-in parameter node interface.
    /// Initializes the internal parameter structure to default values or with the provided parameter block if it is valid.
    AKRESULT Init(AK::IAkPluginMemAlloc* in_pAllocator, const void* in_pParamsBlock, AkUInt32 in_ulBlockSize) override;

    /// Called by the sound engine when a parameter node is terminated.
    AKRESULT Term(AK::IAkPluginMemAlloc* in_pAllocator) override;

    /// Set all plug-in parameters at once using a parameter block.
    AKRESULT SetParamsBlock(const void* in_pParamsBlock, AkUInt32 in_ulBlockSize) override;

    /// Update a single parameter at a time and perform the necessary actions on the parameter changes.
    AKRESULT SetParam(AkPluginParamID in_paramID, const void* in_pValue, AkUInt32 in_ulParamSize) override;

    AK::AkFXParameterChangeHandler<NUM_PARAMS>* GetParamChangeHandler() { return &m_paramChangeHandler; }

    ImpulseGeneratorInnerTypeParams InnerType;
    ImpulseGeneratorRTPCParams RTPC;
    ImpulseGeneratorNonRTPCParams NonRTPC;

private:
    AK::AkFXParameterChangeHandler<NUM_PARAMS> m_paramChangeHandler;
};

#endif // ImpulseGeneratorSourceParams_H
