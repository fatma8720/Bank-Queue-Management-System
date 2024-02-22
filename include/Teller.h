#ifndef TELLER_H
#define TELLER_H

class Teller {
public:
    int id;
    bool available;
    int serviceTime;
    int customerId; // Track which customer the teller is serving

    Teller() {
        id = 0;
        available = true;
        serviceTime = 0;
        customerId = -1; // Initialize to -1 (no customer)
    }

    Teller(int id) {
        this->id = id;
        available = true;
        serviceTime = 0;
        customerId = -1; // Initialize to -1 (no customer)
    }
};

#endif // TELLER_H
