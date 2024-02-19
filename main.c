#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_Processes 25

//skeleton functions TO-Do:
void initializeProcessHierarchy(){
    //todo
}
void createChild(int process_p){
    //todo
};
void destroy_descendants(int process_p){
    //todo
};
void printPCB(){
    printf("CHANGE PRINTPCB");
};

//MENU of continuous options for the user
//calls functions base on user input
int menu(int option){
    int id;
    switch(option){
        case 1:
            initializeProcessHierarchy();
            break;
        case 2:
            printf("Enter the parent process id: ");
            scanf("%d", &id);
            createChild(id);
            break;
        case 3:
            printf("Enter the parent process whose descendants are to be destroyed: ");
            scanf("%d", &id);
            destroy_descendants(id);
            break;
        case 4:
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