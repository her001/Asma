#include "asma.h"
#include "launcher.h"

static gchar* mods_param()
{
	GObject *mods_box;
	GList *mods_l;
	gchar *param;

	mods_box = gtk_builder_get_object(builder, "mods_list");
	mods_l = gtk_container_get_children(GTK_CONTAINER (mods_box));

	param = "";
	while (mods_l) {
		GtkButton *b;
		b = GTK_BUTTON (gtk_bin_get_child(mods_l->data));
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b)))
			param = g_strconcat(param, gtk_button_get_label(b), "\\\\;", NULL);
		mods_l = mods_l->next;
	}

	if(!g_str_equal(param, ""))
		param = g_strconcat(A3_MOD, param, NULL);

	return param;
}

static gchar* get_command()
{
	gchar *command;

	command = DEFAULT_LAUNCH;
	if (g_settings_get_boolean(gset_a3, "force-windowed"))
		command = g_strconcat(command, A3_WINDOW, NULL);
	if (!g_settings_get_boolean(gset_a3, "show-splash"))
		command = g_strconcat(command, A3_NOSPLASH, NULL);
	if (!g_settings_get_boolean(gset_a3, "show-world"))
		command = g_strconcat(command, A3_NOWORLD, NULL);
	if (g_settings_get_boolean(gset_a3, "show-script-errors"))
		command = g_strconcat(command, A3_DEBUG, NULL);
	if (g_settings_get_boolean(gset_a3, "file-patching"))
		command = g_strconcat(command, A3_FILE_PATCHING, NULL);
	command = g_strconcat(command, mods_param(), NULL);

	return command;
}

void play_game()
{
	gchar *command;

	command = get_command();
	g_spawn_command_line_async(command, NULL);
}

