#ifndef CONTROL_H
#define CONTROL_H

#include <gtk/gtk.h>
#include "EventStructure.h"
#include "Model.h"
#include "View.h"

typedef struct {
	EventClass event;
	ImageList * ImageStack;
	/*if necessary*/
	/*ModelHandle * MainModelHandle;
	ViewHandle * MainViewHandle;*/
} ControlHandle;

ControlHandle * Control_Initialize(void);
void Control_MainLoop(ControlHandle *);
void Control_CleanUp(ControlHandle *);

/*function to take care of all event*/
ControlHandle * Control_ProcessEvent(ControlHandle *);

#define
