#include <iostream>
#include <iomanip>
using namespace std;
#define size 10

class Client
{
    string name;
    long int telephone;
    friend class HashTable;
};

long int getHashCode(long int key)
{
    return key % size;
}

class HashTable
{
    Client HashArray[size];

public:
    HashTable()
    {
        for (int i = 0; i < size; i++)
        {
            HashArray[i].telephone = 0;
            HashArray[i].name = "--";
        }
    }
    void insert(string, long int);
    void insertR(string, long int);
    void display();
    void search(long int key);
    void del(long int key);
    int hash(long int);
};

void HashTable::insert(string name, long int num) // without replacement
{
    Client c;
    c.name = name;
    c.telephone = num;
    int iPos;
    int count = 0;
    char ans;

    iPos = getHashCode(c.telephone);
    if (HashArray[iPos].telephone == 0)
    {
        HashArray[iPos] = c;
    }
    else
    {
        while (HashArray[iPos].telephone != 0)
        {
            // iPos = (iPos + 1) % size;
            iPos++;
        }
        HashArray[iPos] = c;
    }
    cout << "\nRecord added!";
    count++;
}

void HashTable::insertR(string name, long int num)
{
    Client c, r;
    c.name = name;
    c.telephone = num;
    int count = 0;
    int iPos;

    iPos = getHashCode(c.telephone);

    if (HashArray[iPos].telephone == 0)
    {
        HashArray[iPos] = c;
    }
    else
    {
        r = HashArray[iPos];
        if (getHashCode(r.telephone) == iPos)
        {
            for (int i = iPos + 1; i % size != 0; i++)
            {
                if (HashArray[i].telephone == 0)
                {
                    HashArray[i] = c;
                    break;
                }
            }
        }
        else
        {
            HashArray[iPos] = c;
            for (int i = iPos + 1; i % size != 0; i++)
            {
                if (HashArray[i].telephone == 0)
                {
                    HashArray[i] = r;
                    break;
                }
            }
        }
    }
    cout << "\nRecord added!";
    count++;
}

void HashTable::display()
{
    cout << "\n----------------------------------------------------------------------";
    cout << "\nSr.No" << setw(25) << "Name" << setw(30) << "Telephone";
    cout << "\n----------------------------------------------------------------------";
    for (int i = 0; i < size; i++)
    {
        cout << endl;
        cout << i << setw(30) << HashArray[i].name << setw(30) << HashArray[i].telephone;
    }
}

void HashTable::search(long int key)
{
    int flag = 0;
    // int a = 0;
    int count = 1;
    // cout << "\nEnter Number to search: ";
    // cin >> key;
    int index = getHashCode(key);
    while (count != 9)
    // for (int i = index; i < size; i++)
    {
        if (HashArray[index].telephone == key)
        {
            cout << "\nClient Found!";
            cout << "\nPosition: " << index;
            cout << endl
                 << HashArray[index].name << ": " << HashArray[index].telephone;
            flag = 1;
            break;
        }
        else
        {
            index = (index + 1) % size;
        }
        count++;
    }
    if (flag == 0)
    {
        cout << endl
             << "\nClient Record Not Found";
    }
    cout << endl
         << "Number of Comparisons: " << count;
}

void HashTable::del(long int key)
{
    int flag = 0;
    cout << "\nEnter Number to delete: ";
    cin >> key;
    for (int i = 0; i < size; i++)
    {
        if (key == HashArray[i].telephone)
        {
            HashArray[i].name = "--";
            HashArray[i].telephone = 0;
            flag = 1;
            cout << "\nRecord Deleted!";
        }
    }
    if (flag == 0)
    {
        cout << "\nRecord not present";
    }
}

int main()
{
    HashTable h;
    HashTable hR;
    char ans, y;
    long int key;
    string name;
    long int num;
    do
    {
        cout << "\n1.Insert\n2,Display\n3.Search\n4.Delete";
        int ch;
        cout << "\nEnter choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            do
            {
                cout << "\nEnter name: ";
                cin >> name;
                cout << "\nEnter Phone number: ";
                cin >> num;
                h.insert(name, num);
                hR.insertR(name, num);
                cout << "\nDo you want to insert more? (Y/y): ";
                cin >> y;
            } while (y == 'y' || y == 'Y');
            break;
        case 2:
            h.display();
            hR.display();
            break;
        case 3:
            cout << "\nEnter Number to search: ";
            cin >> key;
            h.search(num);
            hR.search(num);
            break;
        case 4:
            hR.del(num);
            break;
        }

        cout << "\nDo you want to continue: ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    return 0;
}
