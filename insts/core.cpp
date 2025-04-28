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

void LOOP(VM* vm, float* op1, float* op2) {
    vm->ECX--;
    if (vm->ECX) {
        vm->JMP(*op1);
    }
}

void LOOPA(VM* vm, float* op1, float* op2) {
    vm->EAX--;
    if (vm->EAX) {
        vm->JMP(*op1);
    }
}

void LOOPB(VM* vm, float* op1, float* op2) {
    vm->EBX--;
    if (vm->EBX) {
        vm->JMP(*op1);
    }
}

void LOOPD(VM* vm, float* op1, float* op2) {
    vm->EDX--;
    if (vm->EDX) {
        vm->JMP(*op1);
    }
}

void IDLE(VM* vm, float* op1, float* op2) {
    
}

void NOP(VM* vm, float* op1, float* op2) {
    
}

void JMPR(VM* vm, float* op1, float* op2) {
    vm->JMP(vm->IP + *op1);
}

void LNEG(VM* vm, float* op1, float* op2) {
    *op1 = !*op1;
}

void RETF(VM* vm, float* op1, float* op2) {
    float ip = vm->Pop();
    if (vm->interrupt_flag) return;

    float cs = vm->Pop();
    if (vm->interrupt_flag) return;

    vm->JMP(ip, cs);
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

void JUMPF(VM* vm, float* op1, float* op2) {
    vm->JMP(*op1, *op2);
}

void CALL(VM* vm, float* op1, float* op2) {
    vm->CALL(*op1);
}

void RET(VM* vm, float* op1, float* op2) {
    float ip = vm->Pop();
    if (vm->interrupt_flag) return;

    vm->JMP(ip);
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

void CALLF(VM* vm, float* op1, float* op2) {
    vm->CALL(*op1, *op2);
}

void TIMER(VM* vm, float* op1, float* op2) {
    clock_t now = clock();
    
    *op1 = (now - vm->creation_time) / CLK_TCK;
}

void CPUGET(VM* vm, float* op1, float* op2) {
    *op1 = vm->GetInternalRegister(*op2);
}

void CPUSET(VM* vm, float* op1, float* op2) {
    vm->SetInternalRegister(*op1, *op2);
}

void LEA(VM* vm, float* op1, float* op2) {
    
}

void BLOCK(VM* vm, float* op1, float* op2) {
    
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