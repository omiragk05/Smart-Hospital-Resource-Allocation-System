#include <stdio.h>
#include "hospital.h"
#include "filehandling.h"

void saveBedOccupancyStatus()
{
    FILE *file;

    file = fopen("src/beds_status.txt", "w");
    if(file==NULL)
    {
        printf("\nCould not save bed occupancy status.\n");
        return;
    }
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
    if(file==NULL)
    {
        printf("\nCould not load bed occupancy status.\n");
        return;
    }
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

    for(int i=savedPatientCount;i<numberOfPatients;i++)
    {
        fprintf(file,"%s,%d,%s,%s,%s,%d,%d,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf\n",
                patientName[i],
                patientAge[i],
                specialtyName[patientSpecialtyID[i]],
                patientUrgencyLevel[i]==1?"Normal":patientUrgencyLevel[i]==2?"Urgent":"Critical",
                patientWardID[i]==0?"Not Admitted":wardName[patientWardID[i]-1],
                patientWardID[i]== 0?0 : patientBedNumber[i]+1,
                patientDaysAdmitted[i],
                patientBaseConsultationFee[i],
                patientEmergencySurcharge[i],
                patientWardCost[i],
                patientGrossTotal[i],
                patientDiscount[i],
                patientFinalPayable[i]);
    }

    fclose(file);
    savedPatientCount=numberOfPatients;
    printf("\nPatient records saved successfully.\n\n");
}
