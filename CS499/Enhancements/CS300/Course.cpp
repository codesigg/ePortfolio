#include "Course.h"

/**
 * Constructor for creating a Course object.
 *
 * @param id the id value for the course.
 * @param name the name for the course.
 * @param prerequisites the list of any prerequisites for the course.
 */
Course::Course(std::string& id, std::string& name, std::vector<std::string>& prerequisites) {
    this->courseId = id;
    this->courseName = name;
    this->coursePrerequisites = prerequisites;
}

/**
 * Getter for the course id.
 * @return courseId
 */
std::string Course::getCourseId() const {
    return this->courseId;
}

/**
 * Getter for the course name.
 * @return courseName
 */
std::string Course::getCourseName() const {
    return this->courseName;
}

/**
 * Getter for the list of course prerequisites.
 * @return coursePrerequisites
 */
std::vector<std::string> Course::getCoursePrerequisites() const {
    return this->coursePrerequisites;
}

/**
 * Returns a concatenated string of course values.
 * @return string with courseId and courseName
 */
std::string Course::courseToString() const {
    if (courseId.empty() || courseName.empty()) {
        return "Invalid course data";
    }
    return this->courseId + ", " + this->courseName;
}

/**
 * Validates if the course data is valid.
 * @return true if courseId and courseName are not empty
 */
bool Course::isValid() const {
    if (courseId.empty() || courseName.empty()) {
        return false;
    }
    for (const auto& prereq : coursePrerequisites) {
        if (prereq.empty()) {
            return false;
        }
    }
    return true;
}

/**
 * Equality operator for comparing two courses.
 * @param other the course to compare with
 * @return true if both courses have the same ID and name
 */
bool Course::operator==(const Course& other) const {
    return courseId == other.courseId && courseName == other.courseName;
}

