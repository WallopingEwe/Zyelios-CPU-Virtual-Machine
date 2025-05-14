void CMP(VM* vm, float* op1, float* op2) {
    vm->CMPR = *op1 - *op2;
}

void CMPAND(VM* vm, float* op1, float* op2) {
    if (vm->CMPR != 0) {
        vm->CMPR = *op1 - *op2;
    }
}

void CMPOR(VM* vm, float* op1, float* op2) {
    if (vm->CMPR == 0) {
        vm->CMPR = *op1 - *op2;
    }
}

void JNE(VM* vm, float* op1, float* op2) {
    if (vm->CMPR != 0) {
        vm->JMP(*op1);
    }
}

void JMP(VM* vm, float* op1, float* op2) {
    vm->JMP(*op1);
}

void JMPR(VM* vm, float* op1, float* op2) {
    vm->JMP(vm->IP + *op1);
}

void JUMPF(VM* vm, float* op1, float* op2) {
    vm->JMP(*op1, *op2);
}

void CALL(VM* vm, float* op1, float* op2) {
    vm->CALL(*op1);
}

void CALLF(VM* vm, float* op1, float* op2) {
    vm->CALL(*op1, *op2);
}

void RET(VM* vm, float* op1, float* op2) {
    float ip = vm->Pop();
    if (vm->interrupt_flag) return;

    vm->JMP(ip);
}

void RETF(VM* vm, float* op1, float* op2) {
    float ip = vm->Pop();
    if (vm->interrupt_flag) return;

    float cs = vm->Pop();
    if (vm->interrupt_flag) return;

    vm->JMP(ip, cs);
}

void EXTRETA(VM* vm, float* op1, float* op2) {
    
}

void JG(VM* vm, float* op1, float* op2) {
    if (vm->CMPR > 0) {
        vm->JMP(*op1);
    }
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

void JGE(VM* vm, float* op1, float* op2) {
    if (vm->CMPR >= 0) {
        vm->JMP(*op1);
    }
}

void JL(VM* vm, float* op1, float* op2) {
    if (vm->CMPR < 0) {
        vm->JMP(*op1);
    }
}

void JLE(VM* vm, float* op1, float* op2) {
    if (vm->CMPR <= 0) {
        vm->JMP(*op1);
    }
}

void JE(VM* vm, float* op1, float* op2) {
    if (vm->CMPR == 0) {
        vm->JMP(*op1);
    }
}

void CNE(VM* vm, float* op1, float* op2) {
    if (vm->CMPR != 0) {
        vm->CALL(*op1);
    }
}

void CG(VM* vm, float* op1, float* op2) {
    if (vm->CMPR > 0) {
        vm->CALL(*op1);
    }
}

void CGE(VM* vm, float* op1, float* op2) {
    if (vm->CMPR >= 0) {
        vm->CALL(*op1);
    }
}

void CL(VM* vm, float* op1, float* op2) {
    if (vm->CMPR < 0) {
        vm->CALL(*op1);
    }
}

void CLE(VM* vm, float* op1, float* op2) {
    if (vm->CMPR <= 0) {
        vm->CALL(*op1);
    }
}

void CE(VM* vm, float* op1, float* op2) {
    if (vm->CMPR == 0) {
        vm->CALL(*op1);
    }
}

void JNER(VM* vm, float* op1, float* op2) {
    if (vm->CMPR != 0) {
        vm->CALL(*op1, vm->IP);
    }
}

void JGR(VM* vm, float* op1, float* op2) {
    if (vm->CMPR > 0) {
        vm->CALL(*op1, vm->IP);
    }
}

void JGER(VM* vm, float* op1, float* op2) {
    if (vm->CMPR >= 0) {
        vm->CALL(*op1, vm->IP);
    }
}

void JLR(VM* vm, float* op1, float* op2) {
    if (vm->CMPR < 0) {
        vm->CALL(*op1, vm->IP);
    }
}

void JLER(VM* vm, float* op1, float* op2) {
    if (vm->CMPR <= 0) {
        vm->CALL(*op1, vm->IP);
    }
}

void JER(VM* vm, float* op1, float* op2) {
    if (vm->CMPR == 0) {
        vm->CALL(*op1, vm->IP);
    }
}