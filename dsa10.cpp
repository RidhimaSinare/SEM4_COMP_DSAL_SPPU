#include<iostream>
#include<queue>
using namespace std;

class node
{
    int val;
    node *left,*right;
public:
    node()
    {
        val=0;
        left=nullptr;
        right=nullptr;
    }

    friend class Heap;
};

class Heap
{
    node *root=nullptr;
    int numNodes=0;

public:
    void insert(int keys[],int n)
    {   //n is num of nodes to insert in keys
        //keys is BT array so we are inserting in keys
        numNodes=n;

        //root is first value of array
        node *newNode= new node();
        newNode->val=keys[0];
        root=newNode;

        //level wise traversal and insert nodes from keys
        int i=0;
        queue<node*> q;
        q.push(root);

        while(i<n-1)
        {
            node* poppedNode=q.front();
            q.pop();

            //insert left
            node *leftNode = new node();
            leftNode->val=keys[++i];
            poppedNode->left=leftNode;
            q.push(poppedNode->left);

            //right insert
            node *rightNode=new node();
            rightNode->val=keys[++i];
            poppedNode->right=rightNode;
            q.push(poppedNode->right);
        }//end of while
    }//end of insert func

    void breadthFirst()
    {
        queue<node*>q;
        q.push(root);
        cout<<endl;
        while(!q.empty())
        {
            node* popped= q.front();
            cout<<popped->val<<" ";
            q.pop();

            if(popped->left!=nullptr)
            {
                q.push(popped->left);
            }
            if(popped->right!=nullptr)
            {
                q.push(popped->right);
            }

        }//end of while
        cout<<endl;
    }//end of bfs

    node* heapify(node *Node)
    {
        if(Node==nullptr)
        {
            return nullptr;
        }
        Node->left=heapify(Node->left);
        Node->right=heapify(Node->right);

        if(Node->left!=nullptr && Node->left->val > Node->val)
        {
            //left child val greater than left root so swap val
            int temp=Node->left->val;
            Node->left->val=Node->val;
            Node->val=temp;
        }
        if(Node->right!=nullptr && Node->right->val > Node->val)
        {
            //right child val > right root so swap
            int temp=Node->right->val;
            Node->right->val=Node->val;
            Node->val=temp;
        }

        return Node;
    }//end of heapify func

    void sort()
    {
        //heap Sort Algorithm
        for(int i=0;i<numNodes;i++)
        {
            //heapify tree
            heapify(root);

            //get last node fromheapified tree
            node *lastNode=getLastNodeValue();

            //swap val of root node and last node
            int temp=lastNode->val;
            lastNode->val=root->val;
            root->val=temp;

            //print val of lastnode and delete it from tree
            cout<<lastNode->val<<"  ";
            deleteNode(root,lastNode->val);  
        }
        cout<<endl;
    }// end of sort func

    node *deleteNode(node *Node,int val)
    {
        if(Node==nullptr)
        {
            return nullptr;
        }
        if(Node->val==val)
        {
            delete Node;
            return nullptr;
        }
        Node->left=deleteNode(Node->left,val);
        Node->right=deleteNode(Node->right,val);
        return Node;
    }//end of delete

    node *getLastNodeValue()
    {
        //perform bfs and get last node as the popped one

        queue<node*> q;
        q.push(root);
        node* poppedNode=nullptr;

        while(!q.empty())
        {
            poppedNode=q.front();
            q.pop();
            if(poppedNode->left!=nullptr)
            {
                q.push(poppedNode->left);
            }
            if(poppedNode->right!=nullptr)
            {
                q.push(poppedNode->right);
            }
        }
        return poppedNode;
    }
};

int main() {
    int keys[ 7 ] = { 87 , 5 , 34 , 99 , 44 , 12 , 68 } ; 
    Heap heap ; 
    heap.insert( keys , 7 ) ;
    heap.sort() ; 
    return 0 ;
}