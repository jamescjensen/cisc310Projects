#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RUNNING 0
#define READY 1
#define WAITING 2
#define FINISHED 4

#define NEW 10
#define SSD 11
#define INP 12

struct process {
    int state;
    int id;
    int next_index;
    int ssd_accesses;
    int wait_time;
    struct command *commands[150];
};

struct command {
    int name;
    int time;
};

/*
struct ssd {
    process *pcs;
};

struct cpu {
    process *pcs;
};

struct cpu_q {
    cpu *cpus;
};

struct ssd_q {
    ssd *ssds;
};
*/
void readCommands(char commands[]) {
    FILE * filePointer; // File pointer
    filePointer = fopen(commands, "r"); //opens the filename pointed to by filename using the given mode.
    char line[128]; // variable that holds each line that is read

    // File EOF. Keep reading until the file pointer reaches the end of the file
    while(!feof(filePointer)) {
        // Gets a line from the file
        fgets(line, 128, filePointer);
        char * pch;
        pch = strtok (line, " ");

        while(pch != NULL) {

            if (strcmp(pch,"NEW")==0) {
                printf("new\n");
            } else if(strcmp(pch,"CPU")== 0) {
                printf("cpu\n");
            } else if(strcmp(pch,"INP")== 0) {
                printf("inp\n");
            }

            pch = strtok (NULL, " ");

            if(pch != NULL) {
                printf ("le number is %s\n", pch);
            }

        }
        // Print in command line
        //fputs(line, stdout);
    }

    // Closing the file
    fclose(filePointer);
}

int main (int argc, char *argv[] ) {
    static const char commands[] = "input.txt"; // File containing the commands
    extern struct 
    readCommands(commands);
    return 0;
};




