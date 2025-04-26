void LIDTR(VM* vm, float* op1, float* op2) {
    vm->IDTR = *op1;
}

void EXTRET(VM* vm, float* op1, float* op2) {
    
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
    
}

void STD2(VM* vm, float* op1, float* op2) {
    
}