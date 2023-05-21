#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class node
{
    char name;int cost;
    node *next,*down;
    public:
    node(char charac,int data)
    {
        this->name=charac;
        this->cost=data;
        this->next=nullptr;
        this->down=nullptr;
    }
    friend class Graph;
};

class Edge
{   char v1,v2;
    int weight;
    public:
    Edge()
    {

    }
    Edge(char v1, char v2,int w)
    {
        this->v1=v1;
        this->v2=v2;
        this->weight=w;
    }
    friend class Graph;

};

class Graph
{
    node *node1,*node2,*node3,*node4,*node5;
    public:
    Graph(){
        this -> node1 = new node('A',0);
        this -> node2 = new node('B',0);
        this -> node3 = new node('C',0);
        this -> node4 = new node('D',0);
        this -> node5 = new node('E',0);

        this -> node1 -> down = this -> node2;
        this -> node2 -> down = this -> node3;
        this -> node3 -> down = this -> node4;
        this -> node4 -> down = this -> node5;
    }

    void insert(char parentName,char adjacentName,int value)
    {
        node *parent=node1;
        while(parent!=nullptr)
        {
            if(parent->name==parentName)
            {
                break;
            }
            else
                parent=parent->down;
        }

        node *previous=nullptr;
        node *curr=parent;
        node *newNode=new node(adjacentName,value);

        while(curr!=nullptr)
        {
            previous=curr;
            curr=curr->next;
        }

        previous->next=newNode;
    }

    void display()
    {
        node *parent=node1;
        while(parent!=nullptr)
        {
            node *curr=parent;
            cout<<endl<<curr->name<<"  ";

            curr=curr->next;   
            while(curr!=nullptr)
            {
                cout<<curr->name<<"  "<<curr->cost<<" - ";
                curr=curr->next;
            }
            cout<<"null";

            parent=parent->down;
        }
    }

    void primsAlgo(char initial)
    {
        vector<char>visited;
        int min_span_tree_cost=0;
        visited.push_back(initial);
        //while all nodes are visited
        while(visited.size()<5)
        {
            int min_cost=1000;
            Edge mincostedge;
            for(char visitedNode:visited)
            {
                node *curr=node1;
                while(curr!=nullptr)
                {
                    if(curr->name==visitedNode)
                    {
                        node *neighbor=curr->next;
                        while(neighbor!=nullptr)
                        {
                            if(std::find(visited.begin(),visited.end(),neighbor->name)==visited.end())
                            {
                                //neighbor not visited
                                if(neighbor->cost<min_cost)
                                {
                                    mincostedge.v1=curr->name;
                                    mincostedge.v2=neighbor->name;
                                    mincostedge.weight=neighbor->cost;
                                    min_cost=mincostedge.weight;

                                }
                            }
                            neighbor=neighbor->next;
                        }
                        break;
                    }
                    curr=curr->down;
                }
            }//end of for loop
            cout<<endl<<"Edge added: "<<mincostedge.v1<<" - "<<mincostedge.v2<<endl;
            min_span_tree_cost+=mincostedge.weight;
            visited.push_back(mincostedge.v2);
        }//end of main while
        cout<<endl<<"Cost of spanning tree: "<<min_span_tree_cost;
    }//end of prims


};

int main(){
    Graph g;
    g.insert('A','B',4);
    g.insert('A','C',3);
    g.insert('A','D',2);
    g.insert('B','A',4);
    g.insert('B','C',3);
    g.insert('B','E',6);
    g.insert('C','A',3);
    g.insert('C','B',3);
    g.insert('C','D',2);
    g.insert('C','E',5);
    g.insert('D','A',2);
    g.insert('D','C',4);
    g.insert('E','B',6);
    g.insert('E','C',5);

    g.display();
    g.primsAlgo( 'A' ) ; 

    return 0;
}