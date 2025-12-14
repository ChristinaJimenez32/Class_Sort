//libraries included
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
using namespace std;

// Structure to store course information
struct Course {
    string courseNumber;               // Course number
    string courseTitle;                // Course title
    vector<string> prerequisites;      // List of prerequisites

    Course() {}                        // Constructor
    Course(string num, string title) : courseNumber(num), courseTitle(title) {}
};

// Binary Search Tree node structure
struct BSTNode {
    Course course; // cpurse data
    BSTNode* left; // left child 
    BSTNode* right; //right child 

    BSTNode(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// BST class
class BST {
private:
    BSTNode* root;

    // Helper function for inserting a node
    BSTNode* insertNode(BSTNode* node, Course course) {
        if (node == nullptr) { // if found empty , insert here 
            return new BSTNode(course);
        }

        if (course.courseNumber < node->course.courseNumber) {
            node->left = insertNode(node->left, course); // go left
        } else if (course.courseNumber > node->course.courseNumber) {
            node->right = insertNode(node->right, course); // go right
        }

        return node;
    }

    // Helper function for in order traversal
    void inOrderTraversal(BSTNode* node) const {
        if (node == nullptr) return;

        inOrderTraversal(node->left);
        cout << node->course.courseNumber << ", " // prints course number
        << node->course.courseTitle << endl; // prints course title
        inOrderTraversal(node->right);
    }

    // Helper function to search
    BSTNode* searchNode(BSTNode* node, const string& courseNumber) const {
        if (node == nullptr || node->course.courseNumber == courseNumber) {
            return node; // found or reached end 
        }

        if (courseNumber < node->course.courseNumber) {
            return searchNode(node->left, courseNumber); //search left
        } else {
            return searchNode(node->right, courseNumber); //search right
        }
    }

    // Helper function to delete the tree
    void deleteTree(BSTNode* node) {
        if (node == nullptr) return;
        deleteTree(node->left); // delete left subtree
        deleteTree(node->right); // delete right subtree
        delete node; // delete current node
    }

public:
    BST() : root(nullptr) {} //constructor 

    ~BST() {
        deleteTree(root);
    }

    // Public insert function
    void insert(Course course) {
        root = insertNode(root, course);
    }

    // Public function prints in order
    void printInOrder() const {
        if (root == nullptr) { // check if empty
            cout << "No courses loaded." << endl;
            return;
        }
        cout << "Courses:" << endl;
        inOrderTraversal(root);
    }

    // Public search function
    Course* search(const string& courseNumber) {
        BSTNode* node = searchNode(root, courseNumber);
        return (node != nullptr) ? &(node->course) : nullptr;
    }

    // isEmpty function
    bool isEmpty() const {
        return root == nullptr;
    }
};

// Global data structures
BST courseTree;                                    //  sets up BST
unordered_map<string, Course*> courseHashTable;   // Hash table for lookup 

// Function validates prerequisites
bool validatePrerequisites(const Course& course) {
    for (const string& prereq : course.prerequisites) {
        if (courseHashTable.find(prereq) == courseHashTable.end()) {
            cout << "Warning: Prerequisite '" << prereq 
                 << "' for course " << course.courseNumber 
                 << " does not exist in the system." << endl;
            return false;
        }
    }
    return true;
}

// Function to load data from a file into the BST and hash table
void loadDataStructure(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Unable to open file: " << fileName << endl;
        return;
    }

    vector<Course> tempCourses;  // Temporary storage 
    string line;
    int lineNumber = 0;

    // Load all courses
    while (getline(file, line)) {
        lineNumber++;
        if (line.empty()) continue;  // Skip empty lines

        Course course;
        stringstream ss(line);
        string token;

        // Parse course number
        if (!getline(ss, token, ',')) {
            cout << "Error: Invalid format at line " << lineNumber << endl;
            continue;
        }
        course.courseNumber = token;

        // Parse course title
        if (!getline(ss, token, ',')) {
            cout << "Error: Missing course title at line " << lineNumber << endl;
            continue;
        }
        course.courseTitle = token;

        // Parse prerequisites
        while (getline(ss, token, ',')) {
            
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            if (!token.empty()) {
                course.prerequisites.push_back(token);
            }
        }

        tempCourses.push_back(course);
    }

    file.close();

    if (tempCourses.empty()) {
        cout << "No valid courses found in file." << endl;
        return;
    }

    // Insert all courses into BST and hash table
    for (auto& course : tempCourses) {
        courseTree.insert(course);
        Course* searchResult = courseTree.search(course.courseNumber);
        if (searchResult != nullptr) {
            courseHashTable[course.courseNumber] = searchResult;
        }
    }

    cout << "Data loaded successfully. " << tempCourses.size() << " courses loaded." << endl;

    // Validate prerequisites
    cout << "\nValidating prerequisites..." << endl;
    bool allValid = true;
    for (const auto& course : tempCourses) {
        if (!course.prerequisites.empty()) {
            if (!validatePrerequisites(course)) {
                allValid = false;
            }
        }
    }

    if (allValid) {
        cout << "All prerequisites are valid." << endl;
    } else {
        cout << "Some prerequisite validation issues were found." << endl;
    }
}

// Function to print the list of courses  in sorted order
void printCourseList() {
    courseTree.printInOrder();  // BST traversal
}

// Function to print details of course
void printCourse(const string& courseNumber) {
    if (courseTree.isEmpty()) {
        cout << "No courses loaded." << endl;
        return;
    }

    // Use hash table for lookup
    auto it = courseHashTable.find(courseNumber);
    
    if (it != courseHashTable.end()) {
        Course* course = it->second; // get course pointer
        cout << course->courseNumber << ", " << course->courseTitle << endl;
        cout << "Prerequisites: ";
        
        if (course->prerequisites.empty()) {
            cout << "None" << endl;
        } else {
            for (size_t i = 0; i < course->prerequisites.size(); ++i) {
                cout << course->prerequisites[i];
                if (i < course->prerequisites.size() - 1) cout << ", ";
            }
            cout << endl;
        }
    } else {
        cout << "Course not found." << endl;
    }
}



int main() {
    string fileName;
    int choice;
    string courseNumber;

    cout << "Welcome to the Course Planner System" << endl;
   

    do {
        // Display menu options
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "4. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter the file name: ";
                cin >> fileName;
                loadDataStructure(fileName);
                break;
            case 2:
                printCourseList();
                break;
            case 3:
                cout << "What course do you want information on? ";
                cin >> courseNumber;
                printCourse(courseNumber);
                break;
            case 4:
                cout << "Exiting program. Thank you!" << endl;
                break;
            default:
                cout << choice << " is not a valid option." << endl;
        }
    } while (choice != 4);

    return 0;
}