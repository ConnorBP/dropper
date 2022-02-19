# Ceasar Salad Dropper

This is a simple dropper program that can dress wahtever file it drops up with some tasty ceasar cypher. From the cyphered bytes created by my encoder program, it will then write to disk those bytes (in this case a cute little png dude), and then open it (on mac at least. Command to open files may vary on another OS.)

## Building

On Mac the build command is the following `gcc -o drop main.c`. and for usage simply type `./drop`

as for the encoder do the same as above but replace drop with encoder and main.c with encoder.c.
The encoder is currently hard coded to look for a file called `yuh.png` in the same directory as it was run from. It will output both the raw bytes as `encoded.bin` and c source as `encoded.c`.

## Disclaimer

The Ceasar Salad Dropper was made for research purposes only. Please don't be a baddie. Plus its probably not all that useful anyways.