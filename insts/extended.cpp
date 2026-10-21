void LIDTR(VM* vm, float* op1, float* op2) {
    vm->IDTR = *op1;
}

void EXTRET(VM* vm, float* op1, float* op2) {
    vm->Pop(); if(vm->interrupt_flag) return; // IRET CS
    vm->Pop(); if(vm->interrupt_flag) return; // IRET EIP

    int32_t ip = vm->Pop(); if(vm->interrupt_flag) return;
    vm->CMPR = vm->Pop(); if(vm->interrupt_flag) return;

    vm->EAX = vm->Pop(); if(vm->interrupt_flag) return;
    vm->EBX = vm->Pop(); if(vm->interrupt_flag) return;
    vm->ECX = vm->Pop(); if(vm->interrupt_flag) return;
    vm->EDX = vm->Pop(); if(vm->interrupt_flag) return;
    vm->EBP = vm->Pop(); if(vm->interrupt_flag) return;
    vm->Pop(); if(vm->interrupt_flag) return; // ESP
    vm->ESI = vm->Pop(); if(vm->interrupt_flag) return;
    vm->EDI = vm->Pop(); if(vm->interrupt_flag) return;

    int32_t cs = vm->Pop(); if(vm->interrupt_flag) return;

    vm->Pop(); if(vm->interrupt_flag) return; // SS
    vm->DS = vm->Pop(); if(vm->interrupt_flag) return;
    vm->FS = vm->Pop(); if(vm->interrupt_flag) return;
    vm->GS = vm->Pop(); if(vm->interrupt_flag) return;
    vm->ES = vm->Pop(); if(vm->interrupt_flag) return;
    vm->KS = vm->Pop(); if(vm->interrupt_flag) return;
    vm->LS = vm->Pop(); if(vm->interrupt_flag) return;

    vm->JMP(ip, cs);
}


void STEF(VM* vm, float* op1, float* op2) {
    vm->extended_flag = 1;
}

void CLEF(VM* vm, float* op1, float* op2) {
    vm->extended_flag = 0;
}

void IRET(VM* vm, float* op1, float* op2) {
    int32_t cs = vm->Pop();
    if(vm->interrupt_flag) return;

    int32_t ip = vm->Pop();
    if(vm->interrupt_flag) return;
    
    vm->JMP(ip, cs);
}

void EXTINT(VM* vm, float* op1, float* op2) {
    vm->extint_vm(*op1, 0);
}

void STD2(VM* vm, float* op1, float* op2) {
    
}