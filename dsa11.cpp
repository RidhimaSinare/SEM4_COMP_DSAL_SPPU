#include<bits/stdc++.h>
using namespace std;

class Student
{
    char name[10];
    int roll_no;
public:
    Student()
    {
        name[0]='\0';
        roll_no-1;
    }
    void getData()  //input
    {
        cout<<"\nEnter Student Data"<<endl;
        cout<<"\nName: ";
        cin>>name;
        cout<<"\nRoll Number: ";
        cin>>roll_no;
    }

    void putData()//print
    {
        cout<<endl<<name<<"\t"<<roll_no;
    }

    int returnRoll()
    {
        return roll_no;
    }
};

class Seq_File
{
    char file_name[15];

public:

    Seq_File()
    {
        ofstream file("Student.txt");
        strcpy(file_name,"Student.txt");

        if(file)
        {
            cout<<"\nFile opened successfully";
            file.close();
        }
        else{cout<<"\nFile creation error";}
    }

    Seq_File(char F[])
    {
        ofstream file;
        strcpy(file_name,F);

        file.open(file_name);
        
        if(file)
        {
            cout<<"\nFile opened successfully";
            file.close();
        }
        else{cout<<"\nFile creation error";}

    }
    void create()
    {
        ofstream file;
        Student s;
        file.open(file_name);
        s.getData();
        file.write(reinterpret_cast<char*>(&s),sizeof(s));
        file.close();
    }

    void display()
    {
        ifstream file;
        file.open(file_name);
        Student s;
        file.read(reinterpret_cast<char*>(&s),sizeof(s));
        while (!file.eof())
        {
            
        s.putData();
        file.read(reinterpret_cast<char*>(&s),sizeof(s));

        }
        
        file.close();
    }

    void add() //adding in existing using app
    {
        ofstream file;
        file.open(file_name,ios::app);
        Student s;
        s.getData();
        file.write(reinterpret_cast<char*>(&s),sizeof(s));
        file.close();

    }

    void Remove(int roll)
    {
        ifstream file;
        ofstream temp;
        file.open(file_name);
        temp.open("temp.txt");
        Student s;
        int flag=0;
        file.read(reinterpret_cast<char*>(&s),sizeof(s));
        while(!file.eof())
        {
            if(s.returnRoll()==roll)
            {
                s.putData();
                flag=1;
            }
            else
            {
                temp.write(reinterpret_cast<char*>(&s),sizeof(s));

            }
            file.read(reinterpret_cast<char*>(&s),sizeof(s));
        }//end of while

        if(flag==0)
        {
            cout<<endl<<"roll number does not exist";
        }
        file.close();
        temp.close();
        remove(file_name);
        rename("temp.txt",file_name);
    }

    void Modify(int roll)
    {
        ifstream file;
        ofstream temp;
        Student s;
        int flag=0;
        file.open(file_name);
        temp.open("temp.txt");
        file.read(reinterpret_cast<char*>(&s),sizeof(s));
        while(!file.eof())
        {
            if(s.returnRoll()==roll)
            {
                s.putData();
                flag=1;
                cout<<endl<<"Enter modified data: ";
                s.getData();
                //temp.write(reinterpret_cast<char*>(&s),sizeof(s));

            }
            
            temp.write(reinterpret_cast<char*>(&s),sizeof(s));
            file.read(reinterpret_cast<char*>(&s),sizeof(s));
        }//end of while
            if(flag==0)
            {
                cout<<endl<<"roll num not present";
            }
            file.close();
            temp.close();
            remove(file_name);
            rename("temp.txt",file_name);
        
    }

};
	
int main() {
	int Choice;
	char F[15];
	int R;
	cout<<"\nEnter File Name : ";
	cin>>F;
	Seq_File  sFile(F);

	do {
	cout<<"\n1: Create Database\n2: Display Database\n3: Add a record\n4: Delete a record\n5: Modify a record\nEnter your choice: ";
		cin>>Choice;

		switch( Choice ) {
				
		case 1:
			sFile.create();
			break;
				
		case 2:               		                
			sFile.display();
			break;
				
		case 3:
			sFile.add();
			break;
				
		case 4:
			cout<<"\nEnter Roll No to delete";
			cin>>R;
			sFile.Remove( R );
			break;
				
		case 5:                                                                
			cout<<"\nEnter Roll No to Modify";
			cin>>R;
			sFile.Modify( R);
			break;
		}
    }

    while(Choice<6);	            
 	cout<<"\n";
   	return 1;
}