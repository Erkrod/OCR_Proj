#include "Model.h"

int main(void){
	/*give it a hellow orld program string*/
	
	char TestString[] = "#include <stdlib.h>\n#include <stdio.h>\nint main(void){\nprintf(\"Hello World.\\n\");\nreturn 0;\n}";
	
	UT_string * Carrier;
	utstring_new(Carrier);
	
	utstring_clear(Carrier);
	utstring_printf(Carrier, "%s", TestString);
	UT_string * Receiver = GetCompileMessage(Carrier);
	printf("Compile message is:\n%s\n", utstring_body(Receiver));
	utstring_free(Receiver);
	
	char TestString2[] = "#include <stdlib.h>\n#include <stdio.h>\nint main(void){\nprintf(\"Hello World.\\n\")\nreturn 0;\n}";
	utstring_clear(Carrier);
	utstring_printf(Carrier, "%s", TestString2);
	Receiver = GetCompileMessage(Carrier);
	printf("Compile message is:\n%s\n", utstring_body(Receiver));
	
	utstring_free(Carrier);
	utstring_free(Receiver);
	return 0;
	
}