#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <limits>
using namespace std;    
// BSIT 1C

enum Campuses { Lubao =  1, Porac = 2, Apalit = 3, Mexico = 4};
Campuses campus;

class Dhvsu {
    protected: 
        string Fname, Mname, Lname, YearLevel, Sex, Gmail, Address;  // Encapsulation
        string Username, Userpass;
        static string AdminName; static string AdminPass; 
        int SchoolProgram, Campus, StudentNumber, age;
        static int registCount; 

    string getCampusName(Campuses campus) {
        switch (campus) {
        case Lubao: return "Lubao";
        case Porac: return "Porac";
        case Apalit: return "Apalit";
        case Mexico: return "Mexico";
        default: return "errror";}
    }

    int Generate_id () { // Abstraction.. Automatically generate a unique ID for every student who registerd
        time_t current =time(0);
        struct tm* Ltime = localtime(&current); 
        int year = 1900 + Ltime->tm_year;
        return year * 1000000 + registCount++;
        }
    
    void setInfo (string Fname, string Mname, string Lname, int Campus, int SchoolProgram, string YearLevel,
                  string Sex, string Gmail, string Address, int age) { // Abstraction.

        this-> age = age;            
        this -> Fname = Fname; this -> Mname = Mname; 
        this -> Lname = Lname; this -> Sex = Sex;
        this -> SchoolProgram = SchoolProgram;  this-> Gmail = Gmail;
        this -> YearLevel = YearLevel;  this-> Address = Address;
        this -> StudentNumber = Generate_id(); this -> Campus = Campus;
        this -> Username =  to_string(this->StudentNumber);  //ex: 2025000001
        this -> Userpass = "Dhvsu" + to_string(this->StudentNumber); //ex: Dhvsu2025000001
    }

    public: 
    int GetStudentNum() const { return StudentNumber;}

    void CleanBuffer() { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); };
};  

int Dhvsu::registCount = 1; 
string Dhvsu::AdminName = "Admin";
string Dhvsu::AdminPass = "Admin123";
//string Dhvsu::Username = "User";
//string Dhvsu::Userpass = "User123";

class Admission : public Dhvsu {
    protected:

    vector<string>  CollegePrograms =  {
        "Bachelor of Science in Civil Engineering",
        "Bachelor of Science in Business Administration", 
        "Bachelor of Science in Information Technology",
        "Bachelor of Elementary Education", 
        "Bachelor of Science in Entrepreneurship",
        "Bachelor of Science in Psychology", 
        "Bachelor of Science in Tourism Management",
        "Bachelor of Secondary Education", 
        "Bachelor of Science in Hospitality and Management",
        "Bachelor in Physical Education", 
        "Bachelor of Science in Industrial Technology",
        "Bachelor of Technology and Livelihood Education", 
        "Bachelor of Science in Accountancy", 
        "Bachelor of Science in Social Work"};

    static vector<string> StudentList; // use to store the list of student who registered
    vector<int> validIndexes; // use to store the real indexes of campus in each derived class
    static vector<string> TeachersList;

    public:
    int numbering = 1;

    void Dhvsu_banner() {
        cout << "   _____________________________________________________________________________________________________________" << endl;
        cout << "   |                                                                                                           |" << endl;
        cout << "   |                                       WELCOME   ASPIRING   HONORIANS!!!                                   |" << endl;
        cout << "   |                      D O N   H O N O R I O   V E N T U R A   S T A T E   U N I V E S I T Y                |" << endl;
        cout << "   |                                                                                                           |" << endl;
        cout << "   |                                       ADMISSION   AND   STUDENT   PORTAL                                  |" << endl;
        cout << "   |___________________________________________________________________________________________________________|" << endl;
        cout << endl;
    }

    virtual void GetInfo(){ // get student info
        cout << "Enter First Name: "; getline(cin, Fname);   
        cout << "Enter Middle Name: "; getline(cin, Mname);
        cout << "Enter Last Name: "; getline(cin, Lname);
        cout << "Enter Year Level: "; getline(cin, YearLevel);
        cout << "Enter Gender: "; getline(cin, Sex);
        cout << "Enter Gmail: "; getline(cin, Gmail);
        cout << "Enter Address: "; getline(cin, Address);
        if ((Fname.empty()) || (Mname.empty()) || (Lname.empty()) || (YearLevel.empty()) ||
            (Sex.empty()) || (Gmail.empty()) || (Address.empty())) {
            cout << "Please fill in the blanks..." << endl;
            system("cls"); GetInfo(); }
    }      

    void GetProgram(){ // Studentt choose program
        cout << endl << "Choose: "; cin >> SchoolProgram;// store student input
        if(cin.fail()) {CleanBuffer(); GetProgram();}
        int actualIndex = validIndexes[SchoolProgram - 1]; //decrement the value of Validindex to get the real index and store it to actualIndex
        SchoolProgram = actualIndex; // SchoolProgram now has same value of ActualIndex
    }

    virtual void printInfo() { // print student Info
        cout << endl;
        cout << "__________________" << endl;
        cout << "|Name:           |" << "\t" << Fname << " " << Mname << " " << Lname << endl;
        cout << "|Year Level:     |" << "\t" << YearLevel <<endl;
        cout << "|Student Number: |" << "\t" << StudentNumber << endl;
        cout << "|Gmail:          |" << "\t" << Gmail<< endl; 
        cout << "|Gender:         |" << "\t" << Sex << endl;
        cout << "|Address:        |" << "\t" << Address << endl;
        cout << "|School Program: |" << "\t" << CollegePrograms[SchoolProgram] << endl; 
        cout << "|Campus:         |" << "\t" << getCampusName(campus) << endl;
        cout << "|________________|" << endl;
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
            S_list << file << endl; }
            S_list.close();
        } else { cout << "Error saving StudentList!" << endl; }
    }   

    virtual void Create_SaveFile(){ // Create and save a file of student using their ID/student number
    string Filename = (to_string(GetStudentNum()) + ".txt");
    ofstream studentFile(Filename);
        if(studentFile.is_open()){
        studentFile << "Name: " << Fname + " " + Mname + " " + Lname << endl;
        studentFile << "Year Level: " << YearLevel << endl;
        studentFile << "Student Number: " << StudentNumber << endl;
        studentFile << "School Program: " << CollegePrograms[SchoolProgram] << endl;
        studentFile << "Gmail: " << Gmail<< endl; 
        studentFile << "Gender: " << Sex << endl;
        studentFile << "Address: " << Address << endl;
        studentFile << "Campus: " << getCampusName(campus) << endl;
        studentFile << "Password: " << Userpass << endl;
        StudentList.push_back(Filename);
        studentFile.close();
    }else {
        cout << "FIle is not created " << endl; }   
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
                lines.push_back("Password: " + newpass); }
            else { lines.push_back(line);}
        } i_file.close();
        
    }
    ofstream o_file(filename);

    if (!o_file) { cout << "File didnt open.."; return; }
    else{  for (string& i : lines) {
        o_file << i << endl; }   
        }  
        o_file.close();
        cout << "Password changed successfully!!" << endl;
    }   

    virtual void printProgram() = 0;
    
    void Registration () {
    cin.ignore();
    Dhvsu_banner();
    GetInfo(); cout << endl; system("cls");
    Dhvsu_banner();
    printProgram(); cout << endl;
    GetProgram(); cout << endl;
    setInfo (Fname, Mname, Lname, Campus, SchoolProgram , YearLevel, Sex, Gmail, Address, age);
    printInfo(); cout << endl;
    Create_SaveFile(); cout << endl;
    saveStudentList();
    saveRegistCount();
    }

    virtual ~Admission() {}
    
    static void LoadRegistCount(); // declaration of static function, to make one share value accross the sys

    static void LoadStudentList(); // same sa loadRegistCount
};

void Admission::LoadRegistCount () { // declaration outside of class for static function, similar to the variables
    ifstream R_count("regist_count.txt");
    if(R_count.is_open()) { R_count >> registCount; }
}

void Admission::LoadStudentList() { // same with LoadRegust
    string line;
    ifstream S_list("students.txt");
    if (S_list.is_open()) {
        while (getline(S_list, line)) {
            StudentList.push_back(line);}
    }
}

vector<string> Admission::TeachersList; 
vector<string> Admission::StudentList; // make one share value across the system

class Subjects_1stSem {
    public:

    string Fyear_BSInfoTech () {
        return R"(
        _________________________________________________________________________
        | SUBJECT CODE  | DESCRIPTION                                   | UNITS |
        |_______________|_______________________________________________|_______|
        | FIRST YEAR / FIRST SEMESTER                                           |
        |_______________________________________________________________________|
        |_______________________________________________________________________|
        |                                                                       |
        |   CCP 1101     Computer Programming 1                         |   3   |
        |   CIC 1101     Introduction to Computing                      |   3   |
        |   CSP 1101     Social and Professional Issues in Computing    |   3   |
        |   MLC 1101     Literacy/Civic Welfare/Military Science 1      |   3   |
        |   PPE 1101     Physical Education 1                           |   2   |
        |   ZGE 1102     The Contemporary World                         |   3   |
        |   ZGE 1108     Understanding the Self                         |   3   |
        |_______________________________________________________________|_______|
        | Total Units                                                   |  20   |
        |_______________________________________________________________|_______|)";

    } 

    string Fyear_BSCE() {
        return R"(
        _________________________________________________________________________
        | SUBJECT CODE  |DESCRIPTION                                     |UNITS |                      
        |_______________|________________________________________________|______|    
        | FIRST YEAR / FIRST SEMESTER                                           |
        |_______________________________________________________________________|
        |_______________________________________________________________________|
        |                                                                |      |
        |   MLC 1101    Literacy/Civic Welfare/Military Science 1        |  3   |
        |   NCE 1201	Engineering Drawing and Plans                    |  1   |
        |   NCH 1101	Chemistry for Engineers Lecture                  | 	3   |
        |   NCH 1102	Chemistry for Engineers Laboratory       	     |  1   |
        |   NMA 1101	Calculus 1          	                         |  3   |
        |   PPE 1101	Physical Education 1                             |  2   |
        |   ZGE 1104	Mathematics in the Modern World                  |  3   |
        |   ZGE 1108	Understanding the Self	                         |  3   |  
        |________________________________________________________________|______|
        |Total Units	                                                 | 19   |
        |________________________________________________________________|______|)";
    }

    string Fyear_BSBA(){
        return R"(
        _________________________________________________________________________
        | SUBJECT CODE  |DESCRIPTION                                     |UNITS |                      
        |_______________|________________________________________________|______|    
        | FIRST YEAR / FIRST SEMESTER                                           |
        |_______________________________________________________________________|
        |_______________________________________________________________________|
        |                                                                |      |
        |   BBC 1101	Basic Microeconomics                             |  3   |
        |   BBC 1109	Human Resources Management                       |  3   |
        |   BME 1101	Administrative Management and Automation         |  3   |
        |   MLC 1101	Literacy/Civic Welfare/Military Science 1        |  3   |
        |   PPE 1101	Physical Education 1  	                         |  2   |
        |   ZGE 1104	Mathematics in the Modern World                  |  3   |
        |   ZGE 1106	Readings in Philippine History                   |  3   |
        |   ZGE 1108	Understanding the Self	                         |  3   |  
        |________________________________________________________________|______|
        |Total Units	                                                 | 23   |
        |________________________________________________________________|______|)";
    }

    string Fyear_BEED() {
        return R"(
        _________________________________________________________________________
        | SUBJECT CODE  |DESCRIPTION                                     |UNITS |                      
        |_______________|________________________________________________|______|    
        | FIRST YEAR / FIRST SEMESTER                                           |
        |_______________________________________________________________________|
        |_______________________________________________________________________|
        |                                                                |      |
        |   EPE 1101	The Child and Adolescent Learners                |  3   |
        |   MLC 1101	Literacy/Civic Welfare/Military Science          |  3   |
        |   PPE 1101	Physical Education 1                             |  2   |
        |   ZGE 1102	The Contemporary World                           |  3   |
        |   ZGE 1103	Ethics 	                                         |  2   |
        |   ZGE 1104	Mathematics in the Modern World                  |  3   |
        |   ZGE 1105	Purposive Communication                          |  3   |
        |   ZGE 1106	Readings in Philippine History                   |  3   |  
        |   ZGE 1108	Understanding the Self                           |  3   |
        |________________________________________________________________|______|
        |Total Units	                                                 | 26   |
        |________________________________________________________________|______|)";
    }

    string Fyear_BSpsych() {
        return  R"(
        _________________________________________________________________________
        | SUBJECT CODE  |DESCRIPTION                                     |UNITS |                      
        |_______________|________________________________________________|______|    
        | FIRST YEAR / FIRST SEMESTER                                           |
        |_______________________________________________________________________|
        |_______________________________________________________________________|
        |                                                                |      |
        |   APY 1101	Introduction to Psychology                       |  3   |
        |   MLC 1101	Literacy/Civic Welfare/Military Science 1        |  3   |
        |   PPE 1101	Physical Education 1                             |  2   |
        |   ZGE 1102	The Contemporary World                           |  3   |
        |   ZGE 1104	Mathematics in the Modern World                  |  3   |
        |   ZGE 1105	Purposive Communication                          |  3   |
        |   ZGE 1106	Readings in Philippine History                   |  3   |  
        |   ZGE 1108	Understanding the Self                           |  3   |
        |________________________________________________________________|______|
        |Total Units	                                                 | 23   |
        |________________________________________________________________|______|)";
    }

    string Fyear_Bstour(){
        return R"(
        _________________________________________________________________________
        | SUBJECT CODE  |DESCRIPTION                                     |UNITS |                      
        |_______________|________________________________________________|______|    
        | FIRST YEAR / FIRST SEMESTER                                           |
        |_______________________________________________________________________|
        |_______________________________________________________________________|
        |                                                                |      |
        |   ATH 1103	Macro Perspective of Tourism and Hospitality     |  3   |
        |   ATH 1110	Risk Management as Applied to S.S.S              |  3   |
        |   MLC 1101	Literacy/Civic Welfare/Military Science 1        |  3   |
        |   PPE 1101	Physical Education 1                             |  2   |
        |   ZGE 1104	Mathematics in the Modern World                  |  3   |
        |   ZGE 1105	Purposive Communication                          |  3   |
        |   ZGE 1106	Readings in Philippine History                   |  3   |  
        |________________________________________________________________|______|
        |Total Units	                                                 | 20   |
        |________________________________________________________________|______|)";
    }

    string Fyear_BSHM () {
        return R"(
        _________________________________________________________________________
        | SUBJECT CODE  |DESCRIPTION                                     |UNITS |                      
        |_______________|________________________________________________|______|    
        | FIRST YEAR / FIRST SEMESTER                                           |
        |_______________________________________________________________________|
        |_______________________________________________________________________|
        |                                                                |      |
        |   ATH 1103	Macro Perspective of Tourism and Hospitality     |  3   |
        |   ATH 1110	Risk Management as Applied to S.S.S              |  3   |
        |   MLC 1101	Literacy/Civic Welfare/Military Science 1        |  3   |
        |   PPE 1101	Physical Education 1                             |  2   |
        |   ZGE 1103	Ethics                                           |  3   |
        |   ZGE 1105	Purposive Communication                          |  3   |
        |   ZGE 1106	Readings in Philippine History                   |  3   |  
        |________________________________________________________________|______|
        |Total Units	                                                 | 20   |
        |________________________________________________________________|______|)";
    }

    string Fyear_BSPE(){
        return  R"(
        _________________________________________________________________________
        | SUBJECT CODE  |DESCRIPTION                                     |UNITS |            
        |_______________|________________________________________________|______|    
        | FIRST YEAR / FIRST SEMESTER                                           |
        |_______________________________________________________________________|
        |_______________________________________________________________________|
        |                                                                |      |
        |   EPH 1101	Philosophy and Socio-anthropological Foundations |  3   |
        |   EPH 1102	Anatomy and Physiology of Human Movement         |  3   |
        |   EPH 1103	Principles Motor Control and Learning of Exercise|  3   |
        |   MLC 1101	Literacy/Civic Welfare/Military Science 1        |  3   |
        |   PPE 1101	Physical Education 1                             |  2   |
        |   ZGE 1102	The Contemporary World                           |  3   |
        |   ZGE 1106	Readings in Philippine History                   |  3   |  
        |   ZGE 1108	Understanding the Self                           |  3   |
        |________________________________________________________________|______|
        |Total Units	                                                 | 23   |
        |________________________________________________________________|______|)";
    }

    string Fyear_BSA() {
        return R"(
        _________________________________________________________________________
        | SUBJECT CODE  |DESCRIPTION                                     |UNITS |                      
        |_______________|________________________________________________|______|    
        | FIRST YEAR / FIRST SEMESTER                                           |
        |_______________________________________________________________________|
        |_______________________________________________________________________|
        |                                                                |      |
        |   BSA 1101	Fundamentals of Accounting 1 & 2                 |  6   |
        |   BSA 1102	Law on Obligation and Contracts                  |  3   |
        |   EPH 1103	Principles Motor Control and Learning of Exercise|  3   |
        |   MLC 1101	Literacy/Civic Welfare/Military Science 1        |  2   |
        |   PPE 1101	Physical Education 1                             |  3   |
        |   ZGE 1104	Mathematics in the Modern World                  |  3   |
        |   ZGE 1106	Readings in Philippine History                   |  3   |  
        |   ZGE 1107	Science, Technology, and Society                 |  3   |
        |   ZGE 1108	Understanding the Self                           |  3   |
        |________________________________________________________________|______|
        |Total Units	                                                 | 26   |
        |________________________________________________________________|______|)";
    }

    string Fyear_BSIndustTech() {
        return R"(
        _________________________________________________________________________
        | SUBJECT CODE  |DESCRIPTION                                     |UNITS |                     
        |_______________|________________________________________________|______|    
        | FIRST YEAR / FIRST SEMESTER                                           |
        |_______________________________________________________________________|
        |_______________________________________________________________________|
        |                                                                |      |
        |   AST 111      Math for Technology                             |  3   |
        |   AST 102      Applied Chemistry                               |  3   |
        |   AST 105      Applied Physics                                 |  3   |
        |   AST 133      Production Drawing                              |  2   |
        |   AST 127      Civil Techology Measurements                    |  2   |
        |   PM 101       Occupational Health and Safety Management       |  2   |
        |   CVT 111      Introduction to Structures                      |  4   |  
        |   CVT 112      National Building Code                          |  2   |
        |   NSTP 111     National Service Training Program 1             |  3   |
        |   PE 101       Physical Fitness, Gymnastics and Aerobics       |  2   |
        |________________________________________________________________|______|
        |Total Units	                                                 | 26   |
        |________________________________________________________________|______|)";
    }

    string Fyear_BTLE(){
        return R"(
        _________________________________________________________________________
        | SUBJECT CODE  |DESCRIPTION                                     |UNITS |                      
        |_______________|________________________________________________|______|    
        | FIRST YEAR / FIRST SEMESTER                                           |
        |_______________________________________________________________________|
        |_______________________________________________________________________|
        |                                                                |      |
        |   NSTP 111    National Service Training Program 1              |  3   |
        |   PE 101      Physical Fitness, Gymnastics and Aerobics        |  2   |
        |   GEd 104     The Contemporary World                           |  3   |
        |   GEd 105     Readings in Philippine History                   |  3   |
        |   GEd 106     Purposive Communication                          |  3   |
        |   Litr 101    Sosyedad at Literatura/Panitikang Panlipunan     |  3   |
        |   Ed 102      The Teaching Profession                          |  3   |  
        |   TLEd 111    Introduction to Industrial Arts 1                |  3   |
        |   TLEd 112    Introduction to ICT Specializations 1            |  3   |
        |   TLEd 113    Home Economics Literacy                          |  3   |
        |________________________________________________________________|______|
        |Total Units	                                                 | 29   |
        |________________________________________________________________|______|)";
    }

    string Fyear_BSEntrep() {
        return R"(
        _________________________________________________________________________
        | SUBJECT CODE  |DESCRIPTION                                     |UNITS |                      
        |_______________|________________________________________________|______|    
        | FIRST YEAR / FIRST SEMESTER                                           |
        |_______________________________________________________________________|
        |_______________________________________________________________________|
        |                                                                |      |
        |   GEN-US       Understanding The Self                          |  3   |
        |   GEN-RP       Readings in Philippine Historys                 |  2   |
        |   GEN-PC       Purposive Communication                      	 |  3   |
        |   ECC112       Administrative and Office Management            |  3   |
        |   ECC111       Human Resource Managementn                      |  3   |
        |   IES111       Business Marketing                              |  3   |
        |   NSTP1        National Service Training Program               |  3   |  
        |   PE1          Physical Activities towards Health and Fitness 1|  3   |
        |   PEP1         Personality Development                         |  2   |
        |   GE-RE        Religious Experiences and Benedictine           |  1   |
        |________________________________________________________________|______|
        |Total Units	                                                 | 27   |
        |________________________________________________________________|______|)";

    }

    string GetSubjectbyChoice(int choice) {
    switch (choice) {
        case 1:  return Fyear_BSInfoTech();
        case 2:  return Fyear_BSCE();
        case 3:  return Fyear_BSBA();
        case 4:  return Fyear_BEED();
        case 5:  return Fyear_BSEntrep();
        case 6:  return Fyear_BSpsych();
        case 7:  return Fyear_Bstour();
        case 8:  return Fyear_BEED();
        case 9:  return Fyear_BSHM();
        case 10: return Fyear_BSPE();
        case 11: return Fyear_BSIndustTech();
        case 12: return Fyear_BTLE();
        case 13: return Fyear_BSA();
        case 14: return Fyear_BSPE();
        default: return "Invalid input..."; system("cls"); }
    }
};

class StudentConsole : public Admission {
    protected:
    string LoginName, LoginPass;
    string line;
    public: 

    void printProgram() override {}

    void StudentLogin () { // login via search info in a txt file saved, base on registration
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
                if(line == "Student Number: "  + LoginName) { // check if the Login Name use is the same with the Student ID
                    valid_name = true; 
                }
            } File.close(); 
            
            if ((!valid_name) || (!valid_pass)) {
                cout <<"Invalid Credentials.." << endl << endl;
                return;
            } 
            else {
                system ("cls");
                cout << "Login sucessfully!!" << endl;
                Console();
            }   
        }
        else {
            cout <<"Invalid credentials..." << endl;
            system("pause"); system("cls");
            return;
        }
    }

    void AccessFiles(string Access) { // readfile using the Username as parameter to make it as a filename
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
        return; }
    }

    void Console() { 
    string newpass;
    int student_choice;
    system("cls");
    Dhvsu_banner();
    
    cout <<"--------------------------------------------------STUDENT PORTAL-------------------------------------------------------" << endl << endl;
    cout << "1. Change Log-in info" << endl << "2. Acess info" << endl; 
    cout << "3. Exit" << endl << "Choose: "; cin >> student_choice;
    cout << endl;
    if(cin.fail()) { system ("cls"); CleanBuffer(); return;}
    if (student_choice != 1 && student_choice != 2) {system("cls"); return;}
    cin.ignore();
    
    switch (student_choice) {
    case 1:
        cout << "Enter new password: "; getline(cin, newpass);
        ChangePass(LoginName, newpass);
        break;
    case 2:
        AccessFiles(Username + ".txt");
        system("pause");
        Console();
        break;
    case 3: 
        return ;
        break;
    default:
        cout << "error..Please try again.." << endl;
        break;  }       
    }

};

class AdminConsole : public Admission{ //inherit the methods of asdmission and attributes/methods of Dhvsu clss
    protected: 
    
    string subject;
    vector<string> subs = {
    "bsInfoTech", "bsCivilEng", "bsBusinessAdmin", "elemEd", "bsEntrep", "bsPsych", "bsTourism", "secondaryEd",
    "bsHospMgmt", "physEd", "bsIndTech", "btle", "bsAcctg", "bsSocialWork"
    };


    void printProgram() override {} // to avoid the error of using a abstract class and pure virtual functions

    void GetInfo() override { // override the og getinfo of students to teachers
        do {
        cout << "Enter First Name: "; getline(cin, Fname);
        cout << "Enter Middle Name: "; getline(cin, Mname);
        cout << "Enter Last Name: "; getline(cin, Lname);
        cout << "Enter entrusted subject: "; getline(cin, subject);
        if(Fname.empty() || Mname.empty() || Lname.empty() || subject.empty()) {
            cout <<"Please fill in the blanks.."; return;} 
        }while ((Fname.empty() || Mname.empty() || Lname.empty() || subject.empty()));
         
    }

    void printInfo() override { // override the og Print info for students to teachers
        cout << "Name: " << Fname <<" " << Mname << " " << Lname << endl;
        cout << "Subject: " << subject << endl;
    }

    void Create_SaveFile() override { // override the og Create_savefile in the admission, and this one creates for teachers
        ofstream Teacher_File("Teacher Credentials.txt", ios::app);
        if(!Teacher_File) {
            cout<<"Fille cannot be created..";
        }
        else {
            Teacher_File << "Name: " << Fname << " " << Mname << " " << Lname << endl;
            Teacher_File << "Subject: " << subject << endl;
            Teacher_File << "--------------------------------------------------------------------------------------------------------------" << endl;
            TeachersList.push_back("Teacher Credentials.txt");
            Teacher_File.close();
        } 
    }

    void PrintList(vector<string>& StudentInfo){ // print list of students who registred using the memory address of StudentList as paramter
        StudentConsole Sc;
        int num = 1;
        int admin_choice;
        size_t choice;
        for (size_t i = 0; i < StudentInfo.size(); i++) {
            cout << num <<". " << StudentList[i] << endl;
            num++; }

        if(StudentInfo.empty()) { 
            cout << "FIle is empty..." << endl; 
            system("pause"); system("cls"); Console();}
            
        cout << "Pick a number: "; cin >> choice; 
        if(cin.fail()) {system ("cls"); CleanBuffer();}

        if(choice > 0 && choice <= StudentInfo.size()) {
        string SelectedFile = StudentInfo[choice - 1];
        cout <<"Student: " << SelectedFile<< endl << endl;
        Sc.AccessFiles(SelectedFile); cout << endl;
        
        cout << "1. Give subjects" << endl << "2. Exit" << endl;
        cout << "Choose: "; cin >> admin_choice;

        if(cin.fail()) { system("cls"); CleanBuffer();}
            switch (admin_choice){
            case 1:
                Setsubjects(SelectedFile);
                system("pause"); system("cls");
                return;
                break;
            case 2:
                system("cls"); return;
            default:
                break;
            }
        }
        else {
            cout<< "Invalid input.."; system("cls");
            Console();
        }
    }

    void prnt_TeachList() {
        string line;
        ifstream infile("Teacher Credentials.txt");
        if(!infile) { cout << "File cannot be opened.." << endl;}
        else { while(getline(infile, line)){
            cout <<line << endl;
        } infile.close(); }
    }        

    void Setsubjects(string file) { // give subjects enrolled to students if they pass the exam
    Subjects_1stSem sb;
    string to_addsub;
    int choc_2;
    
    cout << endl << "This are the availabe subjects for now: " << endl; //loop through vector subs
    for(size_t i = 0; i < subs.size();i++){
        cout << numbering << ". " << subs[i] << endl;
        numbering++;
    } cout << endl << "Choose: "; cin >> choc_2;
    if(cin.fail()) {system("cls"); CleanBuffer(); return;} // system handling
    sb.GetSubjectbyChoice(choc_2);
    to_addsub = sb.GetSubjectbyChoice(choc_2);

    ofstream ofile(file,ios::app); // right at the end of the file and not overwrite it
    if(!ofile) {cout << "File cannnot be opened..."; return;}
    ofile << to_addsub << endl;
    ofile.close();
    cout << "file has been updated!!..."<< endl; system("pause"); system("cls"); return;
    }
  
    public:
    int choice;

    void Console() { 
        string *pAdminName = &AdminName; 
        string *pAdminpass = &AdminPass; // make a pointer of the original value to use it to update later
        string OldAdminName = AdminName; 
        string OldAdminPass = AdminPass; // store the old value of AdminName/Pass for error handling later
        system("cls");
        Dhvsu_banner();
        cout <<"--------------------------------------------------STUDENT PORTAL-------------------------------------------------------" << endl << endl;
        cout << endl << "1. Change Log-in info" << endl << "2. See Students Info: " << endl;
        cout << "3. See Teacher's List" << endl << "4. Add a teacher" << endl;
        cout << "5. Exit"<< endl << "Choose: "; cin >> choice;  
        if(cin.fail()) { system("cls"); CleanBuffer(); Console();}
        if (choice < 1 || choice > 5) { Console();}
        cin.ignore();

    switch (choice){
        case 1: 
        do {
        cout << endl  << "Enter new Admin name: "; getline(cin, *pAdminName); // update the originalvalue of AdminName
        cout << "Enter new Admin password: "; getline(cin, *pAdminpass); // update the orig valuye of AdminPass
        if  ((*pAdminName == OldAdminName) || (*pAdminpass == OldAdminPass)) { 
            cout << "Please put a new one.. " << endl;}

        else {  system("cls"); cout << "Changed Sucess!!" << endl; 
                system("pause"); Console();}
                
        }while ((*pAdminName == OldAdminName) || (*pAdminpass == OldAdminPass));     
            break;
        case 2: 
            PrintList(StudentList); cout << endl;// call out method using the StudentList vector in admission as argument to access the data
            system("cls");
            Console();
            break;
        case 3:
            cout << endl;
            prnt_TeachList(); // print teachers list
            system("pause");
            system("cls");
            Console();
            break;
           
        case 4: // add a teacher
            GetInfo(); cout << endl;
            printInfo();
            system("pause");
            Create_SaveFile();
            Console();
            break;
        case 5:
            return;
            break;

        default:
        cout << "Error...Please try againn." << endl;
            break;
        }
    }
};

class DhvsuLubao : public Admission{
    public:
    void printProgram() override {
        cout << "\t\t\t\t DHVSU LUBAO CAMPUS" << endl << endl;
        for (size_t i = 0; i < CollegePrograms.size(); i++) {
        if( i <= 7 ) {
            cout << numbering << ". " << CollegePrograms[i] << endl;
            validIndexes.push_back(i);
            numbering++; }
        else {
            continue; }
        }
    }
};

class DhvsuPorac : public Admission{
    public: 
    void printProgram() override {
        cout << "\t\t\t\t DHVSU PORAC CAMPUS" << endl << endl;
        for (size_t i = 0; i < CollegePrograms.size(); i++) {
        if ((i >= 1) && (i <= 3 || i == 13)) {
            cout << numbering << ". " << CollegePrograms[i] << endl;
            validIndexes.push_back(i);
            numbering++;
        }
        else {
            continue; }
        }
    }
};

class DhvsuApalit : public Admission {
    public:
    void printProgram() override {
        cout << "\t\t\t\t DHVSU APALIT CAMPUS" << endl << endl;
        for (size_t i = 0; i < CollegePrograms.size(); i++) {
        if ((i >= 1) && (i<= 3 || i == 8)) {
            cout << numbering << ". " << CollegePrograms[i] << endl;
            validIndexes.push_back(i); 
            numbering++;
        }
        else {
            continue; }
        }
    }
};

class DhvsuMexico : public Admission{
    public:
    void printProgram(){
        cout << "\t\t\t\t DHVSU MEXICO CAMPUS" << endl << endl;
        for (size_t i = 0; i < CollegePrograms.size(); i++) {
        if ((i >= 4 && i <= 6 ) || i == 13 || i == 0) {
            continue;
        } else {
            cout << numbering << ". " << CollegePrograms[i] << endl;
            validIndexes.push_back(i); 
            numbering++;} 
        }
    }
};

class Management : public Admission {
    public: 
    int choice, choice2;
    string LoginName, LoginPass;
    
    void printProgram() override {};

    void Menu() {
    StudentConsole sc;
    AdminConsole ac;
   
    do {system("cls");
        Dhvsu_banner();
        cout << "1. Log in " << endl << "2. Admissiom" << endl;
        cout << "3. Exit " << endl << "Choose: "; cin >> choice;
        cout << endl;
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
            if ((LoginName != AdminName) || (LoginPass != AdminPass)) {
                system("cls"); Dhvsu_banner(); cout << "Invalid Credentials..." << endl;
            }
            if ((LoginName == AdminName) && (LoginPass == AdminPass)) {
                ac.Console(); 
                Menu();
                break; }
        }while ((LoginName != AdminName) || (LoginPass != AdminPass));
        }
        else if (choice2 == 2) {
            sc.StudentLogin(); 
            Menu();
        }
        else { cout << "Invalid input";  
            system("cls"); Menu(); }
        break;

    case 2: {

    Admission* student = nullptr;
        system("cls");
        while(true){
        Dhvsu_banner();
        cout << "\nSelect a campus: " << endl;
        cout << "1. DHVSU Lubao Campus \n2. DHVSU Porac Campus" << endl;
        cout << "3. DHVSU Apalit Campus \n4. DHVSU Mexico Campus" << endl;
        cout << "Choose: "; cin >> Campus; system("cls");
        if(cin.fail()) {  system("cls"); CleanBuffer(); }

        if (Campus > 4 || Campus < 1) { 
            system("cls"); 
            cout <<"Please try again.." ; }

        campus =  (Campuses) Campus;

        if(campus == Lubao) { student = new DhvsuLubao(); break;}
        else if(campus == Porac) { student = new DhvsuPorac(); break;}
        else if(campus == Apalit) { student = new DhvsuApalit(); break;}
        else if(campus == Mexico) { student = new DhvsuMexico(); break;}
        else{ cout << "Invalid input.. please try again"; system("cls");}
        } 
        
        student->Registration();
        system("pause");
        delete student;
        Menu();
        break;
    }
    
    case 3:
        cout << "Programmed by yours truly: Chavez, Brent Yuri P. " << endl;
        cout << "BSIT - 1C  [Batch 2024-2025]" << endl;
        return;
        break;
    default:
        Menu();
        break;
    }
  };
};

int main () {


Admission::LoadRegistCount();
Admission::LoadStudentList();

Management user1;
user1.Menu();

    return 0;
}