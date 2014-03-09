#include "Model.h"

int main(void){
	/*give it a hellow orld program string*/
	
	char TestString[] = "#include <stdlib.h>\n#include <stdio.h>\nint main(void){\nprintf(\"Hello World.\\n\");\nreturn 0;\n}";
	
	UT_string * Carrier;
	utstring_new(Carrier);
	utstring_printf(Carrier, "%s", TestString);
	UT_string * Receiver = GetCompileMessage(Carrier);
	printf("Compile message is:\n%s\n", utstring_body(Receiver));
	return 0;
	
}