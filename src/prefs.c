#import "prefs.h"
#import "asma.h"

void update_root_file(GSettings *settings,
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
