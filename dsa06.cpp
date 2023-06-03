#include<iostream>
#include<stack>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

class node
{
    string name;
    node *next,*down;
public:
    node(string name)
    {
        this->name=name;
        next=down=nullptr;
    }

    friend class Graph;
};

class Graph
{
    node* head=nullptr;

    void add(string nodeA,string nodeB)
    {
        if(head==nullptr)
        {
            node *node1=new node(nodeA);
            node *node2=new node(nodeB);
            node1->next=node2;
            head=node1;
        }

        else
        {
            node *curr=head;
            node *prev=nullptr;
            bool found=false;
            while(curr!=nullptr)
            {
                if(curr->name==nodeA){
                
                    found=true;
                    node *neighbour=curr;
                    while(neighbour->next!=nullptr)
                    {
                        neighbour=neighbour->next;
                    }
                    node *newNode=new node(nodeB);
                    neighbour->next=newNode;
                
                    break;}
                prev=curr;
                curr=curr->down;

                
            }
            if(!found)
        {
            node *node1=new node(nodeA);
            node *node2=new node(nodeB);
            prev->down=node1;
            node1->next=node2;
        }
        }
        
    }//end of add

public:
    void addNode(string a, string b)
    {
        add(a,b);
        add(b,a);
    }

    void display()
    {
        node *curr=head;
        while(curr!=nullptr)
        {   cout<<endl<<curr->name<<" : ";
            node* neighbour=curr->next;
            while(neighbour!=nullptr)
            {
                cout<<neighbour->name<<" - ";
                neighbour=neighbour->next;
            }
            curr=curr->down;
        }
    }

    void BFS(string initial)
    {   
        cout<<endl<<"BFS is: ";
        queue<string>q;
        vector<string> visited;
        q.push(initial);
        visited.push_back(initial);

        while(true)
        {
            if(!q.empty())
            {
                initial=q.front();
                q.pop();
                cout<<initial<<" - ";
            }
            else
            {
                cout<<endl;
                break;
            }

            node*curr=head;
            bool found=false;
            while(curr!=nullptr)
            {
                if(curr->name==initial)
                {
                    found=true;
                    node *neigh=curr->next;
                    while(neigh!=nullptr)
                    {
                        if(find(visited.begin(),visited.end(),neigh->name)==visited.end())
                        {
                            q.push(neigh->name);
                        visited.push_back(neigh->name);
                        }
                        neigh=neigh->next;
                    }
                    break;
                    
                }
                curr=curr->down;
            }

            if(!found)
            {
                cout<<endl<<"given node not found";
            }
            
            
        }
    }//end of BFS

    void DFS(string  initial)
    {   cout<<endl<<"DFS is: ";
        stack<string> s;
        vector<string>visited;
        s.push(initial);
        visited.push_back(initial);
        while(true)
        {
            if(!s.empty())
            {
                initial=s.top();
                s.pop();
                cout<<initial<<" - ";
            }
            else
            {
                cout<<endl;
                break;
            }

            node *curr=head;
            bool found=false;
            while(curr!=nullptr)
            {
                if(curr->name==initial)
                {
                    found=true;
                    node *neigh=curr->next;
                    while(neigh!=nullptr)
                    {
                        if(find(visited.begin(),visited.end(),neigh->name)==visited.end())
                        {
                            s.push(neigh->name);
                            visited.push_back(neigh->name);
                        }
                        neigh=neigh->next;
                    }
                    break;
                }
                curr=curr->down;
            }

            if(!found)
            {
                cout<<endl<<"Given node not found";
            }
        }
    }//end of DFS

    void printIndegree()
    {
        node *curr=head;
        while(curr!=nullptr)
        {
            node *temp=head;
            int count=0;
            while(temp!=nullptr)
            {
                node *neigh=temp->next;
                while(neigh!=nullptr)
                {
                    if(neigh->name==curr->name)
                    {
                        count++;
                        
                    }
                    neigh=neigh->next;
                    
                }
                temp=temp->down;
            }
            cout<<endl<<"In degree of "<<curr->name<<": "<<count;
            curr=curr->down;
        }
    }

    void printOutdegree()
    {
        node *curr=head;
        while(curr!=nullptr)
        {
            int count=0;
            node *neigh=curr->next;
            while(neigh!=nullptr)
            {
                
                
                count++;
                
                neigh=neigh->next;
            }
            cout<<endl<<"Out degree of "<<curr->name<<" : "<<count;
            curr=curr->down;
        }
    }
};

int main() {
    Graph g ; 
    g.addNode( "Katraj" , "PICT" ) ;
    g.addNode( "Bharti" , "Katraj" ) ; 
    g.addNode( "Bharti" , "PICT" ) ;
    g.addNode( "Katraj" , "SKNCOE" ) ; 
    g.addNode( "PICT" , "SKNCOE" ) ;
    g.addNode( "SKNCOE" , "Temple" ) ; 
    g.addNode( "Temple" , "Katraj" ) ; 
    g.addNode( "Temple" , "Kondwa" ) ; 
    g.display() ; 
    g.printIndegree();
    g.printOutdegree();
    g.BFS( "Katraj" ) ; 
    g.DFS( "Katraj" ) ;
    return 0;
}
