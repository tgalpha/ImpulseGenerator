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

#include "ImpulseGeneratorSource.h"
#include "../ImpulseGeneratorConfig.h"

#include <AK/AkWwiseSDKVersion.h>

AK::IAkPlugin* CreateImpulseGeneratorSource(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, ImpulseGeneratorSource());
}

AK::IAkPluginParam* CreateImpulseGeneratorSourceParams(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, ImpulseGeneratorSourceParams());
}

AK_IMPLEMENT_PLUGIN_FACTORY(ImpulseGeneratorSource, AkPluginTypeSource, ImpulseGeneratorConfig::CompanyID, ImpulseGeneratorConfig::PluginID)

ImpulseGeneratorSource::ImpulseGeneratorSource()
    : m_pParams(nullptr)
    , m_pAllocator(nullptr)
    , m_pContext(nullptr)
{
}

ImpulseGeneratorSource::~ImpulseGeneratorSource()
{
}

AKRESULT ImpulseGeneratorSource::Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkSourcePluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat)
{
    m_pParams = (ImpulseGeneratorSourceParams*)in_pParams;
    m_pAllocator = in_pAllocator;
    m_pContext = in_pContext;

    m_core.Setup(m_pParams->RTPC.fDuration, in_pContext->GetNumLoops(), in_rFormat.uSampleRate);

    return AK_Success;
}

AKRESULT ImpulseGeneratorSource::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT ImpulseGeneratorSource::Reset()
{
    m_core.Reset();
    return AK_Success;
}

AKRESULT ImpulseGeneratorSource::GetPluginInfo(AkPluginInfo& out_rPluginInfo)
{
    out_rPluginInfo.eType = AkPluginTypeSource;
    out_rPluginInfo.bIsInPlace = true;
    out_rPluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
    return AK_Success;
}

void ImpulseGeneratorSource::Execute(AkAudioBuffer* out_pBuffer)
{
    HandleParameterChange();
    m_core.ProduceBuffer(out_pBuffer);
}

AkReal32 ImpulseGeneratorSource::GetDuration() const
{
    return m_core.GetDuration() * 1000.0f;
}

void ImpulseGeneratorSource::HandleParameterChange()
{
    auto pChangeHandler = m_pParams->GetParamChangeHandler();
    if (pChangeHandler->HasChanged(PARAM_DURATION_ID))
    {
        m_core.SetDuration(m_pParams->RTPC.fDuration);
    }
    if (pChangeHandler->HasChanged(PARAM_GAIN_ID))
    {
        m_core.SetAmplitude(AK_DBTOLIN(m_pParams->RTPC.fGain));
    }

    pChangeHandler->ResetAllParamChanges();
}
