# ASMA
Simple Arma 3 launcher for Linux

## Requirements
Must have GTK+ 3 and have addons installed in (or linked to) Arma 3 folder

## Installation

Install GTK+ 3.

```console
$ sudo apt-get install libgtk-3-dev
```

Clone the repo OR [download it](https://github.com/busquetsaguilopau/asma/archive/master.zip).

```console
$ git clone git@github.com:busquetsaguilopau/asma.git
```

Open the terminal and go to `asma/src` folder.

```console
$ cd asma/src
~/asma/src$
```

Compile

```console
~/asma/src$ cmake .
~/asma/src$ make
```

or compile like this:

```console
~/asma/src$ gcc asma.h asma.c addons.h addons.c errors.h errors.c settings.h settings.c  $(pkg-config --cflags --libs gtk+-3.0) -o asma
```

Use ASAM:

```console
~/asma/src$ ./asam
```
