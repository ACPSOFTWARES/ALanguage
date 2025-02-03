#ifndef SCOPE_H
#define SCOPE_H
#include "AST.h"

typedef struct SCOPE_STRUCT
{
    AST_T** fx_defs;
    size_t fx_defs_size;
} scope_T;

scope_T* init_scope();

#endif
