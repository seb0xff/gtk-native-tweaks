import sys
from os import path as p
import gi

TYPELIB_DIR_ABS = p.abspath(
    p.realpath(p.join(p.dirname(__file__), '..', 'build')))

gi.require_version('GIRepository', '2.0')
from gi.repository import GIRepository

repo = GIRepository.Repository.get_default()
repo.prepend_search_path(TYPELIB_DIR_ABS)
repo.prepend_library_path(TYPELIB_DIR_ABS)

gi.require_version('Gtk', '4.0')
gi.require_version('Gdk', '4.0')
gi.require_version('Adw', '1')
gi.require_version('Gnt', '0.1')

from gi.repository import Gtk, Gdk, Adw, Gnt


class MainWindow(Gtk.ApplicationWindow):

  def __init__(self, *args, **kwargs):
    super().__init__(*args, **kwargs)

    self.set_default_size(400, 250)
    # self.set_decorated(False)
    # self.props.default_width = 400
    # print(self.props.default_width)
    # self.props.default_height = 250
    self.set_resizable(False)
    self.set_title("Adwaita")
    css = """
    .background {
      background-color: rgb(36,0,36);
    }

    .view {
      background-color: rgba(36,0,36,0.7);
    }"""
    css_provider = Gtk.CssProvider()
    css_provider.load_from_data(css.encode())
    display = Gdk.Display.get_default()
    Gtk.StyleContext.add_provider_for_display(
        display, css_provider, Gtk.STYLE_PROVIDER_PRIORITY_APPLICATION)

    button = Gtk.Button(label="click me")
    button.connect('clicked', self.on_click)
    self.set_child(button)

  def on_click(self, button):
    pass


class MyApp(Adw.Application):

  def __init__(self, **kwargs):
    super().__init__(**kwargs)
    self.connect('activate', self.on_activate)

  def on_activate(self, app):
    self.win = MainWindow(application=app)
    self.win.present()
    # help(Gnt.Macos)
    gnt = Gnt.Macos(window=self.win)
    rgba = Gdk.RGBA()
    rgba.parse('rgb(36,0,36)')
    gnt.set_titlebar_color(rgba)
    # gnt.set_titlebar_color(Gdk.RGBA(0, 0, 0, 1)) # this is not working
    # gnt.set_miniaturizable(False)
    # gnt.set_resizable(False)
    # gnt.set_closable(False)
    gnt.props.x_position = 100
    print(gnt.props.x_position)
    print(gnt.get_x_position())
    gnt.set_y_position(0)
    # print(gnt.props.closable)


app = MyApp()
app.run()
