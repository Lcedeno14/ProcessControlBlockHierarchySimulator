#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//todo use maxProcesses
#define MAX_Processes 25

typedef struct Child {
    int id;
    struct Child* next;
} Child;

typedef struct PCB{
    int parentID ;
    Child* children;
} PCB;
PCB* PCB_array[MAX_Processes];
//skeleton functions TO-Do:
void initializeProcessHierarchy(){
    PCB* first = (PCB*)malloc(sizeof(PCB));
    first ->parentID = -1;
    first ->children = NULL;
    PCB_array[0] = first;
    for (int i =1; i< MAX_Processes; i++){
        PCB_array[i] = NULL;
    }
}
//function finds an open index where a PCB could go
int findOpenPCB(){
    for(int i = 0; i<MAX_Processes;i++){
        if(!PCB_array[i]){
            return i;
        }
    }
        return -1;
}
void appendChild(Child* curr, int c_id){
//case 1: if curr is null
if(!curr){
    curr = (Child*)malloc(sizeof(Child));
    curr ->id = c_id;
}
//case 2: if curr is not null
else{
        appendChild(curr->next,c_id);
}
}
void createChild(int P_ID){
    //find open ID for new child
    int  ChildID = findOpenPCB();
    if(ChildID == -1){ return;}
    //dynamically allocate a PCB
    PCB* child = (PCB*)malloc(sizeof(PCB));
    //add the child to array
    PCB_array[ChildID] = child;
    //initialize the child
    child ->parentID = P_ID;
    child ->children = NULL;
    //add this child to the parents children
    appendChild(PCB_array[P_ID]->children, ChildID);
};
void destroy_descendants(int P_ID){
    //todo recursively call this method to destroy children
    //todo free the memory of each child PCB and linked list node
};
void printPCB(){
    //todo
    printf("CHANGE PRINTPCB");
};

//MENU of continuous options for the user
//calls functions base on user input
int menu(int option){
    int id;
    switch(option){
        case 1://initialize
            initializeProcessHierarchy();
            break;
        case 2://create child
            printf("Enter the parent process id: ");
            scanf("%d", &id);
            createChild(id);
            break;
        case 3://destroy descendants
            printf("Enter the parent process whose descendants are to be destroyed: ");
            scanf("%d", &id);
            destroy_descendants(id);
            break;
        case 4://Quit program and free memory
            printf("Quitting program...");
            //todo free memory
            return 0;
        default:
            return 1;
    }
    printPCB();
    return 1;
}
int main() {
    int option; //menu option
    //move to a function later
    while (1) {
    printf("\nProcess creation and destruction\n");
    printf("--------------------------------\n");
    printf("1) Initialize process hierarchy\n");
    printf("2) Create a new child process\n");
    printf("3) Destroy all descendants of a process\n");
    printf("4) Quit program and free memory\n");
    printf("Enter selection: ");
    scanf("%d", &option);
    if(!menu(option)){
        return 0;
    }

}
}