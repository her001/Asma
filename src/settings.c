// File: "settings.c"
// Author: Pau Busquets Aguiló
#include "asma.h"
#include "settings.h"

void fnc_set_addonFolder()
{
  action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
  dialog = gtk_file_chooser_dialog_new( "Open File",
                                        GTK_WINDOW( window),
                                        action,
                                        ( "_Cancel"),
                                        GTK_RESPONSE_CANCEL,
                                        ( "_Open"),
                                        GTK_RESPONSE_ACCEPT,
                                        NULL);
  res = gtk_dialog_run( GTK_DIALOG( dialog));
  if( res == GTK_RESPONSE_ACCEPT)
  {
    chooser = GTK_FILE_CHOOSER( dialog);
    arma3_root = gtk_file_chooser_get_filename( chooser);
  }

  gtk_widget_destroy( dialog);
  call_refresh();
}
