#include "gnt.h"
#include "helpers.h"

GNT_TEST(GntMacosWindowTest, titlebarColor) {
  GntMacosWindow *gnt = gnt_macos_window_new(data.window);
  GdkRGBA color = {0.0, 0.0, 0.0, 1.0};
  gnt_macos_window_set_titlebar_color(gnt, &color);
  GdkRGBA *result = gnt_macos_window_get_titlebar_color(gnt);
  EXPECT_EQ(color.red, result->red);
  EXPECT_EQ(color.green, result->green);
  EXPECT_EQ(color.blue, result->blue);
  // alpha is ignored so don't need to check it
  g_object_unref(gnt);
}
GNT_TEST_END()

GNT_TEST(GntMacosWindowTest, titleVisible) {
  GntMacosWindow *gnt = gnt_macos_window_new(data.window);
  gnt_macos_window_set_title_visible(gnt, false);
  EXPECT_EQ(gnt_macos_window_get_title_visible(gnt), false);
  g_object_unref(gnt);
}
GNT_TEST_END()

GNT_TEST(GntMacosWindowTest, size) {
  GntMacosWindow *gnt = gnt_macos_window_new(data.window);
  int width, height;
  gnt_macos_window_get_size(gnt, &width, &height);
  int titlebar_height = gnt_macos_window_get_titlebar_height(gnt);
  EXPECT_EQ(width, 200);
  EXPECT_EQ(height, 200 + titlebar_height);
  g_object_unref(gnt);
}
GNT_TEST_END()

GNT_TEST(GntMacosWindowTest, position) {

  GntMacosWindow *gnt = gnt_macos_window_new(data.window);
  int ww = gnt_macos_window_get_width(gnt);
  int sw = gnt_macos_get_screen_width();
  int menubar_height = gnt_macos_get_menubar_height();
  // set pos to 20, 20 from top right
  gnt_macos_window_set_position(gnt, sw - ww - 20, menubar_height + 20);
  int x, y;
  gnt_macos_window_get_position(gnt, &x, &y);

  EXPECT_EQ(x, sw - ww - 20);
  EXPECT_EQ(y, menubar_height + 20);
  g_object_unref(gnt);
}
GNT_TEST_END()

GNT_TEST(GntMacosWindowTest, titlebarButtons) {
  GntMacosWindow *gnt = gnt_macos_window_new(data.window);
  gnt_macos_window_set_resizable(gnt, false);
  gnt_macos_window_set_miniaturizable(gnt, false);
  gnt_macos_window_set_closable(gnt, false);
  EXPECT_EQ(gnt_macos_window_get_resizable(gnt), false);
  EXPECT_EQ(gnt_macos_window_get_miniaturizable(gnt), false);
  EXPECT_EQ(gnt_macos_window_get_closable(gnt), false);
  g_object_unref(gnt);
}
GNT_TEST_END()
