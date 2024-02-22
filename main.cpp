#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#include "Customer.h"
#include "Teller.h"
#include <Windows.h>

using namespace std;

// Comparison function for priority_queue to order customers based on arrival time and priority is the arrival time the same
struct CompareCustomer {
    bool operator()(const Customer& c1, const Customer& c2) {
        if (c1.arrivalTime == c2.arrivalTime) {
            return c1.isVIP < c2.isVIP;
        }
        return c1.arrivalTime > c2.arrivalTime;
    }
};

//make output colorful
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
// Struct to store customer data
struct CustomerData {
    int id;
    int arrivalTime;
    int serviceTime;
    int waitingTime;
    int tellerId;
    int leavingTime;
};

// Function to read customer data from the input file
void readCustomerData(const string& filename, int& numTellers, priority_queue<Customer, deque<Customer>, CompareCustomer>& customerQueue, Teller tellers[]) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Failed to open input file!" << endl;
        return;
    }

    inputFile >> numTellers;
    for (int i = 0; i < numTellers; ++i) {
        tellers[i].id = i + 1;
    }
    int customerId, arrivalTime, serviceTime;
    bool isVIP;
    while (inputFile >> customerId >> arrivalTime >> serviceTime >> isVIP) {
        Customer newCustomer(customerId, arrivalTime, serviceTime, isVIP);
        customerQueue.push(newCustomer);
    }
    inputFile.close();
}

// Function to print customer data as a resume of whole customers served
void printCustomerResume(const queue<CustomerData>& customerData) {
    setColor(14);
    cout <<"\n\n\n\t\t\t\t\tBank Queue Management System \n\n\n";
    setColor(9);
    cout << "Customer\tArrival Time\tService Time\tWaiting Time\tServiced by Teller\tLeaving Time" << endl;
    setColor(15);
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    queue<CustomerData> temp = customerData;
    while (!temp.empty()) {
        CustomerData data = temp.front();
        setColor(12);
        cout << data.id << "\t\t" << data.arrivalTime << "\t\t" << data.serviceTime << "\t\t"
             << data.waitingTime << "\t\t\t"<< data.tellerId << "\t\t" << data.leavingTime << endl;
        setColor(15);
        cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
        temp.pop();
    }
}

// Function to simulate the bank operation
void simulateBankOperation(int numTellers, priority_queue<Customer, deque<Customer>, CompareCustomer>& customerQueue, Teller tellers[]) {
    int currentTime = 0;
    bool allCustomersServed = false;
    int prevTime = -1; // Previous time a customer
    int nextTime = -1; // Next time a customer will leave

    // Variables to calculate statistics
    int totalServiceTime = 0;
    vector<int> utilizationTimes(numTellers, 0);

    // Queue to store customer data
    queue<CustomerData> customerData;

    // Simulation loop
    while (!allCustomersServed || any_of(tellers, tellers + numTellers, [](const Teller& t) { return !t.available; })) {

        // Teller service simulation
        allCustomersServed = customerQueue.empty(); //as all customers are served until one or more become not
        for (int i = 0; i < numTellers; ++i) {
            if (tellers[i].available && !customerQueue.empty()) {
                Customer currentCustomer = customerQueue.top();
                if (currentCustomer.arrivalTime <= currentTime) {
                    // Store customer data
                    CustomerData currentCustomerData;
                    currentCustomerData.id = currentCustomer.id;
                    currentCustomerData.arrivalTime = currentCustomer.arrivalTime;
                    currentCustomerData.serviceTime = currentCustomer.serviceTime;
                    currentCustomerData.waitingTime = currentTime - currentCustomer.arrivalTime;
                    currentCustomerData.tellerId = tellers[i].id;
                    currentCustomerData.leavingTime = currentTime + currentCustomer.serviceTime;
                    customerData.push(currentCustomerData);

                    // Update total service time
                    totalServiceTime += currentCustomer.serviceTime;

                    // Update utilization time for the current teller
                    utilizationTimes[i] += currentCustomer.serviceTime;

                    // Update teller state
                    customerQueue.pop();
                    tellers[i].available = false;
                    tellers[i].serviceTime = currentCustomer.serviceTime;
                    tellers[i].customerId = currentCustomer.id; // Update customerId

                    prevTime = currentTime; // Update previous time
                    nextTime = currentTime + 1; // Update next time
                }
            }
            if (!tellers[i].available) {
                --tellers[i].serviceTime;
                if (tellers[i].serviceTime == 0) {
                    tellers[i].available = true;
                    tellers[i].customerId = -1; // Reset customerId because teller becomes free not serving any customer
                } else {
                    allCustomersServed = false; // If any teller is still serving, not all customers are served
                }
            }
        }
        ++currentTime;
    }

    // Print customer data as a resume
    printCustomerResume(customerData);

    // Calculate average service time
    double averageServiceTime = static_cast<double>(totalServiceTime) / customerData.size();
     setColor(14);
    cout << "\n\n\t\t\t\tAverage Service Time of the Bank: " <<averageServiceTime << "\n\n\n";

    // Calculate and print utilization rate of each teller
     setColor(9);
    cout << "Utilization Rate of Each Teller: \n\n" ;
    for (int i = 0; i < numTellers; ++i) {
        double utilizationRate = static_cast<double>(utilizationTimes[i]) / currentTime;
        setColor(6);
        cout << "Teller " << i + 1 << ": " << utilizationRate * 100 << "%" << endl;
    }
    setColor(15);
}

int main() {
    int numTellers;
    priority_queue<Customer, deque<Customer>, CompareCustomer> customerQueue;
    Teller tellers[100]; //Max tellers

    readCustomerData("input.txt", numTellers, customerQueue, tellers);
    simulateBankOperation(numTellers, customerQueue, tellers);

    return 0;
}
