# [Asma](https://github.com/her001/asma)

Copyright © 2016, 2017 Andrew "HER0" Conrad

Copyright © 2016 Pau Busquets Aguiló

**Asma** is a simple Arma 3 launcher for Linux.

## Requirements

* [Arma 3](http://store.steampowered.com/app/107410) (obviously)
* [GTK+ 3](https://www.gtk.org/download/index.php)
* [Meson](https://github.com/mesonbuild/meson/releases) and [Ninja](https://github.com/ninja-build/ninja/releases) (for building and installing)

Any mods should be in the Arma 3 folder (linking works) and start with the "@"
character.

## Installation

First, clone the project and switch to the directory:

```
git clone https://github.com/her001/asma.git
cd asma
```

Next, configure and build:

```
meson builddir
cd builddir
ninja
```

Finally, install (as root):

```
ninja install
```

