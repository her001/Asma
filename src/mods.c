// File: "mods.c"

#include "asma.h"
#include "mods.h"
#include "prefs.h"

static void toggle_image(GtkButton *button,
                         gpointer   user_data)
{
	if (gtk_button_get_always_show_image(button))
		gtk_button_set_always_show_image(button, FALSE);
	else
		gtk_button_set_always_show_image(button, TRUE);
}

static GtkWidget* create_list_item(gpointer item,
                                   gpointer user_data)
{
	GtkWidget *check;

	check = gtk_image_new_from_icon_name("object-select-symbolic", GTK_ICON_SIZE_BUTTON);
	gtk_widget_set_margin_start(check, 6);
	gtk_button_set_image(GTK_BUTTON (item), check);
	gtk_button_set_image_position(GTK_BUTTON(item), GTK_POS_RIGHT);
	gtk_button_set_relief(item, GTK_RELIEF_NONE);
	g_signal_connect(item, "toggled", (gpointer) &toggle_image, NULL);
	return GTK_WIDGET (item);
}

static gint sort_alpha(const void *a,
		       const void *b,
		       void *user_data)
{
	const gchar *x = gtk_button_get_label(GTK_BUTTON (a));
	const gchar *y = gtk_button_get_label(GTK_BUTTON (b));
	return g_strcmp0((gchar *) x, (gchar *) y);
}

static GListStore* get_local_mods()
{
	GDir *dir;
	GListStore *mods;
	gchar *entry = "";

	mods = g_list_store_new(g_type_from_name("GtkToggleButton"));

	dir = g_dir_open(g_file_get_path(arma3_root), 0, NULL);
	if (dir == NULL) {
		return mods;
	}

	do {
		if (g_str_has_prefix(entry, "@")) {
			const gchar *abs_path;
			abs_path = g_file_get_path(g_file_get_child(arma3_root, entry));
			if (g_file_test(abs_path, G_FILE_TEST_IS_DIR)) {
				GtkToggleButton *button;
				button = GTK_TOGGLE_BUTTON (gtk_toggle_button_new_with_label(entry));
				g_list_store_append(mods, (gpointer) button);
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
	GtkListBox *mods_list;

	local_mods_store = G_LIST_MODEL (get_local_mods());
	mods_list = GTK_LIST_BOX (gtk_builder_get_object(builder, "mods_list"));

	gtk_list_box_bind_model(mods_list, local_mods_store, create_list_item,
		NULL, NULL);
}

