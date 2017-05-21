#ifndef __DISASM_HPP__
#define __DISASM_HPP__

#include <stdint.h>
#include <stdio.h>
#include "RAM.hpp"
#include "Z80.hpp"

namespace CPU {

  class Disasm {

  public:

    /* 00 */
    
    static void Dis0x00(CPU::Z80*);
    static void Dis0x01(CPU::Z80*);
    static void Dis0x02(CPU::Z80*);
    static void Dis0x03(CPU::Z80*);
    static void Dis0x04(CPU::Z80*);
    static void Dis0x05(CPU::Z80*);
    static void Dis0x06(CPU::Z80*);
    static void Dis0x07(CPU::Z80*);
    static void Dis0x08(CPU::Z80*);
    static void Dis0x09(CPU::Z80*);
    static void Dis0x0A(CPU::Z80*);
    static void Dis0x0B(CPU::Z80*);
    static void Dis0x0C(CPU::Z80*);
    static void Dis0x0D(CPU::Z80*);
    static void Dis0x0E(CPU::Z80*);
    static void Dis0x0F(CPU::Z80*);

    /* 10 */

    static void Dis0x10(CPU::Z80*);
    static void Dis0x11(CPU::Z80*);
    static void Dis0x12(CPU::Z80*);
    static void Dis0x13(CPU::Z80*);
    static void Dis0x14(CPU::Z80*);
    static void Dis0x15(CPU::Z80*);
    static void Dis0x16(CPU::Z80*);
    static void Dis0x17(CPU::Z80*);
    static void Dis0x18(CPU::Z80*);
    static void Dis0x19(CPU::Z80*);
    static void Dis0x1A(CPU::Z80*);
    static void Dis0x1B(CPU::Z80*);
    static void Dis0x1C(CPU::Z80*);
    static void Dis0x1D(CPU::Z80*);
    static void Dis0x1E(CPU::Z80*);
    static void Dis0x1F(CPU::Z80*);

    /* 20 */

    static void Dis0x20(CPU::Z80*);
    static void Dis0x21(CPU::Z80*);
    static void Dis0x22(CPU::Z80*);
    static void Dis0x23(CPU::Z80*);
    static void Dis0x24(CPU::Z80*);
    static void Dis0x25(CPU::Z80*);
    static void Dis0x26(CPU::Z80*);
    static void Dis0x27(CPU::Z80*);
    static void Dis0x28(CPU::Z80*);
    static void Dis0x29(CPU::Z80*);
    static void Dis0x2A(CPU::Z80*);
    static void Dis0x2B(CPU::Z80*);
    static void Dis0x2C(CPU::Z80*);
    static void Dis0x2D(CPU::Z80*);
    static void Dis0x2E(CPU::Z80*);
    static void Dis0x2F(CPU::Z80*);

    /* 30 */

    static void Dis0x30(CPU::Z80*);
    static void Dis0x31(CPU::Z80*);
    static void Dis0x32(CPU::Z80*);
    static void Dis0x33(CPU::Z80*);
    static void Dis0x34(CPU::Z80*);
    static void Dis0x35(CPU::Z80*);
    static void Dis0x36(CPU::Z80*);
    static void Dis0x37(CPU::Z80*);
    static void Dis0x38(CPU::Z80*);
    static void Dis0x39(CPU::Z80*);
    static void Dis0x3A(CPU::Z80*);
    static void Dis0x3B(CPU::Z80*);
    static void Dis0x3C(CPU::Z80*);
    static void Dis0x3D(CPU::Z80*);
    static void Dis0x3E(CPU::Z80*);
    static void Dis0x3F(CPU::Z80*);

    /* 40 */

    static void Dis0x40(CPU::Z80*);
    static void Dis0x41(CPU::Z80*);
    static void Dis0x42(CPU::Z80*);
    static void Dis0x43(CPU::Z80*);
    static void Dis0x44(CPU::Z80*);
    static void Dis0x45(CPU::Z80*);
    static void Dis0x46(CPU::Z80*);
    static void Dis0x47(CPU::Z80*);
    static void Dis0x48(CPU::Z80*);
    static void Dis0x49(CPU::Z80*);
    static void Dis0x4A(CPU::Z80*);
    static void Dis0x4B(CPU::Z80*);
    static void Dis0x4C(CPU::Z80*);
    static void Dis0x4D(CPU::Z80*);
    static void Dis0x4E(CPU::Z80*);
    static void Dis0x4F(CPU::Z80*);

    /* 50 */

    static void Dis0x50(CPU::Z80*);
    static void Dis0x51(CPU::Z80*);
    static void Dis0x52(CPU::Z80*);
    static void Dis0x53(CPU::Z80*);
    static void Dis0x54(CPU::Z80*);
    static void Dis0x55(CPU::Z80*);
    static void Dis0x56(CPU::Z80*);
    static void Dis0x57(CPU::Z80*);
    static void Dis0x58(CPU::Z80*);
    static void Dis0x59(CPU::Z80*);
    static void Dis0x5A(CPU::Z80*);
    static void Dis0x5B(CPU::Z80*);
    static void Dis0x5C(CPU::Z80*);
    static void Dis0x5D(CPU::Z80*);
    static void Dis0x5E(CPU::Z80*);
    static void Dis0x5F(CPU::Z80*);

    /* 60 */

    static void Dis0x60(CPU::Z80*);
    static void Dis0x61(CPU::Z80*);
    static void Dis0x62(CPU::Z80*);
    static void Dis0x63(CPU::Z80*);
    static void Dis0x64(CPU::Z80*);
    static void Dis0x65(CPU::Z80*);
    static void Dis0x66(CPU::Z80*);
    static void Dis0x67(CPU::Z80*);
    static void Dis0x68(CPU::Z80*);
    static void Dis0x69(CPU::Z80*);
    static void Dis0x6A(CPU::Z80*);
    static void Dis0x6B(CPU::Z80*);
    static void Dis0x6C(CPU::Z80*);
    static void Dis0x6D(CPU::Z80*);
    static void Dis0x6E(CPU::Z80*);
    static void Dis0x6F(CPU::Z80*);

    /* 70 */

    static void Dis0x70(CPU::Z80*);
    static void Dis0x71(CPU::Z80*);
    static void Dis0x72(CPU::Z80*);
    static void Dis0x73(CPU::Z80*);
    static void Dis0x74(CPU::Z80*);
    static void Dis0x75(CPU::Z80*);
    static void Dis0x76(CPU::Z80*);
    static void Dis0x77(CPU::Z80*);
    static void Dis0x78(CPU::Z80*);
    static void Dis0x79(CPU::Z80*);
    static void Dis0x7A(CPU::Z80*);
    static void Dis0x7B(CPU::Z80*);
    static void Dis0x7C(CPU::Z80*);
    static void Dis0x7D(CPU::Z80*);
    static void Dis0x7E(CPU::Z80*);
    static void Dis0x7F(CPU::Z80*);

    /* 80 */

    static void Dis0x80(CPU::Z80*);
    static void Dis0x81(CPU::Z80*);
    static void Dis0x82(CPU::Z80*);
    static void Dis0x83(CPU::Z80*);
    static void Dis0x84(CPU::Z80*);
    static void Dis0x85(CPU::Z80*);
    static void Dis0x86(CPU::Z80*);
    static void Dis0x87(CPU::Z80*);
    static void Dis0x88(CPU::Z80*);
    static void Dis0x89(CPU::Z80*);
    static void Dis0x8A(CPU::Z80*);
    static void Dis0x8B(CPU::Z80*);
    static void Dis0x8C(CPU::Z80*);
    static void Dis0x8D(CPU::Z80*);
    static void Dis0x8E(CPU::Z80*);
    static void Dis0x8F(CPU::Z80*);

    /* 90 */

    static void Dis0x90(CPU::Z80*);
    static void Dis0x91(CPU::Z80*);
    static void Dis0x92(CPU::Z80*);
    static void Dis0x93(CPU::Z80*);
    static void Dis0x94(CPU::Z80*);
    static void Dis0x95(CPU::Z80*);
    static void Dis0x96(CPU::Z80*);
    static void Dis0x97(CPU::Z80*);
    static void Dis0x98(CPU::Z80*);
    static void Dis0x99(CPU::Z80*);
    static void Dis0x9A(CPU::Z80*);
    static void Dis0x9B(CPU::Z80*);
    static void Dis0x9C(CPU::Z80*);
    static void Dis0x9D(CPU::Z80*);
    static void Dis0x9E(CPU::Z80*);
    static void Dis0x9F(CPU::Z80*);

    /* A0 */

    static void Dis0xA0(CPU::Z80*);
    static void Dis0xA1(CPU::Z80*);
    static void Dis0xA2(CPU::Z80*);
    static void Dis0xA3(CPU::Z80*);
    static void Dis0xA4(CPU::Z80*);
    static void Dis0xA5(CPU::Z80*);
    static void Dis0xA6(CPU::Z80*);
    static void Dis0xA7(CPU::Z80*);
    static void Dis0xA8(CPU::Z80*);
    static void Dis0xA9(CPU::Z80*);
    static void Dis0xAA(CPU::Z80*);
    static void Dis0xAB(CPU::Z80*);
    static void Dis0xAC(CPU::Z80*);
    static void Dis0xAD(CPU::Z80*);
    static void Dis0xAE(CPU::Z80*);
    static void Dis0xAF(CPU::Z80*);

    /* B0 */

    static void Dis0xB0(CPU::Z80*);
    static void Dis0xB1(CPU::Z80*);
    static void Dis0xB2(CPU::Z80*);
    static void Dis0xB3(CPU::Z80*);
    static void Dis0xB4(CPU::Z80*);
    static void Dis0xB5(CPU::Z80*);
    static void Dis0xB6(CPU::Z80*);
    static void Dis0xB7(CPU::Z80*);
    static void Dis0xB8(CPU::Z80*);
    static void Dis0xB9(CPU::Z80*);
    static void Dis0xBA(CPU::Z80*);
    static void Dis0xBB(CPU::Z80*);
    static void Dis0xBC(CPU::Z80*);
    static void Dis0xBD(CPU::Z80*);
    static void Dis0xBE(CPU::Z80*);
    static void Dis0xBF(CPU::Z80*);

    /* C0 */

    static void Dis0xC0(CPU::Z80*);
    static void Dis0xC1(CPU::Z80*);
    static void Dis0xC2(CPU::Z80*);
    static void Dis0xC3(CPU::Z80*);
    static void Dis0xC4(CPU::Z80*);
    static void Dis0xC5(CPU::Z80*);
    static void Dis0xC6(CPU::Z80*);
    static void Dis0xC7(CPU::Z80*);
    static void Dis0xC8(CPU::Z80*);
    static void Dis0xC9(CPU::Z80*);
    static void Dis0xCA(CPU::Z80*);
    static void Dis0xCB(CPU::Z80*);
    static void Dis0xCC(CPU::Z80*);
    static void Dis0xCD(CPU::Z80*);
    static void Dis0xCE(CPU::Z80*);
    static void Dis0xCF(CPU::Z80*);

    /* D0 */

    static void Dis0xD0(CPU::Z80*);
    static void Dis0xD1(CPU::Z80*);
    static void Dis0xD2(CPU::Z80*);
    static void Dis0xD3(CPU::Z80*);
    static void Dis0xD4(CPU::Z80*);
    static void Dis0xD5(CPU::Z80*);
    static void Dis0xD6(CPU::Z80*);
    static void Dis0xD7(CPU::Z80*);
    static void Dis0xD8(CPU::Z80*);
    static void Dis0xD9(CPU::Z80*);
    static void Dis0xDA(CPU::Z80*);
    static void Dis0xDB(CPU::Z80*);
    static void Dis0xDC(CPU::Z80*);
    static void Dis0xDD(CPU::Z80*);
    static void Dis0xDE(CPU::Z80*);
    static void Dis0xDF(CPU::Z80*);

    /* E0 */

    static void Dis0xE0(CPU::Z80*);
    static void Dis0xE1(CPU::Z80*);
    static void Dis0xE2(CPU::Z80*);
    static void Dis0xE3(CPU::Z80*);
    static void Dis0xE4(CPU::Z80*);
    static void Dis0xE5(CPU::Z80*);
    static void Dis0xE6(CPU::Z80*);
    static void Dis0xE7(CPU::Z80*);
    static void Dis0xE8(CPU::Z80*);
    static void Dis0xE9(CPU::Z80*);
    static void Dis0xEA(CPU::Z80*);
    static void Dis0xEB(CPU::Z80*);
    static void Dis0xEC(CPU::Z80*);
    static void Dis0xED(CPU::Z80*);
    static void Dis0xEE(CPU::Z80*);
    static void Dis0xEF(CPU::Z80*);

    /* F0 */

    static void Dis0xF0(CPU::Z80*);
    static void Dis0xF1(CPU::Z80*);
    static void Dis0xF2(CPU::Z80*);
    static void Dis0xF3(CPU::Z80*);
    static void Dis0xF4(CPU::Z80*);
    static void Dis0xF5(CPU::Z80*);
    static void Dis0xF6(CPU::Z80*);
    static void Dis0xF7(CPU::Z80*);
    static void Dis0xF8(CPU::Z80*);
    static void Dis0xF9(CPU::Z80*);
    static void Dis0xFA(CPU::Z80*);
    static void Dis0xFB(CPU::Z80*);
    static void Dis0xFC(CPU::Z80*);
    static void Dis0xFD(CPU::Z80*);
    static void Dis0xFE(CPU::Z80*);
    static void Dis0xFF(CPU::Z80*);

    /* BC Extension Instruction */
    /* 00 */

    static void DisCB0x00(CPU::Z80*);
    static void DisCB0x01(CPU::Z80*);
    static void DisCB0x02(CPU::Z80*);
    static void DisCB0x03(CPU::Z80*);
    static void DisCB0x04(CPU::Z80*);
    static void DisCB0x05(CPU::Z80*);
    static void DisCB0x06(CPU::Z80*);
    static void DisCB0x07(CPU::Z80*);
    static void DisCB0x08(CPU::Z80*);
    static void DisCB0x09(CPU::Z80*);
    static void DisCB0x0A(CPU::Z80*);
    static void DisCB0x0B(CPU::Z80*);
    static void DisCB0x0C(CPU::Z80*);
    static void DisCB0x0D(CPU::Z80*);
    static void DisCB0x0E(CPU::Z80*);
    static void DisCB0x0F(CPU::Z80*);

    /* 10 */

    static void DisCB0x10(CPU::Z80*);
    static void DisCB0x11(CPU::Z80*);
    static void DisCB0x12(CPU::Z80*);
    static void DisCB0x13(CPU::Z80*);
    static void DisCB0x14(CPU::Z80*);
    static void DisCB0x15(CPU::Z80*);
    static void DisCB0x16(CPU::Z80*);
    static void DisCB0x17(CPU::Z80*);
    static void DisCB0x18(CPU::Z80*);
    static void DisCB0x19(CPU::Z80*);
    static void DisCB0x1A(CPU::Z80*);
    static void DisCB0x1B(CPU::Z80*);
    static void DisCB0x1C(CPU::Z80*);
    static void DisCB0x1D(CPU::Z80*);
    static void DisCB0x1E(CPU::Z80*);
    static void DisCB0x1F(CPU::Z80*);

    /* 20 */

    static void DisCB0x20(CPU::Z80*);
    static void DisCB0x21(CPU::Z80*);
    static void DisCB0x22(CPU::Z80*);
    static void DisCB0x23(CPU::Z80*);
    static void DisCB0x24(CPU::Z80*);
    static void DisCB0x25(CPU::Z80*);
    static void DisCB0x26(CPU::Z80*);
    static void DisCB0x27(CPU::Z80*);
    static void DisCB0x28(CPU::Z80*);
    static void DisCB0x29(CPU::Z80*);
    static void DisCB0x2A(CPU::Z80*);
    static void DisCB0x2B(CPU::Z80*);
    static void DisCB0x2C(CPU::Z80*);
    static void DisCB0x2D(CPU::Z80*);
    static void DisCB0x2E(CPU::Z80*);
    static void DisCB0x2F(CPU::Z80*);

    /* 30 */

    static void DisCB0x30(CPU::Z80*);
    static void DisCB0x31(CPU::Z80*);
    static void DisCB0x32(CPU::Z80*);
    static void DisCB0x33(CPU::Z80*);
    static void DisCB0x34(CPU::Z80*);
    static void DisCB0x35(CPU::Z80*);
    static void DisCB0x36(CPU::Z80*);
    static void DisCB0x37(CPU::Z80*);
    static void DisCB0x38(CPU::Z80*);
    static void DisCB0x39(CPU::Z80*);
    static void DisCB0x3A(CPU::Z80*);
    static void DisCB0x3B(CPU::Z80*);
    static void DisCB0x3C(CPU::Z80*);
    static void DisCB0x3D(CPU::Z80*);
    static void DisCB0x3E(CPU::Z80*);
    static void DisCB0x3F(CPU::Z80*);

    /* 40 */

    static void DisCB0x40(CPU::Z80*);
    static void DisCB0x41(CPU::Z80*);
    static void DisCB0x42(CPU::Z80*);
    static void DisCB0x43(CPU::Z80*);
    static void DisCB0x44(CPU::Z80*);
    static void DisCB0x45(CPU::Z80*);
    static void DisCB0x46(CPU::Z80*);
    static void DisCB0x47(CPU::Z80*);
    static void DisCB0x48(CPU::Z80*);
    static void DisCB0x49(CPU::Z80*);
    static void DisCB0x4A(CPU::Z80*);
    static void DisCB0x4B(CPU::Z80*);
    static void DisCB0x4C(CPU::Z80*);
    static void DisCB0x4D(CPU::Z80*);
    static void DisCB0x4E(CPU::Z80*);
    static void DisCB0x4F(CPU::Z80*);

    /* 50 */

    static void DisCB0x50(CPU::Z80*);
    static void DisCB0x51(CPU::Z80*);
    static void DisCB0x52(CPU::Z80*);
    static void DisCB0x53(CPU::Z80*);
    static void DisCB0x54(CPU::Z80*);
    static void DisCB0x55(CPU::Z80*);
    static void DisCB0x56(CPU::Z80*);
    static void DisCB0x57(CPU::Z80*);
    static void DisCB0x58(CPU::Z80*);
    static void DisCB0x59(CPU::Z80*);
    static void DisCB0x5A(CPU::Z80*);
    static void DisCB0x5B(CPU::Z80*);
    static void DisCB0x5C(CPU::Z80*);
    static void DisCB0x5D(CPU::Z80*);
    static void DisCB0x5E(CPU::Z80*);
    static void DisCB0x5F(CPU::Z80*);

    /* 60 */

    static void DisCB0x60(CPU::Z80*);
    static void DisCB0x61(CPU::Z80*);
    static void DisCB0x62(CPU::Z80*);
    static void DisCB0x63(CPU::Z80*);
    static void DisCB0x64(CPU::Z80*);
    static void DisCB0x65(CPU::Z80*);
    static void DisCB0x66(CPU::Z80*);
    static void DisCB0x67(CPU::Z80*);
    static void DisCB0x68(CPU::Z80*);
    static void DisCB0x69(CPU::Z80*);
    static void DisCB0x6A(CPU::Z80*);
    static void DisCB0x6B(CPU::Z80*);
    static void DisCB0x6C(CPU::Z80*);
    static void DisCB0x6D(CPU::Z80*);
    static void DisCB0x6E(CPU::Z80*);
    static void DisCB0x6F(CPU::Z80*);

    /* 70 */

    static void DisCB0x70(CPU::Z80*);
    static void DisCB0x71(CPU::Z80*);
    static void DisCB0x72(CPU::Z80*);
    static void DisCB0x73(CPU::Z80*);
    static void DisCB0x74(CPU::Z80*);
    static void DisCB0x75(CPU::Z80*);
    static void DisCB0x76(CPU::Z80*);
    static void DisCB0x77(CPU::Z80*);
    static void DisCB0x78(CPU::Z80*);
    static void DisCB0x79(CPU::Z80*);
    static void DisCB0x7A(CPU::Z80*);
    static void DisCB0x7B(CPU::Z80*);
    static void DisCB0x7C(CPU::Z80*);
    static void DisCB0x7D(CPU::Z80*);
    static void DisCB0x7E(CPU::Z80*);
    static void DisCB0x7F(CPU::Z80*);

    /* 80 */

    static void DisCB0x80(CPU::Z80*);
    static void DisCB0x81(CPU::Z80*);
    static void DisCB0x82(CPU::Z80*);
    static void DisCB0x83(CPU::Z80*);
    static void DisCB0x84(CPU::Z80*);
    static void DisCB0x85(CPU::Z80*);
    static void DisCB0x86(CPU::Z80*);
    static void DisCB0x87(CPU::Z80*);
    static void DisCB0x88(CPU::Z80*);
    static void DisCB0x89(CPU::Z80*);
    static void DisCB0x8A(CPU::Z80*);
    static void DisCB0x8B(CPU::Z80*);
    static void DisCB0x8C(CPU::Z80*);
    static void DisCB0x8D(CPU::Z80*);
    static void DisCB0x8E(CPU::Z80*);
    static void DisCB0x8F(CPU::Z80*);

    /* 90 */

    static void DisCB0x90(CPU::Z80*);
    static void DisCB0x91(CPU::Z80*);
    static void DisCB0x92(CPU::Z80*);
    static void DisCB0x93(CPU::Z80*);
    static void DisCB0x94(CPU::Z80*);
    static void DisCB0x95(CPU::Z80*);
    static void DisCB0x96(CPU::Z80*);
    static void DisCB0x97(CPU::Z80*);
    static void DisCB0x98(CPU::Z80*);
    static void DisCB0x99(CPU::Z80*);
    static void DisCB0x9A(CPU::Z80*);
    static void DisCB0x9B(CPU::Z80*);
    static void DisCB0x9C(CPU::Z80*);
    static void DisCB0x9D(CPU::Z80*);
    static void DisCB0x9E(CPU::Z80*);
    static void DisCB0x9F(CPU::Z80*);

    /* A0 */

    static void DisCB0xA0(CPU::Z80*);
    static void DisCB0xA1(CPU::Z80*);
    static void DisCB0xA2(CPU::Z80*);
    static void DisCB0xA3(CPU::Z80*);
    static void DisCB0xA4(CPU::Z80*);
    static void DisCB0xA5(CPU::Z80*);
    static void DisCB0xA6(CPU::Z80*);
    static void DisCB0xA7(CPU::Z80*);
    static void DisCB0xA8(CPU::Z80*);
    static void DisCB0xA9(CPU::Z80*);
    static void DisCB0xAA(CPU::Z80*);
    static void DisCB0xAB(CPU::Z80*);
    static void DisCB0xAC(CPU::Z80*);
    static void DisCB0xAD(CPU::Z80*);
    static void DisCB0xAE(CPU::Z80*);
    static void DisCB0xAF(CPU::Z80*);

    /* B0 */

    static void DisCB0xB0(CPU::Z80*);
    static void DisCB0xB1(CPU::Z80*);
    static void DisCB0xB2(CPU::Z80*);
    static void DisCB0xB3(CPU::Z80*);
    static void DisCB0xB4(CPU::Z80*);
    static void DisCB0xB5(CPU::Z80*);
    static void DisCB0xB6(CPU::Z80*);
    static void DisCB0xB7(CPU::Z80*);
    static void DisCB0xB8(CPU::Z80*);
    static void DisCB0xB9(CPU::Z80*);
    static void DisCB0xBA(CPU::Z80*);
    static void DisCB0xBB(CPU::Z80*);
    static void DisCB0xBC(CPU::Z80*);
    static void DisCB0xBD(CPU::Z80*);
    static void DisCB0xBE(CPU::Z80*);
    static void DisCB0xBF(CPU::Z80*);

    /* C0 */

    static void DisCB0xC0(CPU::Z80*);
    static void DisCB0xC1(CPU::Z80*);
    static void DisCB0xC2(CPU::Z80*);
    static void DisCB0xC3(CPU::Z80*);
    static void DisCB0xC4(CPU::Z80*);
    static void DisCB0xC5(CPU::Z80*);
    static void DisCB0xC6(CPU::Z80*);
    static void DisCB0xC7(CPU::Z80*);
    static void DisCB0xC8(CPU::Z80*);
    static void DisCB0xC9(CPU::Z80*);
    static void DisCB0xCA(CPU::Z80*);
    static void DisCB0xCB(CPU::Z80*);
    static void DisCB0xCC(CPU::Z80*);
    static void DisCB0xCD(CPU::Z80*);
    static void DisCB0xCE(CPU::Z80*);
    static void DisCB0xCF(CPU::Z80*);

    /* D0 */

    static void DisCB0xD0(CPU::Z80*);
    static void DisCB0xD1(CPU::Z80*);
    static void DisCB0xD2(CPU::Z80*);
    static void DisCB0xD3(CPU::Z80*);
    static void DisCB0xD4(CPU::Z80*);
    static void DisCB0xD5(CPU::Z80*);
    static void DisCB0xD6(CPU::Z80*);
    static void DisCB0xD7(CPU::Z80*);
    static void DisCB0xD8(CPU::Z80*);
    static void DisCB0xD9(CPU::Z80*);
    static void DisCB0xDA(CPU::Z80*);
    static void DisCB0xDB(CPU::Z80*);
    static void DisCB0xDC(CPU::Z80*);
    static void DisCB0xDD(CPU::Z80*);
    static void DisCB0xDE(CPU::Z80*);
    static void DisCB0xDF(CPU::Z80*);

    /* E0 */

    static void DisCB0xE0(CPU::Z80*);
    static void DisCB0xE1(CPU::Z80*);
    static void DisCB0xE2(CPU::Z80*);
    static void DisCB0xE3(CPU::Z80*);
    static void DisCB0xE4(CPU::Z80*);
    static void DisCB0xE5(CPU::Z80*);
    static void DisCB0xE6(CPU::Z80*);
    static void DisCB0xE7(CPU::Z80*);
    static void DisCB0xE8(CPU::Z80*);
    static void DisCB0xE9(CPU::Z80*);
    static void DisCB0xEA(CPU::Z80*);
    static void DisCB0xEB(CPU::Z80*);
    static void DisCB0xEC(CPU::Z80*);
    static void DisCB0xED(CPU::Z80*);
    static void DisCB0xEE(CPU::Z80*);
    static void DisCB0xEF(CPU::Z80*);

    /* F0 */

    static void DisCB0xF0(CPU::Z80*);
    static void DisCB0xF1(CPU::Z80*);
    static void DisCB0xF2(CPU::Z80*);
    static void DisCB0xF3(CPU::Z80*);
    static void DisCB0xF4(CPU::Z80*);
    static void DisCB0xF5(CPU::Z80*);
    static void DisCB0xF6(CPU::Z80*);
    static void DisCB0xF7(CPU::Z80*);
    static void DisCB0xF8(CPU::Z80*);
    static void DisCB0xF9(CPU::Z80*);
    static void DisCB0xFA(CPU::Z80*);
    static void DisCB0xFB(CPU::Z80*);
    static void DisCB0xFC(CPU::Z80*);
    static void DisCB0xFD(CPU::Z80*);
    static void DisCB0xFE(CPU::Z80*);
    static void DisCB0xFF(CPU::Z80*);

  };
};

#endif
