#pragma warn -par
#define MEMORY_MODEL 512
#define DEBUG_MODE 1
#define KEYBOARD_IRQ 0x09
#define PITIRQ 0x08
#define PITFreq 1193181.184
#define INTERNAL_READ_CYCLES 10
#define INTERNAL_WRITE_CYCLES 10
#define EXTERNAL_READ_CYCLES 15
#define EXTERNAL_WRITE_CYCLES 15
#include "zcpu/stdint.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <dos.h>

#include "zcpu/vmf.h"
#include "zcpu/insts/core.cpp"
#include "zcpu/insts/branch.cpp"
#include "zcpu/insts/stack.cpp"
#include "zcpu/insts/math.cpp"
#include "zcpu/insts/bit.cpp"
#include "zcpu/insts/extended.cpp"
#include "zcpu/insts/paging.cpp"

int far* screen_ptr = (int far*)MK_FP(0xb800,0);

void interrupt(*old_pit_irq)(...);
void interrupt(*old_keyboard_irq)(...);

volatile unsigned char scancode = 0;
volatile unsigned char ctrlc = 0;
volatile unsigned char ctrl = 0;
volatile uint32_t ticks = 0;
volatile unsigned char irq_ticks;
volatile unsigned char keyboard_extint;
volatile unsigned char keyboard_extint_scancode;

Instruction instructions[] = {
    { 0, 0, 0, END },
    { 1, 1, 0, JNE },
    { 2, 1, 0, JMP },
    { 3, 1, 0, JG },
    { 4, 1, 0, JGE },
    { 5, 1, 0, JL },
    { 6, 1, 0, JLE },
    { 7, 1, 0, JE },
    { 8, 0, 0, CPUID },
    { 9, 1, 0, PUSH },
    { 10, 2, 0, ADD },
    { 11, 2, 0, SUB },
    { 12, 2, 0, MUL },
    { 13, 2, 0, DIV },
    { 14, 2, 0, MOV },
    { 15, 2, 0, CMP },
    { 16, 0, 0, 0 },
    { 17, 0, 0, 0 },
    { 18, 2, 0, MIN },
    { 19, 2, 0, MAX },
    { 20, 1, 0, INC },
    { 21, 1, 0, DEC },
    { 22, 1, 0, NEG },
    { 23, 1, 0, RAND },
    { 24, 1, 0, LOOP },
    { 25, 1, 0, LOOPA },
    { 26, 1, 0, LOOPB },
    { 27, 1, 0, LOOPD },
    { 28, 1, 0, SPG },
    { 29, 1, 0, CPG },
    { 30, 1, 0, POP },
    { 31, 1, 0, CALL },
    { 32, 1, 0, BNOT },
    { 33, 1, 0, FINT },
    { 34, 1, 0, RND },
    { 35, 1, 0, FFRAC },
    { 36, 1, 0, FINV },
    { 37, 0, 0, 0 },
    { 38, 1, 0, FSHL },
    { 39, 1, 0, FSHR },
    { 40, 0, 0, RET },
    { 41, 0, 0, IRET },
    { 42, 0, 0, STI },
    { 43, 0, 0, CLI },
    { 44, 0, 0, 0 },
    { 45, 0, 0, 0 },
    { 46, 0, 0, 0 },
    { 47, 0, 0, RETF },
    { 48, 0, 0, STEF },
    { 49, 0, 0, CLEF },
    { 50, 2, 0, AND },
    { 51, 2, 0, OR },
    { 52, 2, 0, XOR },
    { 53, 2, 0, FSIN },
    { 54, 2, 0, FCOS },
    { 55, 2, 0, FTAN },
    { 56, 2, 0, FASIN },
    { 57, 2, 0, FACOS },
    { 58, 2, 0, FATAN },
    { 59, 2, 0, MOD },
    { 60, 2, 0, BIT },
    { 61, 2, 0, SBIT },
    { 62, 2, 0, CBIT },
    { 63, 2, 0, TBIT },
    { 64, 2, 0, BAND },
    { 65, 2, 0, BOR },
    { 66, 0, 0, 0 },
    { 67, 2, 0, BSHL },
    { 68, 0, 0, BSHR },
    { 69, 2, 0, JUMPF },
    { 70, 0, 0, EXTINT },
    { 71, 1, 0, CNE },
    { 72, 0, 0, 0 },
    { 73, 1, 0, CG },
    { 74, 1, 0, CGE },
    { 75, 1, 0, CL },
    { 76, 1, 0, CLE },
    { 77, 1, 0, CE },
    { 78, 1, 0, MCOPY },
    { 79, 1, 0, MXCHG },
    { 80, 2, 0, FPWR },
    { 81, 2, 0, XCHG },
    { 82, 2, 0, FLOG },
    { 83, 2, 0, FLOG10 },
    { 84, 2, 0, IN },
    { 85, 2, 0, OUT },
    { 86, 2, 0, FABS },
    { 87, 2, 0, FSGN },
    { 88, 2, 0, FEXP },
    { 89, 2, 0, CALLF },
    { 90, 1, 0, FPI },
    { 91, 1, 0, FE },
    { 92, 1, 0, INT },
    { 93, 0, 0, TPG },
    { 94, 1, 0, FCEIL },
    { 95, 0, 0, ERPG },
    { 96, 0, 0, WRPG },
    { 97, 0, 0, RDPG },
    { 98, 1, 0, TIMER },
    { 99, 1, 0, LIDTR },
    { 100, 0, 0, 0 },
    { 101, 1, 0, JNER },
    { 102, 1, 0, JMPR },
    { 103, 1, 0, JGR },
    { 104, 1, 0, JGER },
    { 105, 1, 0, JLR },
    { 106, 1, 0, JLER },
    { 107, 1, 0, JER },
    { 108, 1, 0, LNEG },
    { 109, 0, 0, 0 },
    { 110, 0, 0, EXTRET },
    { 111, 0, 0, IDLE },
    { 112, 0, 0, NOP },
    { 113, 0, 0, 0 },
    { 114, 0, 0, PUSHA },
    { 115, 0, 0, POPA },
    { 116, 0, 0, STD2 },
    { 117, 0, 0, LEAVE },
    { 118, 0, 0, STM },
    { 119, 0, 0, CLM },
    { 120, 2, 0, CPUGET },
    { 121, 2, 0, CPUSET },
    { 122, 2, 0, SPP },
    { 123, 2, 0, CPP },
    { 124, 2, 0, SRL },
    { 125, 2, 0, CRL },
    { 126, 2, 0, LEA },
    { 127, 2, 0, BLOCK },
    { 128, 2, 0, CMPAND },
    { 129, 2, 0, CMPOR },
    { 130, 0, 0, MSHIFT },
    { 131, 2, 0, SMAP },
    { 132, 2, 0, GMAP },
    { 133, 2, 0, RSTACK },
    { 134, 2, 0, SSTACK },
    { 135, 1, 0, ENTER },
    { 136, 1, 0, IRETP },
    { 137, 0, 0, EXTRETP },
    { 138, 0, 0, 0 },
    { 139, 0, 0, 0 },
    { 140, 0, 0, EXTRETA },
    { 141, 0, 0, EXTRETPA },
    { 142, 0, 0, 0 },
    { 143, 0, 0, 0 },
    { 144, 0, 0, 0 },
    { 145, 0, 0, 0 },
    { 146, 0, 0, 0 },
    { 147, 0, 0, 0 },
    { 148, 0, 0, 0 },
    { 149, 0, 0, 0 },
    { 150, 0, 0, STERR },
    { 151, 0, 0, CLERR },
    { 152, 0, 0, QUOCMP },
    { 153, 0, 0, QUOTIMER },
};

void interrupt keyboard_irq(...) {
    scancode = inportb(0x60);

    if(!keyboard_extint) {
        keyboard_extint = 1;
        keyboard_extint_scancode = scancode;
    }

    if(scancode == 0x1D) {
        ctrl = 1;
    } else if(scancode == 0x9D) {
        ctrl = 0;
    } else if(scancode == 0x2E && ctrl) {
        ctrlc = 1;
    }
    
    outportb(0x20, 0x20);
}

void interrupt pit_irq(...) {
    ticks++;
    if(++irq_ticks == 55) {
        irq_ticks = 0;
        (*old_pit_irq)();
    } else {
        outportb(0x20, 0x20);
    }
}

void VM::JMP(int32_t address, int32_t segment) {
    address += segment;        
    if(address < 0 || address >= MEMORY_MODEL) {
        int_vm(ERR_END_EXECUTION, address, 0, 0);
        return;
    }

    CS = segment;
    IP = address;
}

void VM::JMP(int32_t address) {
    address += CS;
    if(address < 0 || address >= MEMORY_MODEL) {
        int_vm(ERR_END_EXECUTION, address, 0, 0);
        return;
    }
    
    IP = address;
}

void VM::CALL(int32_t address, int32_t segment) {
    Push(IP);
    if(interrupt_flag) return;
    JMP(address, segment);
}

void VM::CALL(int32_t address) {
    Push(IP);
    if(interrupt_flag) return;
    JMP(address);
}

void VM::int_vm(int32_t n, float p, char external, char cascade) {
    if(!cascade && interrupt_flag) return;

    LINT = n;
    LADD = p;
    interrupt_flag = 1;
    
    if(cli_flag) {
        if(extended_flag) {
            int32_t addr = IDTR + n*4;
            addr = (addr < 0) ? 0 : (addr > MEMORY_MODEL - 4) ? MEMORY_MODEL - 4 : addr;

            bus_lock = 0;
            GetPage(addr / 128, &current_page, &current_page_map);

            cli_flag = 0;
            interrupt_flag = 0;
            int prev_pcap = PCAP;
            PCAP = 0;
            int32_t ip = *ReadCell(addr);
            int32_t cs = *ReadCell(addr+1);
            int32_t newptbl = *ReadCell(addr+2);
            int flags = *ReadCell(addr+3);
            PCAP = prev_pcap;
            cli_flag = 1;

            if(interrupt_flag) {
                if(!cascade) int_vm(ERR_PROCESSOR_FAULT, 2, 0, 1);
                return;
            } else {
                interrupt_flag = 1;
            }

            previous_page = current_page;
            previous_page_map = current_page_map;
            GetPage(XEIP / 128, &current_page, &current_page_map);
            bus_lock = 1;

            if(external && !(flags & 64)) { // 6
                if(!cascade) int_vm(ERR_PROCESSOR_FAULT, 4, 0, 1);
                return;
            }

            if(flags & 32) { // 5

                bus_lock = 0;
                if(flags & 512) { // 9
                    for(char i = 0; i < 32; i++) {
                        Push(R[i]);
                    } 
                }

                cli_flag = 0;
                interrupt_flag = 0;
                Push(IP);
                Push(CS);
                cli_flag = 1;
                if(interrupt_flag) {
                    if(!cascade) int_vm(ERR_PROCESSOR_FAULT, 6, 0, 1);
                    return;
                }  

                cli_flag = 0;
                interrupt_flag = 0;
                if(flags & 16) { // 4
                    JMP(ip);
                } else {
                    JMP(ip, cs);
                }
                
                cli_flag = 1;
                if(interrupt_flag) {
                    if(!cascade) int_vm(ERR_PROCESSOR_FAULT, 7, 0, 1);
                    return;
                } else{
                    interrupt_flag = 1;
                }
                
                if(flags & 8) { // 3
                    CMPR = 1;
                }
            } else {
                if(flags & 8) { // 3
                    CMPR = 1;
                }
            }

            if(flags & 128) { // 7
                PTBL = newptbl;
            } else if(flags & 256) { // 8
                PTBE = newptbl;
            }
        } else {
            interrupt_skip = 0;
            return;
        }
    }

    bus_lock = 0;
}

void VM::extint_vm(int32_t n, float p) {
    if(cli_flag) {
        Push(LS); if(interrupt_flag) return;
        Push(KS); if(interrupt_flag) return;
        Push(ES); if(interrupt_flag) return;
        Push(GS); if(interrupt_flag) return;
        Push(FS); if(interrupt_flag) return;
        Push(DS); if(interrupt_flag) return;
        Push(SS); if(interrupt_flag) return;
        Push(CS); if(interrupt_flag) return;

        Push(EDI); if(interrupt_flag) return;
        Push(ESI); if(interrupt_flag) return;
        Push(ESP); if(interrupt_flag) return;
        Push(EBP); if(interrupt_flag) return;
        Push(EDX); if(interrupt_flag) return;
        Push(ECX); if(interrupt_flag) return;
        Push(EBX); if(interrupt_flag) return;
        Push(EAX); if(interrupt_flag) return;

        Push(CMPR); if(interrupt_flag) return;
        Push(IP); if(interrupt_flag) return;
        
        int_vm(n, p, 1, 1);
    }
}

void VM::PrivilegeRequest(float* op1, float* op2, int32_t opcode) {
    PreqOperand1 = *op1;
    PreqOperand2 = *op2;
    PreqReturn = 0;
    PreqHandled = -1;

    IP = XEIP;
    int_vm(ERR_PROCESSOR_FAULT, opcode, 0, 0);
}

void VM::ExecuteInstruction(Instruction* instruction, float* op1, float* op2) {
    if(instruction->privileged) {
        if(PCAP && current_page.bits.runlevel > 0) {
            if(PreqHandled == 0) {
                PrivilegeRequest(op1, op2, instruction->opcode);
                return;
            }

            PreqHandled = 0;
        }
    }

    instruction->execute(this, op1, op2);
    if(!interrupt_flag) {
        if(ext_flush[0]) {
            ext_flush[0] = 0;
            ExternalWrite(ext_op_address[0], ext_op[0]);
            if(interrupt_flag) return;
        }

        if(ext_flush[1]) {
            ext_flush[1] = 0;
            ExternalWrite(ext_op_address[1], ext_op[1]);
            if(interrupt_flag) return;
        }
    }
    Timer += TimerDT;
}

void VM::Push(float n) {
    if(bus_lock) return;

    WriteCell(ESP-- + SS, n);
    if(interrupt_flag) return;
    
    if(ESP < 0) {
        ESP = 0;
        int_vm(ERR_STACK_ERROR, ESP, 0, 0);
    }
}

float VM::Pop() {
    if(bus_lock) return 0;

    ESP++;

    if(ESP > ESZ) {
        ESP = ESZ;
        int_vm(ERR_STACK_ERROR, ESP, 0, 0);
        return NULL;
    }

    float* value = ReadCell(ESP + SS);
    if(interrupt_flag) return NULL;

    return *value;
}

void VM::GetPage(int32_t index, Page* page, int32_t* map) {
    if(PCAP && extended_memory_flag) {
        int32_t pageEntry;

        if(index >= PTBE || index < 0) {
            pageEntry = PTBL;
        } else {
            pageEntry = PTBL + (index + 1) * 2;
        }

        PCAP = 0;
        float* new_bits = ReadCell(pageEntry);
        float* new_map = ReadCell(pageEntry + 1);
        PCAP = 1;

        if(interrupt_flag) return;

        page->raw = *new_bits;
        *map = *new_map;
    }
}

void VM::SetPage(int32_t index, int32_t mask, int32_t map) {
    if(PCAP && extended_memory_flag) {
        int32_t pageEntry;

        if(index >= PTBE || index < 0) {
            pageEntry = PTBL;
        } else {
            pageEntry = PTBL + (index + 1) * 2;
        }

        PCAP = 0;
        WriteCell(pageEntry, mask);
        WriteCell(pageEntry + 1, map);
        PCAP = 1;
    }
}

float* VM::ReadCell(int32_t address, char operand) {
    if(bus_lock) return NULL;
    
    TMR += INTERNAL_READ_CYCLES;

    if(address < 0) {
        int_vm(ERR_MEMORY_FAULT, address, 0, 0);
        return NULL;
    }

    if(PCAP && extended_memory_flag) {
        int32_t index = address / 128;
        Page page;
        int32_t map;
        GetPage(index, &page, &map);
        if(interrupt_flag) return NULL;

        if(page.bits.trapped) {
            int_vm(ERR_PAGE_TRAPPED, address, 0, 0);
            //return NULL;
        }
        
        if(page.bits.disabled) {
            int_vm(ERR_MEMORY_FAULT, address, 0, 0);
            return NULL;
        }

        if(extended_flag && current_page.bits.runlevel > page.bits.runlevel && !page.bits.read) {
            int_vm(ERR_READ_VIOLATION, address, 0, 0);
            return NULL;
        }

        if(page.bits.remapped && map != index) {
            address = address % 128 + map * 128;
        }

        if(page.bits.override) {
            if(MEMRQ == 4) {
                static float immediate = LADD;
                MEMRQ = 0;
                return &immediate;
            } else {
                MEMRQ = 2;
                MEMADDR = address;
                if(address >= MEMORY_MODEL) {
                    TMR += EXTERNAL_READ_CYCLES;
                    LADD = *ExternalRead(address, operand);
                } else {
                    LADD = Memory[address];
                }

                TMR += 10;
                int_vm(READ_REQUEST, 0, 0, 0);
                return NULL;
            }
        }
    }

    if(address >= MEMORY_MODEL) {
        TMR += EXTERNAL_READ_CYCLES;
        return ExternalRead(address, operand);
    } else {
        return &Memory[address];
    }
}

void VM::WriteCell(int32_t address, float value) {
    if(bus_lock) return;

    TMR += INTERNAL_WRITE_CYCLES;
    if(address < 0) {
        int_vm(ERR_MEMORY_FAULT, address, 0, 0);
        return;
    }

    if(PCAP && extended_memory_flag) {
        int32_t index = address / 128;
        Page page;
        int32_t map;
        GetPage(index, &page, &map);
        if(interrupt_flag) return;

        if(page.bits.trapped) {
            int_vm(ERR_PAGE_TRAPPED, address, 0, 0);
            return;
        }
        
        if(page.bits.disabled) {
            int_vm(ERR_MEMORY_FAULT, address, 0, 0);
            return;
        }

        if(page.bits.override) {
            if(MEMRQ == 6) {
                MEMRQ = 0;
                return;
            } else if(MEMRQ == 5) {
                MEMRQ = 0;
                address = MEMADDR;
                value = LADD;
            } else {
                MEMRQ = 3;
                MEMADDR = address;
                LADD = value;

                TMR += 10;
                int_vm(WRITE_REQUEST, LADD, 0, 0);
                return;
            }
        }

        if(extended_flag && current_page.bits.runlevel > page.bits.runlevel && !page.bits.write) {
            int_vm(ERR_WRITE_VIOLATION, address, 0, 0);
            return;
        }

        if(page.bits.remapped && map != index) {
            address = address % 128 + map * 128;
        }
    }

    if(address >= MEMORY_MODEL) {
        TMR += EXTERNAL_WRITE_CYCLES;
        ExternalWrite(address, value);
    } else {
        Memory[address] = value;
    }
}

float* VM::ExternalRead(int32_t address, char operand) {
    if(address >= MEMORY_MODEL && address < MEMORY_MODEL + 2000) {
        if(operand) {
            ext_swap = !ext_swap;
            ext_flush[ext_swap] = 1;
            ext_op[ext_swap] = screen_ptr[address - MEMORY_MODEL];
            ext_op_address[ext_swap] = address;
            return &ext_op[ext_swap];
        } else {
            static float immediate;
            immediate = screen_ptr[address - MEMORY_MODEL];
            return &immediate;
        }
    } else {
        int_vm(ERR_MEMORY_FAULT, address, 0, 0);
        return NULL;
    }
}

void VM::ExternalWrite(int32_t address, float value) {
    if(address >= MEMORY_MODEL && address < MEMORY_MODEL + 2000) {
        screen_ptr[address - MEMORY_MODEL] = value;
    } else {
        int_vm(ERR_MEMORY_FAULT, address, 0, 0);
        return;
    }
}

float VM::fetch() {
    int32_t address = CS + IP;

    if(address < 0 || address >= MEMORY_MODEL) {
        int_vm(ERR_MEMORY_FAULT, address, 0, 0);
        return 0;
    }

    IP++; 
    return Memory[address];
}

float* VM::GetOperand(int32_t rm, int32_t segment) {
    if(rm == 0) {
        static float immediates[2];
        immediate_swap = !immediate_swap;
        immediates[immediate_swap] = fetch();
        if(interrupt_flag) return NULL;

        return &immediates[immediate_swap];
    } else if(rm <= 16) {
        float* reg = GetRegister(rm);
        if(interrupt_flag) return NULL;

        return reg;
    } else if(rm >= 17 && rm <= 24) {
        float* reg = GetRegister(rm - 16);
        if(interrupt_flag) return NULL;

        if(segment == -1) {
            return ReadCell(*reg + DS, 1);
        } else {
            float* seg = GetSegment(segment);
            if(interrupt_flag) return NULL;
            return ReadCell(*reg + *seg, 1);
        }
    } else if(rm == 25) {
        float addr = fetch();
        if(interrupt_flag) return NULL;

        if(segment == -1) {
            return ReadCell(addr + DS, 1);
        } else {
            float* seg = GetSegment(segment);
            if(interrupt_flag) return NULL;
            return ReadCell(addr + *seg, 1);
        }
    } else if(rm >= 26 && rm <= 33) {
        float* seg = GetSegment(segment);
        if(interrupt_flag) return NULL;

        float* reg = GetRegister(rm - 26);
        if(interrupt_flag) return NULL;
        
        static float immediate;
        
        immediate = *seg + *reg;
        return &immediate;
    } else if(rm == 50) {
        float* reg = GetSegment(segment);
        if(interrupt_flag) return NULL;
        static float immediate;
        immediate = fetch();
        if(interrupt_flag) return NULL;
        immediate += *reg;
        return &immediate;
    } else if(rm >= 2048 && rm <= 2079) {
        return &R[rm-2048];
    } else if(rm >= 2080 && rm <= 2111) {
        if(segment == -1) {
            return ReadCell(R[rm-2080] + DS, 1);
        } else {
            float* seg = GetSegment(segment);
            if(interrupt_flag) return NULL;
            return ReadCell(R[rm-2080] + *seg, 1);
        }
    } else if(rm >= 2144 && rm <= 2175) {
        float addr = fetch();
        if(interrupt_flag) return NULL;

        if(segment == -1) {
            return ReadCell(addr + DS, 1);
        } else {
            float* seg = GetSegment(segment);
            if(interrupt_flag) return NULL;
            return ReadCell(addr + *seg, 1);
        }
    }

    int_vm(ERR_PROCESSOR_FAULT, 0, 0, 0);
    return NULL;
}

float* VM::GetRegister(int32_t index) {
    switch(index) {
        case 0: goto invalid;
        case 1: return &EAX;
        case 2: return &EBX;
        case 3: return &ECX;
        case 4: return &EDX;
        case 5: return &ESI;
        case 6: return &EDI;
        case 7: return &ESP;
        case 8: return &EBP;
        case 9: return &CS;
        case 10: return &SS;
        case 11: return &DS;
        case 12: return &ES;
        case 13: return &GS;
        case 14: return &FS;
        case 15: return &KS;
        case 16: return &LS;
        default: invalid:
            int_vm(ERR_PROCESSOR_FAULT, 0, 0, 0);
            return NULL;
    }
}

float* VM::GetSegment(int32_t index) {
    switch(index) {
        case 0: goto invalid;
        case 1: return &CS;
        case 2: return &SS;
        case 3: return &DS;
        case 4: return &ES;
        case 5: return &GS;
        case 6: return &FS;
        case 7: return &KS;
        case 8: return &LS;
        case 9: return &EAX;
        case 10: return &EBX;
        case 11: return &ECX;
        case 12: return &EDX;
        case 13: return &ESI;
        case 14: return &EDI;
        case 15: return &ESP;
        case 16: return &EBP;
        default: invalid:
            if(index >= 17 && index <= 47) {
                return &R[index - 17];
            }

            int_vm(ERR_PROCESSOR_FAULT, index, 0, 0);
            return NULL;
    }
}

float VM::GetInternalRegister(int32_t index) {
    switch(index) {
        case 0: return IP;
        case 1: return EAX;
        case 2: return EBX;
        case 3: return ECX;
        case 4: return EDX;
        case 5: return ESI;
        case 6: return EDI;
        case 7: return ESP;
        case 8: return EBP;
        case 9: return ESZ;
        case 16: return CS;
        case 17: return SS;
        case 18: return DS;
        case 19: return ES;
        case 20: return GS;
        case 21: return FS;
        case 22: return KS;
        case 23: return LS;
        case 24: return IDTR;
        case 25: return CMPR;
        case 26: return XEIP;
        case 27: return LADD;
        case 28: return LINT;
        case 29: return TMR; // TMR
        case 30: return Timer; // TIMER
        case 31: return 0; // CPAGE
        case 32: return interrupt_flag;
        case 33: return 0; // PF
        case 34: return extended_flag;
        case 35: return n_cli_flag; // NIF
        case 36: return extended_memory_flag;
        case 37: return PTBL;
        case 38: return PTBE;
        case 39: return PCAP; // PCAP
        case 40: return 0; // RQCAP
        case 41: return 0; // PPAGE
        case 42: return MEMRQ;
        case 43: return MEMORY_MODEL;
        case 44: return 0; // External
        case 45: return bus_lock; // Buslock
        case 46: return idle; // Idle
        case 47: return interrupt_flag; // INTR
        case 48: return 0; // Serial Number
        case 49: return 0; // Code Bytes
        case 50: return 0; // BPREC
        case 51: return 0; // IPREC
        case 52: return 0; // NIDT
        case 53: return BLOCKSTART;
        case 54: return BLOCKSIZE;
        case 55: return 0; // VMODE
        case 56: return 0; // XTRL
        case 57: return 0; // HaltPort
        case 58: return 0; // HWDEBUG
        case 59: return 0; // DBGSTATE
        case 60: return 0; // DBGADDR
        case 61: return 0; // CRL
        case 62: return TimerDT; // TIMERDT
        case 63: return MEMADDR;
        case 64: return TimerMode; // TimerMode
        case 65: return TimerRate; // TimerRate
        case 66: return TimerPrevTime; // TimerPrevTime
        case 67: return TimerAddress; // TimerAddress
        case 68: return TimerPrevMode; // TimerPrevMode
        case 69: return 0; // LASTQUO
        case 70: return 0; // QUOFLAG
        case 71: return PreqOperand1;
        case 72: return PreqOperand2;
        case 73: return PreqReturn;
        case 74: return PreqHandled;
        case 75: return external_interrupts;
        case 76: return portb;
        default:
            if(index >= 96 && index <= 126) {
                return R[index - 17];
            }

            int_vm(ERR_PROCESSOR_FAULT, index, 0, 0);
            return NULL;
    }
}

void VM::SetInternalRegister(int32_t index, float value) {
    switch(index) {
        case 0: JMP(value); break; // IP
        case 1: EAX = value; break;
        case 2: EBX = value; break;
        case 3: ECX = value; break;
        case 4: EDX = value; break;
        case 5: ESI = value; break;
        case 6: EDI = value; break;
        case 7: ESP = value; break;
        case 8: EBP = value; break;
        case 9: ESZ = value; break;
        case 16: CS = value; break;
        case 17: SS = value; break;
        case 18: DS = value; break;
        case 19: ES = value; break;
        case 20: GS = value; break;
        case 21: FS = value; break;
        case 22: KS = value; break;
        case 23: LS = value; break;
        case 24: IDTR = value; break;
        case 25: CMPR = value; break;
        case 26: break; // XEIP
        case 27: LADD = value; break;
        case 28: LINT = value; break;
        case 29: TMR = value; break; // TMR
        case 30: Timer = value; break; // TIMER
        case 31: break; // CPAGE
        case 32: interrupt_flag = value; break;
        case 33: break; // PF
        case 34: extended_flag = value; break;
        case 35: n_cli_flag; // NIF
        case 36: extended_memory_flag = value; break;
        case 37: PTBL = value; break;
        case 38: PTBE = value; break;
        case 39: break; // PCAP
        case 40: break; // RQCAP
        case 41: break; // PPAGE
        case 42: break; // MEMRQ
        case 43: break; // Memory Model
        case 44: break; // External
        case 45: bus_lock = value; break; // Buslock
        case 46: break; // Idle
        case 47: interrupt_flag; // INTR
        case 48: break; // Serial Number
        case 49: break; // Code Bytes
        case 50: break; // BPREC
        case 51: break; // IPREC
        case 52: break; // NIDT
        case 53: BLOCKSTART = value; break;
        case 54: BLOCKSIZE = value; break;
        case 55: break; // VMODE
        case 56: break; // XTRL
        case 57: break; // HaltPort
        case 58: break; // HWDEBUG
        case 59: break; // DBGSTATE
        case 60: break; // DBGADDR
        case 61: break; // CRL
        case 62: break; // TIMERDT
        case 63: break; // MEMADDR
        case 64: TimerMode = value; break; // TimerMode
        case 65: TimerRate = value; break; // TimerRate
        case 66: TimerPrevTime = value; break; // TimerPrevTime
        case 67: TimerAddress = value; break; // TimerAddress
        case 68: TimerPrevMode = value; break; // TimerPrevMode
        case 69: break; // LASTQUO
        case 70: break; // QUOFLAG
        case 71: PreqOperand1 = value; break;
        case 72: PreqOperand2 = value; break;
        case 73: PreqReturn = value; break;
        case 74: PreqHandled = value; break;
        case 75: external_interrupts = value; break;
        case 76: portb = value; break;
        default:
            if(index >= 96 && index <= 126) {
                R[index - 17] = value;
            } else {
                int_vm(ERR_PROCESSOR_FAULT, index, 0, 0);
            }
            break;
    }
}

void VM::step() {
    if(bus_lock) return;
    
    if(TimerMode != TimerPrevMode) {
        switch(TimerMode) {
            case 0: break;
            case 1: TimerPrevTime = Timer; break;
            case 2: TimerPrevTime = TMR; break;
            default: break;
        }

        TimerPrevMode = TimerMode;
    }

    switch(TimerMode) {
        case 0: break;
        case 1:
            if(Timer - TimerPrevTime >= TimerRate) {
                TimerPrevTime = Timer;
                extint_vm(TimerAddress, 0);
                return;
            }
            break;
        case 2: {
            if(TMR - TimerPrevTime >= TimerRate) {
                TimerPrevTime = TMR;
                extint_vm(TimerAddress, 0);
                return;
            }
            break;
        }
        default: break;
    }

    interrupt_flag = 0;
    if(n_cli_flag) {
        cli_flag = 1;
        n_cli_flag = 0;
    }
    
    XEIP = IP + CS;
    TMR++;

    float time = ticks / 1000.0f;
    TimerDT = time - PrevTime;
    PrevTime = time;

    previous_page = current_page;
    previous_page_map = current_page_map;
    GetPage(XEIP / 128, &current_page, &current_page_map);
    if(interrupt_flag) return;

    if(PCAP && !current_page.bits.execute && previous_page.bits.runlevel > 0) {
        int_vm(ERR_EXECUTE_VIOLATION, IP, 0, 0);
        return;
    }

    int32_t opcode = fetch();
    if(interrupt_flag) return;    

    /*
    //bool isFixedSize = false;
    if((opcode >= 2000 && opcode < 4000) || (opcode >= 12000 && opcode < 14000)) {
        opcode -= 2000;
        //isFixedSize = true;
    }
    */

    if(opcode >= 0 && opcode < (sizeof(instructions) / sizeof(Instruction))) {
        if(!instructions[opcode].operand_count && instructions[opcode].execute != NULL) {
            static float blank;
            blank = 0;
            
            ExecuteInstruction(&instructions[opcode], &blank, &blank);
            return;
        }
    }

    int32_t rm = fetch();
    if(interrupt_flag) return;

    int32_t rm2 = rm / 10000;
    int32_t rm1 = rm - (rm2 * 10000);

    int32_t segment1 = -1;
    int32_t segment2 = -1;

    if(opcode > 1000) {
        if(opcode > 10000) {
            segment2 = fetch();
            if(interrupt_flag) return;
            opcode -= 10000;

            if(opcode > 1000) {
                segment1 = fetch();
                if(interrupt_flag) return;
                opcode -= 1000;
            }
        } else {
            segment1 = fetch();
            if(interrupt_flag) return;
            opcode -= 1000;
        }
    }

    if(opcode < 0 || opcode >= (sizeof(instructions) / sizeof(Instruction)) || !instructions[opcode].execute) {
        int_vm(ERR_UNKNOWN_OPCODE, opcode, 0, 0);
    } else {
         if(instructions[opcode].operand_count == 1) {
            static float blank;
            
            float* op1 = GetOperand(rm1, segment1);
            if(interrupt_flag) return;

            blank = 0;
            ExecuteInstruction(&instructions[opcode], op1, &blank);
        } else {
            float* op1 = GetOperand(rm1, segment1);
            if(interrupt_flag) return;

            float* op2 = GetOperand(rm2, segment2);
            if(interrupt_flag) return;

            ExecuteInstruction(&instructions[opcode], op1, op2);
        }
    }
}

void VM::VM() {
    int i;
    for(i = 0; i < MEMORY_MODEL; i++) Memory[i] = 0;
    for(i = 0; i < 32; i++) R[i] = 0;
    IP = XEIP = CMPR = interrupt_flag = LADD = LINT = extended_flag = extended_memory_flag = external_interrupts = 0;
    bus_lock = 0;
    cli_flag = 1;
    n_cli_flag = 0;
    interrupt_skip = 1;
    EAX = EBX = ECX = EDX = ESI = EDI = 0;
    ESP = MEMORY_MODEL-1;
    EBP = 0;
    ESZ = ESP;
    CS = SS = DS = ES = GS = FS = KS = LS = 0;
    PTBL = PTBE = 0;
    PCAP = 1;
    immediate_swap = 0;
    MEMRQ = MEMADDR = 0;
    BLOCKSTART = BLOCKSIZE = 0;
    PreqHandled = -1;
    PreqOperand1 = PreqOperand2 = PreqReturn = 0;
    current_page.raw = 0;
    current_page_map = 0;
    previous_page.raw = 0;
    previous_page_map = 0;
    TMR = 0;
    Timer = 0;
    TimerDT = 0;
    PrevTime = 0;
    TimerMode = 0;
    TimerRate = 0;
    TimerPrevTime = 0;
    TimerPrevMode = 0;
    idle = 0;
    ext_swap = 0;
    ext_op[0] = 0;
    ext_op[1] = 0;
    ext_op_address[0] = 0;
    ext_op_address[1] = 0;
    ext_flush[0] = 0;
    ext_flush[1] = 0;
    portb = 0;
}

#ifdef DEBUG_MODE
    #if DEBUG_MODE == 1
        void debug_print(int* ptr, float n) {
            static char str[128];
            sprintf(str, "%f  ", n);

            int i = 0;
            while(str[i]) {
                ptr[i] = 0x0F00 | str[i];
                i++;
            }

            int cursor_x = (ptr - screen_ptr) % 80;
            int remaining = 80 - cursor_x;

            while(i < remaining) {
                ptr[i++] = 0x0020;
            }
        }

        void debug_print_register(int** ptr, int** ptr_2, char* str) {
            int i = 0;
            int output;
            int* real_ptr = *ptr;

            while(str[i]) {
                output = 0x7000 | str[i];
                real_ptr[i] = output;
                i++;
            }

            int cursor_x = (real_ptr - screen_ptr) % 80;
            int remaining = 80 - ((cursor_x + i) % 80);

            *ptr = real_ptr + i + remaining;
            *ptr_2 = real_ptr + i + 1;
        }
    #endif
#endif

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("You need to provide the filename as an argument.");
        return 1;
    }

    srand(time(NULL));

    FILE* script = fopen(argv[1], "r");
    if(!script) {
        printf("Couldn't open the file.");
        return 1;
    }

    int32_t frequency;
    if(argv[2]) {
        frequency = atol(argv[2]);
    } else{
        frequency = 5000;
    }

    VM vm;

    int32_t count = 0;
    char num[32];
    int len = 0;

    while(1) {
        int ch = fgetc(script);
        if((ch >= '0' && ch <= '9') || ch == '-' || ch == '.') {
            if(len < 31) num[len++] = ch;
        } else if(len) {
            if(count >= MEMORY_MODEL) break;
            num[len] = 0;
            vm.Memory[count++] = atof(num);
            len = 0;
        }

        if(ch == EOF) break;
    }

    if(len && count < MEMORY_MODEL) {
        num[len] = 0;
        vm.Memory[count++] = atof(num);
    }

    fclose(script);

    asm {
        PUSH AX
        PUSH BX
        PUSH CX
        PUSH DX

        MOV AH, 7
        XOR AL, AL
        XOR CX, CX
        MOV BX, 0x0700
        MOV DH, 25
        MOV DL, 80
        INT 010h
        
        POP DX
        POP CX
        POP BX
        POP AX
    }

    printf("\033[1;1HLoaded bytecode (\033[1;37m%ld\033[0m bytes)\n", count);

    /*
    for(size_t i = 0; i < count; i++) {
        printf("%f ", vm.Memory[i]);
    }

    printf("\n");
    */

    #ifdef DEBUG_MODE
            #if DEBUG_MODE == 1
                int* new_ptr = screen_ptr + 960;
        
                int* ip_ptr;
                debug_print_register(&new_ptr, &ip_ptr, " IP:");

                int* eax_ptr;
                debug_print_register(&new_ptr, &eax_ptr, "EAX:");
        
                int* ebx_ptr;
                debug_print_register(&new_ptr, &ebx_ptr, "EBX:");
        
                int* ecx_ptr;
                debug_print_register(&new_ptr, &ecx_ptr, "ECX:");
        
                int* edx_ptr;
                debug_print_register(&new_ptr, &edx_ptr, "EDX:");
        
                int* esi_ptr;
                debug_print_register(&new_ptr, &esi_ptr, "ESI:");
        
                int* edi_ptr;
                debug_print_register(&new_ptr, &edi_ptr, "EDI:");
        
                int* esp_ptr;
                debug_print_register(&new_ptr, &esp_ptr, "ESP:");
        
                int* ebp_ptr;
                debug_print_register(&new_ptr, &ebp_ptr, "EBP:");
        
                int* cs_ptr;
                debug_print_register(&new_ptr, &cs_ptr, " CS:");
        
                int* ds_ptr;
                debug_print_register(&new_ptr, &ds_ptr, " DS:");
        
                int* r0_ptr;
                debug_print_register(&new_ptr, &r0_ptr, " R0:");
        
                int* r1_ptr;
                debug_print_register(&new_ptr, &r1_ptr, " R1:");
                
                int breakPoint;
                if(argv[3]) {
                    breakPoint = atoi(argv[3]);
                } else {
                    breakPoint = -1;
                }
            #endif
    #endif

    printf("\033[0;37mExecuting bytecode (\033[1;37m%ld\033[0m hz)\n", frequency);
    
    unsigned int divisor = (unsigned int)(PITFreq / 1000.0 + 0.5);

    old_pit_irq = getvect(PITIRQ);
    setvect(PITIRQ, pit_irq);

    outportb(0x43, 0x36);
    outportb(0x40, divisor & 0xFF);
    outportb(0x40, (divisor >> 8) & 0xFF);

    old_keyboard_irq = getvect(KEYBOARD_IRQ);
    setvect(KEYBOARD_IRQ, keyboard_irq);

    uint32_t inst_count = 0;
    int32_t cycles = 0;
    uint32_t prev_ticks = ticks;
    uint32_t prev_tmr = 0;
    uint32_t cur_ticks;

    ldiv_t cost;
    cost.rem = 0;

    while(1) {
        cur_ticks = ticks;
        cost = ldiv(frequency * (cur_ticks - prev_ticks) + cost.rem, 1000);
        cycles += cost.quot;
        prev_ticks = cur_ticks;

        while(cycles > 0 && !vm.idle) {
            prev_tmr = vm.TMR;
            vm.step();
            cycles -= vm.TMR - prev_tmr;
            inst_count++;
            
            if(ctrlc) break;
            if(!vm.interrupt_skip) break;

            if(vm.external_interrupts) {
                if(keyboard_extint) {
                    vm.extint_vm(32, keyboard_extint_scancode);
                    keyboard_extint = 0;
                }
            }

            #ifdef DEBUG_MODE
                #if DEBUG_MODE == 1
                    debug_print(ip_ptr, vm.IP);
                    debug_print(eax_ptr, vm.EAX);
                    debug_print(ebx_ptr, vm.EBX);
                    debug_print(ecx_ptr, vm.ECX);
                    debug_print(edx_ptr, vm.EDX);
                    debug_print(esi_ptr, vm.ESI);
                    debug_print(edi_ptr, vm.EDI);
                    debug_print(esp_ptr, vm.ESP);
                    debug_print(ebp_ptr, vm.EBP);
                    debug_print(cs_ptr, vm.CS);
                    debug_print(ds_ptr, vm.DS);
                    debug_print(r0_ptr, vm.R[0]);
                    debug_print(r1_ptr, vm.R[1]);

                    if(vm.IP == breakPoint) break;
                #endif
            #endif
        }

        vm.idle = 0;
        if(!vm.interrupt_skip || ctrlc) break;
    }

    outportb(0x43, 0x36);
    outportb(0x40, 0x00);
    outportb(0x40, 0x00);
    setvect(PITIRQ, old_pit_irq);
    setvect(KEYBOARD_IRQ, old_keyboard_irq);

    printf("\033[1;31mError:\033[0m \033[1;37m%d.%f\033[0m, \033[1;31mIP:\033[0m \033[1;37m%ld\033[0m, \033[1;31mIPS:\033[0m \033[1;37m%u\033[0m", vm.LINT, vm.LADD, vm.IP, (uint32_t)(inst_count / (ticks / 1000.0f)));
    return 0;
}