// File: "asma.h"
// Author: Pau Busquets Aguiló
#ifndef _COMMON_H
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <gio/gio.h>
#include <glib.h>
#include <gtk-3.0/gtk/gtk.h>
#include <dirent.h>

#define DEFAULT_LAUNCH "steam -applaunch 107410"
#define A3_MOD " -mod="
#define A3_WINDOW " -window"
#define A3_NOSPLASH " -noSplash"
#define A3_WORLD " -world=empty"
#define A3_FILE_PATCHING " -filePatching"
#define A3_DEBUG " -showScriptErrors"
#define A3_PRIMUS " MESA_GL_VERSION_OVERRIDE=4.1 MESA_GLSL_VERSION_OVERRIDE=410 \%command\%"

void browse_dir();
void check_dir();
void refresh();

int i, ii;
GError* error;

DIR *directory;
struct dirent *properities;

GFile *arma3_root;

GtkWidget* widget;
GtkWidget* assistant;
GtkWidget* vBox;
GtkWidget* hBox;
GtkWidget* rootBox;
GtkWidget* addonBox;
GtkWidget* button;
GtkWidget* header;
GtkWidget* image;
GtkWidget* scrolled;
GtkWidget* item;
GtkWidget* bar;
GtkWidget* label;
GtkFileChooserNative* native;
GSettings* gset;

char* a3_window;
char* a3_nosplash;
char* a3_world;
char* a3_file_patching;
char* a3_debug;
char* a3_primus;

#define _COMMON_H
#endif
