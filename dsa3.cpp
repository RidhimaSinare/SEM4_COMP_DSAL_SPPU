#include<iostream>
#include<stack>
using namespace std;

class node
{
    int data;
    node *left,*right;
    bool lThread,rThread;

    public:
    node(int d)
    {
        this->data=d;
        this->left=nullptr;
        this->right=nullptr;
        this->lThread=true;
        this->rThread=true;
    }

    friend class TBST;
};

class TBST
{
    node *root;
    public:
    TBST()
    {
        root=nullptr;
        cout<<endl<<"Creation of Threaded BST";
        cout<<endl<<"Enter number of nodes: ";
        int n;cin>>n;
        cout<<"Enter value of each node: ";
        int a[n];
        for(int i=0;i<n;i++)
        {
            cin>>a[i];
            insert(a[i]);
        }

    }

    void insert(int key);
    void inorder();void preorder();void postorder();
    node *leftmost(node *root);
    node *inorderSucc(node *root);
    node *inorderPred(node *root);
    void deletion(int key);
};

void TBST::insert(int key)
{
    node *newNode=new node(key);
    if(root==nullptr)
    {
        root=newNode;
        return;
    }

    node *temp=root;
    node *parent=nullptr;

    while(temp!=nullptr)
    {
        if(key==temp->data)
            cout<<endl<<"Key already exists";
            return;
        parent=temp;
        if(key<temp->data)
        {
            if(temp->lThread==false)//thread not present, child present
                temp-temp->left;
            else    
                break;
        }
        else
        {
            if(temp->rThread==false)
                temp=temp->right;
            else
                break;
        }
    }

    if(key<temp->data)
    {
        newNode->left=parent->left;
        newNode->right=parent;
        parent->lThread=false;  //child present , thread removed
        parent->left=newNode;
    }
    else
    {
        newNode->right=parent->right;
        newNode->left=parent;
        parent->rThread=false;
        parent->right=newNode;
    }
}

void TBST::deletion(int key)
{
    node *temp=root;
    node *parent=nullptr;

    while(temp!=nullptr)
    {
        if(key==temp->data)
            return;
        parent=temp;
        if(key<temp->data)
            if(temp->lThread==false) temp=temp->left;
            else break;
        else
            if(temp->rThread==false) temp=temp->right;
            else break;
    }
    if(temp->data!=key)
        cout<<endl<<"Key not found";

    //deleting leaf node
    else if(temp->lThread==true && temp->rThread==true)
    {
        if(parent=nullptr)
            root=nullptr;
        else if(temp==parent->left)
           { parent->lThread=true;
            parent->left=temp->left;}
        else
            parent->rThread=true;
            parent->right=temp->right;

        delete temp;
        cout<<endl<<"Node deleted successfully";
        return;
    }
    //deleting node with single child
    else if((temp->lThread==false && temp->rThread==true)||(temp->rThread==true && temp->rThread==false))
    {
        node *child;
        if(temp->lThread==false)
            child=temp->left;
        else
            child=temp->right;
        
        if(parent==nullptr)
            root=child;
        else if(temp=parent->left)
        {
            parent->left=child;
        }
        else
            parent->right=child;

        node *s=inorderSucc(temp);
        node *p=inorderPred(temp);

        if(temp->lThread==false)    //left child present
            p->right=s;
        else
            s->left=p;

        delete temp;
        cout<<endl<<"Node deleted successfully";
        return;
    }

    //deleting node with 2 children
    else
    {
        node *s=inorderSucc(temp);
        int t=s->data;
        deletion(s->data);
        temp->data=t;
    }

    
}// end of deletion

node* TBST::leftmost(node *temp)
{
    if(temp==nullptr)
        return nullptr;
    while(temp->left!=nullptr && temp->lThread==false)
    {
        temp=temp->left;
    }
    return temp;
}

node* TBST::inorderSucc(node *temp)
{
    if(temp->rThread==true)
        return temp->right;
    else
        temp=temp->right;
        return leftmost(temp);
}

node* TBST::inorderPred(node *temp)
{
    return temp->left;
}

void TBST::inorder()
{
    node *temp=leftmost(root);
    cout<<endl;
    while(temp!=nullptr)
    {
        cout<<temp->data<<"  ";
        if(temp->rThread==true) temp=temp->right;
        else{
            temp=temp->right;
            temp=leftmost(temp);
        }
    }
}

void TBST::preorder()
{
    node *temp=root;
    cout<<endl;
    while(temp!=nullptr)
    {
        cout<<temp->data<<"  ";
        if(temp->lThread==false)
        {
            temp=temp->left;
        }
        else if(temp->rThread==false)
        {
            temp=temp->right;
        }
        else
        {
            while(temp!=nullptr && temp->rThread==true)
            {
                temp=temp->right;
            }
            if(temp!=nullptr)
                temp=temp->right;
        }

    }
    cout<<endl;
}

void TBST::postorder()
{
    stack <node*>s;
    stack <node*> out;
    node *temp=root;
    s.push(temp);
    while(!s.empty())
    {
        temp=s.top();
        s.pop();
        out.push(temp);
        if(temp->lThread==false)
            s.push(temp->left);
        if(temp->rThread==false)
            s.push(temp->right);

    }
    while(!out.empty())
    {
        temp=out.top();
        out.pop();
        cout<<temp->data<<" ";
    }
    cout<<endl;
}

int main()
{
	TBST tree;
	while(true)
    {
		cout<<"Implementation of Threaded BST"<<endl<<endl;
		cout<<"1. Traversal of Threaded BST"<<endl;
		cout<<"2. Delete a node from Threaded BST"<<endl;
		cout<<"3. Exit"<<endl;
		int res;
		cout<<"Enter your choice : ";
		cin>>res;
		if(res==1)
        {
			cout<<"Inorder :";
			tree.inorder();
			cout<<"Preorder :";
			tree.preorder();
			cout<<"Postorder :";
			tree.postorder();
			cout<<endl;
		}
		else if(res==2)
        {
			int n;
			cout<<"Enter a no. to delete from threaded BST : ";
			cin>>n;
			tree.deletion(n);
			cout<<"After deletion : "<<endl;
			cout<<"Inorder :";
			tree.inorder();
			cout<<"Preorder :";
			tree.preorder();
			cout<<"Postorder :";
			tree.postorder();
			cout<<endl;
		}
		else if(res==3)
        {
			cout<<"Terminating program"<<endl;
			break;
		}
		else
            continue;
	}
	return 0;
}