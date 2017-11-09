#include "asma.h"
#include "mods.h"
#include "prefs.h"

static void destroy_bars(GtkWidget *widget,
			 gpointer data)
{
	if (GTK_IS_INFO_BAR(widget))
	    gtk_widget_destroy(widget);
}

static void info_bar_response(GtkInfoBar *info_bar,
                      gint        response_id,
		      gpointer    user_data)
{
	if (response_id != GTK_RESPONSE_OK)
		gtk_widget_destroy(GTK_WIDGET (info_bar));
	else
		select_a3_folder(NULL, NULL);
}

static void clear_info_bar()
{
	GtkContainer *app_box;

	app_box = GTK_CONTAINER (gtk_builder_get_object(builder, "app_box"));
	gtk_container_foreach(app_box, (GtkCallback) destroy_bars, NULL);
}

static void show_info_bar(gchar *message)
{
	GtkBox *app_box;
	GtkInfoBar *bar;
	GtkWidget *label;

	app_box = GTK_BOX (gtk_builder_get_object(builder, "app_box"));
	bar = GTK_INFO_BAR (gtk_info_bar_new_with_buttons("_Select Folder", GTK_RESPONSE_OK, NULL));
	label = GTK_WIDGET (gtk_label_new(message));
	clear_info_bar();

	gtk_box_pack_start(GTK_BOX (gtk_info_bar_get_content_area(bar)), label, FALSE, FALSE, 0);
	gtk_info_bar_set_message_type(bar, GTK_MESSAGE_WARNING);
	gtk_info_bar_set_show_close_button(bar, TRUE);
	g_signal_connect(GTK_WIDGET (bar), "response", G_CALLBACK (info_bar_response), NULL);

	gtk_box_pack_start(app_box, GTK_WIDGET (bar), FALSE, FALSE, 0);
	gtk_info_bar_set_default_response(bar, GTK_RESPONSE_OK);
	gtk_widget_show_all(GTK_WIDGET (bar));
}


void update_root_dir(GSettings *settings,
		      gchar *key,
		      gpointer user_data)
{
	gchar *path;

	g_settings_sync();
	path = g_settings_get_string(settings, key);
	if (!g_path_is_absolute(path))
		path = g_strconcat(g_get_home_dir(), "/", path, NULL);
	arma3_root = g_file_new_for_path(path);
}

void check_dir()
{
	gchar *bin;
	GtkWidget *browse;
	GtkWidget *refresh;

	browse = GTK_WIDGET (gtk_builder_get_object(builder, "browse_dir_button"));
	refresh = GTK_WIDGET (gtk_builder_get_object(builder, "refresh_button"));

	if (g_file_query_file_type(arma3_root, G_FILE_QUERY_INFO_NONE, NULL) != G_FILE_TYPE_DIRECTORY) {
		show_info_bar("Arma 3 folder not found.");
		gtk_widget_set_sensitive(browse, FALSE);
		gtk_widget_set_sensitive(refresh, FALSE);
	} else {
		gtk_widget_set_sensitive(browse, TRUE);
		bin = g_file_get_path(g_file_get_child(arma3_root, "arma3"));
		if (g_find_program_in_path(bin) == NULL) {
			show_info_bar("Arma 3 folder is invalid.");
			gtk_widget_set_sensitive(refresh, FALSE);
		} else {
			clear_info_bar();
			gtk_widget_set_sensitive(refresh, TRUE);
		}
	}
	mods_refresh();
}

void update_and_check_dir(GSettings *settings,
			  gchar *key,
			  gpointer user_data)
{
	update_root_dir(settings, key, user_data);
	check_dir();
}

void select_a3_folder(GtkButton *button,
		      gpointer user_data)
{
	GtkFileChooserNative *native;
	GtkApplication *app;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
	gint res;
	app = gtk_builder_get_application(builder);
	native = gtk_file_chooser_native_new("Select Arma 3 Folder",
					     gtk_application_get_active_window(app),
					     action,
					     ("_Open"),
					     ("_Cancel"));
	res = gtk_native_dialog_run(GTK_NATIVE_DIALOG (native));
	if (res == GTK_RESPONSE_ACCEPT) {
		GObject *e;
		gchar *path;
		e = gtk_builder_get_object(builder, "a3_dir_entry");
		path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (native));
		gtk_entry_set_text(GTK_ENTRY (e), path);
	}

	g_object_unref(native);
}

