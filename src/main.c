#include<stdio.h>
#include "include/lexer.h"
#include "include/parser.h"
int main(){

    lexer_T* lexer = init_lexer(
        "var name = \"Piyush\";\n"
        "print(name);\n"
    );

    parser_T* parser = init_parser(lexer);
    AST_T* root = parser_parse(parser);

    return 0;

}
