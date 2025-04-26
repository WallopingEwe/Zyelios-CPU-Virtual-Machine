#pragma once

#include "zcpu/stdint.h"

struct VM;
void END(VM* vm, float* op1, float* op2);
void JNE(VM* vm, float* op1, float* op2);
void JMP(VM* vm, float* op1, float* op2);
void JG(VM* vm, float* op1, float* op2);
void JGE(VM* vm, float* op1, float* op2);
void JL(VM* vm, float* op1, float* op2);
void JLE(VM* vm, float* op1, float* op2);
void JE(VM* vm, float* op1, float* op2);
void CPUID(VM* vm, float* op1, float* op2);
void PUSH(VM* vm, float* op1, float* op2);
void ADD(VM* vm, float* op1, float* op2);
void SUB(VM* vm, float* op1, float* op2);
void MUL(VM* vm, float* op1, float* op2);
void DIV(VM* vm, float* op1, float* op2);
void MOV(VM* vm, float* op1, float* op2);
void CMP(VM* vm, float* op1, float* op2);
void MIN(VM* vm, float* op1, float* op2);
void MAX(VM* vm, float* op1, float* op2);
void INC(VM* vm, float* op1, float* op2);
void DEC(VM* vm, float* op1, float* op2);
void NEG(VM* vm, float* op1, float* op2);
void RAND(VM* vm, float* op1, float* op2);
void LOOP(VM* vm, float* op1, float* op2);
void LOOPA(VM* vm, float* op1, float* op2);
void LOOPB(VM* vm, float* op1, float* op2);
void LOOPD(VM* vm, float* op1, float* op2);
void SPG(VM* vm, float* op1, float* op2);
void CPG(VM* vm, float* op1, float* op2);
void POP(VM* vm, float* op1, float* op2);
void CALL(VM* vm, float* op1, float* op2);
void BNOT(VM* vm, float* op1, float* op2);
void FINT(VM* vm, float* op1, float* op2);
void RND(VM* vm, float* op1, float* op2);
void FFRAC(VM* vm, float* op1, float* op2);
void FINV(VM* vm, float* op1, float* op2);
void FSHL(VM* vm, float* op1, float* op2);
void FSHR(VM* vm, float* op1, float* op2);
void RET(VM* vm, float* op1, float* op2);
void IRET(VM* vm, float* op1, float* op2);
void STI(VM* vm, float* op1, float* op2);
void CLI(VM* vm, float* op1, float* op2);
void RETF(VM* vm, float* op1, float* op2);
void STEF(VM* vm, float* op1, float* op2);
void CLEF(VM* vm, float* op1, float* op2);
void AND(VM* vm, float* op1, float* op2);
void OR(VM* vm, float* op1, float* op2);
void XOR(VM* vm, float* op1, float* op2);
void FSIN(VM* vm, float* op1, float* op2);
void FCOS(VM* vm, float* op1, float* op2);
void FTAN(VM* vm, float* op1, float* op2);
void FASIN(VM* vm, float* op1, float* op2);
void FACOS(VM* vm, float* op1, float* op2);
void FATAN(VM* vm, float* op1, float* op2);
void MOD(VM* vm, float* op1, float* op2);
void BIT(VM* vm, float* op1, float* op2);
void SBIT(VM* vm, float* op1, float* op2);
void CBIT(VM* vm, float* op1, float* op2);
void TBIT(VM* vm, float* op1, float* op2);
void BAND(VM* vm, float* op1, float* op2);
void BOR(VM* vm, float* op1, float* op2);
void BSHL(VM* vm, float* op1, float* op2);
void BSHR(VM* vm, float* op1, float* op2);
void JUMPF(VM* vm, float* op1, float* op2);
void EXTINT(VM* vm, float* op1, float* op2);
void CNE(VM* vm, float* op1, float* op2);
void CG(VM* vm, float* op1, float* op2);
void CGE(VM* vm, float* op1, float* op2);
void CL(VM* vm, float* op1, float* op2);
void CLE(VM* vm, float* op1, float* op2);
void CE(VM* vm, float* op1, float* op2);
void MCOPY(VM* vm, float* op1, float* op2);
void MXCHG(VM* vm, float* op1, float* op2);
void FPWR(VM* vm, float* op1, float* op2);
void XCHG(VM* vm, float* op1, float* op2);
void FLOG(VM* vm, float* op1, float* op2);
void FLOG10(VM* vm, float* op1, float* op2);
void IN(VM* vm, float* op1, float* op2);
void OUT(VM* vm, float* op1, float* op2);
void FABS(VM* vm, float* op1, float* op2);
void FSGN(VM* vm, float* op1, float* op2);
void FEXP(VM* vm, float* op1, float* op2);
void CALLF(VM* vm, float* op1, float* op2);
void FPI(VM* vm, float* op1, float* op2);
void FE(VM* vm, float* op1, float* op2);
void INT(VM* vm, float* op1, float* op2);
void TPG(VM* vm, float* op1, float* op2);
void FCEIL(VM* vm, float* op1, float* op2);
void ERPG(VM* vm, float* op1, float* op2);
void WRPG(VM* vm, float* op1, float* op2);
void RDPG(VM* vm, float* op1, float* op2);
void TIMER(VM* vm, float* op1, float* op2);
void LIDTR(VM* vm, float* op1, float* op2);
void JNER(VM* vm, float* op1, float* op2);
void JMPR(VM* vm, float* op1, float* op2);
void JGR(VM* vm, float* op1, float* op2);
void JGER(VM* vm, float* op1, float* op2);
void JLR(VM* vm, float* op1, float* op2);
void JLER(VM* vm, float* op1, float* op2);
void JER(VM* vm, float* op1, float* op2);
void LNEG(VM* vm, float* op1, float* op2);
void EXTRET(VM* vm, float* op1, float* op2);
void IDLE(VM* vm, float* op1, float* op2);
void NOP(VM* vm, float* op1, float* op2);
void PUSHA(VM* vm, float* op1, float* op2);
void POPA(VM* vm, float* op1, float* op2);
void STD2(VM* vm, float* op1, float* op2);
void LEAVE(VM* vm, float* op1, float* op2);
void STM(VM* vm, float* op1, float* op2);
void CLM(VM* vm, float* op1, float* op2);
void CPUGET(VM* vm, float* op1, float* op2);
void CPUSET(VM* vm, float* op1, float* op2);
void SPP(VM* vm, float* op1, float* op2);
void CPP(VM* vm, float* op1, float* op2);
void SRL(VM* vm, float* op1, float* op2);
void CRL(VM* vm, float* op1, float* op2);
void LEA(VM* vm, float* op1, float* op2);
void BLOCK(VM* vm, float* op1, float* op2);
void CMPAND(VM* vm, float* op1, float* op2);
void CMPOR(VM* vm, float* op1, float* op2);
void MSHIFT(VM* vm, float* op1, float* op2);
void SMAP(VM* vm, float* op1, float* op2);
void GMAP(VM* vm, float* op1, float* op2);
void RSTACK(VM* vm, float* op1, float* op2);
void SSTACK(VM* vm, float* op1, float* op2);
void ENTER(VM* vm, float* op1, float* op2);
void IRETP(VM* vm, float* op1, float* op2);
void EXTRETP(VM* vm, float* op1, float* op2);
void EXTRETA(VM* vm, float* op1, float* op2);
void EXTRETPA(VM* vm, float* op1, float* op2);
void STERR(VM* vm, float* op1, float* op2);
void CLERR(VM* vm, float* op1, float* op2);
void QUOCMP(VM* vm, float* op1, float* op2);
void QUOTIMER(VM* vm, float* op1, float* op2);

enum ErrorCodes {
    ERR_END_EXECUTION = 2,        // End of program execution
    ERR_DIVISION_ZERO = 3,        // Division by zero
    ERR_UNKNOWN_OPCODE = 4,       // Unknown opcode
    ERR_INTERNAL_ERROR = 5,       // Internal processor error
    ERR_STACK_ERROR = 6,          // Stack error (overflow/underflow)
    ERR_MEMORY_FAULT = 7,         // Memory read/write fault
    ERR_MEMBUS_FAULT = 8,         // MemBus fault
    ERR_WRITE_VIOLATION = 9,      // Write access violation
    ERR_PORT_FAULT = 10,          // Port read/write fault
    ERR_PAGE_VIOLATION = 11,      // Page access violation
    ERR_READ_VIOLATION = 12,      // Read access violation
    ERR_PROCESSOR_FAULT = 13,     // General processor fault
    ERR_EXECUTE_VIOLATION = 14,   // Execute access violation
    ERR_ADDRESS_VIOLATION = 15    // Address space violation
};

struct Instruction {
    int opcode;
    int operand_count;
    void (*execute)(VM* vm, float* op1, float* op2);
};

struct VM {
    float Memory[MEMORY_MODEL];
    int32_t IP;
    float CMPR;
    int32_t IDTR;
    int32_t PTBE;
    int32_t PTBL;
    int interrupt_flag;
    int interrupt_skip;
    int cli_flag;
    int extended_flag;
    float EAX, EBX, ECX, EDX, ESI, EDI, ESP, EBP;
    float CS, SS, DS, ES, GS, FS, KS, LS;
    float R[32]; // Extended registers
    int immediate_swap;
    
    VM();

    void JMP(int32_t address, int32_t segment);
    void JMP(int32_t address);
    void CALL(int32_t address, int32_t segment);
    void CALL(int32_t address);
    void int_vm(int32_t n);
    void Push(float n);
    float Pop();
    float* ReadCell(int32_t address, int32_t segment);
    float* ReadCell(int32_t address);
    void WriteCell(int32_t address, int32_t segment, int32_t value);
    void WriteCell(int32_t address, int32_t value);
    float fetch();
    float* GetOperand(int32_t rm, int32_t segment);
    float* GetRegister(int32_t index);
    float* GetSegment(int32_t index);
    void step();
};