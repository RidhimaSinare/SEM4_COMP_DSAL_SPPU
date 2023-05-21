#include<iostream>
using namespace std;

class node
{
    int data;
    node *left;
    node *right;

    public:
    node(int d)
    {
        this->data=d;
        this->right=nullptr;
        this->left=nullptr;
    }

    friend class BST;
};

class BST
{
    node *root;
    public:
        BST(int i)
        {
            this->root=new node(i);
        }

        node *getRoot()
        {
            return this->root;
        }

        void insert(int i)
        {
            node *current=root;
            node *previous=nullptr;


            while(current!=nullptr)
            {
                previous=current;
                if(i<current->data)
                {
                    current=current->left;
                }
                else
                {
                    current=current->right;
                }
            }
            if(i<previous->data)
            {
                node *newNode=new node(i);
                previous->left=newNode;
            }
            else
            {
                node *newNode=new node(i);
                previous->right=newNode;
            }
        }

        void displayInorder(node *Node)
        {
            if(Node==nullptr)
            {
                return;
            }
            else
            {
                displayInorder(Node->left);
                cout<<Node->data<<" ";
                displayInorder(Node->right);
            }
        }

        void displayPreorder(node *Node)
        {
            if(Node==nullptr)
            {
                return;
            }
            else
            {
                cout<<Node->data<<" ";
                displayInorder(Node->left);
                displayInorder(Node->right);
            }
        }

        void displayPostorder(node *Node)
        {
            if(Node==nullptr)
            {
                return;
            }
            else
            {
                displayInorder(Node->left);
                displayInorder(Node->right);
                cout<<Node->data<<" ";
            }
        }

        void search(int key)
        {
            node *current=root;
            int level=0;
            while(current!=nullptr)
            {
            if(current->data==key)
            {
                cout<<endl<<"Element Found";
                cout<<endl<<"Level: "<<level<<endl;
            }
            else if(key<current->data)
            {
                current=current->left;
                level++;
            }
            else
            {
                current=current->right;
                level++;
            }
            }

            if(current==nullptr)
            {
                cout<<endl<<"Element Not Found";
            }
        }

        void minElement()
        {
            node *current=root;
            while(current->left!=nullptr)
            {
                current=current->left;
            }
            cout<<endl<<"Minimum Element: "<<current->data;
        }

        void maxElement()
        {
            node *current=root;
            while(current->right!=nullptr)
            {
                current=current->right;
            }
            cout<<endl<<"Maximum Element: "<<current->data;
        }

        int longestPath(node *root)
        {
            if(root==nullptr)
                return -1;
            int left=longestPath(root->left);
            int right=longestPath(root->right);

            return max(left,right)+1;
        }

        void swapNodes(node *root)
        {
            node *current=root;
            node *temp;
            
            if(current!=nullptr)
            {
                temp=current->left;
                current->left=current->right;
                current->right=temp;
            
            swapNodes(current->left);
            swapNodes(current->right);
            }
            else
                return ;

        }
};

int main()
{
    return 0;
}