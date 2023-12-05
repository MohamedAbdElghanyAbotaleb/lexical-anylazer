// this file is responsible about calling the stages of compilation
#include "compiler.h"
#include <stdio.h>
#include <iostream>
#include<vector>
#include <queue>
#include <stdlib.h>
#include <fstream>
using namespace std;
// global variable for current process we can change it after
struct compile_process*current_process=NULL;
// define vector that contain all tokens\

   /*vector of pointer every pointer refer to token in heap
   the pointer itself in heap also
   the vector name in stack
   we need to free memory by traverse element by element and use free (v[i])
   we need also to  make vector.erase() to delet all pointer names */
vector<struct token*> tokens_set;

int compile_file(const char * input_file_name, const char*output_file_name){
    //****************************************************************************************
    // first we create compilation process
   current_process= compilation_process_create(input_file_name,output_file_name);
    if(!current_process)
        return COMPILER_FAILED;
    //****************************************************************************************
    // second we call lexical analyzer

    // inti lexical analyzer and create
   lexical_analyzer *current_lexical= lexical_init(current_process);
   if(!current_lexical)
      return COMPILER_FAILED;
   // now we call lexical analyzer functions to produce token
   if(lexical(current_lexical,tokens_set))
      return COMPILER_FAILED;
  // cout << tokens_set[0].type << " "<< tokens_set[0].int_value<<endl;
  // current_process->token_set=current_lexical->tokens_set;
   //*****************************************************************************************
    // third we perform parsing
    // fourth we make code generation

   print_all_tokens(); // this function used to print tokens in file
    return COMPILER_SUCCESS;
}






// function that make open input file and make memory representation for every file we will compile
// this function will define all abstraction details we need
 compile_process*compilation_process_create(const char*input_file_path,const char*output_file_path){
    // open input file using c language method not c++ for reading
    FILE*input_file= fopen(input_file_path,"r");
    // check if the file has been opened or may be error
    if(!input_file)
        //::current_process=NULL;
        return NULL;
    // open output file for writing
    FILE *output_file= fopen(output_file_path,"w");
    if(!output_file)
         return NULL;
        // :: current_process=NULL;
    // now make memory representaion for process
    // we will using heap memory to store the data about current compilation process
   struct  compile_process* current_process=new struct compile_process;
    current_process->input_file=input_file;
    current_process->output_file=output_file;
    // make pos of line and colum =1 as start
    current_process->pos.line=1;
    current_process->pos.column=1;
    // now current_process pointer contain all information
    //  make global variable refer to heap
    return current_process;
   // :: current_process=current_process;

}


// function to make memory representation for every lexical calling and init value of lexical
lexical_analyzer* lexical_init (struct compile_process*current_process){
    // creation object of lexical in heap
     lexical_analyzer * current_lexical=new  lexical_analyzer;
    current_lexical->current_process=current_process;
    current_lexical->pos.line=1;
    current_lexical->pos.column=1;
  //  current_lexical->number_of_open_expression=0;
    return current_lexical;
}
// function used to print error messange when it happened
void compiler_error(compile_process*current_process,string error_message){
  cerr << error_message << "on line "<< current_process->pos.line << ", column " << current_process->pos.column<<endl;
  // stop the whole programm
  exit(-1);
}

// open file to print output of scanner in it


// print all tokens

void print_all_tokens(){
    // we will use cpp file style to open file
    fstream token_file;
    token_file.open("C:\\Users\\Administrator\\Desktop\\lexical analyzer\\token_file.txt",ios::out);
    token_file<< ("  Token_Type    |    Lexeme\n\n");

   // token_file << "Token_Type    |    Lexeme\n"<<endl;
    for(int i=0;i<tokens_set.size();++i)
    {
        int type=tokens_set[i]->type;
        switch (type) {
            case TOKEN_TYPE_KEYWORD:
                token_file<< "  keyword       |   " << tokens_set[i]->string_value<<endl;

                break;
            case TOKEN_TYPE_IDENTIFIE:
                token_file<< "  IDENTIFIER    |   " << tokens_set[i]->string_value<<endl;
                break;
            case TOKEN_TYPE_COMMENT:
                token_file<< "  comment       |   " << tokens_set[i]->string_value<<endl;
                break;
            case TOKEN_TYPE_OPERATOR:
                token_file<< "  operator      |   " << tokens_set[i]->string_value<<endl;
                break;
            case TOKEN_TYPE_STRING:
                token_file<< "  string        |   " << tokens_set[i]->string_value<<endl;
                break;
            case TOKEN_TYPE_SYMBOL:
                token_file<< "  symbol        |   " << tokens_set[i]->char_value<<endl;
                break;
            case TOKEN_TYPE_NUMBER:
                token_file<< "  Number        |   " << tokens_set[i]->long_long_value<<endl;
                break;
            default:
                token_file<< "  New_line      |   " <<endl;




        }
    }
}
