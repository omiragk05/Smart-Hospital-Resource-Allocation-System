#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define NUM_OF_SPECIALTIES 4
#define NUM_OF_WARDS 4


//Doctor Specialties Data
const int specialtyID[NUM_OF_SPECIALTIES] = {1,2,3,4};
const char specialtyName[NUM_OF_SPECIALTIES][30] = {"General Practice (OPD)","Paediatrics","Cardiology","Neurology"};
const double baseFee[NUM_OF_SPECIALTIES] = {1500.00,2500.00,4500.00,5000.00};
const int consultationTime[NUM_OF_SPECIALTIES] = {15,20,30,30};
const int dailyPatientCap[NUM_OF_SPECIALTIES] = {30,20,12,10};

//Hospital Wards Data
const int wardID[NUM_OF_WARDS] = {1,2,3,4};
const char wardName[NUM_OF_WARDS][30] = {"General Ward","Paediatric Ward","Surgical Ward","ICU (Intensive Care Unit)"};
const double dailyBedRate[NUM_OF_WARDS] = {3000.00,6000.00,12000.00,25000.00};
const int bedCapacity[NUM_OF_WARDS] = {20,10,10,5};

int bedAvailabilityStatus[NUM_OF_WARDS][20] = {0};


//data arrays

char patientName[MAX_PATIENTS][50];
int patientAge[MAX_PATIENTS] = {0};
int patientSpecialtyID[MAX_PATIENTS] = {0};
int patientWardID[MAX_PATIENTS] = {0};
int patientBedNumber[MAX_PATIENTS] = {0};
int patientUrgencyLevel[MAX_PATIENTS] = {0};
int patientDaysAdmitted[MAX_PATIENTS] = {0};

double patientWaitingTime[MAX_PATIENTS] = {0.0};
double patientBaseConsultationFee[MAX_PATIENTS] = {0.0};
double patientEmergencySurcharge[MAX_PATIENTS] = {0.0};
double patientWardCost[MAX_PATIENTS] = {0.0};
double patientGrossTotal[MAX_PATIENTS] = {0.0};
double patientDiscount[MAX_PATIENTS] = {0.0};
double patientFinalPayable[MAX_PATIENTS] = {0.0};

int dailyPatientRegisteredCount[NUM_OF_SPECIALTIES] = {0};

int numOfPatientsInQueue[NUM_OF_SPECIALTIES] = {0};
int numberOfPatients = 0;

int patientDisplayOrder[MAX_PATIENTS];

//function prototype

int chooseBedFromWard(int wardIDChoice);

double calculateWaitingTime(int patientIndex);
double calculateBaseConsultationFee(int specialtyIDChoice);
double calculateEmergencySurcharge(int urgencyLevel,double baseConsultationFee);
double calculateWardCost(int wardIDChoice,int daysAdmitted);
double calculateGrossTotal(double baseConsultationFee, double emergencySurcharge,double wardCost);
double calculateDiscount(int age,double grossTotal);
double calculateFinalPayable(double grossTotal,double discount);

void displayPatientBill(int patientIndex);
void sortPatientsIndexesByPriority();
void displayRegisteredPatientsByPriority();
void refreshWaitingTimesOfOtherPatients(int specialtyIDChoice);


void displayMainMenu()
{
    printf("\n====================================================\n");
    printf("     SMART HOSPITAL AND RESOURCE ALLOCATION SYSTEM\n");
    printf("====================================================\n");
    printf("1. Register Patient\n");
    printf("2. Display Registered Patients\n");
    printf("3. Generate Reports\n");
    printf("4. Save Data\n");
    printf("5. Exit\n");
    printf("====================================================\n");
}

void registerPatient()
{
    int admissionChoice;
    int specialtyIDChoice;
    int wardIDChoice;
    int urgencyLevel;
    printf("===============================\n");
    printf("      PATIENT REGISTRATION\n");
    printf("===============================\n");

    printf("Enter patient name: ");
    scanf(" %[^\n]", patientName[numberOfPatients]);

    printf("Enter patient age: ");
    scanf("%d", &patientAge[numberOfPatients]);

    printf("Enter specialty ID (1-4): ");
    scanf("%d", &specialtyIDChoice);

    if(dailyPatientRegisteredCount[specialtyIDChoice-1]>=dailyPatientCap[specialtyIDChoice-1])
    {
        printf("Sorry. Daily Patient Capacity for %s is already Reached.\n",specialtyName[specialtyIDChoice-1]);
        printf("Enter any key to go to main menu..");
        getchar();
        getchar();
        return;
    }

    printf("Enter urgency level (1 = Normal, 2 = Urgent, 3 = Critical): ");
    scanf("%d", &urgencyLevel);



    printf("Admitted to ward? (1 = Yes, 0 = No): ");
    scanf("%d", &admissionChoice);

    if(admissionChoice == 1)
    {
        printf("Enter ward ID (1-4): ");
        scanf("%d", &wardIDChoice);
        int bed = chooseBedFromWard(wardIDChoice);
        if(bed == -1)
        {
            printf("Sorry. No beds available in %s.\n",wardName[wardIDChoice-1]);
            printf("Enter any key to go to main menu..");
            getchar();
            getchar();
            getchar();
            return;
        }else
        {
            patientWardID[numberOfPatients] = wardIDChoice;
            bedAvailabilityStatus[wardIDChoice-1][bed] =1;
            patientBedNumber[numberOfPatients] = bed;
        }

        printf("Enter days admitted: ");
        scanf("%d", &patientDaysAdmitted[numberOfPatients]);
    }
    else
    {
        patientWardID[numberOfPatients] = 0;
        patientBedNumber[numberOfPatients] = 0;
        patientDaysAdmitted[numberOfPatients] = 0;
    }

    patientSpecialtyID[numberOfPatients] = specialtyIDChoice-1;
    patientUrgencyLevel[numberOfPatients] = urgencyLevel;
    patientWaitingTime[numberOfPatients] = calculateWaitingTime(numberOfPatients);
    patientBaseConsultationFee[numberOfPatients] =calculateBaseConsultationFee(specialtyIDChoice);

    patientEmergencySurcharge[numberOfPatients] =calculateEmergencySurcharge(patientUrgencyLevel[numberOfPatients],
                                                patientBaseConsultationFee[numberOfPatients]);

    patientWardCost[numberOfPatients] =calculateWardCost(patientWardID[numberOfPatients],
                                        patientDaysAdmitted[numberOfPatients]);

    patientGrossTotal[numberOfPatients] =calculateGrossTotal(patientBaseConsultationFee[numberOfPatients],
                                    patientEmergencySurcharge[numberOfPatients],patientWardCost[numberOfPatients]);

    patientDiscount[numberOfPatients] =calculateDiscount(patientAge[numberOfPatients],
                                                         patientGrossTotal[numberOfPatients]);

    patientFinalPayable[numberOfPatients] =calculateFinalPayable(patientGrossTotal[numberOfPatients],
                                                    patientDiscount[numberOfPatients]);

    printf("\nPatient registation successful.\n");
    displayPatientBill(numberOfPatients);
    numOfPatientsInQueue[specialtyIDChoice - 1]++;
    dailyPatientRegisteredCount[specialtyIDChoice - 1]++;
    numberOfPatients++;

    refreshWaitingTimesOfOtherPatients(specialtyIDChoice);
}


int chooseBedFromWard(int wardIDChoice)
{
    for(int i =0 ;i<bedCapacity[wardIDChoice-1];i++)
    {
        if(bedAvailabilityStatus[wardIDChoice-1][i]==0)
        {
            return i;
        }
    }

    return -1;

}


double calculateBaseConsultationFee(int specialtyIDChoice)
{
    return baseFee[specialtyIDChoice-1];
}


double calculateWaitingTime(int patientNumber)
{
    int patientsAheadCount = 0;

    for(int i= 0;i<numberOfPatients;i++)
    {
        if(i==patientNumber)
        {
            continue;
        }
        if (patientSpecialtyID[i] == patientSpecialtyID[patientNumber])
        {
            if (patientUrgencyLevel[i]>patientUrgencyLevel[patientNumber])
            {
                patientsAheadCount++;
            }
            else if(patientUrgencyLevel[i]==patientUrgencyLevel[patientNumber]&& i<patientNumber)
            {
                patientsAheadCount++;
            }
        }
    }
    return patientsAheadCount * consultationTime[patientSpecialtyID[patientNumber]];
}


double calculateEmergencySurcharge(int urgencyLevel, double baseConsultationFee)
{
    if(urgencyLevel == 1)
    {
        return 0.00;
    }
    else if(urgencyLevel == 2)
    {
        return baseConsultationFee * 0.20;
    }
    else
    {
        return baseConsultationFee * 0.50;
    }
}


double calculateWardCost(int wardIDChoice, int daysAdmitted)
{
    if(wardIDChoice == 0)
    {
        return 0.00;
    }

    return dailyBedRate[wardIDChoice - 1] * daysAdmitted;
}


double calculateGrossTotal(double baseConsultationFee,double emergencySurcharge,double wardCost)
{
    return baseConsultationFee + emergencySurcharge + wardCost;
}


double calculateDiscount(int age, double grossTotal)
{
    if(age < 5 || age > 65)
    {
        return grossTotal * 0.15;
    }
    return 0.00;
}


double calculateFinalPayable(double grossTotal, double discount)
{
    return grossTotal - discount;
}

void displayPatientBill(int patientIndex)
{
    printf("\n===============================================\n");
    printf("Patient ID          : PAT-%04d\n", patientIndex+1);
    printf("Patient Name        : %s\n", patientName[patientIndex]);
    printf("Age                 : %d\n", patientAge[patientIndex]);
    printf("Specialty           : %s\n", specialtyName[patientSpecialtyID[patientIndex]]);
    printf("Urgency Level       : %d\n", patientUrgencyLevel[patientIndex]);
    printf("Waiting Time        : %.0lf minutes\n",patientWaitingTime[patientIndex]);

    if(patientWardID[patientIndex] == 0)
    {
        printf("Assigned Ward          : Not Admitted\n");
    }
    else
    {
        printf("Ward                : %s\n",wardName[patientWardID[patientIndex] - 1]);
        printf("Bed Number          : %d\n",patientBedNumber[patientIndex] + 1);
        printf("Days Admitted       : %d\n",patientDaysAdmitted[patientIndex]);
    }
    printf("-----------------------------------------------\n");
    printf("Base Consultation   : Rs. %.2f\n",patientBaseConsultationFee[patientIndex]);
    printf("Emergency Surcharge : Rs. %.2f\n",patientEmergencySurcharge[patientIndex]);
    printf("Ward Cost           : Rs. %.2f\n",patientWardCost[patientIndex]);
    printf("Gross Total         : Rs. %.2f\n",patientGrossTotal[patientIndex]);
    printf("Discount            : Rs. %.2f\n",patientDiscount[patientIndex]);
    printf("-----------------------------------------------\n");
    printf("Final Payable       : Rs. %.2f\n",patientFinalPayable[patientIndex]);
    printf("===============================================\n");
}

void sortPatientsIndexesByPriority()
{
    for(int i= 0; i<numberOfPatients;i++)
    {
        patientDisplayOrder[i] = i;
    }
    for(int i=0;i<numberOfPatients-1;i++)
    {
         for(int j=0;j<numberOfPatients-i-1;j++)
         {
            if(patientUrgencyLevel[patientDisplayOrder[j]] <
               patientUrgencyLevel[patientDisplayOrder[j+1]])
            {
                int temp = patientDisplayOrder[j];
                patientDisplayOrder[j] = patientDisplayOrder[j+1];
                patientDisplayOrder[j+1] = temp;
            }
         }
    }
}

void displayRegisteredPatientsByPriority()
{
    sortPatientsIndexesByPriority();
    printf("\n====================================================\n");
    printf("       REGISTERED PATIENTS(Priority Order)\n");
    printf("====================================================\n");

    for(int i=0;i<numberOfPatients; i++)
    {
        displayPatientBill(patientDisplayOrder[i]);
    }
    printf("\n====================================================\n");
}


void refreshWaitingTimesOfOtherPatients(int specialtyIDChoice)
{
    for(int i=0;i<numberOfPatients;i++)
    {
        if(patientSpecialtyID[i]==specialtyIDChoice-1)
        {
            patientWaitingTime[i]=calculateWaitingTime(i);
        }
    }

}


