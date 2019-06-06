#include "Course.h"
#include "Student.h"

namespace BrooklynPoly{
    Course::Course(const std::string& courseName): name(courseName){}
    const std::string& Course::getName() const{
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
        size_t iStudent = students.size();
        for(size_t i = 0; i < students.size(); ++i){
            iStudent = i;
            students[i]->removedFromCourse(this);
        }
        students.clear();
    }

    std::ostream& operator<<(std::ostream& os, const Course& rhs){
        //os << "Courses:";
        os << rhs.name << ':';
        if(rhs.students.size() == 0){
            os << " No Students";
        }
        else{
            for(Student* student: rhs.students){
                os << ' ';
                os << student->getName();//I think name here is fine!
                //os << student->name; no it's not okayy!!! bc this is a Course class not student class
                //=> only friend with Course!
            }
        }
        
        return os;
    }
}