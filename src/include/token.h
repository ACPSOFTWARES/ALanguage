#ifndef TOKEN_H
#define TOKEN_H

typedef struct TOKEN_STRUCT
{
    enum
    {
        TOKEN_ID,
        TOKEN_EQUALS,
        TOKEN_STRING,
        TOKEN_SEMI,
        TOKEN_LPARAN,
        TOKEN_RPARAN
    }type;

    char* value;

} token_T;

token_T* init_token(int type, char* value);

#endif