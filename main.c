#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
void appendChild(Child** head, int c_id){
    Child* newChild = (Child*)malloc(sizeof(Child));
    newChild->id = c_id;
    newChild->next = NULL;

    if(*head == NULL){
        *head = newChild;
    }
    else {
        Child* temp = *head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newChild;
    }
}
bool invalid_id(int id){
    if (id < 0 || id >= MAX_Processes || PCB_array[id] == NULL) {
        return true;
    }
    return false;
}
// Modify the createChild function call to appendChild accordingly.

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
    appendChild(&(PCB_array[P_ID]->children), ChildID);
};
void destroy_descendants(int P_ID){
   //set up
    Child* child = PCB_array[P_ID]->children;
    Child* temp;
    //recursive loop to destroy children
    while (child != NULL) {
        int childID = child->id; // Get the ID of the child
        //recursively destroy the descendants
        if (!invalid_id(childID)) {
            destroy_descendants(childID);
            //free the PCB of the child
            free(PCB_array[childID]);
            PCB_array[childID] = NULL; //
        }

        temp = child; // Hold the current child to free it after moving to the next
        child = child->next; // Move to the next child
        free(temp); // Free the current child node
    }
    PCB_array[P_ID]->children = NULL;
};
void printPCB(){
   printf("Process list:\n");
    for(int i = 0; i < MAX_Processes; i++){
        PCB* curr = PCB_array[i];
        if(curr) {
            printf("Process id: %d\n", i);
            if (curr->parentID != -1) {
                printf("\tParent process: %d\n", curr->parentID);
            } else { printf("\tNo parent process\n"); }
            Child *childProcess = curr->children;
            if (!childProcess) { printf("\tNo child processes\n"); }
            else {
                while (childProcess) {
                    printf("\tChild process: %d\n", childProcess->id);
                    childProcess = childProcess->next;
                }
            }

        }
    }

};

//MENU of continuous options for the user
//calls functions base on user input
int menu(int option){
    int id;
    switch(option){
        case 1://initialize
            initializeProcessHierarchy();
            printf("\n");
            break;
        case 2://create child
            printf("Enter the parent process id: ");
            scanf("%d", &id);
            printf("\n");
            if(invalid_id(id)){break;}
            createChild(id);
            break;
        case 3://destroy descendants
            printf("Enter the parent process whose descendants are to be destroyed: ");
            scanf("%d", &id);
            printf("\n");
            if(invalid_id(id)){break;}
            destroy_descendants(id);
            break;
        case 4://Quit program and free memory
            printf("\n");
            printf("Quitting program...");
            destroy_descendants(0);
            free(PCB_array[0]);
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
    printf("4) Quit program and free memory\n\n");
    printf("Enter selection: ");
    scanf(" %d", &option);
    if(!menu(option)){
        return 0;
    }

}
}