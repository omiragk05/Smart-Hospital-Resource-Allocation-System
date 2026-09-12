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
    printf("===============================\n");
    printf("      PATIENT REGISTRATION\n");
    printf("===============================\n");

    printf("Enter patient name: ");
    scanf(" %[^\n]", patientName[numberOfPatients]);

    printf("Enter patient age: ");
    scanf("%d", &patientAge[numberOfPatients]);

    printf("Enter urgency level (1 = Normal, 2 = Urgent, 3 = Critical): ");
    scanf("%d", &patientUrgencyLevel[numberOfPatients]);

    printf("Enter specialty ID (1-4): ");
    scanf("%d", &patientSpecialtyID[numberOfPatients]);

    printf("Is admitted to ward? (1 = Yes, 0 = No): ");
    scanf("%d", &admissionChoice);

    if(admissionChoice == 1)
    {
        printf("Enter ward ID (1-4): ");
        scanf("%d", &patientWardID[numberOfPatients]);

        printf("Enter days admitted: ");
        scanf("%d", &patientDaysAdmitted[numberOfPatients]);
    }
    else
    {
        patientWardID[numberOfPatients] = 0;
        patientBedNumber[numberOfPatients] = 0;
        patientDaysAdmitted[numberOfPatients] = 0;
    }

    numberOfPatients++;

    printf("\nPatient registation successful.\n");
}
