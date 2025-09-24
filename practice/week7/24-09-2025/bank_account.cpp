

class BankAccount {
    int balance;
public:
    
    BankAccount(int initial = 0) : balance(initial) {}
    
    void deposit(int amount) { 
        balance += amount; 
    }
    
    bool withdraw(int amount) {
        if (amount > balance) return false;
        balance -= amount;
        return true;
    }
    
    int getBalance() const { 
        return balance; 
    }
};
