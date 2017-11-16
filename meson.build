project('asma', 'c', meson_version: '>=0.36.0')

add_project_link_arguments('-export-dynamic', language: 'c')

subdir('src')
subdir('data')

meson.add_install_script('meson_post_install.py')

