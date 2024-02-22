#ifndef CUSTOMER_H
#define CUSTOMER_H


class Customer
{
public :
    int id;
    int arrivalTime;
    int serviceTime;
    int waitingTime;
    int responseTime;
    int leavingTime;
    bool isVIP;
    int tellerId;

    Customer(int id, int arrivalTime, int serviceTime, bool isVIP)
    {
        this->id = id;
        this->arrivalTime = arrivalTime;
        this->serviceTime = serviceTime;
        waitingTime = 0;
        responseTime = 0;
        leavingTime = 0;
        this->isVIP = isVIP;
    }

protected:

private:
};

#endif // CUSTOMER_H
