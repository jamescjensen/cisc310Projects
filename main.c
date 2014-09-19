#include <stdio.h>
#include <stdlib.h>

void readCommands(char commands[]) {
    FILE * filePointer; // File pointer
    filePointer = fopen(commands, "r"); //opens the filename pointed to by filename using the given mode.
    char line[128]; // variable that holds each line that is read

    // File EOF. Keep reading until the file pointer reaches the end of the file
    while(!feof(filePointer)) {
        // Gets a line from the file
        fgets(line, 128, filePointer);

        // Print in command line
        fputs(line, stdout);
    }

    // Closing the file
    fclose(filePointer);
}


int main (int *argc, char *argv[] ) {
    static const char commands[] = "input.txt"; // File containing the commands

    readCommands(commands);
    return 0;
};




