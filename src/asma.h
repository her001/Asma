// File: "asma.h"
// Author: Pau Busquets Aguiló
#ifndef _COMMON_H
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <gtk-3.0/gtk/gtk.h>
#include <dirent.h>

#define ARMA3_DEFAULT_PATH "/.local/share/Steam/steamapps/common/Arma 3"

#define DEFAULT_LAUNCH "steam -applaunch 107410"
#define A3_MOD " -mod="
#define A3_WINDOW " -window"
#define A3_NOSPLASH " -nosplash"
#define A3_WORLD " -world=empty"
#define A3_FILE_PATCHING " -filePatching"
#define A3_DEBUG " -showScriptErrors"
#define A3_PRIMUS " MESA_GL_VERSION_OVERRIDE=4.1 MESA_GLSL_VERSION_OVERRIDE=410 \%command\%"

int i, ii;

DIR *directory;
struct dirent *properities;

char* user_root;
char* arma3_root;

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
GtkWidget* window;
GtkWidget* item;
GtkWidget* bar;
GtkWidget* label;
GtkWidget* native;
GIcon* icon;

GtkWidget* b_a3_window;
GtkWidget* b_a3_nosplash;
GtkWidget* b_a3_world;
GtkWidget* b_a3_file_patching;
GtkWidget* b_a3_debug;
GtkWidget* b_a3_primus;

char* a3_window;
char* a3_nosplash;
char* a3_world;
char* a3_file_patching;
char* a3_debug;
char* a3_primus;

static void call_quit();
static void call_launch();
void call_refresh();
static void call_open_folder();
static void set_a3_window( GtkToggleButton*);
static void set_a3_nosplash( GtkToggleButton*);
static void set_a3_world( GtkToggleButton*);
static void set_a3_file_patching( GtkToggleButton*);
static void set_a3_debug( GtkToggleButton*);
static void set_a3_primus( GtkToggleButton*);

#define _COMMON_H
#endif
