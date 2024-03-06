# Compile.sh

g++ -o kilt main.cpp `pkg-config --cflags --libs gtk+-3.0`
