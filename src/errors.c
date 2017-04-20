// File: "errors.c"
// Author: Pau Busquets Aguiló
#include "asma.h"
#include "errors.h"
#include "settings.h"

void fnc_error_nofolder()
{
  bar = gtk_info_bar_new_with_buttons( ( "_OK"), GTK_RESPONSE_OK, NULL);
  g_signal_connect( bar, "response", G_CALLBACK( evt_error_nofolder), NULL);
  gtk_info_bar_set_show_close_button( GTK_INFO_BAR( bar), TRUE);
  gtk_box_pack_end( GTK_BOX( rootBox), bar, FALSE, TRUE, 0);
  gtk_info_bar_set_message_type( GTK_INFO_BAR( bar), GTK_MESSAGE_QUESTION);
  label = gtk_label_new( "ERROR: default ARMA 3 folder not found. Set new one?");
  gtk_box_pack_start( GTK_BOX( gtk_info_bar_get_content_area( GTK_INFO_BAR( bar))), label, TRUE, TRUE, 0);
}


static void evt_error_nofolder( GtkInfoBar* _bar, gint _respose)
{
  if( _respose != GTK_RESPONSE_CLOSE)
  {
    fnc_set_addonFolder();
  }
  gtk_widget_destroy( GTK_WIDGET( _bar));
}
