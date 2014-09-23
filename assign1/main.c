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
    int state;
    int pid;
    int next_index;
    int ssd_accesses;
    int wait_time;
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

void createNewProcess()
{
    //printf("createNew\n");
    process_ctr++;
    pid_ctr++;
    struct process *pcs;
    pcs = (struct process *) malloc(sizeof(struct process*));
    pcs->state = READY;
    pcs->pid = pid_ctr;
    pcs->next_index = 0;
    pcs->ssd_accesses = 0;
    pcs->wait_time = 0;
    process_table[process_ctr] = pcs;
    //printf("%d\n", process_table[process_ctr]->pid);
}

void addCommandToProcess(int name, int time)
{
    process_table[process_ctr]->next_index++;
    int tmp = process_table[process_ctr]->next_index;
    struct command *cmd;
    cmd = (struct command*) malloc(sizeof(struct command*));
    cmd->name = name;
    cmd->time = time;
    process_table[process_ctr]->commands[tmp] = *cmd;
    printf("le %d\n", process_table[process_ctr]->commands[tmp].name);
    printf("le %d\n", process_table[process_ctr]->commands[tmp].time);
}


void readCommands(char *commands) {
    FILE * filePointer; // File pointer
    filePointer = fopen(commands, "r"); //opens the filename pointed to by filename using the given mode.
    char line[128]; // variable that holds each line that is read

    // File EOF. Keep reading until the file pointer reaches the end of the file
    while(!feof(filePointer)) {
        // Gets a line from the file
        fgets(line, 128, filePointer);

        char * pch; // TODO what is this?
        pch = strtok (line, " "); // string operations

        while(pch != NULL) {
            int cmd_name;
            if (strcmp(pch,"NEW")==0) {
                createNewProcess();
                cmd_name = NEW;
            } else if(strcmp(pch,"CPU")==0) {
                cmd_name = CPU;
            } else if(strcmp(pch,"INP")==0) {
                cmd_name = INP;
            }

            pch = strtok (NULL, " ");

            if(pch != NULL) {
                printf ("le number is %s\n", pch);
                addCommandToProcess(cmd_name, atoi(pch));
            }

        }
        //fputs(line, stdout);
    }

    // Closing the file
    fclose(filePointer);
}

int main (int argc, char *argv[]) {
    char *input = "input.txt"; // File containing the commands
    //// TODO this was creating an compile error when not commented.
    readCommands(input);
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
    return 0;
};



