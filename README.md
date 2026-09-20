# Smart Hospital and Resource Allocation System

A menu-driven Hospital Resource Allocation System that manages patient registration, hospital ward and bed allocation, waiting-time calculation, billing, priority-based patient display, performance reports, and file-based data storage.

## Features

### 1. Patient Registration
- Register up to 100 patients.
- Store patient name and age.
- Select a medical specialty:
  - General Practice (OPD)
  - Paediatrics
  - Cardiology
  - Neurology
- Select urgency level:
  - Level 1 - Normal
  - Level 2 - Urgent
  - Level 3 - Critical
- Choose whether the patient is admitted to a ward.
- Automatically allocate an available bed when admission is selected.
- Validate user input and reject invalid values.
  
### 2. Waiting-Time Calculation

The estimated waiting time is calculated using:

`Waiting Time = Current Queue Count × Consultation Time`

### 3. Billing System

The system calculates:

- Base consultation fee
- Emergency surcharge
- Ward cost
- Gross total
- Age-based discount
- Final payable amount

Emergency surcharge:
- Normal: 0%
- Urgent: 20% of the base consultation fee
- Critical: 50% of the base consultation fee

Patients younger than 5 years or older than 65 years receive a 15% discount.

### 4. Bed Allocation and Availability

- Four hospital wards are supported.
- Beds are represented using a two-dimensional array.
- The system automatically assigns the first available bed in the selected ward.
- Bed occupancy is displayed through the **Bed Availability** menu.
- Bed occupancy percentages can be generated in the performance reports.

### 5. Priority-Based Patient Display

Registered patients can be displayed in priority order.

Priority is based on urgency level:
1. Critical
2. Urgent
3. Normal
   
A Bubble Sort algorithm is used to arrange patient indexes according to urgency without changing the original patient data arrays.

### 6. Performance Reports

The system provides:

- Patient registration summary
- Patient counts by urgency level
- Total revenue/discounts given
- Ward bed occupancy report
- Highest-paying patient(s)

If multiple patients have exactly the same highest final payable amount, all matching patients are displayed.

### 7. File Handling

The system uses text files to preserve data between program sessions.

#### `src/beds_status.txt`
Stores the occupancy status of beds in each ward.

- `0` = Available
- `1` = Occupied

#### `src/patient_records.txt`
Stores saved patient billing and registration information in CSV-style format.

Patient records are appended to the file when data is saved.

### 8. Unsaved Data Protection

When exiting, the system checks whether there are newly registered patients that have not been saved.

The user can:
- Save the data and exit
- Exit without saving

  
## 📷 Program Preview

### 🏠 Main Menu & Navigation

<table> <tr> <td><img src="https://github.com/user-attachments/assets/df80b604-821d-45dc-a05c-da074502a229" width="100%"></td> <td><img src="https://github.com/user-attachments/assets/277dc326-2cfb-4091-b37e-3a48a9725c89" width="100%"></td> </tr> <tr> <td align="center"><b>Main Menu</b></td> <td align="center"><b>Reports Sub Menu</b></td> </tr> </table>

### 👤 Patient Registration

<table> <tr> <td><img src="https://github.com/user-attachments/assets/26e8bddb-cd25-40a5-87bf-f7593f87b1b6" width="100%"></td> <td><img src="https://github.com/user-attachments/assets/f536bdbe-024d-403a-bea5-05ea3a395d65" width="100%"></td> </tr> <tr> <td align="center"><b>Patient Registration Form</b></td> <td align="center"><b>Registration Form</b></td> </tr> </table>

### 💳 Patient Billing

<table> <tr> <td><img src="https://github.com/user-attachments/assets/93e0b744-c34c-409b-97e0-085521347ca4" width="100%"></td> <td><img src="https://github.com/user-attachments/assets/2598bbb0-2e02-4104-9b80-87b6130da832" width="100%"></td> </tr> <tr> <td align="center"><b>Patient Bill - Admission</b></td> <td align="center"><b>Patient Bill</b></td> </tr> </table>

### 🛏️ Bed Management

<table> <tr> <td><img src="https://github.com/user-attachments/assets/f7df7b0c-abad-4e65-8e2e-ae1c3e3e28ed" width="100%"></td> <td><img src="https://github.com/user-attachments/assets/12e7a6c0-391b-4b51-a1a0-61daae045296" width="100%"></td> </tr> <tr> <td align="center"><b>Bed Availability Report</b></td> <td align="center"><b>Bed Occupancy</b></td> </tr> </table>

### 📊 Patient Reports

<table> <tr> <td><img src="https://github.com/user-attachments/assets/09b9e323-173e-4f28-93f9-e7a65ea2c65f" width="100%"></td> <td><img src="https://github.com/user-attachments/assets/136a6655-5667-4561-8034-8b99aa024952" width="100%"></td> </tr> <tr> <td align="center"><b>Registration Summary</b></td> <td align="center"><b>Payment & Discount Summary</b></td> </tr> </table>

### 📋 Patient Priority & Reports

<table> <tr> <td><img src="https://github.com/user-attachments/assets/8e9b033a-cc57-40c4-8bd4-9f00d00aa7d0" width="100%"></td> <td><img src="https://github.com/user-attachments/assets/667d1325-29c9-4e23-949f-30171c1dc61c" width="100%"></td> </tr> <tr> <td align="center"><b>Patient Priority Order</b></td> <td align="center"><b>Highest-Paying Patient Report</b></td> </tr> </table>

## Project Structure

```text
Smart-Hospital-Resource-Allocation-System/
│
├── main.c
├── hospital.c
├── hospital.h
├── filehandling.c
├── filehandling.h
├── Smart-Hospital-Resource-Allocation-System.cbp
│
├── src/
│   ├── beds_status.txt
│   └── patient_records.txt
│
└── README.md
```

## Main Program Files

### `main.c`
Contains the main program loop and main menu.

### `hospital.c`
Contains the main hospital-management logics and calculations:
- Patient registration
- Bed allocation
- Billing calculations
- Patient display
- Priority sorting
- Performance reports
- Bed availability
- Exit handling

### `filehandling.c`
Contains functions for:
- Saving bed occupancy
- Loading bed occupancy
- Saving patient records

## Hospital Configuration

### Medical Specialties

| ID | Specialty | Base Fee (Rs.) | Consultation Time | Daily Capacity |
|---:|---|---:|---:|---:|
| 1 | General Practice (OPD) | 1,500 | 15 min | 30 |
| 2 | Paediatrics | 2,500 | 20 min | 20 |
| 3 | Cardiology | 4,500 | 30 min | 12 |
| 4 | Neurology | 5,000 | 30 min | 10 |

### Wards

| ID | Ward | Daily Bed Rate (Rs.) | Capacity |
|---:|---|---:|---:|
| 1 | General Ward | 3,000 | 20 |
| 2 | Paediatric Ward | 6,000 | 10 |
| 3 | Surgical Ward | 12,000 | 10 |
| 4 | ICU (Intensive Care Unit) | 25,000 | 5 |



## How to Run

### Using Code::Blocks

1. Open Code::Blocks.
2. Open `Smart-Hospital-Resource-Allocation-System.cbp`.
3. Make sure the text files are available in `src` directory:
   - `src/beds_status.txt`
   - `src/patient_records.txt`
4. Build the project.
5. Run the program.

## Saving Data

Selecting **Save Data** performs two operations:

1. Saves the current bed occupancy status to `src/beds_status.txt`.
2. Appends newly registered patient records to `src/patient_records.txt`.

The program tracks the number of patients already saved during the current session to avoid repeatedly writing the same in-memory patient records when the Save option is used multiple times.

## Authors
- [Omira Karannagoda](https://github.com/omiragk05)
