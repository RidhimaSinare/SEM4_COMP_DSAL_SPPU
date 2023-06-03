#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

class HashTable
{
    int empId;
    int location; //in file
    int tablesize=10;

public:
    HashTable()
    {
        empId=0;
        location=0;
    }
    void createHT();
    void showHT();
    int Hash(int);
    void insertHT(int ,int);
    int searchHT();
}HT[10];

//hash table functions
int HashTable ::Hash(int empId)
{
    int Tablesize = 10;
    return (empId % Tablesize);
}

void HashTable::createHT()
{
    int i,tablesize=10;
    for(i=0;i<tablesize;i++)
    {
        HT[i].empId=0;
        HT[i].location=0;
    }

}

void HashTable:: showHT()
{
    for(int i=0;i<tablesize;i++)
    {
        cout<<endl<<i<<" "<<HT[i].empId<<" "<<HT[i].location;
    }
}

void HashTable::insertHT(int empId,int loc)
{
    int index=Hash(empId);
    if(HT[index].location==0)
    {
        HT[index].empId=empId;
        HT[index].location=loc;
    }
    else
    {
        do
        {
            index=(index+1)%tablesize;
        }while(HT[index].location!=0);
        HT[index].empId=empId;
        HT[index].location=loc;
    }
}

int HashTable::searchHT()
{
    int empId;
    int index;
    cout<<endl<<"enter empId to search: ";cin>>empId;

    index=Hash(empId);

    if(HT[index].empId==empId)
    {
        return HT[index].location;
    }
    else
    {
        do
        {
            index=(index+1)%tablesize;
        }while(HT[index].empId!=empId);

        return HT[index].location;
    }    
}

//end of hash table functions

class myFile
{
    char buffer[40],fname[10];
    int empId,count;
    string name,address;
    fstream file;
    HashTable HT;

public:
    myFile()
    {
        empId=0;
        count=0;
        name='\0';
        address='\0';
        cout<<endl<<"enter file name"; 
        cin>>fname;    
    }
    ~myFile()
    {
        remove("file");
    }
    void writefile();
    void readfile();
    void searchrecord();
    void displayrecord();
};

//file class functions

void myFile::writefile()
{
    file.open(fname,ios::out);
    if (!file)
    {
        cout<<endl<<"error";
    }
    else{
        cout<<endl<<"enter num of records: ";
        cin>>count;
        for(int i=0;i<count;i++)
        {
           cout << "emp number : ";
            cin >> empId;
            cout << "Name : ";
            cin >> name;
            cout << "Address : ";
            cin >> address;
            cout << "Location : " << file.tellp() << endl;
            HT.insertHT(empId,file.tellp());
            file << empId << " " << name << " " << address << endl;
             
        }
    }
    file.close();
}

void myFile::searchrecord()
{
    file.open(fname,ios::in);
    if (!file)
    {
        /* code */
        cout<<endl<<"error";
    }
    else
    {
        int id=HT.searchHT();
        file.seekg(id,ios::beg);
        file.getline(buffer,40);
        cout<<"\nrecord: "<<buffer;

    }
    file.close();    
}

void myFile::readfile()
{
    file.open(fname,ios::in);
    if (!file)
    {
        /* code */
        cout<<endl<<"error"<<endl;
    }
    else
    {
        int i=0;
        while(!file.eof())
        {
            file.getline(buffer,40);
            cout<<"Record: "<<buffer<<endl;
            i++;
        }
    }
    file.close();
    cout<<"\nHash Table: "<<endl;
    HT.showHT();
}


int main()
{

    myFile file;

    file.writefile();

    file.readfile();

    file.searchrecord();

    return 0;
}