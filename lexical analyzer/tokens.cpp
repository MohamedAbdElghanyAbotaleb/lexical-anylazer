#include "compiler.h"
#include <string>
// note : "include" will not accept as it is string bu  <include> will accept as it is keyword
bool token_is_certain_keyword(struct token*last_token,string word){
    int compare= str_are_equal(last_token->string_value,word); // function will return 1 if equal
    // the token must be keywrod token and compare value =1;

    return (last_token->type== TOKEN_TYPE_KEYWORD && compare);
}