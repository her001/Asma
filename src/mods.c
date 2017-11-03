// File: "mods.c"

#include "mods.h"
#include "asma.h"

static GArray* get_local_mods()
{
	GDir *dir;
	GArray *mods;
	gchar *entry = "";


	mods = g_array_new(FALSE, FALSE, sizeof(gpointer));

	dir = g_dir_open(g_file_get_path(arma3_root), 0, NULL);
	if (dir == NULL) {
		check_dir();
		return mods;
	}

	do {
		if (g_str_has_prefix(entry, "@")) {
			const gchar *abs_path;
			abs_path = g_file_get_path(g_file_get_child(arma3_root, entry));
			if (g_file_test(abs_path, G_FILE_TEST_IS_DIR)) {
				g_array_append_val(mods, entry);
			}
		}
		entry = g_strdup(g_dir_read_name(dir));
	} while (entry != NULL);

	g_array_sort(mods, (GCompareFunc) g_strcmp0);

	g_dir_close(dir);
	return mods;
}

void mods_refresh(GtkWidget *widget,
		  gpointer user_data)
{
	GArray *local_mods;
	GtkWidget *view;
	guint i;

	local_mods = get_local_mods();
	i = local_mods->len;

	if (i == 0) {
		view = gtk_stack_get_child_by_name(GTK_STACK (widget), "mods_empty");
	} else {
		view = gtk_stack_get_child_by_name(GTK_STACK (widget), "mods_view");
		GtkListBox *mod_list;
		mod_list = GTK_LIST_BOX (gtk_bin_get_child(GTK_BIN (gtk_bin_get_child(GTK_BIN (view)))));
		for (; i>0; i--) {
			GtkWidget *item;
			const gchar *str;

			str = g_array_index(local_mods, gpointer, i-1);
			item = gtk_label_new(str);
			gtk_widget_set_visible(item, TRUE);
			gtk_list_box_prepend(mod_list, item);
		}
		g_array_free(local_mods, FALSE);
	}
	gtk_widget_set_visible(view, TRUE);
	gtk_stack_set_visible_child(GTK_STACK (widget), view);
}
