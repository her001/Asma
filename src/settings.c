// File: "settings.c"
// Author: Pau Busquets Aguiló
#include "asma.h"
#include "settings.h"

void fnc_set_addonFolder(GtkApplication *app)
{
  action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
  native = gtk_file_chooser_native_new( "Open File",
                                        gtk_application_get_active_window(app),
                                        action,
                                        ( "_Open"),
                                        ( "_Cancel"));
  res = gtk_native_dialog_run( GTK_NATIVE_DIALOG( native));
  if( res == GTK_RESPONSE_ACCEPT)
  {
    chooser = GTK_FILE_CHOOSER( native);
    arma3_root = g_file_new_for_path(gtk_file_chooser_get_filename(chooser));
    g_settings_set_string(gset, "game-path", g_file_get_path(arma3_root));
  }

  g_object_unref( native);
}
