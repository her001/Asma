project('asma', 'c')

add_project_link_arguments('-rdynamic', language: 'c')

subdir('src')
subdir('data')

meson.add_install_script('meson_post_install.py')
