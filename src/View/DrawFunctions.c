/******************************************************************/
/* DrawFunctions.c                                                */
/******************************************************************/

#include "DrawFunctions.h"

GtkWidget *drawMain(ViewHandle * MainViewHandle){
 ObjectHandle * NewObject;
 
 GtkWidget *window  = gtk_window_new(GTK_WINDOW_TOPLEVEL);
 NewObject = ObjectHandle_Initialize("MainWindow", window);
 HASH_ADD(HashByName, MainViewHandle->ObjectListByName, Name, sizeof(char) * MAX_HASH_KEY_LENGTH, NewObject);
 HASH_ADD(HashByWidget,MainViewHandle->ObjectListByWidget,Widget,sizeof(GtkWidget *),NewObject);
    
 gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
 gtk_window_set_default_size(GTK_WINDOW(window), 1000, 200);
 gtk_window_set_title(GTK_WINDOW(window), "OCR Program");
      
 g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

 return window;
}

GtkWidget *drawMenuBar(ViewHandle * MainViewHandle){
  ObjectHandle * NewObject;
  GtkWidget *menubar = gtk_menu_bar_new();
  GtkWidget *separator = gtk_separator_menu_item_new();
/*****************************************************************************************************************/
/*RYAN: here is an example of how you can add a new Widget to the data structure*/
/*The onlythinng you need to change is "NewName", NewGtkWidget*"*/
  AddWidgetToViewHandle(MainViewHandle, "MenuBar", menubar);
/*****************************************************************************************************************/  
  
  /* file options for menubar */
  GtkWidget  *filemenu = gtk_menu_new(),
    *file = gtk_menu_item_new_with_label("File"),
    *open = gtk_menu_item_new_with_label("Open"),
    *save = gtk_menu_item_new_with_label("Save"),
    *quit = gtk_menu_item_new_with_label("Quit");
  AddWidgetToViewHandle(MainViewHandle, "FileMenu", file);
  AddWidgetToViewHandle(MainViewHandle, "OpenFile", open);
  AddWidgetToViewHandle(MainViewHandle, "SaveFile", save);
  
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), save);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), separator);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);

  /* preprocessor options for menubar */
  GtkWidget *preProcMenu = gtk_menu_new(),
    *preProc       = gtk_menu_item_new_with_label("Preprocessing"),
    *convert       = gtk_menu_item_new_with_label("Convert to Black and White"),
    *removeStain   = gtk_menu_item_new_with_label("Stain Removal"),
    *removeWrinkle = gtk_menu_item_new_with_label("Wrinkle Removal"),
    *rotate        = gtk_menu_item_new_with_label("Rotate  (Level Image)"),
    *lineBound     = gtk_menu_item_new_with_label("Line Boundaries"),
    *crop          = gtk_menu_item_new_with_label("Crop  (Select OCR Region)");

  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), preProc);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(preProc), preProcMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), convert);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), removeStain);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), removeWrinkle);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), rotate);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), lineBound);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), crop);

  /* ocr options for menubar */
  GtkWidget *ocrMenu = gtk_menu_new(),
    *ocr        = gtk_menu_item_new_with_label("OCR"),    
    *performOCR =  gtk_menu_item_new_with_label("Perform OCR");

  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), ocr);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(ocr), ocrMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(ocrMenu), performOCR);

  /* postprocessing options for menubar */
  GtkWidget *postProcMenu = gtk_menu_new(),
    *postProc   = gtk_menu_item_new_with_label("Postprocessing"),
    *edit       = gtk_menu_item_new_with_label("Edit OCR Text Output"),
    *dictionary =  gtk_menu_item_new_with_label("Dictionary Settings");
 
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), postProc);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(postProc), postProcMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(postProcMenu), edit);
  gtk_menu_shell_append(GTK_MENU_SHELL(postProcMenu), dictionary);

  g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(gtk_main_quit), NULL);   
  
  
/*********************************************************************************************************/
/*RYAN: Here is an example of signal connect. You only need to change the first parameter G_OBJECT(_____)*/
  g_signal_connect(G_OBJECT(open), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(save), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
/*********************************************************************************************************/
  return menubar;
}
