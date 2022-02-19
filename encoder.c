#include <stdio.h>
#include <stdlib.h>

// a simple helper to encode a char value into a hex string (4 characters wide)
void tohex(unsigned char in, char * out) {
    const char * hex = "0123456789ABCDEF";
    unsigned char * pin = &in;
    char * pout = out;
    pout[0] = '0';
    pout[1] = 'x';
    pout[2] = hex[(*pin>>4) & 0xF];
    pout[3] = hex[ *pin     & 0xF];
    pout[4] = '\0';
    pout[-1] = 0;
}

// simple cesarean cypher example (key = 69)
int main(int argc, char *argv[]) {
    FILE *fptr;
    FILE *outptr;
    FILE *txtoutptr;
    char *buffer;
    long filelen;
    if ((fptr = fopen("/Users/connor/Documents/CodeProjects/c_dropper/yuh.png", "rb")) == NULL) {
        printf("Error: failed to get handle to file.");
        exit(1);
    }
    if ((outptr = fopen("/Users/connor/Documents/CodeProjects/c_dropper/encoded", "wb")) == NULL) {
        printf("Error: failed to get handle to output file.");
        exit(1);
    }
    if ((txtoutptr = fopen("/Users/connor/Documents/CodeProjects/c_dropper/encoded.c", "w")) == NULL) {
        printf("Error: failed to get handle to output file.");
        exit(1);
    }
    fseek(fptr, 0, SEEK_END);          // Jump to the end of the file
    filelen = ftell(fptr);             // Get the current byte offset in the file
    rewind(fptr);                      // Jump back to the beginning of the file

    buffer = (char *)malloc(filelen * sizeof(char)); // Enough memory for the file
    fread(buffer, filelen, 1, fptr); // Read in the entire file
    // print to our text file output the beginnings of a c-style array
    fprintf(txtoutptr, "unsigned char encodedBytes[%ld] = {\n\t", filelen);
    for (int i = 0; i < filelen; i++) {
        // increase the value by our cypher key in place
        buffer[i] += 69;
        // then write the value as hex into our text output
        char hexChar[5];
        tohex(buffer[i],hexChar);
        fprintf(txtoutptr,"%s%s%s",
            hexChar,
            i+1 == filelen ? "" : ",",
            (i +1) % 12 == 0 ? "\n\t" : " "
        );
        //printf("%c", outBuf[i]);
    }
    // print a closing bracked for our text files array
    fprintf(txtoutptr, "\n};");

    // now write the raw encoded binary data to our output file
    fwrite(buffer, filelen, 1, outptr);

    // free memory and file handles at the end
    free(buffer);
    fclose(fptr); // Close the file
    fclose(outptr);
    fclose(txtoutptr);

    printf("finished writing encoded file.\n");

    return 0;
}

// // simple cesarean cypher example (key = 3)
// void cypher_test() {
//     char inputStr[100];

//     printf("Enter a string: ");
//     gets(inputStr);
//     for(int i = 0; (i < 100 && inputStr[i] != "\0"); i++) {
//         inputStr[i] +=3; // Add the cypher key (3) to the index
//     }
//     printf("encrypted: %s\n", inputStr);
//     for(int i = 0; (i < 100 && inputStr[i] != "\0"); i++) {
//         inputStr[i] -=3; // Add the cypher key (3) to the index
//     }
//     printf("decrypted: %s\n", inputStr);
// }