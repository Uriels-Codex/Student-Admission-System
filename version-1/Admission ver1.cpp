#include <iostream>
using namespace std;

class Dhvsu {
    protected: 
        string Fname, Mname, Lname, YearLevel; 
        int StudentNumber, SchoolProgram, Campus; 
    
    void setInfo (string Fname, string Mname, string Lname, int Campus, int SchoolProgram, string YearLevel, int StudentNumber) {
       this -> Fname = Fname;
       this -> Mname = Mname;
       this -> Lname = Lname;
       this -> SchoolProgram = SchoolProgram;
       this -> YearLevel = YearLevel;
       this -> StudentNumber = StudentNumber;
       this -> Campus = Campus;
    }
};
class Admission : public Dhvsu {
    public:
    int numbering = 1;
    void GetInfo(){
      do{   cout << "\t\t\t\t DHVSU ADMISSION PORTAL  \n\n";
            cout << "Enter First Name: ";
            getline(cin, Fname);   
            cout << "Enter Middle Name: ";
            getline(cin, Mname);
            cout << "Enter Last Name: ";
            getline(cin, Lname);
            cout << "Enter Year Level: ";
            getline(cin, YearLevel);
            cout << "Enter School Number: ";
            cin >> StudentNumber;
            cin.ignore();
            if ((Fname.empty()) || (Mname.empty()) || (Lname.empty()) || (YearLevel.empty())) {
                cout << "Please fill in the blanks..." << endl; }
        }while ((Fname.empty()) || (Mname.empty()) || (Lname.empty()) || (YearLevel.empty()));      
    }
    void GetCampus() {
    do{ cout << "\nSelect a campus: " << endl;
        cout << "1. DHVSU Lubao Campus \n2. DHVSU Porac Campus" << endl;
        cout << "3. DHVSU Apalit Campus \n4. DHVSU Mexico Campus" << endl;
        cout << "Choose: ";
        cin >> Campus;
      }while (Campus > 5);  
    }
};
class DhvsuLubao : public Admission{
    public:
    void GetProgram() {
    string DLCprograms[] = {"Bachelor of Science in Civil Engineering" , "Bachelor of Science in Business Administration", 
        "Bachelor of Science in Information Technology", "Bachelor of Elementary Education","Bachelor of Science in Entrepreneurship",
        "Bachelor of Science in Psychology", "Bachelor of Science in Tourism Management"};
    
        for (int i = 0; i < (sizeof(DLCprograms)/sizeof(DLCprograms[0])); i++) {
            cout << numbering << ". " << DLCprograms[i] << endl;
            numbering++;
        }
        cout << "Choose: ";
        cin >> SchoolProgram;
        cin.ignore();
        system("cls");
        
    }
};
class DhvsuPorac : public Admission{
    public:
    void GetProgram() {
        string DPCprograms[] = {"Bachelor of Science in Business Administration", "Bachelor of Science in Information Technology", 
            "Bachelor of Elementary Education", "Bachelor of Science in Social Work"};
        
            for (int i = 0; i < (sizeof(DPCprograms)/sizeof(DPCprograms[0])); i++) {
                cout << numbering << ". " << DPCprograms[i] << endl;
                numbering++;
            }
            cout << "Choose: ";
            cin >> SchoolProgram;
            system("cls");
            cout << "Name: " << Fname << " " << Mname << " " << Lname << endl;
            cout << "Student Number: " << StudentNumber << endl;
            cout << "Year Level: " << YearLevel << endl;
            cout << "Program: " << DPCprograms[SchoolProgram - 1];
        }
};
class DhvsuApalit : public Admission {
    public:
    void GetProgram() {
        string DACprograms[] = {"Bachelor of Science in Business Administration", "Bachelor of Science in Information Technology", 
            "Bachelor of Elementary Education", "Bachelor of Science in Hospitality and Management"};
        
            for (int i = 0; i < (sizeof(DACprograms)/sizeof(DACprograms[0])); i++) {
                cout << numbering << ". " << DACprograms[i] << endl;
                numbering++;
            }
            cout << "Choose: ";
            cin >> SchoolProgram;
            system("cls");
            cout << "Name: " << Fname << " " << Mname << " " << Lname << endl;
            cout << "Student Number: " << StudentNumber << endl;
            cout << "Year Level: " << YearLevel << endl;
            cout << "Program: " << DACprograms[SchoolProgram - 1];
        }
};
class DhvsuMexico : public Admission{
    public:
    void getProgram() {
        string DMCprograms[] = {"Bachelor of Science in Business Administration", "Bachelor of Science in Information Technology", 
            "Bachelor of Elementary Education", "Bachelor of Secondary Education", "Bachelor of Science in Hospitality and Management",
            "Bachelor in Physical Education", "Bachelor of Science in Industrial Technology", "Bachelor of Technology and Livelihood Education",
            "Bachelor of Science in Accountancy"};
        
            for (int i = 0; i < (sizeof(DMCprograms)/sizeof(DMCprograms[0])); i++) {
                cout << numbering << ". " << DMCprograms[i] << endl;
                numbering++;
            }
            cout << "Choose: ";
            cin >> SchoolProgram;
            system("cls");
            cout << "Name: " << Fname << " " << Mname << " " << Lname << endl;
            cout << "Student Number: " << StudentNumber << endl;
            cout << "Year Level: " << YearLevel << endl;
            cout << "Program: " << DMCprograms[SchoolProgram - 1];
        }
   
};
class Management : public Admission {
    public:
    void Main_menu() {
        GetInfo();
        GetCampus();
        if (Campus == 1){
            DhvsuLubao student1;
            student1.GetProgram();
            cout << "First Name: " << Fname << endl; 
            cout << "Middle Name: " << Mname << endl; 
            cout << "Last Name: " << Lname << endl;
            cout << "Student Number: " << StudentNumber << endl;
            cout << "Year Level: " << YearLevel << endl;
            
           
        }
        else if (Campus == 2) {
            DhvsuPorac student1;
            student1.GetProgram();
            cout << "Choose: ";
            cin >> SchoolProgram;
        }
        else if (Campus == 3) {
            DhvsuApalit student1;
            student1.GetProgram();
            cout << "Choose: ";
            cin >> SchoolProgram;
        }
        else if (Campus == 4) {
            DhvsuMexico student1;
            student1.getProgram();
           
        }
    }
};

int main () {
    
    Management user1;
    user1.Main_menu();
    
    return 0;
}