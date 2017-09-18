// File: "settings.c"
// Author: Pau Busquets Aguiló
#include "asma.h"
#include "settings.h"

void fnc_set_addonFolder()
{
  action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
  native = gtk_file_chooser_native_new( "Open File",
                                        GTK_WINDOW( window),
                                        action,
                                        ( "_Open"),
                                        ( "_Cancel"));
  res = gtk_native_dialog_run( GTK_NATIVE_DIALOG( native));
  if( res == GTK_RESPONSE_ACCEPT)
  {
    chooser = GTK_FILE_CHOOSER( native);
    arma3_root = gtk_file_chooser_get_filename( chooser);
  }

  g_object_unref( native);
  call_refresh();
}
