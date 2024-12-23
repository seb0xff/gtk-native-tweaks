#pragma once
#define __GDKMACOS_H_INSIDE__

#include <gdk/macos/gdkmacos.h>
#include <glib-object.h>
#include <gtk/gtk.h>

#ifdef __cplusplus
extern "C" {
#endif

int gnt_macos_get_menubar_height();

void gnt_macos_get_screen_size(int *width, int *height);
int gnt_macos_get_screen_width();
int gnt_macos_get_screen_height();

#define GNT_TYPE_MACOS_WINDOW (gnt_macos_window_get_type())
G_DECLARE_FINAL_TYPE(GntMacosWindow, gnt_macos_window, GNT, MACOS, GObject)

void gnt_macos_window_set_window(GntMacosWindow *self, GtkWindow *window);

GtkWindow *gnt_macos_window_get_window(GntMacosWindow *self);

// void gnt_macos_window_set_full_size_content_view(GntMacosWindow *self,
//                                           gboolean full_size_content_view);

void gnt_macos_window_set_titlebar_color(GntMacosWindow *self, GdkRGBA *color);
GdkRGBA *gnt_macos_window_get_titlebar_color(GntMacosWindow *self);

void gnt_macos_window_set_resizable(GntMacosWindow *self, gboolean resizable);
gboolean gnt_macos_window_get_resizable(GntMacosWindow *self);

void gnt_macos_window_set_miniaturizable(GntMacosWindow *self,
                                         gboolean miniaturizable);
gboolean gnt_macos_window_get_miniaturizable(GntMacosWindow *self);

void gnt_macos_window_set_closable(GntMacosWindow *self, gboolean exitable);
gboolean gnt_macos_window_get_closable(GntMacosWindow *self);

void gnt_macos_window_set_title_visible(GntMacosWindow *self, gboolean visible);
gboolean gnt_macos_window_get_title_visible(GntMacosWindow *self);

void gnt_macos_window_set_position(GntMacosWindow *self, int x, int y);
void gnt_macos_window_get_position(GntMacosWindow *self, int *x, int *y);

void gnt_macos_window_set_x_position(GntMacosWindow *self, int x);
int gnt_macos_window_get_x_position(GntMacosWindow *self);

void gnt_macos_window_set_y_position(GntMacosWindow *self, int y);
int gnt_macos_window_get_y_position(GntMacosWindow *self);

void gnt_macos_window_get_size(GntMacosWindow *self, int *width, int *height);
int gnt_macos_window_get_width(GntMacosWindow *self);
int gnt_macos_window_get_height(GntMacosWindow *self);

int gnt_macos_window_get_titlebar_height(GntMacosWindow *self);

GntMacosWindow *gnt_macos_window_new(GtkWindow *window);

#ifdef __cplusplus
} // extern "C"
#endif