#include <iostream>
#include "compiler.h"
using namespace  std;
int main(int argc , char *argv[]) {

    // first we get the absolute path of input file we must use \\ to get ride of escape sequence ;
   char input_file_path[] ="C:\\Users\\Administrator\\Desktop\\lexical analyzer\\test.c";
   // this output file for the final output of compiler  main.o (object file)
   char output_file_path[]="C:\\Users\\Administrator\\Desktop\\lexical analyzer\\test.o";

   int compile_resutl=compile_file(input_file_path,output_file_path);
   if(compile_resutl==0){
       cout << "the file has been compiled\n";
   }
   else{
       cerr<< "compilation fail\n";
   }
   return 0;
 }

