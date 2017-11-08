#include "asma.h"
#include "mods.h"
#include "prefs.h"

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

	bin = g_file_get_path(g_file_get_child(arma3_root, "arma3"));
	if (g_find_program_in_path(bin) == NULL) {
		//TODO
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
