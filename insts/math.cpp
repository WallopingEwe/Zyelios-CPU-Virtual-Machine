void FLOG(VM* vm, float* op1, float* op2) {
    *op1 = log(*op2);
}

void FLOG10(VM* vm, float* op1, float* op2) {
    *op1 = log10(*op2);
}

void FABS(VM* vm, float* op1, float* op2) {
    *op1 = fabs(*op2);
}

void FSGN(VM* vm, float* op1, float* op2) {
    if (*op2 < 0) {
        *op1 = -1;
    } else if (*op2 > 0) {
        *op1 = 1;
    } else {
        *op1 = 0;
    }
}

void FPWR(VM* vm, float* op1, float* op2) {
    *op1 = pow(*op1, *op2);
}

void FEXP(VM* vm, float* op1, float* op2) {
    *op1 = exp(*op2);
}

void FPI(VM* vm, float* op1, float* op2) {
    *op1 = M_PI;
}

void FE(VM* vm, float* op1, float* op2) {
    *op1 = M_E;
}

void FCEIL(VM* vm, float* op1, float* op2) {
    *op1 = ceil(*op1);
}

void FSIN(VM* vm, float* op1, float* op2) {
    *op1 = sin(*op2);
}

void FCOS(VM* vm, float* op1, float* op2) {
    *op1 = cos(*op2);
}

void FTAN(VM* vm, float* op1, float* op2) {
    *op1 = tan(*op2);
}

void FASIN(VM* vm, float* op1, float* op2) {
    *op1 = asin(*op2);
}

void FACOS(VM* vm, float* op1, float* op2) {
    *op1 = acos(*op2);
}

void FATAN(VM* vm, float* op1, float* op2) {
    *op1 = atan(*op2);
}

void MOD(VM* vm, float* op1, float* op2) {
    *op1 = *op1 - *op2 * floor(*op1 / *op2);
}

void FINT(VM* vm, float* op1, float* op2) {
    *op1 = floor(*op1);
}

void RND(VM* vm, float* op1, float* op2) {
    *op1 = floor(*op1 + 0.5);
}

void FFRAC(VM* vm, float* op1, float* op2) {
    double integer;

    *op1 = modf(*op1, &integer);
}

void FINV(VM* vm, float* op1, float* op2) {
    *op1 = 1 / *op1;
}

void FSHL(VM* vm, float* op1, float* op2) {
    *op1 *= 2;
}

void FSHR(VM* vm, float* op1, float* op2) {
    *op1 /= 2;
}