project('asma', 'c')

gtkdep = dependency('gtk+-3.0')

src = ['asma.c', 'addons.c', 'errors.c', 'settings.c']
executable('asma', src,
	dependencies: gtkdep,
	install: true)

install_data('../asma.desktop',
	install_dir: 'share/applications')
install_data('../asma.png',
	install_dir: 'share/icons/hicolor/256x256/apps')
