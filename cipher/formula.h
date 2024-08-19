#pragma once
#include "types.h"

#define HIHEX(x) (x>>4)
#define LOWHEX(x) (x&0x0F)
#define BTOW(b0,b1,b2,b3) (((WORD)b0 <<24)|((WORD)b1 << 16)|((WORD)b2<<8)|((WORD)b3))

BYTE GFMultiple(BYTE b, BYTE n);
WORD RotateWord(WORD wordValue);
WORD SubWord(WORD wordValue);