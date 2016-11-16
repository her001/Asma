// File: "asma.c"
// Author: Pau Busquets Aguiló
#include "asma.h"
#include "addons.h"
#include "settings.h"
#include "errors.h"

  /********/
 /* MAIN */
/*************************************************************************************************/
int main( int argc, char* argv[])
{
  //config


  //def constants
  user_root = getenv( "HOME");
  arma3_root = g_strconcat( user_root, ARMA3_DEFAULT_PATH, NULL);
  a3_window = "";
  a3_nosplash = "";
  a3_world = "";
  a3_file_patching = "";
  a3_debug = "";
  a3_primus = "";

  //init
  gtk_init( &argc, &argv);
  g_object_set(gtk_settings_get_default(), "gtk-application-prefer-dark-theme", TRUE, NULL);

   ////////////
  // Window ///////////////////////////////////////////////////////////////////////////////////////
  window = gtk_window_new( GTK_WINDOW_TOPLEVEL);
  gtk_window_set_icon_from_file( GTK_WINDOW( window), "asma.png", NULL);
  gtk_window_set_title( GTK_WINDOW( window), "asma");
  g_signal_connect( G_OBJECT( window), "destroy", G_CALLBACK( call_quit), NULL);
  gtk_window_set_default_size( GTK_WINDOW( window), 600, 200);

   ////////////
  // Header ///////////////////////////////////////////////////////////////////////////////////////
  header = gtk_header_bar_new();
  gtk_header_bar_set_show_close_button( GTK_HEADER_BAR( header), TRUE);

  hBox = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_style_context_add_class( gtk_widget_get_style_context( hBox), "linked");
  gtk_header_bar_pack_start( GTK_HEADER_BAR( header), hBox);

  // play button
  button = gtk_button_new();
  g_signal_connect( G_OBJECT( button), "clicked", G_CALLBACK( call_launch), NULL);
  icon = g_themed_icon_new( "media-playback-start");
  image = gtk_image_new_from_gicon( icon, GTK_ICON_SIZE_BUTTON);
  g_object_unref( icon);
  gtk_container_add( GTK_CONTAINER ( button), image);
  gtk_container_add( GTK_CONTAINER ( hBox), button);

  // refresh button
  button = gtk_button_new();
  g_signal_connect( G_OBJECT( button), "clicked", G_CALLBACK( call_refresh), NULL);
  icon = g_themed_icon_new( "view-refresh");
  image = gtk_image_new_from_gicon( icon, GTK_ICON_SIZE_BUTTON);
  g_object_unref( icon);
  gtk_container_add( GTK_CONTAINER( button), image);
  gtk_container_add( GTK_CONTAINER( hBox), button);

  // open arma 3 folder button
  button = gtk_button_new();
  g_signal_connect( G_OBJECT( button), "clicked", G_CALLBACK( call_open_folder), NULL);
  icon = g_themed_icon_new( "folder");
  image = gtk_image_new_from_gicon( icon, GTK_ICON_SIZE_BUTTON);
  g_object_unref( icon);
  gtk_container_add( GTK_CONTAINER( button), image);
  gtk_container_add( GTK_CONTAINER( hBox), button);

  // Context Frame
  rootBox = gtk_box_new( GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add( GTK_CONTAINER( window), rootBox);

  hBox = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start( GTK_BOX( rootBox), hBox, TRUE, TRUE, 0);

   //////////////////
  // Settings Box /////////////////////////////////////////////////////////////////////////////////
  b_a3_window = gtk_toggle_button_new_with_label( "Windowed");
  g_signal_connect( G_OBJECT( b_a3_window), "toggled", G_CALLBACK( set_a3_window), NULL);
  b_a3_nosplash = gtk_toggle_button_new_with_label( "noSplash");
  g_signal_connect( G_OBJECT( b_a3_nosplash), "toggled", G_CALLBACK( set_a3_nosplash), NULL);
  b_a3_world = gtk_toggle_button_new_with_label( "noWorld");
  g_signal_connect( G_OBJECT( b_a3_world), "toggled", G_CALLBACK( set_a3_world), NULL);
  b_a3_file_patching = gtk_toggle_button_new_with_label( "FilePatching");
  g_signal_connect( G_OBJECT( b_a3_file_patching), "toggled", G_CALLBACK( set_a3_file_patching), NULL);
  b_a3_debug = gtk_toggle_button_new_with_label( "Debug");
  g_signal_connect( G_OBJECT( b_a3_debug), "toggled", G_CALLBACK( set_a3_debug), NULL);
  b_a3_primus = gtk_toggle_button_new_with_label( "Primus");
  g_signal_connect( G_OBJECT( b_a3_primus), "toggled", G_CALLBACK( set_a3_primus), NULL);

  vBox = gtk_box_new( GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_end( GTK_BOX( hBox), vBox, FALSE, FALSE, 1);
  gtk_container_add( GTK_CONTAINER( vBox), b_a3_window);
  gtk_container_add( GTK_CONTAINER( vBox), b_a3_nosplash);
  gtk_container_add( GTK_CONTAINER( vBox), b_a3_world);
  gtk_container_add( GTK_CONTAINER( vBox), b_a3_file_patching);
  gtk_container_add( GTK_CONTAINER( vBox), b_a3_debug);
  gtk_container_add( GTK_CONTAINER( vBox), b_a3_primus);

   ////////////////
  // Addons Box ///////////////////////////////////////////////////////////////////////////////////
  scrolled = gtk_scrolled_window_new( NULL, NULL);
  addonBox = gtk_box_new( GTK_ORIENTATION_VERTICAL, 0);

  gtk_box_pack_start( GTK_BOX( hBox), scrolled, TRUE, TRUE, 1);
  gtk_scrolled_window_set_policy( GTK_SCROLLED_WINDOW( scrolled), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
  gtk_container_add( GTK_CONTAINER( scrolled), addonBox);


   //////////////////////////////////
  // Container structure and loop /////////////////////////////////////////////////////////////////
  call_refresh();
  gtk_window_set_titlebar( GTK_WINDOW( window), header);
  gtk_widget_show_all( window);

  gtk_main();
  return 0;
}


   /**********/
  /* CALLS */
 /************************************************************************************************/

// quit call
static void call_quit()
{
  gtk_main_quit();
}

// launch call
static void call_launch()
{
    g_spawn_command_line_async(
        g_strconcat(
            DEFAULT_LAUNCH, a3_primus,
            a3_window, a3_nosplash, a3_world, a3_file_patching, a3_debug,
            A3_MOD, active_addons_command,
        NULL),
    NULL);

    puts(
        g_strconcat(
            DEFAULT_LAUNCH, a3_primus,
            a3_window, a3_nosplash, a3_world, a3_file_patching, a3_debug,
            A3_MOD, active_addons_command,
        NULL)
    );
}

// refresh call
void call_refresh()
{
    active_addons_command = "";
    i = 0;
    while( i != 50)
    {
        active_addons[i] = NULL;
        i++;
    }

    i = 0;
    while( i != 50)
    {
        if( current_addons[i] == NULL)
            break;
        gtk_widget_destroy( GTK_WIDGET( current_addons[i]));
        i++;
    }

    i = 0;
    directory = opendir( arma3_root);
    if( directory != NULL)
    {
      while( properities = readdir( directory))
      {
          if( strncmp( "@", properities->d_name, strlen( "@")) == 0)
          {
              current_addons[i] = fnc_create_addon( properities->d_name);
              i ++;
          }
      }
      ( void)closedir( directory);
    }
    else
      fnc_error_nofolder();
}

// open folder call
static void call_open_folder()
{
  system( g_strconcat( "xdg-open \"", arma3_root, "\"", NULL));
}

// set_a3_window call
static void set_a3_window( GtkToggleButton* _button)
{
    if( gtk_toggle_button_get_active( _button)) { a3_window = A3_WINDOW;}
    else{ a3_window = "";}
}

//set_a3_nosplash
static void set_a3_nosplash( GtkToggleButton* _button)
{
    if( gtk_toggle_button_get_active( _button)) { a3_nosplash = A3_NOSPLASH;}
    else{ a3_nosplash = "";}
}

//set_a3_world
static void set_a3_world( GtkToggleButton* _button)
{
    if( gtk_toggle_button_get_active( _button)) { a3_world = A3_WORLD;}
    else{ a3_world = "";}
}

//set_a3_file_patching
static void set_a3_file_patching( GtkToggleButton* _button)
{
    if( gtk_toggle_button_get_active( _button)) { a3_file_patching = A3_FILE_PATCHING;}
    else{ a3_file_patching = "";}
}

//set_a3_debug
static void set_a3_debug( GtkToggleButton* _button)
{
    if( gtk_toggle_button_get_active( _button)) { a3_debug = A3_DEBUG;}
    else{ a3_debug = "";}
}

//set_a3_primus
static void set_a3_primus( GtkToggleButton* _button)
{
    if( gtk_toggle_button_get_active( _button)) { a3_primus = A3_PRIMUS;}
    else{ a3_primus = "";}
}
