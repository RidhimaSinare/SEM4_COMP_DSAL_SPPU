#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class Node
{
public:
    Node *left;
    int data;
    Node *right;
    
    Node(int d)
    {
        left = NULL;
        data = d;
        right = NULL;
    }
};

Node* makeTree(Node *root)
{
    cout<<" Enter data for node (-1 indicates for no data): ";
    int d;
    cin>>d;
    root = new Node(d);
    
    if(d == -1)
        return NULL;
    
    cout<<"Enter data to the left of "<<d;
    root->left = makeTree(root->left);
    cout<<"Enter data to the right of "<<d;
    root->right = makeTree(root->right);
    return root;
}

void SwapNode(Node *root)
{
    if(root)
    {
        if(root->left || root->right)
        {
            Node *temp = root->left;
            root->left = root->right;
            root->right = temp;
        }
        SwapNode(root->right);
        SwapNode(root->left);
    }
}

void recpostorder(Node *root)
{
    if(root == NULL)
        return;

    recpostorder(root->left);
    recpostorder(root->right);
    cout<<root->data<<" ";
}

void recpreorder(Node *root)
{
    if(root == NULL)
        return;

    cout<<root->data<<" ";
    recpreorder(root->left);
    recpreorder(root->right);
}

void recinorder(Node *root)
{
    if(root == NULL)
        return;

    recinorder(root->left);
    cout<<root->data<<" ";
    recinorder(root->right);
}

void iteinorder(Node *root)
{
    stack<Node*> s;
    Node *curr = root;
    while(!s.empty() or curr!=NULL)
    {
        if(curr!=NULL)
        {
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();
        cout<<curr->data<<" ";

        curr = curr->right;
    }
}

void itepreorder(Node *root)
{
    stack<Node*> s;
    Node *curr = root;
    s.push(root);
    while(!s.empty() or curr!=NULL)
    {
        Node *t = s.top();
        s.pop();
        cout<<t->data<<" ";
        if(t->right)
            s.push(t->right);
        if(t->left)
            s.push(t->left);
    }
}

void itepostorder(Node *root)
{
    stack<Node*> s1, s2;
    s1.push(root);
    while(!s1.empty())
    {
        Node *t = s1.top();
        s1.pop();
        s2.push(t);
        if(t->left)
            s1.push(t->left);
        if(t->right)
            s1.push(t->right);
    }
    while(!s2.empty())
    {
        cout<<s2.top()->data<<" ";
        s2.pop();
    }
}

int findheight(Node* root)
{
    if(root == NULL) return 0;

    int heightL = findheight(root->left);
    int heightR = findheight(root->right);

    return max(heightL,heightR)+1;
}


int LeafCount(Node *root)
{
    if(root == NULL)
        return 0;
    else if(root->left == NULL and root->right == NULL)
        return 1;
    else
        return LeafCount(root->right) + LeafCount(root->left);
}

int InternalNodes(Node *root)
{
    if(root == NULL or (root->right == NULL and root->left == NULL))
        return 0;
    else return 1 + InternalNodes(root->left) + InternalNodes(root->right);
}

void deleteAllNodes(Node* root)
{
    if (root == NULL) return;

    deleteAllNodes(root->left);
    deleteAllNodes(root->right);

    cout << "\n Deleting node: " << root->data;
    delete root;
}


int main()
{
    char y='y';
    int ch;
    Node *root;
    while(y=='y')
    {
        cout<<endl<<"MENU"<<endl;
        cout<<"1.Create Tree";
        cout<<endl<<"2.Inorder";
        cout<<endl<<"3.Preorder";
        cout<<endl<<"4.Postorder";
        cout<<endl<<"5.Height of tree";
        cout<<endl<<"6.Leaf count";
        cout<<endl<<"7.Internal Nodes";
        cout<<endl<<"8.Delete All Nodes";
        cin>>ch;
        switch(ch)
        {
            case 1:root=makeTree(root);break;
            case 2:recinorder(root);break;
            case 3:recpreorder(root);break;
            case 4:recpostorder(root);break;
            case 5:cout<<findheight(root);break;
            case 6:cout<<LeafCount(root);break;
            case 7:cout<<InternalNodes(root);break;
            case 8:deleteAllNodes(root);break;
            
        }

    }
}