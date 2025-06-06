    #include <iostream>
    #include <vector>
    #include <fstream>
    #include <ctime>
    using namespace std;    
    // BSIT 1C

    class Dhvsu {
        protected: 
            string Fname, Mname, Lname, YearLevel;  // Encapsulation
            static string Username; static string Userpass;
            static string AdminName; static string AdminPass; 
            int SchoolProgram, Campus, StudentNumber;
            static int registCount; 

        int Generate_id () { // Abstraction
            time_t current =time(0);
            struct tm* Ltime = localtime(&current); 
            int year = 1900 + Ltime->tm_year;
            return year * 1000000 + registCount++;
            }

        void setInfo (string Fname, string Mname, string Lname, int Campus, int SchoolProgram, string YearLevel) { // Abstraction
            this -> Fname = Fname; this -> Mname = Mname; this -> Lname = Lname;
            this -> SchoolProgram = SchoolProgram; this -> YearLevel = YearLevel;
            this -> StudentNumber = Generate_id(); this -> Campus = Campus;
            //this -> Username =  to_string(this->StudentNumber);  //ex: 2025000001
            //this -> Userpass = "Dhvsu" + to_string(this->StudentNumber); //ex: Dhvsu2025000001
        }

        public: int GetStudentNum() const { return StudentNumber;}

    };  

    int Dhvsu::registCount = 1;
    string Dhvsu::AdminName = "Admin";
    string Dhvsu::AdminPass = "Admin123";
    string Dhvsu::Username = "User";
    string Dhvsu::Userpass = "User123";

    class LogInConsole: public Dhvsu{
        protected: 
            void AccessStudentFiles () {
                  string line;
                  string AccessInfo;

                    cout << "Enter Student ID to see info: ";
                    cin >> AccessInfo;

                    fstream File(AccessInfo + ".txt");
                    if(File.is_open()) {
                        while(getline(File,line)) {
                            cout << line << endl;
                        }
                       File.close(); 
                    }
                    else {
                        cout <<"File cannot be open...";
                        return;
                    }
            }
        public:
        int choice;
        

           void AdminConsole() { 
                string *pAdminName = &AdminName; string *pAdminpass = &AdminPass;
                string OldAdminName = AdminName; string OldAdminPass = AdminPass;

                cout << endl << "1. Change Log-in info" << endl << "2. See Students Info: " << endl;
                cout << "Choose: "; cin >> choice;
                cin.ignore();

                switch (choice){
                 case 1: 
                    do {
                    cout << endl  <<  "Enter new Admin name: "; getline(cin, *pAdminName);
                    cout << "Enter new Admin password: "; getline(cin, *pAdminpass); 
                    if  ((*pAdminName == OldAdminName) || (*pAdminpass == OldAdminPass)) { // bug
                        cout << "Please put a new one.. " << endl;}

                    else { cout << "Changed Sucess!!" <<endl;}
                        system("cls");
                    }while ((*pAdminName == OldAdminName) || (*pAdminpass == OldAdminPass));      
                     break;
                 case 2: 
                        AccessStudentFiles();
                        break;
                 default:
                    cout << "Error...Please try againn.";
                     break;
                 }
            }

            void StudentConsole() { 
                
                string *pUsername = &Username; 
                string *pUserpass = &Userpass;
                string OldUsername = Username;
                string OldUserPass = Userpass;

                    cout << "1. Change Log-in info" << endl << "2. Acess info" << endl; 
                    cout << "Choose: "; cin >> choice;
                    cin.ignore();
                    switch (choice)
                    {
                    case 1:
                        do {
                        cout << "Enter new User name: "; getline(cin, *pUsername);
                        cout << "Enter new User password: "; getline(cin, *pUserpass); 
                        if  ((*pUsername == OldUsername) || (*pUserpass == OldUserPass)) {
                            cout << "Please put a new one.. " << endl;}

                        else { cout << "Changed Sucess!!" <<endl;}
                        }while ((*pUsername == OldUsername) || (*pUserpass== OldUserPass));  
                        break;
                    case 2:
                        AccessStudentFiles();
                        break;
                    default:
                        cout << "error..Please try again..";
                        break;
                    }       
            }
    };
    class Admission : public Dhvsu {
        protected:

            vector<string>  CollegePrograms =  {"Bachelor of Science in Civil Engineering", "Bachelor of Science in Business Administration", 
                "Bachelor of Science in Information Technology","Bachelor of Elementary Education", "Bachelor of Science in Entrepreneurship",
                "Bachelor of Science in Psychology", "Bachelor of Science in Tourism Management","Bachelor of Secondary Education", 
                "Bachelor of Science in Hospitality and Management","Bachelor in Physical Education", "Bachelor of Science in Industrial Technology",
                "Bachelor of Technology and Livelihood Education", "Bachelor of Science in Accountancy", "Bachelor of Science in Social Work"};
            
            vector<int> validIndexes;

        public:
        int numbering = 1;

        void GetInfo(){
        do{     cout << "Enter First Name: "; getline(cin, Fname);   
                cout << "Enter Middle Name: "; getline(cin, Mname);
                cout << "Enter Last Name: "; getline(cin, Lname);
                cout << "Enter Year Level: "; getline(cin, YearLevel);
                if ((Fname.empty()) || (Mname.empty()) || (Lname.empty()) || (YearLevel.empty())) {
                    cout << "Please fill in the blanks..." << endl; }
            }while ((Fname.empty()) || (Mname.empty()) || (Lname.empty()) || (YearLevel.empty()));      
        }

        void GetProgram(){
            cout << "Choose: "; cin >> SchoolProgram; 
            int actualIndex = validIndexes[SchoolProgram - 1]; 
            SchoolProgram = actualIndex;
        }

       void GetCampus() {
        do{ cout << "\nSelect a campus: " << endl;
            cout << "1. DHVSU Lubao Campus \n2. DHVSU Porac Campus" << endl;
            cout << "3. DHVSU Apalit Campus \n4. DHVSU Mexico Campus" << endl;
            cout << "Choose: "; cin >> Campus;
            if (Campus > 4 || Campus < 1) { cout << "Please try again..";}
        }while (Campus > 4 || Campus < 1);  
        }

        void printInfo() {
            cout << "Name: " << Fname << " " << Mname << " " << Lname << endl;
            cout << "Year Level: " << YearLevel << endl;
            cout << "Student Number: " << StudentNumber << endl;
            cout << "School Program: " <<  CollegePrograms[SchoolProgram] << endl; 

        }

        void Create_SaveFile(){
            string Filename = (to_string(GetStudentNum()) + ".txt");
                ofstream studentFile(Filename);
                if(studentFile.is_open()){
                    studentFile << "Name: " << Fname + " " + Mname + " " + Lname << endl;
                    studentFile << "Year Level: " << YearLevel << endl;
                    studentFile << "Student Number: " << StudentNumber << endl;
                    studentFile << "School Program: " << CollegePrograms[SchoolProgram] << endl;
           
                    studentFile.close();
                }else {
                    cout << "FIle is not created " << endl;
                }   
            }
    };

    class DhvsuLubao : public Admission{
        public:
       
        void printDLCprogram(){

            cout << "\t\t\t\t DHVSU LUBAO CAMPUS" << endl << endl;
            for (size_t i = 0; i < CollegePrograms.size(); i++) {
            if( i >= 0 && i <= 7 ) {
                cout << numbering << ". " << CollegePrograms[i] << endl;
                validIndexes.push_back(i);
                numbering++;
            }
            else {
                continue;
            }
        }
    }


    void Registration () {
            cin.ignore();
            GetInfo();
            printDLCprogram();
            GetProgram();
            setInfo (Fname, Mname, Lname, Campus, SchoolProgram , YearLevel);
            printInfo();
         
        }
    };

    class DhvsuPorac : public Admission{
        public: 
        void printDPCprogram(){
            //InitializeInfo();
            cout << "\t\t\t\t DHVSU PORAC CAMPUS" << endl << endl;
            for (size_t i = 0; i < CollegePrograms.size(); i++) {
            if ((i >= 1) && (i <= 3 || i == 13)) {
                cout << numbering << ". " << CollegePrograms[i] << endl;
                validIndexes.push_back(i);
                numbering++;
            }
            else {
                continue;
            }
          }
        }

        void Registration () {
            cin.ignore();
            GetInfo();
            printDPCprogram();
            GetProgram();
            setInfo (Fname, Mname, Lname, Campus, SchoolProgram, YearLevel);
            printInfo();
          
            }
    };

    class DhvsuApalit : public Admission {
        public:

        void printDACprogram(){
            //InitializeInfo();
            cout << "\t\t\t\t DHVSU APALIT CAMPUS" << endl << endl;
            for (size_t i = 0; i < CollegePrograms.size(); i++) {
            if ((i >= 1) && (i<= 3 || i == 8)) {
                cout << numbering << ". " << CollegePrograms[i] << endl;
                validIndexes.push_back(i); 
                numbering++;
            }
            else {
                continue;
            }
        }
    }

    void Registration () {
            cin.ignore();
            GetInfo();
            printDACprogram();
            GetProgram();
            setInfo (Fname, Mname, Lname, Campus, SchoolProgram, YearLevel);
            printInfo();
           
        }
    };

    class DhvsuMexico : public Admission{
        public:

        void printDMCprogram(){
            //InitializeInfo();
            cout << "\t\t\t\t DHVSU MEXICO CAMPUS" << endl << endl;
            for (size_t i = 0; i < CollegePrograms.size(); i++) {
            if ((i >= 4 && i <= 6 ) || i == 13 || i == 0) {
                continue;
            } else {
                cout << numbering << ". " << CollegePrograms[i] << endl;
                validIndexes.push_back(i); 
                numbering++;
            } 
        }
    }
        void Registration () {
            cin.ignore();
            GetInfo();
            printDMCprogram();
            GetProgram();
            setInfo (Fname, Mname, Lname, Campus, SchoolProgram, YearLevel);
            printInfo();


        }
    };

    class Management : public Admission {
        public: 
        LogInConsole Log;
        int choice;
        string LoginName, LoginPass;
          
        void Menu() {
        cout << "---------------Dhvsu Portal----------------" << endl << endl;
        cout << "1. Log in " << endl << "2. Admissiom" << endl;
        cout << "3. Exit " << endl << "Choose: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            do{
            cout << "Enter Username: "; cin >> LoginName;
            cout << "Enter password: "; cin >> LoginPass;
            if ((LoginName == AdminName) && (LoginPass == AdminPass)) {
                    Log.AdminConsole(); 
                    Menu();
                break; }
            else if((LoginName == Username) && (LoginPass == Userpass)) {
                    Log.StudentConsole(); 
                    Menu();
                break;}
            else { system("cls"); cout << "Invalid Credentials...." << endl; }
            }while (((LoginName != AdminName) && (LoginPass != AdminPass)) ||((LoginName != Username) && (LoginPass != Userpass)));
                break;

        case 2:

            GetCampus();
                if (Campus == 1) {
                    DhvsuLubao student1;
                    student1.Registration();
                    student1.Create_SaveFile();
                    system("pause"); 
                    system("cls");
                    Menu();
                }   
                else if (Campus == 2) {
                    DhvsuPorac student1;
                    student1.Registration();
                    student1.Create_SaveFile();
                    system("pause"); 
                    system("cls");
                    Menu();
                }      
                else if (Campus == 3) {
                    DhvsuApalit student1;
                    student1.Registration();
                    student1.Create_SaveFile();
                    system("pause"); 
                    system("cls");
                    Menu();
                }
                else if (Campus == 4) {
                    DhvsuMexico student1;
                    student1.Registration();
                    student1.Create_SaveFile();
                    system("pause"); 
                    system("cls");
                    Menu();
                }
                break;
            case 3:
                return;
                break;
        default: 
                cout << "error.....";
                break;
            }
        }
    };

    int main () {
        
        Management user1;
        user1.Menu();
        
        return 0;
    }