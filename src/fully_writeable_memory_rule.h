#pragma once

#include "MemoryRule.h"

class FullyWriteableMemoryRule : public MemoryRule
{
public:
    FullyWriteableMemoryRule(Processor* pProcessor, Memory* pMemory, Video* pVideo, Input* pInput, Cartridge* pCartridge, Audio* pAudio);
    ~FullyWriteableMemoryRule() override = default;
    virtual u8 PerformRead(u16 address);
    virtual void PerformWrite(u16 address, u8 value);
    virtual void Reset(bool bCGB);
    virtual u8* GetRomBank0();
    virtual int GetCurrentRomBank0Index();
    size_t FullyWriteableMemoryRule::GetDefaultROMSize() const override;

private:
    int m_iCurrentRAMBank;
    int m_iCurrentROMBank;
    int m_iCurrentROMBankHi;
    bool m_bRamEnabled;
    u8* m_pRAMBanks;
    int m_CurrentROMAddress;
    int m_CurrentRAMAddress;
};