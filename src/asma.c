// File: "asma.c"
// Author: Pau Busquets Aguiló

#include "asma.h"
#include "addons.h"
#include "errors.h"
#include "mods.h"
#include "settings.h"
#include "prefs.h"

static GActionEntry app_entries[];

static void about_activated();
static void preferences_activated();
static void quit_activated();

static GActionEntry app_entries[3] = {
	{"about", about_activated, NULL, NULL, NULL},
	{"preferences", preferences_activated, NULL, NULL, NULL},
	{"quit", quit_activated, NULL, NULL, NULL},
};

static void about_activated(GSimpleAction *action,
			    GVariant *parameter,
			    gpointer user_data)
{
	GtkBuilder *builder;
	GtkWindow *dialog;
	GtkApplication *app = user_data;

	builder = gtk_builder_new_from_resource(
		"/io/github/busquetsaguilopau/Asma/asma.glade");
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
	GtkApplication *app = user_data;
	GtkWidget *win;
	GList *list, *next;

	list = gtk_application_get_windows(app);
	while (list) {
		win = list->data;
		next = list->next;

		gtk_widget_destroy(win);

		list = next;
	}
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

void check_dir()
{
	gchar *bin;

	bin = g_strconcat(g_file_get_path(arma3_root), "/arma3", NULL);
	if (g_find_program_in_path(bin) == NULL)
		return; //TODO
}

static void bind_settings(GtkBuilder *builder)
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

static void startup(GtkApplication *app)
{
	GtkBuilder *builder;
	GMenuModel *menu;

	g_assert(GTK_IS_APPLICATION (app));

	g_action_map_add_action_entries(G_ACTION_MAP (app),
					app_entries, G_N_ELEMENTS (app_entries),
					app);

	builder = gtk_builder_new_from_resource(
		"/io/github/busquetsaguilopau/Asma/appmenu.ui");
	menu = G_MENU_MODEL (gtk_builder_get_object(builder, "appmenu"));

	gtk_application_set_app_menu(app, menu);
}

static void activate(GtkApplication *app)
{
	GtkBuilder *builder;
	GtkWindow *window;
	GtkWindow *prefs;

	g_assert(GTK_IS_APPLICATION (app));

	builder = gtk_builder_new();
	gtk_builder_add_from_resource(builder, "/io/github/busquetsaguilopau/Asma/asma.glade", NULL);
	gtk_builder_add_from_resource(builder, "/io/github/busquetsaguilopau/Asma/preferences.glade", NULL);
	gtk_builder_connect_signals(builder, NULL);

	window = GTK_WINDOW (gtk_builder_get_object(builder, "app_window"));
	gtk_window_set_application(window, app);
	prefs = GTK_WINDOW (gtk_builder_get_object(builder, "prefs_window"));
	gtk_window_set_application(prefs, app);
	gtk_window_set_transient_for(prefs, gtk_application_get_window_by_id(app, 1));

	bind_settings(builder);
	gtk_window_present(window);
}

static void init_settings()
{
	gset = g_settings_new("io.github.busquetsaguilopau.Asma");
	gset_a3 = g_settings_new("io.github.busquetsaguilopau.Asma.arma3");
	g_signal_connect(gset_a3, "changed::game-path", G_CALLBACK (update_root_file), NULL);
	update_root_file(gset_a3, "game-path", NULL);
}

int main(int argc, char* argv[])
{
	g_autoptr (GtkApplication) app;

	init_settings();

	app = gtk_application_new("io.github.busquetsaguilopau.Asma",
		G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "startup", G_CALLBACK (startup), NULL);
	g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);

	return g_application_run(G_APPLICATION (app), argc, argv);
}
