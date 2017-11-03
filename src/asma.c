// File: "asma.c"
// Author: Pau Busquets Aguiló

#include "asma.h"
#include "addons.h"
#include "errors.h"
#include "mods.h"
#include "settings.h"

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
	GtkBuilder *builder;
	GtkWindow *prefs;
	GtkApplication *app = user_data;

	builder = gtk_builder_new_from_resource(
		"/io/github/busquetsaguilopau/Asma/asma.glade");
	prefs = GTK_WINDOW (gtk_builder_get_object(builder, "prefs_window"));
	gtk_window_set_application(prefs, app);

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

void refresh_button()
{
	mods_refresh();
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

static void startup(GtkApplication *app)
{
	GtkBuilder *builder;
	GMenuModel *menu;

	g_assert(GTK_IS_APPLICATION (app));

	g_action_map_add_action_entries(G_ACTION_MAP (app),
					app_entries, G_N_ELEMENTS (app_entries),
					app);

	builder = gtk_builder_new_from_resource(
		"/io/github/busquetsaguilopau/Asma/gmenu.ui");
	menu = G_MENU_MODEL (gtk_builder_get_object(builder, "appmenu"));

	gtk_application_set_app_menu(app, menu);
}

static void activate(GtkApplication *app)
{
	GtkBuilder *builder;
	GtkWindow *window;

	g_assert(GTK_IS_APPLICATION (app));

	builder = gtk_builder_new_from_resource(
		"/io/github/busquetsaguilopau/Asma/asma.glade");
	gtk_builder_connect_signals(builder, NULL);

	window = GTK_WINDOW (gtk_builder_get_object(builder, "app_window"));
	gtk_window_set_application(window, app);

	gtk_window_present(window);
}

int main(int argc, char* argv[])
{
	gchar *path;
	g_autoptr (GtkApplication) app;

	gset = g_settings_new("io.github.busquetsaguilopau.Asma");
	path = g_settings_get_string(gset, "game-path");
	if (!g_path_is_absolute(path))
		path = g_strconcat(g_get_home_dir(), "/", path, NULL);
	arma3_root = g_file_new_for_path(path);

	app = gtk_application_new("io.github.busquetsaguilopau.Asma",
		G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "startup", G_CALLBACK (startup), NULL);
	g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);

	return g_application_run(G_APPLICATION (app), argc, argv);
}
