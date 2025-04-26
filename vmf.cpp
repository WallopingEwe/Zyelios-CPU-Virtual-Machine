#pragma warn -par
#define MEMORY_MODEL 512
#define DEBUG_MODE 1
#include "zcpu/stdint.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
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
int far* print_ptr = (int far*)MK_FP(0xb800,0);

Instruction instructions[] = {
    { 0, 0, END },
    { 1, 1, JNE },
    { 2, 1, JMP },
    { 3, 1, JG },
    { 4, 1, JGE },
    { 5, 1, JL },
    { 6, 1, JLE },
    { 7, 1, JE },
    { 8, 0, CPUID },
    { 9, 1, PUSH },
    { 10, 2, ADD },
    { 11, 2, SUB },
    { 12, 2, MUL },
    { 13, 2, DIV },
    { 14, 2, MOV },
    { 15, 2, CMP },
    { 16, 0, 0 },
    { 17, 0, 0 },
    { 18, 2, MIN },
    { 19, 2, MAX },
    { 20, 1, INC },
    { 21, 1, DEC },
    { 22, 1, NEG },
    { 23, 1, RAND },
    { 24, 1, LOOP },
    { 25, 1, LOOPA },
    { 26, 1, LOOPB },
    { 27, 1, LOOPD },
    { 28, 0, SPG },
    { 29, 0, CPG },
    { 30, 1, POP },
    { 31, 1, CALL },
    { 32, 1, BNOT },
    { 33, 1, FINT },
    { 34, 1, RND },
    { 35, 1, FFRAC },
    { 36, 1, FINV },
    { 37, 0, 0 },
    { 38, 1, FSHL },
    { 39, 1, FSHR },
    { 40, 0, RET },
    { 41, 0, IRET },
    { 42, 0, STI },
    { 43, 0, CLI },
    { 44, 0, 0 },
    { 45, 0, 0 },
    { 46, 0, 0 },
    { 47, 0, RETF },
    { 48, 0, STEF },
    { 49, 0, CLEF },
    { 50, 2, AND },
    { 51, 2, OR },
    { 52, 2, XOR },
    { 53, 2, FSIN },
    { 54, 2, FCOS },
    { 55, 2, FTAN },
    { 56, 2, FASIN },
    { 57, 2, FACOS },
    { 58, 2, FATAN },
    { 59, 2, MOD },
    { 60, 2, BIT },
    { 61, 2, SBIT },
    { 62, 2, CBIT },
    { 63, 2, TBIT },
    { 64, 2, BAND },
    { 65, 2, BOR },
    { 66, 0, 0 },
    { 67, 2, BSHL },
    { 68, 0, BSHR },
    { 69, 2, JUMPF },
    { 70, 0, EXTINT },
    { 71, 1, CNE },
    { 72, 0, 0 },
    { 73, 1, CG },
    { 74, 1, CGE },
    { 75, 1, CL },
    { 76, 1, CLE },
    { 77, 1, CE },
    { 78, 1, MCOPY },
    { 79, 1, MXCHG },
    { 80, 2, FPWR },
    { 81, 2, XCHG },
    { 82, 2, FLOG },
    { 83, 2, FLOG10 },
    { 84, 2, IN },
    { 85, 2, OUT },
    { 86, 2, FABS },
    { 87, 2, FSGN },
    { 88, 2, FEXP },
    { 89, 2, CALLF },
    { 90, 1, FPI },
    { 91, 1, FE },
    { 92, 1, INT },
    { 93, 0, TPG },
    { 94, 1, FCEIL },
    { 95, 0, ERPG },
    { 96, 0, WRPG },
    { 97, 0, RDPG },
    { 98, 0, TIMER },
    { 99, 1, LIDTR },
    { 100, 0, 0 },
    { 101, 1, JNER },
    { 102, 1, JMPR },
    { 103, 1, JGR },
    { 104, 1, JGER },
    { 105, 1, JLR },
    { 106, 1, JLER },
    { 107, 1, JER },
    { 108, 1, LNEG },
    { 109, 0, 0 },
    { 110, 0, EXTRET },
    { 111, 0, IDLE },
    { 112, 0, NOP },
    { 113, 0, 0 },
    { 114, 0, PUSHA },
    { 115, 0, POPA },
    { 116, 0, STD2 },
    { 117, 0, LEAVE },
    { 118, 0, STM },
    { 119, 0, CLM },
    { 120, 0, CPUGET },
    { 121, 0, CPUSET },
    { 122, 0, SPP },
    { 123, 0, CPP },
    { 124, 0, SRL },
    { 125, 0, CRL },
    { 126, 0, LEA },
    { 127, 0, BLOCK },
    { 128, 2, CMPAND },
    { 129, 2, CMPOR },
    { 130, 0, MSHIFT },
    { 131, 0, SMAP },
    { 132, 0, GMAP },
    { 133, 2, RSTACK },
    { 134, 2, SSTACK },
    { 135, 1, ENTER },
    { 136, 0, IRETP },
    { 137, 0, EXTRETP },
    { 138, 0, 0 },
    { 139, 0, 0 },
    { 140, 0, EXTRETA },
    { 141, 0, EXTRETPA },
    { 142, 0, 0 },
    { 143, 0, 0 },
    { 144, 0, 0 },
    { 145, 0, 0 },
    { 146, 0, 0 },
    { 147, 0, 0 },
    { 148, 0, 0 },
    { 149, 0, 0 },
    { 150, 0, STERR },
    { 151, 0, CLERR },
    { 152, 0, QUOCMP },
    { 153, 0, QUOTIMER },
};

void VM::JMP(int32_t address, int32_t segment) {
    address += segment;        
    if(address < 0 || address >= MEMORY_MODEL) {
        int_vm(ERR_END_EXECUTION);
        return;
    }

    CS = segment;
    IP = address;
}

void VM::JMP(int32_t address) {
    address += CS;
    if(address < 0 || address >= MEMORY_MODEL) {
        int_vm(ERR_END_EXECUTION);
        return;
    }
    
    IP = address;
}

void VM::CALL(int32_t address, int32_t segment) {
    Push(IP);
    if (interrupt_flag) return;
    JMP(address, segment);
}

void VM::CALL(int32_t address) {
    Push(IP);
    if (interrupt_flag) return;
    JMP(address);
}

void VM::int_vm(int32_t n) {
    if(cli_flag) {
        interrupt_flag = n;
        interrupt_skip = 1;
        return;
    }

    if(extended_flag) {
        int32_t addr = IDTR + n*4;
        addr = (addr < 0) ? 0 : (addr > MEMORY_MODEL - 2) ? MEMORY_MODEL - 2 : addr;

        int32_t ip = *ReadCell(addr);
        int32_t cs = *ReadCell(addr+1);
        int32_t newptbl = *ReadCell(addr+2);
        int32_t flags = *ReadCell(addr+3);

        if(flags & 32) { // 5

            Push(IP);
            Push(CS);

            if(flags & 8) { // 3
                CMPR = 1;
            }

            if(flags & 16) { // 4
                JMP(ip);
            } else {
                JMP(ip, cs);
            }

            if(flags & 128) { // 7
                PTBL = newptbl;
            }
    
            if(flags & 256) { // 8
                PTBE = newptbl;
            }

            if(flags & 512) { // 9
                for(int i = 0; i < 31; i++) {
                    Push(R[i]);
                } 
            }

            interrupt_skip = 1;
        }
    }

    interrupt_flag = n;
}

void VM::Push(float n) {
    int32_t address = ESP + SS;

    if(ESP == SS || address < 0 || address >= MEMORY_MODEL) {
        int_vm(ERR_STACK_ERROR);
        return;
    }
    
    Memory[address] = n;
    ESP--;
}

float VM::Pop() {
    ESP++;

    int32_t address = ESP + SS;
    if(address < 0 || address >= MEMORY_MODEL) {
        int_vm(ERR_STACK_ERROR);
        return NULL;
    }

    return Memory[address];
}

float* VM::ReadCell(int32_t address, int32_t segment) {
    address += segment;

    if (address < 0 || address >= MEMORY_MODEL) {
        int_vm(ERR_MEMORY_FAULT);
        return nullptr;
    }

    return &Memory[address];
}

float* VM::ReadCell(int32_t address) {
    address += DS;

    if (address < 0 || address >= MEMORY_MODEL) {
        int_vm(ERR_MEMORY_FAULT);
        return nullptr;
    }

    return &Memory[address];
}
    
void VM::WriteCell(int32_t address, int32_t segment, int32_t value) {
    address += segment;

    if (address < 0 || address >= MEMORY_MODEL) {
        int_vm(ERR_MEMORY_FAULT);
        return;
    }

    Memory[address] = value;
}

void VM::WriteCell(int32_t address, int32_t value) {
    address += DS;
    
    if (address < 0 || address >= MEMORY_MODEL) {
        int_vm(ERR_MEMORY_FAULT);
        return;
    }

    Memory[address] = value;
}

float VM::fetch() {
    int32_t address = CS + IP;

    if(address < 0 || address >= MEMORY_MODEL) {
        int_vm(ERR_MEMORY_FAULT);
        return 0;
    }

    float value = Memory[address];
    IP++; 

    return value;
}

float* VM::GetOperand(int32_t rm, int32_t segment) {
    if (rm == 0) {
        static float immediates[2];
        immediate_swap = !immediate_swap;
        immediates[immediate_swap] = fetch();
        if (interrupt_flag) return nullptr;

        return &immediates[immediate_swap];
    } else if (rm <= 16) {
        float* reg = GetRegister(rm);
        if (interrupt_flag) return nullptr;

        return reg;
    } else if (rm >= 17 && rm <= 24) {
        float* reg = GetRegister(rm - 16);
        if (interrupt_flag) return nullptr;

        if(segment == -1) {
            return ReadCell(*reg);
        } else {
            float* seg = GetSegment(segment);
            if (interrupt_flag) return nullptr;
            return ReadCell(*reg, *seg);
        }
    } else if (rm == 25) {
        float addr = fetch();
        if (interrupt_flag) return nullptr;

        if(segment == -1) {
            return ReadCell(addr);
        } else {
            float* reg = GetSegment(segment);
            if (interrupt_flag) return nullptr;
            return ReadCell(*reg, addr);
        }
    } else if (rm == 50) {
        float* reg = GetSegment(segment);
        if (interrupt_flag) return nullptr;
        static float immediate;
        immediate = fetch();
        if (interrupt_flag) return nullptr;
        immediate += *reg;
        return &immediate;
    } else if (rm >= 2048 && rm <= 2079) {
        return &R[rm-2048];
    } else if (rm >= 2080 && rm <= 2111) {
        if(segment == -1) {
            return ReadCell(R[rm-2080]);
        } else {
            float* reg = GetSegment(segment);
            if (interrupt_flag) return nullptr;
            return ReadCell(*reg, R[rm-2080]);
        }
    } else if (rm >= 2144 && rm <= 2175) {
        float addr = fetch();
        if (interrupt_flag) return nullptr;

        if(segment == -1) {
            return ReadCell(addr);
        } else {
            float* reg = GetSegment(segment);
            if (interrupt_flag) return nullptr;
            return ReadCell(*reg, addr);
        }
    }

    int_vm(ERR_PROCESSOR_FAULT);
    return nullptr;
}


float* VM::GetRegister(int32_t index) {
    switch(index) {
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
        default: 
            int_vm(ERR_PROCESSOR_FAULT);
            return nullptr;
    }
}

float* VM::GetSegment(int32_t index) {
    switch(index) {
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
        default:
            if (index >= 17 && index <= 47) {
                return &R[index - 17];
            }

            int_vm(ERR_PROCESSOR_FAULT);
            return nullptr;
    }
}

void VM::step() {
    if(interrupt_flag) return;
    
    int32_t opcode = fetch();
    if(interrupt_flag) return;

    //bool isFixedSize = false;
    if((opcode >= 2000 && opcode < 4000) || (opcode >= 12000 && opcode < 14000)) {
        opcode -= 2000;
        //isFixedSize = true;
    }

    if (opcode >= 0 || opcode < (sizeof(instructions) / sizeof(Instruction))) {
        if(!instructions[opcode].operand_count && instructions[opcode].execute != NULL) {
            static float blank;
            blank = 0;
            instructions[opcode].execute(this, &blank, &blank);
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

    if (opcode < 0 || opcode >= (sizeof(instructions) / sizeof(Instruction)) || !instructions[opcode].execute) {
        int_vm(ERR_UNKNOWN_OPCODE);
    } else {
        if(instructions[opcode].operand_count == 1) {
            static float blank;
            
            float* op1 = GetOperand(rm1, segment1);
            if(interrupt_flag) return;

            blank = 0;
            instructions[opcode].execute(this, op1, &blank);
        } else {
            float* op1 = GetOperand(rm1, segment1);
            if(interrupt_flag) return;

            float* op2 = GetOperand(rm2, segment2);
            if(interrupt_flag) return;

            instructions[opcode].execute(this, op1, op2);
        }

    }
}

void VM::VM() {
    int i;
    for (i = 0; i < MEMORY_MODEL; i++) Memory[i] = 0;
    for (i = 0; i < 32; i++) R[i] = 0;
    IP = CMPR = interrupt_flag = interrupt_skip = extended_flag = cli_flag = 0;
    EAX = EBX = ECX = EDX = ESI = EDI = 0;
    ESP = MEMORY_MODEL-1;
    EBP = 0;
    CS = SS = DS = ES = GS = FS = KS = LS = 0;
    PTBL = PTBE = 0;
    immediate_swap = 0;
}

void out_printf(char* str, ...) {
    static char buffer[2048];
    va_list args;

    va_start(args, str);
    vsprintf(buffer, str, args);
    va_end(args);

    int i = 0;
    int output;

    while (buffer[i]) {
        if (buffer[i] == '\n') {
            int cursor_x = (print_ptr - screen_ptr) % 80;
            int remaining = 80 - ((cursor_x + i) % 80);

            print_ptr += remaining - 1;
        } else {
            output = 0x0D00 | buffer[i];
            print_ptr[i] = output;
        }

        i++;
    }

    print_ptr += i;
}

void emit_error(char* str, ...) {
    int offset = print_ptr - screen_ptr;
    va_list args;

    printf("\033[%d;%dH", offset / 80, offset % 80);
    va_start(args, str);
    vprintf(str, args);
    va_end(args);
}

#ifdef DEBUG_MODE
    #if DEBUG_MODE == 1
        void debug_print(int* ptr, float n) {
            static char str[128];
            sprintf(str, "%f  ", n);

            int i = 0;
            int output;
            while(str[i]) {
                output = 0x0F00 | str[i];
                ptr[i] = output;
                i++;
            }
        }

        void debug_print_register(int** ptr, int** ptr_2, char* str) {
            int i = 0;
            int output;
            int* real_ptr = *ptr;

            while (str[i]) {
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
    VM vm;

    srand(time(NULL));

    char* filename = argv[1];
    if(!filename) {
        printf("You need to provide the filename as an argument.");
        return 1;
    }

    FILE* script = fopen(filename, "r");
    if(!script) {
        printf("Couldn't open the file.");
        return 1;
    }

    int32_t count = 0;

    while (!feof(script)) {
        float value;

        if (fscanf(script, "%f,", &value) == 1) {
            if (count >= MEMORY_MODEL) {
                break;
            }

            vm.Memory[count++] = value;
        }
    }

    fclose(script);

    asm {
        PUSHA
        MOV AH, 7
        XOR AL, AL
        XOR CX, CX
        MOV BX, 0x0700
        MOV DH, 25
        MOV DL, 80
        INT 010h
        POPA
    }

    out_printf("Loaded bytecode (%ld values):\n", count);
    for (size_t i = 0; i < count; i++) {
        //out_printf("%f ", vm.Memory[i]);
    }
    out_printf("\n");

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
                if(argv[2] != nullptr) {
                    breakPoint = atoi(argv[2]);
                } else {
                    breakPoint = -1;
                }
            #endif
    #endif

    out_printf("Executing bytecode...\n");

    while(1) {
        vm.step();

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

                if(vm.IP == breakPoint) {
                    emit_error("\nBreakpoint reached...");
                    return 0;
                }
            #endif
        #endif

        if(vm.interrupt_flag) {
            if(vm.interrupt_skip) {
                vm.interrupt_skip = 0;
                vm.interrupt_flag = 0;
            } else {
                break;
            }
        }

        if(kbhit()) {
            if(getch() == 3) {
                emit_error("\nProgram exited by user...");
                return 0;
            }
        }
    }

    emit_error("\nError: %d, IP: %ld", vm.interrupt_flag, vm.IP);
    return 0;
}