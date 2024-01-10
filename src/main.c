#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/sysctl.h>
#include <libproc.h>

#define INSTR1 90
#define INSTR2 80
#define INSTR3 70
#define INSTR4 60
#define INSTR5 50
#define INSTR6 40
#define INSTR7 30
#define INSTR8 20
#define INSTR9 30
#define INSTR10 40
#define INSTR11 50
#define INSTR12 60
#define INSTR13 70
#define INSTR14 80
#define INSTR15 90
#define INSTR16 80
#define INSTR17 70
#define INSTR18 60
#define INSTR19 50
#define INSTR20 40
#define EXIT 10

#define S_QUANTUM 80
#define G_QUANTUM 120
#define P_QUANTUM 120
#define S_TO_G_CYCLE 3
#define G_TO_P_CYCLE 5

#define CONTEXT_SWITCH 10
#define MAX_NUM_PROCESS 10

#define MAX_LINE_LENGTH 1024


typedef struct Process {
    int p_id;
    int priority;
    int arrival;
    int type; //0 = Silver , 1 = Gold , 2 = Plat
    int line;
    int id;
} Process;

typedef struct Manager{

    Process table[MAX_NUM_PROCESS+1];
    int length;
} Manager;

typedef struct PQueue{
    Process *processes;
    int size;
    int maxSize;
}PQueue;

PQueue createPriorityQueue(int capacity) {
    PQueue pq;
    pq.processes = malloc(sizeof(Process) * capacity);
    pq.size = 0;
    pq.maxSize = capacity;
    return pq;
}








Manager parser(char *filename){
    char *token;
    Manager manager;
    manager.length =0;
    char line[MAX_LINE_LENGTH];
    // Delimiters are space, tab, and newline
    FILE *file;
    // Open the file for reading
    file = fopen(filename, "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    int process_counter = 0;

    // Read and display the file content line by line
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        Process new_process;
        new_process.id = process_counter;
        token = strtok(line, " \t\n"); 

        new_process.p_id = (int)(token[1])-48;
        printf("%d ",new_process.p_id);

        token = strtok(NULL, " \t\n"); 
        new_process.priority = atoi(token);
        printf("%d ",new_process.priority);

        token = strtok(NULL, " \t\n"); 
        new_process.arrival = atoi(token);
        printf("%d ",new_process.arrival);

        token = strtok(NULL, " \t\n"); 
        if (token[0] == 'S'){
            new_process.type = 0;
            printf("%d \n",new_process.type);
        }
        else if (token[0] == 'G'){
            new_process.type = 1;
            printf("%d \n",new_process.type);
        }
        else {
            new_process.type = 2;
            printf("%d \n",new_process.type);
        }
        manager.table[manager.length] = new_process;
        
        manager.length++;

    }

    // Close the file
    fclose(file);

    

    return manager;
}


int main(){
    printf("boot \n");
    char filename[] = "definition.txt";
    Manager manager;
    manager = parser(filename);
    

    return 0;
}