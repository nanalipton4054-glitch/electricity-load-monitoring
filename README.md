# Electrical Load Monitoring System

This is a C++ console application that allows users to manage household electrical appliances and monitor their energy consumption. The program calculates daily electricity usage and can also estimate the total electricity cost based on a user-defined tariff.

The system stores appliance data in a file so that it is available the next time the program runs.

---

## Features

- Add new appliances
- View all registered appliances
- Search appliance by name
- Edit appliance details
- Delete appliance
- Calculate total daily energy usage
- Generate monthly and yearly energy reports
- Calculate electricity cost (billing summary)
- Save data to file
- Automatically load saved data at startup
- Input validation to prevent invalid entries

---

## How Energy Is Calculated

Energy consumption is calculated using the formula:

Energy (kWh) = (Power in Watts × Hours per Day) ÷ 1000

The total daily energy is the sum of all registered appliances.

Monthly and yearly estimates are based on:
- Monthly = Daily × 30
- Yearly = Daily × 365

---

## Files Used

### appliances.txt
Stores appliance data in this format:

name,power,hours

Example:

### billing_summary.txt
Stores the latest calculated billing summary.

---

## Program Menu

The system provides a simple menu:

1. Register appliance  
2. View all appliances  
3. Search appliance  
4. Edit appliance  
5. Delete appliance  
6. Energy summary  
7. Billing summary  
0. Exit  

When exiting, data is saved automatically.

---

## Requirements

- C++ compiler (g++ recommended)
- Works in any standard C++17 environment

---

## How to Compile and Run

Using g++:

Or compile and run using any C++ IDE.

---

## Purpose of the Project

This project demonstrates:

- Object-Oriented Programming
- Use of classes and vectors
- File handling (ifstream / ofstream)
- Input validation
- Menu-driven console applications

It was developed step-by-step, gradually adding features such as file storage, billing calculations, editing, and reporting.

---

## Notes

- Data is automatically loaded when the program starts.
- Data is saved when the program exits.
- The program prevents invalid numeric input to avoid crashes.

---
## Author

William Asamoah  
C++ Electrical Load Monitoring System Project  
