#include <stdio.h>
#include "hospital.h"
#include "filehandling.h"

void saveBedOccupancyStatus()
{
    FILE *file;

    file = fopen("src/beds_status.txt", "w");
    for(int i=0;i<NUM_OF_WARDS;i++)
    {
        for(int j=0;j<bedCapacity[i];j++)
        {
            fprintf(file, "%d ", bedAvailabilityStatus[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("\nBed occupancy status saved successfully.\n");
}


void loadBedOccupancyStatus()
{
    FILE *file;
    file = fopen("src/beds_status.txt", "r");
    for(int i=0;i<NUM_OF_WARDS;i++)
    {
        for(int j=0;j<bedCapacity[i];j++)
        {
            fscanf(file, "%d", &bedAvailabilityStatus[i][j]);
        }
    }
    fclose(file);
}
