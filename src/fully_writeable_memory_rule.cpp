/*
 * Gearboy - Nintendo Game Boy Emulator
 * Copyright (C) 2012  Ignacio Sanchez

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/
 *
 */

#include "fully_writeable_memory_rule.h"

#include "Cartridge.h"
#include "Input.h"
#include "Memory.h"
#include "Processor.h"
#include "Video.h"

FullyWriteableMemoryRule::FullyWriteableMemoryRule(Processor* pProcessor,
                                                   Memory* pMemory,
                                                   Video* pVideo, Input* pInput,
                                                   Cartridge* pCartridge,
                                                   Audio* pAudio)
    : MemoryRule(pProcessor, pMemory, pVideo, pInput, pCartridge, pAudio) {
  Reset(false);
}

void FullyWriteableMemoryRule::Reset(bool bCGB) { m_bCGB = bCGB; }

u8 FullyWriteableMemoryRule::PerformRead(u16 address) {
  if (address >= 0xA000 && address < 0xC000) {
    if (m_pCartridge->GetRAMSize() > 0)
      return m_pMemory->Retrieve(address);
    else {
      Log("--> ** Attempting to read from RAM without ram in cart %X", address);
      return 0xFF;
    }
  } else
    return m_pMemory->Retrieve(address);
}

void FullyWriteableMemoryRule::PerformWrite(u16 address, u8 value) {
  if (address < 0x2000) {
    m_pMemory->Load(address, value);
  } else if (address >= 0xA000 && address < 0xC000) {
    if (m_pCartridge->GetRAMSize() > 0) {
      m_pMemory->Load(address, value);
    } else {
      Log("--> ** Attempting to write to RAM without ram in cart  %X %X",
          address, value);
    }
  } else {
    m_pMemory->Load(address, value);
  }
}

u8* FullyWriteableMemoryRule::GetRomBank0() {
  return m_pMemory->GetMemoryMap() + 0x0000;
}

int FullyWriteableMemoryRule::GetCurrentRomBank0Index() { return 0; }

size_t FullyWriteableMemoryRule::GetDefaultROMSize() const { return 0x2000; }