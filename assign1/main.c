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

struct process *process_table[25];
int process_ctr = 0;
int pid_ctr = 0;

struct command {
    int name;
    int time;
};

struct process {
    int pid;
    int state;
    int next_index;
    int ssd_accesses_time;
    int ssd_wait_time;
    struct command commands[150];
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

// TODO make it simpler
void createNewProcess()
{
    //printf("createNew\n");
    process_ctr++;
    pid_ctr++;
    struct process *pcs;

    /*
    pcs = (struct process *) malloc(sizeof(struct process*));
    pcs->state = READY;
    pcs->pid = pid_ctr;
    pcs->next_index = 0;
    pcs->ssd_accesses = 0;
    pcs->wait_time = 0;
    process_table[process_ctr] = pcs;
    //printf("%d\n", process_table[process_ctr]->pid);
    */
}


// TODO make it simpler
void addCommandToProcess(int name, int time)
{
    process_table[process_ctr]->next_index++;
    int tmp = process_table[process_ctr]->next_index;
    struct command *cmd;
    cmd = (struct command*) malloc(sizeof(struct command*));
    cmd->name = name;
    cmd->time = time;
    process_table[process_ctr]->commands[tmp] = *cmd;
    printf("The process name is %d\n", process_table[process_ctr]->commands[tmp].name);
    printf("The time of the process is %d\n", process_table[process_ctr]->commands[tmp].time);
}


void readCommands(char *commands) {
    FILE * filePointer; // File pointer
    filePointer = fopen(commands, "r"); //opens the filename pointed to by filename using the given mode.
    char line[128]; // variable that holds each line that is read
    char command[10]; // command
    int time; // time or start time of command

    // Run while fscanf successfully reads in 2 variables
    while(fscanf(filePointer, "%s %d", command, &time) == 2) {
        int cmd_name;

        printf("Command: %s ", command);
        if (strcmp(command,"NEW")==0) {
            //createNewProcess(); // TODO this creates a problem
            cmd_name = NEW;
        } else if(strcmp(command,"CPU")==0) {
            cmd_name = CPU;
        } else if(strcmp(command,"INP")==0) {
            cmd_name = INP;
        }

        printf("Time: %d\n", time);
        //addCommandToProcess(cmd_name, atoi(time)); // TODO this creates a problem

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
    readCommands(input);

    // TODO how was thing compiling? You cannot do for(int....
    /*
    for(int i=1;i<process_ctr;i++) {
        printf("%d\n", process_table[i]->pid);
        printf("%d\n", process_table[i]->state);
        printf("%d\n", process_table[i]->next_index);
        printf("%d\n", process_table[i]->ssd_accesses);
        printf("%d\n", process_table[i]->wait_time);
            printf("sup1\n");
        for(int j=1;j<process_table[i]->next_index;j++) {
            printf("sup\n");
            printf("%d\n", process_table[i]->commands[j].name);
            printf("%d\n", process_table[i]->commands[j].time);
        }
    }
    */
    return 0;
};



