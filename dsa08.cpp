#include<iostream>
#define max 10
using namespace std;

class node
{
    int key;
    node *left,*right;
public:
    node ()
    {
        key=0;
        left=right=nullptr;
    }
    node (int k)
    {
        key=k;
        left=right=nullptr;
    }

    friend class OBST;
};

class OBST
{
    node *root;
    double W[max][max];
    double C[max][max];
    int R[max][max];
    int keys[max];
    double p[max],q[max];
    int n;

public:
    OBST()
    {
        root=nullptr;
    }

    void input()
    {
        cout<<endl<<"Enter number of keys: ";
        cin>>n;

        for(int i=1;i<=n;i++)
        {
            cout<<endl<<"Enter key: ";
            cin>>keys[i];
            cout<<endl<<"Enter probability: ";
            cin>>p[i];
        }
        for(int i=0;i<n;i++)
        {
            cout<<endl<<("Enter q {%d}",i)<<": ";
            cin>>q[i];
        }
    }

    node* create_obst(int i,int j)
    {
        node *p;
        if(i==j)
        {
            p=nullptr;
            return p;
        }
        else
        {
            p=new node();
            p->key=keys[R[i][j]];
            p->left=create_obst(i,R[i][j]-1);       //IMP R[I][J]  -1
            p->right=create_obst(R[i][j],j);
            return p;
        }
    }

    void display(node *temp,int nivel)
    {
        if(temp==nullptr)
        {
            return ;
        }
        else
        {
            display(temp->left,nivel+1);
            cout<<temp->key<<"  ";
            display(temp->right,nivel+1);
        }
    }

    void calc_WCR()
    {
        int i,j,k,h,m;
        double min,x;

        for(i=0;i<=n;i++)
        {
            W[i][i]=q[i];
            for(j=i+1;j<=n;j++)
            {
                W[i][j]=W[i][j-1]+ p[j]+q[j];
            }
            C[i][i]=W[i][i];
        }
        for(i=0;i<n;i++)
        {
            j=i+1;
            C[i][j]=C[i][i]+C[j][j]+W[i][j];
            R[i][j]=j;
        }

        for(h=2;h<=n;h++)
        {
            for(i=0;i<=n-h;i++)
            {
                j=i+h;
                m=R[i][j-1];
                min=C[i][m-1]+C[m][j];
                for(k=m+1;k<=R[i+1][j];k++)         //IMP RANGE OF K
                {
                    x=C[i][k-1]+C[k][j];
                    if(x<min)
                    {
                        m=k;
                        min=x;
                    }
                }
                C[i][j]=W[i][j]+min;
                R[i][j]=m;

            }
        }

        cout<<("\nThe Weight matrix R:\n");
		for (i = 0; i <= n; i++)
		{
			for (j = i; j <= n; j++)
				cout << W[i][j] << " ";
			cout << "\n";
		}
        cout<<("\nThe Cost matrix R:\n");
		for (i = 0; i <= n; i++)
		{
			for (j = i; j <= n; j++)
				cout << C[i][j] << " ";
			cout << "\n";
		}
        cout<<("\nThe root matrix R:\n");
		for (i = 0; i <= n; i++)
		{
			for (j = i+1; j <= n; j++)
				cout << R[i][j] << " ";
			cout << "\n";
		}
    }

    void obst()
    {
        calc_WCR();

        
		cout << "C[0] = " << C[0][n] << " W[0] = " << W[0][n] << endl;


		cout << "The Least cost is: \n"
			 << C[0][n]<<endl;
		root = create_obst(0, n);  // Construct the optimal binary search tree using the root matrix R
    }

    node *get()
	{
		return root;
	}
    
};



int main()
{
	int k;

	OBST tree;

	while (true)
	{
		cout << "1.Construct tree\n2.Display tree\n3.Exit\n";
		cin >> k;
		switch (k)
		{
		case 1:
		    tree.input();  // Input the number of keys, their access probabilities, and dummy key access probabilities
			tree.obst();  // Calculate the optimal binary search tree and construct it
			break;
		case 2:
			tree.display(tree.get(), 0);  // Display the constructed tree
			break;
		}
		if(k==3)
			break;
	}
	return 0;
}
