#include<iostream>
#include<string.h>
#include<fstream>
#include<conio.h>
#include<cstdio>
#include<stdlib.h>


#define max 100
using namespace std;

struct r{
    char dish[50];
    int key;
    float price;
}r;
class Resturant
{
public:
    void create();
    void query();
    void display();
    void update();
    void delet();
    void admin();
};
void Resturant::create()
{
    char a;
    int k;
    fstream obj;
    top:
    do {
        obj.open("resturant.txt",ios::in|ios::binary);
        cout<<"enter the dish key:";
        cin>>k;
         while(obj.read((char*)&r,sizeof(r)))
            {
                if(r.key==k)
                {
                    cout<<"key is already exist"<<endl;
                    obj.close();
                goto top;
                }
            }
        obj.close();
        obj.open("resturant.txt",ios::app|ios::binary);
        r.key=k;
        cin.ignore();
        cout<<"ENTER THE DISH NAME:";
        gets(r.dish);
        cout<<"ENTER THE DISH PRICE:";
        cin>>r.price;
        obj.write((char*)&r,sizeof(r));
        cout<<"do you want to add an other [y/n]:";
        cin>>a;
        obj.close();
    }
    while(a!='n');
}
void Resturant::display()
{
      int c=0;
     fstream obj;
     obj.open("resturant.txt",ios::in|ios::binary);
    cout<<"\tKey\t\tDISH NAME\t\tPRICE"<<endl;
    while(obj.read((char*)&r,sizeof(r)))
    {
            cout<<"\t"<<r.key<<"\t\t"<<r.dish<<"\t\t\t"<<r.price<<endl;
            c++;
    }
    if(c==0)
    {
        cout<<"list is empty"<<endl;
    }
    obj.close();
}
void Resturant::query()
{
     int a,c=0;
     fstream obj;
     obj.open("resturant.txt",ios::in);
    cout<<"enter the dish key:";
    cin>>a;
    while(obj.read((char*)&r,sizeof(r)))
    {
           if(r.key==a)
           {
            cout<<"\t"<<r.key<<"\t\t"<<r.dish<<"\t\t\t"<<r.price<<endl;
            c++;
           }
    }
    if(c==0)
    {
        cout<<"not found"<<endl;
    }
    obj.close();
}
void Resturant::update()
{
     int a,p,c=0;
     fstream obj;
     obj.open("resturant.txt",ios::in|ios::out|ios::binary);
    cout<<"enter the dish key:";
    cin>>a;
    obj.seekg(0);
    while(obj.read((char*)&r,sizeof(r)))
    {
        if(r.key==a)
        {
            cout<<"destinatio record:"<<endl;
            cout<<"\t"<<r.key<<"\t\t"<<r.dish<<"\t\t\t"<<r.price<<endl;
            p=obj.tellg()-(sizeof(r));
            obj.seekp(p);
            cout<<"enter the dish key:";
            cin>>r.key;
            cin.ignore();
            cout<<"ENTER THE DISH NAME:";
             gets(r.dish);
            cout<<"ENTER THE DISH PRICE:";
            cin>>r.price;
            obj.write((char*)&r,sizeof(r));
            c++;
           }

        }
        if(c==0)
        {
            cout<<"not found"<<endl;
        }

    obj.close();
}
void Resturant::delet()
{
     int a,c;
     fstream obj,obj1;
     obj.open("resturant.txt",ios::in|ios::binary);
     obj1.open("temp.txt",ios::app|ios::binary);
    cout<<"enter the dish key:";
    cin>>a;
    while(obj.read((char*)&r,sizeof(r)))
    {
        if(r.key==a)
        {
            c++;
            cout<<"\t"<<r.key<<"\t\t"<<r.dish<<"\t\t\t"<<r.price<<endl;
            cout<<"destination record is deleted"<<endl;
        }
        if(r.key!=a)
        {
            obj1.write((char*)&r,sizeof(r));
           }
    }
    obj.close();
    obj1.close();
    if(c==0)
       {
         cout<<"not found"<<endl;
       }
    remove("resturant.txt");
    rename("temp.txt","resturant.txt");
}
 void Resturant::admin()
{
char a;
    do{

            cout<<"\n\t\t\t\t\t\t|||||||||||||||||||||||||"<<endl;
            cout<<"\t\t\t\t\t\t|                       |"<<endl;
            cout<<"\t\t\t\t\t\t|  1) ADD DISH          |"<<endl;
            cout<<"\t\t\t\t\t\t|  2) Display           |"<<endl;
            cout<<"\t\t\t\t\t\t|  3) QUERY             |"<<endl;
            cout<<"\t\t\t\t\t\t|  4) UPDATE            |"<<endl;
            cout<<"\t\t\t\t\t\t|  5) DELETE            |"<<endl;
            cout<<"\t\t\t\t\t\t|  0) EXIT TO MAIN MANU |"<<endl;
            cout<<"\t\t\t\t\t\t|                       |"<<endl;
            cout<<"\t\t\t\t\t\t|||||||||||||||||||||||||"<<endl;
            cout<<"\t\t\t\t\t\tselect the key";
            cin>>a;
            switch(a)
            {
            case '0':
                break;
            case '1':
                system("CLS");
               create();
                break;
            case '2':
                system("CLS");
               display();
                break;
            case '3':
                system("CLS");
               query();
                break;
            case '4':
                system("CLS");
               update();
                break;
            case '5':
                system("CLS");
             delet();
                break;
            }
    }
    while(a!='0');
}
struct {
char d[50];
float p,amount;
int qty;
}rd;
class custmer:public Resturant
{
public:
    void bill();
    void showbill();
    void dish_menu();
};
void custmer::bill()
{
     int a,c=0;
     char ch;
     float total=0;
    fstream obj,obj1;
    dish_menu();
    obj1.open("bill.txt",ios::out|ios::binary);
     do{
    obj.open("resturant.txt",ios::in|ios::binary);
    cout<<"enter the dish key:";
    cin>>a;
    while(obj.read((char*)&r,sizeof(r)))
    {
           if(r.key==a)
           {
            c++;
            cout<<"enter the quantity:";
            cin>>rd.qty;
            rd.amount=rd.qty*r.price;
            cout<<"\t"<<r.dish<<"\t\t"<<r.price<<"*"<<rd.qty<<"\t\t"<<rd.amount<<endl;
            strcpy(rd.d,r.dish);
            rd.p=r.price;
            obj1.write((char*)&rd,sizeof(rd));
            total=total+rd.amount;
           }
        }
        if(c==0)
     {
        cout<<"not found"<<endl;
     }

    cout<<"do you want to order more [y/n]";
    cin>>ch;
    obj.close();
     }
     while(ch!='n');
    obj1.close();
    cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout<<"|||||||||||||||||||||||||||||||||||||||||||||||| BILL  |||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
     cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
    showbill();
    cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout<<"|||\t\t\t\t\t\t\t   TOTAL="<<total<<"\t\t\t\t\t   |||"<<endl;
    cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
}
 void custmer::showbill(){
    fstream obj;
    obj.open("bill.txt",ios::in|ios::binary);
    cout<<"\tDISH NAME\t\tPRICE\t\tQTY\t\tAMOUNT"<<endl;
    while(obj.read((char*)&rd,sizeof(rd)))
    {

            cout<<"\t"<<rd.d<<"\t\t\t"<<rd.p<<"\t\t"<<rd.qty<<"\t\t"<<rd.amount<<endl;


    }
    obj.close();
 }
 void custmer::dish_menu()
 {
      fstream obj;
     obj.open("resturant.txt",ios::in|ios::binary);
    while(obj.read((char*)&r,sizeof(r)))
    {


            cout<<"\t\t"<<r.key<<") "<<r.dish<<"-------RS  "<<r.price<<endl;
    }
    obj.close();
 }



//Class Customer
class Customer
{
public:
char name[100];
char address[100];
char phone[12];
char from_date[20];
char to_date[20];
float payment_advance;
int booking_id;
};


class Room
{
public:
char type;
char stype;
char ac;
int roomNumber;
int rent;
int status;

class Customer cust;
class Room addRoom(int);
void searchRoom(int);
void deleteRoom(int);
void displayRoom(Room);
};

//Global Declarations
class Room rooms[max];
int count=0;


Room Room::addRoom(int rno)
{
class Room room;
room.roomNumber=rno;
cout<<"\nType AC/Non-AC (A/N) : ";
cin>>room.ac;
cout<<"\nType Comfort (S/N) : ";
cin>>room.type;
cout<<"\nType Size (B/S) : ";
cin>>room.stype;
cout<<"\nDaily Rent : ";
cin>>room.rent;
room.status=0;

cout<<"\n Room Added Successfully!";
getch();
return room;
}


void Room::searchRoom(int rno)
{
int i,found=0;
for(i=0;i<count;i++)
{
if(rooms[i].roomNumber==rno)
{
found=1;
break;
}
}
if(found==1)
{
cout<<"Room Details\n";
if(rooms[i].status==1)
{
cout<<"\nRoom is Reserved";
}
else
{
cout<<"\nRoom is available";
}
displayRoom(rooms[i]);
getch();
}
else
{
cout<<"\nRoom not found";
getch();
}
}

void Room::displayRoom(Room tempRoom)
{
cout<<"\nRoom Number: \t"<<tempRoom.roomNumber;
cout<<"\nType AC/Non-AC (A/N) "<<tempRoom.ac;
cout<<"\nType Comfort (S/N) "<<tempRoom.type;
cout<<"\nType Size (B/S) "<<tempRoom.stype;
cout<<"\nRent: "<<tempRoom.rent;
}

//hotel management class
class HotelMgnt:protected Room
{
public:
void checkIn();
void getAvailRoom();
void searchCustomer(char *);
void checkOut(int);
void guestSummaryReport();
};


void HotelMgnt::guestSummaryReport(){

if(count==0){
	cout<<"\n No Guest in Hotel !!";
}	
for(int i=0;i<count;i++)
{
if(rooms[i].status==1)
{
cout<<"\n Customer First Name : "<<rooms[i].cust.name;
cout<<"\n Room Number : "<<rooms[i].roomNumber;
cout<<"\n Address (only city) : "<<rooms[i].cust.address;
cout<<"\n Phone : "<<rooms[i].cust.phone;
cout<<"\n---------------------------------------";	
}
	
}

getch();
}

//hotel management reservation of room
void HotelMgnt::checkIn()
{
int i,found=0,rno;

class Room room;
cout<<"\nEnter Room number : ";
cin>>rno;
for(i=0;i<count;i++)
{
if(rooms[i].roomNumber==rno)
{
found=1;
break;
}
}
if(found==1)
{
if(rooms[i].status==1)
{
cout<<"\nRoom is already Booked";
getch();
return;
}

cout<<"\nEnter booking id: ";
cin>>rooms[i].cust.booking_id;

cout<<"\nEnter Customer Name (First Name): ";
cin>>rooms[i].cust.name;

cout<<"\nEnter Address (only city): ";
cin>>rooms[i].cust.address;

cout<<"\nEnter Phone: ";
cin>>rooms[i].cust.phone;

cout<<"\nEnter From Date: ";
cin>>rooms[i].cust.from_date;

cout<<"\nEnter to  Date: ";
cin>>rooms[i].cust.to_date;


cout<<"\nEnter Advance Payment: ";
cin>>rooms[i].cust.payment_advance;

rooms[i].status=1;

cout<<"\n Customer Checked-in Successfully..";
getch();
}
}


//hotel management shows available rooms
void HotelMgnt::getAvailRoom()
{
int i,found=0;
for(i=0;i<count;i++)
{
if(rooms[i].status==0)
{
displayRoom(rooms[i]);
cout<<"\n\nPress enter for next room";
found=1;
getch();
}
}
if(found==0)
{
cout<<"\nAll rooms are reserved";
getch();
}
}


//hotel management shows all persons that have booked room
void HotelMgnt::searchCustomer(char *pname)
{
int i,found=0;
for(i=0;i<count;i++)
{
if(rooms[i].status==1 && stricmp(rooms[i].cust.name,pname)==0)
{
cout<<"\nCustomer Name: "<<rooms[i].cust.name;
cout<<"\nRoom Number: "<<rooms[i].roomNumber;

cout<<"\n\nPress enter for next record";
found=1;
getch();
}
}
if(found==0)
{
cout<<"\nPerson not found.";
getch();
}
}


//hotel managemt generates the bill of the expenses
void HotelMgnt::checkOut(int roomNum)
{
int i,found=0,days,rno;
float billAmount=0;
for(i=0;i<count;i++)
{
if(rooms[i].status==1 && rooms[i].roomNumber==roomNum)
{
//rno = rooms[i].roomNumber;
found=1;
//getch();
break;
}
}
if(found==1)
{
cout<<"\nEnter Number of Days:\t";
cin>>days;
billAmount=days * rooms[i].rent;

cout<<"\n\t######## CheckOut Details ########\n";
cout<<"\nCustomer Name : "<<rooms[i].cust.name;
cout<<"\nRoom Number : "<<rooms[i].roomNumber;
cout<<"\nAddress : "<<rooms[i].cust.address;
cout<<"\nPhone : "<<rooms[i].cust.phone;
cout<<"\nTotal Amount Due : "<<billAmount<<" /";
cout<<"\nAdvance Paid: "<<rooms[i].cust.payment_advance<<" /";
cout<<"\n*** Total Payable: "<<billAmount-rooms[i].cust.payment_advance<<"/ only";

rooms[i].status=0;
}
getch();
}


//managing rooms (adding and searching available rooms)
void manageRooms()
{
class Room room;
int opt,rno,i,flag=0;
char ch;
do
{
system("cls");
cout<<"\n### Manage Rooms ###";
cout<<"\n1. Add Room";
cout<<"\n2. Search Room";
cout<<"\n3. Back to Main Menu";
cout<<"\n\nEnter Option: ";
cin>>opt;


//switch statement
switch(opt)
{
case 1:
cout<<"\nEnter Room Number: ";
cin>>rno;
i=0;
for(i=0;i<count;i++)
{
if(rooms[i].roomNumber==rno)
{
flag=1;
}
}
if(flag==1)
{
cout<<"\nRoom Number is Present.\nPlease enter unique Number";
flag=0;
getch();
}
else
{
rooms[count]=room.addRoom(rno);
count++;
}
break;
case 2:
cout<<"\nEnter room number: ";
cin>>rno;
room.searchRoom(rno);
break;
case 3:
//nothing to do
break;
default:
cout<<"\nPlease Enter correct option";
break;
}
}while(opt!=3);
}
using namespace std;

int main()
{
int choice=1 ;
int change;

while(choice) {
		
cout<<"Enter where you want to go press 1 for hotel press 2 for restrurant \n"	;
cin>>change;

if(change==1){
	class HotelMgnt hm;
int i,j,opt,rno;
char ch;
char pname[100];

system("cls");

do
{
system("cls");
cout<<"######## Hotel Management #########\n";
cout<<"\n1. Manage Rooms";
cout<<"\n2. Check-In Room";
cout<<"\n3. Available Rooms";
cout<<"\n4. Search Customer";
cout<<"\n5. Check-Out Room";
cout<<"\n6. Guest Summary Report";
cout<<"\n7. Exit";
cout<<"\n\nEnter Option: ";
cin>>opt;
switch(opt)
{
case 1:
manageRooms();
break;
case 2:
if(count==0)
{
cout<<"\nRooms data is not available.\nPlease add the rooms first.";
getch();
}
else
hm.checkIn();
break;
case 3:
if(count==0)
{
cout<<"\nRooms data is not available.\nPlease add the rooms first.";
getch();
}
else
hm.getAvailRoom();
break;
case 4:
if(count==0)
{
cout<<"\nRooms are not available.\nPlease add the rooms first.";
getch();
}
else
{
cout<<"Enter Customer Name: ";
cin>>pname;
hm.searchCustomer(pname);
}
break;
case 5:
if(count==0)
{
cout<<"\nRooms are not available.\nPlease add the rooms first.";
getch();
}
else
{
cout<<"Enter Room Number : ";
cin>>rno;
hm.checkOut(rno);
}
break;
case 6:
hm.guestSummaryReport();	
break;
case 7:
cout<<"\nTHANK YOU! FOR USING SOFTWARE \n";
break;
default:
cout<<"\nPlease Enter correct option";
break;
}
}while(opt!=7);

getch();
}

else {
	char a;
    custmer obj;
    do
    {
        cout<<"\n\t\t\t\t\t\t||||||||||||||||||||"<<endl;
        cout<<"\t\t\t\t\t\t|                  |"<<endl;
        cout<<"\t\t\t\t\t\t|    1)Admin       |"<<endl;
        cout<<"\t\t\t\t\t\t|    2)custmer     |"<<endl;
        cout<<"\t\t\t\t\t\t|    0)Exit        |"<<endl;
        cout<<"\t\t\t\t\t\t|                  |"<<endl;
        cout<<"\t\t\t\t\t\t||||||||||||||||||||"<<endl;
        cout<<"\t\t\t\t\t\tselect the manu";
        cin>>a;
        switch(a)
        {
        case '0':
            break;
        case '1':
             system("CLS");
            obj.admin();
            break;
        case '2':
             system("CLS");
            obj.bill();
            break;
        }
    }
    while(a!='0');
}

cout<<"Do you want to continue press 1 else press 0 \n ";
cin>>choice;
}

getch();
}
