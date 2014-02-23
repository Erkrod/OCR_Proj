#include "View.h"

void CatchEvent(GtkWidget *widget, gpointer data){
	ViewHandle * MainHandle = (ViewHandle *) data;
	ObjectHandle * CurrObject;
	ObjectHandle * ObjectListByWidget = MainHandle->ObjectListByWidget;
	HASH_FIND(HashByWidget,ObjectListByWidget, &widget, sizeof(GtkWidget *),CurrObject);
	if (CurrObject)
		Control_ProcessEvent(CurrObject);
	else
		printf("Can't find object with this GtkWidget value: %p\n", widget);
}

ObjectHandle * ObjectHandle_Initialize(const char * name, GtkWidget * widget){
	ObjectHandle * NewObject = (ObjectHandle *) malloc(sizeof(ObjectHandle));
	assert(NewObject);
	strncpy(NewObject->Name, name, MAX_HASH_KEY_LENGTH);
	NewObject->Widget = widget;
	return NewObject;
}

void AddWidgetToViewHandle(ViewHandle * MainViewHandle, const char * NewName, GtkWidget * NewWidget){
	 ObjectHandle * NewObject;
	 NewObject = ObjectHandle_Initialize(NewName, NewWidget);
	HASH_ADD(HashByName, MainViewHandle->ObjectListByName, Name, sizeof(char) * MAX_HASH_KEY_LENGTH, NewObject);
	HASH_ADD(HashByWidget,MainViewHandle->ObjectListByWidget,Widget,sizeof(GtkWidget *),NewObject);
}

ViewHandle * View_Initialize(void){
	ViewHandle * ReturnHandle = (ViewHandle *) malloc(sizeof(ViewHandle));
	ReturnHandle->ObjectListByName = NULL;
	ReturnHandle->ObjectListByWidget = NULL;
	return ReturnHandle;
	
	/*Ryan, in this functions you'll need to follow these rules
		- Don't call gtk_main(), that's my turn
		- write signal connect with this format
			g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(button1_Clicked), MainControl);
		  Then somewhere else you define button1_Clicked as 
		  void button_clicked(GtkWidget *widget, gpointer data)
		  {
		    ControlHandle * MainControl = (ControlHandle *) data;
		    MainControl->Event->Type = ButtonClick;		//the enum here is taken from inc/Control/EventStructure.h, add more to enum as you add more button
		    MainControl->Event->ButtonClicked = HASH_FIND_STR(MainControl->ObjectHashTable, name, "button1";
		    Control_ProcessEvent(MainControl);
		  }
		
		- Important: this is the equivalent of ObjectList we have last time
		ObjectHandle * NewObject = ObjectHandle_Initialize(button1, "Start Button"); 	//this time we use a string to denote the object
		//then use HASH_ADD_INT
	*/


}
