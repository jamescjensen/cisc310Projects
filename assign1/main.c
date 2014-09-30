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

/** CPU and SSD struct */
struct hardware {
    int pid;
    int busy; // If the hardware is being used or not.
    int finish_time; // The global time when the process will be done using that hardware. If start time of process is 120 and it uses the CPU for 15, the finish_time should be 135.
};

/** Queue */
struct queue {
    int pid[26];
    int nextEmpty;
};

// Enqueue a process to the queue.
void enqueue(struct queue *q, int pid) {
    // Add process
    q->pid[q->nextEmpty] = pid;

    // Increment
    q->nextEmpty = q->nextEmpty + 1;
}

// Dequeue and returns the process at position 0 from the queue.
int dequeue(struct queue *q) {
    // Decrement
    q->nextEmpty = q->nextEmpty - 1;

    // Store the process in a variable
    int pid = q->pid[0];

    // Shifting processes to the beginning of the queue.
    int i;

    for(i = 0; i < 24; i++) {
        q->pid[i] = q->pid[i+1];
    }

    return pid;
}

void move_to_WAITING_INPUT(struct queue *io, int pid, struct process process_table[])
{
    // Set state to waiting
    int i = 0;

    while(process_table[i].pid != pid) {
        i++;
    }

    process_table[i].state = WAITING;

    // Add process
    io->pid[io->nextEmpty] = pid;

    // Increment
    io->nextEmpty = io->nextEmpty + 1;

    // Sort by IO duration
    int j, process_id;
    //struct process *p;

    for (i = 0; i < io->nextEmpty; ++i)
    {
        for (j = i + 1; j < io->nextEmpty; ++j)
        {
            if (process_table[i].commands->time > process_table[j].commands->time)
            {
                process_id =  io->pid[i];
                io->pid[i] = io->pid[j];
                io->pid[j] = process_id;
            }
        }
    }

}

/*
void move_to_READY(struct queue *ready,  int pid, struct process process_table[])
{
    // Set state to ready
    int i = 0;

    while(process_table[i].pid != pid) {
        i++;
    }

    process_table[i].state = READY;

    // Add process
    ready->pid[ready->nextEmpty] = pid;

    // Increment
    ready->nextEmpty = ready->nextEmpty + 1;
}
*/

// Method that creates and returns a process struct
struct process create_new_process()
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
struct command create_command(int name, int time)
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
void read_commands(char *commands, struct process process_table[])
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
            process_table[process_ctr] = create_new_process();
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
        process_table[process_ctr-1].commands[process_table[process_ctr-1].command_index] = create_command(cmd_name, time);

        // Increment the command index
        process_table[process_ctr-1].command_index++;
        process_table[process_ctr-1].total_commands++;
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
    cpu1.busy = 0;

    // Initialize CPU 2
    struct hardware cpu2;
    cpu2.busy = 0;

    // Initialize SSD
    struct hardware ssd;
    ssd.busy = 0;

    // Initialize IO priority queue
    struct queue io_q;
    io_q.nextEmpty = 0;

    // Initialize Ready queue.
    struct queue ready_q;
    ready_q.nextEmpty = 0;

    // Initialize SSD queue.
    struct queue ssd_q;
    ssd_q.nextEmpty = 0;


    // Read the file with the commands.
    read_commands(input, process_table);


    // Setting the total commands and reseting the command_index of each process to 0;
    for(i=0;i<process_ctr;i++) {
        process_table[i].total_commands = process_table[i].command_index - 1;
        process_table[i].command_index = 0;
    }



    // Testing code to check if the process were created correctly
    int i, j;

    for(i=0;i<process_ctr;i++) {

        printf("PID %d\n", process_table[i].pid);
        printf("STATE %d\n", process_table[i].state);
        printf("COMMAND_INDEX %d\n", process_table[i].command_index);
        printf("TOTAL_COMMANDS %d\n", process_table[i].total_commands);
        printf("SSD_ACCESS_TIME %d\n", process_table[i].ssd_accesses_time);
        printf("SSD_WAIT_TIME %d\n", process_table[i].ssd_wait_time);

        for(j=0;j<process_table[i].command_index;j++) {
            printf("\tNAME %d", process_table[i].commands[j].name);
            printf("\tTIME %d\n", process_table[i].commands[j].time);
        }

        printf("\n");
    }


    // TODO Implement main logic

    // TODO Main loop that checks CPU1, CPU2, SSD, INP, PROCESS_TABLE

        // TODO check if all processes are FINISHED

        // TODO CPU1() // State: RUNNING // WILL
            // Remove current process, meaning that set the struct to not busy
            // Execute its next command and place in corresponding struct, queue, or array
            // Go to READY queue and fetch the next command

        // TODO CPU2() // State: RUNNING // WILL
            // Remove current process, meaning that set the struct to not busy
            // Execute its next command and place in corresponding struct, queue, or array
            // Go to READY queue and fetch the next command

        // TODO SSD() // State: WAITING // MIGUEL
            // Remove current process, meaning that set the struct to not busy
            // Execute its next command and place in corresponding struct, queue, or array
            // Go to SSD queue and fetch the next command

        // TODO INP() // State: WAITING // ANDREW
            // Remove current process from the priority queue IO
            // Execute its next command and place in corresponding CPU or SSD. If not possible, put int CPU_queue or SSD_queue

        // TODO PROCESS_TABLE() // State: RUNNING(If it can put process in CPU) or READY(If it cannot put process in CPU) // ANNE
            // Put process in CPU or READY_q

        // TODO move_to_FINISHED(pid) // FINISHED


    // TODO Loop through the process table printing the information about each process // JIMMY
    /*
    move_to_WAITING(&io, &process_table[2]);
    move_to_WAITING(&io, &process_table[0]);
    move_to_WAITING(&io, &process_table[1]);


    for(i=0; i < 3; i++)
    {
        printf("Time %d\n", io.procs[i]->commands[io.procs[i]->command_index].time);
        printf("State in IO %d\n", io.procs[i]->state);
    }

     for(i=0;i<process_ctr;i++) {

        printf("PID %d\n", process_table[i].pid);
        printf("STATE %d\n", process_table[i].state);


        printf("\n");
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




    // Finish program
    return 0;
};
