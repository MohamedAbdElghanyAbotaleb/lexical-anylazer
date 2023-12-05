// this file will contain all function  declaration,struct ,enum
// all functioni definition at the end of file;
#include <iostream>
#include <stdio.h> // calling this library for FILE object
#include <string>
#include <vector>
using namespace std;
//void  compilation_process_create(const char*input_file_path,const char*output_file_path);

// define pos
struct pos {
    int line;
    int column;
};
// define detail about every token
struct token{
    // type of token : string ,keyword ,identifier etc
    int type;
    // the value of token: we will use the union to share the same memory of all memebers in union
    // how to define string in union
    union {   // unknown nunion
        int int_value;
        long long lnog_value; //8
        long long_long_value;
        char char_value;
        //const char * string_value;
      // string can not defined in union

    };
    string string_value;
    //string brackets_content;  //(5+10) content will be 5+10;
};
// define detail about every compilation_process
struct compile_process{
    // the pos in input file
    struct pos pos;
    // input file object
    FILE * input_file;
    // output file object
    FILE* output_file;
    // vector object to tokens vector
    // vector<struct token*> token_set; // how assign this

};
// define struct to count expression and breackets
struct brackets{
    int square_bracket_count=0; //[]
    int round_bracket_count=0; //()
    int curly_bracket_count=0; //{}
};
class lexical_analyzer{
public:
    // we must know our pos
    struct pos pos ;
    // way to know all detail abbout the compilation process we lex it
    compile_process * current_process;
    // define vector of tokens
     std::vector<struct  token* > tokens_set; // dynamic array
    // way to know that : (((()))) is valid or not
    struct brackets brackets_count;
    // string bracket_buffer
    //
    // string bracket buffer

    // function to push token in tokens_set vector

    // function to peek char from input file the parameter is input file
    // #incldude<iostrea>    x++ x+4
    char read_char(){
        // read char form file stream buffer
        char c= getc(current_process->input_file);
        // push the same char in file stream buffer in same order
        ungetc(c,current_process->input_file);
        return c;

    }
    // remove the char from file stream buffer
    char pop_char(){
        char c=getc(current_process->input_file);
        // increase lexical position with one
        pos.column+=1;
        // increase compilation_process with one
        current_process->pos.column+=1;
        // if c equal endline we will go to the next line ;
        if(c=='\n'){
            pos.line+=1;
            pos.column=1;
            current_process->pos.line+=1;
            current_process->pos.column=1;
        }
        return c;
    }
    // add char to file stream buffer in same order we read since we don't need char now
    void push_char(char c){
        ungetc(c,current_process->input_file);
        return;
    }
};
//*********************************************************************************************************************8
// make readable code
enum{
    COMPILER_SUCCESS,
    COMPILER_FAILED
};
enum{
    lexical_analyzer_sucess,
    lexical_analyzer_failed
};

enum{
    square_bracket,
    round_bracket,
    curly_bracket
};
// make enumeration of tokens types;
enum{
    TOKEN_TYPE_IDENTIFIE=0,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_SYMBOL,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_NEWLINE,
    TOKEN_TYPE_STRING
};
//**********************************************************************************************************************
// defining number
#define Numeric_Case \
    case '0' :        \
    case '1' :        \
    case '2' :        \
    case '3' :        \
    case '4' :        \
    case '5' :        \
    case '6' :        \
    case '7' :        \
    case '8':         \
    case '9'  :

// define operator excluding division operator /
#define Operator_Case_Not_division      \
    case '+':                           \
    case '-':                           \
    case '*':                           \
    case '>':                           \
    case '<':                           \
    case '^':                           \
    case '%':                           \
    case '!':                           \
    case '=':                           \
    case '~':                           \
    case '|':                           \
    case '&':                           \
    case '(':                           \
    case '[':                           \
    case ',':                           \
    case '.':                           \
    case '?':
// define symbol
#define Symbol_Case \
  case '{':         \
    case '}':       \
    case ':':       \
    case ';':       \
    case '#':       \
    case '\\':      \
    case ')':       \
    case ']' :;

// define keword


 //**********************************************************************************************************************
int compile_file(const char * input_file_name, const char*output_file_name);

compile_process*  compilation_process_create(const char*input_file_path,const char*output_file_path);

lexical_analyzer* lexical_init (struct compile_process*current_process);

int lexical(lexical_analyzer * current_lexical,vector<token*> &tokens_set);

void compiler_error(compile_process*current_process,string message);

// define macro to check if two string are equal or not
bool str_are_equal(string str1,string str2);
// define function to get the last token in tokens_set;
struct token* get_last_token_in_tokens_set();

bool token_is_certain_keyword(struct token*last_token,string word);

// function to print all tokens
void print_all_tokens();

/*
#define get_certain_string (buffer,c,exp) \
             while(expr){                  \
               buffer+=c;                 \
               current_lexical->pop_char() \
               c=current_lexical->read_char() \
               }
*/