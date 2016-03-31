// File: "addons.c"
// Author: Pau Busquets Aguiló
#include "addons.h"

 //////////////////////
// fnc create addon ////////////////////////////////////////////////////////////////////////////////
GtkWidget* fnc_create_addon( char* _name)
{
    widget = gtk_check_button_new_with_label( _name);
    g_signal_connect( G_OBJECT( widget), "toggled", G_CALLBACK( fnc_addon_event), NULL);
    gtk_container_add( GTK_CONTAINER( addonBox), widget);
    gtk_widget_show_all( addonBox);
    return widget;
}

//////////////////////
// fnc addon event ////////////////////////////////////////////////////////////////////////////////
static void fnc_addon_event( GtkToggleButton* _button)
{
    char* _name = g_strconcat( gtk_button_get_label( GTK_BUTTON( _button)), "\\\\;", NULL);
    if( gtk_toggle_button_get_active( _button))
    {
        i = 0;
        while( i != 50)
        {
            gtk_box_reorder_child( GTK_BOX( addonBox), GTK_WIDGET( _button), i);
            if( active_addons[i] == NULL)
            {
                active_addons[i] = _name;
                break;
            }
            i++;
        }
    }
    else
    {
        i = 0;
        while( i != 50)
        {
            if( active_addons[i] == NULL)
                break;
            if( strcmp( active_addons[i], _name) == 0)
            {
                ii = i;
                while( active_addons[ii] != NULL)
                {
                    active_addons[ii] = active_addons[ii+1];
                    ii++;
                }
            }
            i++;
        }
    }
    i = 0;
    active_addons_command = "";
    while( active_addons[i] != NULL)
    {
        active_addons_command = g_strconcat( active_addons_command, active_addons[i], NULL);
        i++;
    }
}
