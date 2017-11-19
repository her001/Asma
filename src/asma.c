// File: "asma.c"
// Author: Pau Busquets Aguiló

#include "asma.h"
#include "mods.h"
#include "prefs.h"

static GActionEntry app_entries[];

static void about_activated();
static void preferences_activated();
static void quit_activated();
static void init_builder();

static GActionEntry app_entries[3] = {
	{"about", about_activated, NULL, NULL, NULL},
	{"preferences", preferences_activated, NULL, NULL, NULL},
	{"quit", quit_activated, NULL, NULL, NULL},
};

static void about_activated(GSimpleAction *action,
			    GVariant *parameter,
			    gpointer user_data)
{
	GtkWindow *dialog;
	GtkApplication *app = user_data;

	dialog = GTK_WINDOW (gtk_builder_get_object(builder, "about_dialog"));
	gtk_window_set_application(dialog, app);

	gtk_window_present(dialog);
}

static void preferences_activated(GSimpleAction *action,
				  GVariant *parameter,
				  gpointer user_data)
{
	GtkWindow *prefs;
	GtkApplication *app = user_data;

	prefs = gtk_application_get_window_by_id(app, 2);

	gtk_window_present(prefs);
}

static void quit_activated(GSimpleAction *action,
			   GVariant *parameter,
			   gpointer user_data)
{
	GApplication *app = G_APPLICATION (user_data);
	g_application_quit(app);
}

void destroy(GtkWindow *window,
	     gpointer *user_data)
{
	GActionMap *am;
	GAction *action;

	am = G_ACTION_MAP (gtk_window_get_application(window));
	action = g_action_map_lookup_action(am, "quit");
	g_action_activate(action, NULL);
}

void browse_dir()
{
	GError *error = NULL;
	if (!g_app_info_launch_default_for_uri(g_file_get_uri(arma3_root), NULL, &error))
		g_warning("Browsing game folder failed: %s\n", error->message);
}

static void bind_settings()
{
	g_settings_bind(gset_a3, "game-path",
			gtk_builder_get_object(builder, "a3_dir_entry"),
			"text", G_SETTINGS_BIND_DEFAULT);
	g_settings_bind(gset_a3, "force-windowed",
			gtk_builder_get_object(builder, "a3_windowed_check"),
			"active", G_SETTINGS_BIND_DEFAULT);
	g_settings_bind(gset_a3, "show-splash",
			gtk_builder_get_object(builder, "a3_splash_check"),
			"active", G_SETTINGS_BIND_DEFAULT);
	g_settings_bind(gset_a3, "show-world",
			gtk_builder_get_object(builder, "a3_world_check"),
			"active", G_SETTINGS_BIND_DEFAULT);
	g_settings_bind(gset_a3, "show-script-errors",
			gtk_builder_get_object(builder, "a3_script_err_check"),
			"active", G_SETTINGS_BIND_DEFAULT);
	g_settings_bind(gset_a3, "file-patching",
			gtk_builder_get_object(builder, "a3_file_patching_check"),
			"active", G_SETTINGS_BIND_DEFAULT);
	g_object_set(gtk_settings_get_default(), "gtk-application-prefer-dark-theme",
		     g_settings_get_boolean(gset, "prefer-dark-theme"), NULL);
}

static void activate(GtkApplication *app)
{
	GtkWindow *window;
	GtkWindow *prefs;
	GtkWidget *placeholder;

	g_assert(GTK_IS_APPLICATION (app));

	init_builder();

	g_action_map_add_action_entries(G_ACTION_MAP (app),
					app_entries, G_N_ELEMENTS (app_entries),
					app);

	window = GTK_WINDOW (gtk_builder_get_object(builder, "app_window"));
	gtk_window_set_application(window, app);
	placeholder = GTK_WIDGET (gtk_builder_get_object(builder, "mods_placeholder"));
	gtk_widget_set_visible(placeholder, TRUE);
	gtk_list_box_set_placeholder(GTK_LIST_BOX (gtk_builder_get_object(builder, "mods_list")),
				     placeholder);
	prefs = GTK_WINDOW (gtk_builder_get_object(builder, "prefs_window"));
	gtk_window_set_application(prefs, app);
	gtk_window_set_transient_for(prefs, gtk_application_get_window_by_id(app, 1));

	gtk_builder_connect_signals(builder, NULL);
	bind_settings();
	gtk_window_present(window);
}

static void init_settings()
{
	gset = g_settings_new("io.github.her001.Asma");
	gset_a3 = g_settings_new("io.github.her001.Asma.arma3");
	g_signal_connect(gset_a3, "changed::game-path", G_CALLBACK (update_and_check_dir), NULL);
	update_root_dir(gset_a3, "game-path", NULL);
}

static void init_builder()
{
	builder = gtk_builder_new();
	gtk_builder_add_from_resource(builder, "/io/github/her001/Asma/asma.glade", NULL);
	gtk_builder_add_from_resource(builder, "/io/github/her001/Asma/preferences.glade", NULL);
	gtk_builder_add_from_resource(builder, "/io/github/her001/Asma/appmenu.ui", NULL);
}

int main(int argc, char* argv[])
{
	g_autoptr (GtkApplication) app;

	init_settings();

	app = gtk_application_new("io.github.her001.Asma",
		G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);

	return g_application_run(G_APPLICATION (app), argc, argv);
}

