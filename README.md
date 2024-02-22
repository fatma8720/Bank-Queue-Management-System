
Bank Queue Management System

This project implements a simulation of a bank queue management system in C++. It simulates the operation of a bank with multiple tellers serving customers who arrive at different times and have varying service times. The system tracks customer data, such as arrival time, service time, waiting time, and the teller serving them.

Features
Customer Queue: Customers are prioritized based on arrival time, with VIP customers served first in case of a tie.
Tellers: Multiple tellers are available to serve customers concurrently. Each teller can serve only one customer at a time.
Statistics: The system calculates and displays statistics such as average service time and teller utilization rates.


File Structure
main.cpp: Contains the main program logic, including file reading, simulation, and output.
Customer.h: Defines the Customer class, representing a customer with arrival time, service time, and VIP status.
Teller.h: Defines the Teller class, representing a teller with availability and service time tracking.
input.txt: Sample input file containing customer data.

Usage
Compilation: Compile the program using a C++ compiler.
Input: Ensure that the input file input.txt is present in the same directory as the executable. Modify this file to change the customer data.

Output
The program outputs a summary of customer data, including arrival time, service time, waiting time, teller ID, and leaving time. It also provides statistics such as average service time and teller utilization rates.

Output Sample
![image](https://github.com/fatma8720/Bank-Queue-Management-System/assets/88749492/a4113eeb-6dfa-4548-aeaa-f86933b02455)


Requirements
C++ compiler
