#include <iostream>
#include<windows.h>
#include<mysql.h>
#include <sstream>
#include<stdio.h>
#define ipadd "192.168.162.48"
using namespace std;

bool dbconn();
void addrec();
void editrec();
void findmed();
void view();

int main()
{
    int runforever = 1;
    int ans;

    while(runforever == 1){

        cout << endl << endl << "---------------" << endl << endl << "1. Add  Record" << endl << "2. Edit  Record" << endl << "3. Find " << endl << "4. View " << endl << "5. End" << endl << endl << endl << "---------------" << endl;

        cout << endl << "Your Answer : ";

        cin >> ans;

        switch(ans){
        case 1:
            addrec();
            break;
        case 2:
            editrec();
            break;
        case 3:
            findmed();
            break;
        case 4:
            view();
            break;
        case 5:
            runforever = 0;
            break;
        }
    }

    return 0;
}



void addrec(){
    string dummy;
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, ipadd, "ronak", "ronak", "atm", 0, NULL, 0);
    if(conn){
        int time,qstate = 0, quantity;
        string name, location;

        cout << "Enter time : ";
        cin >> time;
//check for opertaion//continue only if the op is possible//add a check condition

        char  operation;
        cout << "Arrival/Depature (A/D) : ";
        cin >> operation;
        //check if the entered value is A or D
        string airline;
        cout << "Enter the airline : ";
        cin >> airline;
        string aircraft;
        cout << "Enter the type aircraft : ";
        //add the options that gives ooptions for type of aircraft//
        cin >>aircraft;
        int passengers;
        cout << "Enter No. of passengers : ";
        cin >> passengers;
        stringstream ss;
        ss << "INSERT INTO ATM(time,operation, airline,aircraft,passengers) VALUES('"<<time<<"','"<<operation<<"','"<< airline<<"','"<<aircraft<<"','"<<passengers<<"')";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record Inserted..." << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
        cin >> dummy;
    }

    system("pause");
    system("cls");

}

void editrec(){  //edit the rec based in airline an dthe time//
    string dummy;
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, ipadd, "ronak", "ronak", "atm", 0, NULL, 0);
    if(conn){
        int qstate = 0;
        string name;
        int time,prevtime;
        cout << "Enter Name of airline: ";
        cin >> name;
        cout << "Enter prevtime : ";
        cin >> prevtime;
        //check if the data exsist //
        cout<<"Enter the new time:";
        cin>>time;
        //check if the time is possible//

        stringstream ss;
        ss << "UPDATE atm SET time =  " << time << " WHERE airline= '" << name << "' and time='"<<prevtime<<"'";

        string query = ss.str();

        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record Updated..." << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
        cin >> dummy;
    }

    system("pause");
    system("cls");

}

void findmed(){//need to write a prog that return false when the returned rows are null//eg:use count(*)//
    string dummy;
    MYSQL* conn;
    MYSQL* conn2;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, ipadd, "ronak", "ronak", "atm", 0, NULL, 0);

    if(conn){

        string name;
        int quantity;
        cout << "Enter Name : ";
        cin >> name;
        cout << "Enter Quantity : ";
        cin >> quantity;


        int qstate1 = 0;

        stringstream ss1;
      //  ss1 << "UPDATE inventory SET quantity = quantity - " << quantity << " WHERE name = '" << name << "'";

        string query1 = ss1.str();

        const char* q1 = query1.c_str();
        qstate1 = mysql_query(conn, q1);
        if(qstate1 == 0){
            cout << "Record Updated..." << endl;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
        }

    }

    cout << "Press B to go back";
    cin >> dummy;

    system("pause");
    system("cls");
}

void view(){
    string dummy;
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, ipadd, "ronak", "ronak", "atm", 0, NULL, 0);
    if(conn){
        int qstate = mysql_query(conn, "SELECT time,operation, airline,aircraft,passengers FROM atm");

        if(!qstate){
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res)){
                cout << row[0] <<"\t | \t" << row[1] <<"\t | \t" << row[2] <<"\t | \t" << row[3] << endl << endl;
             }
        }
    }

    cout << "Press B to go back";
    cin >> dummy;

    system("pause");
    system("cls");
}
