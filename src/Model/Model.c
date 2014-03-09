#include "Model.h"

UT_string * GetCompileMessage(UT_string * code){
	FILE * file = fopen("TempCode.c", "w");
	if (!file) return NULL;
	
	fprintf(file, "%s", utstring_body(code));
	fclose(file);
	
	system("rm TempGCC_err.txt TempGCC_good.txt");
	system("gcc -o run TempCode.c 2>TempGCC_err.txt 1>TempGCC_good.txt");
	
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
		
		return CompileMsg;
	} else {
		fclose(file);
		utstring_clear(CompileMsg);
		utstring_printf(CompileMsg, "No error compiling. The code looks good.\n");
		return CompileMsg;
	}
}