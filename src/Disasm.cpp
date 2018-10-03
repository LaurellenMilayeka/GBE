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

void Disasm::OP0x10(GBE::CPU &) {

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
        cpu.TickClock(4);
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
        cpu.TickClock(4);
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
        cpu.TickClock(4);
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

void Disasm::OP0x38(GBE::CPU &cpu) {
    if (cpu.IsFlagSet(Flags::CARRY)) {
        cpu.JumpRelative((SignedByte)(RAM::Read8(cpu.GetProgramCounter()) + 1));
        cpu.TickClock(4);
    } else {
        cpu.JumpRelative(1);
    }
}

void Disasm::OP0x39(GBE::CPU &cpu) {
    cpu.ADD16(Registry16::HL, Registry16::SP);
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
    cpu.UnsetFlag(Flags::CARRY);
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

void Disasm::OP0x76(GBE::CPU &) {
    /*if (cpu.IsInterruptsEnabled()) {
        cpu.SetRegistry16Value(Registry16::PC, (Word)(cpu.GetRegistry16Value(Registry16::PC) - 1));
    }*/
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
        cpu.TickClock(12);
    }
}

void Disasm::OP0xC1(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::BC, cpu.PopFromStack());
}

void Disasm::OP0xC2(GBE::CPU &cpu) {
    if (!cpu.IsFlagSet(Flags::ZERO)) {
        cpu.SetRegistry16Value(Registry16::PC, RAM::Read16(cpu.GetProgramCounter()));
        cpu.TickClock(4);
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
        cpu.TickClock(12);
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
        cpu.TickClock(12);
    }
}

void Disasm::OP0xC9(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::PC, cpu.PopFromStack());
}

void Disasm::OP0xCA(GBE::CPU &cpu) {
    if (cpu.IsFlagSet(Flags::ZERO)) {
        cpu.SetRegistry16Value(Registry16::PC, RAM::Read16(cpu.GetProgramCounter()));
        cpu.TickClock(4);
    } else {
        cpu.JumpRelative(2);
    }
}

void Disasm::OP0xCB(GBE::CPU &cpu) {
    Byte instr;
    bool found = false;

    instr = cpu.GetNextInstruction();
    //printf("Executing instruction 0x%02X...\n", instr);
    for (unsigned int i = 0; extOpCodes[i].mnemo != "Not Implemented"; i++) {
        if (instr == extOpCodes[i].opCode) {
            extOpCodes[i].f(cpu);
            cpu.TickClock(extOpCodes[i].cycles);
            //Debug::DumpRegistries(cpu);
            found = true;
        }
    }
    if (!found) {
        printf("[INSTR] : 0xCB - 0x%02X at 0x%04X Instruction not implemented\n", instr, cpu.GetProgramCounter());
        Debug::DumpRegistries(cpu);
        Debug::DumpFlags(cpu);
        Debug::DumpRAMRegistries();
        exit(EXIT_FAILURE);
    }
}

void Disasm::OP0xCD(GBE::CPU &cpu) {
    cpu.PushToStack((Word)(cpu.GetProgramCounter() + 2));
    cpu.SetRegistry16Value(Registry16::PC, (Word)RAM::Read16(cpu.GetProgramCounter()));
}

void Disasm::OP0xCE(GBE::CPU &cpu) {
    Byte carry = (Byte)(cpu.IsFlagSet(Flags::CARRY) ? 1 : 0);

    if ((RAM::Read8(cpu.GetProgramCounter()) + cpu.GetRegistry8Value(Registry8::A) + carry) > 255) cpu.SetFlags(Flags::CARRY);
    else cpu.UnsetFlag(Flags::CARRY);
    if (((cpu.GetRegistry8Value(Registry8::A) & 0xF) + (RAM::Read8(cpu.GetProgramCounter()) & 0xF) + carry) & 0x10) cpu.SetFlags(Flags::HALF_CARRY);
    else cpu.UnsetFlag(Flags::HALF_CARRY);
    cpu.SetRegistry8Value(Registry8::A, (Byte)(cpu.GetRegistry8Value(Registry8::A) + RAM::Read8(cpu.GetProgramCounter()) + carry));
    if (cpu.GetRegistry8Value(Registry8::A) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);
    cpu.UnsetFlag(Flags::OPERATION);
    cpu.JumpRelative(1);
}

void Disasm::OP0xCF(GBE::CPU &cpu) {
    cpu.PushToStack(cpu.GetProgramCounter());
    cpu.SetRegistry16Value(Registry16::PC, 0x0008);
}

void Disasm::OP0xD0(GBE::CPU &cpu) {
    if (!cpu.IsFlagSet(Flags::CARRY)) {
        cpu.SetRegistry16Value(Registry16::PC, cpu.PopFromStack());
        cpu.TickClock(12);
    }
}

void Disasm::OP0xD1(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::DE, cpu.PopFromStack());
}

void Disasm::OP0xD2(GBE::CPU &cpu) {
    if (!cpu.IsFlagSet(Flags::CARRY)) {
        cpu.SetRegistry16Value(Registry16::PC, RAM::Read16(cpu.GetProgramCounter()));
        cpu.TickClock(4);
    } else {
        cpu.JumpRelative(2);
    }
}

void Disasm::OP0xD4(GBE::CPU &cpu) {
    if (!cpu.IsFlagSet(Flags::CARRY)) {
        cpu.PushToStack((Word)(cpu.GetProgramCounter() + 2));
        cpu.SetRegistry16Value(Registry16::PC, RAM::Read16(cpu.GetProgramCounter()));
        cpu.TickClock(12);
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

void Disasm::OP0xD8(GBE::CPU &cpu) {
    if (cpu.IsFlagSet(Flags::CARRY)) {
        cpu.SetRegistry16Value(Registry16::PC, cpu.PopFromStack());
        cpu.TickClock(12);
    }
}

void Disasm::OP0xD9(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::PC, cpu.PopFromStack());
    cpu.EnableInterrupts();
}

void Disasm::OP0xDA(GBE::CPU &cpu) {
    if (cpu.IsFlagSet(Flags::CARRY)) {
        cpu.SetRegistry16Value(Registry16::PC, RAM::Read16(cpu.GetProgramCounter()));
        cpu.TickClock(4);
    } else {
        cpu.JumpRelative(2);
    }
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
    Word fromStack = cpu.PopFromStack();

    fromStack >>= 4;
    fromStack <<= 4;
    cpu.SetRegistry16Value(Registry16::AF, fromStack);
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

void Disasm::OP0xF8(GBE::CPU &cpu) {
    cpu.SetRegistry16Value(Registry16::HL, cpu.GetRegistry16Value(Registry16::SP));
    if ((cpu.GetRegistry16Value(Registry16::HL) + (SignedByte)RAM::Read8(cpu.GetProgramCounter())) > 0xFFFF) cpu.SetFlags(Flags::CARRY);
    else cpu.UnsetFlag(Flags::CARRY);
    if (((cpu.GetRegistry16Value(Registry16::HL) & 0xF) + (SignedByte)(RAM::Read8(cpu.GetProgramCounter()) & 0xF)) & 0x10) cpu.SetFlags(Flags::HALF_CARRY);
    else cpu.UnsetFlag(Flags::HALF_CARRY);
    cpu.SetRegistry16Value(Registry16::HL, (Word)(cpu.GetRegistry16Value(Registry16::HL) + (SignedByte)RAM::Read8(cpu.GetProgramCounter())));
    cpu.UnsetFlag(Flags::OPERATION | Flags::ZERO);
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

void Disasm::EXT_OP0x47(GBE::CPU &cpu) {
    if (((cpu.GetRegistry8Value(Registry8::A) >> 0) & 1) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);

    cpu.SetFlags(Flags::HALF_CARRY);
    cpu.UnsetFlag(Flags::OPERATION);
}

void Disasm::EXT_OP0x4F(GBE::CPU &cpu) {
    if (((cpu.GetRegistry8Value(Registry8::A) >> 1) & 1) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);

    cpu.SetFlags(Flags::HALF_CARRY);
    cpu.UnsetFlag(Flags::OPERATION);
}

void Disasm::EXT_OP0x50(GBE::CPU &cpu) {
    if (((cpu.GetRegistry8Value(Registry8::B) >> 2) & 1) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);

    cpu.SetFlags(Flags::HALF_CARRY);
    cpu.UnsetFlag(Flags::OPERATION);
}

void Disasm::EXT_OP0x56(GBE::CPU &cpu) {
    if (((RAM::Read8(cpu.GetRegistry16Value(Registry16::HL)) >> 2) & 1) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);

    cpu.SetFlags(Flags::HALF_CARRY);
    cpu.UnsetFlag(Flags::OPERATION);
}

void Disasm::EXT_OP0x57(GBE::CPU &cpu) {
    if (((cpu.GetRegistry8Value(Registry8::A) >> 2) & 1) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);

    cpu.SetFlags(Flags::HALF_CARRY);
    cpu.UnsetFlag(Flags::OPERATION);
}

void Disasm::EXT_OP0x58(GBE::CPU &cpu) {
    if (((cpu.GetRegistry8Value(Registry8::B) >> 3) & 1) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);

    cpu.SetFlags(Flags::HALF_CARRY);
    cpu.UnsetFlag(Flags::OPERATION);
}

void Disasm::EXT_OP0x5E(GBE::CPU &cpu) {
    if (((RAM::Read8(cpu.GetRegistry16Value(Registry16::HL)) >> 3) & 1) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);

    cpu.SetFlags(Flags::HALF_CARRY);
    cpu.UnsetFlag(Flags::OPERATION);
}

void Disasm::EXT_OP0x5F(GBE::CPU &cpu) {
    if (((cpu.GetRegistry8Value(Registry8::A) >> 3) & 1) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);

    cpu.SetFlags(Flags::HALF_CARRY);
    cpu.UnsetFlag(Flags::OPERATION);
}

void Disasm::EXT_OP0x6E(GBE::CPU &cpu) {
    if (((RAM::Read8(cpu.GetRegistry16Value(Registry16::HL)) >> 5) & 1) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);

    cpu.SetFlags(Flags::HALF_CARRY);
    cpu.UnsetFlag(Flags::OPERATION);
}

void Disasm::EXT_OP0x70(GBE::CPU &cpu) {
    if (((cpu.GetRegistry8Value(Registry8::B) >> 6) & 1) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);

    cpu.SetFlags(Flags::HALF_CARRY);
    cpu.UnsetFlag(Flags::OPERATION);
}

void Disasm::EXT_OP0x76(GBE::CPU &cpu) {
    if (((RAM::Read8(cpu.GetRegistry16Value(Registry16::HL)) >> 6) & 1) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);

    cpu.SetFlags(Flags::HALF_CARRY);
    cpu.UnsetFlag(Flags::OPERATION);
}

void Disasm::EXT_OP0x77(GBE::CPU &cpu) {
    if (((cpu.GetRegistry8Value(Registry8::A) >> 6) & 1) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);

    cpu.SetFlags(Flags::HALF_CARRY);
    cpu.UnsetFlag(Flags::OPERATION);
}

void Disasm::EXT_OP0x78(GBE::CPU &cpu) {
    if (((cpu.GetRegistry8Value(Registry8::B) >> 7) & 1) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);

    cpu.SetFlags(Flags::HALF_CARRY);
    cpu.UnsetFlag(Flags::OPERATION);
}

void Disasm::EXT_OP0x7C(GBE::CPU &cpu) {
    if (((cpu.GetRegistry8Value(Registry8::H) >> 7) & 1) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);

    cpu.SetFlags(Flags::HALF_CARRY);
    cpu.UnsetFlag(Flags::OPERATION);
}

void Disasm::EXT_OP0x7E(GBE::CPU &cpu) {
    if (((RAM::Read8(cpu.GetRegistry16Value(Registry16::HL)) >> 7) & 1) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);

    cpu.SetFlags(Flags::HALF_CARRY);
    cpu.UnsetFlag(Flags::OPERATION);
}

void Disasm::EXT_OP0x7F(GBE::CPU &cpu) {
    if (((cpu.GetRegistry8Value(Registry8::A) >> 7) & 1) == 0) cpu.SetFlags(Flags::ZERO);
    else cpu.UnsetFlag(Flags::ZERO);

    cpu.SetFlags(Flags::HALF_CARRY);
    cpu.UnsetFlag(Flags::OPERATION);
}

void Disasm::EXT_OP0x87(GBE::CPU &cpu) {
    Byte tmp = cpu.GetRegistry8Value(Registry8::A);

    tmp &= ~(1 << 0);
    cpu.SetRegistry8Value(Registry8::A, tmp);
}

void Disasm::EXT_OP0x96(GBE::CPU &cpu) {
    Byte tmp = RAM::Read8(cpu.GetRegistry16Value(Registry16::HL));

    tmp &= ~(1 << 2);
    RAM::Write8(tmp, cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::EXT_OP0xAF(GBE::CPU &cpu) {
    Byte tmp = cpu.GetRegistry8Value(Registry8::A);

    tmp &= ~(1 << 5);
    cpu.SetRegistry8Value(Registry8::A, tmp);
}

void Disasm::EXT_OP0xF6(GBE::CPU &cpu) {
    Byte tmp = RAM::Read8(cpu.GetRegistry16Value(Registry16::HL));

    tmp &= (1 << 6);
    RAM::Write8(tmp, cpu.GetRegistry16Value(Registry16::HL));
}

void Disasm::EXT_OP0xFF(GBE::CPU &cpu) {
    Byte tmp = cpu.GetRegistry8Value(Registry8::A);

    tmp &= (1 << 6);
    cpu.SetRegistry8Value(Registry8::A, tmp);
}