#ASMA
Simple Arma 3 launcher for Linux

#Requirements
Must have GTK+ 3 and have Arma 3 installed in (or linked to) `~/.local/share/Steam/steamapps/common/Arma 3`

#Compile
In the `src` directory:

`cmake .`

`make`

**or**

`gcc asma.h asma.c addons.h addons.c $(pkg-config --cflags --libs gtk+-3.0) -o asma`
