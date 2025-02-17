#include "include/visitor.h"
#include "include/scope.h"
#include <stdio.h>
#include<string.h>

static AST_T* builtin_function_print(visitor_T* visitor, AST_T** args, int args_size)
{
    for(int i = 0; i < args_size; i++)
    {
        AST_T* visited_ast = visitor_visit(visitor, args[i]);
        switch(visited_ast->type)
        {
            case AST_STRING: printf("%s\n", visited_ast->string_value); break;
            default: printf("%p\n", visited_ast); break;
        }


    }

    return init_ast(AST_NOOP);

}

static AST_T* builtin_function_printsl(visitor_T* visitor, AST_T** args, int args_size)
{
    for(int i = 0; i < args_size; i++)
    {
        AST_T* visited_ast = visitor_visit(visitor, args[i]);
        switch(visited_ast->type)
        {
            case AST_STRING: printf("%s", visited_ast->string_value); break;
            default: printf("%p", visited_ast); break;
        }


    }

    return init_ast(AST_NOOP);

}

visitor_T* visitor_init()
{
    visitor_T* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));
    visitor->variable_definitions = (void*)0;
    visitor->variable_definitions_size = 0;

    return visitor;
}

AST_T* visitor_visit(visitor_T* visitor, AST_T* node)
{
    switch(node->type)
    {
        case AST_VARIABLE_DEFINITION: return visitor_visit_variable_definition(visitor, node); break;
        case AST_FX_DEFINITION: return visitor_visit_fx_def(visitor, node); break;
        case AST_VARIABLE: return visitor_visit_variable(visitor, node); break;
        case AST_FUNCTION_CALL: return visitor_visit_function_call(visitor, node); break;
        case AST_STRING: return visitor_visit_string(visitor, node); break;
        case AST_COMPOUND: return visitor_visit_compound(visitor, node); break;
        case AST_NOOP: return node; break;
    }

    printf("Uncaught Statement of type `%d`\n", node->type);

    exit(1);

    return init_ast(AST_NOOP);

}

AST_T* visitor_visit_variable_definition(visitor_T* visitor, AST_T* node)
{
    if(visitor->variable_definitions == (void*)0)
    {
        visitor->variable_definitions = calloc(1, sizeof(struct AST_STRUCT*));
        visitor->variable_definitions[0] = node;
        visitor->variable_definitions_size += 1;
    }
    else
    {
        visitor->variable_definitions_size += 1;
        visitor->variable_definitions = realloc(
            visitor->variable_definitions,
            visitor->variable_definitions_size * sizeof(struct AST_STRUCT*)
        );

        visitor->variable_definitions[visitor->variable_definitions_size-1] = node;

    }

    return node;

}


AST_T* visitor_visit_fx_def(visitor_T* visitor, AST_T* node)
{
    
    scope_add_fx_def(
        node->scope,
        node
    );

    return node;
}



AST_T* visitor_visit_variable(visitor_T* visitor, AST_T* node)
{
    for(int i = 0; i < visitor->variable_definitions_size; i++)
    {
        AST_T* vardef = visitor->variable_definitions[i];

        if(strcmp(vardef->variable_definition_variable_name, node->variable_name) == 0)
        {
            return visitor_visit(visitor, vardef->variable_definition_value);
        }
    }

    printf("Undefined Variable: `%s`\n", node->variable_name);

    return node;

}

AST_T* visitor_visit_function_call(visitor_T* visitor, AST_T* node)
{
    if(strcmp(node->function_call_name, "print") == 0)
    {
        return builtin_function_print(visitor, node->function_call_arguments, node->function_call_arguments_size);
    }
    if(strcmp(node->function_call_name, "printsl") == 0)
    {
        return builtin_function_printsl(visitor, node->function_call_arguments, node->function_call_arguments_size);
    }

    AST_T* fdef = scope_get_fx_def(
        node->scope,
        node->function_call_name
    );

    if(fdef != (void*)0)
        return visitor_visit(visitor, fdef->fx_def_body);

    printf("Undefined method: `%s`\n", node->function_call_name);
    exit(1);

}

AST_T* visitor_visit_string(visitor_T* visitor, AST_T* node)
{
    return node;
}

AST_T* visitor_visit_compound(visitor_T* visitor, AST_T* node)
{
    for(int i=0; i < node->compound_size; i++)
    {
        visitor_visit(visitor, node->compound_value[i]);
    }

    return init_ast(AST_NOOP);

}




