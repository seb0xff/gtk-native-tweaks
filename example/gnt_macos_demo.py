import gi
## Uncomment the following lines if you don't want to install the library
# from os import path as p

# TYPELIB_DIR_ABS = p.abspath(
#     p.realpath(p.join(p.dirname(__file__), '..', 'build')))

# gi.require_version('GIRepository', '2.0')
# from gi.repository import GIRepository

# repo = GIRepository.Repository.get_default()
# repo.prepend_search_path(TYPELIB_DIR_ABS)
# repo.prepend_library_path(TYPELIB_DIR_ABS)

gi.require_version('Gtk', '4.0')
gi.require_version('Gdk', '4.0')
gi.require_version('Adw', '1')
gi.require_version('Gnt', '0.1')

# from gi.repository import Gtk, Gdk, Adw, GntMacos as Gnt
from gi.repository import Gtk, Gdk, Adw, Gnt


class MainWindow(Gtk.ApplicationWindow):

  def __init__(self, *args, **kwargs):
    super().__init__(*args, **kwargs)

    self.set_default_size(400, 250)
    self.set_title("GNT MacOS Demo")
    css = """
    window.background {
      background-color: transparent;
    }"""
    css_provider = Gtk.CssProvider()
    css_provider.load_from_data(css.encode())
    display = Gdk.Display.get_default()
    Gtk.StyleContext.add_provider_for_display(
        display, css_provider, Gtk.STYLE_PROVIDER_PRIORITY_APPLICATION)


class MyApp(Gtk.Application):

  def __init__(self, **kwargs):
    super().__init__(**kwargs)
    self.connect('activate', self.on_activate)

  def on_activate(self, app):
    self.win = MainWindow(application=app)
    self.win.present()
    # help(Gnt.MacosWindow)
    tweaker = Gnt.MacosWindow(window=self.win)
    rgba = Gdk.RGBA()
    rgba.parse('rgb(36,0,36)')
    tweaker.set_titlebar_color(rgba)
    # tweaker.set_titlebar_color(Gdk.RGBA(0, 0, 0, 1)) # Gdk.RGBA is probably boxed type, so this will not work
    # tweaker.set_miniaturizable(False)
    # tweaker.set_resizable(False)
    # tweaker.set_closable(False)
    tweaker.props.x_position = 100
    print(tweaker.props.x_position)
    print(tweaker.get_x_position())
    tweaker.set_y_position(0)
    # print(tweaker.props.closable)


app = MyApp()
app.run()
