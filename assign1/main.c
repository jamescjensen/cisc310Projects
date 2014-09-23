#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RUNNING 0
#define READY 1
#define WAITING 2
#define FINISHED 3

#define NEW 10
#define SSD 11
#define INP 12


// TODO finish adding the variables needed for each struct.

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

void read_commands(char commands[]) {
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
                // TODO create a new process struct. Then add this command to the command array.
            } else if(strcmp(pch,"CPU")== 0) {
                printf("CPU\n");
                //TODO add this command to the command array of the current process
            } else if(strcmp(pch,"INP")== 0) {
                printf("INP\n");
                //TODO add this command to the command array of the current process
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
void create_struct() { // TODO some information about the process should be passed to this function.
    static int process_id = 0;

    // Create process
    struct process pr;

    // Initialize variables
    pr.id = process_id;
    pr.state = READY;
    pr.next_index = 0;
    pr.ssd_accesses = 0;
    pr.wait_time_ssd = 0;
    pr.time_ssd = 0;
    // struct command *commands[150]; // TODO initialize this struct.

    // Put the process in the Process Table array

    // Put process in ready queue
    printf("%d\n", process_id);

    process_id++;
}

// Method that takes a process and puts the commands for that process in its commands array.
void read_write_commands() {
    //TODO Be sure to include the NEW XXX as the first command.

}

int main (int argc, char *argv[]) {
    static const char input[] = "input.txt"; // File containing the commands
    //extern struct // TODO this was creating an compile error when not commented.

    // TODO Initialize Process Table array.
    // TODO Initialize CPU 1.
    // TODO Initialize CPU 2.
    // TODO Initialize SSD.
    // TODO Initialize Ready queue.
    // TODO Initialize SSD queue.
    // TODO Initialize Waiting queue.
    // TODO Initialize Finished Process array.

    read_commands(input);

    // TODO execute main logic.
    //

    return 0;
};
