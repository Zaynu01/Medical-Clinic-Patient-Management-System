# Medical Clinic Patient Management System

## Description

This C program implements a patient management system for a medical clinic. It uses a priority queue (implemented as a max heap) to manage patients based on their visit priority. The system handles patient information, manages appointments, and processes patients in order of urgency.

## How It Works

The program uses a max heap data structure to manage patients. Each patient has a name, phone number, and priority number. The heap is implemented as an array of structures.

The program offers a menu-driven interface with the following options:
1. Start (load initial patient data)
2. Add a new patient
3. Print the list of patients
4. Serve a patient
5. Drop a visit
6. End doctor visits

## Features

1. **Load Initial Patient Data**: Reads patient information from a file, populating the heap.

2. **New Patient Registration**: Allows new patients to be added to the system with varying priority levels.

3. **Patient List Visualization**: Displays all patients in the system sorted by priority.

4. **Serve Highest Priority Patient**: Removes and returns the patient with the highest priority from the heap.

5. **Cancel Appointment**: Allows a patient to be removed from the system.

6. **End of Day Processing**: 
   - Serves all emergency cases
   - Resets priorities for remaining patients
   - Saves updated appointment list to a file

7. **Heap Management**:
   - Implements heapify operation to maintain heap property
   - Handles adding and removing elements from the heap

8. **Priority System**:
   - 0: A Friendly Visit
   - 5: A Medical Checkup
   - 10: An Appointment
   - 15: An Emergency Case

9. **Input Validation**: Ensures proper menu selection and data entry.

10. **File I/O**: Reads initial patient data from a file and writes updated appointments to a file.

## Technologies Used

1. **Programming Language**: C

2. **Data Structures**: 
   - Max Heap (implemented as an array)
   - Structures for patient information

3. **Algorithms**:
   - Heapify
   - Heap Sort
   - Linear Search

4. **File Handling**: Used for reading initial patient data and writing updated appointments

5. **Standard C Libraries**:
   - stdio.h: For input/output operations
   - string.h: For string manipulation functions

6. **Preprocessor Directives**: 
   - #define for constant definition (SIZE 10)

This program provides a comprehensive solution for managing patient visits in a medical clinic, prioritizing patients based on the urgency of their needs, and maintaining an efficient appointment system.