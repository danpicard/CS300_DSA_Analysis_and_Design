//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Daniel Picard
// Version     : 1.0
// Description : Develop code using algorithms and data structures to solve 
//               basic programming problems
//============================================================================

#include <iostream>                                                                         // for input/output
#include <vector>                                                                           // for using the vector container
#include <time.h>                                                                           // for measuring execution time
#include <algorithm>                                                                        // for using the transform function to convert strings to uppercase
#include <string>                                                                           // for using the string class
#include <fstream>                                                                          // for file input/output
#include <limits>                                                                           // for numeric limits, used in input validation

using namespace std;                                                                        // to avoid having to write std:: before every standard library type or function


/***************************************************************************************
*                           Course structure
***************************************************************************************/
/* ---
 * 
 * @brief Holds information about a course, including its course number, 
 *        title, and prerequisites.
 * 
 * ---
 * 
 * i.e.: 
 *
 *      course number - "CSCI100"
 * 
 *      title - "Introduction to Computer Science"
 * 
 *      prerequisites - "MATH201", "CSCI350"
 */
struct Course {
	string courseNumber;                                                                   
	string title;                                                                          
	vector<string> prerequisites;                                                           
};


/***************************************************************************************
*                          BST Node structure
***************************************************************************************/
/*---
* @brief Represents a node in the binary search tree, 
* containing a course and pointers to left and right child nodes.
* 
* ---
* 
* constructor takes a Course object and initializes the node with it,
* setting the left and right child pointers to nullptr.
*/
struct Node {
	Course course;                                                                         
	Node* left;                                                                             
	Node* right;                                                                           

    /*
    * @brief Constructor initializes the node with a Course object.
    * @param courseIn - The Course object to be stored in the node.
    */
	Node(Course courseIn) {                                                                 
		this->course = courseIn;                                                           
        left = nullptr;                                                         
        right = nullptr;
    }
};


/***************************************************************************************
*                           BST Class
***************************************************************************************/
/*---
* @brief Represents a binary search tree (BST) for storing courses.
* 
* ---
* 
* constructor initializes the root to nullptr.
*/
class BinarySearchTree {
private:
    
    Node* root;

    /*
	* @brief Helper function to insert a course into the BST.
	* @param node - The current node being processed for insertion.
	* @param course - The Course object to be inserted into the BST.
    */
    Node* insert(Node* node, Course course) {
        if (node == nullptr) {
            return new Node(course);                                                        // if the current node is null retuen a new node with the current cours
        }

        if (course.courseNumber < node->course.courseNumber) {                              // if the current course courseNumber is less (alphanumerically) then the current node
            node->left = insert(node->left, course);                                        // move left down the tree and try again
        }
        else {
            node->right = insert(node->right, course);                                      // else move right down the tree and try again
        }

        return node;                                                                        // return the node to be placed in the tree
    }


    /*
	* @brief Helper function to perform in-order traversal of the BST and print courses.
	* @param node - The current node being processed in the traversal.
    */
    void inOrder(Node* node) {
        if (node != nullptr) {                                                              // as long as the current nod isnt null (root or leaf)
            inOrder(node->left);                                                            // recusively move left down the tree
            cout << node->course.courseNumber << ", "                                       // once at the bottom print the course number
                << node->course.title << endl;                                              // and course title

            inOrder(node->right);                                                           // now move right if possible and repeat
        }
    }


    /*
	* @brief Helper function to search for a course in the BST by course number.
	* @param node - The current node being processed in the search.
	* @param courseNumber - The course number to search for.
    */
    Course search(Node* node, string courseNumber) {
        while (node != nullptr) {                                                           // as long as the current node is not the root or a leaf
            if (courseNumber == node->course.courseNumber) {                                // if the current node course number matches
                return node->course;                                                        // send back the course
            }

            if (courseNumber < node->course.courseNumber) {                                 // if the course number is less than the current nodes
                node = node->left;                                                          // move left down the tree
            }
            else {
                node = node->right;                                                         // else move right down the tree
            }
        }

        Course emptyCourse;                                                                 // if you make it this far a match was not found
        emptyCourse.courseNumber = "";                                                      // make an empty course
        return emptyCourse;                                                                 // and send that back
    }


    /*
	* @brief Helper function to destroy the BST and free memory.
	* @param node - The current node being processed for deletion.
    */
    void destroyTree(Node* node) {                                                          // destroy each node recusively
        if (node != nullptr) {          
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:

    /*
	* @brief Constructor initializes the root of the BST to nullptr.
    */
    BinarySearchTree() {
        root = nullptr;
    }


    /*
	* @brief Destructor destroys the BST and frees memory.
    */
    ~BinarySearchTree() {
        destroyTree(root);
    }


    /*
	* @brief Public method to insert a course into the BST, which calls the private insert helper function.
	* @param course - The Course object to be inserted into the BST.
    */
    void Insert(Course course) {
        root = insert(root, course);
    }


    /*
	* @brief Public method to print all courses in the BST in order, which calls the private inOrder helper function.
    */
    void PrintAllCourses() {
        inOrder(root);
    }


    /*
	* @brief Public method to search for a course in the BST by course number, which calls the private search helper function.
    */
    Course Search(string courseNumber) {
        return search(root, courseNumber);
    }


    /*
	* @brief Public method to check if the BST is empty (i.e., if the root is nullptr).
    */
    bool IsEmpty() {
        return root == nullptr;
    }


    /*
	* @brief Public method to clear the BST by destroying all nodes and setting the root to nullptr.
    */
    void Clear() {
        destroyTree(root);
        root = nullptr;
    }
};


/*
* @brief Check if a course with the given course number exists in the provided vector of courses.
* @param courses - A vector of Course objects to search through.
* @param courseNumber - The course number to check for existence.
* @return True if the course exists, false otherwise.
*/
bool courseExists(vector<Course>& courses, string courseNumber) {
    for (Course& c : courses) {
        if (c.courseNumber == courseNumber) {
            return true;
        }
    }
    return false;
}


/*
* @brief Split a line of text from the CSV file into tokens based on commas.
* @param line - The line of text to be split.
* @return A vector of strings, where each string is a token from the line.
*/
vector<string> splitLine(string line) {
    
    vector<string> tokens;                                                                  // each token is one datum of the course data

    size_t start = 0;
    size_t commaPos = line.find(',');

    while (commaPos != string::npos) {
        tokens.push_back(line.substr(start, commaPos - start));
        start = commaPos + 1;
        commaPos = line.find(',', start);
    }

    tokens.push_back(line.substr(start));
    return tokens;                                                                          // return all the data in the line as a vector
}

/*
* @brief Convert a string to uppercase.
* @param text - The string to be converted to uppercase.
* @return The input string converted to uppercase.
*/
string toUpperCase(string text) {
    transform(text.begin(), text.end(), text.begin(), ::toupper);
    return text;
}


/*
* @brief Clear the input stream and return the cleared line as a string.
*/
string clearInput() {
	string trashLine;
	std::cin.clear();
	getline(cin, trashLine);
	return trashLine;
}


/*
* @brief Load courses from a CSV file into the binary search tree.
* @param filePath - The path to the CSV file containing course data.
* @param courseTree - The binary search tree to insert the courses into.
* @return True if the courses were loaded successfully, false if there was an error opening the file.
*/
bool loadCoursesFromFile(string filePath, BinarySearchTree& courseTree) {
    
    ifstream file;
    file.open(filePath);

    vector<Course> allCourses;                                                              // Need a list of all courses for validation    
    string line;

    if (!file.is_open()) {
        cout << "Error: could not open file." << endl;
        return false;
    }

    courseTree.Clear();                                                                     // make sure we are working with a clear tree

    while (getline(file, line)) {                                                           // this will loop each line of the csv
        vector<string> rowData = splitLine(line);                                           // create a vector of each line item

		// Validate row format
        if (rowData.size() < 2) {                                                           // must have at least 2 items to be a valid course
            cout << "Invalid row format" << endl;
        }
        else {
            Course course;                                                                  // a course can be created now that the first validation has passed
            course.courseNumber = toUpperCase(rowData[0]);                                  // store the course numbers in uppercase for consistancy
            course.title = rowData[1];

            for (int i = 2; i < (int)rowData.size(); i++) {                                 // if there are more than 2 items those are prereqs
                rowData[i] = toUpperCase(rowData[i]);                                       // make them uppercase to match the other course numbers
                if (rowData[i] != "") {                                                     // as long as it isn't a blank item
                    course.prerequisites.push_back(rowData[i]);                             // store it as an item, it will be validated later
                }
            }

            allCourses.push_back(course);                                                   // course data collection is complete add it to the course list
        }
    }

    // Validate prerequisites and insert 
    for (int i = 0; i < (int)allCourses.size(); i++) {                                      // now we have to validate each prereq
        bool isValid = true;                                                                // assume they are valid until prove otherwise

        for (int j = 0; j < (int)allCourses[i].prerequisites.size(); j++) {                 // loop each prereq for the course
            if (!courseExists(allCourses, allCourses[i].prerequisites[j])) {                // check if the prereq exists in the course list
                cout << "Invalid prerequisite for " << 
                    allCourses[i].courseNumber << endl;

                isValid = false;                                                            // no longer valid if not found
                break;                                                                      // no need to look at any others the course is already invalid
            }
        }

        if (isValid) {                                                                      // if all the course prereqs remain valid
            courseTree.Insert(allCourses[i]);                                               // the course can now be inserted into the tree
        }
    }

    file.close();                                                                           
    cout << "Courses loaded successfully." << endl;
    return true;
}


/*
* @brief Print the details of a course, including its course number, title, and prerequisites. If the course is not found, inform the user.
* @param course - The course to be printed.
* @param courseTree - The binary search tree containing all courses.
*/
void printCourse(Course course, BinarySearchTree& courseTree) {
    
    if (course.courseNumber == "") {                                                        // if a blank course is sent to print
        cout << "Course not found." << endl;                                                // inform the user
        return;                                                                             // return, no need to waste any time    
    }

    cout << course.courseNumber << ", " << course.title << endl;        

    if (course.prerequisites.size() == 0) {                                                 // no prereqs in the list for this course
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";

        for (int i = 0; i < (int)course.prerequisites.size(); i++) {                        // if the course has prereqs, loop them all
            //Course prereqCourse = 
            //    courseTree.Search(course.prerequisites[i]);

            cout << course.prerequisites[i];

            if (i < (int)course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }

        cout << endl;
    }
}


/*
* @brief Display the details of a singlecourse, including its course number, title, and prerequisites
* @param course - The Course object whose details are to be displayed.
*/
void displayCourse(const Course& course) {
    
    cout << endl;
    cout << "Course Number: " << course.courseNumber << endl;
    cout << "Course Title: " << course.title << endl;
    cout << "Prerequisites: ";
    
    for (const string& prereq : course.prerequisites) {
        cout << prereq << " ";
    }
    
    cout << endl;
}


/*
* @brief Get the file path from command line arguments or user input
* @param argc - The number of command line arguments passed to the program.
* @param argv - The array of command line arguments passed to the program.
* @return The file path to the CSV course data, either from command line arguments or user input.
*/
string getPath(const int argc, const string& argv) {
	
    string csvPath;
    
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    
    default:
        cout << "Enter file path to the CSV course data: ";
        getline(cin, csvPath);
    }
	
    return csvPath;
}


/*
* @brief Display the menu of options to the user
*/
void displayMenu() {
    
    cout << endl;
    cout << "  1. Load Courses to Binary Search Tree" << endl;
    cout << "  2. Display All Courses in Order" << endl;
    cout << "  3. Display Prerequisites for a Course" << endl;
    cout << "  9. Exit" << endl << endl;
}



/*
* @brief Get the user's menu choice
* @return The integer value representing the user's menu choice.
*/
int getUserChoice() {
    
    int choice;
    cout << "Enter choice: ";
    cin >> choice;
	return choice;
}



/*
* @brief Main function to run the course planner program
* @param csvPath - The file path to the CSV course data, passed as an argument to the function.
* @return 0 if the program runs successfully, or a non-zero value if there is an error.
*/
int runProjectTwo(string csvPath) {
    
    BinarySearchTree courseTree;
    string filePath;
    int optionSelected = -1;
    
    filePath = csvPath;
	
    cout << endl << "Welcome to the course planner!" << endl;

    while (optionSelected != 9) {
 
        displayMenu();
        
        cout << "What would you like to do? ";
        cin >> optionSelected;

        switch (optionSelected) {
        
        case 1:
            loadCoursesFromFile(filePath, courseTree);
            break;

        case 2:
            if (!courseTree.IsEmpty()) {
                cout << endl;
                cout << "Here is a sample schedule:" << endl << endl;
                courseTree.PrintAllCourses();
            }
            else {
                cout << "Courses not loaded." << endl;
            }
            break;

        case 3:
            if (!courseTree.IsEmpty()) {
                string courseNumber;
                cout << "What course do you want to know about? ";
                cin >> courseNumber;

                transform(
                    courseNumber.begin(), 
                    courseNumber.end(), 
                    courseNumber.begin(), 
                    ::toupper
                );

                Course foundCourse = courseTree.Search(courseNumber);
        
                printCourse(foundCourse, courseTree);
            }
            else {
                cout << "Courses not loaded." << endl;
            }
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:

            
            if (cin.fail()) {
                
                cout <<  clearInput() << " is not a valid option." << endl;
            }
            else {

                cout << optionSelected << clearInput() << " is not a valid option." << endl;
            }

            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    //courseTree.~BinarySearchTree();
    cout << "Good bye." << endl;
    
    return 0;
}


/*
* @brief Entry point of the program
* @param argc - The number of command line arguments passed to the program.
* @param argv - The array of command line arguments passed to the program.
* @return 0 if the program runs successfully, or a non-zero value if there is an error.
*/
int main(int argc, char* argv[])
{
    return runProjectTwo(getPath(argc, *argv));	
}
