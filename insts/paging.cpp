void CLM(VM* vm, float* op1, float* op2) {
    vm->extended_memory_flag = 0;
}

void SMAP(VM* vm, float* op1, float* op2) {
    Page page;  
    int32_t map;

    Page curPage;
    int32_t curMap;
    vm->GetPage(vm->IP / 128, &curPage, &curMap);
    if(vm->interrupt_flag) return;

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

        if(curPage.bits.runlevel <= page.bits.runlevel) {
            page.bits.remapped = 1;
            vm->SetPage(index, page.raw, *op2);
            if(vm->interrupt_flag) return;
        } else {
            vm->int_vm(ERR_PAGE_VIOLATION, index);
            return;
        }

        addr += 128;
    }
}

void GMAP(VM* vm, float* op1, float* op2) {
    Page curPage;
    int32_t curMap;
    vm->GetPage(vm->IP / 128, &curPage, &curMap);
    if(vm->interrupt_flag) return;

    if(curPage.bits.runlevel) {
        if(vm->PreqHandled == 1) {
            *op1 = vm->PreqReturn;
            vm->PreqReturn = 0;
            vm->PreqHandled = 0;
        } else if(vm->PreqHandled == 0) {
            vm->PreqOperand1 = *op1;
            vm->PreqOperand2 = *op2;
            vm->PreqReturn = 0;
            vm->PreqHandled = -1;

            vm->int_vm(ERR_PROCESSOR_FAULT, 132);
        } else {
            vm->PreqHandled = 0;
        }
    } else {
        vm->GetPage(*op2 / 128, &curPage, &curMap);
        if(vm->interrupt_flag) return;
        
        *op1 = curMap;
    }
}

void IRETP(VM* vm, float* op1, float* op2) {
    int32_t cs = vm->Pop();
    if(vm->interrupt_flag) return;

    int32_t ip = vm->Pop();
    if(vm->interrupt_flag) return;
    
    PTBL = *op1;
    vm->JMP(ip, cs);
}

void EXTRETP(VM* vm, float* op1, float* op2) {
    
}

void EXTRETPA(VM* vm, float* op1, float* op2) {
    
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

    Page curPage;
    int32_t curMap;
    vm->GetPage(vm->IP / 128, &curPage, &curMap);
    if(vm->interrupt_flag) return;

    if(curPage.bits.runlevel <= page.bits.runlevel) {
        page.bits.read = 1;
        page.bits.write = 0;
        vm->SetPage(index, page.raw, map);
    } else {
        vm->int_vm(ERR_PAGE_VIOLATION, index);
    }
}

void CPG(VM* vm, float* op1, float* op2) {
    Page page;
    int32_t map;
    int32_t index = *op1 / 128;
    vm->GetPage(index, &page, &map);
    if(vm->interrupt_flag) return;

    Page curPage;
    int32_t curMap;
    vm->GetPage(vm->IP / 128, &curPage, &curMap);
    if(vm->interrupt_flag) return;

    if(curPage.bits.runlevel <= page.bits.runlevel) {
        page.bits.read = 1;
        page.bits.write = 1;
        vm->SetPage(index, page.raw, map);
    } else {
        vm->int_vm(ERR_PAGE_VIOLATION, index);
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

    Page curPage;
    int32_t curMap;
    vm->GetPage(vm->IP / 128, &curPage, &curMap);
    if(vm->interrupt_flag) return;

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

        if(curPage.bits.runlevel <= page.bits.runlevel) {
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
            vm->int_vm(ERR_PAGE_VIOLATION, index);
            return;
        }

        addr += 128;
    }
}

void CPP(VM* vm, float* op1, float* op2) {
    Page page;  
    int32_t map;

    Page curPage;
    int32_t curMap;
    vm->GetPage(vm->IP / 128, &curPage, &curMap);
    if(vm->interrupt_flag) return;

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

        if(curPage.bits.runlevel <= page.bits.runlevel) {
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
            vm->int_vm(ERR_PAGE_VIOLATION, index);
            return;
        }

        addr += 128;
    }
}

void SRL(VM* vm, float* op1, float* op2) {
    Page page;  
    int32_t map;

    Page curPage;
    int32_t curMap;
    vm->GetPage(vm->IP / 128, &curPage, &curMap);
    if(vm->interrupt_flag) return;

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

        if(curPage.bits.runlevel <= page.bits.runlevel) {
            page.bits.runlevel = *op2;
            vm->SetPage(index, page.raw, map);
            if(vm->interrupt_flag) return;
        } else {
            vm->int_vm(ERR_PAGE_VIOLATION, index);
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