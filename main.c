#include <stdio.h>

#include "hospital.h"

int main()
{

    int choice;
    do
    {
        displayMainMenu();
        printf("Input an option : ");
        if(scanf("%d", &choice)!= 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while(getchar()!= '\n'){}
            choice = -1;
            continue;
        }
        switch(choice)
        {
            case 1:
                clearScreen();
                registerPatient();
                break;
            case 2:
                clearScreen();
                displayRegisteredPatientsByPriority();
                //display function, Bed Occupancy        by sorting , by search
                break;
            case 3:
                clearScreen();
                displayBedAvailability();
                break;
            case 4:
                clearScreen();
                performanceReportsSubMenu();
                //Reports function
                break;
            case 5:
                //Save data
                break;
            case 6:
                clearScreen();
                printf("\n\nExited the program\n\n");
                break;
            default:
                clearScreen();
                printf("\nWring Input. please input a number between 1-6\n");
                break;
        }
    }while(choice!=6);



    return 0;
}
