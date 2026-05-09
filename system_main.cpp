#include<iostream>
#include "hospital_Management .h"
using namespace std;
    int main(){ 
    HospitalSystem sys;
    sys.load();
 
    int choice;
    bool running = true;
 
    while(running){
     cout << "\n-------------------\n";
        cout << "1. Add\n";
        cout << "2. Edit\n";
        cout << "3. Delete Patient\n";
        cout << "4. Delete Doctor\n";
        cout << "5. Search Patient\n";
        cout << "6. Search Doctor\n";
        cout << "7. Show All Patients\n";
        cout << "8. Show All Doctors\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
 
        switch(choice){
        case 1: sys.add();               break;
            case 2: sys.edit();              break;
            case 3: sys.removePerson('P');   break;
            case 4: sys.removePerson('D');   break;
            case 5: sys.search('P');         break;
            case 6: sys.search('D');         break;
            case 7: sys.displayByType('P');  break;
            case 8: sys.displayByType('D');  break;
            case 0: running = false;         break;
            default: cout << "Invalid choice!\n";
        }
    }
 
    return 0;
}