#ASMA
Simple Arma 3 launcher for Linux

#Requirements
Must have GTK+ 3 and have addons installed in (or linked to) Arma 3 folder

#Compile
In the `src` directory:

`cmake .`

`make`

**or**

`gcc asma.h asma.c addons.h addons.c errors.h errors.c settings.h settings.c  $(pkg-config --cflags --libs gtk+-3.0) -o asma`
