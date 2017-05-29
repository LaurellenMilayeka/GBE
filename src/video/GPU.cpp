#include "GPU.hpp"
#include "RAM.hpp"

Graphics::GPU *Graphics::GPU::_singleton = nullptr;

Graphics::GPU::GPU() {
  this->_nbrRefresh = 0;

#ifndef NOGRAPHICS

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(Core::Window::Instance()->GetWindow());

#endif

}

Graphics::GPU::~GPU() {

}

Graphics::GPU *Graphics::GPU::Instance() {
  if (Graphics::GPU::_singleton == nullptr) {
    Graphics::GPU::_singleton = new Graphics::GPU();
  }
  return (Graphics::GPU::_singleton);
}

void Graphics::GPU::DrawScanLine(CPU::Z80 *cpu) {
  uint8_t status = Engine::RAM::GetByte(0xFF40);
  uint8_t lcdc_status = Engine::RAM::GetByte(0xFF41);

  if (Engine::RAM::GetByte(0xFF45) == Engine::RAM::GetByte(0xFF44)) {
    uint8_t iFlags = Engine::RAM::GetByte(0xFF0F);

    iFlags |= (1 << 1);
    lcdc_status |= (1 << 2);
    Engine::RAM::SetByte(0xFF41, lcdc_status);
    Engine::RAM::SetByte(0xFF0F, iFlags);
  } else {
    lcdc_status &= ~(1 << 2);
    Engine::RAM::SetByte(0xFF41, lcdc_status);
  }
  this->_lcdc = status;
  switch ((lcdc_status & 3)) {
  case 0:
    if (cpu->clock.t >= 204) {
      Engine::RAM::SetByte(0xFF44, Engine::RAM::GetByte(0xFF44) + 1);
      lcdc_status |= (1 << 1);
      lcdc_status |= (1 << 0);
      Engine::RAM::SetByte(0xFF41, lcdc_status);
    }
    break;
  case 3:
    if (cpu->clock.t >= 172) {
      if (Engine::RAM::GetByte(0xFF44) < 144) {
	if (((this->_lcdc >> 0) & 1) == 1) {
	  this->RenderTiles();
	}
	/*if (((this->_lcdc >> 1) & 1) == 1) {
	  this->RenderSprites();
	  }*/
	lcdc_status &= ~(1 << 0);
	lcdc_status &= ~(1 << 1);
      } else {
	lcdc_status |= (1 << 0);
	lcdc_status &= ~(1 << 1);
      }
      Engine::RAM::SetByte(0xFF41, lcdc_status);
    }
    break;
  case 1:
    if (cpu->clock.t >= 456) {
      uint8_t iFlags = Engine::RAM::GetByte(0xFF0F);
      
      this->_nbrRefresh++;
      iFlags |= (1 << 0);
      Engine::RAM::SetByte(0xFF0F, iFlags);
      Engine::RAM::SetByte(0xFF44, Engine::RAM::GetByte(0xFF44) + 1);
      if (Engine::RAM::GetByte(0xFF44) > 153) {

#ifndef NOGRAPHICS
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRasterPos2i(-1, 1);
	glPixelZoom(1, -1);
	glDrawPixels(160, 144, GL_RGB, GL_UNSIGNED_BYTE, this->_data);
	SDL_GL_SwapWindow(Core::Window::Instance()->GetWindow());

#endif
	
	Engine::RAM::SetByte(0xFF44, 0);
	lcdc_status |= (1 << 1);
	lcdc_status |= (1 << 0);
	Engine::RAM::SetByte(0xFF41, lcdc_status);
	isFrameDone = true;
      }
    }
    break; 
  }
}

int GetColour(uint8_t colour, uint16_t address) {
  uint8_t palette = Engine::RAM::GetByte(address);
  int hi = 0;
  int lo = 0;

  switch (colour)
    {
    case 0: hi = 1 ; lo = 0 ;break ;
    case 1: hi = 3 ; lo = 2 ;break ;
    case 2: hi = 5 ; lo = 4 ;break ;
    case 3: hi = 7 ; lo = 6 ;break ;
    }

  int ret_colour = 0;
  ret_colour = ((palette >> hi) & 1) << 1;
  ret_colour |= ((palette >> lo) & 1);

  return ret_colour;
}

void Graphics::GPU::RenderTiles() {
  uint16_t tileData = 0;
  uint16_t backgroundMemory = 0;
  bool unsig = true;
  uint8_t scrollY = Engine::RAM::GetByte(0xFF42);
  uint8_t scrollX = Engine::RAM::GetByte(0xFF43);
  uint8_t windowY = Engine::RAM::GetByte(0xFF4A);
  uint8_t windowX = Engine::RAM::GetByte(0xFF4B) - 7;
  uint8_t yPos = 0;
  bool usingWindow = false;
  uint16_t tileRow = 0;
  
  if (((this->_lcdc >> 5) & 1) == 1) {
    if (windowY <= Engine::RAM::GetByte(0xFF44)) {
      usingWindow = true;
    }
  }
  if (((this->_lcdc  >> 4) & 1) == 1) {
    tileData = 0x8000;
  } else {
    tileData = 0x8800;
    unsig = false;
  }
  if (usingWindow) {
    if (((this->_lcdc >> 3) & 1) == 1) {
      backgroundMemory = 0x9C00 ;
    } else {
      backgroundMemory = 0x9800 ;
    }
  } else {
    if (((this->_lcdc >> 6) & 1) == 1) {
      backgroundMemory = 0x9C00 ;
    } else {
      backgroundMemory = 0x9800 ;
    }
  }
  if (!usingWindow) {
    yPos = scrollY + Engine::RAM::GetByte(0xFF44);
  } else {
    yPos = Engine::RAM::GetByte(0xFF44) - windowY;
  }
  tileRow = (((yPos / 8)) * 32);
  for (int x = 0 ; x < GB_SCR_WIDTH; x++)
    {
      uint8_t xPos = x+scrollX;
      uint16_t tileCol = 0;
      short tileNum = 0;
      uint16_t tileAddress = 0;
      uint16_t tileLocation = 0;
      uint8_t line = 0;
      uint8_t data1 = 0, data2 = 0;
      int colourBit = 0;
      int colourNum = 0;
      int col = 0;
      int red = 0, green = 0, blue = 0;
      int scanline = 0;
      
      if (usingWindow) {
	if (x >= windowX) {
	    xPos = x - windowX ;
	  }
      }
      tileCol = (xPos / 8);
      tileAddress = backgroundMemory + tileRow + tileCol;
      tileLocation = tileData;
      if(unsig) {
	tileNum =(uint8_t)Engine::RAM::GetByte(tileAddress);
      } else {
	tileNum =(char)Engine::RAM::GetByte(tileAddress);
      }
      if (unsig) {
	tileLocation += (tileNum * 16);
      } else {
	tileLocation += ((tileNum + 128) *16);
      }
      line = yPos % 8;
      line *= 2;
      data1 = Engine::RAM::GetByte(tileLocation + line);
      data2 = Engine::RAM::GetByte(tileLocation + line + 1);
      colourBit = xPos % 8;
      colourBit -= 7;
      colourBit *= -1;
      colourNum = ((data2 >> colourBit) & 1);
      colourNum <<= 1;
      colourNum |= ((data1 >> colourBit) & 1);
      col = GetColour(colourNum, 0xFF47);
      switch(col) {
      case 0:
	red = 255;
	green = 255;
	blue = 255;
	break;
      case 1:
	red = 0xCC;
	green = 0xCC;
	blue = 0xCC;
	break;
      case 2:
	red = 0x77;
	green = 0x77;
	blue = 0x77;
	break;
      }
      scanline = Engine::RAM::GetByte(0xFF44) ;
      /*if ((scanline < 0) || (scanline > 143) || (x < 0) || (x > (GB_SCR_WIDTH - 1))) {
	continue;
	}*/
      this->_data[scanline][x][0] = red;
      this->_data[scanline][x][1] = green;
      this->_data[scanline][x][2] = blue;
    }
}
