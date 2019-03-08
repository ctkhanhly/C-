/* Ly Cao
Lab 5
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//STORED IN HEAP = POINTERS!!!!

class Section{
    friend ostream& operator<<(ostream& os, const Section& section){
        //Section: A2, Time slot: [Day: Tuesday, Start time: 4pm], Students: None
        os << "Section: " << section.name << ", Time slot: [" << section.timeslot 
        << "], Students:";
        if(section.students.size() == 0){
            os << " None";
        }
        else{
            for(Student* student: (section.students)){
                os << endl;
                os << *student;
            }
        }
        return os;
        
    }

    class TimeSlot{
        friend ostream& operator<<(ostream& os, const TimeSlot& timeslot){
       
            string timeSign = "am";
            if(timeslot.hour > 12){
                timeSign = "pm";
            }
            os << "Day: " << timeslot.dayOfWeek << ", Start time: " << timeslot.hour%12 << timeSign;
            return os;
        }
    private:
        unsigned int hour;
        string dayOfWeek;
    public:
        TimeSlot(const string& dayOfWeek, unsigned int hour): dayOfWeek(dayOfWeek), hour(hour){}
        unsigned int getHour()const{
            return hour;
        }
        const string& getDayOfWeek() const {
            return dayOfWeek;
        }
        //TimeSlot(const TimeSlot& timeslot): dayOfWeek(timeslot.dayOfWeek), hour(timeslot.hour){}
    };
    class Student{

        friend ostream& operator<<(ostream& os, const Student& student){
                //Name: John, Grades: -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 
            os << "Name: " << student.name << ", Grades: ";
            for(int grade: student.studentRecords){
                os << grade << " ";
            }
            return os;
        }
        const size_t numOfWeeks = 14;
        const int absence = -1;
    private:
        string name;
        vector<int> studentRecords;// cannot make function/ to constructor outside of function/ main
        //int* studentRecords;
        //int totalStudents = 0;

    public:
        Student(const string& name): name(name), studentRecords(numOfWeeks, absence){
            //studentRecords.push_back(-1); // every1 is absence if be4 first grade is entered
        }
        //studentRecords(student.studentRecords)
        Student(const Student& student): name(student.name){
            for(int grade: student.studentRecords){
                studentRecords.push_back(grade);
            }
            // for(size_t i  = 0; i< student.studentRecords.size(); ++ i){
            //     studentRecords.push_back(student.studentRecords[i]);
            // }
        }
        void changeGrade(int grade, int week){//setStudentRecords
            studentRecords[week] = grade;
        }
        const vector<int>& getStudentRecords() const {
            return studentRecords;
        }
        const string& getName() const {
            return name;
        }
        
    };
    
private:
    string name;
    //int* studentNames;//vector of students
    vector<Student*> students;
    TimeSlot timeslot; //must initialize constant when declaring - should TimeSlot be constant?
    /*
    Grades should be kept separately for each week - 
    so each week the lab worker adds the student's score 
    for that week to the current grade record for the section he is teaching. 
    Each student lab record consists only of the student's name and their weekly grades
    */
public:
    Section(const string& name, string dayOfWeek, int hour): name(name), timeslot(dayOfWeek, hour){
        //studentRecords = new int[1]
    }
    // void setStudent(size_t i, Student* student){
    //     students[i] = student;
    // }
    void addStudent(const string& name){
        students.push_back(new Student(name));//********
    }
    void addGrade(const string& studentName, int grade, int week){
        for(Student* student : students){
            if(student->getName() == studentName){
                student->changeGrade(grade, week - 1);
            }
        }
    }
    //dont want to change entire vector
    // const vector<Student*> getStudents() const{
    //     return students;
    // }
    // Student* getStudent(size_t i) const {
    //     return students[i];
    // }
    ~Section(){
        cout <<  "Section "<< name << " is being deleted"<< endl;
        for(Student* student: students){
            cout << "Deleting " << student-> getName() << endl;
            delete student;
            student = nullptr;
        }
    }
    //timeslot(section.timeslot.getDayOfWeek(), section.timeslot.getHour())
    //why section can access timeslot here? private field
    Section(const Section& section): timeslot(section.timeslot), name(section.name){
        for(size_t i = 0; i < section.students.size(); ++i){
            //no student b/c constructor
            students.push_back(new Student(*section.students[i]));
            //*(students[i]) = *(section.getStudent(i));
        }

    }
};

class LabWorker{
    friend ostream& operator<<(ostream& os, const LabWorker& labworker){
        if(labworker.section){
            os << labworker.name << " has " << *labworker.section;
        }
        else{
            os << labworker.name << "does not have a section";
        }
        return os;
    }
private:
    string name;
    Section* section; //initialize to nullptr
public:
    LabWorker(const string& name): name(name), section(nullptr){}
    void addSection(Section& section) {
        //the parameter cannot be const
        this->section = &section;// later test w/o parenthesis
    }
    //every student is absence before the first grade is entered

    void addGrade(const string& studentName, int grade, int week){
        //delegation dont allow access to students b/c it can't
        //b/c it does not have access to students shouldnt change anything
        //inside students -> ask other to do for it
        section->addGrade(studentName, grade, week);
    }
};

// Test code
void doNothing(Section sec) { 
    cout << sec << endl;;
}
int main(){

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe("Moe");//Labworker is public class
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection(secA2); // has a section field
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection(secB3);// jane connects to secB3 here
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1); //LabWorker 
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works properly, i.e. no memory leaks\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

}// main