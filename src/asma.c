// File: "asma.c"
// Author: Pau Busquets Aguiló

#include "asma.h"
#include "addons.h"
#include "errors.h"
#include "settings.h"

static void startup(GtkApplication *app)
{
	GtkBuilder *builder;
	GMenuModel *menu;

	g_assert(GTK_IS_APPLICATION (app));

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
