#ifndef SCOPE_H
#define SCOPE_H
#include "AST.h"

typedef struct SCOPE_STRUCT
{
    AST_T** fx_defs;
    size_t fx_defs_size;
} scope_T;

scope_T* init_scope();

AST_T* scope_add_fx_def(scope_T* scope, AST_T* fdef);

AST_T* scope_get_fx_def(scope_T* scope, const char* fname);

#endif
