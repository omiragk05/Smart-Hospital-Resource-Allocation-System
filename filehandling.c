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


void savePatientRecords()
{
    FILE *file;
    file = fopen("src/patient_records.txt", "a");
    if(file == NULL)
    {
        printf("\nCould not save patient records.\n");
        return;
    }

    for(int i=0;i<numberOfPatients;i++)
    {
        fprintf(file,"PAT-%04d,%s,%d,%d,%d,%d,%d,%d,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf\n",
                i + 1,
                patientName[i],
                patientAge[i],
                patientSpecialtyID[i] + 1,
                patientUrgencyLevel[i],
                patientWardID[i],
                patientBedNumber[i] + 1,
                patientDaysAdmitted[i],
                patientWaitingTime[i],
                patientBaseConsultationFee[i],
                patientEmergencySurcharge[i],
                patientWardCost[i],
                patientGrossTotal[i],
                patientDiscount[i],
                patientFinalPayable[i]);
    }

    fclose(file);
    printf("\nPatient records saved successfully.\n\n");
}
