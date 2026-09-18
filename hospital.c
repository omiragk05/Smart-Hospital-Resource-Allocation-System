#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void displayPerformanceReportsSubMenu();
void clearScreen();
int findTheIndexOfHighestPayingPatient();
void displayHighestPayingPatient();
void displayPatientRegistrationSummary();
int getPatientCountPerUrgencyLevel(int urgency);
void displayTotalRevenueAndDiscountAmounts();
double calculateBedOccupancyPercentage(int wardIDChoice);
void displayWardBedOccupancyReport();


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
    int age;
    int days;
    printf("===============================\n");
    printf("      PATIENT REGISTRATION\n");
    printf("===============================\n");

    if(numberOfPatients>= MAX_PATIENTS)
    {
        printf("Maximum patient capacity reached.\n");
        return;
    }
    printf("Enter patient name: ");
    scanf(" %49[^\n]", patientName[numberOfPatients]);

    do
    {
        printf("Enter patient age: ");
        scanf("%d", &age);
        if(age<0)
        {
            printf("Invalid age.\n");
        }
    }while(age<0);

    patientAge[numberOfPatients]=age;
    printf("\n");

    for(int i=0;i<NUM_OF_SPECIALTIES;i++)
    {
        printf("%-25s : %d\n", specialtyName[i],specialtyID[i]);
    }
    do
    {
        printf("\nEnter specialty ID (1-4): ");
        scanf("%d", &specialtyIDChoice);

        if(specialtyIDChoice<1||specialtyIDChoice>4)
        {
            printf("Invalid Specialty Input...\n");
        }
    }while(specialtyIDChoice<1||specialtyIDChoice>4);

    if(dailyPatientRegisteredCount[specialtyIDChoice-1]>=dailyPatientCap[specialtyIDChoice-1])
    {
        printf("Sorry. Daily Patient Capacity for %s is already Reached.\n",specialtyName[specialtyIDChoice-1]);
        printf("Enter any key to go to main menu..");
        getchar();
        getchar();
        return;
    }

    printf("\n1 = Normal\n2 = Urgent\n3 = Critical\n\n");

    do
    {
        printf("Enter urgency level : ");
        scanf("%d", &urgencyLevel);

        if(urgencyLevel<1||urgencyLevel>3)
        {
            printf("invalid Urgency Level...\n\n");
        }
    }while(urgencyLevel<1||urgencyLevel>3);

    do
    {
        printf("\nAdmitted to ward? (1 = Yes, 0 = No): ");
        scanf("%d", &admissionChoice);

        if(admissionChoice!= 0 && admissionChoice!= 1)
        {
            printf("Invalid input... Please enter 1 or 0.\n");
        }
    }while(admissionChoice != 0 && admissionChoice != 1);

    printf("\n");
    if(admissionChoice == 1)
    {
        do
        {
            printf("Enter ward ID (1-4): ");
            scanf("%d", &wardIDChoice);

            if(wardIDChoice< 1||wardIDChoice> 4)
            {
                printf("Invalid ward ID...\n");
            }

        }while(wardIDChoice< 1||wardIDChoice> 4);

        int bed = chooseBedFromWard(wardIDChoice);
        if(bed == -1)
        {
            printf("\nSorry.Currently No beds available in %s.\n",wardName[wardIDChoice-1]);
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

        do
        {
            printf("\nEnter days admitted: ");
            scanf("%d", &days);
            if(days<= 0)
            {
                printf("Invalid number of days.\n");
            }

        }while(days<= 0);
        patientDaysAdmitted[numberOfPatients]=days;
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

    clearScreen();
    printf("\nPatient registation successful.\n");
    displayPatientBill(numberOfPatients);
    numOfPatientsInQueue[specialtyIDChoice - 1]++;
    dailyPatientRegisteredCount[specialtyIDChoice - 1]++;
    numberOfPatients++;

    refreshWaitingTimesOfOtherPatients(specialtyIDChoice);
    printf("Enter any key to go back..");
    getchar();
    getchar();
    clearScreen();
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
    printf("Age                 : %d Years %s", patientAge[patientIndex],
           patientAge[patientIndex]<5||patientAge[patientIndex]>65?"(15% Subsidy Eligible)\n":"\n");
    printf("Specialty           : %s\n", specialtyName[patientSpecialtyID[patientIndex]]);
    printf("Urgency Level       : %d (%s)\n", patientUrgencyLevel[patientIndex],
           patientUrgencyLevel[patientIndex]==1?"Normal":patientUrgencyLevel[patientIndex]==2?"Urgent":"Critical");
    printf("Waiting Time        : %.2lf minutes\n",patientWaitingTime[patientIndex]);

    if(patientWardID[patientIndex] == 0)
    {
        printf("Assigned Ward          : Not Admitted\n");
    }
    else
    {
        printf("Ward                : %s\n",wardName[patientWardID[patientIndex] - 1]);
        printf("Bed Number          : Bed#%d\n",patientBedNumber[patientIndex] + 1);
        printf("Days Admitted       : %d Days\n",patientDaysAdmitted[patientIndex]);
    }
    printf("-----------------------------------------------\n");
    printf("Base Consultation   : Rs. %10.2lf\n",patientBaseConsultationFee[patientIndex]);
    printf("Emergency Surcharge : Rs. %10.2lf\n",patientEmergencySurcharge[patientIndex]);
    printf("Ward Cost           : Rs. %10.2lf\n",patientWardCost[patientIndex]);
    printf("Gross Total         : Rs. %10.2lf\n",patientGrossTotal[patientIndex]);
    printf("Discount            : Rs. -%9.2lf %s",patientDiscount[patientIndex] ,
           patientDiscount[patientIndex]>0.0?"(15%%)\n":"\n");
    printf("-----------------------------------------------\n");
    printf("Final Payable       : Rs. %10.2lf\n",patientFinalPayable[patientIndex]);
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
    if(numberOfPatients<1)
    {
        printf("\nNo Patients are available to display. \n");
    }
    else
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

    printf("\nEnter any key to go back..");
    getchar();
    getchar();
    clearScreen();
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

void displayPerformanceReportsSubMenu()
{
    printf("====================================================\n");
    printf("      PERFORMANCE REPORTS\n");
    printf("====================================================\n");
    printf("1. Patient Registration Summary\n");
    printf("2. Revenue and Discount Summary\n");
    printf("3. Ward Bed Occupancy Report\n");
    printf("4. Highest-Paying Patient\n");
    printf("5. Back to Main Menu\n");
    printf("====================================================\n");
}
void performanceReportsSubMenu()
{
    int option;
    do
    {
        displayPerformanceReportsSubMenu();
        printf("Input an option : ");
        scanf("%d",&option);
        switch(option)
        {
            case 1:
                clearScreen();
                displayPatientRegistrationSummary();
                break;
            case 2:
                clearScreen();
                displayTotalRevenueAndDiscountAmounts();
                break;
            case 3:
                clearScreen();
                displayWardBedOccupancyReport();
                break;
            case 4:
                clearScreen();
                displayHighestPayingPatient();
                break;
            case 5:
                clearScreen();
                break;
            default:
                clearScreen();
                printf("Wrong option. Enter again. \n\n");

        }
    }while(option!=5);
}

int findTheIndexOfHighestPayingPatient()
{
    int index=0;
    for(int i=1;i<numberOfPatients;i++)
    {
        if(patientFinalPayable[index]<patientFinalPayable[i])
        {
            index=i;
        }
    }
    return index;
}

void displayHighestPayingPatient()
{
    if(numberOfPatients==0)
    {
        printf("\nCurrently no patients are registered. \n");
    }
    else
    {
        int index=findTheIndexOfHighestPayingPatient();
        printf("\n====================================================\n");
        printf("      Highest Paying Patient\n");
        printf("====================================================\n");
        printf("Name : %s\n",patientName[index]);
        printf("Age  : %d\n",patientAge[index]);
        printf("Bill Amount : %.2lf\n",patientFinalPayable[index]);
        printf("====================================================\n");
    }

    printf("\nEnter any key to go back..");
    getchar();
    getchar();
    clearScreen();
}

int getPatientCountPerUrgencyLevel(int urgency)
{
    int count=0;
    for(int i=0;i<numberOfPatients;i++)
    {
        if(patientUrgencyLevel[i]==urgency)
        {
            count++;
        }

    }
    return count;
}

void displayPatientRegistrationSummary()
{
    printf("\n====================================================\n");
    printf("      Patient Registration Summary\n");
    printf("====================================================\n");
    printf("Level 1 Normal Patient Count   : %d\n",getPatientCountPerUrgencyLevel(1));
    printf("Level 2 Urgent Patient Count   : %d\n",getPatientCountPerUrgencyLevel(2));
    printf("Level 3 Critical Patient Count : %d\n",getPatientCountPerUrgencyLevel(3));
    printf("----------------------------------------------------\n");
    printf("Total Registerd Patient Count  : %d\n",numberOfPatients);
    printf("====================================================\n");
    printf("\nEnter any key to go back..");
    getchar();
    getchar();
    clearScreen();
}

void displayTotalRevenueAndDiscountAmounts()
{
    double totalRevenue = 0.0;
    double totalDiscount = 0.0;

    for(int i =0;i<numberOfPatients;i++)
    {
        totalDiscount+=patientDiscount[i];
        totalRevenue+=patientFinalPayable[i];
    }

    printf("\n====================================================\n");
    printf("      Revenue and Discount Summary\n");
    printf("====================================================\n");
    printf("Total Revenue         : %.2lf\n",totalRevenue);
    printf("Total Discounts Given : %.2lf\n",totalDiscount);
    printf("====================================================\n");
    printf("\nEnter any key to go back..");
    getchar();
    getchar();
    clearScreen();
}

double calculateBedOccupancyPercentage(int wardIDChoice)
{
    double percentage=0.0;
    int OccupiedBedCount = 0;

    for(int i=0;i<bedCapacity[wardIDChoice-1];i++)
    {
        if(bedAvailabilityStatus[wardIDChoice-1][i]==1)
        {
            OccupiedBedCount++;
        }
    }
    percentage = OccupiedBedCount*1.0 / bedCapacity[wardIDChoice-1] *100;
    return percentage;
}
void displayWardBedOccupancyReport()
{
    printf("\n====================================================\n");
    printf("      Ward Bed Occupancy Report\n");
    printf("====================================================\n");
    for(int i=0;i<NUM_OF_WARDS;i++)
    {
        printf("%.2lf %% Beds Occupied in %s\n",calculateBedOccupancyPercentage(wardID[i]),wardName[i]);
    }
    printf("====================================================\n");
    printf("\nEnter any key to go back..");
    getchar();
    getchar();
    clearScreen();
}

void clearScreen()
{
    system("cls");
}
