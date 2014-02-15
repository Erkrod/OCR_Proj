

void View_Initialize(ControlHandle * MainControl){
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
