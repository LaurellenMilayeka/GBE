//
// Created by Flox Ajuro on 08/09/2018.
//

#ifndef GAMEBOY_EMULATOR_CPU_HPP
#define GAMEBOY_EMULATOR_CPU_HPP

#include <bitset>
#include <stack>

#include "GBE.hpp"

#define CLOCKSPEED 4194304
#define TIME_PER_FRAME 1.0 / 60.0
#define CYCLES_PER_FRAME CLOCKSPEED / 59.7

#define DIV 0xFF04
#define TIMA 0xFF05
#define TMA 0xFF06
#define TMC 0xFF07

#define CLOCKSPEED 4194304

namespace GBE {

    typedef enum {
        ZERO = 1 << 7,
        OPERATION = 1 << 6,
        HALF_CARRY = 1 << 5,
        CARRY = 1 << 4
    } Flags;

    typedef enum {
        A,
        B,
        C,
        D,
        E,
        H,
        L
    } Registry8;

    typedef enum {
        AF,
        BC,
        DE,
        HL,
        SP,
        PC
    } Registry16;

    typedef enum {
        INT_VBLANK = 0,
        INT_LCD_STAT = 1,
        INT_TIMER = 2,
        INT_SERIAL = 3,
        INT_JOYPAD = 4,
    } Interrupt;

    class CPU {

        private:

            std::bitset<8> _flags;

            Word _clock;
            Byte _actualInstr;
            Byte _lastInstrCycles;

            Word _af;
            Word _bc;
            Word _de;
            Word _hl;

            Word _sp;
            Word _pc;

            bool _ime;

            bool IsClockEnabled() const;

            Word GetTimerFrequency();

        public:

            explicit CPU();
            ~CPU() = default;

            void UpdateTimers();

            void EnableInterrupts();
            void DisableInterrupts();

            bool HasInterrupt(Interrupt toCheck);
            bool CheckIFEnabledInterrupt(Interrupt toCheck);

            bool IsInterruptsEnabled() const;

            Byte GetActualInstr() const;
            Byte GetFlags();

            void SetFlags(unsigned int mask);
            void UnsetFlag(unsigned int mask);

            bool IsFlagSet(unsigned int mask) const;

            Byte GetRegistry8Value(Registry8 reg) const;
            Word GetRegistry16Value(Registry16 reg) const;

            void SetRegistry8Value(Registry8 reg, Byte value);
            void SetRegistry16Value(Registry16 reg, Word value);

            Word GetProgramCounter() const;
            Byte GetNextInstruction();

            void PushToStack(Word value);
            void PushToStack(Byte value);

            Word PopFromStack();

            void JumpRelative(int amountToJump);

            unsigned char GetLastInstrCycles() const;
            void AddToLastInstrCycles(Byte toAdd);

            void EnableInterrupt(Interrupt toSet);
            void SetupInterrupt(Interrupt toSet);

            void INC8(Registry8 reg);
            void INC8(Word address);
            void INC16(Registry16 reg);

            void DEC8(Registry8 reg);
            void DEC8(Word address);
            void DEC16(Registry16 reg);

            void ADD8(Registry8 dst, Registry8 toAdd);
            void ADD8(Registry8 dst, Word toAdd);
            void ADD16(Registry16 dst, Registry16 toAdd);

            void ADC8(Registry8 dst, Registry8 toAdd);
            void ADC8(Registry8 dst, Word toAdd);

            void SUB8(Registry8 dst, Registry8 toSub);
            void SUB8(Registry8 dst, Word toSub);

            void SBC8(Registry8 dst, Registry8 toSbc);
            void SBC8(Registry8 dst, Word toSbc);

            void AND8(Registry8 dst, Registry8 toAnd);
            void AND8(Registry8 dst, Word toAnd);

            void XOR8(Registry8 dst, Registry8 toXor);
            void XOR8(Registry8 dst, Word toXor);

            void OR8(Registry8 dst, Registry8 toOr);
            void OR8(Registry8 dst, Word toOr);

            void CP8(Registry8 orig, Registry8 toCp);
            void CP8(Registry8 orig, Word toCp);

            void RLC(Registry8 toShift);
            void RLC(Word toShift);
            void RRC(Registry8 toShift);
            void RRC(Word toShift);
            void RL(Registry8 toShift);
            void RL(Word toShift);
            void RR(Registry8 toShift);
            void RR(Word toShift);

            void SRA(Registry8 toShift);
            void SRA(Word toShift);
            void SLA(Registry8 toShift);
            void SLA(Word toShift);
            void SRL(Registry8 toShift);
            void SRL(Word toShift);

            void SWAP(Registry8 toSwap);
            void SWAP(Word toSwap);

            void BIT(Registry8 dst, Byte toTest);
            void BIT(Word dst, Byte toTest);
            void RES(Registry8 dst, Byte toReset);
            void RES(Word dst, Byte toReset);
            void SET(Registry8 dst, Byte toSet);
            void SET(Word dst, Byte toSet);

            void TimerStep();

            void Step();
    };

};

#endif //GAMEBOY_EMULATOR_CPU_HPP
