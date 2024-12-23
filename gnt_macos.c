#import <Cocoa/Cocoa.h>

#include "gnt_macos.h"

/**
 * gnt_macos_get_screen_size:
 * @width: (out): the width
 * @height: (out): the height
 *
 * Gets the size of the screen.
 */
void gnt_macos_get_screen_size(int *width, int *height) {
  g_return_if_fail(width != NULL);
  g_return_if_fail(height != NULL);
  *width = gnt_macos_get_screen_width();
  *height = gnt_macos_get_screen_height();
}

/**
 * gnt_macos_get_screen_width:
 *
 * Returns: the width of the screen
 */
int gnt_macos_get_screen_width() {
  return NSScreen.mainScreen.frame.size.width;
}

/**
 * gnt_macos_get_screen_height:
 *
 * Returns: the height of the screen
 */
int gnt_macos_get_screen_height() {
  return NSScreen.mainScreen.frame.size.height;
}

/**
 * gnt_macos_get_menubar_height:
 *
 * Returns: the height of the menubar
 */
int gnt_macos_get_menubar_height() {
  return NSScreen.mainScreen.frame.size.height -
         NSScreen.mainScreen.visibleFrame.size.height;
}

enum {
  PROP_0,
  PROP_WINDOW,
  PROP_TITLEBAR_COLOR,
  PROP_RESIZABLE,
  PROP_MINIATURIZABLE,
  PROP_CLOSABLE,
  PROP_TITLE_VISIBLE,
  PROP_X_POSITION,
  PROP_Y_POSITION,
  PROP_WIDTH,
  PROP_HEIGHT,
  PROP_TITLEBAR_HEIGHT,
  NUM_PROPERTIES
};

static GParamSpec *obj_props[NUM_PROPERTIES] = {
    NULL,
};

struct _GntMacosWindow {
  GObject parent;
  GtkWindow *window;
};

G_DEFINE_TYPE(GntMacosWindow, gnt_macos_window, G_TYPE_OBJECT)

static void gnt_macos_window_set_property(GObject *object, guint property_id,
                                          const GValue *value,
                                          GParamSpec *pspec) {
  GntMacosWindow *self = GNT_MACOS(object);
  switch (property_id) {
  case PROP_WINDOW:
    gnt_macos_window_set_window(self, g_value_get_object(value));
    break;
  case PROP_TITLEBAR_COLOR:
    gnt_macos_window_set_titlebar_color(self, g_value_get_boxed(value));
    break;
  case PROP_RESIZABLE:
    gnt_macos_window_set_resizable(self, g_value_get_boolean(value));
    break;
  case PROP_MINIATURIZABLE:
    gnt_macos_window_set_miniaturizable(self, g_value_get_boolean(value));
    break;
  case PROP_CLOSABLE:
    gnt_macos_window_set_closable(self, g_value_get_boolean(value));
    break;
  case PROP_TITLE_VISIBLE:
    gnt_macos_window_set_title_visible(self, g_value_get_boolean(value));
    break;
  case PROP_X_POSITION:
    gnt_macos_window_set_x_position(self, g_value_get_int(value));
    break;
  case PROP_Y_POSITION:
    gnt_macos_window_set_y_position(self, g_value_get_int(value));
    break;

  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
  }
}

static void gnt_macos_window_get_property(GObject *object, guint property_id,
                                          GValue *value, GParamSpec *pspec) {
  GntMacosWindow *self = GNT_MACOS(object);

  switch (property_id) {
  case PROP_WINDOW:
    g_value_set_object(value, (GObject *)self->window);
    break;
  case PROP_TITLEBAR_COLOR:
    g_value_set_boxed(value, gnt_macos_window_get_titlebar_color(self));
    break;
  case PROP_RESIZABLE:
    g_value_set_boolean(value, gnt_macos_window_get_resizable(self));
    break;
  case PROP_MINIATURIZABLE:
    g_value_set_boolean(value, gnt_macos_window_get_miniaturizable(self));
    break;
  case PROP_CLOSABLE:
    g_value_set_boolean(value, gnt_macos_window_get_closable(self));
    break;
  case PROP_TITLE_VISIBLE:
    g_value_set_boolean(value, gnt_macos_window_get_title_visible(self));
    break;
  case PROP_X_POSITION:
    g_value_set_int(value, gnt_macos_window_get_x_position(self));
    break;
  case PROP_Y_POSITION:
    g_value_set_int(value, gnt_macos_window_get_y_position(self));
    break;
  case PROP_WIDTH:
    g_value_set_int(value, gnt_macos_window_get_width(self));
    break;
  case PROP_HEIGHT:
    g_value_set_int(value, gnt_macos_window_get_height(self));
    break;
  case PROP_TITLEBAR_HEIGHT:
    g_value_set_int(value, gnt_macos_window_get_titlebar_height(self));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
  }
}

static void gnt_macos_window_class_init(GntMacosWindowClass *class) {
  GObjectClass *gobject_class = G_OBJECT_CLASS(class);

  gobject_class->set_property = gnt_macos_window_set_property;
  gobject_class->get_property = gnt_macos_window_get_property;

  obj_props[PROP_WINDOW] = g_param_spec_object(
      "window", NULL, NULL, GTK_TYPE_WINDOW, G_PARAM_READWRITE);

  obj_props[PROP_TITLEBAR_COLOR] =
      g_param_spec_boxed("titlebar-color", NULL, NULL, GDK_TYPE_RGBA,
                         G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);

  obj_props[PROP_RESIZABLE] =
      g_param_spec_boolean("resizable", NULL, NULL, FALSE, G_PARAM_READWRITE);

  obj_props[PROP_MINIATURIZABLE] = g_param_spec_boolean(
      "miniaturizable", NULL, NULL, FALSE, G_PARAM_READWRITE);

  obj_props[PROP_CLOSABLE] =
      g_param_spec_boolean("closable", NULL, NULL, FALSE, G_PARAM_READWRITE);

  obj_props[PROP_TITLE_VISIBLE] = g_param_spec_boolean(
      "title-visible", NULL, NULL, FALSE, G_PARAM_READWRITE);

  obj_props[PROP_X_POSITION] = g_param_spec_int(
      "x-position", NULL, NULL, G_MININT, G_MAXINT, 0, G_PARAM_READWRITE);

  obj_props[PROP_Y_POSITION] = g_param_spec_int(
      "y-position", NULL, NULL, G_MININT, G_MAXINT, 0, G_PARAM_READWRITE);

  obj_props[PROP_WIDTH] = g_param_spec_int("width", NULL, NULL, G_MININT,
                                           G_MAXINT, 0, G_PARAM_READABLE);

  obj_props[PROP_HEIGHT] = g_param_spec_int("height", NULL, NULL, G_MININT,
                                            G_MAXINT, 0, G_PARAM_READABLE);

  obj_props[PROP_TITLEBAR_HEIGHT] = g_param_spec_int(
      "titlebar-height", NULL, NULL, G_MININT, G_MAXINT, 0, G_PARAM_READABLE);

  g_object_class_install_properties(gobject_class, NUM_PROPERTIES, obj_props);
}

static void gnt_macos_window_init(GntMacosWindow *self) {}

NSWindow *get_native_window(GntMacosWindow *self) {
  return (NSWindow *)gdk_macos_surface_get_native_window(
      (GdkMacosSurface *)gtk_native_get_surface((GtkNative *)self->window));
}

/**
 * gnt_macos_window_set_window:
 * @self: a `GntMacosWindow`
 * @window: (transfer none): a `GtkWindow`
 *
 * Sets the window.
 */
void gnt_macos_window_set_window(GntMacosWindow *self, GtkWindow *window) {
  g_return_if_fail(GNT_IS_MACOS(self));
  self->window = window;
}

/**
 * gnt_macos_window_get_window:
 * @self: a `GntMacosWindow`
 *
 * Returns: (transfer none): the window
 */
GtkWindow *gnt_macos_window_get_window(GntMacosWindow *self) {
  g_return_val_if_fail(GNT_IS_MACOS(self), NULL);
  return self->window;
}

// void gnt_macos_window_set_full_size_content_view(GntMacosWindow *self,
//                                           gboolean full_size_content_view)
//                                           {
//   g_return_if_fail(GNT_IS_MACOS(self));
//   NSWindow *window = get_native_window(self);
//   window.titlebarAppearsTransparent = YES;
//   window.styleMask |= NSWindowStyleMaskFullSizeContentView;
//   // gdk_surface_set_opaque_region(GdkSurface *surface, cairo_region_t
//   *region)
// }

/**
 * gnt_macos_window_new:
 * @window: a `GtkWindow`
 *
 * Returns: (transfer full): a new `GntMacosWindow`
 */
GntMacosWindow *gnt_macos_window_new(GtkWindow *window) {
  GntMacosWindow *self;

  // self = g_object_new(GNT_TYPE_MACOS_WINDOW, "surface", surface, NULL);
  self = g_object_new(GNT_TYPE_MACOS_WINDOW, NULL);
  // gnt_macos_window_set_surface(self, surface);
  gnt_macos_window_set_window(self, window);
  return self;
}

/**
 * gnt_macos_window_set_titlebar_color:
 * @self: a `GntMacosWindow`
 * @color: (transfer none): a #GdkRGBA
 *
 * Sets the titlebar color of the window. It ignores the alpha channel.
 * Note: In fact, this makes titlebar transparent and sets the background
 * color of the native window, which is underneath the Gtk surface.
 */
void gnt_macos_window_set_titlebar_color(GntMacosWindow *self, GdkRGBA *color) {
  g_return_if_fail(GNT_IS_MACOS(self));
  g_return_if_fail(color != NULL);
  NSWindow *window = get_native_window(self);
  window.titlebarAppearsTransparent = YES;
  float red = color->red;
  float green = color->green;
  float blue = color->blue;
  [window setBackgroundColor:[NSColor colorWithCalibratedRed:red
                                                       green:green
                                                        blue:blue
                                                       alpha:1.0]];
}

/**
 * gnt_macos_window_get_titlebar_color:
 * @self: a `GntMacosWindow`
 *
 * Returns: (transfer full): the titlebar color
 */
GdkRGBA *gnt_macos_window_get_titlebar_color(GntMacosWindow *self) {
  g_return_val_if_fail(GNT_IS_MACOS(self), NULL);
  NSWindow *window = get_native_window(self);
  NSColor *color = window.backgroundColor;
  double red, green, blue, alpha;
  [color getRed:&red green:&green blue:&blue alpha:&alpha];
  GdkRGBA *rgba = g_new(GdkRGBA, 1);
  // downcast to float
  rgba->red = red;
  rgba->green = green;
  rgba->blue = blue;
  rgba->alpha = alpha;
  return rgba;
}

/**
 * gnt_macos_window_set_resizable:
 * @self: a `GntMacosWindow`
 * @resizable: whether the window should be resizable
 *
 * Sets whether the window should be resizable.
 */
void gnt_macos_window_set_resizable(GntMacosWindow *self, gboolean resizable) {
  g_return_if_fail(GNT_IS_MACOS(self));
  NSWindow *window = get_native_window(self);
  window.styleMask = resizable ? window.styleMask | NSWindowStyleMaskResizable
                               : window.styleMask & ~NSWindowStyleMaskResizable;
}

/**
 * gnt_macos_window_get_resizable:
 * @self: a `GntMacosWindow`
 *
 * Returns: whether the window is resizable
 */
gboolean gnt_macos_window_get_resizable(GntMacosWindow *self) {
  g_return_val_if_fail(GNT_IS_MACOS(self), FALSE);
  NSWindow *window = get_native_window(self);
  return window.styleMask & NSWindowStyleMaskResizable;
}

/**
 * gnt_macos_window_set_miniaturizable:
 * @self: a `GntMacosWindow`
 * @miniaturizable: whether the window should be miniaturizable
 *
 * Sets whether the window should be miniaturizable and have a miniaturize
 * button.
 */
void gnt_macos_window_set_miniaturizable(GntMacosWindow *self,
                                         gboolean miniaturizable) {
  g_return_if_fail(GNT_IS_MACOS(self));
  NSWindow *window = get_native_window(self);
  window.styleMask = miniaturizable
                         ? window.styleMask | NSWindowStyleMaskMiniaturizable
                         : window.styleMask & ~NSWindowStyleMaskMiniaturizable;
}

/**
 * gnt_macos_window_get_miniaturizable:
 * @self: a `GntMacosWindow`
 *
 * Returns: whether the window is miniaturizable
 */
gboolean gnt_macos_window_get_miniaturizable(GntMacosWindow *self) {
  g_return_val_if_fail(GNT_IS_MACOS(self), FALSE);
  NSWindow *window = get_native_window(self);
  return window.styleMask & NSWindowStyleMaskMiniaturizable;
}

/**
 * gnt_macos_window_set_closable:
 * @self: a `GntMacosWindow`
 * @exitable: whether the window should be closable
 *
 * Sets whether the window should be closable and have a close button.
 */
void gnt_macos_window_set_closable(GntMacosWindow *self, gboolean exitable) {
  g_return_if_fail(GNT_IS_MACOS(self));
  NSWindow *window = get_native_window(self);
  window.styleMask = exitable ? window.styleMask | NSWindowStyleMaskClosable
                              : window.styleMask & ~NSWindowStyleMaskClosable;
}

/**
 * gnt_macos_window_get_closable:
 * @self: a `GntMacosWindow`
 *
 * Returns: whether the window is closable
 */
gboolean gnt_macos_window_get_closable(GntMacosWindow *self) {
  g_return_val_if_fail(GNT_IS_MACOS(self), FALSE);
  NSWindow *window = get_native_window(self);
  return window.styleMask & NSWindowStyleMaskClosable;
}

/**
 * gnt_macos_window_set_title_visible:
 * @self: a `GntMacosWindow`
 * @visible: whether the title should be visible
 *
 * Sets the visibility of the title.
 */
void gnt_macos_window_set_title_visible(GntMacosWindow *self,
                                        gboolean visible) {
  g_return_if_fail(GNT_IS_MACOS(self));
  NSWindow *window = get_native_window(self);
  window.titleVisibility = visible ? NSWindowTitleVisible : NSWindowTitleHidden;
}

/**
 * gnt_macos_window_get_title_visible:
 * @self: a `GntMacosWindow`
 *
 * Returns: whether the title is visible
 */
gboolean gnt_macos_window_get_title_visible(GntMacosWindow *self) {
  g_return_val_if_fail(GNT_IS_MACOS(self), FALSE);
  NSWindow *window = get_native_window(self);
  return window.titleVisibility == NSWindowTitleVisible;
}

/**
 * gnt_macos_window_set_position:
 * @self: a `GntMacosWindow`
 * @x: the x coordinate
 * @y: the y coordinate
 *
 * Sets the position of the window. The origin is the top-left corner.
 */
void gnt_macos_window_set_position(GntMacosWindow *self, int x, int y) {
  g_return_if_fail(GNT_IS_MACOS(self));
  gnt_macos_window_set_x_position(self, x);
  gnt_macos_window_set_y_position(self, y);
}

/**
 * gnt_macos_window_get_position:
 * @self: a `GntMacosWindow`
 * @x: (out): the x coordinate
 * @y: (out): the y coordinate
 *
 * Gets the position of the window. The origin is the top-left corner.
 */
void gnt_macos_window_get_position(GntMacosWindow *self, int *x, int *y) {
  g_return_if_fail(GNT_IS_MACOS(self));
  g_return_if_fail(x != NULL);
  g_return_if_fail(y != NULL);
  *x = gnt_macos_window_get_x_position(self);
  *y = gnt_macos_window_get_y_position(self);
}

/**
 * gnt_macos_window_set_x_position:
 * @self: a `GntMacosWindow`
 * @x: the x coordinate
 *
 * Sets the horizontal position of the window. The origin is the top-left
 * corner.
 */
void gnt_macos_window_set_x_position(GntMacosWindow *self, int x) {
  g_return_if_fail(GNT_IS_MACOS(self));
  NSWindow *window = get_native_window(self);
  int y = window.frame.origin.y;
  NSPoint newOrigin = NSMakePoint(x, y);
  [window setFrameOrigin:newOrigin];
}

/**
 * gnt_macos_window_get_x_position:
 * @self: a `GntMacosWindow`
 *
 * Returns: the horizontal position of the window. The origin is the top-left
 */
int gnt_macos_window_get_x_position(GntMacosWindow *self) {
  g_return_val_if_fail(GNT_IS_MACOS(self), 0);
  NSWindow *window = get_native_window(self);
  return window.frame.origin.x;
}

/**
 * gnt_macos_window_set_y_position:
 * @self: a `GntMacosWindow`
 * @y: the y coordinate
 *
 * Sets the vertical position of the window. The origin is the top-left
 * corner.
 */
void gnt_macos_window_set_y_position(GntMacosWindow *self, int y) {
  g_return_if_fail(GNT_IS_MACOS(self));
  NSWindow *window = get_native_window(self);
  int x = window.frame.origin.x;
  y = NSScreen.mainScreen.frame.size.height - y;
  [window setFrameTopLeftPoint:NSMakePoint(x, y)];
}

/**
 * gnt_macos_window_get_y_position:
 * @self: a `GntMacosWindow`
 *
 * Returns: the vertical position of the window. The origin is the top-left
 */
int gnt_macos_window_get_y_position(GntMacosWindow *self) {
  g_return_val_if_fail(GNT_IS_MACOS(self), 0);
  NSWindow *window = get_native_window(self);
  int flipped_y = window.frame.origin.y + window.frame.size.height;
  return NSScreen.mainScreen.frame.size.height - flipped_y;
}

/**
 * gnt_macos_window_get_titlebar_height:
 * @self: a `GntMacosWindow`
 *
 * Returns: the height of the titlebar
 */
int gnt_macos_window_get_titlebar_height(GntMacosWindow *self) {
  g_return_val_if_fail(GNT_IS_MACOS(self), 0);
  NSWindow *window = get_native_window(self);
  return window.frame.size.height -
         [window contentRectForFrameRect:window.frame].size.height;
}

/**
 * gnt_macos_window_get_size:
 * @self: a `GntMacosWindow`
 * @width: (out): the width
 * @height: (out): the height
 *
 * Gets the size of the window.
 */
void gnt_macos_window_get_size(GntMacosWindow *self, int *width, int *height) {
  g_return_if_fail(GNT_IS_MACOS(self));
  g_return_if_fail(width != NULL);
  g_return_if_fail(height != NULL);
  *width = gnt_macos_window_get_width(self);
  *height = gnt_macos_window_get_height(self);
}

/**
 * gnt_macos_window_get_width:
 * @self: a `GntMacosWindow`
 *
 * Returns: the width of the window
 */
int gnt_macos_window_get_width(GntMacosWindow *self) {
  g_return_val_if_fail(GNT_IS_MACOS(self), 0);
  NSWindow *window = get_native_window(self);
  return window.frame.size.width;
}

/**
 * gnt_macos_window_get_height:
 * @self: a `GntMacosWindow`
 *
 * Returns: the height of the window
 */
int gnt_macos_window_get_height(GntMacosWindow *self) {
  g_return_val_if_fail(GNT_IS_MACOS(self), 0);
  NSWindow *window = get_native_window(self);
  return window.frame.size.height;
}
