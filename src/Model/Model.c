#include "Model.h"

int file_exist (char *filename)
{
  struct stat   buffer;   
  return (stat (filename, &buffer) == 0);
}

UT_string * GetCompileMessage(UT_string * code){
	FILE * file = fopen("TempCode.c", "w");
	if (!file) return NULL;
	
	fprintf(file, "%s", utstring_body(code));
	fclose(file);
	
	if (file_exist("TempGCC_err.txt")) unlink("TempGCC_err.txt");
	if (file_exist("TempGCC_good.txt")) unlink("TempGCC_good.txt");
	int a = system("gcc -o run TempCode.c 2>TempGCC_err.txt 1>TempGCC_good.txt");
	if (a == 0) a = 1;
	if (file_exist("TempCode.c")) unlink("TempCode.c");
	
	file = fopen("TempGCC_err.txt", "r");
	if (!file) return NULL;
		
	UT_string * CompileMsg;
	utstring_new(CompileMsg);
	
	fseek( file , 0L , SEEK_END);
	long lSize = ftell( file );
	rewind( file );
	
	if (lSize > 0) {
	
		char * ReadString = (char *) malloc(sizeof(char) * lSize);
		assert(ReadString);
		
		if( 1!=fread( ReadString , lSize, sizeof(char) , file) )
			fclose(file),free(ReadString),fputs("Can't read TempGCC_err.txt",stderr),exit(1);
		fclose(file);
		
		utstring_printf(CompileMsg, "%s", ReadString);
		
		free(ReadString);
		
		if (file_exist("TempGCC_err.txt")) unlink("TempGCC_err.txt");
		if (file_exist("TempGCC_good.txt")) unlink("TempGCC_good.txt");
		if (file_exist("run")) unlink("run");
		
		return CompileMsg;
	} else {
		fclose(file);
		utstring_clear(CompileMsg);
		utstring_printf(CompileMsg, "No error compiling. The code looks good.\n");
		if (file_exist("TempGCC_err.txt")) unlink("TempGCC_err.txt");
		if (file_exist("TempGCC_good.txt")) unlink("TempGCC_good.txt");
		if (file_exist("run")) unlink("run");
		return CompileMsg;
	}
}