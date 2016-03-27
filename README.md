#ASMA
simple arma 3 launcher for linux

#Compile
In the `src` directory:

`cmake .
make`

**or**

gcc asma.h asma.c addons.h addons.c $(pkg-config --cflags --libs gtk+-3.0) -o asma
