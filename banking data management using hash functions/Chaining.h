#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>
using namespace std;

class Chaining : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    int binarysearch(vector<int> &vec, int count);
    void insert(vector<int> &vec, int count);
    Chaining(){
        size = 0;
        bankStorage2d.resize(initial_size_of_the_vector);
    }
    
private:
    // Other data members and functions specific to Chaining
    const int initial_size_of_the_vector = 100000;
    vector<int> vec;
    int size;
};

#endif // CHAINING_H
