// File: "mods.c"

#include "mods.h"
#include "asma.h"

static GtkWidget* create_list_item(gpointer item,
                                   gpointer user_data)
{
	return GTK_WIDGET (item);
}

static gint sort_alpha(const void *a,
		       const void *b,
		       void *user_data)
{
	const gchar *x = gtk_label_get_text(GTK_LABEL (a));
	const gchar *y = gtk_label_get_text(GTK_LABEL (b));
	return g_strcmp0((gchar *) x, (gchar *) y);
}

static GListStore* get_local_mods()
{
	GDir *dir;
	GListStore *mods;
	gchar *entry = "";

	mods = g_list_store_new(g_type_from_name("GtkLabel"));

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
				GtkWidget *label;
				label = gtk_label_new(entry);
				g_list_store_append(mods, (gpointer) label);
			}
		}
		entry = g_strdup(g_dir_read_name(dir));
	} while (entry != NULL);

	g_list_store_sort(mods, &sort_alpha, NULL);
	g_dir_close(dir);
	return mods;
}

void mods_refresh(GtkWidget *widget,
		  gpointer user_data)
{
	GListModel *local_mods_store;
	GtkWidget *view;
	GtkListBox *mod_list;

	local_mods_store = G_LIST_MODEL (get_local_mods());
	view = gtk_stack_get_child_by_name(GTK_STACK (widget), "mods_view");
	mod_list = GTK_LIST_BOX (gtk_bin_get_child(GTK_BIN (gtk_bin_get_child(GTK_BIN (view)))));

	gtk_list_box_bind_model(mod_list, local_mods_store, create_list_item,
		NULL, NULL);
	gtk_widget_set_visible(view, TRUE);
	gtk_stack_set_visible_child(GTK_STACK (widget), view);
}

