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
	switch (response_id) {
	case 1:
		select_a3_folder(NULL, NULL);
		break;
	case 2:
		gtk_widget_destroy(GTK_WIDGET (info_bar));
		check_steam(TRUE);
		break;
	case GTK_RESPONSE_CLOSE:
		gtk_widget_destroy(GTK_WIDGET (info_bar));
	}
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
	gchar *button_message;
	GtkResponseType response;

	if (check_steam(FALSE)) {
		label = GTK_WIDGET (gtk_label_new(message));
		button_message = "_Select Folder";
		response = 1;
	} else {
		label = GTK_WIDGET (gtk_label_new("Steam not found! Please install Steam."));
		button_message = "_Done";
		response = 2;
	}

	app_box = GTK_BOX (gtk_builder_get_object(builder, "app_box"));
	bar = GTK_INFO_BAR (gtk_info_bar_new_with_buttons(button_message, response, NULL));
	clear_info_bar();

	gtk_box_pack_start(GTK_BOX (gtk_info_bar_get_content_area(bar)), label, FALSE, FALSE, 0);
	gtk_info_bar_set_message_type(bar, GTK_MESSAGE_WARNING);
	gtk_info_bar_set_show_close_button(bar, TRUE);
	g_signal_connect(GTK_WIDGET (bar), "response", G_CALLBACK (info_bar_response), NULL);

	gtk_box_pack_start(app_box, GTK_WIDGET (bar), FALSE, FALSE, 0);
	gtk_info_bar_set_default_response(bar, response);
	gtk_widget_show_all(GTK_WIDGET (bar));
}

gboolean check_steam(gboolean show_bar)
{
	GtkWidget *button;
	gboolean present;

	button = GTK_WIDGET (gtk_builder_get_object(builder, "play_button"));
	present = (g_find_program_in_path("steam") != NULL);
	if ((!present) && show_bar)
		show_info_bar("");
	gtk_widget_set_sensitive(button, present);
	return present;
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
	GtkWidget *dialog;
	GtkApplication *app;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
	gint res;
	app = gtk_builder_get_application(builder);
	dialog = gtk_file_chooser_dialog_new("Select Arma 3 Folder",
					     gtk_application_get_window_by_id(app, 1),
					     action,
					     ("_Cancel"),
					     GTK_RESPONSE_CANCEL,
					     ("_Open"),
					     GTK_RESPONSE_ACCEPT,
					     NULL);
	res = gtk_dialog_run(GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT) {
		GObject *e;
		gchar *path;
		e = gtk_builder_get_object(builder, "a3_dir_entry");
		path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (dialog));
		gtk_entry_set_text(GTK_ENTRY (e), path);
	}

	g_object_unref(dialog);
}

