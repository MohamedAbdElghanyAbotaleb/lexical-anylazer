//this file will contain all functionality of lexical
// Created by Administrator on 11/10/2023.
//designated initializers
// problem of taking the address of temporry object
#include<vector>
#include "compiler.h"
#include <iostream>
#include <assert.h>  // make assumption
#include <string>
#include <string.h>
#include <iostream>
using namespace std;

static lexical_analyzer *current_lexical; // global variable
static vector<struct token*> tokens_set;  // global token
// global file object for input file and output file
//static FILE*input_file;
//static FILE*output_file;
/*
#define get_certain_string (buffer,c,exp)\
             while(exp){                  \
               buffer+=c   ;            \
               current_lexical->pop_char() ;\
               c=current_lexical->read_char(); \
               }
*/
// function used to change the bracket counters;
void start_expression(int flag){
    switch (flag) {
        case 0: current_lexical->brackets_count.square_bracket_count++;
            break;
        case 1: current_lexical->brackets_count.round_bracket_count ++;
            break;
        default :
            current_lexical->brackets_count.curly_bracket_count++;

    }
}
// function used to check if vaidi (()) or {{}} or [[]] or not
void finish_expression(int flag){
    switch (flag) {
        case square_bracket: current_lexical->brackets_count.square_bracket_count--;
               break;
        case round_bracket: current_lexical->brackets_count.round_bracket_count --;
             break;
        default :
                current_lexical->brackets_count.curly_bracket_count--;

    }
    if(current_lexical->brackets_count.curly_bracket_count <0 || current_lexical->brackets_count.square_bracket_count<0 || current_lexical->brackets_count.round_bracket_count<0){
        compiler_error(current_lexical->current_process,"Using Extra Bracket\n");
    }
}

// function used to check if two string are equal or not
bool str_are_equal(string str1,string str2){
    if(str1.compare(str2)==0) // str.compare return 0 if equal or >1 or  <1 if not equal
        return 1;
    else
        return 0;
}

//
// function to check if keword or not
bool token_is_keyword(string str ){
    return str_are_equal(str, "unsigned") ||
           str_are_equal(str, "signed") ||
           str_are_equal(str, "char") ||
           str_are_equal(str, "short") ||
           str_are_equal(str, "int") ||
           str_are_equal(str, "long") ||
           str_are_equal(str, "float") ||
           str_are_equal(str, "double") ||
           str_are_equal(str, "void") ||
           str_are_equal(str, "struct") ||
           str_are_equal(str, "union") ||
           str_are_equal(str, "static") ||
           str_are_equal(str, "return") ||
           str_are_equal(str, "include") ||
           str_are_equal(str, "sizeof") ||
           str_are_equal(str, "if") ||
           str_are_equal(str, "else") ||
           str_are_equal(str, "while") ||
           str_are_equal(str, "for") ||
           str_are_equal(str, "do") ||
           str_are_equal(str, "break") ||
           str_are_equal(str, "continue") ||
           str_are_equal(str, "switch") ||
           str_are_equal(str, "case") ||
           str_are_equal(str, "default") ||
           str_are_equal(str, "typedef") ||
           str_are_equal(str, "const") ||
           str_are_equal(str, "extern") ;
}


// this function used to make keyword or identifier
/*
 * THOUGHT about identifier  if first char is alpha or _ it mean identifier or keword
 */
struct token *token_make_keywrod_or_identifier(){
  string buffer="";
  char c=current_lexical->read_char();
  if(!(isalpha(c)|| c=='_'))
      return NULL;
    while ((c>='A' && c<='z') ||  (c>='a' && c<='z') || c=='_' || (c>='0' && c<='9')){  // check about condition of identifier
        buffer+=c;
        current_lexical->pop_char(); // remove the char from buffer
        c=current_lexical->read_char(); // read next_char
    }

    int type=TOKEN_TYPE_IDENTIFIE;  // MAKE the default type is identifier
    if(token_is_keyword(buffer)) // check if keyword we will change the type of token
        type=TOKEN_TYPE_KEYWORD;
   struct token * token_keyword_or_identifier=new token ; // create token in heap memory
   token_keyword_or_identifier->type=type;
   token_keyword_or_identifier->string_value=buffer ;
   return token_keyword_or_identifier;

}

// this function is resposible for creating string ex "mhoamed"
struct token* token_make_string(char start_delim,char end_delim){ // "mohamed"
    string buffer="";
    // read char " and increase buffer pointer by one
    char c=current_lexical->pop_char();
    //get_certain_string(buffer,c,((c>='a'&& c<='z')|| (c>='A' && c<='Z')));
    // check if c not equal " it will abort the whole programm
   // assert(c==start_delim);
    // read first char after " and increase buffer pointer by one
    c=current_lexical->read_char();
    while(c!=end_delim){
        // we need to check this condition
       // if(c=='\\'){
         //   c=current_lexical->pop_char();
            //continue;}
        buffer+=c;
        current_lexical->pop_char();
        c=current_lexical->read_char();
    }
    current_lexical->pop_char(); /// remove the end " from buffer
    // create token in heap
    struct token* string_token= new token;
    string_token->type=TOKEN_TYPE_STRING;
    string_token->string_value=buffer;
    // return addres of first member of struct and string_token pointer will be deleted form the activation  record;
    return string_token;

}

// function to check if valid compound operator like ++ && etc;
bool is_compound_operator(string &op ){
 return  ( str_are_equal (op, "+=") ||
           str_are_equal(op, "-=") ||
           str_are_equal(op, "*=") ||
           str_are_equal(op, "/=") ||
           str_are_equal(op, ">>") ||
           str_are_equal(op, "<<") ||
           str_are_equal(op, ">=") ||
           str_are_equal(op, "<=") ||
           str_are_equal(op, "||") ||
           str_are_equal(op, "&&") ||
           str_are_equal(op, "|")  ||
           str_are_equal(op, "&")  ||
           str_are_equal(op, "++") ||
           str_are_equal(op, "--") ||
           str_are_equal(op, "!=") ||
           str_are_equal(op, "==") ||
           str_are_equal(op, "->") );
}
// function to check if char is operator or not 
bool is_operator (char c){
    switch (c) {
        Operator_Case_Not_division
         return true;
        default :
            return false ;
    }
}
// function to create operator token
struct token* token_make_operator(){
    string operator_buffer="";
    char c=current_lexical->pop_char(); // pop the first operator from the buffer
    operator_buffer+=c; // now buffer contain only one operator ;
    c=current_lexical->read_char(); // we read the char after operator 
    if(is_operator(c)){
         operator_buffer+=c; // add the second operator to string not pop it from stream file object 
         if(is_compound_operator(operator_buffer)){
             current_lexical->pop_char(); // remove second operator from buffer  and now buffer contain ++ or += etc 
         }
         else{
             operator_buffer=operator_buffer[0]; // buffer contain now one operator only + , * etc 
         }
    }
    // create operator token
    struct token*operator_token=new token;
    operator_token->type=TOKEN_TYPE_OPERATOR;
    operator_token->string_value=operator_buffer;
    return operator_token;

    
}
// function to get last token in vector
struct token* get_last_token_in_tokens_set(){
    int x=tokens_set.size();
    if(tokens_set.size()>0){
        return tokens_set[tokens_set.size()-1];
    }
    return NULL;
}

// function to
// function to choose if i will create operator token or string
struct token* token_make_operator_or_string(){
    char op= current_lexical->read_char();
    // now check if have include<file_name.h> we deal file_name as string and < start delimeter and > end delimater
    struct token*last_token=NULL;
    if(op=='<'){
        last_token =get_last_token_in_tokens_set();
        //cout << (*last_token)->string_value<<endl;
        string word="include";
        if(!last_token){   // check on the last token  case: if the first char in  file is <  the last token =NULL;
            bool flag= token_is_certain_keyword(last_token,word);
            if(flag){ // check if last token is keyword and its value is include  note: "include" will not accept
                return token_make_string('<','>'); // include<com.h>  so com.h will be string token
            }
        }

    }
    if(op=='['){
        start_expression(square_bracket);
    }
    else if(op=='('){
        start_expression(round_bracket);
    }

   // this mean we don't have include before < operator
    return token_make_operator(); // calling function that create operator token
}


// function to make symbol token
struct token* token_make_symbol(){
    char c= current_lexical->read_char();
    int flag;

    if(c==']'){
        flag=square_bracket;
        finish_expression(flag);
    }
    else if(c==')'){
        flag=round_bracket;
        finish_expression(flag);
    }
    else if(c=='}'){
        flag=curly_bracket;
        finish_expression(flag);
    }
    else if(c=='{'){
        flag=curly_bracket;
        start_expression(flag);
    }
    c=current_lexical->pop_char();
    struct token * symbol_token=new token;
    symbol_token->type=TOKEN_TYPE_SYMBOL;
    symbol_token->char_value=c;
    return symbol_token;
}
// function to read string each char is a number
void read_number_as_string(string &buffer){
    char c=current_lexical->read_char();
    while(c>='0' && c<='9'){
        buffer+=c;
        current_lexical->pop_char();
        c=current_lexical->read_char();
    }
}
// this function is used to convert string to number
long long token_read_number(){
    string buffer="";
    read_number_as_string(buffer);
    // convert string to long logn using built in function stoll : string to long logn
    return stoll(buffer);
    //char c ;
    //get_certain_string(buffer,c,c >= '0' && c <= '9');
}
// this function is used to create a number token
struct token* token_make_number(){
    long long number=token_read_number();
    struct token*number_token=new token;
    number_token->type=TOKEN_TYPE_NUMBER;
    number_token->long_long_value=number;
    return  number_token;

}

// this function is for handle newline
struct token* token_make_new_line(){
    current_lexical->pop_char(); // remove newline buffer
    struct token*new_line_token= new token;
    // we don not store value at new line
    new_line_token->type=TOKEN_TYPE_NEWLINE;
    return new_line_token;
}

// function to handle whitespaces
void  handle_whitespaces(){
    // skip the " " or "\t"
    current_lexical->pop_char();

}
struct token* token_make_comment(){
    current_lexical->pop_char(); // pop the seconde / from file buffer
    string comment_content="";
    char c= current_lexical->read_char();
    while(c!='\n' && c!=EOF){
        comment_content+=c; // addd char to content
        current_lexical->pop_char();
        c=current_lexical->read_char();
    }
    // create token and store value ;
    struct token* comment_token= new token;
    comment_token->type=TOKEN_TYPE_COMMENT;
    comment_token->string_value=comment_content;
    return comment_token;
}
// make comment or division operator
struct token* token_make_comment_or_operator(){
    current_lexical->pop_char(); // pop first / from buffer
    char c= current_lexical->read_char();
    if(c='/')
       return  token_make_comment();
    else
      return   token_make_operator();

}

// this function used to read char by char and make suitable token
struct token*read_next_token(){
    struct token *token=NULL;  // #include "mohamed"
    char c= current_lexical->read_char();
    //cout << c<<endl;
    switch (c) {
        case'"': // "mohamed"
            token=token_make_string('"','"');
            break;
        case'\n':
            token=token_make_new_line();
            break;
        case ' ':
        case '\t':
            handle_whitespaces();
            // skip the whitespaces and go to next token to read
            token=read_next_token();
            break;
        case '/':
            token=token_make_comment_or_operator();
            break;
        case EOF :  // end of file
            break;
        Numeric_Case
              token=token_make_number();
              break;
        Symbol_Case
              token=token_make_symbol();
              break;
        Operator_Case_Not_division 
              token=token_make_operator_or_string(); // may be operator or my be string like <file_name.h>
              break;
        default:
              token=token_make_keywrod_or_identifier();
              if(!token) {
              compiler_error(current_lexical->current_process,"unexpected token\n");}
            break;
    }
    return token;
}
int lexical(lexical_analyzer * current_lexical,vector<token*> &tokens_set){
  //  struct token*token=read_next_token();
  // to access all things outisde this function
  ::current_lexical=current_lexical;
 // input_file=current_lexical->current_process->input_file;
 // output_file=current_lexical->current_process->output_file;
    struct token*token=NULL;
    token=read_next_token();
    ::tokens_set=tokens_set;  // make object to vector  global
    while(token){
        ::  tokens_set.push_back(token);
       tokens_set.push_back(token);
      // int x=tokens_set.size();
        token=read_next_token();
    }

    return lexical_analyzer_sucess;
}