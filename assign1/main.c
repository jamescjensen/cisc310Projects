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
    int id;
    int state;
    int next_index;
    int ssd_accesses;
    int wait_time_ssd;
    int time_ssd;
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

        char * pch; // TODO what is this?
        pch = strtok (line, " "); // TODO what is this doing?

        while(pch != NULL) {
            // TODO Be careful since it might be reading the new lines as a separate character
            // TODO is this doing string comparison?
            if (strcmp(pch,"NEW")==0) {
                printf("NEW\n");
                // TODO create a new process struct
            } else if(strcmp(pch,"CPU")== 0) {
                printf("CPU\n");
            } else if(strcmp(pch,"INP")== 0) {
                printf("INP\n");
            }

            // TODO what is this doing?
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

// Method that creates and initializes a struct.
void createStruct() { // TODO some information about the process should be passed to this function.
    static int processId = 0;

    printf("%d\n", processId);


    processId++;
}

int main (int argc, char *argv[]) {
    static const char input[] = "input.txt"; // File containing the commands
    //extern struct // TODO this was creating an compile error when not commented.
    readCommands(input);
    return 0;
};




