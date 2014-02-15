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
ControlHandle * Control_ProcessEvent(ControlHandle * MainHandle){
	switch (MainHandle->Event->Type){
		case Event1:
			
			break;
		case Event2:
			
			break;
	}
}
