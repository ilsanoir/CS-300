//============================================================================
// Name        : Advising Assistance.cpp
// Author      : Similoluwa Adeyemi
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// Structure for Course information
struct Course {
    string courseNum; // unique identifier
    string courseName;
    vector<string> preReq;
    Course() {}
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void printSchedule(Node* node);
    void printCourseInfo(Node* node, string courseNum);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(Course course);
    void RecursiveDelete(Node* node);
    void PrintSchedule();
    void PrintCourseInfo(string courseNum);
    int PreReqCounter(Course course);
};

//Public methods
//Default constructor
BinarySearchTree::BinarySearchTree() {
    //Initialize Binary Tree roots
    Node* root = nullptr;
}

//Destructor
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node   
    RecursiveDelete(root);
}

//If a node exists, delete the node, starting from the root
void BinarySearchTree::RecursiveDelete(Node* node) {
    if (node) {
        RecursiveDelete(node->right);
        RecursiveDelete(node->left);
        delete(node);
    }

}

//Insert a course
void BinarySearchTree::Insert(Course course) {
    // if root equarl to null ptr
      // root is equal to new node course
    // else
      // add Node root and course
    if (root == nullptr) {
        root = new Node(course);
    }

    else {
        this->addNode(root, course);
    }
}

//Count the number of prerequsites a course has
int BinarySearchTree::PreReqCounter(Course course) {
    int count = 0;
    for (int i = 0; i < course.preReq.size(); i++) {
        count++;
    }
    return count;
}

//Pass to private
void BinarySearchTree::PrintCourseInfo(string courseNum) {
    this->printCourseInfo(root, courseNum);
}

//Pass to private
void BinarySearchTree::PrintSchedule() {
    this->printSchedule(root);
}


//Private methods
/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param Course course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // if node is larger then add to left
        // if no left node
            // this node becomes left
        // else recurse down the left node
    // else
        // if no right node
            // this node becomes right
        //else
            // recurse down the left node
    if (node->course.courseNum < course.courseNum) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            this->addNode(node->left, course);
        }
    }

    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            this->addNode(node->left, course);
        }
    }

}


//Print schedule starting from root node 
void BinarySearchTree::printSchedule(Node* node) {
    if (node != nullptr) {
        printSchedule(node->left);
        cout << node->course.courseNum << ", " << node->course.courseName << endl;
        printSchedule(node->right);
    }
    return;
}

void BinarySearchTree::printCourseInfo(Node* curr, string courseNum) {
    //Search tree until course is found or bottom is reached 
    Node* curr = root;

    while (curr != nullptr) {
        if (curr->course.courseNum == courseNum) {
            cout << curr->course.courseNum << ", " << curr->course.courseName << endl;
        }

        //Check for prereq
        int size = PreReqCounter(curr->course);
        cout << "Prerequisite(s): ";
        for (int i = 0; i < size; i++) {
            cout << curr->course.preReq.at(i);
        }

        if (size == 0) {
            cout << "No prerequisites found.";
        }

        if (curr->course.courseNum < courseNum) {
            curr = curr->left;
        }

        else {
            curr = curr->right;
        }
    }

    //If no course is found return error
    cout << "Error, course not found, try again" << endl;

}

//============================================================================
// Static methods used for testing
//============================================================================
//Should open and read course file. Should.
bool loadCourses(string csvPath, BinarySearchTree* coursesBST) {
    vector<string> courseInfo;
    string courseData;

    try {
        ifstream courseFile(csvPath);

        if (courseFile.is_open()) {
            while (!courseFile.eof()) {
                

                getline(courseFile, courseData);
                while (courseData.length() > 0) {
                    unsigned int comma = courseData.find(',');
                    if (comma < 100) {
                        courseInfo.push_back(courseData.substr(0, comma));
                        courseData.erase(0, comma + 1);
                    }
                    else {
                        courseInfo.push_back(courseData.substr(0, courseData.length()));
                        courseData = "";
                    }
                }
            }

                Course course;
                course.courseNum = courseInfo[0];
                course.courseName = courseInfo[1];

                for (int i = 2; i < courseInfo.size(); i++) {
                    course.preReq.push_back(courseInfo[i]);
                }
                coursesBST->Insert(course);
                courseFile.close();
                return true;
            }
        }
        catch (csv::Error& e) {
            cerr << e.what() << endl;
        }
        return false;
    }

//Main
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    string courseId;

    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    case 3:
        csvPath = argv[1];
        courseId = argv[2];
        break;
    default:
        csvPath = "";
        break;
    }

    // Define a binary search tree for courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    //Menu and user input acceptance
    int choice = 0;
    while (choice != 9) {
        cout << "Welcome to the course planner." << endl;
        cout << "  1. Load Data Structre." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit" << endl;
        cout << endl << "What would you like to do? ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Complete the method call to load the courses
            if(csvPath.length() == 0){
                cout << "Enter file name: ";
                cin >> csvPath;
            }

            loadCourses(csvPath, bst);
            break;

        case 2:
            //Call print schedule method
            cout << "Here is a sample schedule: " << endl << endl;
            bst->PrintSchedule();
            break;

        case 3:
            //Pass user input to find and print course info
            cout << "What course do you want to know about? ";
            cin >> courseId;
            bst->PrintCourseInfo(courseId);
            break;
        }
    }

    cout << "Thank you for using the course planner!" << endl; //Exit

    return 0;
}
