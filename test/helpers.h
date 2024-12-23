#include "gdk/gdkkeysyms.h"
#include "gtest/gtest.h"
#include <functional>
#include <gtk/gtk.h>

struct Data {
  GtkApplication *app;
  GtkWindow *window;
  std::function<void()> test_func;
};

static void event_key_pressed_cb(GtkEventControllerKey *controller,
                                 guint keyval, guint keycode,
                                 GdkModifierType state, gpointer user_data) {
  Data *data = (Data *)user_data;

  if (keyval == GDK_KEY_Return || keyval == GDK_KEY_space) {
    gtk_window_close(GTK_WINDOW(data->window));
  }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static void activate_cb(GtkApplication *app, gpointer user_data) {
  Data *data = (Data *)user_data;
  data->window = (GtkWindow *)gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(data->window), "Test Window");
  gtk_window_set_default_size(GTK_WINDOW(data->window), 200, 200);
  if (INTERACTIVE_TEST) {
    GtkEventController *event_controller = gtk_event_controller_key_new();
    g_signal_connect(event_controller, "key-pressed",
                     G_CALLBACK(event_key_pressed_cb), data);
    gtk_widget_add_controller((GtkWidget *)data->window, event_controller);
  }
  gtk_window_present(GTK_WINDOW(data->window));
  data->test_func();
  if (!INTERACTIVE_TEST) {
    gtk_window_close(GTK_WINDOW(data->window));
  }
}
#pragma GCC diagnostic pop

#define GNT_TEST(test_suite_name, test_name)                                   \
  TEST(test_suite_name, test_name) {                                           \
    Data data;                                                                 \
    data.app =                                                                 \
        gtk_application_new("gnt.test.app", G_APPLICATION_DEFAULT_FLAGS);      \
    data.test_func = [&]() -> void

#define GNT_TEST_END()                                                         \
  ;                                                                            \
  g_signal_connect(data.app, "activate", G_CALLBACK(activate_cb), &data);      \
  g_application_run(G_APPLICATION(data.app), 0, NULL);                         \
  g_object_unref(data.app);                                                    \
  }