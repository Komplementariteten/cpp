#include <iostream>
#include <string>

class BankAccount
{
private:
    // TODO: declare member variables
    float balance_{0};
    std::string owner_;
    std::string account_number_;
    std::string iban_;
    std::string bic_;
public:
    BankAccount(std::string owner, std::string account, std::string iban, std::string bic);
    // TODO: declare setters
    void Balance(float b);
    void AddToBalance(float amount);
    void Owner(std::string n);
    void AccountNumber(std::string n);
    void Iban(std::string iban);
    void Bic(std::string bic);

    // TODO: declare getters
    float Balance() const;
    std::string Owner() const;
    std::string AccountNumber() const;
    std::string Iban() const;
    std::string Bic() const;
};

BankAccount::BankAccount(std::string owner, std::string account, std::string iban, std::string bic) : owner_(owner), iban_(iban), bic_(bic) {
    balance_ = 0.0;
}


// TODO: implement setters
void BankAccount::Balance(float b) { balance_ = b; }
void BankAccount::AddToBalance(float amount) {
    balance_ += amount;
}
void BankAccount::Owner(std::string n) { owner_ = n; }
void BankAccount::AccountNumber(std::string n) { account_number_ = n; }
void BankAccount::Iban(std::string iban) { iban_ = iban;}
void BankAccount::Bic(std::string bic) { bic_ = bic; }

// TODO: implement getters
float BankAccount::Balance() const { return balance_; }
std::string BankAccount::Owner() const { return owner_; }
std::string BankAccount::AccountNumber() const { return account_number_; }
std::string BankAccount::Iban() const { return iban_; }
std::string BankAccount::Bic() const { return bic_; }


int main(){
    // TODO: instantiate and output a bank account
    BankAccount me("Ich", "AccountNo1", "DE13456789", "some_bank");
    me.Balance(-100);
    std::cout << me.Owner() << " has " << me.Balance() << " On Bank Account:" << me.Iban() << std::endl;
}