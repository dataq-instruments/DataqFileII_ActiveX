#pragma pack(push,before_di2s32,2)
#include "hdrdef32.h"

typedef struct tagCODASHDR29
{
   unsigned short header[2];
   struct hdrcmn hdrc;
   struct chinfo cary[29];
   unsigned short vbflags;
} CODASHDR29;

typedef struct tagCODASHDR254
{
   unsigned short header[2];
   struct hdrcmn hdrc;
   struct chinfo cary[254];
   unsigned short vbflags;
} CODASHDR254;

typedef struct tagCODASHDRCirc
{
   unsigned short header[2];
   struct hdrcmn hdrc;
   struct chinfo cary[29];
   char padding[1536-sizeof(short)*2-sizeof(hdrcmn)-sizeof(chinfo)*29];
   unsigned short vbflags;
} CODASHDRCIRC;

#pragma pack(pop,before_di2s32)
