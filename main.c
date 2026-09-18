#include <stdio.h>

void displayMainMenu();
void registerPatient();
void displayRegisteredPatientsByPriority();
void performanceReportsSubMenu();
void clearScreen();

int main()
{

    int choice;
    do
    {
        displayMainMenu();
        printf("Input an option : ");
        scanf("%d",&choice);
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
                performanceReportsSubMenu();
                //Reports function
                break;
            case 4:
                //Save data
                break;
            case 5:
                clearScreen();
                printf("\n\nExited the program\n\n");
                break;
            default:
                clearScreen();
                printf("\nWring Input. please input a number between 1-5\n");
                break;
        }
    }while(choice!=5);



    return 0;
}
