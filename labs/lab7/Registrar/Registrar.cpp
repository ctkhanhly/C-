#include "Registrar.h"
#include "Course.h" //course_h defined here
#include "Student.h" // check since course_h defined => dont include course

namespace BrooklynPoly{
    size_t Registrar::findStudent(const std::string& name) const{
        for(size_t i = 0; i < students.size(); ++i){
            if(students[i]->getName() == name){
                return i;
            }
        }
        return students.size();
    }
    size_t Registrar::findCourse(const std::string& name) const{
        for(size_t i = 0; i < courses.size(); ++i){
            if(courses[i]->getName() == name){
                return i;
            }
        }
        return courses.size();
    }
    Registrar::Registrar(){}
    bool Registrar::addCourse(const std::string& cName){
        //check if course existed
        size_t iCourse = findCourse(cName);
        if(iCourse != courses.size() && courses.size()!= 0){
            return false;
        }
        courses.push_back(new Course(cName));
        return true;
    }
    bool Registrar::addStudent(const std::string& sName){
        //check if student existed
        size_t iStudent = findStudent(sName);
        if(iStudent != students.size() && students.size() != 0){
            return false;
        }
        students.push_back(new Student(sName));
        return true;
    }
    bool Registrar::enrollStudentInCourse(const std::string& studentName,
                                const std::string& courseName){
        size_t iCourse = findCourse(courseName);
        size_t iStudent = findStudent(studentName);
        if(iStudent == students.size()|| iCourse == courses.size()){
            return false;
        }
        courses[iCourse]->addStudent(students[iStudent]);
        students[iStudent]->addCourse(courses[iCourse]);
        return true;
    }
    bool Registrar::cancelCourse(const std::string& courseName){
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
    std::ostream& operator<<(std::ostream& os, const Registrar& rhs){
        os << "Registrar's Report" << std::endl;
        os << "Courses:";
        if(rhs.courses.size() != 0){
            for(Course* course: rhs.courses){
                os << std::endl;
                os << *course;
            }
        }
        else{
            os << "No Courses";
        }
        os << std::endl << "Students: ";
        if(rhs.students.size() != 0){
            for(Student* student: rhs.students){
                os << std::endl;
                os << *student;
            }
        }
        else{
            os << "No Students";
        }
    
        return os;
    }
}
