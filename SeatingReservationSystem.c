#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


typedef struct CustomerRec{
    char seatID[4];  //Unique seat ID
    bool assignmentStatus;
    char *firstName;
    char *lastName;
}CustomerRec;


//Function Declarations
void populateCustomerInfo(CustomerRec *custInfo);
void displayMenu(CustomerRec *custInfo, int size);
void displayEmptySeat(CustomerRec *cr, int size);
void displayNameAndSeat(CustomerRec *cr, int size);
void displayAllSeats(CustomerRec *cr, int size);
void assignSeat(CustomerRec *cr, int size);
void deleteSeat(CustomerRec *cr, int size);


   
int main(){
    int size = 20;
    CustomerRec *custInfo = (CustomerRec*)malloc(sizeof(CustomerRec)*20);
    if(custInfo ==NULL){
        printf("Memory not allocated.\n");
        return 1;    
    }
    
    populateCustomerInfo(custInfo);
      
    displayMenu(custInfo, size);

    //Free memory
    for (int i = 0; i < 20; i++) {
        free(custInfo[i].firstName);
        free(custInfo[i].lastName);
    }
    free(custInfo);
    
    
    return 0;
}

void populateCustomerInfo(CustomerRec *custInfo){

    char* firstName[7] = {"Emily", "Liam", "Sophia", "Noah", "Olivia", "Ethan", "Ava"};
    char* lastName[6] = {"Smith", "Patel", "Tremblay", "Singh", "Leblanc", "Chen"};
    char IDLetter[4] = {'A', 'D', 'G', 'K'};
    int seatIndex = 0;
    
    //Id - rowNum + A/D/G/K, each row has 4, 
  // Seed the random number generator
    srand(time(NULL));

    for (int row = 1; row <= 5; row++) {
        for (int seat = 0; seat < 4; seat++) { 
            sprintf(custInfo[seatIndex].seatID,"%d%c" ,row , IDLetter[seat]); // Generate a unique seat ID
            
            custInfo[seatIndex].assignmentStatus = rand() % 2;  // Randomly assign 0 or 1 to assignment status
            // Randomly assign a first name and last name, but first dynamically allocate memory
            
            custInfo[seatIndex].firstName = malloc(strlen(firstName[rand() % 7]) + 1);
            strcpy(custInfo[seatIndex].firstName, firstName[rand() % 7]);
            
            custInfo[seatIndex].lastName = malloc(strlen(lastName[rand() % 6]) + 1);
            strcpy(custInfo[seatIndex].lastName, lastName[rand() % 6]);

            seatIndex++;
        }
        
    }

}


void displayEmptySeat(CustomerRec *cr, int size){
    printf("\nList of Empty Seats:\n");
    for (int i = 0; i < size; i++){
        if(cr[i].assignmentStatus == 0){
            printf(" %s \n", cr[i].seatID);
        }
    } 
}

//displays list of assigned seats
void displayNameAndSeat(CustomerRec *cr, int size){
    printf("\nList of Assigned Seats:\n");
    for(int i = 0; i<size; i++){
        if(cr[i].assignmentStatus == 1 ){
        printf("%s: %s %s \n", cr[i].seatID, cr[i].firstName, cr[i].lastName);      
        }
    }
}

//displays every seat with customer or empty if it is not assigned
void displayAllSeats(CustomerRec *cr, int size){

    printf("\nList of All Seats:\n");
     for(int i = 0; i<size; i++){
        if(cr[i].assignmentStatus == 1 ){
        printf("%s: Assignd \n %8s %s \n", cr[i].seatID, cr[i].firstName, cr[i].lastName);      
        }else{
            printf("%s: Empty \n", cr[i].seatID);      
        }
    }
}

void assignSeat(CustomerRec *cr, int size){
   //change 0 to 1 after assigning 
   
   char seatChoice[3];
   char firstName[50];
   char lastName[50];
   
   printf("\nEnter seat ID to assign customer: ");
   scanf("%s", seatChoice);
   
   for(int i = 0; i <size; i++){
        if(cr[i].assignmentStatus == 1 && !strcmp(cr[i].seatID, seatChoice)){
            printf("Invalid seat ID. Customer not assigned\n");
        }else if(!strcmp(cr[i].seatID, seatChoice) && cr[i].assignmentStatus == 0){        
            printf("Enter customer first name: ");
            scanf("%s", cr[i].firstName);
            
            printf("Enter customer last name: ");
            scanf("%s", cr[i].lastName);
            
            free(cr[i].firstName);
            free(cr[i].lastName);
        
            cr[i].firstName = malloc(strlen(firstName) + 1);
            strcpy(cr[i].firstName, firstName);
            
            cr[i].lastName = malloc(strlen(lastName) + 1);
            strcpy(cr[i].lastName, lastName);
            
            printf("Customer Assigned to seat %s. ", seatChoice);
            strcpy(cr[i].seatID, seatChoice);
            
            cr[i].assignmentStatus = 1;
            return;
        }
   }
   printf("Invalid seat ID. Customer not assigned\n");
}

void deleteSeat(CustomerRec *cr, int size){
    //Unassign, change to null
  
    char seatChoice[3];
   
    printf("\nEnter seat ID to delete assignment: ");
    scanf("%s", seatChoice);
    
    for(int i = 0; i <size; i++){
        if(cr[i].assignmentStatus == 0 && !strcmp(cr[i].seatID, seatChoice)){
            printf("Invalid seat ID or no assignment found. No assignment Deleted\n");
        }else if(!strcmp(cr[i].seatID, seatChoice) && cr[i].assignmentStatus == 1){
            //free(cr[i].firstName); 
            cr[i].firstName = NULL;
            
            //free(cr[i].lastName);
            cr[i].lastName = NULL;  
                     
            cr[i].assignmentStatus = 0;
        }
    }
}

void displayMenu(CustomerRec *cr, int size){

    char* option = malloc(sizeof(char*));
   
    //displayFunction = & //an actual function
    //function pointer
    void (*displayFunction)(CustomerRec *cr, int size) = NULL;  //customer records, size of custom  4


    while(1){   
        printf("\nMenu: \n");
        printf("a) Display the list of empty seats. \n");
        printf("b) Display the list of names with their corresponding seats.\n");
        printf("c) Display the list of all seats.\n");
        printf("d) Assign a customer to a seat\n");
        printf("e) Delete a seat assignment.\n");
        printf("f) Quit\n");
        printf("Enter your choice (a-f): ");
        
        scanf("%s", option);
        
        //Empty seats
        if(*option == 'a'){ 
            displayFunction = displayEmptySeat; 
            displayFunction(cr, size);
        }
        //List of assigned seats
        else if(*option == 'b'){ 
            displayFunction = displayNameAndSeat; 
            displayFunction(cr, size);
        }
        //list of all seats.
        else if(*option == 'c'){
            displayFunction = displayAllSeats; 
            displayFunction(cr, size);
        }
        //Assign customer
         else if(*option == 'd'){
            displayFunction = assignSeat; 
            displayFunction(cr, size);
        }
        //Delete customer
         else if(*option == 'e'){
            displayFunction = deleteSeat; 
            displayFunction(cr, size);
        }       
        else if(*option == 'f'){ 
            break;
        }else{
            printf("\nEnter a valid option\n");
        }  
         
    }
    
    free(option);
}





