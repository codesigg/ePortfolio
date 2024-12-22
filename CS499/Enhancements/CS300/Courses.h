#ifndef PROJECT_2_COURSES_H
#define PROJECT_2_COURSES_H

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include "Course.h"
#include <unordered_set>

struct Node {
    Course course;
    Node* left;
    Node* right;

    // Default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Initialize with a course
    Node(Course newCourse) : Node() {
        course = newCourse;
    }
};

class Courses {
private:
    Node* root;
    std::unordered_map<std::string, Course> courseMap;
    void destroyRecursive(Node* node);
    void addNode(Node* node, Course course);
    void inOrder(Node* node, std::function<void(Course)> visit);
    void postOrder(Node* node, std::function<void(Course)> visit);
    void preOrder(Node* node, std::function<void(Course)> visit);
    Node* removeNode(Node* node, std::string courseId);
    void mergeSort(std::vector<Course>& courses, int left, int right);
    void merge(std::vector<Course>& courses, int left, int mid, int right);

public:
    Courses();
    virtual ~Courses();
    void InOrder(std::function<void(Course)> visit = nullptr);
    void PostOrder(std::function<void(Course)> visit = nullptr);
    void PreOrder(std::function<void(Course)> visit = nullptr);
    void Insert(Course course);
    void Remove(std::string courseId);
    Course Search(std::string courseId);
    Course SearchInMap(std::string courseId);
    std::vector<Course> getAllCourses();
    void sortCoursesByMergeSort();
    bool hasCycle(std::string courseId, std::unordered_set<std::string>& visited, std::unordered_set<std::string>& recursionStack);

};

#endif //PROJECT_2_COURSES_H
