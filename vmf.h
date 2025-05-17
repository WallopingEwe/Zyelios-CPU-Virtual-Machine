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
    ERR_ADDRESS_VIOLATION = 15,   // Address space violation
    READ_REQUEST = 28,            // Read Request
    WRITE_REQUEST = 29,           // Write Request
    ERR_PAGE_TRAPPED = 30         // Page is trapped
};

struct Instruction {
    int opcode;
    int operand_count;
    int privileged;
    void (*execute)(VM* vm, float* op1, float* op2);
};

union Page {
    struct {
        unsigned int disabled : 1; // 0
        unsigned int remapped : 1; // 1
        unsigned int trapped : 1; // 2
        unsigned int override : 1; // 3
        unsigned int unused : 1; // 4
        unsigned int read : 1; // 5
        unsigned int write : 1; // 6
        unsigned int execute : 1; // 7
        unsigned int runlevel : 16;
    } bits;
 
    uint32_t raw;
};

struct VM {
    float Memory[MEMORY_MODEL];
    int32_t IP;
    int32_t XEIP;
    float CMPR;
    int32_t IDTR;
    int32_t PTBE;
    int32_t PTBL;
    int PCAP;
    int interrupt_flag;
    int interrupt_skip;
    int LINT;
    float LADD;
    int32_t MEMRQ;
    int32_t MEMADDR;
    int32_t BLOCKSTART;
    int32_t BLOCKSIZE;
    int cli_flag;
    int extended_flag;
    int extended_memory_flag;
    float EAX, EBX, ECX, EDX, ESI, EDI, ESP, EBP;
    float CS, SS, DS, ES, GS, FS, KS, LS;
    int32_t ESZ;
    float R[32]; // Extended registers
    int immediate_swap;
    clock_t creation_time;
    float PreqHandled;
    int32_t PreqOperand1;
    float PreqOperand2;
    float PreqReturn;
    Page current_page;
    int32_t current_page_map;
    Page previous_page;
    int32_t previous_page_map;
    
    VM();

    void JMP(int32_t address, int32_t segment);
    void JMP(int32_t address);
    void CALL(int32_t address, int32_t segment);
    void CALL(int32_t address);
    void int_vm(int32_t n, float p);
    void PrivilegeRequest(float op1, float op2, int32_t opcode);
    void ExecuteInstruction(Instruction* instruction, float* op1, float* op2);
    void Push(float n);
    float Pop();
    void GetPage(int32_t index, Page* page, int32_t* map);
    void SetPage(int32_t index, int32_t mask, int32_t map);
    float* ReadCell(int32_t address, int32_t segment);
    float* ReadCell(int32_t address);
    void WriteCell(int32_t address, int32_t segment, int32_t value);
    void WriteCell(int32_t address, int32_t value);
    float fetch();
    float* GetOperand(int32_t rm, int32_t segment);
    float* GetRegister(int32_t index);
    float* GetSegment(int32_t index);
    float GetInternalRegister(int32_t index);
    void SetInternalRegister(int32_t index, float value);
    void step();
};