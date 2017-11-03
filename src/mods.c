// File: "mods.c"

#include "mods.h"
#include "asma.h"

static GArray* get_local_mods()
{
	static GDir *dir;
	GArray *mods;
	gchar *entry = "";


	mods = g_array_new(FALSE, FALSE, sizeof(gchar));

	if (dir == NULL)
		dir = g_dir_open(g_file_get_path(arma3_root), 0, NULL);
	if (dir == NULL) {
		check_dir();
		return mods;
	}

	do {
		if (!g_strcmp0(entry, ""))
			g_array_append_val(mods, entry);
		entry = g_strdup(g_dir_read_name(dir));
	} while (entry != NULL);

	g_array_sort(mods, (GCompareFunc) g_strcmp0);

	g_dir_rewind(dir);
	return mods;
}

void mods_refresh(GtkWidget *widget,
		  gpointer user_data)
{
	GArray *local_mods;

	local_mods = get_local_mods();
	if (local_mods->len == 0)
		gtk_stack_set_visible_child_name(GTK_STACK (widget), "mods_empty");
}
