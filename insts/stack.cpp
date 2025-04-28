void PUSH(VM* vm, float* op1, float* op2) {
    vm->Push(*op1);
}

void POP(VM* vm, float* op1, float* op2) {
    *op1 = vm->Pop();
}

void PUSHA(VM* vm, float* op1, float* op2) {
    vm->Push(vm->EDI);
    if (vm->interrupt_flag) return;
    vm->Push(vm->ESI);
    if (vm->interrupt_flag) return;
    vm->Push(vm->EBP);
    if (vm->interrupt_flag) return;
    vm->Push(vm->ESP);
    if (vm->interrupt_flag) return;
    vm->Push(vm->EDX);
    if (vm->interrupt_flag) return;
    vm->Push(vm->ECX);
    if (vm->interrupt_flag) return;
    vm->Push(vm->EBX);
    if (vm->interrupt_flag) return;
    vm->Push(vm->EAX);
}

void POPA(VM* vm, float* op1, float* op2) {
    vm->EAX = vm->Pop();
    if (vm->interrupt_flag) return;
    vm->EBX = vm->Pop();
    if (vm->interrupt_flag) return;
    vm->ECX = vm->Pop();
    if (vm->interrupt_flag) return;
    vm->EDX = vm->Pop();
    if (vm->interrupt_flag) return;
    vm->Pop(); // ESP
    if (vm->interrupt_flag) return;
    vm->EBP = vm->Pop();
    if (vm->interrupt_flag) return;
    vm->ESI = vm->Pop();
    if (vm->interrupt_flag) return;     
    vm->EDI = vm->Pop();
}

void RSTACK(VM* vm, float* op1, float* op2) {
    if (*op2 < 0 || *op2 >= MEMORY_MODEL) {
        vm->int_vm(ERR_STACK_ERROR, *op2);
        return;
    }

    float* val = vm->ReadCell(vm->SS + *op2);
    if (vm->interrupt_flag) return;

    *op1 = *val;
}

void SSTACK(VM* vm, float* op1, float* op2) {
    if (*op1 < 0 || *op1 >= MEMORY_MODEL) {
        vm->int_vm(ERR_STACK_ERROR, *op1);
        return;
    }
    
    vm->WriteCell(vm->SS + *op1, *op2);
}

void ENTER(VM* vm, float* op1, float* op2) {
    vm->Push(vm->EBP);
    vm->EBP = vm->ESP + 1;
    vm->ESP = vm->ESP - *op1;
}

void LEAVE(VM* vm, float* op1, float* op2) {
    vm->ESP = vm->EBP - 1;
    vm->EBP = vm->Pop();
}