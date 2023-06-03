#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class node
{
    char name;
    int cost;
    node *next,*down;
public:
    node()
    {

    }
    node(char name,int cost)
    {
        this->name=name;
        this->cost=cost;
        next=down=nullptr;
    }

    friend class Graph;
};

//edge class
class Edge
{
    char v1,v2;
    int weight;
public:
    Edge()
    {

    }
    Edge(char v1,char v2,int w)
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
    Graph()
    {
        node1=new node('A',0);
        node2=new node('B',0);
        node3=new node('C',0);
        node4=new node('D',0);
        node5=new node('E',0);

        node1->down=node2;
        node2->down=node3;
        node3->down=node4;
        node4->down=node5;
    }

    void insert(char parentName,char adjname,int cost)
    {
        node*parent=node1;
        while(parent!=nullptr)
        {
            if(parent->name==parentName)
            {
                break;
            }
            else
            {
                parent=parent->down;
            }
        }//got the parent node

        node *previous=nullptr;
        node *curr=parent;
        node *newNode=new node(adjname,cost);

        while(curr!=nullptr)
        {
            previous=curr;
            curr=curr->next;
        } //reached end of parent adjacency list to insert new item
        //previous holds the last node in parents list

        previous->next=newNode;
        cout<<endl<<"Insertion Successful";
    }//end of INSERT

    void display()
    {
        node *parent=node1;
        while(parent!=nullptr)
        {   
            cout<<endl<<parent->name<<" : ";
            node *curr=parent->next;
            while(curr!=nullptr)
            {
                cout<<curr->name<<("%d",curr->cost)<<" - ";
                curr=curr->next;
            }
            cout<<"null";

            parent=parent->down;
        }
    }//end of DISPLAY

    void primsAlgo(char initial)
    {
        vector<char> visited;
        int mstc=0;
        visited.push_back(initial);
        //size increases one by one and while end when it reaches 5 ie all nodes are visited
        while(visited.size()<5)
        {
            int min_cost=1000;
            Edge minEdge;
            for(char visitedNode:visited)
            {   
                node *curr=node1;
                while(curr!=nullptr)
                {
                    if(curr->name==visitedNode)
                    {
                        node *neighbour=curr->next;
                        while(neighbour!=nullptr)
                        {
                            if(std::find(visited.begin(),visited.end(),neighbour->name)==visited.end())     //requires include algorithm
                            {
                                //neighbour not present in visited
                                if(neighbour->cost<min_cost)
                                {
                                    minEdge.v1=curr->name;
                                    minEdge.v2=neighbour->name;
                                    minEdge.weight=neighbour->cost;
                                    min_cost=minEdge.weight;
                                }
                            }
                            neighbour=neighbour->next;
                        }
                    }
                    break;
                }
                curr=curr->down;

            }//end of for

            cout<<endl<<"Edge added: "<<minEdge.v1<<"-"<<minEdge.v2<<" of cost : "<<minEdge.weight;
            mstc+=minEdge.weight;
            visited.push_back(minEdge.v2);
        }//end of main while

        cout<<endl<<"Minimun Spanning Tree Cost is:  "<<mstc;

    }//end of PRIMS


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
    g.primsAlgo('A');
    

    return 0;
}
