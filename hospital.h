
#ifndef HOSPITAL_H
#define HOSPITAL_H

#define MAX_PATIENTS 100
#define NUM_OF_SPECIALTIES 4
#define NUM_OF_WARDS 4

/* Doctor Specialties Data */
extern const int specialtyID[NUM_OF_SPECIALTIES];
extern const char specialtyName[NUM_OF_SPECIALTIES][30];
extern const double baseFee[NUM_OF_SPECIALTIES];
extern const int consultationTime[NUM_OF_SPECIALTIES];
extern const int dailyPatientCap[NUM_OF_SPECIALTIES];

/* Hospital Wards Data */
extern const int wardID[NUM_OF_WARDS];
extern const char wardName[NUM_OF_WARDS][30];
extern const double dailyBedRate[NUM_OF_WARDS];
extern const int bedCapacity[NUM_OF_WARDS];

extern int bedAvailabilityStatus[NUM_OF_WARDS][20];

/* Patient Data */
extern char patientName[MAX_PATIENTS][50];
extern int patientAge[MAX_PATIENTS];
extern int patientSpecialtyID[MAX_PATIENTS];
extern int patientWardID[MAX_PATIENTS];
extern int patientBedNumber[MAX_PATIENTS];
extern int patientUrgencyLevel[MAX_PATIENTS];
extern int patientDaysAdmitted[MAX_PATIENTS];

extern double patientWaitingTime[MAX_PATIENTS];
extern double patientBaseConsultationFee[MAX_PATIENTS];
extern double patientEmergencySurcharge[MAX_PATIENTS];
extern double patientWardCost[MAX_PATIENTS];
extern double patientGrossTotal[MAX_PATIENTS];
extern double patientDiscount[MAX_PATIENTS];
extern double patientFinalPayable[MAX_PATIENTS];

extern int dailyPatientRegisteredCount[NUM_OF_SPECIALTIES];
extern int numOfPatientsInQueue[NUM_OF_SPECIALTIES];
extern int numberOfPatients;

extern int patientDisplayOrder[MAX_PATIENTS];

/* Functions */
int chooseBedFromWard(int wardIDChoice);

double calculateWaitingTime(int specialtyIDChoice);
double calculateBaseConsultationFee(int specialtyIDChoice);
double calculateEmergencySurcharge(int urgencyLevel, double baseConsultationFee);
double calculateWardCost(int wardIDChoice, int daysAdmitted);
double calculateGrossTotal(double baseConsultationFee,double emergencySurcharge,double wardCost);
double calculateDiscount(int age, double grossTotal);
double calculateFinalPayable(double grossTotal, double discount);

void displayMainMenu();
void registerPatient();
void displayPatientBill(int patientIndex);

void sortPatientsIndexesByPriority();
void displayRegisteredPatientsByPriority();
void displayPatientDetails(int patientIndex, int priorityNumber);

void displayPerformanceReportsSubMenu();
void performanceReportsSubMenu();

int findTheIndexOfHighestPayingPatient();
void displayHighestPayingPatient();

int getPatientCountPerUrgencyLevel(int urgency);
void displayPatientRegistrationSummary();

void displayTotalRevenueAndDiscountAmounts();

double calculateBedOccupancyPercentage(int wardIDChoice);
void displayWardBedOccupancyReport();

void displayBedAvailability();

void clearScreen();

#endif
