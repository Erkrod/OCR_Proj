/******************************************************************/
/* DrawFunctions.c                                                */
/******************************************************************/
#include "View.h"

void drawAllWindows(ViewHandle * MainViewHandle){
	
  gtk_init(NULL, NULL);
  GtkWidget *window           = drawMain(MainViewHandle);  
  GtkWidget *menubar          = drawMenuBar(MainViewHandle);
  GtkWidget *vbox             = gtk_vbox_new(FALSE, 0);
  GtkWidget *hbox             = gtk_hbox_new(FALSE, 0);    
  GtkWidget *scrollWinImage   = drawImageWindow(MainViewHandle);
  GtkWidget *scrollWinText    = drawTextWindow(MainViewHandle);
  GtkWidget *rotateWindow     = drawRotateWindow(MainViewHandle);
  GtkWidget *cropWindow       = drawCropWindow(MainViewHandle);
  GtkWidget *filterWindow     = drawColorFilterWindow(MainViewHandle);
  GtkWidget *ocrWindow        = drawOCRWindow(MainViewHandle);


  gtk_container_add(GTK_CONTAINER(window), vbox);
  gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), scrollWinImage, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), scrollWinText, TRUE, TRUE, 0);
        
  
  /* show the window*/
  gtk_widget_show_all(window); 
  
  /*invisible all windows*/
  gtk_widget_hide(rotateWindow);
  gtk_widget_hide(cropWindow);
  gtk_widget_hide(filterWindow);
  gtk_widget_hide(ocrWindow);
				  
  
}

GtkWidget *drawMain(ViewHandle * MainViewHandle){
 GtkWidget *window  = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  AddWidgetToViewHandle(MainViewHandle, "MainWindow", window);
    
 gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
 gtk_window_set_default_size(GTK_WINDOW(window), 1000, 450);
 gtk_window_set_title(GTK_WINDOW(window), "OCR Program");
      
 g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

 return window;
}

GtkWidget *drawMenuBar(ViewHandle * MainViewHandle){

  
  GtkWidget *menubar = gtk_menu_bar_new();
  GtkWidget *separator = gtk_separator_menu_item_new();
  GtkWidget *separator2 = gtk_separator_menu_item_new();
  
  /* file options for menubar */
  GtkWidget  *filemenu = gtk_menu_new(),
    *file = gtk_menu_item_new_with_label("File"),
    *open = gtk_menu_item_new_with_label("Open"),
    *save = gtk_menu_item_new_with_label("Save"),
    *quit = gtk_menu_item_new_with_label("Quit");

  AddWidgetToViewHandle(MainViewHandle, "FileMenu", file);
  AddWidgetToViewHandle(MainViewHandle, "OpenFile", open);
  AddWidgetToViewHandle(MainViewHandle, "SaveFile", save);
  AddWidgetToViewHandle(MainViewHandle, "QuitProgram", quit);  

  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), save);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), separator);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);

  /* preprocessor options for menubar */
  GtkWidget *preProcMenu = gtk_menu_new(),
    *preProc       = gtk_menu_item_new_with_label("Preprocessing"),
    *undo          = gtk_menu_item_new_with_label("Undo"),
    *convert       = gtk_menu_item_new_with_label("Convert to Black and White"),
    *removeStain   = gtk_menu_item_new_with_label("Stain Removal"),
    *colorFilter   = gtk_menu_item_new_with_label("Color Filter"),
    *rotate        = gtk_menu_item_new_with_label("Rotate  (Level Image)"),
    *lineBound     = gtk_menu_item_new_with_label("Line Boundaries"),
    *crop          = gtk_menu_item_new_with_label("Crop  (Select OCR Region)");

  AddWidgetToViewHandle(MainViewHandle, "PreProcessMenu", preProcMenu);
  AddWidgetToViewHandle(MainViewHandle, "Preprocessing", preProc);
  AddWidgetToViewHandle(MainViewHandle, "UndoPreproc", undo);
  AddWidgetToViewHandle(MainViewHandle, "ConvertBW", convert);
  AddWidgetToViewHandle(MainViewHandle, "RemoveStain", removeStain);
  AddWidgetToViewHandle(MainViewHandle, "ColorFilter", colorFilter);
  AddWidgetToViewHandle(MainViewHandle, "Rotate", rotate);
  AddWidgetToViewHandle(MainViewHandle, "LineBoundary", lineBound);
  AddWidgetToViewHandle(MainViewHandle, "Crop", crop);

  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), preProc);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(preProc), preProcMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), undo);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), separator2);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), convert);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), removeStain);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), colorFilter);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), rotate);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), lineBound);
  gtk_menu_shell_append(GTK_MENU_SHELL(preProcMenu), crop);

  /* ocr options for menubar */
  GtkWidget *ocrMenu = gtk_menu_new(),
    *ocr        = gtk_menu_item_new_with_label("OCR"),    
    *performOCR =  gtk_menu_item_new_with_label("Perform OCR");

  AddWidgetToViewHandle(MainViewHandle, "OCRMenu", ocrMenu);
  AddWidgetToViewHandle(MainViewHandle, "OCR", ocr);
  AddWidgetToViewHandle(MainViewHandle, "PerformOCR", performOCR);

  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), ocr);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(ocr), ocrMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(ocrMenu), performOCR);

  /* postprocessing options for menubar */
  GtkWidget *postProcMenu = gtk_menu_new(),
    *postProc   = gtk_menu_item_new_with_label("Postprocessing"),
    *edit       = gtk_menu_item_new_with_label("Edit OCR Text Output"),
    *compile    = gtk_menu_item_new_with_label("Compile Code");
   
  AddWidgetToViewHandle(MainViewHandle, "PostProcMenu", postProcMenu);
  AddWidgetToViewHandle(MainViewHandle, "Postprocessing", postProc);
  AddWidgetToViewHandle(MainViewHandle, "EditText", edit);
  AddWidgetToViewHandle(MainViewHandle, "CompileCode", compile);

  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), postProc);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(postProc), postProcMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(postProcMenu), edit);
  gtk_menu_shell_append(GTK_MENU_SHELL(postProcMenu), compile);

  /* help options for menubar */
  GtkWidget *helpMenu = gtk_menu_new(),
    *help         = gtk_menu_item_new_with_label("Help"),
    *userManual   = gtk_menu_item_new_with_label("User Manual"),
    *about        = gtk_menu_item_new_with_label("About OCR");
 
  AddWidgetToViewHandle(MainViewHandle, "HelpMenu", helpMenu);
  AddWidgetToViewHandle(MainViewHandle, "Help", help);
  AddWidgetToViewHandle(MainViewHandle, "UserManual", userManual);
  AddWidgetToViewHandle(MainViewHandle, "About", about);

  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), helpMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(helpMenu), userManual);
  gtk_menu_shell_append(GTK_MENU_SHELL(helpMenu), about);

  g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(gtk_main_quit), NULL);   
  g_signal_connect(G_OBJECT(open), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(save), "activate", G_CALLBACK(CatchEvent), MainViewHandle);

  g_signal_connect(G_OBJECT(preProc), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(undo), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(convert), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(removeStain), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(colorFilter), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(rotate), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(lineBound), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(crop), "activate", G_CALLBACK(CatchEvent), MainViewHandle);  

  g_signal_connect(G_OBJECT(ocr), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(performOCR), "activate", G_CALLBACK(CatchEvent), MainViewHandle);

  g_signal_connect(G_OBJECT(postProc), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(edit), "activate", G_CALLBACK(CatchEvent), MainViewHandle);
  g_signal_connect(G_OBJECT(compile), "activate", G_CALLBACK(CatchEvent), MainViewHandle);

  g_signal_connect(G_OBJECT(about), "activate", G_CALLBACK(CatchEvent), MainViewHandle);

  return menubar;
}

void myprintf(GtkWidget *widget, GdkEvent *event, gpointer data){
	printf("here u go x = %lf; y = %lf\n", event->button.x, event->button.y);
}

GtkWidget *drawImageWindow(ViewHandle *MainViewHandle){

  GtkWidget *scrollWinImage;
  scrollWinImage = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollWinImage),
				 GTK_POLICY_ALWAYS,
				 GTK_POLICY_ALWAYS);
  AddWidgetToViewHandle(MainViewHandle, "ImageScrollWindow", scrollWinImage);
  
  GtkWidget * image = gtk_image_new();
  AddWidgetToViewHandle(MainViewHandle, "MainDisplayImage", image);
  /*gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollWinImage), image);*/
 
	/*reserved for beta release*/
   GtkWidget * event_box = gtk_event_box_new ();
   AddWidgetToViewHandle(MainViewHandle, "DisplayEventBox", event_box);
   gtk_widget_set_events (event_box, GDK_BUTTON_PRESS_MASK);
   gtk_container_add (GTK_CONTAINER (event_box), image);
   gtk_signal_connect (GTK_OBJECT(event_box), "button_press_event", GTK_SIGNAL_FUNC (CatchGdkEvent), MainViewHandle);
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollWinImage), event_box);  

  return scrollWinImage;
}

GtkWidget *drawTextWindow(ViewHandle *MainViewHandle){

  GtkWidget *scrollWinText;
  scrollWinText = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollWinText),
				 GTK_POLICY_ALWAYS,
				 GTK_POLICY_ALWAYS);
  AddWidgetToViewHandle(MainViewHandle, "TextScrollWindow", scrollWinText);
  
  GtkWidget * TextView = gtk_text_view_new ();
  gtk_text_view_set_editable(GTK_TEXT_VIEW(TextView), TRUE);
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(TextView), GTK_WRAP_WORD_CHAR);
  AddWidgetToViewHandle(MainViewHandle, "MainTextArea", TextView);
   gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollWinText), TextView);
  
  return scrollWinText;
}

GtkWidget *drawRotateWindow(ViewHandle * MainViewHandle){

 GtkWidget *rotateWin;    
 GtkWidget *vboxMain;
 GtkWidget *vbox;
 GtkWidget *vbox2;
 GtkWidget *hbox;    
 GtkWidget *frame;
 GtkWidget *spinner;
 GtkWidget *rotateButton;
 GtkWidget *closeButton;
 GtkWidget *label;
 GtkAdjustment *adj;
  
 rotateWin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 AddWidgetToViewHandle(MainViewHandle, "RotateWindow", rotateWin);
 gtk_window_set_default_size(GTK_WINDOW(rotateWin), 230, 100);
 g_signal_connect (rotateWin, "destroy",
		   G_CALLBACK (gtk_widget_hide),
		   rotateWin);

 gtk_window_set_title (GTK_WINDOW (rotateWin), "Rotate Image");
 
 vboxMain = gtk_vbox_new (FALSE, 5);
 AddWidgetToViewHandle(MainViewHandle, "RotateVbox1", vboxMain);
 gtk_container_set_border_width (GTK_CONTAINER (vboxMain), 10);
 gtk_container_add (GTK_CONTAINER (rotateWin), vboxMain);
 
 frame = gtk_frame_new ("Clockwise Rotation");
 AddWidgetToViewHandle(MainViewHandle, "RotateFrame", frame);
 gtk_box_pack_start (GTK_BOX (vboxMain), frame, TRUE, TRUE, 0);
 
 vbox = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "RotateVbox2", vbox);
 gtk_container_set_border_width (GTK_CONTAINER (vbox), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox);
 
 hbox = gtk_hbox_new (FALSE, 30);
 AddWidgetToViewHandle(MainViewHandle, "RotateHbox", hbox);
 gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 5);
 
 vbox2 = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "RotateVbox3", vbox2);
 gtk_box_pack_start (GTK_BOX (hbox), vbox2, FALSE, TRUE, 5);
 
 label = gtk_label_new ("Degrees :");
 AddWidgetToViewHandle(MainViewHandle, "RotateLabel", label);
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 gtk_box_pack_start (GTK_BOX (vbox2), label, FALSE, TRUE, 0);
 
 adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 1.0, 360.0, 1.0, 5.0, 0.0);

 spinner = gtk_spin_button_new (adj, 0, 0);
 AddWidgetToViewHandle(MainViewHandle, "RotateSpinner", spinner);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);
 gtk_box_pack_start (GTK_BOX (vbox2), spinner, FALSE, TRUE, 0);
 
 vbox2 = gtk_vbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), vbox2, FALSE, TRUE, 5);
 
 rotateButton = gtk_button_new_with_label ("Rotate");
 AddWidgetToViewHandle(MainViewHandle, "RotateButton", rotateButton);
 /* g_signal_connect(rotateButton, "clicked", */
 /* 		  G_CALLBACK (grab_int_value),    */
 /* 		  spinner); */
 g_signal_connect(G_OBJECT(rotateButton), "clicked", G_CALLBACK(CatchEvent), MainViewHandle);

 gtk_box_pack_start (GTK_BOX (vbox2), rotateButton, TRUE, TRUE, 5);
 
 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vboxMain), hbox, FALSE, TRUE, 0);
 
 closeButton = gtk_button_new_with_label ("Close");
 AddWidgetToViewHandle(MainViewHandle, "RotCloseButton", closeButton);
 g_signal_connect_swapped (closeButton, "clicked",
			    G_CALLBACK (gtk_widget_hide),
				rotateWin);
 gtk_box_pack_start (GTK_BOX (hbox), closeButton, TRUE, TRUE, 5);

 gtk_widget_show_all(rotateWin);

 return rotateWin;
}

GtkWidget *drawCropWindow(ViewHandle * MainViewHandle){

 GtkWidget *cropWin;
 GtkWidget *vboxMain, *vbox, *vbox2, *vbox3, *vbox4, *vbox5, *vbox6;
 GtkWidget *hbox, *hbox6;
 GtkWidget *spinner, *spinner2, *spinner3, *spinner4;
 GtkWidget *cropButton, *mouseButton1, *mouseButton2, *closeButton;
 GtkWidget *frame;
 GtkWidget *label;
 GtkAdjustment *adj;
  
 cropWin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 AddWidgetToViewHandle(MainViewHandle, "CropWindow", cropWin);
 gtk_window_set_default_size(GTK_WINDOW(cropWin), 230, 100);
 gtk_window_set_resizable (GTK_WINDOW(cropWin), FALSE);
 g_signal_connect (cropWin, "destroy",
 		   G_CALLBACK (gtk_widget_hide),
 		   cropWin);

 gtk_window_set_title (GTK_WINDOW (cropWin), "Crop Image");
 
 vboxMain = gtk_vbox_new (FALSE, 5);
 AddWidgetToViewHandle(MainViewHandle, "CropVboxMain", vboxMain);
 gtk_container_set_border_width (GTK_CONTAINER (vboxMain), 10);
 gtk_container_add (GTK_CONTAINER (cropWin), vboxMain);
 
 frame = gtk_frame_new (NULL);
 AddWidgetToViewHandle(MainViewHandle, "CropFrame", frame);
 gtk_box_pack_start (GTK_BOX (vboxMain), frame, TRUE, TRUE, 0);
 
 vbox = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "CropVbox", vbox);
 gtk_container_set_border_width (GTK_CONTAINER (vbox), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox);

 /* horizontal frame */
 frame = gtk_frame_new ("Coordinate 1");
 gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);
 
 vbox5 = gtk_vbox_new (FALSE, 10);
 gtk_container_set_border_width (GTK_CONTAINER (vbox5), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox5);
 hbox = gtk_hbox_new (FALSE, 30);
 gtk_box_pack_start (GTK_BOX (vbox5), hbox, TRUE, TRUE, 0);

 label = gtk_label_new ("X1 :");
 AddWidgetToViewHandle(MainViewHandle, "Croplabel", label);
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 
 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 10000.0, 1.0, 5.0, 0.0);

 spinner = gtk_spin_button_new (adj, 0, 0);
 AddWidgetToViewHandle(MainViewHandle, "CropSpin", spinner);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 vbox2 = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "CropVbox2", vbox2);
 gtk_box_pack_start (GTK_BOX (hbox), vbox2, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox2), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox2), spinner, TRUE, TRUE, 0);

 label = gtk_label_new ("Y1 :");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 
 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 10000.0, 1.0, 5.0, 0.0);

 spinner2 = gtk_spin_button_new (adj, 0, 0);
 AddWidgetToViewHandle(MainViewHandle, "CropSpin2", spinner2);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner2), TRUE);

 vbox3 = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "CropVbox3", vbox3);
 gtk_box_pack_start (GTK_BOX (hbox), vbox3, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox3), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox3), spinner2, TRUE, TRUE, 0);

 vbox2 = gtk_vbox_new (FALSE, 8);
 gtk_box_pack_start (GTK_BOX (vbox5), vbox2, TRUE, TRUE, 5);

 mouseButton1 = gtk_button_new_with_label ("Select Coordinate 1 with Mouse");
 AddWidgetToViewHandle(MainViewHandle, "CropCoord1", mouseButton1);
 g_signal_connect(G_OBJECT(mouseButton1), "clicked", G_CALLBACK(CatchEvent), MainViewHandle);
 gtk_box_pack_start (GTK_BOX (vbox2), mouseButton1, TRUE, TRUE, 5);

 /* vertical frame */
 frame = gtk_frame_new ("Coordinate 2");
 gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 10);

 vbox6 = gtk_vbox_new (FALSE, 10);
 gtk_container_set_border_width (GTK_CONTAINER (vbox6), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox6);
 hbox6 = gtk_hbox_new (FALSE, 30);
 gtk_box_pack_start (GTK_BOX (vbox6), hbox6, TRUE, TRUE, 0);

 label = gtk_label_new ("X2 :");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 
 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 10000.0, 1.0, 5.0, 0.0);

 spinner3 = gtk_spin_button_new (adj, 0, 0);
 AddWidgetToViewHandle(MainViewHandle, "CropSpin3", spinner3);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner3), TRUE);

 vbox3 = gtk_vbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (hbox6), vbox3, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox3), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox3), spinner3, TRUE, TRUE, 0);

 label = gtk_label_new ("Y2 :");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 
 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 10000.0, 1.0, 5.0, 0.0);

 spinner4 = gtk_spin_button_new (adj, 0, 0);
 AddWidgetToViewHandle(MainViewHandle, "CropSpin4", spinner4);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner4), TRUE);

 vbox4 = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "CropVbox4", vbox4);
 gtk_box_pack_start (GTK_BOX (hbox6), vbox4, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox4), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox4), spinner4, TRUE, TRUE, 0);

 vbox2 = gtk_vbox_new (FALSE, 8);
 gtk_box_pack_start (GTK_BOX (vbox6), vbox2, TRUE, TRUE, 5);

 mouseButton2 = gtk_button_new_with_label ("Select Coordinate 2 with Mouse");
 AddWidgetToViewHandle(MainViewHandle, "CropCoord2", mouseButton2);
 g_signal_connect(G_OBJECT(mouseButton2), "clicked", G_CALLBACK(CatchEvent), MainViewHandle);
 gtk_box_pack_start (GTK_BOX (vbox2), mouseButton2, TRUE, TRUE, 5);

 /* crop button */
 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, TRUE, 0);

 cropButton = gtk_button_new_with_label ("Crop");
 gtk_widget_set_size_request(cropButton, 125, 25);
 AddWidgetToViewHandle(MainViewHandle, "CropButton", cropButton);
 /* g_signal_connect(cropButton, "clicked", */
 /* 		  G_CALLBACK (gtk_widget_destroy), /\* temporary, need to fix *\/ */
 /* 		  spinner); */
 g_signal_connect(G_OBJECT(cropButton), "clicked", G_CALLBACK(CatchEvent), MainViewHandle);
 gtk_box_pack_start (GTK_BOX (hbox), cropButton, FALSE, TRUE, 60);

 /* close button */
 closeButton = gtk_button_new_with_label ("Close");
 gtk_widget_set_size_request(closeButton, 80, 25);
 AddWidgetToViewHandle(MainViewHandle, "CropCloseButton", closeButton);
 g_signal_connect_swapped (closeButton, "clicked",
 			   G_CALLBACK (gtk_widget_hide),
 		   cropWin);
 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vboxMain), hbox, TRUE, TRUE, 0);
 gtk_box_pack_end (GTK_BOX (hbox), closeButton, FALSE, FALSE, 5);

 gtk_widget_show_all(cropWin); 

 return cropWin;
}

GtkWidget *drawColorFilterWindow(ViewHandle * MainViewHandle){

 GtkWidget *filterWin;
 GtkWidget *vboxMain, *vbox, *vbox2, *vbox3, *hbox;
 GtkWidget *frame;
 /* GtkWidget *radio1, *radio2; */
 GtkWidget *spinner;
 GtkWidget *filterButton, *closeButton;
 GtkWidget *label;
 GtkAdjustment *adj;
  
 filterWin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 AddWidgetToViewHandle(MainViewHandle, "ColorFilterWindow", filterWin);
 gtk_window_set_default_size(GTK_WINDOW(filterWin), 230, 100);
 gtk_window_set_resizable (GTK_WINDOW(filterWin), FALSE);
 g_signal_connect (filterWin, "destroy",
 		   G_CALLBACK (gtk_main_quit),
 		   NULL);

 gtk_window_set_title (GTK_WINDOW (filterWin), "Color Filter");
 
 vboxMain = gtk_vbox_new (FALSE, 5);
 AddWidgetToViewHandle(MainViewHandle, "vboxMain", vboxMain);
 gtk_container_set_border_width (GTK_CONTAINER (vboxMain), 10);
 gtk_container_add (GTK_CONTAINER (filterWin), vboxMain);
 
 frame = gtk_frame_new (NULL);
 AddWidgetToViewHandle(MainViewHandle, "frame", frame);
 gtk_box_pack_start (GTK_BOX (vboxMain), frame, TRUE, TRUE, 0);
 
 vbox = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "vbox", vbox);
 gtk_container_set_border_width (GTK_CONTAINER (vbox), 8);
 gtk_container_add (GTK_CONTAINER (frame), vbox);

 /* reference point frame */
 frame = gtk_frame_new ("Reference Point");
 gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);

 hbox = gtk_hbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "hbox", hbox);

 gtk_container_set_border_width (GTK_CONTAINER (hbox), 15);
 gtk_container_add (GTK_CONTAINER (frame), hbox);

 label = gtk_label_new ("X:    ");
 AddWidgetToViewHandle(MainViewHandle, "label", label);
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 10000.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 AddWidgetToViewHandle(MainViewHandle, "spinner", spinner);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);
 label = gtk_label_new ("           ");
 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);

 label = gtk_label_new ("Y:    ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 10000.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);

 /* filter area frame */
 frame = gtk_frame_new ("Filter Area");
 gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 10);
 vbox2 = gtk_vbox_new (FALSE, 0);

 AddWidgetToViewHandle(MainViewHandle, "vbox2", vbox2);
 gtk_container_set_border_width (GTK_CONTAINER (vbox2), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox2);

 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vbox2), hbox, TRUE, TRUE, 0);

 label = gtk_label_new ("X1:  ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 10000.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);

 label = gtk_label_new ("           ");
 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);

 label = gtk_label_new ("Y1:  ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 10000.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);

 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vbox2), hbox, TRUE, TRUE, 10);

 label = gtk_label_new ("X2:  ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 10000.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);

 label = gtk_label_new ("           ");
 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);

 label = gtk_label_new ("Y2:  ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 10000.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);

 /* color attributes frame */
 frame = gtk_frame_new ("Color Attributes");
 gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);

 vbox3 = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "vbox3", vbox3);
 gtk_container_set_border_width (GTK_CONTAINER (vbox3), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox3);

 /* radio1 = gtk_radio_button_new_with_label(NULL, "Make Pixel Black"); */
 /* AddWidgetToViewHandle(MainViewHandle, "Radio1", radio1); */
 /* g_signal_connect(G_OBJECT(radio1), "clicked", G_CALLBACK(CatchEvent), MainViewHandle); */
 /* radio2 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio1), */
 /* 						       "Make Pixel White"); */
 /* AddWidgetToViewHandle(MainViewHandle, "Radio2", radio2); */
 /* g_signal_connect(G_OBJECT(radio2), "clicked", G_CALLBACK(CatchEvent), MainViewHandle); */

 /* gtk_box_pack_start (GTK_BOX (vbox3), radio1, TRUE, TRUE, 0); */
 /* gtk_box_pack_start (GTK_BOX (vbox3), radio2, FALSE, TRUE, 0); */

 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vbox3), hbox, TRUE, TRUE, 0);
 
 label = gtk_label_new ("New Pixel Value:  ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 10000.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);

 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vbox3), hbox, TRUE, TRUE, 10);
 
 label = gtk_label_new ("Threshold Value:  ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 10000.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);

 /* color filter button */
 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 10);

 filterButton = gtk_button_new_with_label ("Apply Color Filter");
 gtk_widget_set_size_request(filterButton, 200, 25);
 AddWidgetToViewHandle(MainViewHandle, "FilterButton", filterButton);
 /* g_signal_connect(filterButton, "clicked", */
 /* 		  G_CALLBACK (gtk_widget_destroy), */
 /* 		  spinner); */
 g_signal_connect(G_OBJECT(filterButton), "clicked", G_CALLBACK(CatchEvent), MainViewHandle);
 gtk_box_pack_start (GTK_BOX (hbox), filterButton, TRUE, TRUE, 5);

 /* close button */
 closeButton = gtk_button_new_with_label ("Close");
 gtk_widget_set_size_request(closeButton, 80, 25);
 AddWidgetToViewHandle(MainViewHandle, "CloseButton", closeButton);
 g_signal_connect_swapped (closeButton, "clicked",
 			   G_CALLBACK (gtk_widget_destroy),
 			   filterWin);
 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vboxMain), hbox, TRUE, TRUE, 0);
 gtk_box_pack_end (GTK_BOX (hbox), closeButton, FALSE, FALSE, 5);

 gtk_widget_show_all(filterWin); 

 return filterWin;
}

GtkWidget *drawStainRemoveWindow(ViewHandle * MainViewHandle){

 GtkWidget *stainWin;
 GtkWidget *vboxMain, *vbox;
 GtkWidget *hbox;
 GtkWidget *frame;
 GtkWidget *spinner;
 GtkWidget *stainButton, *closeButton;
 GtkWidget *label;
 GtkAdjustment *adj;

 stainWin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 AddWidgetToViewHandle(MainViewHandle, "RemoveStainWin", stainWin);
 gtk_window_set_default_size(GTK_WINDOW(stainWin), 500, 100);
 gtk_window_set_resizable (GTK_WINDOW(stainWin), FALSE);
 g_signal_connect (stainWin, "destroy",
 		   G_CALLBACK (gtk_main_quit),
 		   NULL);
 gtk_window_set_title (GTK_WINDOW (stainWin), "Stain Removal");

 vboxMain = gtk_vbox_new (FALSE, 5);
 AddWidgetToViewHandle(MainViewHandle, "vboxMain", vboxMain);
 gtk_container_set_border_width (GTK_CONTAINER (vboxMain), 10);
 gtk_container_add (GTK_CONTAINER (stainWin), vboxMain);

 frame = gtk_frame_new (NULL);
 AddWidgetToViewHandle(MainViewHandle, "StainFrame", frame);
 gtk_box_pack_start (GTK_BOX (vboxMain), frame, TRUE, TRUE, 0);
 
 vbox = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "StainVbox", vbox);
 gtk_container_set_border_width (GTK_CONTAINER (vbox), 8);
 gtk_container_add (GTK_CONTAINER (frame), vbox);

 /* channel variance 1 selection */
 hbox = gtk_hbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "StainHbox", hbox);
 gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 10);
 
 label = gtk_label_new ("Channel Variance 1:");
 AddWidgetToViewHandle(MainViewHandle, "StainLabel", label);
 gtk_widget_set_size_request(label, 50, 25);
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 255.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 AddWidgetToViewHandle(MainViewHandle, "Var1Spinner", spinner);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);

 /* channel variance 2 selection */
 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 10);
 
 label = gtk_label_new ("Channel Variance 2:  ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 255.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 AddWidgetToViewHandle(MainViewHandle, "Var2Spinner", spinner);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);

 /* brightness selection */
 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 10);
 
 label = gtk_label_new ("Brightness Threshold:      ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 255.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 AddWidgetToViewHandle(MainViewHandle, "BrightSpinner", spinner);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);

 /* darken limiter selectio */
 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 10);
 
 label = gtk_label_new ("Darken Limiter:  ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

 adj = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 255.0, 1.0, 5.0, 0.0);
 spinner = gtk_spin_button_new (adj, 0, 0);
 AddWidgetToViewHandle(MainViewHandle, "DarkenSpinner", spinner);
 gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinner), TRUE);

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), spinner, FALSE, TRUE, 0);

 /* remove stain button */
 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 15);

 stainButton = gtk_button_new_with_label ("Apply Stain Removal");
 /* gtk_widget_set_size_request(stainButton, 200, 25); */
 AddWidgetToViewHandle(MainViewHandle, "RemoveStainButton", stainButton);
 /* g_signal_connect(ocrButton, "clicked", */
 /* 		  G_CALLBACK (gtk_widget_destroy), */
 /* 		  ocrWin); */
 g_signal_connect(G_OBJECT(stainButton), "clicked", G_CALLBACK(CatchEvent), MainViewHandle);
 gtk_box_pack_start (GTK_BOX (hbox), stainButton, FALSE, FALSE, 35);

 /* close button */
 closeButton = gtk_button_new_with_label ("Close");
 gtk_widget_set_size_request(closeButton, 80, 25);
 AddWidgetToViewHandle(MainViewHandle, "StainCloseButton", closeButton);
 /* g_signal_connect_swapped (closeButton, "clicked", */
 /* 			   G_CALLBACK (gtk_widget_destroy), */
 /* 			   ocrWin); */
 g_signal_connect_swapped (closeButton, "clicked",
 			   G_CALLBACK (gtk_widget_destroy),
 			   stainWin);

 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vboxMain), hbox, TRUE, TRUE, 0);
 gtk_box_pack_end (GTK_BOX (hbox), closeButton, FALSE, FALSE, 5);

 gtk_widget_show_all(stainWin); 

 return stainWin;
}

GtkWidget *drawOCRWindow(ViewHandle * MainViewHandle){

 GtkWidget *ocrWin;
 GtkWidget *vboxMain, *vbox, *vbox2;
 GtkWidget *hbox, *hbox2, *hboxMain;
 GtkWidget *radio1, *radio2;
 GtkWidget *frame;
 GtkWidget *combo;
 GtkWidget *ocrButton, *previewButton, *closeButton;
 GtkWidget *label;

 ocrWin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 AddWidgetToViewHandle(MainViewHandle, "OCRWindow", ocrWin);
 gtk_window_set_default_size(GTK_WINDOW(ocrWin), 230, 100);
 g_signal_connect (ocrWin, "destroy",
 		   G_CALLBACK (gtk_main_quit),
 		   NULL);
 gtk_window_set_title (GTK_WINDOW (ocrWin), "OCR");
 
 vboxMain = gtk_vbox_new (FALSE, 5);
 AddWidgetToViewHandle(MainViewHandle, "vboxMain", vboxMain);
 gtk_container_set_border_width (GTK_CONTAINER (vboxMain), 10);
 gtk_container_add (GTK_CONTAINER (ocrWin), vboxMain);
 
 frame = gtk_frame_new(NULL);
 AddWidgetToViewHandle(MainViewHandle, "frame", frame);
 gtk_box_pack_start(GTK_BOX(vboxMain), frame, TRUE, TRUE, 0);

 vbox = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "vbox", vbox);
 gtk_container_set_border_width (GTK_CONTAINER (vbox), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox);

 hboxMain = gtk_hbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "hboxMain", hboxMain);
 gtk_box_pack_start (GTK_BOX (vbox), hboxMain, TRUE, TRUE, 0);

 /* character frame */
 frame = gtk_frame_new ("Character Attributes");
 gtk_box_pack_start (GTK_BOX (hboxMain), frame, TRUE, TRUE, 0);

 vbox2 = gtk_vbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "vbox2", vbox2);
 gtk_container_set_border_width (GTK_CONTAINER (vbox2), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox2);

 /* Font */
 hbox = gtk_hbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "hbox", hbox);
 gtk_box_pack_start (GTK_BOX (vbox2), hbox, TRUE, TRUE, 0);

 label = gtk_label_new ("Font:");
 AddWidgetToViewHandle(MainViewHandle, "label", label);
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 
 combo = gtk_combo_box_new_text();
 AddWidgetToViewHandle(MainViewHandle, "FontComboBox", combo);
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "Courier New" );
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "Lucida Console" );

 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox), combo, FALSE, TRUE, 0);

 /* Font Size */
 hbox2 = gtk_hbox_new (FALSE, 0);
 AddWidgetToViewHandle(MainViewHandle, "hbox2", hbox2);
 gtk_box_pack_start (GTK_BOX (vbox2), hbox2, TRUE, TRUE, 0);

 label = gtk_label_new ("Font Size:");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 
 combo = gtk_combo_box_new_text();
 AddWidgetToViewHandle(MainViewHandle, "FontSizeComboBox", combo);
 gtk_widget_set_size_request(GTK_WIDGET(combo), 72, -1);
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "10" );
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "12" );

 gtk_box_pack_start (GTK_BOX (hbox2), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox2), combo, FALSE, TRUE, 0);

 /* Font Resolution */
 hbox2 = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vbox2), hbox2, TRUE, TRUE, 0);

 label = gtk_label_new ("Scan Resolution:  ");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 
 combo = gtk_combo_box_new_text();
 AddWidgetToViewHandle(MainViewHandle, "ScanResComboBox", combo);
 gtk_widget_set_size_request(GTK_WIDGET(combo), 72, -1);
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "200 DPI" );
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "300 DPI" );

 gtk_box_pack_start (GTK_BOX (hbox2), label, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (hbox2), combo, FALSE, TRUE, 0);

 frame = gtk_frame_new("Character Isolation");
 gtk_box_pack_start(GTK_BOX(hboxMain), frame, TRUE, TRUE, 0);

 vbox2 = gtk_vbox_new (FALSE, 0);
 gtk_container_set_border_width (GTK_CONTAINER (vbox2), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox2);

 radio1 = gtk_radio_button_new_with_label(NULL, "Lazy Algorithm");
 radio2 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio1),
 						       "Active Algorithm");

 AddWidgetToViewHandle(MainViewHandle, "LazyRadio", radio1);
 AddWidgetToViewHandle(MainViewHandle, "ActiveRadio", radio2);
 
 gtk_box_pack_start (GTK_BOX (vbox2), radio1, TRUE, TRUE, 0);
 gtk_box_pack_start (GTK_BOX (vbox2), radio2, FALSE, TRUE, 0);

 previewButton = gtk_button_new_with_label ("Preview Isolate");
 AddWidgetToViewHandle(MainViewHandle, "PreviewIsolate", previewButton);
 g_signal_connect(previewButton, "clicked",
 		  G_CALLBACK (gtk_widget_destroy),
 		  ocrWin);
 gtk_box_pack_start (GTK_BOX (vbox2), previewButton, TRUE, TRUE, 5);

 /* post processing frame */
 frame = gtk_frame_new("Post Processing");
 gtk_box_pack_start(GTK_BOX(vbox), frame, TRUE, TRUE, 10);

 vbox2 = gtk_vbox_new (FALSE, 0);
 gtk_container_set_border_width (GTK_CONTAINER (vbox2), 15);
 gtk_container_add (GTK_CONTAINER (frame), vbox2);

 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vbox2), hbox, TRUE, TRUE, 0);

 label = gtk_label_new ("                   ");
 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);

 label = gtk_label_new ("Use Dictionary:");
 gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);

 combo = gtk_combo_box_new_text();
 AddWidgetToViewHandle(MainViewHandle, "DictionaryCombo", combo);
 gtk_widget_set_size_request(GTK_WIDGET(combo), 72, -1);
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "Yes" );
 gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "No" );

 gtk_box_pack_start (GTK_BOX (hbox), combo, FALSE, TRUE, 0);
 label = gtk_label_new ("                   ");
 gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);

 /* ocr button */
 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 0);

 ocrButton = gtk_button_new_with_label ("Perform OCR");
 gtk_widget_set_size_request(ocrButton, 200, 25);
 AddWidgetToViewHandle(MainViewHandle, "OCRButton", ocrButton);
 /* g_signal_connect(ocrButton, "clicked", */
 /* 		  G_CALLBACK (gtk_widget_destroy), */
 /* 		  ocrWin); */
 g_signal_connect(G_OBJECT(ocrButton), "clicked", G_CALLBACK(CatchEvent), MainViewHandle);
 gtk_box_pack_start (GTK_BOX (hbox), ocrButton, FALSE, FALSE, 100);

 /* close button */
 closeButton = gtk_button_new_with_label ("Close");
 gtk_widget_set_size_request(closeButton, 80, 25);
 AddWidgetToViewHandle(MainViewHandle, "CloseButton", closeButton);
 /* g_signal_connect_swapped (closeButton, "clicked", */
 /* 			   G_CALLBACK (gtk_widget_destroy), */
 /* 			   ocrWin); */
 g_signal_connect_swapped (closeButton, "clicked",
 			   G_CALLBACK (gtk_widget_destroy),
 			   ocrWin);

 hbox = gtk_hbox_new (FALSE, 0);
 gtk_box_pack_start (GTK_BOX (vboxMain), hbox, TRUE, TRUE, 0);
 gtk_box_pack_end (GTK_BOX (hbox), closeButton, FALSE, FALSE, 5);

 gtk_widget_show_all(ocrWin); 

 return ocrWin;
}

GtkWidget *drawAboutWindow(ViewHandle * MainViewHandle){

  /* GtkWidget *aboutWin; */
  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("Images/ocrMedium.png", NULL);
  GtkWidget *dialog = gtk_about_dialog_new();

  gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), "OCR");
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "1.0"); 
  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), 
				 "Quan Chau\nHanchel Cheng\nKevin Duong\n"
				 "Jamie Lee\nRyan Morrison\nEric Rodriguez\nAndrew Trinh");
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), 
				"OCR is a tool for image processing,"
				"optical character recognition, and text editing.");

  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
  gtk_dialog_run(GTK_DIALOG (dialog));
  gtk_widget_destroy(dialog);

  return dialog;
}
