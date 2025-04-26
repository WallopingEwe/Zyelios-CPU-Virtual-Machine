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

void JG(VM* vm, float* op1, float* op2) {
    if (vm->CMPR > 0) {
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