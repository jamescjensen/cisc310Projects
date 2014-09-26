#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Constants */
#define READY 0
#define RUNNING 1
#define WAITING 2
#define FINISHED 4

#define NEW 10
#define INP 11
#define CPU 12
#define SSD 13

/** Global variables */
int process_ctr = 0;
int pid_ctr = 0;

/** Command struct */
struct command {
    int name;
    int time;
};

/** Command struct */
struct process {
    int pid;
    int state;
    int command_index;
    int ssd_accesses_time;
    int ssd_wait_time;
    struct command commands[150];
};

/** CPU and hardware struct */
struct hardware {
    struct process proc;
    int counter;
};

/*
struct cpu_2 {
    struct process cpu2_proc;

    int cpu2_counter;
};

struct ssd {
    struct process ssd;

    int ssd_counter;
};
*/

// TODO create a queue struct
// TODO implement queue function (Insert an element)
// TODO implement deque function (Remove element)

// Method that creates and returns a process struct
struct process createNewProcess()
{
    // Create a process struct
    struct process pcs;

    // Initialize the variables in that process
    pcs.state = READY;
    pcs.pid = pid_ctr;
    pcs.command_index = 0;
    pcs.ssd_accesses_time = 0;
    pcs.ssd_wait_time = 0;

    // Return the struct
    return pcs;
}

// Method that creates a command
struct command createCommand(int name, int time)
{
    // Create command struct
    struct command cmd;

    // Initialize variables
    cmd.name = name;
    cmd.time = time;

    // Return struct
    return cmd;
}

// Reads the input file and creates a process.
void readCommands(char *commands, struct process process_table[])
{
    FILE * filePointer; // File pointer
    filePointer = fopen(commands, "r"); // Opens the filename pointed to by commands using the given mode.
    char line[128]; // Variable that holds each line that is read
    char command[10]; // Command
    int time; // Time or start time of command

    // Run while fscanf successfully reads in 2 variables and store the first part as
    // a string and the second as an int
    while(fscanf(filePointer, "%s %d", command, &time) == 2) {
        int cmd_name;

        // Parsing the commands
        if (strcmp(command,"NEW")==0) {
            // Create process
            process_table[process_ctr] = createNewProcess();
            cmd_name = NEW;

            // Increment process id
            pid_ctr++;

            // Increment process counter
            process_ctr++;
        } else if(strcmp(command,"CPU")==0) {
            // Access CPU
            cmd_name = CPU;

        } else if(strcmp(command,"INP")==0) {
            // Access INP
            cmd_name = INP;

        } else if(strcmp(command,"SSD")==0) {
            // Access SSD
            cmd_name = SSD;

        }

        // Access the process table and get the created process. Access the commands array of that
        // process at position of the command index. Create a command in that position.
        process_table[process_ctr-1].commands[process_table[process_ctr-1].command_index] = createCommand(cmd_name, time);

        // Increment the command index
        process_table[process_ctr-1].command_index++;
    }

    // Close the file
    fclose(filePointer);

    // TODO go through all the processes created reseting the command_index to 0.

}

// Main function
int main (int argc, char *argv[])
{
    char *input = "input.txt"; // File containing the commands

    struct process process_table[25]; // Initialize Process Table
    struct process finish_process[25]; // Initialize Finish Process

    // Initialize CPU 1
    struct hardware cpu1;
    cpu1.counter = 0;

    // Initialize CPU 2
    struct hardware cpu2;
    cpu2.counter = 0;

    // Initialize SSD
    struct hardware ssd;
    ssd.counter = 0;
    /*
    struct process cpu_2[2]; // Initialize CPU 2
    struct process ssd[2]; // Initialize SSD
    */

    // TODO have to implement a queue struct.
    // TODO Initialize Ready queue.
    // TODO Initialize SSD queue.
    // TODO Initialize Waiting queue.

    // Read the file with the commands.
    readCommands(input, process_table);

    // TODO besides adding the newly created processes to the process_table, which
    // is done in the readCommands function, we need to add them to the Ready queue.
    // This step needs to be implemented. You can do it here, inside readCommands,
    // or implement a separate function. Make your choice.

    // TODO add processes to Ready queue

    // Testing code to check if the process were created correctly
    int i, j;

    for(i=0;i<process_ctr;i++) {
        printf("PID %d\n", process_table[i].pid);
        printf("STATE %d\n", process_table[i].state);
        printf("COMMAND_INDEX %d\n", process_table[i].command_index);
        printf("SSD_ACCESS_TIME %d\n", process_table[i].ssd_accesses_time);
        printf("SSD_WAIT_TIME %d\n", process_table[i].ssd_wait_time);

        for(j=0;j<process_table[i].command_index;j++) {
            printf("\tNAME %d", process_table[i].commands[j].name);
            printf("\tTIME %d\n", process_table[i].commands[j].time);
        }

        process_table[i].command_index = 0;
        printf("COMMAND_INDEX %d\n", process_table[i].command_index);
    }

    printf("%d\n", cpu1.counter);
    printf("%d", sizeof(cpu1.proc));
    // End of testing code


    // TODO Implement main logic

    // TODO create a "currentCalls" array that will hold the calls that need to be executed in the
    // current time stamp. This is just one way of implementing it. There might other ways.

    // TODO remember this from the projetct description: "If multiple requests are made at the
    // same time you should allocate (1) CPU, (2) SSD, and (3) INP"


    // Finish program
    return 0;
};
