//
// Created by Flox Ajuro on 08/09/2018.
//

#include <RAM.hpp>
#include "CPU.hpp"

using namespace GBE;

CPU::CPU() {
    this->_af = 0x00;
    this->_bc = 0x00;
    this->_de = 0x00;
    this->_hl = 0x00;
    this->_pc = 0x00;
    this->_sp = 0x00;
}

bool CPU::IsClockEnabled() const {
    return (((RAM::Read8(TMC) >> 2) & 1) == 1);
}


void CPU::UpdateTimers() {
//    int frequency = this->GetTimerFrequency();
}

void CPU::EnableInterrupts() {
    this->_ime = true;
}

void CPU::DisableInterrupts() {
    this->_ime = false;
}

bool CPU::HasInterrupt(GBE::Interrupt toCheck) {
    return (((RAM::Read8(0xFF0F) >> toCheck) & 1) == 1 && ((RAM::Read8(0xFFFF) >> toCheck) & 1) == 1);
}

bool CPU::IsInterruptsEnabled() const {
    return (this->_ime);
}

Byte CPU::GetFlags() {
    return ((Byte)(this->_flags.to_ulong()));
}

void CPU::SetFlags(unsigned int mask) {
    Byte flags = (Byte)(this->_af & 0xFF);
    flags |= mask;
    this->_af = ((this->_af >> 8) << 8) + flags;
}

void CPU::UnsetFlag(unsigned int mask) {
    Byte flags = (Byte)(this->_af & 0xFF);
    flags &= ~mask;
    this->_af = ((this->_af >> 8) << 8) + flags;
}

bool CPU::IsFlagSet(unsigned int mask) const {
    return (((this->_af & 0xFF) & mask) == mask);
}

Byte CPU::GetRegistry8Value(GBE::Registry8 reg) const {
    Byte toReturn;

    switch (reg) {
        case Registry8::A:
            toReturn = (Byte)(this->_af >> 8);
            break;
        case Registry8::B:
            toReturn = (Byte)(this->_bc >> 8);
            break;
        case Registry8::C:
            toReturn = (Byte)(this->_bc & 0xFF);
            break;
        case Registry8::D:
            toReturn = (Byte)(this->_de >> 8);
            break;
        case Registry8::E:
            toReturn = (Byte)(this->_de & 0xFF);
            break;
        case Registry8::H:
            toReturn = (Byte)(this->_hl >> 8);
            break;
        case Registry8::L:
            toReturn = (Byte)(this->_hl & 0xFF);
            break;
        default:
            toReturn = 0;
            break;
    }
    return (toReturn);
}

Word CPU::GetRegistry16Value(GBE::Registry16 reg) const {
    Word toReturn;

    switch (reg) {
        case Registry16::AF:
            toReturn = this->_af;
            break;
        case Registry16::BC:
            toReturn = this->_bc;
            break;
        case Registry16::DE:
            toReturn = this->_de;
            break;
        case Registry16::HL:
            toReturn = this->_hl;
            break;
        case Registry16::SP:
            toReturn = this->_sp;
            break;
        case Registry16::PC:
            toReturn = this->_pc;
            break;
        default:
            toReturn = 0;
            break;
    }
    return (toReturn);
}

void CPU::SetRegistry8Value(GBE::Registry8 reg, Byte value) {
    switch (reg) {
        case Registry8::A:
            this->_af = (Word)((value << 8) + (this->_af & 0xFF));
            break;
        case Registry8::B:
            this->_bc = (Word)((value << 8) + (this->_bc & 0xFF));
            break;
        case Registry8::C:
            this->_bc = (Word)(((this->_bc >> 8) << 8) + value);
            break;
        case Registry8::D:
            this->_de = (Word)((value << 8) + (this->_de & 0xFF));
            break;
        case Registry8::E:
            this->_de = (Word)(((this->_de >> 8) << 8) + value);
            break;
        case Registry8::H:
            this->_hl = (Word)((value << 8) + (this->_hl & 0xFF));
            break;
        case Registry8::L:
            this->_hl = (Word)(((this->_hl >> 8) << 8) + value);
            break;
    }
}

void CPU::SetRegistry16Value(GBE::Registry16 reg, Word value) {
    switch (reg) {
        case Registry16::AF:
            this->_af = value;
            break;
        case Registry16::BC:
            this->_bc = value;
            break;
        case Registry16::DE:
            this->_de = value;
            break;
        case Registry16::HL:
            this->_hl = value;
            break;
        case Registry16::PC:
            this->_pc = value;
            break;
        case Registry16::SP:
            this->_sp = value;
            break;
    }
}

void CPU::PushToStack(Word value) {
    RAM::Write8((Byte)(value >> 8), --(this->_sp));
    RAM::Write8((Byte)(value & 0xFF), --(this->_sp));
}

void CPU::PushToStack(Byte value) {
    RAM::Write8(value, --this->_sp);
}

Word CPU::PopFromStack() {
    Byte toReturn1;
    Byte toReturn2;
    Word toReturn;

    toReturn1 = (Byte)RAM::Read8(this->_sp++);
    toReturn2 = (Byte)RAM::Read8(this->_sp++);
    toReturn = (toReturn2 << 8) + toReturn1;
    return (toReturn);
}

Word CPU::GetProgramCounter() const {
    return (this->_pc);
}

Byte CPU::GetNextInstruction() {
    return ((Byte)RAM::Read8(this->_pc++));
}

void CPU::JumpRelative(int amountToJump) {
    this->_pc += amountToJump;
}

unsigned char CPU::GetLastInstrCycles() const {
    return (this->_lastInstrCycles);
}

void CPU::SetLastInstrCycles(unsigned char cycles) {
    this->_lastInstrCycles = cycles;
}

void CPU::TickClock(char nbrCycles) {
    this->_clock += nbrCycles;
}

void CPU::EnableInterrupt(GBE::Interrupt toSet) {
    Byte flag = RAM::Read8(0xFF0F);

    flag |= (1 << toSet);
    RAM::Write8(flag, 0xFF0F);
}

void CPU::SetupInterrupt(GBE::Interrupt toSet) {
    Byte ifReg = RAM::Read8(0xFF0F);

    this->PushToStack(this->_pc);
    this->DisableInterrupts();
    switch (toSet) {
        case Interrupt::INT_VBLANK:
            this->_pc = 0x0040;
            ifReg &= ~(1 << Interrupt::INT_VBLANK);
            break;
        case Interrupt::INT_LCD_STAT:
            this->_pc = 0x0048;
            ifReg &= ~(1 << Interrupt::INT_LCD_STAT);
            break;
        case Interrupt::INT_TIMER:
            this->_pc = 0x0050;
            ifReg &= ~(1 << Interrupt::INT_TIMER);
            break;
        case Interrupt::INT_SERIAL:
            this->_pc = 0x0058;
            ifReg &= ~(1 << Interrupt::INT_SERIAL);
            break;
        case Interrupt::INT_JOYPAD:
            this->_pc = 0x0060;
            ifReg &= ~(1 << Interrupt::INT_JOYPAD);
            break;
    }
    RAM::Write8(ifReg, 0xFF0F);
}

void CPU::INC8(GBE::Registry8 reg) {
    if ((this->GetRegistry8Value(reg) & 0x0F) == 0x0F) {
        this->SetFlags(Flags::HALF_CARRY);
    } else {
        this->UnsetFlag(Flags::HALF_CARRY);
    }
    this->SetRegistry8Value(reg, (Byte)(this->GetRegistry8Value(reg) + 1));
    if (this->GetRegistry8Value(reg) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION);
}

void CPU::INC8(Word address) {
    if ((RAM::Read8(address) & 0x0F) == 0x0F) {
        this->SetFlags(Flags::HALF_CARRY);
    } else {
        this->UnsetFlag(Flags::HALF_CARRY);
    }
    RAM::Write8((Byte)(RAM::Read8(address) + 1), address);
    if (RAM::Read8(address) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION);
}

void CPU::INC16(GBE::Registry16 reg) {
    this->SetRegistry16Value(reg, (Word)(this->GetRegistry16Value(reg) + 1));
}

void CPU::DEC8(GBE::Registry8 reg) {
    if ((this->GetRegistry8Value(reg) & 0xF) == 0) {
        this->SetFlags(Flags::HALF_CARRY);
    } else {
        this->UnsetFlag(Flags::HALF_CARRY);
    }
    this->SetRegistry8Value(reg, (Byte)(this->GetRegistry8Value(reg) - 1));
    if (this->GetRegistry8Value(reg) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->SetFlags(Flags::OPERATION);
}

void CPU::DEC8(Word address) {
    if ((RAM::Read8(address) & 0xF) == 0) {
        this->SetFlags(Flags::HALF_CARRY);
    } else {
        this->UnsetFlag(Flags::HALF_CARRY);
    }
    RAM::Write8((Byte)(RAM::Read8(address) - 1), address);
    if (RAM::Read8(address) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->SetFlags(Flags::OPERATION);
}

void CPU::DEC16(GBE::Registry16 reg) {
    this->SetRegistry16Value(reg, (Word)(this->GetRegistry16Value(reg) - 1));
}

void CPU::ADD8(GBE::Registry8 dst, Word toAdd) {
    Word result = (Word)(this->GetRegistry8Value(dst) + RAM::Read8(toAdd));

    if (result & 0xFF00) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    if ((((this->GetRegistry8Value(dst) & 0xF) + (RAM::Read8(toAdd) & 0xF)) & 0x10) == 0x10) {
        this->SetFlags(Flags::HALF_CARRY);
    } else {
        this->UnsetFlag(Flags::HALF_CARRY);
    }
    this->SetRegistry8Value(dst, (Byte)result);
    if (this->GetRegistry8Value(dst) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION);
}

void CPU::ADD8(GBE::Registry8 dst, GBE::Registry8 toAdd) {
    Word result = (Word)(this->GetRegistry8Value(dst) + this->GetRegistry8Value(toAdd));

    if (result & 0xFF00) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    if ((((this->GetRegistry8Value(dst) & 0xF) + (this->GetRegistry8Value(toAdd) & 0xF)) & 0x10) == 0x10) {
        this->SetFlags(Flags::HALF_CARRY);
    } else {
        this->UnsetFlag(Flags::HALF_CARRY);
    }
    this->SetRegistry8Value(dst, (Byte)result);
    if (this->GetRegistry8Value(dst) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION);
}

void CPU::ADD16(GBE::Registry16 dst, GBE::Registry16 toAdd) {
    if ((this->GetRegistry16Value(dst) + this->GetRegistry16Value(toAdd)) > 0xFFFF) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    if ((((this->GetRegistry16Value(dst) & 0xF) + (this->GetRegistry16Value(toAdd) & 0xF)) & 0x10) == 0x10) {
        this->SetFlags(Flags::HALF_CARRY);
    } else {
        this->UnsetFlag(Flags::HALF_CARRY);
    }
    this->SetRegistry16Value(dst, (Word)(this->GetRegistry16Value(dst) + this->GetRegistry16Value(toAdd)));
    this->UnsetFlag(Flags::OPERATION);
}

void CPU::ADC8(GBE::Registry8 dst, Word toAdd) {
    Byte carry = (Byte)(this->IsFlagSet(Flags::CARRY) ? 1 : 0);

    if ((this->GetRegistry8Value(dst) + RAM::Read8(toAdd) + carry) > 255) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    if ((((this->GetRegistry8Value(dst) & 0x0F) + (RAM::Read8(toAdd) & 0x0F) + (carry & 0x0F)) & 0x10) == 0x10) {
        this->SetFlags(Flags::HALF_CARRY);
    } else {
        this->UnsetFlag(Flags::HALF_CARRY);
    }
    this->SetRegistry8Value(dst, (Byte)(this->GetRegistry8Value(dst) + RAM::Read8(toAdd) + carry));
    if (this->GetRegistry8Value(dst) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
}

void CPU::ADC8(GBE::Registry8 dst, Registry8 toAdd) {
    Byte carry = (Byte)(this->IsFlagSet(Flags::CARRY) ? 1 : 0);

    if ((this->GetRegistry8Value(dst) + this->GetRegistry8Value(toAdd) + carry) > 255) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    if ((((this->GetRegistry8Value(dst) & 0x0F) + (this->GetRegistry8Value(toAdd) & 0x0F) + (carry & 0x0F)) & 0x10) == 0x10) {
        this->SetFlags(Flags::HALF_CARRY);
    } else {
        this->UnsetFlag(Flags::HALF_CARRY);
    }
    this->SetRegistry8Value(dst, (Byte)(this->GetRegistry8Value(dst) + this->GetRegistry8Value(toAdd) + carry));
    if (this->GetRegistry8Value(dst) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
}

void CPU::SUB8(GBE::Registry8 dst, Word toSub) {
    if (RAM::Read8(toSub) > this->GetRegistry8Value(dst)) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    if ((this->GetRegistry8Value(dst) & 0xF) < (RAM::Read8(toSub) & 0xF)) {
        this->SetFlags(Flags::HALF_CARRY);
    } else {
        this->UnsetFlag(Flags::HALF_CARRY);
    }
    this->SetRegistry8Value(dst, (Byte)(this->GetRegistry8Value(dst) - RAM::Read8(toSub)));
    if (this->GetRegistry8Value(dst) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->SetFlags(Flags::OPERATION);
}

void CPU::SUB8(GBE::Registry8 dst, GBE::Registry8 toSub) {
    if (this->GetRegistry8Value(toSub) > this->GetRegistry8Value(dst)) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    if ((this->GetRegistry8Value(dst) & 0xF) < (this->GetRegistry8Value(toSub) & 0xF)) {
        this->SetFlags(Flags::HALF_CARRY);
    } else {
        this->UnsetFlag(Flags::HALF_CARRY);
    }
    this->SetRegistry8Value(dst, (Byte)(this->GetRegistry8Value(dst) - this->GetRegistry8Value(toSub)));
    if (this->GetRegistry8Value(dst) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->SetFlags(Flags::OPERATION);
}

void CPU::SBC8(GBE::Registry8 dst, GBE::Registry8 toSbc) {
    Byte carry = (Byte)(this->IsFlagSet(Flags::CARRY) ? 1 : 0);
    Byte value = (Byte)(this->GetRegistry8Value(toSbc) + carry);

    if ((value > this->GetRegistry8Value(dst))) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    if (value == this->GetRegistry8Value(dst)) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    if ((value & 0xF) > (this->GetRegistry8Value(dst) & 0xF)) {
        this->SetFlags(Flags::HALF_CARRY);
    } else {
        this->UnsetFlag(Flags::HALF_CARRY);
    }
    this->SetRegistry8Value(dst, this->GetRegistry8Value(dst) - value);
}

void CPU::SBC8(GBE::Registry8 dst, Word toSbc) {
    Byte carry = (Byte)(this->IsFlagSet(Flags::CARRY) ? 1 : 0);
    Byte value = (Byte)(RAM::Read8(toSbc) + carry);

    if ((value > this->GetRegistry8Value(dst))) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    if (value == this->GetRegistry8Value(dst)) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    if ((value & 0xF) > (this->GetRegistry8Value(dst) & 0xF)) {
        this->SetFlags(Flags::HALF_CARRY);
    } else {
        this->UnsetFlag(Flags::HALF_CARRY);
    }
    this->SetRegistry8Value(dst, this->GetRegistry8Value(dst) - value);
}

void CPU::AND8(GBE::Registry8 dst, GBE::Registry8 toAnd) {
    this->SetRegistry8Value(dst, (Byte)(this->GetRegistry8Value(dst) & this->GetRegistry8Value(toAnd)));
    if (this->GetRegistry8Value(dst) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->SetFlags(Flags::HALF_CARRY);
    this->UnsetFlag(Flags::CARRY | Flags::OPERATION);
}

void CPU::AND8(GBE::Registry8 dst, Word toAnd) {
    this->SetRegistry8Value(dst, (Byte)(this->GetRegistry8Value(dst) & RAM::Read8(toAnd)));
    if (this->GetRegistry8Value(dst) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->SetFlags(Flags::HALF_CARRY);
    this->UnsetFlag(Flags::CARRY | Flags::OPERATION);
}

void CPU::XOR8(GBE::Registry8 dst, GBE::Registry8 toXor) {
    this->SetRegistry8Value(dst, (Byte)(this->GetRegistry8Value(dst) ^ this->GetRegistry8Value(toXor)));
    if (this->GetRegistry8Value(dst) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY | Flags::CARRY);
}

void CPU::XOR8(GBE::Registry8 dst, Word toXor) {
    this->SetRegistry8Value(dst, (Byte)(this->GetRegistry8Value(dst) ^ RAM::Read8(toXor)));
    if (this->GetRegistry8Value(dst) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY | Flags::CARRY);
}

void CPU::OR8(GBE::Registry8 dst, GBE::Registry8 toOr) {
    this->SetRegistry8Value(dst, (Byte)(this->GetRegistry8Value(dst) | this->GetRegistry8Value(toOr)));
    if (this->GetRegistry8Value(dst) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::CARRY | Flags::HALF_CARRY);
}

void CPU::OR8(GBE::Registry8 dst, Word toOr) {
    this->SetRegistry8Value(dst, (Byte)(this->GetRegistry8Value(dst) | RAM::Read8(toOr)));
    if (this->GetRegistry8Value(dst) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::CARRY | Flags::HALF_CARRY);
}

void CPU::CP8(GBE::Registry8 orig, GBE::Registry8 toCp) {
    if (this->GetRegistry8Value(orig) == this->GetRegistry8Value(toCp)) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    if (this->GetRegistry8Value(toCp) > this->GetRegistry8Value(orig)) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    if ((this->GetRegistry8Value(toCp) & 0xF) > (this->GetRegistry8Value(orig) & 0xF)) {
        this->SetFlags(Flags::HALF_CARRY);
    } else {
        this->UnsetFlag(Flags::HALF_CARRY);
    }
    this->SetFlags(Flags::OPERATION);
}

void CPU::CP8(GBE::Registry8 orig, Word toCp) {
    if (this->GetRegistry8Value(orig) == RAM::Read8(toCp)) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    if (RAM::Read8(toCp) > this->GetRegistry8Value(orig)) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    if ((RAM::Read8(toCp) & 0xF) > (this->GetRegistry8Value(orig) & 0xF)) {
        this->SetFlags(Flags::HALF_CARRY);
    } else {
        this->UnsetFlag(Flags::HALF_CARRY);
    }
    this->SetFlags(Flags::OPERATION);
}

void CPU::RLC(GBE::Registry8 toShift) {
    if (((this->GetRegistry8Value(toShift) >> 7) & 1) == 1) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    this->SetRegistry8Value(toShift, (Byte)((this->GetRegistry8Value(toShift) << 1) + ((this->IsFlagSet(Flags::CARRY)) ? 1 : 0)));
    if (this->GetRegistry8Value(toShift) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY);
}

void CPU::RLC(Word toShift) {
    if (((RAM::Read8(toShift) >> 7) & 1) == 1) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    RAM::Write8((Byte)((RAM::Read8(toShift) << 1) + ((this->IsFlagSet(Flags::CARRY)) ? 1 : 0)), toShift);
    if (RAM::Read8(toShift) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY);
}

void CPU::RRC(GBE::Registry8 toShift) {
    if (((this->GetRegistry8Value(toShift) >> 0) & 1) == 1) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    this->SetRegistry8Value(toShift, (Byte)((((this->IsFlagSet(Flags::CARRY)) ? 1 : 0) << 7) | (this->GetRegistry8Value(toShift) >> 1)));
    if (this->GetRegistry8Value(toShift) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY);
}

void CPU::RRC(Word toShift) {
    if (((RAM::Read8(toShift) >> 0) & 1) == 1) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    RAM::Write8((Byte)((((this->IsFlagSet(Flags::CARRY)) ? 1 : 0) << 7) | (RAM::Read8(toShift) >> 1)), toShift);
    if (RAM::Read8(toShift) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY);
}

void CPU::RR(GBE::Registry8 toShift) {
    bool hasCarry = (Byte)(((this->GetRegistry8Value(toShift) >> 0) & 1) == 1);
    this->SetRegistry8Value(toShift, (Byte)(((this->IsFlagSet(Flags::CARRY) ? 1 : 0) << 7) | (this->GetRegistry8Value(toShift) >> 1)));
    if (hasCarry) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    if (this->GetRegistry8Value(toShift) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY);
}

void CPU::RR(Word toShift) {
    bool hasCarry = (Byte)(((RAM::Read8(toShift) >> 0) & 1) == 1);
    RAM::Write8((Byte)(((this->IsFlagSet(Flags::CARRY) ? 1 : 0) << 7) | (RAM::Read8(toShift) >> 1)), toShift);
    if (hasCarry) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    if (RAM::Read8(toShift) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY);
}

void CPU::RL(GBE::Registry8 toShift) {
    bool hasCarry = (Byte)(((this->GetRegistry8Value(toShift) >> 7) & 1) == 1);
    this->SetRegistry8Value(toShift, (Byte)((this->GetRegistry8Value(toShift) << 1) + (this->IsFlagSet(Flags::CARRY) ? 1 : 0)));
    if (hasCarry) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    if (this->GetRegistry8Value(toShift) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY);
}

void CPU::RL(Word toShift) {
    bool hasCarry = (Byte)(((RAM::Read8(toShift) >> 7) & 1) == 1);
    RAM::Write8((Byte)((RAM::Read8(toShift) << 1) + (this->IsFlagSet(Flags::CARRY) ? 1 : 0)), toShift);
    if (hasCarry) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    if (RAM::Read8(toShift) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY);
}

void CPU::SLA(GBE::Registry8 toShift) {
    if (((this->GetRegistry8Value(toShift) >> 7) & 1) == 1) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    this->SetRegistry8Value(toShift, (Byte)(this->GetRegistry8Value(toShift) << 1));
    if (this->GetRegistry8Value(toShift) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY);
}

void CPU::SLA(Word toShift) {
    if (((RAM::Read8(toShift) >> 7) & 1) == 1) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    RAM::Write8((Byte)(RAM::Read8(toShift) << 1), toShift);
    if (RAM::Read8(toShift) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY);
}

void CPU::SRA(GBE::Registry8 toShift) {
    Byte msb = (Byte)(this->GetRegistry8Value(toShift) & 0x80);
    if (((this->GetRegistry8Value(toShift) >> 0) & 1) == 1) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    this->SetRegistry8Value(toShift, (Byte)((msb << 7) | (this->GetRegistry8Value(toShift) >> 1)));
    if (this->GetRegistry8Value(toShift) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY);
}

void CPU::SRA(Word toShift) {
    Byte msb = (Byte)(RAM::Read8(toShift) & 0x80);
    if (((RAM::Read8(toShift) >> 0) & 1) == 1) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    RAM::Write8((Byte)((msb << 7) | (RAM::Read8(toShift) >> 1)), toShift);
    if (RAM::Read8(toShift) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY);
}

void CPU::SRL(GBE::Registry8 toShift) {
    if (((this->GetRegistry8Value(toShift) >> 0) & 1) == 1) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    this->SetRegistry8Value(toShift, (Byte)(this->GetRegistry8Value(toShift) >> 1));
    if (this->GetRegistry8Value(toShift) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY);
}

void CPU::SRL(Word toShift) {
    if (((RAM::Read8(toShift) >> 0) & 1) == 1) {
        this->SetFlags(Flags::CARRY);
    } else {
        this->UnsetFlag(Flags::CARRY);
    }
    RAM::Write8((Byte)(RAM::Read8(toShift) >> 1), toShift);
    if (RAM::Read8(toShift) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY);
}

void CPU::SWAP(GBE::Registry8 toSwap) {
    this->SetRegistry8Value(toSwap, (Byte)((this->GetRegistry8Value(toSwap) & 0x0F) << 4 | (this->GetRegistry8Value(toSwap) & 0xF0) >> 4));
    if (this->GetRegistry8Value(toSwap) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY | Flags::CARRY);
}

void CPU::SWAP(Word toSwap) {
    RAM::Write8((Byte)((RAM::Read8(toSwap) & 0x0F) << 4 | (RAM::Read8(toSwap) & 0xF0) >> 4), toSwap);
    if (RAM::Read8(toSwap) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY | Flags::CARRY);
}

void CPU::BIT(GBE::Registry8 dst, Byte toTest) {
    if (((this->GetRegistry8Value(dst) >> toTest) & 1) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->SetFlags(Flags::HALF_CARRY);
    this->UnsetFlag(Flags::OPERATION);
}

void CPU::BIT(Word dst, Byte toTest) {
    if (((RAM::Read8(dst) >> toTest) & 1) == 0) {
        this->SetFlags(Flags::ZERO);
    } else {
        this->UnsetFlag(Flags::ZERO);
    }
    this->SetFlags(Flags::HALF_CARRY);
    this->UnsetFlag(Flags::OPERATION);
}

void CPU::RES(GBE::Registry8 dst, Byte toReset) {
    Byte value = this->GetRegistry8Value(dst);

    value &= ~(1 << toReset);
    this->SetRegistry8Value(dst, value);
}

void CPU::RES(Word dst, Byte toReset) {
    Byte value = RAM::Read8(dst);

    value &= ~(1 << toReset);
    RAM::Write8(value, dst);
}

void CPU::SET(GBE::Registry8 dst, Byte toSet) {
    Byte value = this->GetRegistry8Value(dst);

    value |= (1 << toSet);
    this->SetRegistry8Value(dst, value);
}

void CPU::SET(Word dst, Byte toSet) {
    Byte value = RAM::Read8(dst);

    value |= (1 << toSet);
    RAM::Write8(value, dst);
}
