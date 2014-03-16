#include "Control.h"

int main(void){
	ControlHandle * MainHandle = Control_Initialize();
	Control_MainLoop(MainHandle);
	Control_CleanUp(MainHandle);
	return 0;
}
