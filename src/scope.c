#include "include/scope.h"
#include<string.h>


scope_T* init_scope()
{
    scope_T* scope = calloc(1, sizeof(struct SCOPE_STRUCT));
    scope->fx_defs = (void*) 0;
    scope->fx_defs_size = 0;

    return scope;
}


AST_T* scope_add_fx_def(scope_T* scope, AST_T* fdef)
{
    scope->fx_defs_size += 1;

    if(scope->fx_defs == (void*) 0)
    {
        scope->fx_defs = calloc(1, sizeof(struct AST_STRUCT*));
    }
    else
    {
        scope->fx_defs = realloc(
            scope->fx_defs,
            scope->fx_defs_size * sizeof(struct AST_STRUCT**)
        );
    }

    scope->fx_defs[scope->fx_defs_size-1] = fdef;

    return fdef;

}

AST_T* scope_get_fx_def(scope_T* scope, const char* fname)
{
    for(int i = 0; i < scope->fx_defs_size; i++)
    {
        AST_T* fdef = scope->fx_defs[i];

        if(strcmp(fdef->fx_def_name, fname) == 0)
        {
            return fdef;
        }
    }

    return (void*) 0;

}



