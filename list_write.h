#ifndef _list_write_h
#define _list_write_h 1
#include "structs.h"

NODE * listInsert(LIST *, double);
NODE * listAppend(LIST *, double);
NODE * listDelete(LIST *, double);
void   listRelease(LIST *pLIST);

#endif
