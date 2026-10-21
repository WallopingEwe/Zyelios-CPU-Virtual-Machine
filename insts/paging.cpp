void CLM(VM* vm, float* op1, float* op2) {
    vm->extended_memory_flag = 0;
}

void SMAP(VM* vm, float* op1, float* op2) {
    Page page;  
    int32_t map;

    int32_t addr;
    int32_t last;
    if(vm->BLOCKSIZE) {
        addr = vm->BLOCKSTART;
        last = addr + vm->BLOCKSIZE;
        vm->BLOCKSIZE = 0;
    } else {
        addr = *op1 * 128;
        last = addr + 127;
    }

    int32_t index;
    while(addr < last) {
        index = addr / 128;
        vm->GetPage(index, &page, &map);
        if(vm->interrupt_flag) return;

        if(vm->current_page.bits.runlevel <= page.bits.runlevel) {
            page.bits.remapped = 1;
            vm->SetPage(index, page.raw, *op2);
            if(vm->interrupt_flag) return;
        } else {
            vm->int_vm(ERR_PAGE_VIOLATION, index, 0, 0);
            return;
        }

        addr += 128;
    }
}

void GMAP(VM* vm, float* op1, float* op2) {
    if(vm->current_page.bits.runlevel) {
        if(vm->PreqHandled == 1) {
            *op1 = vm->PreqReturn;
            vm->PreqReturn = 0;
            vm->PreqHandled = 0;
        } else if(vm->PreqHandled == 0) {
            vm->PrivilegeRequest(op1, op2, 132);
        } else {
            vm->PreqHandled = 0;
        }
    } else {
        Page page;
        int32_t map;

        vm->GetPage(*op2 / 128, &page, &map);
        if(vm->interrupt_flag) return;
        
        *op1 = map;
    }
}

void IRETP(VM* vm, float* op1, float* op2) {
    vm->PTBL = *op1;

    int32_t cs = vm->Pop();
    if(vm->interrupt_flag) return;

    int32_t ip = vm->Pop();
    if(vm->interrupt_flag) return;
    
    vm->JMP(ip, cs);
}

void EXTRETP(VM* vm, float* op1, float* op2) {
    vm->PTBL = *op1;

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

void EXTRETPA(VM* vm, float* op1, float* op2) {
    vm->PTBL = *op1;

    vm->Pop(); if(vm->interrupt_flag) return; // IRET CS
    vm->Pop(); if(vm->interrupt_flag) return; // IRET EIP

    for(char i = 0; i < 32; i++) {
        vm->R[i] = vm->Pop();
        if(vm->interrupt_flag) return;
    }

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

void STM(VM* vm, float* op1, float* op2) {
    vm->extended_memory_flag = 1;
}

void SPG(VM* vm, float* op1, float* op2) {
    Page page;
    int32_t map;
    int32_t index = *op1 / 128;
    vm->GetPage(index, &page, &map);
    if(vm->interrupt_flag) return;

    if(vm->current_page.bits.runlevel <= page.bits.runlevel) {
        page.bits.read = 1;
        page.bits.write = 0;
        vm->SetPage(index, page.raw, map);
    } else {
        vm->int_vm(ERR_PAGE_VIOLATION, index, 0, 0);
    }
}

void CPG(VM* vm, float* op1, float* op2) {
    Page page;
    int32_t map;
    int32_t index = *op1 / 128;
    vm->GetPage(index, &page, &map);
    if(vm->interrupt_flag) return;

    if(vm->current_page.bits.runlevel <= page.bits.runlevel) {
        page.bits.read = 1;
        page.bits.write = 1;
        vm->SetPage(index, page.raw, map);
    } else {
        vm->int_vm(ERR_PAGE_VIOLATION, index, 0, 0);
    }
}

void TPG(VM* vm, float* op1, float* op2) {
    
}

void ERPG(VM* vm, float* op1, float* op2) {
    
}

void WRPG(VM* vm, float* op1, float* op2) {
    
}

void RDPG(VM* vm, float* op1, float* op2) {
    
}

void SPP(VM* vm, float* op1, float* op2) {
    Page page;  
    int32_t map;

    int32_t addr;
    int32_t last;
    if(vm->BLOCKSIZE) {
        addr = vm->BLOCKSTART;
        last = addr + vm->BLOCKSIZE;
        vm->BLOCKSIZE = 0;
    } else {
        addr = *op1 * 128;
        last = addr + 127;
    }

    int32_t index;
    while(addr < last) {
        index = addr / 128;
        vm->GetPage(index, &page, &map);
        if(vm->interrupt_flag) return;

        if(vm->current_page.bits.runlevel <= page.bits.runlevel) {
            switch((int)*op2) {
                case 0: {
                    page.bits.read = 1;
                    break;
                }
                case 1: {
                    page.bits.write = 1;
                    break;

                }
                case 2: {
                    page.bits.execute = 1;
                    break;

                }
                case 3: {
                    page.bits.runlevel = 1;
                    break;
                }
            }

            vm->SetPage(index, page.raw, map);
            if(vm->interrupt_flag) return;
        } else {
            vm->int_vm(ERR_PAGE_VIOLATION, index, 0, 0);
            return;
        }

        addr += 128;
    }
}

void CPP(VM* vm, float* op1, float* op2) {
    Page page;  
    int32_t map;

    int32_t addr;
    int32_t last;
    if(vm->BLOCKSIZE) {
        addr = vm->BLOCKSTART;
        last = addr + vm->BLOCKSIZE;
        vm->BLOCKSIZE = 0;
    } else {
        addr = *op1 * 128;
        last = addr + 127;
    }

    int32_t index;
    while(addr < last) {
        index = addr / 128;
        vm->GetPage(index, &page, &map);
        if(vm->interrupt_flag) return;

        if(vm->current_page.bits.runlevel <= page.bits.runlevel) {
            switch((int)*op2) {
                case 0: {
                    page.bits.read = 0;
                    break;
                }
                case 1: {
                    page.bits.write = 0;
                    break;

                }
                case 2: {
                    page.bits.execute = 0;
                    break;

                }
                case 3: {
                    page.bits.runlevel = 0;
                    break;
                }
            }

            vm->SetPage(index, page.raw, map);
            if(vm->interrupt_flag) return;
        } else {
            vm->int_vm(ERR_PAGE_VIOLATION, index, 0, 0);
            return;
        }

        addr += 128;
    }
}

void SRL(VM* vm, float* op1, float* op2) {
    Page page;  
    int32_t map;

    int32_t addr;
    int32_t last;
    if(vm->BLOCKSIZE) {
        addr = vm->BLOCKSTART;
        last = addr + vm->BLOCKSIZE;
        vm->BLOCKSIZE = 0;
    } else {
        addr = *op1 * 128;
        last = addr + 127;
    }

    int32_t index;
    while(addr < last) {
        index = addr / 128;
        vm->GetPage(index, &page, &map);
        if(vm->interrupt_flag) return;

        if(vm->current_page.bits.runlevel <= page.bits.runlevel) {
            page.bits.runlevel = *op2;
            vm->SetPage(index, page.raw, map);
            if(vm->interrupt_flag) return;
        } else {
            vm->int_vm(ERR_PAGE_VIOLATION, index, 0, 0);
            return;
        }

        addr += 128;
    }
}

void CRL(VM* vm, float* op1, float* op2) {
    Page page;
    int32_t map;

    vm->GetPage(*op2 / 128, &page, &map);
    if(vm->interrupt_flag) return;

    *op1 = page.bits.runlevel;
}