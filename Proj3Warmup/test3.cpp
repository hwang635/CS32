#include <iostream>
#include <vector>
#include <list>
using namespace std;

const int MAGIC = 11223344;

void test()
{
    bool allValid = true;

    vector<int> v1(5, MAGIC); //init vector of size 5, each int = 11223344
    int k = 0;
    for (; k != v1.size(); k++) //loops depends on incremented int k counter
    {
        if (v1[k] != MAGIC)
        {
            cout << "v1[" << k << "] is " << v1[k] << ", not " << MAGIC << "!" << endl;
            allValid = false;
        }
        if (k == 2)
        {
            for (int i = 0; i < 5; i++) //Adds 5 int elements = 11223355
                v1.push_back(MAGIC);
        }
    }
    if (allValid && k == 10)
        cout << "Passed test 1" << endl;
    else
        cout << "Failed test 1" << endl;

    allValid = true;
    list<int> l1(5, MAGIC);
    k = 0;
    for (list<int>::iterator p = l1.begin(); p != l1.end(); p++, k++) //same as prev loop, loop depends on ++int k and itr p
    {
        if (*p != MAGIC)
        {
            cout << "Item# " << k << " is " << *p << ", not " << MAGIC << "!" << endl;
            allValid = false;
        }
        if (k == 2)
        {
            for (int i = 0; i < 5; i++)
                l1.push_back(MAGIC);
        }
    }
    if (allValid && k == 10)
        cout << "Passed test 2" << endl;
    else
        cout << "Failed test 2" << endl;

    allValid = true;
    vector<int> v2(5, MAGIC);
    k = 0;
    //ERROR after k=2, add items to v2 + memory loc shuffled ("can't increment vector it past end")
    for (vector<int>::iterator p = v2.begin(); p != v2.end(); p++, k++)
    {
        if (k >= 20)  // prevent infinite loop
            break;
        if (*p != MAGIC)
        {
            cout << "Item# " << k << " is " << *p << ", not " << MAGIC << "!" << endl;
            allValid = false;
        }
        if (k == 2)
        {
            for (int i = 0; i < 5; i++)
                v2.push_back(MAGIC);
        }
    }
    if (allValid && k == 10)
        cout << "Passed test 3" << endl;
    else
        cout << "Failed test 3" << endl;
}

int main()
{
    test();
}