void END(VM* vm, float* op1, float* op2) {
    vm->int_vm(ERR_END_EXECUTION, vm->IP);
}

void CPUID(VM* vm, float* op1, float* op2) {
}

void ADD(VM* vm, float* op1, float* op2) {
    *op1 += *op2;
}

void SUB(VM* vm, float* op1, float* op2) {
    *op1 -= *op2;
}

void MUL(VM* vm, float* op1, float* op2) {
    *op1 *= *op2;
}

void DIV(VM* vm, float* op1, float* op2) {
    *op1 /= *op2;
}

void MOV(VM* vm, float* op1, float* op2) {
    *op1 = *op2;
}

void MIN(VM* vm, float* op1, float* op2) {
    *op1 = (*op1 < *op2) ? *op1 : *op2;
}

void MAX(VM* vm, float* op1, float* op2) {
    *op1 = (*op1 > *op2) ? *op1 : *op2;
}

void INC(VM* vm, float* op1, float* op2) {
    (*op1)++;
}

void DEC(VM* vm, float* op1, float* op2) {
    (*op1)--;
}

void NEG(VM* vm, float* op1, float* op2) {
    *op1 = -*op1;
}

void RAND(VM* vm, float* op1, float* op2) {
    *op1 = rand();
}

void IDLE(VM* vm, float* op1, float* op2) {
    
}

void NOP(VM* vm, float* op1, float* op2) {
    
}

void LNEG(VM* vm, float* op1, float* op2) {
    *op1 = !*op1;
}

void AND(VM* vm, float* op1, float* op2) {
    *op1 = *op1 && *op2;
}

void OR(VM* vm, float* op1, float* op2) {
    *op1 = *op1 || *op2;
}

void XOR(VM* vm, float* op1, float* op2) {
    *op1 = (float)((int32_t)(*op1) ^ (int32_t)(*op2));
}

void INT(VM* vm, float* op1, float* op2) {
    vm->int_vm(*op1, 0);
}

void STI(VM* vm, float* op1, float* op2) {
    vm->cli_flag = 0;
}

void CLI(VM* vm, float* op1, float* op2) {
    vm->cli_flag = 1;
}

void XCHG(VM* vm, float* op1, float* op2) {
    float cache = *op1;
    *op1 = *op2;
    *op2 = cache;
}

void IN(VM* vm, float* op1, float* op2) {
    *op1 = inportb(*op2);
}

void OUT(VM* vm, float* op1, float* op2) {
    outportb(*op1, *op2);
}

void TIMER(VM* vm, float* op1, float* op2) {
    clock_t now = clock();
    
    *op1 = (now - vm->creation_time) / CLK_TCK;
}

void CPUGET(VM* vm, float* op1, float* op2) {
    if(vm->current_page.bits.runlevel) {
        if(vm->PreqHandled == 1) {
            *op1 = vm->PreqReturn;
            vm->PreqReturn = 0;
            vm->PreqHandled = 0;
        } else if(vm->PreqHandled == 0) {
            vm->PrivilegeRequest(op1, op2, 128);
        } else {
            vm->PreqHandled = 0;
        }
    } else {
        *op1 = vm->GetInternalRegister(*op2);
    }
}

void CPUSET(VM* vm, float* op1, float* op2) {
    vm->SetInternalRegister(*op1, *op2);
}

void LEA(VM* vm, float* op1, float* op2) {
    int32_t address = op2 - vm->Memory;
    if(address < 0 || address >= MEMORY_MODEL) {
        vm->int_vm(ERR_PROCESSOR_FAULT, 0);
        return;
    }

    *op1 = address;
}

void BLOCK(VM* vm, float* op1, float* op2) {
    vm->BLOCKSTART = *op1;
    vm->BLOCKSIZE = *op2;
}

void STERR(VM* vm, float* op1, float* op2) {
    
}

void CLERR(VM* vm, float* op1, float* op2) {
    
}

void QUOCMP(VM* vm, float* op1, float* op2) {
    
}

void QUOTIMER(VM* vm, float* op1, float* op2) {
    
}

void MSHIFT(VM* vm, float* op1, float* op2) {
    
}

void MCOPY(VM* vm, float* op1, float* op2) {
    float* v;

    for (int32_t i = 0; i < *op1; i++) {
        v = vm->ReadCell(i + (int32_t)vm->ESI);
        if (vm->interrupt_flag) return;

        vm->WriteCell(i + (int32_t)vm->EDI, *v);
        if (vm->interrupt_flag) return;

    }
}

void MXCHG(VM* vm, float* op1, float* op2) {
    float* esi_cache;
    float* edi_cache;
    
    for (int32_t i = 0; i < *op1; i++) {
        esi_cache = vm->ReadCell((int32_t)vm->ESI);
        if (vm->interrupt_flag) return;

        edi_cache = vm->ReadCell((int32_t)vm->EDI);
        if (vm->interrupt_flag) return;

        vm->WriteCell((int32_t)vm->ESI, *edi_cache);
        if (vm->interrupt_flag) return;

        vm->WriteCell((int32_t)vm->EDI, *esi_cache);
        if (vm->interrupt_flag) return;

        vm->ESI++;
        vm->EDI++;
    }
}