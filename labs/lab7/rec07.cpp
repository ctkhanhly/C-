/*
  rec07 
  Starter Code for required functionality
  Yes, you may add other methods.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse(); 

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend std::ostream& operator<<(std::ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const std::string& name);
    const std::string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);

private:
    std::string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};


//Student implementation

Student::Student(const string& name): name(name){}
const string& Student::getName() const{
    return name;
}
bool Student::addCourse(Course* course){
    for(Course* theCourse: courses){
        if(course == theCourse){
            return false;
        }
    }
    courses.push_back(course);
    return true;
}

// Student method needed by Course
void Student::removedFromCourse(Course* course){
    size_t iCourse = courses.size();
    for(size_t i = 0; i < courses.size(); ++i){
        if(courses[i] == course){
            iCourse = i;
            //delete courses[i];
        }
    }
    if(courses.size() != iCourse){
        for(size_t i = iCourse; i < courses.size(); ++i){
            courses[i] = courses[i+1];
        }
        // delete courses[iCourse]; - don't delete this address yet
        // courses[iCourse] = nullptr;
        courses.pop_back();
    }
    cout << "Finished Student::removedFromCourse" << endl;
}

ostream& operator<<(ostream& os, const Student& rhs){
    os << rhs.name << ":";
    if(rhs.courses.size() == 0){
        os << " No courses";
    }
    else{
        for(Course* course: rhs.courses){
            os << ' ';
            os << course->getName();
        }
    }
    return os;
}


//Has to put  course down here b/c else it cannot see Student methods
//Courses implementation
Course::Course(const string& courseName): name(courseName){}
const string& Course::getName() const{
    return name;
}
bool Course::addStudent(Student* student){
    for(Student* theStudent: students){
        if(student == theStudent){
            return false;
        }
    }
    students.push_back(student);
    return true;
}
void Course::removeStudentsFromCourse(){
    //size_t iStudent = students.size();
    for(size_t i = 0; i < students.size(); ++i){
        //iStudent = i;
        //member access into incomplete type 'Student'
        students[i]->removedFromCourse(this);
        // delete students[i];
        // students[i] = nullptr;
    }
    // if(students.size() != iStudent){
    //     for(size_t i = iStudent; i < students.size(); ++i){
    //         students[i] = students[i+1];
    //     }
    //     students.pop_back();
    // }
    students.clear();
    cout << "Finished Course::removeStudentsFromCourse" << endl;
}

ostream& operator<<(ostream& os, const Course& rhs){
    //os << "Courses:";
    os << rhs.name << ':';
    if(rhs.students.size() == 0){
        os << " No Students";
    }
    else{
        for(Student* student: rhs.students){
            os << ' ';
            os << student->getName();
        }
    }
    
    return os;
}
//Implementation of Registrar:
size_t Registrar::findStudent(const string& name) const{
    for(size_t i = 0; i < students.size(); ++i){
        if(students[i]->getName() == name){
            return i;
        }
    }
    return students.size();
}
size_t Registrar::findCourse(const string& name) const{
    for(size_t i = 0; i < courses.size(); ++i){
        if(courses[i]->getName() == name){
            return i;
        }
    }
    return courses.size();
}
Registrar::Registrar(){}
bool Registrar::addCourse(const string& cName){
    size_t iCourse = findCourse(cName);
    cout << "course index:" << iCourse << endl;
    if(iCourse != courses.size() && courses.size()!= 0){
        return false;
    }
    courses.push_back(new Course(cName));
    return true;
}
bool Registrar::addStudent(const string& sName){
    size_t iStudent = findStudent(sName);
     cout << "student index:" << iStudent << endl;
    if(iStudent != students.size() && students.size() != 0){
        return false;
    }
    students.push_back(new Student(sName));
    return true;
}
bool Registrar::enrollStudentInCourse(const string& studentName,
                               const string& courseName){
    size_t iCourse = findCourse(courseName);
    size_t iStudent = findStudent(studentName);
    if(iStudent == students.size()|| iCourse == courses.size()){
        return false;
    }
    courses[iCourse]->addStudent(students[iStudent]);
    students[iStudent]->addCourse(courses[iCourse]);
    return true;
}
//only Registrar will delete course
bool Registrar::cancelCourse(const string& courseName){
    size_t iCourse = findCourse(courseName);
    if(iCourse == courses.size()){
        return false;
    }
    courses[iCourse]->removeStudentsFromCourse();
    delete courses[iCourse];
    courses[iCourse] = nullptr;
    for(size_t i = iCourse; i < courses.size(); ++i){
        courses[i] = courses[i+1];
    }
    //forgot to pop_back
    courses.pop_back();
    cout << "Finished Registrar::cancelCourse" << endl;
    return true;
}
void Registrar::purge(){
    for(Course* course: courses){
        delete course;
    }
    courses.clear();
    for(Student* student: students){
        delete student;
    }
    students.clear();
}
ostream& operator<<(ostream& os, const Registrar& rhs){
    // if(rhs.students.size()== 0  && rhs.courses.size() == 0){
    //     //os << "No courses or students added yet" << endl;
    //     os << "Registrar's Report" << endl;
    //     os << "Courses:";
    //     os << endl << "Students: ";
    // }
    // else{
    os << "Registrar's Report" << endl;
    os << "Courses:";
    if(rhs.courses.size() != 0){
        for(Course* course: rhs.courses){
            os << endl;
            os << *course;
        }
    }
    else{
        os << "No Courses";
    }
    os << endl << "Students: ";
    if(rhs.students.size() != 0){
        for(Student* student: rhs.students){
            os << endl;
            os << *student;
        }
    }
    else{
        os << "No Students";
    }
        
    //}
    return os;
}

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

     
    cout << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

     
    cout << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;
    
    cout << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;
 
    cout << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;
 
    cout << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;  

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;  

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;  
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}
  
