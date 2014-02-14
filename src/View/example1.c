/* to compile: gcc -I../../inc/uthash example1.c -o example1 `pkg-config --cflags --libs gtk+-2.0` -Wall -g*/

#include <gtk/gtk.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "uthash.h"

#define MAX_HASH_KEY_LENGTH 20

typedef struct {
	char Name[MAX_HASH_KEY_LENGTH];
	GtkWidget * Widget;
	UT_hash_handle HashByName;
	UT_hash_handle HashByWidget;
} ObjectHandle;

ObjectHandle * ObjectHandle_Initialize(const char * name, GtkWidget * widget){
	ObjectHandle * NewObject = (ObjectHandle *) malloc(sizeof(ObjectHandle));
	assert(NewObject);
	strncpy(NewObject->Name, name, MAX_HASH_KEY_LENGTH);
	NewObject->Widget = widget;
	return NewObject;
}



/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below. */
static void hello( GtkWidget *widget,
                   gpointer   data )
{
    g_print ("Hello World\n");
}

static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    /* If you return FALSE in the "delete-event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs. */

    g_print ("delete event occurred\n");

    /* Change TRUE to FALSE and the main window will be destroyed with
     * a "delete-event". */

    return TRUE;
}

/* Another callback */
static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}

int main( int   argc,
          char *argv[] )
{
	/*declate Object list*/
	ObjectHandle * ObjectList = NULL, * ObjectList2 = NULL, * NewObject, * CurrObject = NULL;
 
    /* GtkWidget is the storage type for widgets */
    GtkWidget *window;
    GtkWidget *button;
    
    /* This is called in all GTK applications. Arguments are parsed
     * from the command line and are returned to the application. */
    gtk_init (&argc, &argv);
    
    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    /* add it to structure*/
   NewObject = ObjectHandle_Initialize("MainWindow", window);
   HASH_ADD(HashByName, ObjectList, Name, sizeof(char) * MAX_HASH_KEY_LENGTH, NewObject);
	HASH_ADD(HashByWidget,ObjectList2,Widget,sizeof(GtkWidget),NewObject);
//    HASH_ADD_PTR(ObjectList2, Widget, NewObject);
    
    /* When the window is given the "delete-event" signal (this is given
     * by the window manager, usually by the "close" option, or on the
     * titlebar), we ask it to call the delete_event () function
     * as defined above. The data passed to the callback
     * function is NULL and is ignored in the callback function. */
    g_signal_connect (window, "delete-event",
		      G_CALLBACK (delete_event), NULL);
    
    /* Here we connect the "destroy" event to a signal handler.  
     * This event occurs when we call gtk_widget_destroy() on the window,
     * or if we return FALSE in the "delete-event" callback. */
    g_signal_connect (window, "destroy",
		      G_CALLBACK (destroy), NULL);
    
    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    
    /* Creates a new button with the label "Hello World". */
    button = gtk_button_new_with_label ("Hello World");
      /* add it to structure*/
   NewObject = ObjectHandle_Initialize("HelloButton", button);
   HASH_ADD(HashByName, ObjectList, Name, sizeof(char) * MAX_HASH_KEY_LENGTH, NewObject);
   HASH_ADD(HashByWidget,ObjectList2,Widget,sizeof(GtkWidget *),NewObject);
//    HASH_ADD_PTR(ObjectList2, Widget, NewObject);
    
    
    /* When the button receives the "clicked" signal, it will call the
     * function hello() passing it NULL as its argument.  The hello()
     * function is defined above. */
    g_signal_connect (button, "clicked",
		      G_CALLBACK (hello), NULL);
    
    /* This will cause the window to be destroyed by calling
     * gtk_widget_destroy(window) when "clicked".  Again, the destroy
     * signal could come from here, or the window manager. */
    g_signal_connect_swapped (button, "clicked",
			      G_CALLBACK (gtk_widget_destroy),
                              window);
    
    /* This packs the button into the window (a gtk container). */
    gtk_container_add (GTK_CONTAINER (window), button);
    
    /* The final step is to display this newly created widget. */
    gtk_widget_show (button);
    
    /* and the window */
    gtk_widget_show (window);
    
    /*try to query the button by pointer value*/
    printf("Try to search by pointer value\n");
    CurrObject = NULL;
    HASH_FIND(HashByWidget,ObjectList2, &button, sizeof(GtkWidget *),CurrObject);
//      HASH_FIND_PTR(ObjectList2, &button, CurrObject);
    if (CurrObject){
	printf("Found object with name %s and pointer value %p, expected %p\n", CurrObject->Name, CurrObject->Widget, button);
	assert(CurrObject->Widget == button);
    } else {
     	printf("Couldn't find it\n");
    }
    
     /*try to query the button by name*/
     printf("Try to search by name\n");
    CurrObject = NULL;
    char name[20] = "HelloButton";
     HASH_FIND(HashByName,ObjectList2, name, sizeof(char) * MAX_HASH_KEY_LENGTH,CurrObject);
    if (CurrObject){
	printf("Found object with name %s and pointer value %p, expected %p\n", CurrObject->Name, CurrObject->Widget, button);
	assert(CurrObject->Widget == button);
    } else {
     	printf("Couldn't find it\n");
    }
    
    /* All GTK applications must have a gtk_main(). Control ends here
     * and waits for an event to occur (like a key press or
     * mouse event). */
    gtk_main ();
    
    return 0;
}
