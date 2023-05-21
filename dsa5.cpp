#include<iostream>
using namespace std;

class node
{
    node *next;
    string word;
    string meaning;

    public:
    node(string key,string value)
    {
        this->word=key;
        this->meaning=value;
        this->next=nullptr;
    }

    friend class Dictionary;
};

class Dictionary
{   int dictionarySize;
    node **headnode;

    int hash(string item)   //hash function
    {
        int ascii=0;
        for(int i=0;i<item.length();i++)
        {
            ascii+=int(item[i]);
        }
        return ascii % dictionarySize;
    }

    void insertNode(node *head , node *newentry)
    {
        node *current=head;
        while (current->next!=nullptr)
        {
            current=current->next;
        }
        current->next=newentry;
        
    }

    void print(node *head)
    {
        node *current=head;
        while(current !=nullptr)
        {
            cout.width(5);
            cout<<current->word<<"  -  "<<current->meaning<<endl;
            current=current->next;
        }
    }


    public:
    Dictionary(int size)
    {
        this->dictionarySize=size;
        headnode=new node*[size];
        for(int i=0;i<size;i++)
        {
            headnode[i]=nullptr;
        }
    }

    void insert(string key,string value)
    {
        int index=hash(key);

        if(headnode[index]==nullptr)
        {
            headnode[index]=new node(key,value);
        }
        else
        {
            node *newnode= new node(key,value);
            insertNode(headnode[index],newnode);
        }
    }

    void display()
    {
        for(int i=0;i<dictionarySize;i++)
        {
            cout.width(5);
            cout<<i<<"  ";
            print(headnode[i]);
            cout<<"\0"<<endl;
        }
    }

    void search(string key)
    {
        int index=hash(key);
        int count=1;

        node *current=headnode[index];
        while(current !=nullptr)
        {
            if(current->word==key)
            {
                cout<<endl<<"word found";
                cout<<current->word<<"  -   "<<current->meaning;
                cout<<endl<<"Number of Comparisons: "<<count;
                break;
            }
            else
            {
                current=current->next;
                count++;
            }
        }
        if(current==nullptr)
        {
            cout<<endl<<"word not found";
            cout<<endl<<"Number of comparisons: "<<count;
        }
    }

    void delWord(string key)
    {
        int index=hash(key);

        if(headnode[index]->word==key)
        {
            node *newhead=headnode[index]->next;
            delete headnode[index];
            headnode[index]=newhead;
        }
        else
        {
            node *current=headnode[index];
            node *previous=nullptr;
            while(current!=nullptr)
            {
                if(current->word==key)
                {
                    break;
                }
                else
                {
                    previous=current;
                    current=current->next;
                }
            }
            previous->next=current->next;
            delete current;
        }
    }
};

int main()
{
    
    Dictionary d(10);
    d.insert("abc" , "godd");
    d.insert("bac" , "dsbjv");
    d.insert("gggg" , "ashv");
    d.display();
    d.delWord("abc");
    d.display();
    d.search("bac");
    d.search("cab");

    return 0;
}