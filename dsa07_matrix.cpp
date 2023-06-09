# include <iostream>
using namespace std;

class Graph
{
    int **adjmatrix;
    int dist,v,e;
public:
    int inf=99999;

    Graph()
    {
        v=0;e=0;
        
    }
    void input()
    {
        cout<<endl<<"Enter number of vertices: ";cin>>v;
        adjmatrix=new int*[v];
        cout<<endl<<"ENter number of edges: ";cin>>e;
        for(int i=0;i<v;i++)
        {
            adjmatrix[i]=new int[v];
            for(int j=0;j<v;j++)
            {
                adjmatrix[i][j]=0;
            }
        }
        for(int i=0;i<e;i++)
        {   int s,d,w;
            cout<<endl<<"src vertex: ";cin>>s;
            cout<<"\ndest vertex: ";cin>>d;
            cout<<"\ndistance: ";cin>>w;
            insert(s,d,w);
        }
        for(int i=0;i<v;i++)
        {
            for(int j=0;j<v;j++)
            {
                if(adjmatrix[i][j]==0)
                {
                    adjmatrix[i][j]=inf;
                }
            }
        }
        
    }
        void insert(int s,int d,int w)
        {
            adjmatrix[s][d]=w;
            adjmatrix[d][s]=w;
        }

        void prims()
        {
            int n=v;int i,j;
            int no_edges=0;
            int cost=0;
            bool selected[n];
            selected[0]=1;

            int x,y;
            while(no_edges<n-1)
            {
                int min=9999;           //IMP DECLARE HERE
                for(i=0;i<n;i++)
                {
                    for(j=0;j<n;j++)
                    {
                        if(i!=j && !selected[j])
                        {
                            if(adjmatrix[i][j]<min)
                            {
                                min=adjmatrix[i][j];
                                x=i;
                                y=j;
                            }
                        }
                        
                    }
                }
                no_edges++;
                cost+=adjmatrix[x][y];
                selected[y]=1;
            }
            cout<<endl<<"Cost: "<<cost;



        }   
};

int main()
{
    Graph g;
    g.input();
    g.prims();
}
