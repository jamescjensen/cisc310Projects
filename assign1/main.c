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

/** Process struct */
struct process {
    int pid;
    int state;
    int command_index;
    int total_commands;
    int ssd_accesses_time;
    int ssd_wait_time;
    struct command commands[150];
};

/** CPU and hardware struct */
struct hardware {
    struct process proc;
    int counter;
};

/** Queue */
struct queue {
    struct process *procs[26];
    int nextEmpty;
};

// Enqueue a process to the queue.
void enqueue(struct queue *q, struct process *proc) {
    // Add process
    q->procs[q->nextEmpty] = proc;

    // Increment
    q->nextEmpty = q->nextEmpty + 1;
}

// Dequeue and returns the process at position 0 from the queue.
struct process * dequeue(struct queue *q) {
    // Decrement
    q->nextEmpty = q->nextEmpty - 1;

    // Store the process in a variable
    struct process *p = q->procs[0];

    // Shifting processes to the beginning of the queue.
    int i;

    for(i = 0; i < 24; i++) {
        q->procs[i] = q->procs[i+1];
    }

    return p;
}

void addProcessIO(struct queue *io, struct process *proc)
{
    // Add process
    io->procs[io->nextEmpty] = proc;

    // Increment
    io->nextEmpty = io->nextEmpty + 1;

    // Sort by IO duration
    int i, j;
    struct process *p;

    for (i = 0; i < io->nextEmpty; ++i)
    {
        for (j = i + 1; j < io->nextEmpty; ++j)
        {
            if (io->procs[i]->commands[io->procs[i]->command_index].time > io->procs[j]->commands[io->procs[i]->command_index].time)
            {
                p =  io->procs[i];
                io->procs[i] = io->procs[j];
                io->procs[j] = p;
            }
        }
    }

}

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
    pcs.total_commands = 0;

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
}


// Main function
int main (int argc, char *argv[])
{
    char *input = "input.txt"; // File containing the commands

    // Initialize Process Table
    struct process process_table[25];

    // Initialize Finish Process
    struct process finish_process[25];

    // Initialize CPU 1
    struct hardware cpu1;
    cpu1.counter = 0;

    // Initialize CPU 2
    struct hardware cpu2;
    cpu2.counter = 0;

    // Initialize SSD
    struct hardware ssd;
    ssd.counter = 0;

    // Initialize Waiting queue
    struct queue io;
    io.nextEmpty = 0;

    // Initialize Ready queue.
    struct queue ready_q;
    ready_q.nextEmpty = 0;

    // Initialize SSD queue.
    struct queue ssd_q;
    ssd_q.nextEmpty = 0;


    // Read the file with the commands.
    readCommands(input, process_table);

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

        printf("\n");
    }

    // Setting the total commands and reseting the command_index of each process to 0;
    for(i=0;i<process_ctr;i++) {
        process_table[i].total_commands = process_table[i].command_index - 1;
        process_table[i].command_index = 0;
    }

    /*
    addProcessIO(&io, &process_table[2]);
    addProcessIO(&io, &process_table[1]);
    addProcessIO(&io, &process_table[0]);
    addProcessIO(&io, &process_table[1]);
    addProcessIO(&io, &process_table[0]);

    for(i=0; i < 5; i++)
    {
        printf("%d\n", io.procs[i]->commands[io.procs[i]->command_index].time);
    }
    */

    /*
    printf("%d\n", cpu1.counter);
    printf("%d", sizeof(cpu1.proc));
    */
    /*
    enqueue(&ready_q, &process_table[0]);

    printf("process command index: %d\n", process_table[0].command_index);
    printf("Process in queue %d\n", ready_q.procs[0]->command_index);

    process_table[0].command_index = 848;

    printf("process command index: %d\n", process_table[0].command_index);
    printf("Process in queue %d", ready_q.procs[0]->command_index);
    */
    /*
    enqueue(&ready_q, &process_table[0]);
    printf("Next int: %d\n", ready_q.nextEmpty);

    enqueue(&ready_q, &process_table[1]);
    printf("Next int: %d\n", ready_q.nextEmpty);

    printf("Command index: %d\n", dequeue(&ready_q)->command_index);
    printf("Next int: %d\n", ready_q.nextEmpty);

    printf("Command index: %d\n", ready_q.procs[0]->command_index);

    printf("Command index: %d\n", dequeue(&ready_q)->command_index);
    printf("Next int: %d\n", ready_q.nextEmpty);

    printf("Command index: %d", ready_q.procs[0]->command_index);
    */


    // TODO Implement main logic

    // TODO create a "currentCalls" array that will hold the calls that need to be executed in the
    // current time stamp. This is just one way of implementing it. There might other ways.

    // TODO remember this from the projetct description: "If multiple requests are made at the
    // same time you should allocate (1) CPU, (2) SSD, and (3) INP"


    // Finish program
    return 0;
};
