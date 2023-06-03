#include<iostream>
#include<stack>
using namespace std;

class node
{
    int data;
    node *left,*right;
    bool lThread,rThread;
public:
    node()
    {
        data=0;
        left=right=nullptr;
        lThread=rThread=true;
    }
    node(int d)
    {
        data=d;
        left=right=nullptr;
        lThread=rThread=true;
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
    }

    void insert()
    {   int data;
        if(root==nullptr)
        {
            cout<<endl<<"Enter root value: ";cin>>data;
            node *newNode=new node(data);
            root=newNode;
            return ;
        }
        else
        {
            cout<<endl<<"Enter key to insert: ";cin>>data;
            node *newNode=new node(data);
            node *curr=root;
            node *parent=nullptr;

            while(curr!=nullptr)
            {
                
                if(data==curr->data)
                {
                    cout<<endl<<"key exists";
                    return;
                }
                
                parent=curr;
                if(curr->data > data)
                {
                    if(curr->lThread==false)    //left child exists
                    {
                        curr=curr->left;
                    }
                    else{break;}
                }
                else
                {
                    if(curr->rThread==false)    //right child present
                    {
                        curr=curr->right;
                    }
                    else{break;}
                }
            }//end of while parent=curr has happened and now connect newNode and parent

            if((data<parent->data))   //left child of parent
            {
                newNode->left=parent->left;
                parent->left=newNode;
                newNode->right=parent;
                //newNode->lThread=true;
                parent->lThread=false;
                cout<<endl<<"Inserted successfully";
            }
            else
            {
                newNode->right=parent->right;
                parent->right=newNode;
                newNode->left=parent;
                //newNode->lThread=newNode->rThread=true;
                parent->rThread=false;
                cout<<endl<<"Inserted successfully";
            }

        }
    }//end of insert

    void inorder()
    {
        node *curr=root;

        while(curr->left!=nullptr)
        {
            curr=curr->left;    //reached smallest and leftmost key
        }
        cout<<endl;
        while(curr!=nullptr)
        {
            cout<<curr->data<<"  ";

            if(curr -> left == nullptr && curr -> right == nullptr){    //for only one key ie root
                cout<<endl;
                return;
            }

            if(curr->rThread==true)
            {
                curr=curr->right;
            }
            else if(curr->right==nullptr)
            {
                return ;
            }
            else
            {
                curr=curr->right;
                while(curr->lThread==false)     //IMP CONDITION  CHECK THREAD NOT CHILD
                {
                    curr=curr->left;
                }
            }
        }
    }// end of inorder

    void preorder()
    {
        node *curr=root;
        cout<<endl;
        while(curr!=nullptr)
        {
            cout<<curr->data<<"  ";
            
            if(curr->lThread==false)
            {
                curr=curr->left;
            }
            else if(curr->rThread==false)
            {
                curr=curr->right;
            }
            else
            {
                while(curr!=nullptr && curr->rThread==true)
                {
                    curr=curr->right;
                }
                if(curr!=nullptr)
                {
                    curr=curr->right;
                }
            }
        }
    }//end of preorder

    void deletion(int key)
    {   //out<<"\nentering deletion";
        node *curr=root;
        node *parent=nullptr;
        while(curr!=nullptr)
        {
            if(key==curr->data)
            {
                break;      //IMP USE BREAK AND NOT RETURN
            }
            parent =curr;
            if(key<curr->data)
            {
                if(curr->lThread==false)
                {
                curr=curr->left;}
                else{break;}
            }
            else
            {   if(curr->rThread==false){
                curr=curr->right;}
                else{break;}
            }
        }   //fount the element or reached the end

        if(curr->data!=key)
        {
            cout<<endl<<"Element does not exist";
            return ;
        }
        //leaf node
        else if(curr->lThread==true && curr->rThread==true)
        {
    
            if(parent==nullptr)
                root=nullptr;
            else if(parent->left==curr)
            {
                parent->left=curr->left;
                parent->lThread=true;
            }
            else
            {
                parent->right=curr->right;
                parent->rThread=true;
            }
            delete curr;
            cout<<endl<<"Deletion no child successful";
            return;
        }
        //to be deleted node has 1 child
        else if((curr->lThread==true && curr->rThread==false)||(curr->lThread==false && curr->rThread==true))
        {   node *child;
            //has left child
            if(curr->lThread==false)
            {
                child=curr->left;
            }
            else
            {
                child=curr->right;
            }//got the child of to be deleted node

            //check if deleted node is left/r child
            
            if(parent==nullptr)
            {
                root=nullptr;
                return;
            }
            else if(curr==parent->left)
            {
                parent->left=child;
            }
            else
            {
                parent->right=child;
            }
            node *s=inordersucc(curr);
            node *p=pred(curr);

            if(curr->lThread==false)
            {
                p->right=s;
            }
            else
            {
                s->left=p;
            }
            delete curr;
            cout<<endl<<"Deletion 1 child successful";
            return ;

        }
    //2 child
        else
        {
            node *s=inordersucc(curr);
            int t=s->data;
            deletion(s->data);  //IMP FIRST DELETION 
            curr->data=t;       //THEN REALLOCATION
            cout<<endl<<"deletion 2 child";
            return ;
        }
    }//end of deletion

    node *inordersucc(node *temp)
    {
        if(temp->rThread==true)
            return temp->right;
        else
        {
            temp=temp->right;
            while(temp->left!=nullptr && temp->lThread==false)  //IMP TO REMEMBER BOTH CONDITIONS
            {
                temp=temp->left;
            }
            return temp;
        }
    }

    node *pred(node *temp)
    {
        return temp->left;
    }


};


int main()
{
    TBST t;
    int ch;

    while(true)
    {
        cout<<endl<<"1.Insert\n2.Display Inorder\n3.Display Preorder\n4.Delet\n5.Exit";
        cout<<endl<<"Enter choice: ";cin>>ch;
        switch (ch)
        {case 1:t.insert();
                break;
        case 2:t.inorder();break;
        case 3:t.preorder();break;
        case 4:
                int key;
                cout<<endl<<"Enter number to delete: ";cin>>key;
                t.deletion(key);break;
        case 5:exit(0);
        
        default:
            break;
        }
    }
}
