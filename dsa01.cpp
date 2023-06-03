#include<iostream>
using namespace std;


class node
{
    int key;
    node *left,*right;
public:
    node()
    {
        key=0;
        left=right=nullptr;
    }
    node(int i)
    {
        key=i;
        left=right=nullptr;
    }
    friend class BST;

};

class BST
{
    node *root;
public:
    BST()
    {
        root=nullptr;
    }

    node *getRoot()
    {
        return root;
    }

    void insert()
    {   int key;
        cout<<endl<<"Enter key to insert: ";cin>>key;
        if(root==nullptr)
        {
            node *temp=new node(key);
            root=temp;
        }
        else 
        {
            node *current=root;
            node *prev=nullptr;

            while(current!=nullptr)
            {
                prev=current;
                if(current->key >key)
                {
                    current=current->left;
                }
                else
                {
                    current=current->right;
                }

            }
            
            if(prev->key>key)
            {
                node *temp=new node(key);
                prev->left=temp;
            }
            else
            {
                node *temp=new node(key);
                prev->right=temp;
            }
    }
    }

    void display(node *temp)    //inorder
    {   
        if(temp==nullptr)
        {
            return;
        }
        else
        {
            display(temp->left);
            cout<<temp->key<<"  ";
            display(temp->right);
        }
    }

    void search()
    {   int key;
        cout<<endl<<"Enter key to search: ";cin>>key;
        
        node *curr=root;
        int level=0;
        while(curr!=nullptr)
        {
            if(curr->key==key)
            {
                cout<<endl<<"Key found at level: "<<level;
                break;
            }
            else if(curr->key<key)
            {
                curr=curr->right;level++;
            }
            else
            {
                curr=curr->left;level++;
            }
        }
    }

    int longestPath(node *temp)
    {
        
        if(temp==nullptr)
        {
            return -1;
        }
        int left=longestPath(temp->left);
        int right=longestPath(temp->right);

        return max(left,right)+1;
    }

    void swapNodes(node *Node)
    {
        node* curr=Node;
        node *temp;
        if(curr!=nullptr)
        {
            temp=curr->left;
            curr->left=curr->right;
            curr->right=temp;
        swapNodes(curr->left);
        swapNodes(curr->right);
        }
        else{
            return;
        }
    }
};




int main()
{
    int ch;
    BST b;
    while(true)
    {
            cout<<endl<<"1.Insert\n2.Display\n3.Search\n4.Longest Path\n5.Swap"<<endl;
            cout<<"Enter choice: ";cin>>ch;
            switch(ch)
            {
                case 1: b.insert();break;
                case 2: b.display(b.getRoot());break;
                case 3: b.search();break;
                case 4: cout<<"\nLongest Path: "<<b.longestPath(b.getRoot());
                case 5: b.swapNodes(b.getRoot());break;
                case 6:exit(0);
            }
    }
}
