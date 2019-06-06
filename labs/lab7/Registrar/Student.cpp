#include "Student.h"
#include "Course.h"
//using namespace std;

namespace BrooklynPoly{
    Student::Student(const std::string& name): name(name){}
    const std::string& Student::getName() const{
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
            }
        }
        if(courses.size() != iCourse){
            for(size_t i = iCourse; i < courses.size(); ++i){
                courses[i] = courses[i+1];
            }
            courses.pop_back();
        }
    }

    std::ostream& operator<<(std::ostream& os, const Student& rhs){
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


}
