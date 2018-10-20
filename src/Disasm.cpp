//
// Created by Flox Ajuro on 08/09/2018.
//

#include <RAM.hpp>
#include <Debug.hpp>
#include <iostream>
#include <OpCodes.hpp>
#include "Disasm.hpp"

using namespace GBE;

void Disasm::OP0x00(GBE::CPU &) {

}

void Disasm::OP0x01(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::BC, RAM::Read16(cpu.GetProgramCounter()));
    cpu.JumpRelative(2);
}

void Disasm::OP0x02(GBE::CPU &cpu) {
    RAM::Write8(cpu.GetRegistry8Value(Registry8::A), cpu.GetRegistry16Value(Registry16::BC));
}

void Disasm::OP0x03(GBE::CPU &cpu) {
    cpu.INC16(Registry16::BC);
}

void Disasm::OP0x04(GBE::CPU &cpu) {
    cpu.INC8(Registry8::B);
}

void Disasm::OP0x05(GBE::CPU &cpu) {
    cpu.DEC8(Registry8::B);
}

void Disasm::OP0x06(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::B, (Byte)RAM::Read8(cpu.GetProgramCounter()));
    cpu.JumpRelative(1);
}

void Disasm::OP0x07(GBE::CPU &cpu) {
    Byte hasCarry = (Byte)((cpu.GetRegistry8Value(Registry8::A) & 0x80) >> 7);
    if (hasCarry == 1) cpu.SetFlags(Flags::CARRY);
    else cpu.UnsetFlag(Flags::CARRY);
    cpu.SetRegistry8Value(Registry8::A, (cpu.GetRegistry8Value(Registry8::A) << 1) + hasCarry);
    cpu.UnsetFlag(Flags::ZERO | Flags::OPERATION | Flags::HALF_CARRY);
}

void Disasm::OP0x08(GBE::CPU &cpu) {
    RAM::Write16(cpu.GetRegistry16Value(Registry16::SP), RAM::Read16(cpu.GetProgramCounter()));
    cpu.JumpRelative(2);
}

void Disasm::OP0x09(GBE::CPU &cpu) {
    cpu.ADD16(Registry16::HL, Registry16::BC);
}

void Disasm::OP0x0A(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, (Byte)(RAM::Read8(cpu.GetRegistry16Value(Registry16::BC))));
}

void Disasm::OP0x0B(GBE::CPU &cpu) {
    cpu.DEC16(Registry16::BC);
}

void Disasm::OP0x0C(GBE::CPU &cpu) {
    cpu.INC8(Registry8::C);
}

void Disasm::OP0x0D(GBE::CPU &cpu) {
    cpu.DEC8(Registry8::C);
}

void Disasm::OP0x0E(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::C, (Byte)RAM::Read8(cpu.GetProgramCounter()));
    cpu.JumpRelative(1);
}

void Disasm::OP0x0F(GBE::CPU &cpu) {
    Byte hasCarry = (Byte)(cpu.GetRegistry8Value(Registry8::A) & 0x01);
    if (hasCarry == 1) cpu.SetFlags(Flags::CARRY);
    else cpu.UnsetFlag(Flags::CARRY);
    cpu.SetRegistry8Value(Registry8::A, (Byte)((hasCarry << 7) + (cpu.GetRegistry8Value(Registry8::A) >> 1)));
    cpu.UnsetFlag(Flags::ZERO | Flags::HALF_CARRY | Flags::OPERATION);
}

void Disasm::OP0x10(GBE::CPU &cpu) {
    cpu.JumpRelative(1);
}

void Disasm::OP0x11(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::DE, (Word)RAM::Read16(cpu.GetProgramCounter()));
    cpu.JumpRelative(2);
}

void Disasm::OP0x12(GBE::CPU &cpu) {
    RAM::Write8(cpu.GetRegistry8Value(Registry8::A), cpu.GetRegistry16Value(Registry16::DE));
}

void Disasm::OP0x13(GBE::CPU &cpu) {
    cpu.INC16(Registry16::DE);
}

void Disasm::OP0x14(GBE::CPU &cpu) {
    cpu.INC8(Registry8::D);
}

void Disasm::OP0x15(GBE::CPU &cpu) {
    cpu.DEC8(Registry8::D);
}

void Disasm::OP0x16(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::D, (Byte)RAM::Read8(cpu.GetProgramCounter()));
    cpu.JumpRelative(1);
}

void Disasm::OP0x17(GBE::CPU &cpu) {
    Byte hasCarry = (Byte)((cpu.GetRegistry8Value(Registry8::A) & 0x80) >> 7);
    cpu.SetRegistry8Value(Registry8::A, (Byte)((cpu.GetRegistry8Value(Registry8::A) << 1) + ((cpu.IsFlagSet(Flags::CARRY) ? 1 : 0))));
    if (hasCarry == 1) cpu.SetFlags(Flags::CARRY);
    else cpu.UnsetFlag(Flags::CARRY);
    cpu.UnsetFlag(Flags::ZERO | Flags::OPERATION | Flags::HALF_CARRY);
}

void Disasm::OP0x18(GBE::CPU &cpu) {
    cpu.JumpRelative((SignedByte)RAM::Read8(cpu.GetProgramCounter()) + 1);
}

void Disasm::OP0x19(GBE::CPU &cpu) {
    cpu.ADD16(Registry16::HL, Registry16::DE);
}

void Disasm::OP0x1A(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, (Byte)RAM::Read8(cpu.GetRegistry16Value(Registry16::DE)));
}

void Disasm::OP0x1B(GBE::CPU &cpu) {
    cpu.DEC16(Registry16::DE);
}

void Disasm::OP0x1C(GBE::CPU &cpu) {
    cpu.INC8(Registry8::E);
}

void Disasm::OP0x1D(GBE::CPU &cpu) {
    cpu.DEC8(Registry8::E);
}

void Disasm::OP0x1E(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::E, (Byte)RAM::Read8(cpu.GetProgramCounter()));
    cpu.JumpRelative(1);
}

void Disasm::OP0x1F(GBE::CPU &cpu) {
    Byte hasCarry = (Byte)(cpu.GetRegistry8Value(Registry8::A) & 0x01);
    cpu.SetRegistry8Value(Registry8::A, (Byte)((((cpu.IsFlagSet(Flags::CARRY)) ? 1 : 0 ) << 7) + (cpu.GetRegistry8Value(Registry8::A) >> 1)));
    if (hasCarry == 1) cpu.SetFlags(Flags::CARRY);
    else cpu.UnsetFlag(Flags::CARRY);
    cpu.UnsetFlag(Flags::ZERO | Flags::OPERATION | Flags::HALF_CARRY);
}

void Disasm::OP0x20(GBE::CPU &cpu) {
    if (!cpu.IsFlagSet(Flags::ZERO)) {
        cpu.JumpRelative((SignedByte)RAM::Read8((Word) (cpu.GetProgramCounter())) + 1);
        cpu.AddToLastInstrCycles(4);
    } else {
        cpu.JumpRelative(1);
    }
}

void Disasm::OP0x21(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::HL, (Word)RAM::Read16(cpu.GetProgramCounter()));
    cpu.JumpRelative(2);
}

void Disasm::OP0x22(GBE::CPU &cpu) {
    RAM::Write8(cpu.GetRegistry8Value(Registry8::A), cpu.GetRegistry16Value(Registry16::HL));
    cpu.SetRegistry16Value(Registry16::HL, (Word)(cpu.GetRegistry16Value(Registry16::HL) + 1));
}

void Disasm::OP0x23(GBE::CPU &cpu) {
    cpu.INC16(Registry16::HL);
}

void Disasm::OP0x24(GBE::CPU &cpu) {
    cpu.INC8(Registry8::H);
}

void Disasm::OP0x25(GBE::CPU &cpu) {
    cpu.DEC8(Registry8::H);
}

void Disasm::OP0x26(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::H, RAM::Read8(cpu.GetProgramCounter()));
    cpu.JumpRelative(1);
}

void Disasm::OP0x27(GBE::CPU &cpu) {
    Byte rega = cpu.GetRegistry8Value(Registry8::A);
    Byte correction = 0;

    if (cpu.IsFlagSet(Flags::HALF_CARRY) || (!cpu.IsFlagSet(Flags::OPERATION) && (rega & 0xF) > 9)) {
        correction |= 0x06;
    }
    if (cpu.IsFlagSet(Flags::CARRY) || (!cpu.IsFlagSet(Flags::OPERATION) && (rega > 0x99))) {
        correction |= 0x60;
        cpu.SetFlags(Flags::CARRY);
    }
    rega += (SignedByte)((cpu.IsFlagSet(Flags::OPERATION) ? (correction * -1) : correction));
    cpu.SetRegistry8Value(Registry8::A, rega);
    cpu.UnsetFlag(Flags::HALF_CARRY);
    if (cpu.GetRegistry8Value(Registry8::A) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);
}

void Disasm::OP0x28(GBE::CPU &cpu) {
    if (cpu.IsFlagSet(Flags::ZERO)) {
        cpu.JumpRelative((SignedByte)RAM::Read8((Word) (cpu.GetProgramCounter())) + 1);
        cpu.AddToLastInstrCycles(4);
    } else {
        cpu.JumpRelative(1);
    }
}

void Disasm::OP0x29(GBE::CPU &cpu) {
    cpu.ADD16(Registry16::HL, Registry16::HL);
}

void Disasm::OP0x2A(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, RAM::Read8(cpu.GetRegistry16Value(Registry16::HL)));
    cpu.SetRegistry16Value(Registry16::HL, (Word)(cpu.GetRegistry16Value(Registry16::HL) + 1));
}

void Disasm::OP0x2B(GBE::CPU &cpu) {
    cpu.DEC16(Registry16::HL);
}

void Disasm::OP0x2C(GBE::CPU &cpu) {
    cpu.INC8(Registry8::L);
}

void Disasm::OP0x2D(GBE::CPU &cpu) {
    cpu.DEC8(Registry8::L);
}

void Disasm::OP0x2E(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::L, (Byte)RAM::Read8(cpu.GetProgramCounter()));
    cpu.JumpRelative(1);
}

void Disasm::OP0x2F(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, ~(cpu.GetRegistry8Value(Registry8::A)));
    cpu.SetFlags(Flags::OPERATION | Flags::HALF_CARRY);
}

void Disasm::OP0x30(GBE::CPU &cpu) {
    if (!cpu.IsFlagSet(Flags::CARRY)) {
        cpu.JumpRelative((SignedByte)(RAM::Read8(cpu.GetProgramCounter()) + 1));
        cpu.AddToLastInstrCycles(4);
    } else {
        cpu.JumpRelative(1);
    }
}

void Disasm::OP0x31(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::SP, (Word)RAM::Read16(cpu.GetProgramCounter()));
    cpu.JumpRelative(2);
}

void Disasm::OP0x32(GBE::CPU &cpu) {
    RAM::Write8(cpu.GetRegistry8Value(Registry8::A), cpu.GetRegistry16Value(Registry16::HL));
    cpu.SetRegistry16Value(Registry16::HL, (Word)(cpu.GetRegistry16Value(Registry16::HL) - 1));
}

void Disasm::OP0x33(CPU &cpu) {
    cpu.INC16(Registry16::SP);
}

void Disasm::OP0x34(GBE::CPU &cpu) {
    cpu.INC8(cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0x35(GBE::CPU &cpu) {
    cpu.DEC8(cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0x36(GBE::CPU &cpu) {
    RAM::Write8(RAM::Read8(cpu.GetProgramCounter()), cpu.GetRegistry16Value(Registry16::HL));
    cpu.JumpRelative(1);
}

void Disasm::OP0x37(CPU &cpu) {
    cpu.SetFlags(Flags::CARRY);
    cpu.UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY);
}

void Disasm::OP0x38(GBE::CPU &cpu) {
    if (cpu.IsFlagSet(Flags::CARRY)) {
        cpu.JumpRelative((SignedByte)(RAM::Read8(cpu.GetProgramCounter()) + 1));
        cpu.AddToLastInstrCycles(4);
    } else {
        cpu.JumpRelative(1);
    }
}

void Disasm::OP0x39(GBE::CPU &cpu) {
    cpu.ADD16(Registry16::HL, Registry16::SP);
}

void Disasm::OP0x3A(CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, RAM::Read8(cpu.GetRegistry16Value(Registry16::HL)));
    cpu.SetRegistry16Value(Registry16::HL, (Word)(cpu.GetRegistry16Value(Registry16::HL) - 1));
}

void Disasm::OP0x3B(CPU &cpu) {
    cpu.DEC16(Registry16::SP);
}

void Disasm::OP0x3C(GBE::CPU &cpu) {
    cpu.INC8(Registry8::A);
}

void Disasm::OP0x3D(GBE::CPU &cpu) {
    cpu.DEC8(Registry8::A);
}

void Disasm::OP0x3E(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, (Byte)RAM::Read8(cpu.GetProgramCounter()));
    cpu.JumpRelative(1);
}

void Disasm::OP0x3F(GBE::CPU &cpu) {
    cpu.UnsetFlag(Flags::OPERATION | Flags::HALF_CARRY | Flags::CARRY);
}

void Disasm::OP0x40(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::B, cpu.GetRegistry8Value(Registry8::B));
}

void Disasm::OP0x41(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::B, cpu.GetRegistry8Value(Registry8::C));
}

void Disasm::OP0x42(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::B, cpu.GetRegistry8Value(Registry8::D));
}

void Disasm::OP0x43(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::B, cpu.GetRegistry8Value(Registry8::E));
}

void Disasm::OP0x44(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::B, cpu.GetRegistry8Value(Registry8::H));
}

void Disasm::OP0x45(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::B, cpu.GetRegistry8Value(Registry8::L));
}

void Disasm::OP0x46(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::B, RAM::Read8(cpu.GetRegistry16Value(Registry16::HL)));
}

void Disasm::OP0x47(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::B, cpu.GetRegistry8Value(Registry8::A));
}

void Disasm::OP0x48(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::C, cpu.GetRegistry8Value(Registry8::B));
}

void Disasm::OP0x49(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::C, cpu.GetRegistry8Value(Registry8::C));
}

void Disasm::OP0x4A(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::C, cpu.GetRegistry8Value(Registry8::D));
}

void Disasm::OP0x4B(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::C, cpu.GetRegistry8Value(Registry8::E));
}

void Disasm::OP0x4C(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::C, cpu.GetRegistry8Value(Registry8::H));
}

void Disasm::OP0x4D(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::C, cpu.GetRegistry8Value(Registry8::L));
}

void Disasm::OP0x4E(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::C, RAM::Read8(cpu.GetRegistry16Value(Registry16::HL)));
}

void Disasm::OP0x4F(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::C, cpu.GetRegistry8Value(Registry8::A));
}

void Disasm::OP0x50(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::D, cpu.GetRegistry8Value(Registry8::B));
}

void Disasm::OP0x51(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::D, cpu.GetRegistry8Value(Registry8::C));
}

void Disasm::OP0x52(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::D, cpu.GetRegistry8Value(Registry8::D));
}

void Disasm::OP0x53(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::D, cpu.GetRegistry8Value(Registry8::E));
}

void Disasm::OP0x54(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::D, cpu.GetRegistry8Value(Registry8::H));
}

void Disasm::OP0x55(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::D, cpu.GetRegistry8Value(Registry8::L));
}

void Disasm::OP0x56(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::D, RAM::Read8(cpu.GetRegistry16Value(Registry16::HL)));
}

void Disasm::OP0x57(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::D, cpu.GetRegistry8Value(Registry8::A));
}

void Disasm::OP0x58(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::E, cpu.GetRegistry8Value(Registry8::B));
}

void Disasm::OP0x59(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::E, cpu.GetRegistry8Value(Registry8::C));
}

void Disasm::OP0x5A(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::E, cpu.GetRegistry8Value(Registry8::D));
}

void Disasm::OP0x5B(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::E, cpu.GetRegistry8Value(Registry8::E));
}

void Disasm::OP0x5C(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::E, cpu.GetRegistry8Value(Registry8::H));
}

void Disasm::OP0x5D(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::E, cpu.GetRegistry8Value(Registry8::L));
}

void Disasm::OP0x5E(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::E, RAM::Read8(cpu.GetRegistry16Value(Registry16::HL)));
}

void Disasm::OP0x5F(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::E, cpu.GetRegistry8Value(Registry8::A));
}

void Disasm::OP0x60(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::H, cpu.GetRegistry8Value(Registry8::B));
}

void Disasm::OP0x61(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::H, cpu.GetRegistry8Value(Registry8::C));
}

void Disasm::OP0x62(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::H, cpu.GetRegistry8Value(Registry8::D));
}

void Disasm::OP0x63(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::H, cpu.GetRegistry8Value(Registry8::E));
}

void Disasm::OP0x64(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::H, cpu.GetRegistry8Value(Registry8::H));
}

void Disasm::OP0x65(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::H, cpu.GetRegistry8Value(Registry8::L));
}

void Disasm::OP0x66(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::H, RAM::Read8(cpu.GetRegistry16Value(Registry16::HL)));
}

void Disasm::OP0x67(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::H, cpu.GetRegistry8Value(Registry8::A));
}

void Disasm::OP0x68(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::L, cpu.GetRegistry8Value(Registry8::B));
}

void Disasm::OP0x69(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::L, cpu.GetRegistry8Value(Registry8::C));
}

void Disasm::OP0x6A(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::L, cpu.GetRegistry8Value(Registry8::D));
}

void Disasm::OP0x6B(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::L, cpu.GetRegistry8Value(Registry8::E));
}

void Disasm::OP0x6C(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::L, cpu.GetRegistry8Value(Registry8::H));
}

void Disasm::OP0x6D(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::L, cpu.GetRegistry8Value(Registry8::L));
}

void Disasm::OP0x6E(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::L, RAM::Read8(cpu.GetRegistry16Value(Registry16::HL)));
}

void Disasm::OP0x6F(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::L, cpu.GetRegistry8Value(Registry8::A));
}

void Disasm::OP0x70(GBE::CPU &cpu) {
    RAM::Write8(cpu.GetRegistry8Value(Registry8::B), cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0x71(GBE::CPU &cpu) {
    RAM::Write8(cpu.GetRegistry8Value(Registry8::C), cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0x72(GBE::CPU &cpu) {
    RAM::Write8(cpu.GetRegistry8Value(Registry8::D), cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0x73(GBE::CPU &cpu) {
    RAM::Write8(cpu.GetRegistry8Value(Registry8::E), cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0x74(GBE::CPU &cpu) {
    RAM::Write8(cpu.GetRegistry8Value(Registry8::H), cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0x75(GBE::CPU &cpu) {
    RAM::Write8(cpu.GetRegistry8Value(Registry8::L), cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0x76(GBE::CPU &cpu) {
    if (cpu.IsInterruptsEnabled()) {

    } else {
        cpu.SetRegistry16Value(Registry16::PC, (Word)(cpu.GetRegistry16Value(Registry16::PC) + 1));
    }
}

void Disasm::OP0x77(GBE::CPU &cpu) {
    RAM::Write8(cpu.GetRegistry8Value(Registry8::A), cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0x78(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, cpu.GetRegistry8Value(Registry8::B));
}

void Disasm::OP0x79(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, cpu.GetRegistry8Value(Registry8::C));
}

void Disasm::OP0x7A(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, cpu.GetRegistry8Value(Registry8::D));
}

void Disasm::OP0x7B(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, cpu.GetRegistry8Value(Registry8::E));
}

void Disasm::OP0x7C(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, cpu.GetRegistry8Value(Registry8::H));
}

void Disasm::OP0x7D(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, cpu.GetRegistry8Value(Registry8::L));
}

void Disasm::OP0x7E(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, RAM::Read8(cpu.GetRegistry16Value(Registry16::HL)));
}

void Disasm::OP0x7F(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, cpu.GetRegistry8Value(Registry8::A));
}

void Disasm::OP0x80(GBE::CPU &cpu) {
    cpu.ADD8(Registry8::A, Registry8::B);
}

void Disasm::OP0x81(GBE::CPU &cpu) {
    cpu.ADD8(Registry8::A, Registry8::C);
}

void Disasm::OP0x82(GBE::CPU &cpu) {
    cpu.ADD8(Registry8::A, Registry8::D);
}

void Disasm::OP0x83(GBE::CPU &cpu) {
    cpu.ADD8(Registry8::A, Registry8::E);
}

void Disasm::OP0x84(GBE::CPU &cpu) {
    cpu.ADD8(Registry8::A, Registry8::H);
}

void Disasm::OP0x85(GBE::CPU &cpu) {
    cpu.ADD8(Registry8::A, Registry8::L);
}

void Disasm::OP0x86(GBE::CPU &cpu) {
    cpu.ADD8(Registry8::A, cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0x87(GBE::CPU &cpu) {
    cpu.ADD8(Registry8::A, Registry8::A);
}

void Disasm::OP0x88(GBE::CPU &cpu) {
    cpu.ADC8(Registry8::A, Registry8::B);
}

void Disasm::OP0x89(GBE::CPU &cpu) {
    cpu.ADC8(Registry8::A, Registry8::C);
}

void Disasm::OP0x8A(GBE::CPU &cpu) {
    cpu.ADC8(Registry8::A, Registry8::D);
}

void Disasm::OP0x8B(GBE::CPU &cpu) {
    cpu.ADC8(Registry8::A, Registry8::E);
}

void Disasm::OP0x8C(GBE::CPU &cpu) {
    cpu.ADC8(Registry8::A, Registry8::H);
}

void Disasm::OP0x8D(GBE::CPU &cpu) {
    cpu.ADC8(Registry8::A, Registry8::L);
}

void Disasm::OP0x8E(GBE::CPU &cpu) {
    cpu.ADC8(Registry8::A, cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0x8F(GBE::CPU &cpu) {
    cpu.ADC8(Registry8::A, Registry8::A);
}

void Disasm::OP0x90(GBE::CPU &cpu) {
    cpu.SUB8(Registry8::A, Registry8::B);
}

void Disasm::OP0x91(GBE::CPU &cpu) {
    cpu.SUB8(Registry8::A, Registry8::C);
}

void Disasm::OP0x92(GBE::CPU &cpu) {
    cpu.SUB8(Registry8::A, Registry8::D);
}

void Disasm::OP0x93(GBE::CPU &cpu) {
    cpu.SUB8(Registry8::A, Registry8::E);
}

void Disasm::OP0x94(GBE::CPU &cpu) {
    cpu.SUB8(Registry8::A, Registry8::H);
}

void Disasm::OP0x95(GBE::CPU &cpu) {
    cpu.SUB8(Registry8::A, Registry8::L);
}

void Disasm::OP0x96(GBE::CPU &cpu) {
    cpu.SUB8(Registry8::A, cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0x97(GBE::CPU &cpu) {
    cpu.SUB8(Registry8::A, Registry8::A);
}

void Disasm::OP0x98(GBE::CPU &cpu) {
    cpu.SBC8(Registry8::A, Registry8::B);
}

void Disasm::OP0x99(GBE::CPU &cpu) {
    cpu.SBC8(Registry8::A, Registry8::C);
}

void Disasm::OP0x9A(GBE::CPU &cpu) {
    cpu.SBC8(Registry8::A, Registry8::D);
}

void Disasm::OP0x9B(GBE::CPU &cpu) {
    cpu.SBC8(Registry8::A, Registry8::E);
}

void Disasm::OP0x9C(GBE::CPU &cpu) {
    cpu.SBC8(Registry8::A, Registry8::H);
}

void Disasm::OP0x9D(GBE::CPU &cpu) {
    cpu.SBC8(Registry8::A, Registry8::L);
}

void Disasm::OP0x9E(GBE::CPU &cpu) {
    cpu.SBC8(Registry8::A, cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0x9F(GBE::CPU &cpu) {
    cpu.SBC8(Registry8::A, Registry8::A);
}

void Disasm::OP0xA0(GBE::CPU &cpu) {
    cpu.AND8(Registry8::A, Registry8::B);
}

void Disasm::OP0xA1(GBE::CPU &cpu) {
    cpu.AND8(Registry8::A, Registry8::C);
}

void Disasm::OP0xA2(GBE::CPU &cpu) {
    cpu.AND8(Registry8::A, Registry8::D);
}

void Disasm::OP0xA3(GBE::CPU &cpu) {
    cpu.AND8(Registry8::A, Registry8::E);
}

void Disasm::OP0xA4(GBE::CPU &cpu) {
    cpu.AND8(Registry8::A, Registry8::H);
}

void Disasm::OP0xA5(GBE::CPU &cpu) {
    cpu.AND8(Registry8::A, Registry8::L);
}

void Disasm::OP0xA6(GBE::CPU &cpu) {
    cpu.AND8(Registry8::A, cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0xA7(GBE::CPU &cpu) {
    cpu.AND8(Registry8::A, Registry8::A);
}

void Disasm::OP0xA8(GBE::CPU &cpu) {
    cpu.XOR8(Registry8::A, Registry8::B);
}

void Disasm::OP0xA9(GBE::CPU &cpu) {
    cpu.XOR8(Registry8::A, Registry8::C);
}

void Disasm::OP0xAA(GBE::CPU &cpu) {
    cpu.XOR8(Registry8::A, Registry8::D);
}

void Disasm::OP0xAB(GBE::CPU &cpu) {
    cpu.XOR8(Registry8::A, Registry8::E);
}

void Disasm::OP0xAC(GBE::CPU &cpu) {
    cpu.XOR8(Registry8::A, Registry8::H);
}

void Disasm::OP0xAD(GBE::CPU &cpu) {
    cpu.XOR8(Registry8::A, Registry8::L);
}

void Disasm::OP0xAE(GBE::CPU &cpu) {
    cpu.XOR8(Registry8::A, cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0xAF(GBE::CPU &cpu) {
    cpu.XOR8(Registry8::A, Registry8::A);
}

void Disasm::OP0xB0(GBE::CPU &cpu) {
    cpu.OR8(Registry8::A, Registry8::B);
}

void Disasm::OP0xB1(GBE::CPU &cpu) {
    cpu.OR8(Registry8::A, Registry8::C);
}

void Disasm::OP0xB2(GBE::CPU &cpu) {
    cpu.OR8(Registry8::A, Registry8::D);
}

void Disasm::OP0xB3(GBE::CPU &cpu) {
    cpu.OR8(Registry8::A, Registry8::E);
}

void Disasm::OP0xB4(GBE::CPU &cpu) {
    cpu.OR8(Registry8::A, Registry8::H);
}

void Disasm::OP0xB5(GBE::CPU &cpu) {
    cpu.OR8(Registry8::A, Registry8::L);
}

void Disasm::OP0xB6(GBE::CPU &cpu) {
    cpu.OR8(Registry8::A, cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0xB7(GBE::CPU &cpu) {
    cpu.OR8(Registry8::A, Registry8::A);
}

void Disasm::OP0xB8(GBE::CPU &cpu) {
    cpu.CP8(Registry8::A, Registry8::B);
}

void Disasm::OP0xB9(GBE::CPU &cpu) {
    cpu.CP8(Registry8::A, Registry8::C);
}

void Disasm::OP0xBA(GBE::CPU &cpu) {
    cpu.CP8(Registry8::A, Registry8::D);
}

void Disasm::OP0xBB(GBE::CPU &cpu) {
    cpu.CP8(Registry8::A, Registry8::E);
}

void Disasm::OP0xBC(GBE::CPU &cpu) {
    cpu.CP8(Registry8::A, Registry8::H);
}

void Disasm::OP0xBD(GBE::CPU &cpu) {
    cpu.CP8(Registry8::A, Registry8::L);
}

void Disasm::OP0xBE(GBE::CPU &cpu) {
    cpu.CP8(Registry8::A, cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0xBF(GBE::CPU &cpu) {
    cpu.CP8(Registry8::A, Registry8::A);
}

void Disasm::OP0xC0(GBE::CPU &cpu) {
    if (!cpu.IsFlagSet(Flags::ZERO)) {
        cpu.SetRegistry16Value(Registry16::PC, cpu.PopFromStack());
        cpu.AddToLastInstrCycles(12);
    }
}

void Disasm::OP0xC1(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::BC, cpu.PopFromStack());
}

void Disasm::OP0xC2(GBE::CPU &cpu) {
    if (!cpu.IsFlagSet(Flags::ZERO)) {
        cpu.SetRegistry16Value(Registry16::PC, RAM::Read16(cpu.GetProgramCounter()));
        cpu.AddToLastInstrCycles(4);
    } else {
        cpu.JumpRelative(2);
    }
}

void Disasm::OP0xC3(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::PC, RAM::Read16(cpu.GetProgramCounter()));
}

void Disasm::OP0xC4(GBE::CPU &cpu) {
    if (!cpu.IsFlagSet(Flags::ZERO)) {
        cpu.PushToStack((Word)(cpu.GetProgramCounter() + 2));
        cpu.SetRegistry16Value(Registry16::PC, RAM::Read16(cpu.GetProgramCounter()));
        cpu.AddToLastInstrCycles(12);
    } else {
        cpu.JumpRelative(2);
    }
}

void Disasm::OP0xC5(GBE::CPU &cpu) {
    cpu.PushToStack(cpu.GetRegistry16Value(Registry16::BC));
}

void Disasm::OP0xC6(GBE::CPU &cpu) {
    cpu.ADD8(Registry8::A, cpu.GetProgramCounter());
    cpu.JumpRelative(1);
}

void Disasm::OP0xC7(GBE::CPU &cpu) {
    cpu.PushToStack(cpu.GetProgramCounter());
    cpu.SetRegistry16Value(Registry16::PC, 0x0000);
}

void Disasm::OP0xC8(GBE::CPU &cpu) {
    if (cpu.IsFlagSet(Flags::ZERO)) {
        cpu.SetRegistry16Value(Registry16::PC, cpu.PopFromStack());
        cpu.AddToLastInstrCycles(12);
    }
}

void Disasm::OP0xC9(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::PC, cpu.PopFromStack());
}

void Disasm::OP0xCA(GBE::CPU &cpu) {
    if (cpu.IsFlagSet(Flags::ZERO)) {
        cpu.SetRegistry16Value(Registry16::PC, RAM::Read16(cpu.GetProgramCounter()));
        cpu.AddToLastInstrCycles(4);
    } else {
        cpu.JumpRelative(2);
    }
}

void Disasm::OP0xCB(GBE::CPU &cpu) {
    Byte instr;

    instr = cpu.GetNextInstruction();
    extOpCodes[instr].f(cpu);
    cpu.AddToLastInstrCycles(extOpCodes[instr].cycles);
}

void Disasm::OP0xCC(CPU &cpu) {
    if (cpu.IsFlagSet(Flags::ZERO)) {
        cpu.PushToStack((Word)(cpu.GetProgramCounter() + 2));
        cpu.SetRegistry16Value(Registry16::PC, RAM::Read16(cpu.GetProgramCounter()));
        cpu.AddToLastInstrCycles(12);
    } else {
        cpu.JumpRelative(2);
    }
}

void Disasm::OP0xCD(GBE::CPU &cpu) {
    cpu.PushToStack((Word)(cpu.GetProgramCounter() + 2));
    cpu.SetRegistry16Value(Registry16::PC, (Word)RAM::Read16(cpu.GetProgramCounter()));
}

void Disasm::OP0xCE(GBE::CPU &cpu) {
    cpu.ADC8(Registry8::A, cpu.GetProgramCounter());
    cpu.JumpRelative(1);
}

void Disasm::OP0xCF(GBE::CPU &cpu) {
    cpu.PushToStack(cpu.GetProgramCounter());
    cpu.SetRegistry16Value(Registry16::PC, 0x0008);
}

void Disasm::OP0xD0(GBE::CPU &cpu) {
    if (!cpu.IsFlagSet(Flags::CARRY)) {
        cpu.SetRegistry16Value(Registry16::PC, cpu.PopFromStack());
        cpu.AddToLastInstrCycles(12);
    }
}

void Disasm::OP0xD1(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::DE, cpu.PopFromStack());
}

void Disasm::OP0xD2(GBE::CPU &cpu) {
    if (!cpu.IsFlagSet(Flags::CARRY)) {
        cpu.SetRegistry16Value(Registry16::PC, RAM::Read16(cpu.GetProgramCounter()));
        cpu.AddToLastInstrCycles(4);
    } else {
        cpu.JumpRelative(2);
    }
}

void Disasm::OP0xD4(GBE::CPU &cpu) {
    if (!cpu.IsFlagSet(Flags::CARRY)) {
        cpu.PushToStack((Word)(cpu.GetProgramCounter() + 2));
        cpu.SetRegistry16Value(Registry16::PC, RAM::Read16(cpu.GetProgramCounter()));
        cpu.AddToLastInstrCycles(12);
    } else {
        cpu.JumpRelative(2);
    }
}

void Disasm::OP0xD5(GBE::CPU &cpu) {
    cpu.PushToStack(cpu.GetRegistry16Value(Registry16::DE));
}

void Disasm::OP0xD6(GBE::CPU &cpu) {
    cpu.SUB8(Registry8::A, cpu.GetProgramCounter());
    cpu.JumpRelative(1);
}

void Disasm::OP0xD7(CPU &cpu) {
    cpu.PushToStack(cpu.GetProgramCounter());
    cpu.SetRegistry16Value(Registry16::PC, 0x0010);
}

void Disasm::OP0xD8(GBE::CPU &cpu) {
    if (cpu.IsFlagSet(Flags::CARRY)) {
        cpu.SetRegistry16Value(Registry16::PC, cpu.PopFromStack());
        cpu.AddToLastInstrCycles(12);
    }
}

void Disasm::OP0xD9(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::PC, cpu.PopFromStack());
    cpu.EnableInterrupts();
}

void Disasm::OP0xDA(GBE::CPU &cpu) {
    if (cpu.IsFlagSet(Flags::CARRY)) {
        cpu.SetRegistry16Value(Registry16::PC, RAM::Read16(cpu.GetProgramCounter()));
        cpu.AddToLastInstrCycles(4);
    } else {
        cpu.JumpRelative(2);
    }
}

void Disasm::OP0xDC(CPU &cpu) {
    if (cpu.IsFlagSet(Flags::CARRY)) {
        cpu.PushToStack((Word)(cpu.GetProgramCounter() + 2));
        cpu.SetRegistry16Value(Registry16::PC, RAM::Read16(cpu.GetProgramCounter()));
        cpu.AddToLastInstrCycles(12);
    } else {
        cpu.JumpRelative(2);
    }
}

void Disasm::OP0xDE(CPU &cpu) {
    cpu.SBC8(Registry8::A, cpu.GetProgramCounter());
    cpu.JumpRelative(1);
}

void Disasm::OP0xDF(CPU &cpu) {
    cpu.PushToStack(cpu.GetProgramCounter());
    cpu.SetRegistry16Value(Registry16::PC, 0x0018);
}

void Disasm::OP0xE0(GBE::CPU &cpu) {
    RAM::Write8(cpu.GetRegistry8Value(Registry8::A), (Word)(0xFF00 + RAM::Read8(cpu.GetProgramCounter())));
    cpu.JumpRelative(1);
}

void Disasm::OP0xE1(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::HL, cpu.PopFromStack());
}

void Disasm::OP0xE2(GBE::CPU &cpu) {
    RAM::Write8(cpu.GetRegistry8Value(Registry8::A), (Word)(0xFF00 + cpu.GetRegistry8Value(Registry8::C)));
}

void Disasm::OP0xE5(GBE::CPU &cpu) {
    cpu.PushToStack(cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0xE6(GBE::CPU &cpu) {
    cpu.AND8(Registry8::A, cpu.GetProgramCounter());
    cpu.JumpRelative(1);
}

void Disasm::OP0xE7(CPU &cpu) {
    cpu.PushToStack(cpu.GetProgramCounter());
    cpu.SetRegistry16Value(Registry16::PC, 0x0020);
}

void Disasm::OP0xE8(GBE::CPU &cpu) {
    if ((cpu.GetRegistry16Value(Registry16::SP) + (SignedByte)(RAM::Read8(cpu.GetProgramCounter()))) > 0xFFFF) cpu.SetFlags(Flags::CARRY);
    else cpu.UnsetFlag(Flags::CARRY);
    cpu.SetRegistry16Value(Registry16::SP, (Word)(cpu.GetRegistry16Value(Registry16::SP) + (SignedByte)(RAM::Read8(cpu.GetProgramCounter()))));
    cpu.UnsetFlag(Flags::ZERO | Flags::OPERATION);
    cpu.JumpRelative(1);
}

void Disasm::OP0xE9(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::PC, cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0xEA(GBE::CPU &cpu) {
    RAM::Write8(cpu.GetRegistry8Value(Registry8::A), (Word)RAM::Read16(cpu.GetProgramCounter()));
    cpu.JumpRelative(2);
}

void Disasm::OP0xEE(GBE::CPU &cpu) {
    cpu.XOR8(Registry8::A, cpu.GetProgramCounter());
    cpu.JumpRelative(1);
}

void Disasm::OP0xEF(GBE::CPU &cpu) {
    cpu.PushToStack(cpu.GetProgramCounter());
    cpu.SetRegistry16Value(Registry16::PC, 0x0028);
}

void Disasm::OP0xF0(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, (Byte)RAM::Read8((Word)(0xFF00 + RAM::Read8(cpu.GetProgramCounter()))));
    cpu.JumpRelative(1);
}

void Disasm::OP0xF1(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::AF, cpu.PopFromStack() & 0xFFF0);
}

void Disasm::OP0xF2(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, (Byte)(RAM::Read8((Word)(0xFF00 + cpu.GetRegistry8Value(Registry8::C)))));
}

void Disasm::OP0xF3(GBE::CPU &cpu) {
    cpu.DisableInterrupts();
}

void Disasm::OP0xF5(GBE::CPU &cpu) {
    cpu.PushToStack(cpu.GetRegistry16Value(Registry16::AF));
}

void Disasm::OP0xF6(GBE::CPU &cpu) {
    cpu.OR8(Registry8::A, cpu.GetProgramCounter());
    cpu.JumpRelative(1);
}

void Disasm::OP0xF7(CPU &cpu) {
    cpu.PushToStack(cpu.GetProgramCounter());
    cpu.SetRegistry16Value(Registry16::PC, 0x0030);
}

void Disasm::OP0xF8(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::HL, cpu.GetRegistry16Value(Registry16::SP));
    if ((cpu.GetRegistry16Value(Registry16::HL) + (SignedWord)RAM::Read8(cpu.GetProgramCounter())) > 0xFFFF) cpu.SetFlags(Flags::CARRY);
    else cpu.UnsetFlag(Flags::CARRY);
    if (((cpu.GetRegistry16Value(Registry16::HL) & 0xFFF) + (SignedWord)(RAM::Read8(cpu.GetProgramCounter()) & 0xFFF)) & 0x1000) cpu.SetFlags(Flags::HALF_CARRY);
    else cpu.UnsetFlag(Flags::HALF_CARRY);
    cpu.SetRegistry16Value(Registry16::HL, (Word)(cpu.GetRegistry16Value(Registry16::HL) + (SignedWord)RAM::Read8(cpu.GetProgramCounter())));
    cpu.UnsetFlag(Flags::OPERATION | Flags::ZERO);
    cpu.JumpRelative(1);
}

void Disasm::OP0xF9(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::SP, cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::OP0xFA(GBE::CPU &cpu) {
    cpu.SetRegistry8Value(Registry8::A, RAM::Read8(RAM::Read16(cpu.GetProgramCounter())));
    cpu.JumpRelative(2);
}

void Disasm::OP0xFB(GBE::CPU &cpu) {
    cpu.EnableInterrupts();
}

void Disasm::OP0xFE(GBE::CPU &cpu) {
    cpu.CP8(Registry8::A, cpu.GetProgramCounter());
    cpu.JumpRelative(1);
}

void Disasm::OP0xFF(CPU &cpu) {
    cpu.PushToStack(cpu.GetProgramCounter());
    cpu.SetRegistry16Value(Registry16::PC, 0x0038);
}

void Disasm::EXT_OP0x00(GBE::CPU &cpu) {
    cpu.RLC(Registry8::B);
}

void Disasm::EXT_OP0x01(GBE::CPU &cpu) {
    cpu.RLC(Registry8::C);
}

void Disasm::EXT_OP0x02(GBE::CPU &cpu) {
    cpu.RLC(Registry8::D);
}

void Disasm::EXT_OP0x03(GBE::CPU &cpu) {
    cpu.RLC(Registry8::E);
}

void Disasm::EXT_OP0x04(GBE::CPU &cpu) {
    cpu.RLC(Registry8::H);
}

void Disasm::EXT_OP0x05(GBE::CPU &cpu) {
    cpu.RLC(Registry8::L);
}

void Disasm::EXT_OP0x06(GBE::CPU &cpu) {
    cpu.RLC(cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::EXT_OP0x07(GBE::CPU &cpu) {
    cpu.RLC(Registry8::A);
}

void Disasm::EXT_OP0x08(GBE::CPU &cpu) {
    cpu.RRC(Registry8::B);
}

void Disasm::EXT_OP0x09(GBE::CPU &cpu) {
    cpu.RRC(Registry8::C);
}

void Disasm::EXT_OP0x0A(GBE::CPU &cpu) {
    cpu.RRC(Registry8::D);
}

void Disasm::EXT_OP0x0B(GBE::CPU &cpu) {
    cpu.RRC(Registry8::E);
}

void Disasm::EXT_OP0x0C(GBE::CPU &cpu) {
    cpu.RRC(Registry8::H);
}

void Disasm::EXT_OP0x0D(GBE::CPU &cpu) {
    cpu.RRC(Registry8::L);
}

void Disasm::EXT_OP0x0E(GBE::CPU &cpu) {
    cpu.RRC(cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::EXT_OP0x0F(GBE::CPU &cpu) {
    cpu.RRC(Registry8::A);
}

void Disasm::EXT_OP0x10(GBE::CPU &cpu) {
    cpu.RL(Registry8::B);
}

void Disasm::EXT_OP0x11(GBE::CPU &cpu) {
    cpu.RL(Registry8::C);
}

void Disasm::EXT_OP0x12(GBE::CPU &cpu) {
    cpu.RL(Registry8::D);
}

void Disasm::EXT_OP0x13(GBE::CPU &cpu) {
    cpu.RL(Registry8::E);
}

void Disasm::EXT_OP0x14(GBE::CPU &cpu) {
    cpu.RL(Registry8::H);
}

void Disasm::EXT_OP0x15(GBE::CPU &cpu) {
    cpu.RL(Registry8::L);
}

void Disasm::EXT_OP0x16(GBE::CPU &cpu) {
    cpu.RL(cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::EXT_OP0x17(GBE::CPU &cpu) {
    cpu.RL(Registry8::A);
}

void Disasm::EXT_OP0x18(GBE::CPU &cpu) {
    cpu.RR(Registry8::B);
}

void Disasm::EXT_OP0x19(GBE::CPU &cpu) {
    cpu.RR(Registry8::C);
}

void Disasm::EXT_OP0x1A(GBE::CPU &cpu) {
    cpu.RR(Registry8::D);
}

void Disasm::EXT_OP0x1B(GBE::CPU &cpu) {
    cpu.RR(Registry8::E);
}

void Disasm::EXT_OP0x1C(GBE::CPU &cpu) {
    cpu.RR(Registry8::H);
}

void Disasm::EXT_OP0x1D(GBE::CPU &cpu) {
    cpu.RR(Registry8::L);
}

void Disasm::EXT_OP0x1E(GBE::CPU &cpu) {
    cpu.RR(cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::EXT_OP0x1F(GBE::CPU &cpu) {
    cpu.RR(Registry8::A);
}

void Disasm::EXT_OP0x20(GBE::CPU &cpu) {
    cpu.SLA(Registry8::B);
}

void Disasm::EXT_OP0x21(GBE::CPU &cpu) {
    cpu.SLA(Registry8::C);
}

void Disasm::EXT_OP0x22(GBE::CPU &cpu) {
    cpu.SLA(Registry8::D);
}

void Disasm::EXT_OP0x23(GBE::CPU &cpu) {
    cpu.SLA(Registry8::E);
}

void Disasm::EXT_OP0x24(GBE::CPU &cpu) {
    cpu.SLA(Registry8::H);
}

void Disasm::EXT_OP0x25(GBE::CPU &cpu) {
    cpu.SLA(Registry8::L);
}

void Disasm::EXT_OP0x26(GBE::CPU &cpu) {
    cpu.SLA(cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::EXT_OP0x27(GBE::CPU &cpu) {
    cpu.SLA(Registry8::A);
}

void Disasm::EXT_OP0x28(GBE::CPU &cpu) {
    cpu.SRA(Registry8::B);
}

void Disasm::EXT_OP0x29(GBE::CPU &cpu) {
    cpu.SRA(Registry8::C);
}

void Disasm::EXT_OP0x2A(GBE::CPU &cpu) {
    cpu.SRA(Registry8::D);
}

void Disasm::EXT_OP0x2B(GBE::CPU &cpu) {
    cpu.SRA(Registry8::E);
}

void Disasm::EXT_OP0x2C(GBE::CPU &cpu) {
    cpu.SRA(Registry8::H);
}

void Disasm::EXT_OP0x2D(GBE::CPU &cpu) {
    cpu.SRA(Registry8::L);
}

void Disasm::EXT_OP0x2E(GBE::CPU &cpu) {
    cpu.SRA(cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::EXT_OP0x2F(GBE::CPU &cpu) {
    cpu.SRA(Registry8::A);
}

void Disasm::EXT_OP0x30(GBE::CPU &cpu) {
    cpu.SWAP(Registry8::B);
}

void Disasm::EXT_OP0x31(GBE::CPU &cpu) {
    cpu.SWAP(Registry8::C);
}

void Disasm::EXT_OP0x32(GBE::CPU &cpu) {
    cpu.SWAP(Registry8::D);
}

void Disasm::EXT_OP0x33(GBE::CPU &cpu) {
    cpu.SWAP(Registry8::E);
}

void Disasm::EXT_OP0x34(GBE::CPU &cpu) {
    cpu.SWAP(Registry8::H);
}

void Disasm::EXT_OP0x35(GBE::CPU &cpu) {
    cpu.SWAP(Registry8::L);
}

void Disasm::EXT_OP0x36(GBE::CPU &cpu) {
    cpu.SWAP(cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::EXT_OP0x37(GBE::CPU &cpu) {
    cpu.SWAP(Registry8::A);
}

void Disasm::EXT_OP0x38(GBE::CPU &cpu) {
    cpu.SRL(Registry8::B);
}

void Disasm::EXT_OP0x39(GBE::CPU &cpu) {
    cpu.SRL(Registry8::C);
}

void Disasm::EXT_OP0x3A(GBE::CPU &cpu) {
    cpu.SRL(Registry8::D);
}

void Disasm::EXT_OP0x3B(GBE::CPU &cpu) {
    cpu.SRL(Registry8::E);
}

void Disasm::EXT_OP0x3C(GBE::CPU &cpu) {
    cpu.SRL(Registry8::H);
}

void Disasm::EXT_OP0x3D(GBE::CPU &cpu) {
    cpu.SRL(Registry8::L);
}

void Disasm::EXT_OP0x3E(GBE::CPU &cpu) {
    cpu.SRL(cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::EXT_OP0x3F(GBE::CPU &cpu) {
    cpu.SRL(Registry8::A);
}

void Disasm::EXT_OP0x40(CPU &cpu) {
    cpu.BIT(Registry8::B, 0);
}

void Disasm::EXT_OP0x41(CPU &cpu) {
    cpu.BIT(Registry8::C, 0);
}

void Disasm::EXT_OP0x42(CPU &cpu) {
    cpu.BIT(Registry8::D, 0);
}

void Disasm::EXT_OP0x43(CPU &cpu) {
    cpu.BIT(Registry8::E, 0);
}

void Disasm::EXT_OP0x44(CPU &cpu) {
    cpu.BIT(Registry8::H, 0);
}

void Disasm::EXT_OP0x45(CPU &cpu) {
    cpu.BIT(Registry8::L, 0);
}

void Disasm::EXT_OP0x46(CPU &cpu) {
    cpu.BIT(cpu.GetRegistry16Value(Registry16::HL), 0);
}

void Disasm::EXT_OP0x47(GBE::CPU &cpu) {
    cpu.BIT(Registry8::A, 0);
}

void Disasm::EXT_OP0x48(CPU &cpu) {
    cpu.BIT(Registry8::B, 1);
}

void Disasm::EXT_OP0x49(CPU &cpu) {
    cpu.BIT(Registry8::C, 1);
}

void Disasm::EXT_OP0x4A(CPU &cpu) {
    cpu.BIT(Registry8::D, 1);
}

void Disasm::EXT_OP0x4B(CPU &cpu) {
    cpu.BIT(Registry8::E, 1);
}

void Disasm::EXT_OP0x4C(CPU &cpu) {
    cpu.BIT(Registry8::H, 1);
}

void Disasm::EXT_OP0x4D(CPU &cpu) {
    cpu.BIT(Registry8::L, 1);
}

void Disasm::EXT_OP0x4E(CPU &cpu) {
    cpu.BIT(cpu.GetRegistry16Value(Registry16::HL), 1);
}

void Disasm::EXT_OP0x4F(GBE::CPU &cpu) {
    cpu.BIT(Registry8::A, 1);
}

void Disasm::EXT_OP0x50(GBE::CPU &cpu) {
    cpu.BIT(Registry8::B, 2);
}

void Disasm::EXT_OP0x51(CPU &cpu) {
    cpu.BIT(Registry8::C, 2);
}

void Disasm::EXT_OP0x52(CPU &cpu) {
    cpu.BIT(Registry8::D, 2);
}

void Disasm::EXT_OP0x53(CPU &cpu) {
    cpu.BIT(Registry8::E, 2);
}

void Disasm::EXT_OP0x54(CPU &cpu) {
    cpu.BIT(Registry8::H, 2);
}

void Disasm::EXT_OP0x55(CPU &cpu) {
    cpu.BIT(Registry8::L, 2);
}

void Disasm::EXT_OP0x56(GBE::CPU &cpu) {
    cpu.BIT(cpu.GetRegistry16Value(Registry16::HL), 2);
}

void Disasm::EXT_OP0x57(GBE::CPU &cpu) {
    cpu.BIT(Registry8::A, 2);
}

void Disasm::EXT_OP0x58(GBE::CPU &cpu) {
    cpu.BIT(Registry8::B, 3);
}

void Disasm::EXT_OP0x59(CPU &cpu) {
    cpu.BIT(Registry8::C, 3);
}

void Disasm::EXT_OP0x5A(CPU &cpu) {
    cpu.BIT(Registry8::D, 3);
}

void Disasm::EXT_OP0x5B(CPU &cpu) {
    cpu.BIT(Registry8::E, 3);
}

void Disasm::EXT_OP0x5C(CPU &cpu) {
    cpu.BIT(Registry8::H, 3);
}

void Disasm::EXT_OP0x5D(CPU &cpu) {
    cpu.BIT(Registry8::L, 3);
}

void Disasm::EXT_OP0x5E(GBE::CPU &cpu) {
    cpu.BIT(cpu.GetRegistry16Value(Registry16::HL), 3);
}

void Disasm::EXT_OP0x5F(GBE::CPU &cpu) {
    cpu.BIT(Registry8::A, 3);
}

void Disasm::EXT_OP0x60(CPU &cpu) {
    cpu.BIT(Registry8::B, 4);
}

void Disasm::EXT_OP0x61(CPU &cpu) {
    cpu.BIT(Registry8::C, 4);
}

void Disasm::EXT_OP0x62(CPU &cpu) {
    cpu.BIT(Registry8::D, 4);
}

void Disasm::EXT_OP0x63(CPU &cpu) {
    cpu.BIT(Registry8::E, 4);
}

void Disasm::EXT_OP0x64(CPU &cpu) {
    cpu.BIT(Registry8::H, 4);
}

void Disasm::EXT_OP0x65(CPU &cpu) {
    cpu.BIT(Registry8::L, 4);
}

void Disasm::EXT_OP0x66(CPU &cpu) {
    cpu.BIT(cpu.GetRegistry16Value(Registry16::HL), 4);
}

void Disasm::EXT_OP0x67(CPU &cpu) {
    cpu.BIT(Registry8::A, 4);
}

void Disasm::EXT_OP0x68(CPU &cpu) {
    cpu.BIT(Registry8::B, 5);
}

void Disasm::EXT_OP0x69(CPU &cpu) {
    cpu.BIT(Registry8::C, 5);
}

void Disasm::EXT_OP0x6A(CPU &cpu) {
    cpu.BIT(Registry8::D, 5);
}

void Disasm::EXT_OP0x6B(CPU &cpu) {
    cpu.BIT(Registry8::E, 5);
}

void Disasm::EXT_OP0x6C(CPU &cpu) {
    cpu.BIT(Registry8::H, 5);
}

void Disasm::EXT_OP0x6D(CPU &cpu) {
    cpu.BIT(Registry8::L, 5);
}

void Disasm::EXT_OP0x6E(GBE::CPU &cpu) {
    cpu.BIT(cpu.GetRegistry16Value(Registry16::HL), 5);
}

void Disasm::EXT_OP0x6F(CPU &cpu) {
    cpu.BIT(Registry8::A, 5);
}

void Disasm::EXT_OP0x70(GBE::CPU &cpu) {
    cpu.BIT(Registry8::B, 6);
}

void Disasm::EXT_OP0x71(CPU &cpu) {
    cpu.BIT(Registry8::C, 6);
}

void Disasm::EXT_OP0x72(CPU &cpu) {
    cpu.BIT(Registry8::D, 6);
}

void Disasm::EXT_OP0x73(CPU &cpu) {
    cpu.BIT(Registry8::E, 6);
}

void Disasm::EXT_OP0x74(CPU &cpu) {
    cpu.BIT(Registry8::H, 6);
}

void Disasm::EXT_OP0x75(CPU &cpu) {
    cpu.BIT(Registry8::L, 6);
}

void Disasm::EXT_OP0x76(GBE::CPU &cpu) {
    cpu.BIT(cpu.GetRegistry16Value(Registry16::HL), 6);
}

void Disasm::EXT_OP0x77(GBE::CPU &cpu) {
    cpu.BIT(Registry8::A, 6);
}

void Disasm::EXT_OP0x78(GBE::CPU &cpu) {
    cpu.BIT(Registry8::B, 7);
}

void Disasm::EXT_OP0x79(CPU &cpu) {
    cpu.BIT(Registry8::C, 7);
}

void Disasm::EXT_OP0x7A(CPU &cpu) {
    cpu.BIT(Registry8::D, 7);
}

void Disasm::EXT_OP0x7B(CPU &cpu) {
    cpu.BIT(Registry8::E, 7);
}

void Disasm::EXT_OP0x7C(GBE::CPU &cpu) {
    cpu.BIT(Registry8::H, 7);
}

void Disasm::EXT_OP0x7D(CPU &cpu) {
    cpu.BIT(Registry8::L, 7);
}

void Disasm::EXT_OP0x7E(GBE::CPU &cpu) {
    cpu.BIT(cpu.GetRegistry16Value(Registry16::HL), 7);
}

void Disasm::EXT_OP0x7F(GBE::CPU &cpu) {
    cpu.BIT(Registry8::A, 7);
}

void Disasm::EXT_OP0x80(CPU &cpu) {
    cpu.RES(Registry8::B, 0);
}

void Disasm::EXT_OP0x81(CPU &cpu) {
    cpu.RES(Registry8::C, 0);
}

void Disasm::EXT_OP0x82(CPU &cpu) {
    cpu.RES(Registry8::D, 0);
}

void Disasm::EXT_OP0x83(CPU &cpu) {
    cpu.RES(Registry8::E, 0);
}

void Disasm::EXT_OP0x84(CPU &cpu) {
    cpu.RES(Registry8::H, 0);
}

void Disasm::EXT_OP0x85(CPU &cpu) {
    cpu.RES(Registry8::L, 0);
}

void Disasm::EXT_OP0x86(CPU &cpu) {
    cpu.RES(cpu.GetRegistry16Value(Registry16::HL), 0);
}

void Disasm::EXT_OP0x87(GBE::CPU &cpu) {
    cpu.RES(Registry8::A, 0);
}

void Disasm::EXT_OP0x88(CPU &cpu) {
    cpu.RES(Registry8::B, 1);
}

void Disasm::EXT_OP0x89(CPU &cpu) {
    cpu.RES(Registry8::C, 1);
}

void Disasm::EXT_OP0x8A(CPU &cpu) {
    cpu.RES(Registry8::D, 1);
}

void Disasm::EXT_OP0x8B(CPU &cpu) {
    cpu.RES(Registry8::E, 1);
}

void Disasm::EXT_OP0x8C(CPU &cpu) {
    cpu.RES(Registry8::H, 1);
}

void Disasm::EXT_OP0x8D(CPU &cpu) {
    cpu.RES(Registry8::L, 1);
}

void Disasm::EXT_OP0x8E(CPU &cpu) {
    cpu.RES(cpu.GetRegistry16Value(Registry16::HL), 1);
}

void Disasm::EXT_OP0x8F(CPU &cpu) {
    cpu.RES(Registry8::A, 1);
}

void Disasm::EXT_OP0x90(CPU &cpu) {
    cpu.RES(Registry8::B, 2);
}

void Disasm::EXT_OP0x91(CPU &cpu) {
    cpu.RES(Registry8::C, 2);
}

void Disasm::EXT_OP0x92(CPU &cpu) {
    cpu.RES(Registry8::D, 2);
}

void Disasm::EXT_OP0x93(CPU &cpu) {
    cpu.RES(Registry8::E, 2);
}

void Disasm::EXT_OP0x94(CPU &cpu) {
    cpu.RES(Registry8::H, 2);
}

void Disasm::EXT_OP0x95(CPU &cpu) {
    cpu.RES(Registry8::L, 2);
}

void Disasm::EXT_OP0x96(GBE::CPU &cpu) {
    cpu.RES(cpu.GetRegistry16Value(Registry16::HL), 2);
}

void Disasm::EXT_OP0x97(CPU &cpu) {
    cpu.RES(Registry8::A, 2);
}

void Disasm::EXT_OP0x98(CPU &cpu) {
    cpu.RES(Registry8::B, 3);
}

void Disasm::EXT_OP0x99(CPU &cpu) {
    cpu.RES(Registry8::C, 3);
}

void Disasm::EXT_OP0x9A(CPU &cpu) {
    cpu.RES(Registry8::D, 3);
}

void Disasm::EXT_OP0x9B(CPU &cpu) {
    cpu.RES(Registry8::E, 3);
}

void Disasm::EXT_OP0x9C(CPU &cpu) {
    cpu.RES(Registry8::H, 3);
}

void Disasm::EXT_OP0x9D(CPU &cpu) {
    cpu.RES(Registry8::L, 3);
}

void Disasm::EXT_OP0x9E(CPU &cpu) {
    cpu.RES(cpu.GetRegistry16Value(Registry16::HL), 3);
}

void Disasm::EXT_OP0x9F(CPU &cpu) {
    cpu.RES(Registry8::A, 3);
}

void Disasm::EXT_OP0xA0(CPU &cpu) {
    cpu.RES(Registry8::B, 4);
}

void Disasm::EXT_OP0xA1(CPU &cpu) {
    cpu.RES(Registry8::C, 4);
}

void Disasm::EXT_OP0xA2(CPU &cpu) {
    cpu.RES(Registry8::D, 4);
}

void Disasm::EXT_OP0xA3(CPU &cpu) {
    cpu.RES(Registry8::E, 4);
}

void Disasm::EXT_OP0xA4(CPU &cpu) {
    cpu.RES(Registry8::H, 4);
}

void Disasm::EXT_OP0xA5(CPU &cpu) {
    cpu.RES(Registry8::L, 4);
}

void Disasm::EXT_OP0xA6(CPU &cpu) {
    cpu.RES(cpu.GetRegistry16Value(Registry16::HL), 4);
}

void Disasm::EXT_OP0xA7(CPU &cpu) {
    cpu.RES(Registry8::A, 4);
}

void Disasm::EXT_OP0xA8(CPU &cpu) {
    cpu.RES(Registry8::B, 5);
}

void Disasm::EXT_OP0xA9(CPU &cpu) {
    cpu.RES(Registry8::C, 5);
}

void Disasm::EXT_OP0xAA(CPU &cpu) {
    cpu.RES(Registry8::D, 5);
}

void Disasm::EXT_OP0xAB(CPU &cpu) {
    cpu.RES(Registry8::E, 5);
}

void Disasm::EXT_OP0xAC(CPU &cpu) {
    cpu.RES(Registry8::H, 5);
}

void Disasm::EXT_OP0xAD(CPU &cpu) {
    cpu.RES(Registry8::L, 5);
}

void Disasm::EXT_OP0xAE(CPU &cpu) {
    cpu.RES(cpu.GetRegistry16Value(Registry16::HL), 5);
}

void Disasm::EXT_OP0xAF(GBE::CPU &cpu) {
    cpu.RES(Registry8::A, 5);
}

void Disasm::EXT_OP0xB0(CPU &cpu) {
    cpu.RES(Registry8::B, 6);
}

void Disasm::EXT_OP0xB1(CPU &cpu) {
    cpu.RES(Registry8::C, 6);
}

void Disasm::EXT_OP0xB2(CPU &cpu) {
    cpu.RES(Registry8::D, 6);
}

void Disasm::EXT_OP0xB3(CPU &cpu) {
    cpu.RES(Registry8::E, 6);
}

void Disasm::EXT_OP0xB4(CPU &cpu) {
    cpu.RES(Registry8::H, 6);
}

void Disasm::EXT_OP0xB5(CPU &cpu) {
    cpu.RES(Registry8::L, 6);
}

void Disasm::EXT_OP0xB6(CPU &cpu) {
    cpu.RES(cpu.GetRegistry16Value(Registry16::HL), 6);
}

void Disasm::EXT_OP0xB7(CPU &cpu) {
    cpu.RES(Registry8::A, 6);
}

void Disasm::EXT_OP0xB8(CPU &cpu) {
    cpu.RES(Registry8::B, 7);
}

void Disasm::EXT_OP0xB9(CPU &cpu) {
    cpu.RES(Registry8::C, 7);
}

void Disasm::EXT_OP0xBA(CPU &cpu) {
    cpu.RES(Registry8::D, 7);
}

void Disasm::EXT_OP0xBB(CPU &cpu) {
    cpu.RES(Registry8::E, 7);
}

void Disasm::EXT_OP0xBC(CPU &cpu) {
    cpu.RES(Registry8::H, 7);
}

void Disasm::EXT_OP0xBD(CPU &cpu) {
    cpu.RES(Registry8::L, 7);
}

void Disasm::EXT_OP0xBE(CPU &cpu) {
    cpu.RES(cpu.GetRegistry16Value(Registry16::HL), 7);
}

void Disasm::EXT_OP0xBF(CPU &cpu) {
    cpu.RES(Registry8::A, 7);
}

void Disasm::EXT_OP0xC0(CPU &cpu) {
    cpu.SET(Registry8::B, 0);
}

void Disasm::EXT_OP0xC1(CPU &cpu) {
    cpu.SET(Registry8::C, 0);
}

void Disasm::EXT_OP0xC2(CPU &cpu) {
    cpu.SET(Registry8::D, 0);
}

void Disasm::EXT_OP0xC3(CPU &cpu) {
    cpu.SET(Registry8::E, 0);
}

void Disasm::EXT_OP0xC4(CPU &cpu) {
    cpu.SET(Registry8::H, 0);
}

void Disasm::EXT_OP0xC5(CPU &cpu) {
    cpu.SET(Registry8::L, 0);
}

void Disasm::EXT_OP0xC6(CPU &cpu) {
    cpu.SET(cpu.GetRegistry16Value(Registry16::HL), 0);
}

void Disasm::EXT_OP0xC7(CPU &cpu) {
    cpu.SET(Registry8::A, 0);
}

void Disasm::EXT_OP0xC8(CPU &cpu) {
    cpu.SET(Registry8::B, 1);
}

void Disasm::EXT_OP0xC9(CPU &cpu) {
    cpu.SET(Registry8::C, 1);
}

void Disasm::EXT_OP0xCA(CPU &cpu) {
    cpu.SET(Registry8::D, 1);
}

void Disasm::EXT_OP0xCB(CPU &cpu) {
    cpu.SET(Registry8::E, 1);
}

void Disasm::EXT_OP0xCC(CPU &cpu) {
    cpu.SET(Registry8::H, 1);
}

void Disasm::EXT_OP0xCD(CPU &cpu) {
    cpu.SET(Registry8::L, 1);
}

void Disasm::EXT_OP0xCE(CPU &cpu) {
    cpu.SET(cpu.GetRegistry16Value(Registry16::HL), 1);
}

void Disasm::EXT_OP0xCF(CPU &cpu) {
    cpu.SET(Registry8::A, 1);
}

void Disasm::EXT_OP0xD0(CPU &cpu) {
    cpu.SET(Registry8::B, 2);
}

void Disasm::EXT_OP0xD1(CPU &cpu) {
    cpu.SET(Registry8::C, 2);
}

void Disasm::EXT_OP0xD2(CPU &cpu) {
    cpu.SET(Registry8::D, 2);
}

void Disasm::EXT_OP0xD3(CPU &cpu) {
    cpu.SET(Registry8::E, 2);
}

void Disasm::EXT_OP0xD4(CPU &cpu) {
    cpu.SET(Registry8::H, 2);
}

void Disasm::EXT_OP0xD5(CPU &cpu) {
    cpu.SET(Registry8::L, 2);
}

void Disasm::EXT_OP0xD6(CPU &cpu) {
    cpu.SET(cpu.GetRegistry16Value(Registry16::HL), 2);
}

void Disasm::EXT_OP0xD7(CPU &cpu) {
    cpu.SET(Registry8::A, 2);
}

void Disasm::EXT_OP0xD8(CPU &cpu) {
    cpu.SET(Registry8::B, 3);
}

void Disasm::EXT_OP0xD9(CPU &cpu) {
    cpu.SET(Registry8::C, 3);
}

void Disasm::EXT_OP0xDA(CPU &cpu) {
    cpu.SET(Registry8::D, 3);
}

void Disasm::EXT_OP0xDB(CPU &cpu) {
    cpu.SET(Registry8::E, 3);
}

void Disasm::EXT_OP0xDC(CPU &cpu) {
    cpu.SET(Registry8::H, 3);
}

void Disasm::EXT_OP0xDD(CPU &cpu) {
    cpu.SET(Registry8::L, 3);
}

void Disasm::EXT_OP0xDE(CPU &cpu) {
    cpu.SET(cpu.GetRegistry16Value(Registry16::HL), 3);
}

void Disasm::EXT_OP0xDF(CPU &cpu) {
    cpu.SET(Registry8::A, 3);
}

void Disasm::EXT_OP0xE0(CPU &cpu) {
    cpu.SET(Registry8::B, 4);
}

void Disasm::EXT_OP0xE1(CPU &cpu) {
    cpu.SET(Registry8::C, 4);
}

void Disasm::EXT_OP0xE2(CPU &cpu) {
    cpu.SET(Registry8::D, 4);
}

void Disasm::EXT_OP0xE3(CPU &cpu) {
    cpu.SET(Registry8::E, 4);
}

void Disasm::EXT_OP0xE4(CPU &cpu) {
    cpu.SET(Registry8::H, 4);
}

void Disasm::EXT_OP0xE5(CPU &cpu) {
    cpu.SET(Registry8::L, 4);
}

void Disasm::EXT_OP0xE6(CPU &cpu) {
    cpu.SET(cpu.GetRegistry16Value(Registry16::HL), 4);
}

void Disasm::EXT_OP0xE7(CPU &cpu) {
    cpu.SET(Registry8::A, 4);
}

void Disasm::EXT_OP0xE8(CPU &cpu) {
    cpu.SET(Registry8::B, 5);
}

void Disasm::EXT_OP0xE9(CPU &cpu) {
    cpu.SET(Registry8::C, 5);
}

void Disasm::EXT_OP0xEA(CPU &cpu) {
    cpu.SET(Registry8::D, 5);
}

void Disasm::EXT_OP0xEB(CPU &cpu) {
    cpu.SET(Registry8::E, 5);
}

void Disasm::EXT_OP0xEC(CPU &cpu) {
    cpu.SET(Registry8::H, 5);
}

void Disasm::EXT_OP0xED(CPU &cpu) {
    cpu.SET(Registry8::L, 5);
}

void Disasm::EXT_OP0xEE(CPU &cpu) {
    cpu.SET(cpu.GetRegistry16Value(Registry16::HL), 5);
}

void Disasm::EXT_OP0xEF(CPU &cpu) {
    cpu.SET(Registry8::A, 5);
}

void Disasm::EXT_OP0xF0(CPU &cpu) {
    cpu.SET(Registry8::B, 6);
}

void Disasm::EXT_OP0xF1(CPU &cpu) {
    cpu.SET(Registry8::C, 6);
}

void Disasm::EXT_OP0xF2(CPU &cpu) {
    cpu.SET(Registry8::D, 6);
}

void Disasm::EXT_OP0xF3(CPU &cpu) {
    cpu.SET(Registry8::E, 6);
}

void Disasm::EXT_OP0xF4(CPU &cpu) {
    cpu.SET(Registry8::H, 6);
}

void Disasm::EXT_OP0xF5(CPU &cpu) {
    cpu.SET(Registry8::L, 6);
}

void Disasm::EXT_OP0xF6(CPU &cpu) {
    cpu.SET(cpu.GetRegistry16Value(Registry16::HL), 6);
}

void Disasm::EXT_OP0xF7(CPU &cpu) {
    cpu.SET(Registry8::A, 6);
}

void Disasm::EXT_OP0xF8(CPU &cpu) {
    cpu.SET(Registry8::B, 7);
}

void Disasm::EXT_OP0xF9(CPU &cpu) {
    cpu.SET(Registry8::C, 7);
}

void Disasm::EXT_OP0xFA(CPU &cpu) {
    cpu.SET(Registry8::D, 7);
}

void Disasm::EXT_OP0xFB(CPU &cpu) {
    cpu.SET(Registry8::E, 7);
}

void Disasm::EXT_OP0xFC(CPU &cpu) {
    cpu.SET(Registry8::H, 7);
}

void Disasm::EXT_OP0xFD(CPU &cpu) {
    cpu.SET(Registry8::L, 7);
}

void Disasm::EXT_OP0xFE(CPU &cpu) {
    cpu.SET(cpu.GetRegistry16Value(Registry16::HL), 7);
}

void Disasm::EXT_OP0xFF(GBE::CPU &cpu) {
    cpu.SET(Registry8::A, 7);
}