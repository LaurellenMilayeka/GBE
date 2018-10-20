//
// Created by Flox Ajuro on 12/09/2018.
//

#include <RAM.hpp>
#include <Display.hpp>
#include <iostream>
#include "GPU.hpp"

using namespace GBE;

GPU::GPU() {
    this->_gpuClock = 0;
    this->_lcdStatus = 0;
    this->SetVideoMode(VideoMode::OAM);
}

GPU::~GPU() {

}

bool GPU::IsStatusInterruptEnabled(LCDStatus toCheck) {
    return ((this->_lcdStatus & toCheck) == toCheck);
}

bool GPU::IsLCDEnabled() const {
    return (((this->_lcdControl >> 7) & 1) == 1);
}

Word GPU::GetBGTileMapAddress() {
    if ((this->_lcdControl & LCDControl::BG_TILE_DATA_ADDRESS) == LCDControl::BG_TILE_DATA_ADDRESS) {
        return (0x9C00);
    } else {
        return (0x9800);
    }
}

Word GPU::GetTileDataAddress() {
    if ((this->_lcdControl & LCDControl::BG_WINDOW_TILE_DATA_ADDRESS) == LCDControl::BG_WINDOW_TILE_DATA_ADDRESS) {
        return (0x8000);
    } else {
        return (0x8800);
    }
}

Word GPU::GetWindowTileAddress() {
    if ((this->_lcdControl & LCDControl::WINDOW_TILE_MAP) == LCDControl::WINDOW_TILE_MAP) {
        return (0x9C00);
    } else {
        return (0x9800);
    }
}

void GPU::ProcessLineData() {
    Word address, tileMap;
    bool isSigned = true, usingWindow = false;
    Byte scrollX = RAM::Read8(0xFF43), scrollY = RAM::Read8(0xFF42);
    Byte windowX = (Byte)(RAM::Read8(0xFF4B) - 7), windowY = RAM::Read8(0xFF4A);

    if ((this->_lcdControl >> 5) & 1) {
        if (RAM::Read8(0xFF44) >= windowY) {
            usingWindow = true;
        }
    }
    address = this->GetTileDataAddress();
    isSigned = (address == 0x8800);
    if (!usingWindow) tileMap = this->GetBGTileMapAddress();
    else tileMap = this->GetWindowTileAddress();
    Byte y = (usingWindow) ? RAM::Read8(LY) - windowY : scrollY + RAM::Read8(LY);
    Word tileRow = ((Byte)(y / 8));
    for (int i = 0; i < 160; i++) {
        Byte x = (usingWindow && i >= windowX) ? (Byte)(i - windowX) : (Byte)(i + scrollX);
        Word tileColumn = (Word)(x / 8);
        Word tileAddress = (Word)(tileMap + tileRow * 32 + tileColumn);
        Word tileNum = (isSigned) ? (SignedByte)(RAM::Read8(tileAddress)) : (Byte)(RAM::Read8(tileAddress));
        Word tile = (isSigned) ? (Word)(address + ((tileNum + 128) * 16)) : (Word)(address + (tileNum * 16));
        Byte lno = (Byte)(y % 8);
        Byte data1 = RAM::Read8((Word)(tile + lno * 2));
        Byte data2 = RAM::Read8((Word)(tile + lno * 2 + 1));
        Byte req_bit = (Byte)(7 - (x % 8));
        Byte bit1 = (Byte)((data1 >> req_bit) & 1);
        Byte bit2 = (Byte)((data2 >> req_bit) & 1);
        Byte colorID = (bit2 << 1) | (bit1);
        this->_color[i] = colorID;
        int color = GetColour(colorID, PALETTE);
        int red, green, blue;

        if (color == Colour::WHITE) {red = 0xE0; green = 0xF8; blue = 0xD0;}
        else if (color == Colour::WHITE_GRAY) {red = 0x88; green = 0xC0; blue = 0x70;}
        else if (color == Colour::DARK_GRAY) {red = 0x34; green = 0x68; blue = 0x56;}
        else {red = 0x08; green = 0x18; blue = 0x20;}
        this->_data[i] = {(Byte) red, (Byte) green, (Byte) blue, 255};
    }
}

void GPU::ProcessSprites() {
    bool use8x16 = false;
    if ((this->_lcdControl & 0x04) == 0x04) {
        use8x16 = true;
    }
    for (unsigned int sprite = 0; sprite < 40; sprite++) {
        Byte index = (Byte)(sprite * 4);
        Byte yPos = (Byte)(RAM::Read8((Word)(0xFE00 + index)) - 16);
        Byte xPos = (Byte)(RAM::Read8((Word)(0xFE00 + index + 1)) - 8);
        Byte tileLocation = RAM::Read8((Word)(0xFE00 + index + 2));
        Byte attributes = RAM::Read8((Word)(0xFE00 + index + 3));
        bool yFlip = ((attributes & 0x40) == 0x40);
        bool xFlip = ((attributes & 0x20) == 0x20);
        bool hasPriority = ((attributes & 0x80) != 0x80);
        Byte scanline = RAM::Read8(LY);
        Byte ySize = (use8x16) ? 15 : 7;

        if ((scanline >= yPos) && (scanline <= (yPos + ySize))) {
            Byte line = scanline - yPos;
            if (yFlip) {
                line -= ySize;
                line *= -1;
            }
            line *= 2;
            Word dataAdress = (Word)((0x8000 + (tileLocation * 16)) + line);
            Byte data1 = RAM::Read8(dataAdress);
            Byte data2 = RAM::Read8((Word)(dataAdress + 1));
            for (int tilePixel = 7; tilePixel >= 0; tilePixel--) {
                int colourBit = tilePixel;
                if (xFlip) {
                    colourBit -= 7;
                    colourBit *= -1;
                }
                int colourNum = ((data2 >> colourBit) & 1);
                colourNum <<= 1;
                colourNum |= ((data1 >> colourBit) & 1);
                Word colourAddress = (Word)(((attributes & 0x10) == 0) ? 0xFF48 : 0xFF49);
                int col = this->GetColour((Byte)colourNum, colourAddress);
                int red = 0, green = 0, blue = 0;
                if (colourNum == 0) {
                    continue;
                }
                if (col == Colour::WHITE) {red = 0xE0; green = 0xF8; blue = 0xD0;}
                else if (col == Colour::WHITE_GRAY) {red = 0x88; green = 0xC0; blue = 0x70;}
                else if (col == Colour::DARK_GRAY) {red = 0x34; green = 0x68; blue = 0x56;}
                else {red = 0x08; green = 0x18; blue = 0x20;}
                Byte xPix = (Byte)(0 - tilePixel);
                xPix += 7;
                int pixel = xPos + xPix;
                if (hasPriority || this->_color[pixel] == 0) {
                    this->_data[pixel] = {(Byte)red, (Byte)green, (Byte)blue, 255};
                }
            }
        }
    }
}

int GPU::GetColour(Byte data, Word address) {
    Byte palette = RAM::Read8(address);
    int hi = 0, lo = 0;

    switch (data)
    {
        case 0:
            hi = 1;
            lo = 0;
            break;
        case 1:
            hi = 3;
            lo = 2;
            break;
        case 2:
            hi = 5;
            lo = 4;
            break;
        case 3:
            hi = 7;
            lo = 6;
            break;
    }

    int ret_colour = 0;
    ret_colour = ((palette >> hi) & 1) << 1;
    ret_colour |= ((palette >> lo) & 1);

    return (ret_colour);
}

void GPU::Step(GBE::CPU &cpu) {
    this->_gpuClock += cpu.GetLastInstrCycles();
    this->_lcdControl = RAM::Read8(0xFF40);
    if (this->IsLCDEnabled()) {
        switch (this->GetVideoMode()) {
            case VideoMode::OAM:
                if (this->_gpuClock >= 80) {
                    this->SetVideoMode(VideoMode::PIXEL_TRANSFER);
                    this->_gpuClock -= 80;
                }
                break;
            case VideoMode::PIXEL_TRANSFER:
                if (this->_gpuClock >= 172) {
                    this->_gpuClock -= 172;
                    if (((this->_lcdControl) & 0x01) == 0x01) {
                        this->ProcessLineData();
                    }
                    if (((this->_lcdControl) & 0x02) == 0x02) {
                        this->ProcessSprites();
                    }
                    Display::UpdateDataScreen(this->_data);
                    this->SetVideoMode(VideoMode::HBLANK);
                }
                break;
            case VideoMode::HBLANK:
                if (this->_gpuClock >= 204) {
                    this->_gpuClock -= 204;

                    RAM::GetRAM()[LY] = (Byte) (RAM::Read8(LY) + 1);
                    if (RAM::Read8(LY) == 143) {
                        if (cpu.CheckIFEnabledInterrupt(Interrupt::INT_VBLANK)) {
                            cpu.EnableInterrupt(Interrupt::INT_VBLANK);
                        }
                        this->SetVideoMode(VideoMode::VBLANK);
                    } else {
                        this->SetVideoMode(VideoMode::OAM);
                    }
                }
                break;
            case VideoMode::VBLANK:
                if (this->_gpuClock >= 456) {
                    this->_gpuClock -= 456;

                    RAM::GetRAM()[LY] = (Byte) (RAM::Read8(LY) + 1);
                    if (RAM::Read8(LY) > 153) {
                        Display::RefreshData();
                        this->SetVideoMode(VideoMode::OAM);
                        RAM::Write8(0, LY);
                    }
                }
                break;
        }
    }
}

VideoMode GPU::GetVideoMode() {
    char toTest;

    toTest = (char)(this->_lcdStatus & 0x07);
    if (toTest == 2) return (VideoMode::OAM);
    else if (toTest == 3) return (VideoMode::PIXEL_TRANSFER);
    else if (toTest == 0) return (VideoMode::HBLANK);
    else return (VideoMode::VBLANK);

}

void GPU::SetVideoMode(GBE::VideoMode videoMode) {
    this->_lcdStatus = ((this->_lcdStatus >> 2) << 2) + videoMode;
}