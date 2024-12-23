#pragma once
#define __GDKMACOS_H_INSIDE__

#include <gdk/macos/gdkmacos.h>
#include <glib-object.h>
#include <gtk/gtk.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GNT_TYPE_MACOS (gnt_macos_get_type())
G_DECLARE_FINAL_TYPE(GntMacos, gnt_macos, GNT, MACOS, GObject)

void gnt_macos_set_window(GntMacos *self, GtkWindow *window);

GtkWindow *gnt_macos_get_window(GntMacos *self);

// void gnt_macos_set_full_size_content_view(GntMacos *self,
//                                           gboolean full_size_content_view);

void gnt_macos_set_titlebar_color(GntMacos *self, GdkRGBA *color);
GdkRGBA *gnt_macos_get_titlebar_color(GntMacos *self);

void gnt_macos_set_resizable(GntMacos *self, gboolean resizable);
gboolean gnt_macos_get_resizable(GntMacos *self);

void gnt_macos_set_miniaturizable(GntMacos *self, gboolean miniaturizable);
gboolean gnt_macos_get_miniaturizable(GntMacos *self);

void gnt_macos_set_closable(GntMacos *self, gboolean exitable);
gboolean gnt_macos_get_closable(GntMacos *self);

void gnt_macos_set_title_visible(GntMacos *self, gboolean visible);
gboolean gnt_macos_get_title_visible(GntMacos *self);

void gnt_macos_set_position(GntMacos *self, int x, int y);
void gnt_macos_get_position(GntMacos *self, int *x, int *y);

void gnt_macos_set_x_position(GntMacos *self, int x);
int gnt_macos_get_x_position(GntMacos *self);

void gnt_macos_set_y_position(GntMacos *self, int y);
int gnt_macos_get_y_position(GntMacos *self);

void gnt_macos_get_size(GntMacos *self, int *width, int *height);
int gnt_macos_get_width(GntMacos *self);
int gnt_macos_get_height(GntMacos *self);

int gnt_macos_get_titlebar_height(GntMacos *self);

int gnt_macos_get_menubar_height();

void gnt_macos_get_screen_size(int *width, int *height);
int gnt_macos_get_screen_width();
int gnt_macos_get_screen_height();

GntMacos *gnt_macos_new(GtkWindow *window);

#ifdef __cplusplus
} // extern "C"
#endif