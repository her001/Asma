gnome = import('gnome')

deps = [dependency('gio-2.0'),
	dependency('glib-2.0'),
	dependency('gmodule-export-2.0'),
	dependency('gtk+-3.0')]

src = ['asma.c', 'addons.c', 'errors.c', 'settings.c']
src += gnome.compile_resources('asma-resources',
	'asma.gresource.xml',
	c_name: 'asma')

executable('asma', src,
	dependencies: deps,
	install: true)

