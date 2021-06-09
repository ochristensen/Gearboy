#pragma once

#include "MemoryRule.h"

class FullyWriteableMemoryRule : public MemoryRule
{
public:
    FullyWriteableMemoryRule(Processor* pProcessor, Memory* pMemory, Video* pVideo, Input* pInput, Cartridge* pCartridge, Audio* pAudio);
    ~FullyWriteableMemoryRule() override = default;
    virtual u8 PerformRead(u16 address) override;
    virtual void PerformWrite(u16 address, u8 value) override;
    virtual void Reset(bool bCGB) override;
    virtual u8* GetRomBank0() override;
    virtual int GetCurrentRomBank0Index() override;
    size_t GetDefaultROMSize() const override;
};