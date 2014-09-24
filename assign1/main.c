#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READY 0
#define RUNNING 1
#define WAITING 2
#define FINISHED 4

#define NEW 10
#define INP 11
#define CPU 12

int process_ctr = 0;
int pid_ctr = 0;

struct command {
    int name;
    int time;
};

struct process {
    int pid;
    int state;
    int command_index;
    int ssd_accesses_time;
    int ssd_wait_time;
    struct command commands[150];
};

struct process createNewProcess()
{
    struct process pcs;
    pcs.state = READY;
    pcs.pid = pid_ctr;
    pcs.command_index = 0;
    pcs.ssd_accesses_time = 0;
    pcs.ssd_wait_time = 0;
    return pcs;
}


struct command addCommandToProcess(int name, int time)
{
    struct command cmd;
    cmd.name = name;
    cmd.time = time;
    return cmd;
}

void readCommands(char *commands, struct process process_table[]) {
    FILE * filePointer; // File pointer
    filePointer = fopen(commands, "r"); //opens the filename pointed to by filename using the given mode.
    char line[128]; // variable that holds each line that is read
    char command[10]; // command
    int time; // time or start time of command

    // Run while fscanf successfully reads in 2 variables
    while(fscanf(filePointer, "%s %d", command, &time) == 2) {
        int cmd_name;
        if (strcmp(command,"NEW")==0) {
            process_table[process_ctr] = createNewProcess();
            cmd_name = NEW;
            pid_ctr++;
            process_ctr++;
        } else if(strcmp(command,"CPU")==0) {
            cmd_name = CPU;
        } else if(strcmp(command,"INP")==0) {
            cmd_name = INP;
        }
        process_table[process_ctr-1].commands[process_table[process_ctr-1].command_index] = addCommandToProcess(cmd_name, time);
        process_table[process_ctr-1].command_index++;
    }

    // Closing the file
    fclose(filePointer);
}

int main (int argc, char *argv[]) {
    char *input = "input.txt"; // File containing the commands

    struct process process_table[25]; // Process Table
    struct process cpu_1[2]; //Initialize CPU 1
    struct process cpu_2[2]; // Initialize CPU 2
    struct process ssd[2]; // Initialize SSD
    struct process finish_process[25]; // Finish Process

    // TODO Initialize Ready queue.
    // TODO Initialize SSD queue.
    // TODO Initialize Waiting queue.

    // Read the file with the commands.
    readCommands(input, process_table);

    // TODO how was thing compiling? You cannot do for(int....
    //printf("\nballer %lu\n", sizeof(process_table[0].commands[0]));
    //printf("\n name %d time %d\n", process_table[0].commands[0].name, process_table[0].commands[0].time);
    for(int i=0;i<process_ctr;i++) {
        printf("PID %d\n", process_table[i].pid);
        printf("STATE %d\n", process_table[i].state);
        printf("COMMAND_INDEX %d\n", process_table[i].command_index);
        printf("SSD_ACCESS_TIME %d\n", process_table[i].ssd_accesses_time);
        printf("SSD_WAIT_TIME %d\n", process_table[i].ssd_wait_time);
        for(int j=0;j<process_table[i].command_index;j++) {
            printf("\tNAME %d", process_table[i].commands[j].name);
            printf("\tTIME %d\n", process_table[i].commands[j].time);
        }
    }
    return 0;
};



