#include<iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <stack>

using namespace std;

class Person;
class Regulate;
class Symptoms;
class Calc;

stack<int> arr;
// Class declarations and initializations
class Person{
protected:
char firstname[30],lastname[30],gender[10];
char id[20];
int  age;
public:
    char time[20],filename[20];int Count_Day;
    Person(){
    cout<<"Enter your id :(\'Note: It can't be changed later.\') :";
    cin>>filename;
    strcpy(id,filename);
    strcat(filename,".txt");
    ofstream File(filename);
    get_details();
    set_details();
    }
    void get_details();
    void set_details();
    void Last_Check();
};
void Person :: Last_Check(){
    if(Count_Day >= 14){
        cout << "The Isolation Period of this Patient Has Been Over. \nIf You Find This Patient's Health OK then You can Delete his or her \nRecord On Choosing Delete Record Option in Main Menu." <<endl;
    }
}
void Person :: get_details(){
cout<<"Enter day number: "; cin>>Count_Day;
Last_Check();
cout<<"Enter time      : "; cin>>time;
cout<<"Enter firstname : "; cin>>firstname; firstname[0]=toupper(firstname[0]);
cout<<"Enter lastname  : "; cin>>lastname;   lastname[0]= toupper(lastname[0]);
cout<<"Enter gender    : "; cin>>gender;       gender[0]= toupper(gender[0]);
}

void Person :: set_details(){
ofstream File;
    File.open(filename, ios::out | ios::app);
        if(File.is_open()){
        File<<Count_Day<<endl;
        File<<time<<endl;
        File<<id<<endl;
        File<<firstname<<endl;
        File<<lastname<<endl;
        File<<gender<<endl;
        }
}

class Regulate : virtual public Person{
protected:
    float bp_h,bp_l,temperature,pulse_rate;


public:
    char location[5];
    Regulate(){
    get_health();
    write_health_to_file();
    }
    void get_health();
    void write_health_to_file();
};
void Regulate :: get_health(){
cout<<"Within location boundary? (y/n) : ";  cin>>location;
cout<<"Enter high blood pressure Normal(120-80): "; cin>>bp_h;
cout<<"Enter low Blood Pressure  Normal(90-60) :";cin>> bp_l;
cout<<"Enter temperature.Normal(98.6-99.9) : "; cin>>temperature;
cout<<"Enter pulse_rate.Normal(60-100) : "; cin>>pulse_rate;
}
void Regulate :: write_health_to_file(){
     ofstream File(filename, ios::out | ios::app);
        if( File.is_open() ) {
        File<<location<<endl;
        File<<bp_h<<endl;
        File<<bp_l<<endl;
        File<<temperature<<endl;
        File<<pulse_rate<<endl;
        }
};

class Symptoms : virtual public Person{
protected:
    char dry_cough[5],running_nose[5],short_breath[5];
public:
    Symptoms(){
    get_symp();
    write_symp_to_file();
    }
    void get_symp();
    void write_symp_to_file();
};

void Symptoms :: get_symp(){
cout<<"Enter dry cough      (y/n): "; cin>>dry_cough;
cout<<"Enter running nose   (y/n): "; cin>>running_nose;
cout<<"Enter short breath   (y/n): "; cin>>short_breath;
}

void Symptoms :: write_symp_to_file(){
    ofstream File;
    File.open(filename, ios::out | ios::app);
        if(File.is_open()){
        File<<dry_cough<<endl;
        File<<running_nose<<endl;
        File<<short_breath<<endl;
        }
}

class Calc : public Regulate , public Symptoms{
public:
    int turn=0;int n=0;
    Calc(){
    cout<<"\nRecord created."<<endl;
    }
    void addto_file();
    void show_details();
    void update_critical();
    void display_critical();
    void check_location();
    void show_location();
};

void Calc :: addto_file(){
set_details();
write_health_to_file();
write_symp_to_file();
update_critical();
check_location();
cout<<"\n\'Details updated.\'"<<endl;
}

void Calc :: show_details(){
ifstream File(filename);
if(File.is_open()){
    while(File>>Count_Day>>time>>id>>firstname>>lastname>>gender>>location>>bp_h>>bp_l>>temperature>>pulse_rate>>dry_cough>>running_nose>>short_breath){
    cout<<"The details are as follows : "<<endl;
    cout<<"\n--------\t       Day Number  : " <<Count_Day<<"\t---------"<<endl;
    cout<<"\n--------\tTime when recorded : " <<time<<"\t---------"<<endl;
    cout<<"ID                     : "<<id<<endl;
    cout<<"Firstname              : "<<firstname<<endl;
    cout<<"Lastname               : "<<lastname<<endl;
    cout<<"Gender                 : "<<gender<<endl;
    cout<<"Within Location ?      : "<<location<<endl;
    cout<<"High blood pressure    : "<<bp_h<<endl;
    cout<<"Lower blood pressure   : "<<bp_l<<endl;
    cout<<"Temperature            : "<<temperature<<endl;
    cout<<"Pulse rate             : "<<pulse_rate<<endl;
    cout<<"Dry cough              : "<<dry_cough<<endl;
    cout<<"Running nose           : "<<running_nose<<endl;
    cout<<"Short breath           : "<<short_breath<<endl;
    }
}
else {cout<<"File not open."<<endl;}
}

void Calc :: update_critical(){

ifstream File(filename);
if ( File.is_open()) {
    while(File>>Count_Day>>time>>id>>firstname>>lastname>>gender>>location>>bp_h>>bp_l>>temperature>>pulse_rate>>dry_cough>>running_nose>>short_breath)
        {
        if(n>=turn){
       if(temperature>99.9 || bp_l <60 || bp_l>90 || bp_h <80 || bp_h>120 || pulse_rate<60 || pulse_rate>100
         || dry_cough=="y"|| dry_cough=="Y"  || running_nose=="y" ||running_nose=="Y" || short_breath=="y" || short_breath=="Y")
                {
            ofstream FILE("Critical.txt", ios::out | ios::app);
            FILE<<Count_Day<<endl;
            FILE<<time<<endl;
            FILE<<id<<endl;
            FILE<<firstname<<endl;
            FILE<<lastname<<endl;
            FILE<<gender<<endl;
            FILE<<location<<endl;
            FILE<<bp_h<<endl;
            FILE<<bp_l<<endl;
            FILE<<temperature<<endl;
            FILE<<pulse_rate<<endl;
            FILE<<dry_cough<<endl;
            FILE<<running_nose<<endl;
            FILE<<short_breath<<endl;

                }

        }
            n++;
    }
        n=0;
  }
}

void Calc :: display_critical(){
ifstream File("Critical.txt");
 if(File.is_open()){
    cout<<"\n--------\tThe following people are in critical file  : "<<endl;
    while(File>>Count_Day>>time>>id>>firstname>>lastname>>gender>>location>>bp_h>>bp_l>>temperature>>pulse_rate>>dry_cough>>running_nose>>short_breath){
    cout<<"The details are as follows : "<<endl;
    cout<<"\n--------\t       Day Number  : " <<Count_Day<<"\t---------"<<endl;
    cout<<"\n--------\tTime when recorded : " <<time<<"\t---------"<<endl;
    cout<<"ID                     : "<<id<<endl;
    cout<<"Firstname              : "<<firstname<<endl;
    cout<<"Lastname               : "<<lastname<<endl;
    cout<<"Gender                 : "<<gender<<endl;
    cout<<"Within Location ?      : "<<location<<endl;
    cout<<"High blood pressure    : "<<bp_h<<endl;
    cout<<"Lower blood pressure   : "<<bp_l<<endl;
    cout<<"Temperature            : "<<temperature<<endl;
    cout<<"Pulse rate             : "<<pulse_rate<<endl;
    cout<<"Dry cough              : "<<dry_cough<<endl;
    cout<<"Running nose           : "<<running_nose<<endl;
    cout<<"Short breath           : "<<short_breath<<endl;
    }
}
else {cout<<"Critical file not open."<<endl;}
}

void Calc :: check_location(){

ofstream file;file.open("location.txt",ios::app);
if(strcmp(location,"n")==0){
file<<Count_Day<<endl;
file<<time<<endl;
file<<id<<endl;
file<<firstname<<endl;
file<<lastname<<endl;

}
}

void Calc :: show_location(){
ifstream file("location.txt");
while(file>>Count_Day>>time>>id>>firstname>>lastname){
cout<<"---------------------- The following people were found out of their location. Details are:- ----------------------------"<<endl;
cout<<"ID        : "<<id<<endl;
cout<<"Day no.   : "<<Count_Day<<endl;
cout<<"Time      : "<<time<<endl;
cout<<"Firstname : "<<firstname<<endl;
cout<<"Lastname  : "<<lastname<<endl;
}
}

int main() {
ofstream FILE("Critical.txt", ios::ate);   // If critical exists then truncate, if not exist
ofstream file("location.txt",ios::ate);    //  then create an empty critical file.
int cnt=0; int temp=0;
Calc *obj[100];
while(1){
system("cls");
cout<<"Choose an option :"<<endl;
cout<<"1.Create a new record."<<endl;
cout<<"2.Update a record ( for the system )."<<endl;
cout<<"3.View a record."<<endl;
cout<<"4.Delete record."<<endl;
cout<<"5.Exit"<<endl;
int n=0;int no;
cin>>n;
switch(n){
case 1: {
         if(arr.empty()== false){
            cout<<"Note: Record number/s : ";
            for(int i=0;i<arr.size();i++){
              cout<<arr.top()<<" ";
            }
            cout<<" is/are empty."<<endl;
            cout<<"Do you want to insert in them ? (y/n)"<<endl;
            char a;
            cin>>a;
            if (a='y'){
            int p;
            cout<<"Enter the record number : "<<endl;
            cin >> p;
            obj[p-1]= new Calc();
            obj[p-1]->update_critical();
            break;
            }
         }
         obj[cnt]= new Calc();
         obj[cnt]->check_location();
         obj[cnt]->update_critical();
         cnt++; temp++;
         break;
        }
case 2:
        //
        try{
                cout<<"Enter number of Person's record you want to update (eg. 1,2,3..): ";
                cin>>no;
                if(no<1 || no>cnt)
                {
                 throw 99;
                }
                cout<<"Enter Day number : ";  cin>>obj[no-1]->Count_Day;
                if(obj[no-1]->Count_Day >= 14){
                    cout << "The Isolation Period of this Patient Has Been Over. \nIf You Find This Patient's Health OK then You can Delete his or her \nRecord On Choosing Delete Record Option in Main Menu." <<endl;
                }
                cout<<"Enter time : ";  cin>>obj[no-1]->time;
                obj[no-1]->get_health();
                obj[no-1]->get_symp();
                obj[no-1]->turn++;
                obj[no-1]->addto_file();
                }
    catch(int y){
                cout<<"Enter valid record number !. Error :"<<y<<endl;
                cout <<"Total registered records are "<<temp<<endl;
        }
        //
        break;
case 3: cout << "Press\n1.See individual record.\n2.See critical record.\n3.People out of location"<<endl;
        int k;
        cin>>k;
        switch(k){
        case 1:
      {
        try{
                cout<<"Enter number of Person's record you want to see (eg. 1,2,3..): ";
                cin>>no;
                if(no<1 || no>cnt)
                {
                 throw 99;
                }
                obj[no-1]->show_details();
        }
        catch(int y){
                cout<<"Enter valid record number !. Error :"<<y<<endl;
                cout <<"Total registered records are "<<temp<<endl;
        }
        break;
      }
        case 2:
     {  if(cnt<1)
        {
         cout<<"There are no records in the system !"<<endl;
         break;
        }
        else {
            obj[cnt-1]->display_critical();
        }
        break;
     }
      case 3:{

            obj[cnt-1]->show_location();
            break;
      }
  }
        break;

case 4: { //
            try{
                cout<<" Enter the number of the record you want to delete : ";
                cin >>no;
                if(no<1 || no>cnt)
                {
                 throw 99;
                }
                ofstream File(obj[no-1]->filename);
                char c[20];
                strcpy(c,obj[no-1]->filename);
                File.close();
                delete obj[no-1];
                if( remove(c) != 0 )
                perror( "Error deleting file" );
                else{
                 if (no!=cnt)
                    {arr.push(no);}
                 cout<<"Record number "<<no<<" and file "<<c<<" deleted"<<endl;
                 temp--;
                }
                 if(no==cnt)
                    cnt--;
        }
        catch(int y){
                cout<<"Enter valid record number !. Error :"<<y<<endl;
                cout <<"Total registered records are "<<temp<<endl;
        }
         //
        break;
        }
case 5: return 0;
}
cout<<"\nPress any key .."<<endl;
getch();
}

return 0;
}

