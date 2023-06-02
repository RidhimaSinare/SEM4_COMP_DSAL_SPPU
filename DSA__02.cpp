#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class node
{
    int data;
    node*left,*right;
public:
    node(int k)
    {
        data=k;
        left=right=nullptr;
    }

    friend class BT;
};

class BT
{
    
public:
    node *root;
    BT()
    {
        root=createTree(root);
    }

    node* createTree(node *root)
    {   
        int data;
        cout<<endl<<"Enter value of node (-1 for none): ";
        cin>>data;
        root=new node(data);

        if(data==-1)
        {
            return NULL;
        }

        cout<<endl<<"Enter left node value of "<<data;
        root->left=createTree(root->left);
        cout<<endl<<"Enter right node vale of "<<data;
        root->right=createTree(root->right);

        return root;  
    }

    void swapTree(node *root)
    {
        if(root)
        {
            if(root->left || root->right)
            {
                node *temp=root->left;
                root->left=root->right;
                root->right=temp;
            }
            swapTree(root->right);
            swapTree(root->left);
        }
    }

    void inorder()
    {
        stack<node*> s;
        node* curr=root;
        cout<<endl;
        while(!s.empty() || curr!=nullptr)
        {
            while(curr!=nullptr)
            {
                s.push(curr);
                curr=curr->left;
            }

            curr=s.top();
            s.pop();
            cout<<curr->data<<"  ";

            curr=curr->right;
        }
    }

    void preorder()
    {
        stack<node*> s;
        node* curr=root;
        s.push(curr);
        cout<<endl;
        while(!s.empty())       //IMP ONLY STACK CONDITION NOT CURR 
        {
            node* t=s.top();
            cout<<t->data<<"  ";
            s.pop();

            if(t->right)
            {
                s.push(t->right);
            }
            if(t->left)
            {
                s.push(t->left);
            }
        }
    }

    void postorder()
    {
        stack<node*>s1,s2;
        s1.push(root);
        while(!s1.empty())
        {
            node *t=s1.top();
            s1.pop();
            s2.push(t); // IMP PUSH IN S2

            if(t->left)
            {
                s1.push(t->left);   //IMP PUSH IN S1
            }
            if(t->right)
            {
                s1.push(t->right);
            }
        }
        cout<<endl;
        while(!s2.empty())
        {
            cout<<s2.top()->data<<"  ";
            s2.pop();
        }
    }

    int findHeight(node *root)
    {
        if(root==nullptr)
        {
            return 0;
        }
        else
        {
            int left=findHeight(root->left);
            int right=findHeight(root->right);

            return max(left,right)+1;
        }
    }

    int leafCount(node *root)
    {
        if(root==nullptr) return 0;

        else if(root->left==nullptr && root->right==nullptr)
        {
            return 1;
        }
        else 
        {
            return leafCount(root->left)+leafCount(root->right);
        }
    }

    int internalNodes(node *root)
    {
        if(root==nullptr || (root->left==nullptr && root->right==nullptr))
        {
            return 0;
        }
        else
        {
            return 1+internalNodes(root->left)+internalNodes(root->right);
        }
    }

    void deleteTree(node *root)
    {
        if(root==nullptr)
        {
            return;
        }
        else
        {
            deleteTree(root->left);
            deleteTree(root->right);
            cout<<endl<<"deleting node: "<<root->data;

            delete root;
        }
    }

    node* copy(node *root)
    {
        if(root==nullptr)
        {
            return nullptr;
        }
        else
        {
            node *root_copy=new node(root->data);

            root_copy->left=copy(root_copy->left);
            root_copy->right=copy(root_copy->right);

            return root_copy;

        }
        
    }
};


int main()
{
    BT b;
    b.preorder();
    b.inorder();
    b.postorder();
    return 0;

}
