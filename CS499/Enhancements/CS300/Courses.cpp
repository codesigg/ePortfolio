#include "Courses.h"
#include <iostream>
#include <algorithm>

/**
 * Default constructor
 */
Courses::Courses() {
    root = nullptr;
}

/**
 * Destructor
 */
Courses::~Courses() {
    destroyRecursive(root);
}

/**
 * In-order traversal with callback
 */
void Courses::InOrder(std::function<void(Course)> visit) {
    inOrder(root, visit);
}

/**
 * Post-order traversal with callback
 */
void Courses::PostOrder(std::function<void(Course)> visit) {
    postOrder(root, visit);
}

/**
 * Pre-order traversal with callback
 */
void Courses::PreOrder(std::function<void(Course)> visit) {
    preOrder(root, visit);
}

/**
 * Helper function to detect cycles using DFS.
 */
bool Courses::hasCycle(std::string courseId, std::unordered_set<std::string>& visited, std::unordered_set<std::string>& recursionStack) {
    // Mark the current node as visited and add it to the recursion stack
    visited.insert(courseId);
    recursionStack.insert(courseId);

    // Check the prerequisites of the current course
    if (courseMap.find(courseId) != courseMap.end()) {
        for (const auto& prereq : courseMap[courseId].getCoursePrerequisites()) {
            // If the prerequisite is in the recursion stack, a cycle is detected
            if (recursionStack.find(prereq) != recursionStack.end()) {
                return true;
            }
            // If the prerequisite has not been visited, recurse
            if (visited.find(prereq) == visited.end() && hasCycle(prereq, visited, recursionStack)) {
                return true;
            }
        }
    }

    // Remove the current node from the recursion stack
    recursionStack.erase(courseId);
    return false;
}

/**
 * Insert a course with cycle detection.
 */
void Courses::Insert(Course course) {
    std::unordered_set<std::string> visited;
    std::unordered_set<std::string> recursionStack;

    // Check for cycles before inserting
    if (hasCycle(course.getCourseId(), visited, recursionStack)) {
        std::cerr << "Error: Cycle detected involving course " << course.getCourseId() << ". Course not inserted." << std::endl;
        return;
    }

    // If no cycle is detected, insert the course
    if (courseMap.find(course.getCourseId()) != courseMap.end()) {
        std::cerr << "Error: Duplicate course ID " << course.getCourseId() << " detected." << std::endl;
        return;
    }

    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        addNode(root, course);
    }

    courseMap[course.getCourseId()] = course;
}

/**
 * Remove a course by ID
 */
void Courses::Remove(std::string courseId) {
    std::transform(courseId.begin(), courseId.end(), courseId.begin(), ::toupper);
    root = removeNode(root, courseId);
    courseMap.erase(courseId);
}

/**
 * Search for a course by ID in the BST
 */
Course Courses::Search(std::string courseId) {
    std::transform(courseId.begin(), courseId.end(), courseId.begin(), ::toupper);
    Node* cur = root;
    while (cur != nullptr) {
        if (cur->course.getCourseId() == courseId) {
            return cur->course;
        }
        else if (courseId < cur->course.getCourseId()) {
            cur = cur->left;
        }
        else {
            cur = cur->right;
        }
    }
    return Course();
}

/**
 * Search for a course by ID in the HashMap
 */
Course Courses::SearchInMap(std::string courseId) {
    std::transform(courseId.begin(), courseId.end(), courseId.begin(), ::toupper);
    if (courseMap.find(courseId) != courseMap.end()) {
        return courseMap[courseId];
    }
    return Course();
}

/**
 * Destroy nodes recursively
 */
void Courses::destroyRecursive(Node* node) {
    if (node != nullptr) {
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }
}

/**
 * Add a course to the tree
 */
void Courses::addNode(Node* node, Course course) {
    if (course.getCourseId() < node->course.getCourseId()) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            addNode(node->left, course);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            addNode(node->right, course);
        }
    }
}

/**
 * Helper function to remove a node by ID
 */
Node* Courses::removeNode(Node* node, std::string courseId) {
    if (node == nullptr) {
        return nullptr;
    }

    if (courseId < node->course.getCourseId()) {
        node->left = removeNode(node->left, courseId);
    }
    else if (courseId > node->course.getCourseId()) {
        node->right = removeNode(node->right, courseId);
    }
    else {
        // Node with one or no child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Node with two children: get the inorder successor (smallest in the right subtree)
        Node* temp = node->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }

        node->course = temp->course;
        node->right = removeNode(node->right, temp->course.getCourseId());
    }

    return node;
}

/**
 * In-order traversal helper with callback
 */
void Courses::inOrder(Node* node, std::function<void(Course)> visit) {
    if (node != nullptr) {
        inOrder(node->left, visit);
        if (visit) {
            visit(node->course);
        }
        else {
            std::cout << node->course.getCourseId() << ", " << node->course.getCourseName() << std::endl;
        }
        inOrder(node->right, visit);
    }
}

/**
 * Post-order traversal helper with callback
 */
void Courses::postOrder(Node* node, std::function<void(Course)> visit) {
    if (node != nullptr) {
        postOrder(node->left, visit);
        postOrder(node->right, visit);
        if (visit) {
            visit(node->course);
        }
        else {
            std::cout << node->course.getCourseId() << ", " << node->course.getCourseName() << std::endl;
        }
    }
}

/**
 * Pre-order traversal helper with callback
 */
void Courses::preOrder(Node* node, std::function<void(Course)> visit) {
    if (node != nullptr) {
        if (visit) {
            visit(node->course);
        }
        else {
            std::cout << node->course.getCourseId() << ", " << node->course.getCourseName() << std::endl;
        }
        preOrder(node->left, visit);
        preOrder(node->right, visit);
    }
}

/**
 * Get all courses from the tree (in-order traversal)
 */
std::vector<Course> Courses::getAllCourses() {
    std::vector<Course> courses;
    inOrder(root, [&courses](Course course) {
        courses.push_back(course);
        });
    return courses;
}

/**
 * Merge Sort entry function
 */
void Courses::sortCoursesByMergeSort() {
    std::vector<Course> courses = getAllCourses();
    if (!courses.empty()) {
        mergeSort(courses, 0, courses.size() - 1);
        std::cout << "Courses sorted by Merge Sort:" << std::endl;
        for (const auto& course : courses) {
            std::cout << course.getCourseId() << ", " << course.getCourseName() << std::endl;
        }
    }
    else {
        std::cerr << "No courses available to sort." << std::endl;
    }
}

/**
 * Merge Sort implementation
 */
void Courses::mergeSort(std::vector<Course>& courses, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(courses, left, mid);
        mergeSort(courses, mid + 1, right);
        merge(courses, left, mid, right);
    }
}

/**
 * Merge function for Merge Sort
 */
void Courses::merge(std::vector<Course>& courses, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Course> leftCourses(n1);
    std::vector<Course> rightCourses(n2);

    for (int i = 0; i < n1; i++)
        leftCourses[i] = courses[left + i];
    for (int j = 0; j < n2; j++)
        rightCourses[j] = courses[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftCourses[i].getCourseId() <= rightCourses[j].getCourseId()) {
            courses[k++] = leftCourses[i++];
        }
        else {
            courses[k++] = rightCourses[j++];
        }
    }

    while (i < n1) {
        courses[k++] = leftCourses[i++];
    }

    while (j < n2) {
        courses[k++] = rightCourses[j++];
    }
}