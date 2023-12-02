#include "LinearProbing.h"
#include <iostream>
using namespace std;

int LinearProbing::binarysearch(vector<int> &vec, int count)
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

void LinearProbing::insert(vector<int> &vec, int count)
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
void LinearProbing::createAccount(std::string id, int count)
{
    // IMPLEMENT YOUR CODE HERE
    // cout << id << ";" << count << ";" << hash(id) << "Acc_created" << endl;
    Account acc_to_be_created;
    acc_to_be_created.id = id;
    acc_to_be_created.balance = count;
    int idx = hash(id);
    if (bankStorage1d[idx].balance == -1)
    {
        bankStorage1d[idx] = acc_to_be_created;
    }
    else
    {
        while (bankStorage1d[idx].balance != -1)
        {
            idx = (idx + 1) % 100000;
        }
        bankStorage1d[idx] = acc_to_be_created;
    }
    insert(vec, count);
    size++;
}

std::vector<int> LinearProbing::getTopK(int k)
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
        for (int i = vec.size() - 1; ((i >= 0) && (i >= vec.size() - k)); i--)
        {
            vec_to_be_returned.push_back(vec[i]);
        }
    }
    return vec_to_be_returned; // Placeholder return value
}

int LinearProbing::getBalance(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    // cout << id << ";" << hash(id) << "Getbalance" << endl;
    if (doesExist(id))
    {
        int t = hash(id);
        if (bankStorage1d[t].id == id)
        {
            return bankStorage1d[t].balance;
        }
        else
        {
            while (bankStorage1d[t].id != id)
            {
                t = (t + 1) % 100000;
            }
            return bankStorage1d[t].balance;
        }
    }
    return -1; // Placeholder return value
}

void LinearProbing::addTransaction(std::string id, int count)
{
    // IMPLEMENT YOUR CODE HERE
    // cout << id << ";" << count << ";" << hash(id) << "Addtrans" << endl;
    if (doesExist(id))
    {
        int t = hash(id);
        if (bankStorage1d[t].id == id)
        {
            int temp = bankStorage1d[t].balance;
            int location_finder = binarysearch(vec, temp);
            vec.erase(vec.begin() + location_finder);
            insert(vec, temp + count);
            bankStorage1d[t].balance = temp + count;
        }
        else
        {
            while (bankStorage1d[t].id != id)
            {
                t = (t + 1) % 100000;
            }
            int temp = bankStorage1d[t].balance;
            int location_finder = binarysearch(vec, temp);
            vec.erase(vec.begin() + location_finder);
            insert(vec, temp + count);
            bankStorage1d[t].balance = bankStorage1d[t].balance + count;
        }
    }
    else
    {
        createAccount(id, count);
    }
}

bool LinearProbing::doesExist(std::string id)
{
    // // IMPLEMENT YOUR CODE HERE
    // int t = hash(id);
    // int temp = t;
    // if (bankStorage1d[t].id == id)
    // {
    //     return true;
    // }
    // else
    // {
    //     while (bankStorage1d[t].id != id && t!=temp)
    //     {
    //         t = (t + 1) % 100000;
    //     }
    //     if(t==temp){
    //         return false;
    //     }
    //     if (bankStorage1d[t].id == id && t!=temp)
    //     {
    //         return true;
    //     }
    // }
    // return false; // Placeholder return value
    int t = hash(id);
    int temp = t;
    if (bankStorage1d[t].id == id)
    {
        return true;
    }
    else
    {
        while (bankStorage1d[t].id != id)
        {
            t = (t + 1) % 100000;
            if (t == temp)
            {
                return false;
            }
        }
        if (bankStorage1d[t].id == id)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // for (int i = 0; i < 100000; i++)
    // {
    //     if (bankStorage1d[i].id == id)
    //     {
    //         return true;
    //     }
    // }
    // return false;
}

bool LinearProbing::deleteAccount(std::string id)
{
    // IMPLEMENT YOUR CODE HERE
    // cout << id << ";" << hash(id) << "delete" << endl;
    if (doesExist(id))
    {
        int t = hash(id);
        if (bankStorage1d[t].id == id)
        {
            int locationfinder = binarysearch(vec, bankStorage1d[t].balance);
            vec.erase(vec.begin() + locationfinder);
            bankStorage1d[t].id = "new";
            bankStorage1d[t].balance = -1;
            size--;
            return true;
        }
        else
        {
            while (bankStorage1d[t].id != id)
            {
                t = (t + 1) % 100000;
            }
            int locationfinder = binarysearch(vec, bankStorage1d[t].balance);
            vec.erase(vec.begin() + locationfinder);
            bankStorage1d[t].id = "new";
            bankStorage1d[t].balance = -1;
            size--;
            return true;
        }
    }
    else
    {
        return false; // Placeholder return value
    }
}

int LinearProbing::databaseSize()
{
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int LinearProbing::hash(std::string id)
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
