#include "Course.h"
#include "Courses.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <memory>

/**
 * Display the course information to the console (std::cout)
 */
void displayCourse(Course course) {
    if (!course.isValid()) {
        std::cerr << "Invalid course data." << std::endl;
        return;
    }

    std::vector<std::string> coursePrerequisites = course.getCoursePrerequisites();
    std::string prerequisites = coursePrerequisites.empty() ? "n/a" : "";
    for (size_t i = 0; i < coursePrerequisites.size(); i++) {
        prerequisites += coursePrerequisites[i];
        if (i < coursePrerequisites.size() - 1) prerequisites += ", ";
    }

    std::cout << course.getCourseId() << ", " << course.getCourseName() << std::endl;
    std::cout << "Prerequisites: " << prerequisites << std::endl;
}

/**
 * Load an input file containing courses
 */
void loadCourses(const std::string& inputFilePath, std::unique_ptr<Courses>& coursesBst) {
    std::ifstream file(inputFilePath);
    if (!file.is_open()) {
        throw std::runtime_error("Error: File not found or could not be opened.");
    }

    std::string currentLine;
    while (std::getline(file, currentLine)) {
        std::stringstream ss(currentLine);
        std::string id, name, word;
        std::vector<std::string> prerequisites;
        int index = 0;

        while (std::getline(ss, word, ',')) {
            word = std::regex_replace(word, std::regex("\\r|\\n"), "");
            if (index == 0) id = word;
            else if (index == 1) name = word;
            else prerequisites.push_back(word);
            index++;
        }

        if (id.empty() || name.empty()) {
            std::cerr << "Error: Invalid course data found in line: " << currentLine << std::endl;
            continue;
        }

        Course course(id, name, prerequisites);
        coursesBst->Insert(course);
    }
    file.close();
    std::cout << "Courses successfully loaded." << std::endl;
}

int main() {
    auto coursesBst = std::make_unique<Courses>();
    std::string inputPath, courseKey;
    int choice = 0;

    while (choice != 9) {
        std::cout << "  1. Load Data Structure\n";
        std::cout << "  2. Print Course List\n";
        std::cout << "  3. Search Course (BST)\n";
        std::cout << "  4. Search Course (HashMap)\n";
        std::cout << "  5. Sort Course List by Merge Sort\n";
        std::cout << "  9. Exit\n";
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        try {
            switch (choice) {
            case 1:
                std::cout << "Enter the path to the input file: ";
                std::cin >> inputPath;
                loadCourses(inputPath, coursesBst);
                break;

            case 2:
                std::cout << "Here is the sorted course list:" << std::endl;
                coursesBst->InOrder();
                break;

            case 3:
                std::cout << "Enter the course ID to search (BST): ";
                std::cin >> courseKey;
                std::transform(courseKey.begin(), courseKey.end(), courseKey.begin(), ::toupper);
                displayCourse(coursesBst->Search(courseKey));
                break;

            case 4:
                std::cout << "Enter the course ID to search (HashMap): ";
                std::cin >> courseKey;
                std::transform(courseKey.begin(), courseKey.end(), courseKey.begin(), ::toupper);
                displayCourse(coursesBst->SearchInMap(courseKey));
                break;

            case 5:
                coursesBst->sortCoursesByMergeSort();
                break;

            case 9:
                std::cout << "Are you sure you want to exit? (y/n): ";
                char confirm;
                std::cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    std::cout << "Goodbye!" << std::endl;
                    return 0;
                }
                break;

            default:
                std::cerr << "Invalid option. Please try again." << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
