#include "bankSwitch.h"


size_t getRBankByPkId(size_t pkId, bool y_mode){
    if(!y_mode && pkId == 0x15){
        return 0x01;
    }
    if(pkId == 0xB6){
        return 0x0B;
    }

    if(pkId < 0x1F){
        return 0x09;
    }
    if(pkId < 0x4A){
        return 0x0A;
    }
    if(pkId < 0x74){
        return 0x0B;
    }
    if(pkId < 0x99){
        return 0x0C;
    }
    return 0x0D;
}

