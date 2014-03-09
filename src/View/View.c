#include "View.h"

void CatchEvent(GtkWidget *widget, gpointer data){
	ViewHandle * MainHandle = (ViewHandle *) data;
	ObjectHandle * CurrObject;
	ObjectHandle * ObjectListByWidget = MainHandle->ObjectListByWidget;
	HASH_FIND(HashByWidget,ObjectListByWidget, &widget, sizeof(GtkWidget *),CurrObject);
	if (CurrObject)
		Control_ProcessEvent(CurrObject, NULL);
	else
		printf("Can't find object with this GtkWidget value: %p\n", widget);
}

void CatchGdkEvent(GtkWidget *widget, GdkEvent * event, gpointer data){
	ViewHandle * MainHandle = (ViewHandle *) data;
	ObjectHandle * CurrObject;
	ObjectHandle * ObjectListByWidget = MainHandle->ObjectListByWidget;
	HASH_FIND(HashByWidget,ObjectListByWidget, &widget, sizeof(GtkWidget *),CurrObject);
	if (CurrObject)
		Control_ProcessEvent(CurrObject, event);
	else
		printf("Can't find object with this GtkWidget value: %p\n", widget);
}



ObjectHandle * ObjectHandle_Initialize(const char * name, GtkWidget * widget, ViewHandle * MainViewHandle){
	ObjectHandle * NewObject = (ObjectHandle *) malloc(sizeof(ObjectHandle));
	assert(NewObject);
	strncpy(NewObject->Name, name, MAX_HASH_KEY_LENGTH);
	NewObject->Widget = widget;
	NewObject->MainViewHandle = MainViewHandle;
	return NewObject;
}

void AddWidgetToViewHandle(ViewHandle * MainViewHandle, const char * NewName, GtkWidget * NewWidget){
	 ObjectHandle * NewObject;
	 NewObject = ObjectHandle_Initialize(NewName, NewWidget, MainViewHandle);
	HASH_ADD(HashByName, MainViewHandle->ObjectListByName, Name, sizeof(char) * MAX_HASH_KEY_LENGTH, NewObject);
	HASH_ADD(HashByWidget,MainViewHandle->ObjectListByWidget,Widget,sizeof(GtkWidget *),NewObject);
}

ViewHandle * View_Initialize(ControlHandle * MainControlHandle){
	ViewHandle * ReturnHandle = (ViewHandle *) malloc(sizeof(ViewHandle));
	ReturnHandle->ObjectListByName = NULL;
	ReturnHandle->ObjectListByWidget = NULL;
	ReturnHandle->MainControlHandle = MainControlHandle;
	
	return ReturnHandle;
}


#if 0
void View_CleanUp(ViewHandle * MainViewHandle){
	
	HASH_ITER(hh, users, current_user, tmp) {
    HASH_DEL(users,current_user);  /* delete it (users advances to next) */
    free(current_user);            /* free it */
  }
}
#endif