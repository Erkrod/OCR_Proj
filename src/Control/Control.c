

#include "Control.h"


ControlHandle * Control_Initialize(void){
	ControlHandle * ToReturn = (ControlHandle *) malloc(sizeof(ControlHandle));
	return ToReturn;
}

void Control_MainLoop(ControlHandle * MainHandle){
	gtk_main();
}

void Control_CleanUp(ControlHandle * MainHandle){
	free(MainHandle);
}

/*function to take care of all event*/
ControlHandle * Control_ProcessEvent(ObjectHandle * ClickedObject){
	printf("Object clicked has name: %s\n", ClickedObject->Name);
	if (strcmp(ClickedObject->Name,"OpenFile") == 0){
		printf("Put the function to open file here\n");
	}
}
