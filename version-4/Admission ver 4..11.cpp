    #include <iostream>
    #include <vector>
    #include <fstream>
    #include <ctime>
    #include <limits>
    using namespace std;    
    // BSIT 1C

    class Dhvsu {
        protected: 
            string Fname, Mname, Lname, YearLevel;  // Encapsulation
            string Username, Userpass;
            static string AdminName; static string AdminPass; 
            int SchoolProgram, Campus, StudentNumber;
            static int registCount; 

        int Generate_id () { // Abstraction.. Automatically generate a unique ID for every student who registerd
            time_t current =time(0);
            struct tm* Ltime = localtime(&current); 
            int year = 1900 + Ltime->tm_year;
            return year * 1000000 + registCount++;
            }
        
        void setInfo (string Fname, string Mname, string Lname, int Campus, int SchoolProgram, string YearLevel) { // Abstraction
            this -> Fname = Fname; this -> Mname = Mname; this -> Lname = Lname;
            this -> SchoolProgram = SchoolProgram; this -> YearLevel = YearLevel;
            this -> StudentNumber = Generate_id(); this -> Campus = Campus;
            this -> Username =  to_string(this->StudentNumber);  //ex: 2025000001
            this -> Userpass = "Dhvsu" + to_string(this->StudentNumber); //ex: Dhvsu2025000001
        }

        public: int GetStudentNum() const { return StudentNumber;}

                void CleanBuffer() {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); };
    };  

    int Dhvsu::registCount = 1; 
    string Dhvsu::AdminName = "Admin";
    string Dhvsu::AdminPass = "Admin123";
    //string Dhvsu::Username = "User";
    //string Dhvsu::Userpass = "User123";

    class Admission : public Dhvsu {
        protected:

        vector<string>  CollegePrograms =  {"Bachelor of Science in Civil Engineering", "Bachelor of Science in Business Administration", 
            "Bachelor of Science in Information Technology","Bachelor of Elementary Education", "Bachelor of Science in Entrepreneurship",
            "Bachelor of Science in Psychology", "Bachelor of Science in Tourism Management","Bachelor of Secondary Education", 
            "Bachelor of Science in Hospitality and Management","Bachelor in Physical Education", "Bachelor of Science in Industrial Technology",
            "Bachelor of Technology and Livelihood Education", "Bachelor of Science in Accountancy", "Bachelor of Science in Social Work"};
        static vector<string> StudentList; // use to store the list of student who registered
        vector<int> validIndexes; // use to store the real indexes of campus in each derived class
        static vector<string> AdminFile;
        static vector<string> TeachersList;

        public:
        int numbering = 1;

        virtual void GetInfo(){ // get student info
                cout << "Enter First Name: "; getline(cin, Fname);   
                cout << "Enter Middle Name: "; getline(cin, Mname);
                cout << "Enter Last Name: "; getline(cin, Lname);
                cout << "Enter Year Level: "; getline(cin, YearLevel);
                if ((Fname.empty()) || (Mname.empty()) || (Lname.empty()) || (YearLevel.empty())) {
                    cout << "Please fill in the blanks..." << endl;
                    system("cls"); GetInfo(); }
            }      

        void GetProgram(){ // Studentt choose program
            cout << "Choose: "; cin >> SchoolProgram;// store student input
            if(cin.fail()) {system("cls"); CleanBuffer(); GetProgram();}
            int actualIndex = validIndexes[SchoolProgram - 1]; //decrement the value of Validindex to get the real index and store it to actualIndex
            SchoolProgram = actualIndex; // SchoolProgram now has same value of ActualIndex
        }

        void GetCampus() { // Student choose Campus
            cout << "\nSelect a campus: " << endl;
            cout << "1. DHVSU Lubao Campus \n2. DHVSU Porac Campus" << endl;
            cout << "3. DHVSU Apalit Campus \n4. DHVSU Mexico Campus" << endl;
            cout << "Choose: "; cin >> Campus;
            if(cin.fail()) {  system("cls"); CleanBuffer();}
            if (Campus > 4 || Campus < 1) { 
                system("cls"); 
                cout <<"Please try again.." ;
                GetCampus(); }
        }

        void printInfo(string SelectedCampus) { // print student Info
            cout << "Name: " << Fname << " " << Mname << " " << Lname << endl;
            cout << "Year Level: " << YearLevel << endl;
            cout << "Student Number: " << StudentNumber << endl;
            cout << "School Program: " <<  CollegePrograms[SchoolProgram] << endl; 
            cout << "Campus: " << SelectedCampus << endl;
        }

        void saveRegistCount() { // save register counter into txt file to continue the counting vene if the sys is restart
            ofstream R_count("regist_count.txt");
            if (R_count.is_open()) {
                R_count << registCount;
                R_count.close();
            } else {
                cout << "Error saving registCount!" << endl;
            }
        }

        void saveStudentList() { // save the value of StudentList vector into one txxt file, so that data wouldnt start at 0
            ofstream S_list("students.txt");
            if (S_list.is_open()) {
                for (const string& file : StudentList) {
                    S_list << file << endl;
                }
                S_list.close();
            } else {
                cout << "Error saving StudentList!" << endl;
            }
        }   

        static void LoadRegistCount(); // declaration of static function, to make one share value accross the sys

        static void LoadStudentList(); // same sa loadRegistCount

        static void Load_ProfCredentials();

        void Create_SaveFile(string SelectedCampus){ // Create and save a file of student using their ID/student number
            string Filename = (to_string(GetStudentNum()) + ".txt");
                ofstream studentFile(Filename);
                if(studentFile.is_open()){
                    studentFile << "Name: " << Fname + " " + Mname + " " + Lname << endl;
                    studentFile << "Year Level: " << YearLevel << endl;
                    studentFile << "Student Number: " << StudentNumber << endl;
                    studentFile << "School Program: " << CollegePrograms[SchoolProgram] << endl;
                    studentFile << "Campus: " << SelectedCampus << endl;
                    studentFile << "Password: " << Userpass << endl;
                    StudentList.push_back(Filename);
           
                    studentFile.close();
                }else {
                    cout << "FIle is not created " << endl;
                }   
            }

    };

    void Admission::Load_ProfCredentials() {
        string line;
        ifstream A_file("Admin Credentials.txt");
        if(A_file.is_open()) {
            while (getline(A_file, line)) {
                AdminFile.push_back(line);
            }
         }
    }

    void Admission::LoadRegistCount () { // declaration outside of class for static function, similar to the variables
        ifstream R_count("regist_count.txt");
        if(R_count.is_open()) { R_count >> registCount; }
    }

    void Admission::LoadStudentList() { // same with LoadRegust
        string line;
        ifstream S_list("students.txt");
        if (S_list.is_open()) {
            while (getline(S_list, line)) {
                StudentList.push_back(line);
            }
        }
    }

    vector<string> Admission::AdminFile;
    vector<string> Admission::TeachersList;
    vector<string> Admission::StudentList; // make one share value across the system

    class LogInConsole: public Admission{ //inherit the methods of asdmission and attributes/methods of Dhvsu clss
        protected: 
        string LoginName, LoginPass;
        string subject;

        void GetInfo() override {
            cout << "Enter First Name: "; getline(cin, Fname);
            cout << "Enter Middle Name: "; getline(cin, Mname);
            cout << "Enter Last Name: "; getline(cin, Lname);
            cout << "Enter entrusted subject: "; getline(cin, subject);
            if(Fname.empty() || Mname.empty() || Lname.empty() || subject.empty()) {
                cout <<"Please fill in the blanks.."; return;
            }
        }

        void printInfo() {
            cout << "Name: " << Fname <<" " << Mname << " " << Lname << endl;
            cout << "Subject: " << subject << endl;
        }

        void Create_SaveFile() {
            ofstream Teacher_File("Teacher Credentials.txt");
            if(!Teacher_File) {
                cout<<"Fille cannot be created..";
            }
            else {
                Teacher_File << "Name: " << Fname << " " << Mname << " " << Lname << endl;
                Teacher_File << subject << endl;
                TeachersList.push_back("Teacher Credentials.txt");
                Teacher_File.close();
            } 
        }

        void PrintList(vector<string>& StudentInfo){ // print list of students who registred using the memory address of StudentList as paramter
            int num = 1;
            size_t choice;
            for (size_t i = 0; i < StudentInfo.size(); i++) {
                cout << num <<". " << StudentList[i] << endl;
                num++;
            }
            cout << "Pick a number: "; cin >> choice; 
            if(cin.fail()) {system ("cls"); CleanBuffer();}

            if(choice > 0 && choice <= StudentInfo.size()) {
                string SelectedFile = StudentInfo[choice - 1];
                cout <<"Student: " << SelectedFile<< endl << endl;
                AccessFiles(SelectedFile);

            }
            else {
                cout<< "Invalid input.."; system("cls");
                AdminConsole();
            }
        }

        void AccessFiles(string Access) { // readfile using the SelectedFile as parameter to make it as a filename
            string line;

                fstream File(Access);
                if(File.is_open()) {
                    while(getline(File,line)) { // check everyline until no new line is read
                        cout << line << endl;
                    }
                    File.close(); 
                }
                else {
                    cout <<"File cannot be open..." << endl;
                    return;
                }
        }
        
        void ChangePass (const string& loginame, string& newpass) {
            string filename = loginame + ".txt";
            string line;
            vector<string> lines;
            ifstream i_file(filename);

            if(!i_file) { cout <<"File cannot be opened..."; return; }
            else {
                while(getline(i_file, line)) {
                    if(line.find("Password: ") == 0) {
                        line = "Password: " + newpass;
                        lines.push_back("Password: " + newpass);
                    }
                    else { lines.push_back(line);}
                }
                i_file.close();
              
            }
            ofstream o_file(filename);
        
            if (!o_file) { cout << "File didnt open.."; return; }
            else{  for (string& i : lines) {
                o_file << i << endl;
            }}  o_file.close();
                cout << "Password changed successfully!!" << endl;
        }

        public:
        int choice;

        void StudentLogin () { // login via search info in a txt file saved, base on registration
                string line;
                bool valid_name = false; // for validation in Login 
                bool valid_pass = false;
         
                cout << "Enter Student ID to login: "; cin >> LoginName;
                cout << "Enter Password: ";  cin >> LoginPass;


                fstream File(LoginName + ".txt"); // if user put 2025000001 it becomes 2025000001.txt and access the txt file saved
                if(File.is_open()) {
                    while(getline(File,line)) {
                        if(line == "Password: " + LoginPass){ //check if the password saved is same as the one in Login
                        valid_pass = true;
                        Username = LoginName;
                        }
                        if(line == "Student Number: "  + LoginName) {
                            valid_name = true;
                        }
                    }
                    File.close(); 
                    
                    if ((!valid_name) || (!valid_pass)) {
                        cout <<"Invalid Credentials.." << endl << endl;
                        return;
                    } 
                    else {
                        system ("cls");
                        cout << "Login sucessfully!!" << endl;
                        StudentConsole();
                    }   
                }
                else {
                    cout <<"Invalid credentials..." << endl << endl;
                    return;
                }
        }
    
        void AdminConsole() { 
                string *pAdminName = &AdminName; string *pAdminpass = &AdminPass; // make a pointer of the original value to use it to update later
                string OldAdminName = AdminName; string OldAdminPass = AdminPass; // store the old value of AdminName/Pass for error handling later

                cout << endl << "1. Change Log-in info" << endl << "2. See Students Info: " << endl;
                cout << "3. Exit" << endl << "4. Add a teacher" << endl << "Choose: "; cin >> choice;  
                if(cin.fail()) { system("cls"); CleanBuffer(); AdminConsole();}
                if (choice < 1 || choice > 3) { AdminConsole();}
                cin.ignore();

                switch (choice){
                 case 1: 
                    do {
                    cout << endl  << "Enter new Admin name: "; getline(cin, *pAdminName); // update the originalvalue of AdminName
                    cout << "Enter new Admin password: "; getline(cin, *pAdminpass); // update the orig valuye of AdminPass
                    if  ((*pAdminName == OldAdminName) || (*pAdminpass == OldAdminPass)) { 
                        cout << "Please put a new one.. " << endl;}

                    else { cout << "Changed Sucess!!" <<endl;}
                        system("cls");
                    }while ((*pAdminName == OldAdminName) || (*pAdminpass == OldAdminPass));     
                     break;
                 case 2: 
                        PrintList(StudentList); // call out method using the StudentList vector in admission as argument to access the data
                        system("pause");
                        system("cls");
                        AdminConsole();
                        break;
                 case 3:
                        return;
                        break;
                 case 4:
                        GetInfo();
                        printInfo();
                        Create_SaveFile();
                        break;
                 default:
                    cout << "Error...Please try againn." << endl;
                     break;
                 }
            }

        void StudentConsole() { 
                string newpass;

                    cout << "1. Change Log-in info" << endl << "2. Acess info" << endl; 
                    cout << "3. Exit" << endl << "Choose: "; cin >> choice;
                    if(cin.fail()) { system ("cls"); CleanBuffer(); return;}
                    if (choice != 1 && choice != 2) {system("cls"); return;}
                    cin.ignore();
                    
                    switch (choice) {
                    case 1:
                        cout << "Enter new password: "; getline(cin, newpass);
                        ChangePass(LoginName, newpass);
                        break;
                    case 2:
                        AccessFiles(Username + ".txt");
                        system("pause");
                        break;
                    case 3: 
                        return ;
                        break;
                    default:
                        cout << "error..Please try again.." << endl;
                        break;
                    }       
            }
    };
    
    class DhvsuLubao : public Admission{
        public:
        string SelectedCampus = "Lubao";
        void printProgram(){

            cout << "\t\t\t\t DHVSU LUBAO CAMPUS" << endl << endl;
            for (size_t i = 0; i < CollegePrograms.size(); i++) {
            if( i <= 7 ) {
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
            printProgram();
            GetProgram();
            setInfo (Fname, Mname, Lname, Campus, SchoolProgram , YearLevel);
            printInfo(SelectedCampus);
            Create_SaveFile(SelectedCampus);
            saveStudentList();
            saveRegistCount();
        }
    };

    class DhvsuPorac : public Admission{
        public: 
         string SelectedCampus = "Porac";
        void printProgram(){

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
            printProgram();
            GetProgram();
            setInfo (Fname, Mname, Lname, Campus, SchoolProgram, YearLevel);
            printInfo(SelectedCampus);
            Create_SaveFile(SelectedCampus);
            saveStudentList();
            saveRegistCount();
            }
    };

    class DhvsuApalit : public Admission {
        public:
        string SelectedCampus = "Apalit";
        void printProgram(){
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
            printProgram();
            GetProgram();
            setInfo (Fname, Mname, Lname, Campus, SchoolProgram, YearLevel);
            printInfo(SelectedCampus);
            Create_SaveFile(SelectedCampus);
            saveStudentList();
            saveRegistCount();
        }
    };

    class DhvsuMexico : public Admission{
        public:
        string SelectedCampus = "Mexico";
        void printProgram(){

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
            printProgram();
            GetProgram();
            setInfo (Fname, Mname, Lname, Campus, SchoolProgram, YearLevel);
            printInfo(SelectedCampus);
            Create_SaveFile(SelectedCampus);
            saveStudentList();
        }
    };

    class Management : public Admission {
        public: 
        LogInConsole Log;
        int choice, choice2;
        string LoginName, LoginPass;
          
        void Menu() {
        do { system("cls"); 
            cout << "---------------Dhvsu Portal----------------" << endl << endl;
            cout << "1. Log in " << endl << "2. Admissiom" << endl;
            cout << "3. Exit " << endl << "Choose: ";
            cin >> choice;
            if(cin.fail()){ system("cls"); CleanBuffer(); } // eror handler for when user input other than int
            }while(choice < 1 || choice > 3);

        switch (choice) {
        case 1:
            cout << "1. Admin" << endl << "2. Student" << endl;
            cout << "Choose: "; cin >> choice2;
            if(cin.fail()) { system("cls"); CleanBuffer(); Menu();}
            if(choice2 == 1) {
                do{
                cout << "Enter Username: "; cin >> LoginName;
                cout << "Enter password: "; cin >> LoginPass;
                if ((LoginName != AdminName) && (LoginPass != AdminPass)) {
                    system("cls"); cout << "Invalid Credentials..." << endl;
                }
                if ((LoginName == AdminName) && (LoginPass == AdminPass)) {
                    Log.AdminConsole(); 
                    Menu();
                    break; }
                } while ((LoginName != AdminName) && (LoginPass != AdminPass));
            }
            else if (choice2 == 2) {
                Log.StudentLogin(); 
                Menu();
            }
            else { cout << "Invalid input";  
                system("cls"); Menu(); }
            break;
        case 2:

            GetCampus();
                if (Campus == 1) {
                    DhvsuLubao student1;
                    student1.Registration();
                    system("pause"); 
                    system("cls");
                    Menu();
                }   
                else if (Campus == 2) {
                    DhvsuPorac student1;
                    student1.Registration();           
                    system("pause"); 
                    system("cls");
                    Menu();
                }      
                else if (Campus == 3) {
                    DhvsuApalit student1;
                    student1.Registration();
                    system("pause"); 
                    system("cls");
                    Menu();
                }
                else if (Campus == 4) {
                    DhvsuMexico student1;
                    student1.Registration();
                    system("pause"); 
                    system("cls");
                    Menu();
                }
                break;
            case 3:
                return;
                break;
            }
        }
    };

    int main () {
        Admission::Load_ProfCredentials();
        Admission::LoadRegistCount();
        Admission::LoadStudentList();
        
        Management user1;
        user1.Menu();
        
        return 0;
    }