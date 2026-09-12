#include <stdio.h>

void displayMainMenu();

int main()
{
    displayMainMenu();
    int choice;
    do
    {
        printf("Input an option : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:

                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                break;
        }
    }while(choice!=5);

    printf("\nExited the program");

    return 0;
}
