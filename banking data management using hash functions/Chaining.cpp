#include "Chaining.h"
#include <iostream>
using namespace std;

int Chaining::binarysearch(vector<int> &vec, int count)
{
    if (vec.size() == 0)
    {
        return 0;
    }
    else if (vec.size() == 1)
    {
        if (count > vec[0])
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    else
    {
        int left = 0;
        int right = vec.size();
        int mid;
        while (left < right)
        {
            mid = (left + right) / 2;
            if (vec[mid] == count)
            {
                return mid;
            }
            else if (vec[mid] < count)
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        return left;
    }
}

void Chaining::insert(vector<int> &vec, int count)
{
    if (vec.size() == 0)
    {
        vec.push_back(count);
    }
    else if (vec.size() == 1)
    {
        if (vec[0] < count)
        {
            vec.push_back(count);
        }
        else if (vec[0] > count)
        {
            vec.insert(vec.begin(), count);
        }
    }
    else
    {
        int location_finder = binarysearch(vec, count);
        vec.insert(vec.begin() + location_finder, count);
    }
}

void Chaining::createAccount(std::string id, int count)
{
    // IMPLEMENT YOUR CODE HERE
    Account acc_to_be_created;
    acc_to_be_created.id = id;
    acc_to_be_created.balance = count;
    int index = hash(id);
    bankStorage2d[index].push_back(acc_to_be_created);
    insert(vec, count);
    size++;
}

std::vector<int> Chaining::getTopK(int k)
{
    // IMPLEMENT YOUR CODE HERE
    vector<int> vec_to_be_returned;
    if (k >= vec.size())
    {
        for (int i = vec.size() - 1; i >= 0; i--)
        {
            vec_to_be_returned.push_back(vec[i]);
        }
    }
    else
    {
        for (int i = vec.size() - 1; (i >= 0) && (i >= vec.size() - k); i--)
        {
            vec_to_be_returned.push_back(vec[i]);
        }
    }
    return vec_to_be_returned; // Placeholder return value
}

int Chaining::getBalance(std::string id)
{

    // IMPLEMENT YOUR CODE HERE
    int t = hash(id);
    for (int i = 0; i < bankStorage2d[t].size(); i++)
    {
        if (bankStorage2d[t][i].id == id)
        {
            return bankStorage2d[t][i].balance;
        }
    }
    return -1; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count)
{
    // IMPLEMENT YOUR CODE HERE
    if (doesExist(id))
    {
        int t = hash(id);

        for (int i = 0; i < bankStorage2d[t].size(); i++)
        {
            if (bankStorage2d[t][i].id == id)
            {
                int locationfinder = binarysearch(vec, bankStorage2d[t][i].balance);
                int temp = vec[locationfinder] + count;
                vec.erase(vec.begin() + locationfinder);
                insert(vec, temp);
                bankStorage2d[t][i].balance = bankStorage2d[t][i].balance + count;
                break;
            }
        }
    }
    else
    {
        createAccount(id, count);
    }
}

bool Chaining::doesExist(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int t = hash(id);
    if (bankStorage2d.size() > t)
    {
        for (int i = 0; i < bankStorage2d[t].size(); i++)
        {
            if (bankStorage2d[t][i].id == id)
            {
                return true;
            }
        }
    }
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    int t = hash(id);
    if (bankStorage2d.size() > t)
    {
        for (int i = 0; i < bankStorage2d[t].size(); i++)
        {
            if (bankStorage2d[t][i].id == id)
            {
                int locationfinder = binarysearch(vec, bankStorage2d[t][i].balance);
                vec.erase(vec.begin() + locationfinder);
                bankStorage2d[t].erase(bankStorage2d[t].begin() + i);
                size--;
                return true;
            }
        }
    }
    return false; // Placeholder return value
}
int Chaining::databaseSize()
{
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int Chaining::hash(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    unsigned long int hash = 0;
    for (int i = 0; i < id.size(); i++)
    {
        hash = hash * 5334 + id[i] * i;
    }
    int t = hash % 99983;
    return t; // Placeholder return value
}
// int main(){
//     Chaining ch;
//     ch.addTransaction("wHW_DTwxMQAePGSZ7IhOGg5Cgs73MB",923);
//     cout<<ch.getBalance("wHW_DTwxMQAePGSZ7IhOGg5Cgs73MB")<<endl;
//     ch.addTransaction("3qde49choRixZAAO7fOyztIdrm_5a", 97);
//     cout<<ch.getBalance("3qde49choRixZAAO7fOyztIdrm_5a")<<endl;
//     cout<<ch.deleteAccount("ENE4tsMzUwiENE4tsMzUwi")<<endl;
//     cout<<ch.deleteAccount("3qde49choRixZAAO7fOyztIdrm_5a")<<endl;
//     ch.createAccount("MMwfiMEVlwnkXX", 672);
//     cout<<ch.getBalance("MMwfiMEVlwnkXX")<<endl;
//     cout<<ch.getBalance("3qde49choRixZAAO7fOyztIdrm_5a")<<endl;
//     cout<<ch.getBalance("wHW_DTwxMQAePGSZ7IhOGg5Cgs73MB")<<endl;
//     // ch.databaseSize;
//     vector<int> k = ch.getTopK(3);
//     for(int i = 0; i<k.size(); i++){
//         cout<<k[i]<<endl;
//     }

//     cout<<1<<endl;
//     return 0;
// }