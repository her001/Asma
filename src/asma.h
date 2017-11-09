// File: "asma.h"
// Author: Pau Busquets Aguiló
#ifndef _COMMON_H
#include <gio/gio.h>
#include <glib.h>
#include <gtk-3.0/gtk/gtk.h>

#define DEFAULT_LAUNCH "steam -applaunch 107410"
#define A3_MOD " -mod="
#define A3_WINDOW " -window"
#define A3_NOSPLASH " -noSplash"
#define A3_NOWORLD " -world=empty"
#define A3_FILE_PATCHING " -filePatching"
#define A3_DEBUG " -showScriptErrors"
#define A3_PRIMUS " MESA_GL_VERSION_OVERRIDE=4.1 MESA_GLSL_VERSION_OVERRIDE=410 \%command\%"

void browse_dir();

GFile *arma3_root;
GtkBuilder *builder;
GSettings *gset;
GSettings *gset_a3;

#define _COMMON_H
#endif

