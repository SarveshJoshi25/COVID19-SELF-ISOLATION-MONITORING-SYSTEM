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
};

void Person :: get_details(){
cout<<"Enter day number: "; cin>>Count_Day;
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
    char location[5];

public:
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
    Calc(){
    }
    void red_zone();
    void addto_file();
    void show_details();
    void Calulate_points();
};

void Calc :: addto_file(){
set_details();
write_health_to_file();
write_symp_to_file();
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
void Calc :: Calulate_points(){
int Points = 0  ;
ifstream FILE(filename);
if(FILE.is_open()){
    while(FILE>>Count_Day>>time>>id>>firstname>>lastname>>gender>>location>>bp_h>>bp_l>>temperature>>pulse_rate>>dry_cough>>running_nose>>short_breath){
  if (bp_h > 120)
        Points++;
  if (bp_l < 60)
        Points++;
  if (temperature > 99.9)
    Points++;
  if (pulse_rate > 100 or pulse_rate < 60)
    Points++;
  if (dry_cough == "Y" or dry_cough == "y")
    Points++;
  if (running_nose == "Y" or running_nose == "y")
    Points++;
  if (short_breath == "Y" or short_breath == "y")
    Points++;
  if (Points > 0 ){
    ofstream File;
    File.open("Critical2.txt", ios::out | ios::app);
        if(File.is_open()){
        File<<"Data For :"<<endl;
        File<<"Name :"<< firstname<< " " << lastname<<endl;
        File<<"Location :"<<location<<endl;
        File<<"ID :"<<id<<endl;
        File<<"Blood Pressure :" << bp_h <<" - " << bp_l << endl ;
        File<<"Temperature :" << temperature<<endl;
        File<<"Pulse Rate :" << pulse_rate<<endl;
        File<<"Dry Cough :" <<dry_cough<<endl;
        File<<"Running Nose :" <<running_nose<<endl;
        File<<"Short Breath:" <<short_breath<<endl;
                         }
                   }
                   }
}
}

int main() {
fstream FILE ;
FILE.open("Critical2.txt",ios::out);
if(!FILE){
    cout<<"FAILED CREATING A FILE."<<endl ;
    return 1;
}
cout<<"Successfully Created Critical File "<< endl ;
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
            int n;
            cout<<"Enter the record number : "<<endl;
            cin >> n;
            obj[n-1]= new Calc();
            break;
            }
         }
         obj[cnt]= new Calc();
         obj[cnt]->Calulate_points();
         cnt++; temp++;
         break;
        }
case 2: cout<<"Enter number of Person's record you want to update (eg. 1,2,3..): ";
        cin>>no;
        if(no<1 || no>cnt)
        {
         cout<<"Enter valid record numbers !"<<endl;
         cout <<"Total registered records are "<<temp<<endl;
         break;
        }
        cout<<"Enter Day number : ";  cin>>obj[no-1]->Count_Day;
        cout<<"Enter time : ";  cin>>obj[no-1]->time;
        obj[no-1]->get_health();
        obj[no-1]->get_symp();
        obj[no-1]->addto_file();
        obj[no-1]->Calulate_points();
        break;
case 3:
        cout<<"Enter number of Person's record you want to see (eg. 1,2,3..): ";
        cin>>no;
        if(no<1 || no>cnt)
        {
         cout<<"Enter valid record number !"<<endl;
         cout <<"Total registered records are "<<temp<<endl;
         break;
        }
        obj[no-1]->show_details();
        break;
case 4: {
        cout<<" Enter the number of the record you want to delete : ";
        cin >>no;
        if(no<1 || no>cnt)
        {
         cout<< "Enter valid record number !"<<endl;
         cout <<"Total registered records are "<<temp<<endl;
         break;
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
        break;
        }
case 5: return 0;
}
cout<<"\nPress any key .."<<endl;
getch();
}
return 0;
}
