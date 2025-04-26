void BIT(VM* vm, float* op1, float* op2) {
    vm->CMPR = ((int32_t)(*op1) >> (int32_t)(*op2)) & 1;
}

void SBIT(VM* vm, float* op1, float* op2) {
    *op1 = (float)((int32_t)(*op1) | (1 << (int32_t)(*op2)));
}

void CBIT(VM* vm, float* op1, float* op2) {
    *op1 = (float)((int32_t)(*op1) & ~(1 << (int32_t)(*op2)));
}

void TBIT(VM* vm, float* op1, float* op2) {
    if (((int32_t)(*op1) >> (int32_t)(*op2)) & 1) {
        *op1 = (float)((int32_t)(*op1) & ~(1 << (int32_t)(*op2)));
    } else {
        *op1 = (float)((int32_t)(*op1) | (1 << (int32_t)(*op2)));
    }
}

void BAND(VM* vm, float* op1, float* op2) {
    *op1 = (float)((int32_t)(*op1) & (int32_t)(*op2));
}

void BOR(VM* vm, float* op1, float* op2) {
    *op1 = (float)((int32_t)(*op1) | (int32_t)(*op2));
}

void BSHL(VM* vm, float* op1, float* op2) {
    *op1 = (float)((int32_t)(*op1) << (int32_t)(*op2));
}

void BSHR(VM* vm, float* op1, float* op2) {
    *op1 = (float)((int32_t)(*op1) >> (int32_t)(*op2));
}

void BNOT(VM* vm, float* op1, float* op2) {
    *op1 = (float)(~(int32_t)(*op1));
}