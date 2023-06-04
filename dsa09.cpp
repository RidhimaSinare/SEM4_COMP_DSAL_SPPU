#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
#include<queue>

class node
{
    int key,height;
    node *left,*right;
public:
    node(int k)
    {
        this->key=k;
        this->height=0;
        left=right=nullptr;
    }
    node(){}

    friend class AVL;
};

class AVL
{
    node *root;

    int getHeight(node *temp)
    {
        if(temp==nullptr)
        {
            return 0;
        }
        else
        {
            return temp->height;
        }
    }// end of getHeight

    int balanceFactor(node *temp)
    {
        if(root==nullptr)
        {
            return 0;
        }
        else
        {
            return getHeight(temp->left)-getHeight(temp->right);
        }
    }

    void changeHeight(node *temp)
    {
        temp->height=1+ max(getHeight(temp->left),getHeight(temp->right));
    }

    node* LLrotate(node *temp)
    {
        node *newNode=temp->left;
        temp->left=newNode->right;
        newNode->right=newNode;

        changeHeight(temp);
        changeHeight(newNode);

        return newNode;
    }

    node* RRrotate(node *temp)
    {
        node* newNode=temp->right;
        temp->right=newNode->left;
        newNode->left=newNode;

        changeHeight(temp);
        changeHeight(newNode);

        return newNode;
    }

    node *RLrotate(node *temp)
    {
        temp->right=LLrotate(temp->right);
        return RRrotate(temp);
    }

    node *LRrotate(node *temp)
    {
        temp->left=RRrotate(temp->left);
        return LLrotate(temp);
    }

    node *balanceTree(node *temp)
    {
        if(balanceFactor(temp)==2)
        {
            if(balanceFactor(temp->left)<0)
            {
                temp=LRrotate(temp);
            }
            else
            {
                temp= LLrotate(temp);
            }
        }
        else if(balanceFactor(temp)==(-2))
        {
            if(balanceFactor(temp->right)>0)
            {
                temp= RLrotate(temp);
            }
            else
            {
                temp= RRrotate(temp);
            }
        }
        changeHeight(temp);
        return temp;
    }

    void inorder( node *root ) {
        if( root == nullptr )
            return;
        inorder( root->left );
        cout<< root->key <<" ";
        inorder( root->right );
    }

    node *insertSubTree(node *temp,int key)
    {
        if(temp==nullptr)
        {
            node *newNode=new node(key);
            temp=newNode;
           return newNode;
        }

        if(temp->key>key)
        {
            temp->left=insertSubTree(temp->left,key);
        }
        else if(temp->key<key)
        {
            temp->right=insertSubTree(temp->right,key);
        }
        else
        {
            temp->key=key;
            return temp;
        }
        return balanceTree(temp);
    }

    node *deletion(node *temp,int &key)
    {
        if(temp==nullptr)
        {
            return nullptr;
        }

        if(temp->key==key)
        {
            //2 child
            if(temp->left!=nullptr && temp->right!=nullptr)
            {
                node *n=temp->right;
                while(n->left!=nullptr)
                {
                    n=n->left;
                }
                n=temp;
                temp->key=n->key;
                temp->right=deletion(temp->right,n->key);

            }
            //one child
            if(temp->left!=nullptr && temp->right==nullptr)
            {
                node *leftChild=temp->left;
                delete temp;
                return leftChild;
            }
            else if(temp->left==nullptr && temp->right!=nullptr)
            {
                node *rightchild=temp->right;
                delete temp;
                return rightchild;
            }
            else
            {
                delete temp;
                return nullptr;
            }
        }

        else
        {
            if(key<temp->key)
            {
                temp->left=deletion(temp->left,key);
            }
            else
            {
                temp->right=deletion(temp->right,key);
            }
        }
    int bf=balanceFactor(temp);
    if(bf!=2 && bf!=-2)
    {
        return temp;
    }
    else
    {
        return balanceTree(temp);
    }

    }

    public:
    AVL()
    {
        root=nullptr;
    }

    void insert(int key)
    {
        root=insertSubTree(root,key);
    }

    void display()
    {
        cout<<endl<<"inorder display: ";
        inorder(root);
    }

    void search(int key)
    {
        node *curr=root;
        bool found=false;
        while(curr!=nullptr)
        {
            if(curr->key==key)
            {
                cout<<endl<<"key found at height: ";
                cout<<curr->height;
                found=true;
                break;
            }
            else if(curr->key>key)
            {
                curr=curr->left;
            }
            else
            {
                curr=curr->right;
            }
        }
        if(!found)
        {
            cout<<endl<<"Key not present";
        }
    }

    void BFS()
    {
        queue<node*> q;
        q.push(root);
        cout<<endl;
        while(!q.empty())
        {
            node *popped=q.front();
            q.pop();
            cout<<popped->key<<"  ";

            if(popped->left!=nullptr)
            {
                q.push(popped->left);
            }
            if(popped->right!=nullptr)
            {
                q.push(popped->right);
            }
        }
        cout<<endl;
    }

    void del(int val)
    {
        root=deletion(root,val);
        cout<<"\nDeletion successful";
    }



};


int main() {
    AVL tree ; 
    while( true ) {
        int option ; 
        cout << "Enter option: " << "\n" ; 
        cout << "1. Insert key, value" << "\n" ; 
        cout << "2. Inorder traversal" << "\n" ;
        cout << "3. Search" << "\n" ;
        cout << "4. Delete" << "\n" ;
        cout << "5. BFS" << "\n" ;
        cin >> option ; 
        if( option == 1 ) {
            int key ; 
            cout << "Enter key: " << "\n" ; cin >> key ; 
            tree.insert( key  ) ; 
        }
        else if( option == 2 ) {
            cout << "Inorder traversal -> " ;
            tree.display() ; 
        }
        else if( option == 3 ) {
            int key ; 
            cout << "Enter key to search: " << "\n" ; cin >> key ; 
           tree.search(key);
        }
        else if( option == 4 ){
            int key ; 
            cout << "Enter key to delete: " << "\n" ; cin >> key ;
            tree.del(key);
        }
        else if( option == 5 ) {
            cout << "BFS traversal is " ; 
            tree.BFS() ; 
        }
    }

    return 0 ; 
}
