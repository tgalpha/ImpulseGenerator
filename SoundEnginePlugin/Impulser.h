#pragma once

#include <AK/Plugin/PluginServices/AkFXDurationHandler.h>

class Impulser : public AkFXDurationHandler
{
public:
    void ProduceBuffer(AkAudioBuffer* io_pBuffer)
    {
        AKASSERT(io_pBuffer->NumChannels() == 1);
        const auto uMaxFrames = io_pBuffer->MaxFrames();
        // Infinite looping or not reached the end, always producing full capacity
        io_pBuffer->uValidFrames = uMaxFrames;
        io_pBuffer->eState = AK_DataReady;

        if (m_iNumLoops != 0)
        {
            // Finite looping, produce full buffer untill the end.
            const AkUInt32 uTotalFrames = m_iNumLoops * m_uIterationFrame;
            if (m_uFrameCount < uTotalFrames)
            {
                const AkUInt32 uFramesRemaining = uTotalFrames - m_uFrameCount;
                if (uFramesRemaining <= uMaxFrames)
                {
                    io_pBuffer->uValidFrames = (AkUInt16)uFramesRemaining;
                    io_pBuffer->eState = AK_NoMoreData;
                }
            }
            else
            {
                io_pBuffer->uValidFrames = 0;
                io_pBuffer->eState = AK_NoMoreData;
            }
        }
        m_uFrameCount += io_pBuffer->uValidFrames;

        const auto uFramesRemainingInCurrentLoop = m_uIterationFrame - m_uFrameInCurrentLoop;
        const auto pBuffer = io_pBuffer->GetChannel(0);
        AkZeroMemLarge(pBuffer, io_pBuffer->uValidFrames * sizeof(AkSampleType));
        if (m_uFrameInCurrentLoop == 0)
        {
            pBuffer[0] = m_fAmplitude;
        }
        else if (uFramesRemainingInCurrentLoop < io_pBuffer->uValidFrames)
        {
            pBuffer[uFramesRemainingInCurrentLoop] = m_fAmplitude;
        }
        m_uFrameInCurrentLoop += io_pBuffer->uValidFrames;
        if (m_uFrameInCurrentLoop >= m_uIterationFrame)
        {
            m_uFrameInCurrentLoop %= m_uIterationFrame;
        }
    }

    void SetAmplitude(AkReal32 in_fAmplitude) { m_fAmplitude = in_fAmplitude; }

private:
    AkUInt32 m_uFrameInCurrentLoop = 0;
    AkReal32 m_fAmplitude = 1.f;
};
