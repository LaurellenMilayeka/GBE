#include "GPU.hpp"

Graphics::GPU::_singleton = nullptr;

Graphics::GPU::GPU() {
  this->_lcdc = 0;
  this->_lcdStatus = 0;
}

Graphics::GPU::~GPU() {

}

Graphics::GPU *Graphics::GPU::Instance() {
  if (Graphics::GPU::_singleton == nullptr) {
    Graphics::GPU::_singleton = new Graphics::GPU();
  }
  return (Graphics::GPU::_singleton);
}

void Graphics::GPU::EnableLCD() {
  this->_lcdc = Engine::RAM::GetByte(0xFF40);
  this->_lcdc |= (1 << 7);
  Engine::RAM::SetByte(0xFF40, this->_lcdc);
}

void Graphics::GPU::EnableWindow() {
  this->_lcdc = Engine::RAM::GetByte(0xFF40);
  this->_lcdc |= (1 << 5);
  Engine::RAM::SetByte(0xFF40, this->_lcdc);
}

void Graphics::GPU::EnableSpriteDisplay() {
  this->_lcdc = Engine::RAM::GetByte(0xFF40);
  this->_lcdc |= (1 << 1);
  Engine::RAM::SetByte(0xFF40, this->_lcdc);
}
