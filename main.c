#include <stdio.h>

void displayMainMenu();
void registerPatient();
void displayRegisteredPatientsByPriority();
void performanceReportsSubMenu();


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
                registerPatient();
                break;
            case 2:
                displayRegisteredPatientsByPriority();
                //display function, Bed Occupancy        by sorting , by search
                break;
            case 3:
                performanceReportsSubMenu();
                //Reports function
                break;
            case 4:
                //Save data
                break;
            case 5:
                printf("\nExited the program");
                break;
            default:
                break;
        }
    }while(choice!=5);



    return 0;
}
