#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;


class person{
public:
    int id;
    string name ;
    string phone ;
    char type;
    person(int id , string name, string phone,char type):id(id),name(name),phone(phone),type(type){}
    virtual void display()=0;
    virtual string serialize()=0;
    virtual ~person(){}
};


class patient : public person{
protected:
    int age ;
    string gender;
public:
    patient(int id , string name,string phone, int age,string gender)
        :person(id,name,phone,'P'),age(age),gender(gender){}

    void display(){
        cout << "Patient ID " << id <<endl;
        cout << "Name " << name <<endl;
        cout << "phone " << phone <<endl;
        cout << "age " << age <<endl;
        cout << "gender " << gender <<endl;
    }

    string serialize(){
        return "P,"  +to_string(id)+ "," + name+ ","+ to_string(age)+ "," + gender+ "," + phone ;
    }
};


class doctor : public person{
public:
    string specialization ;
    doctor( int id , string name, string phone, string specialization)
        :person(id,name,phone,'D'),specialization(specialization){}

    void display(){
        cout <<"Doctor ID ->" << id  << endl ;
        cout <<"Name ->" << name << endl;
        cout << "Phone ->" << phone << endl ;
        cout <<"Specialization ->"<< specialization << endl;
    }

    string serialize(){
        return "D,"  +to_string(id)+ "," + name+ "," + specialization+ "," + phone ;
    }
};



class HospitalSystem {
private:
    person* persons[100];
    int count;

    
    bool idExists(int id){
        for(int i = 0; i < count; i++){
            if(persons[i]->id == id)
                return true;
        }
        return false;
    }

    
    int generateID(){
        int maxID = 0;
        for(int i = 0; i < count; i++){
            if(persons[i]->id > maxID)
                maxID = persons[i]->id;
        }
        return maxID + 1;
    }

public:

    
    HospitalSystem() : count(0){
        for(int i = 0; i < 100; i++)
            persons[i] = nullptr;
    }

   
    ~HospitalSystem(){
        des();
    }


    void save(){
        ofstream file("hospital management.txt");
        for(int i=0; i<count; i++ ){
            file << persons[i]->serialize() << endl;
        }
        file.close();
    }


    void load(){
        ifstream file("hospital management.txt");
        if(!file){
            cout << "No data file found" << endl;
            return;
        }
        string line;
        count = 0;

        while(getline(file,line)){
            if(line.empty()) continue;

            stringstream l(line);
            string type;
            getline(l,type,',');

            if(type == "P"){
                string l_id,l_name,l_age,l_gender,l_phone;
                getline(l,l_id,',');
                getline(l,l_name,',');
                getline(l,l_age,',');
                getline(l,l_gender,',');
                getline(l,l_phone,',');

                persons[count++] = new patient(
                    stoi(l_id), l_name, l_phone, stoi(l_age), l_gender
                );
            }
            else if(type == "D"){
                string l_id,l_name,l_specialization,l_phone;
                getline(l,l_id,',');
                getline(l,l_name,',');
                getline(l,l_specialization,',');
                getline(l,l_phone,',');

                persons[count++] = new doctor(
                    stoi(l_id), l_name, l_phone, l_specialization
                );
            }
        }
        file.close();
    }


    void add(){
        if(count >= 100){
            cout << "Storage Full!\n";
            return;
        }

        
        int typee;
        cout << "Enter type (1 = Patient / 2 = Doctor): ";
        cin >> typee;   

        if(typee != 1 && typee != 2){
            cout << "Invalid choice!\n";
            return;
        }

        
        int id = generateID();
        cout << "ID will be: " << id << endl;

        string name, phone;

        
        cout << "Enter Name: ";
        cin.ignore();        
        getline(cin, name);

        cout << "Enter Phone: ";
        getline(cin, phone);

        if(typee == 1){
            int age;
            string gender;
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Gender: ";
            cin.ignore();
            getline(cin, gender);
            persons[count++] = new patient(id, name, phone, age, gender);
        }
        else{
            string specialization;
            cout << "Enter Specialization: ";
            cin.ignore();
            getline(cin, specialization);
            persons[count++] = new doctor(id, name, phone, specialization);
        }

        save();
        cout << "Added Successfully" << endl;
    }


    void edit(){
        int targetid;
        string newname ;
        cout << "Enter ID To Edit: ";
        cin >> targetid ;

        for(int i = 0; i<count; i++){
            if(persons[i]->id == targetid){
                cout << "Enter New Name: " << endl ;
                cin.ignore();
                getline(cin,newname);
                persons[i]->name = newname;
                save();
                cout << "Updated successfully" << endl;
                return;
            }
        }
        cout << "Not Found !" << endl;
    }


    
    void displayByType(char t){
        if(count == 0){
            cout << "No records found.\n";
            return;
        }
        bool found = false;
        for(int i = 0; i < count; i++){
            if(persons[i]->type == toupper(t)){
                cout << "-------------------\n";
                persons[i]->display();
                found = true;
            }
        }
        
        if(!found)
            cout << "No records found for this type.\n";
    }


    void des(){
        for(int i = 0; i < count; i++){
            delete persons[i];
            persons[i] = nullptr;
        }
        count = 0;
    }


    void search(char t){
        int ch;
        cout << "1. Search by ID\n2. Search by Name\nChoice: ";
        cin >> ch;

        if(ch == 1){
            int id;
            cout << "Enter ID: ";
            cin >> id;

            for(int i = 0; i < count; i++){
                if(persons[i]->id == id && persons[i]->type == toupper(t)){
                    persons[i]->display();
                    return;
                }
            }
        }
        else{
            string name;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin,name);

            for(int i = 0; i < count; i++){
                if(persons[i]->name == name && persons[i]->type == toupper(t)){
                    persons[i]->display();
                    return;
                }
            }
        }
        
        cout << "Not Found!\n";
    }


    void removePerson(char t){
        int targetid;
        cout << "Enter ID to delete: ";
        cin >> targetid;

        for(int i = 0; i < count; i++){
            if(persons[i]->id == targetid && persons[i]->type == toupper(t)){
                delete persons[i];

                for(int j = i; j < count - 1; j++){
                    persons[j] = persons[j + 1];
                }

                
                persons[count - 1] = nullptr;
                count--;
                save();
                cout << "Deleted successfully\n";
                return;
            }
        }
        cout << "Not Found!\n";
    }
};


