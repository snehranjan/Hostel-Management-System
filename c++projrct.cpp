/*
 * PROJECT: HOSTEL MANAGEMENT SYSTEM
 * LANGUAGE: C++
 * 
 * DESCRIPTION:
 * This is a fully functional Hostel Management System console application.
 * It demonstrates key C++ concepts such as Classes, Objects, File Handling,
 * Loops, Conditionals, and Standard I/O.
 * 
 * Each section is heavily commented to explain:
 * 1. The Syntax used.
 * 2. The Name of the Concept.
 * 3. What it does to the code.
 * 4. Why it is used.
 */

// --------------------------------------------------------------------------------------
// CONCEPT: Preprocessor Directives
// SYNTAX: #include <header_file>
// EXPLANATION: Includes standard libraries needed for input/output and file operations.
// --------------------------------------------------------------------------------------
#include <iostream>  // For standard Input/Output (cin, cout)
#include <fstream>   // For File Handling (ifstream, ofstream)
#include <string>    // For string manipulation
#include <cstdlib>   // For system() calls (e.g., cls, pause)
#include <cstdio>    // For remove() and rename() functions

// CONCEPT: Namespace
// SYNTAX: using namespace std;
// EXPLANATION: Allows us to use standard objects like 'cout' and 'cin' directly 
// without prefixing them with 'std::'.
using namespace std;

// --------------------------------------------------------------------------------------
// CONCEPT: Class (Object-Oriented Programming)
// SYNTAX: class ClassName { ... };
// EXPLANATION: A class is a blueprint for creating objects. It encapsulates data 
// (variables) and behavior (functions) into a single unit.
// --------------------------------------------------------------------------------------
class Student {
private:
    // CONCEPT: Access Specifiers (private)
    // EXPLANATION: These variables are hidden from outside the class. 
    // Data Hiding ensures security and integrity of data.
    string rollNo;
    string name;
    string phone;
    string address;

public:
    // CONCEPT: Access Specifiers (public)
    // EXPLANATION: These functions are accessible from outside the class (e.g., main function).

    // CONCEPT: Constructor
    // SYNTAX: ClassName() { ... }
    // EXPLANATION: A special function called automatically when an object is created.
    // Used here to initialize variables.
    Student() : rollNo(""), name(""), phone(""), address("") {}

    // FUNCTION: setData
    // PURPOSE: Captures input from the user to populate the object's data.
    void setData() {
        // CONCEPT: Output Stream (cout)
        // SYNTAX: cout << "message";
        // EXPLANATION: Prints text to the console screen.
        cout << "\n------------------------------------";
        cout << "\n Enter Student Details";
        cout << "\n------------------------------------";
        
        cout << "\n Enter Roll No: ";
        // CONCEPT: Input Stream (cin)
        // SYNTAX: cin >> variable;
        // EXPLANATION: Reads input from the keyboard and stores it in the variable.
        cin >> rollNo;
        cin.ignore(); // CONCEPT: Input Buffer Clearing. Clears newline character left by cin.

        cout << " Enter Name: ";
        // CONCEPT: getline
        // SYNTAX: getline(cin, string_variable);
        // EXPLANATION: Reads a whole line of text (including spaces) from input.
        getline(cin, name);

        cout << " Enter Phone: ";
        cin >> phone;
        cin.ignore();

        cout << " Enter Address: ";
        getline(cin, address);
    }

    // FUNCTION: showData
    // PURPOSE: Displays the object's data to the console.
    void showData() {
        cout << "\n------------------------------------";
        cout << "\n Roll No  : " << rollNo;
        cout << "\n Name     : " << name;
        cout << "\n Phone    : " << phone;
        cout << "\n Address  : " << address;
        cout << "\n------------------------------------";
    }

    // FUNCTION: getRollNo
    // PURPOSE: Getter function to access private 'rollNo' for searching/validation.
    string getRollNo() {
        return rollNo;
    }
    
    // FUNCTION: saveToFile
    // PURPOSE: Writes the student object data to a text file.
    // CONCEPT: File I/O
    void saveToFile() {
        // CONCEPT: ofstream (Output File Stream)
        // SYNTAX: ofstream objectName("filename", mode);
        // EXPLANATION: specific class to write on files.
        // ios::app means 'Append Mode', adding new data to the end of the file without deleting old data.
        ofstream outFile("hostel_data.txt", ios::app);
        
        // Writing data separated by newlines for easy reading later
        outFile << rollNo << "\n" << name << "\n" << phone << "\n" << address << "\n";
        
        outFile.close(); // Always close the file to save changes.
        cout << "\n [SUCCESS] Student Record Added Successfully!";
    }
};

// --------------------------------------------------------------------------------------
// FUNCTION: addStudent
// PURPOSE: Global function to handle the 'Add' operation flow.
// --------------------------------------------------------------------------------------
void addStudent() {
    Student s;        // CONCEPT: Object Instantiation. Creating an instance 's' of class Student.
    s.setData();      // Calling member function to get input.
    s.saveToFile();   // Calling member function to save to file.
}

// --------------------------------------------------------------------------------------
// FUNCTION: readAllStudents
// PURPOSE: Reads and displays all records from the file.
// --------------------------------------------------------------------------------------
void readAllStudents() {
    // CONCEPT: ifstream (Input File Stream)
    // SYNTAX: ifstream objectName("filename");
    // EXPLANATION: specific class to read from files.
    ifstream inFile("hostel_data.txt");
    
    if (!inFile) { // CONCEPT: Error Handling. Checking if file exists.
        cout << "\n [ERROR] File not found or no data exists.";
        return;
    }

    Student s; // Temporary object to hold data while reading
    
    // Variables to hold data temporarily read from file
    string r, n, p, a;
    
    cout << "\n\n\t\t ALL STUDENTS RECORD \n";
    
    // CONCEPT: While Loop with File Reading
    // EXPLANATION: Loops as long as we successfully read a 'rollNo' from the file.
    // The >> operator and getline return the stream itself, which evaluates to false at End Of File (EOF).
    while (inFile >> r) {
        inFile.ignore(); // clear buffer
        getline(inFile, n);
        inFile >> p;
        inFile.ignore();
        getline(inFile, a);
        
        // We manually print here because our object's data members are private
        // and we haven't implemented a 'load from parameters' method for simplicity.
        cout << "\n------------------------------------";
        cout << "\n Roll No  : " << r;
        cout << "\n Name     : " << n;
        cout << "\n Phone    : " << p;
        cout << "\n Address  : " << a;
        cout << "\n------------------------------------";
    }
    
    inFile.close();
}

// --------------------------------------------------------------------------------------
// FUNCTION: searchStudent
// PURPOSE: Search for a specific student by Roll No.
// --------------------------------------------------------------------------------------
void searchStudent() {
    ifstream inFile("hostel_data.txt");
    if (!inFile) {
        cout << "\n [ERROR] No data available.";
        return;
    }

    string searchRoll;
    cout << "\n Enter Roll No to Search: ";
    cin >> searchRoll;

    string r, n, p, a;
    bool found = false; // CONCEPT: Boolean Flag. Tracks if we found the record.

    while (inFile >> r) {
        inFile.ignore();
        getline(inFile, n);
        inFile >> p;
        inFile.ignore();
        getline(inFile, a);

        // CONCEPT: String Comparison
        // EXPLANATION: Checks if the read rollNo matches the search term.
        if (r == searchRoll) {
            cout << "\n [FOUND] Student Found!";
            cout << "\n------------------------------------";
            cout << "\n Roll No  : " << r;
            cout << "\n Name     : " << n;
            cout << "\n Phone    : " << p;
            cout << "\n Address  : " << a;
            cout << "\n------------------------------------";
            found = true;
            break; // CONCEPT: Break Statement. Exits the loop immediately since we found the target.
        }
    }

    if (!found) {
        cout << "\n [NOT FOUND] Student with Roll No " << searchRoll << " is not in the record.";
    }
    
    inFile.close();
}

// --------------------------------------------------------------------------------------
// FUNCTION: updateStudent
// PURPOSE: Update details of an existing student.
// OPERATION: Read all data, modify the target, write all data back to a temporary file, 
// then rename it.
// --------------------------------------------------------------------------------------
void updateStudent() {
    string searchRoll;
    cout << "\n Enter Roll No to Update: ";
    cin >> searchRoll;

    ifstream inFile("hostel_data.txt");
    ofstream outFile("temp.txt"); // Temporary file to write updated data

    string r, n, p, a;
    bool found = false;

    while (inFile >> r) {
        inFile.ignore();
        getline(inFile, n);
        inFile >> p;
        inFile.ignore();
        getline(inFile, a);

        if (r == searchRoll) {
            cout << "\n [FOUND] Record found. Enter New Details.";
            // Getting new input
            cout << "\n New Name: ";
            getline(cin, n);
            cout << " New Phone: ";
            cin >> p;
            cin.ignore();
            cout << " New Address: ";
            getline(cin, a);
            found = true;
        }
        
        // Write (potentially updated) data to temp file
        outFile << r << "\n" << n << "\n" << p << "\n" << a << "\n";
    }

    inFile.close();
    outFile.close();

    // Remove old file and rename temp file to original
    if (found) {
        remove("hostel_data.txt");
        rename("temp.txt", "hostel_data.txt");
        cout << "\n [SUCCESS] Record Updated Successfully.";
    } else {
        remove("temp.txt"); // Delete temp if nothing was effectively done
        cout << "\n [NOT FOUND] Record not found.";
    }
}

// --------------------------------------------------------------------------------------
// FUNCTION: deleteStudent
// PURPOSE: Delete a student record using the same Copy-and-Rename strategy.
// --------------------------------------------------------------------------------------
void deleteStudent() {
    string searchRoll;
    cout << "\n Enter Roll No to Delete: ";
    cin >> searchRoll;

    ifstream inFile("hostel_data.txt");
    ofstream outFile("temp.txt");

    string r, n, p, a;
    bool found = false;

    while (inFile >> r) {
        inFile.ignore();
        getline(inFile, n);
        inFile >> p;
        inFile.ignore();
        getline(inFile, a);

        if (r == searchRoll) {
            // CONCEPT: Logic Skipping
            // EXPLANATION: If we find the student to delete, we simply set found = true
            // and DO NOT write it to the new file. Thus, it is removed.
            found = true;
            cout << "\n [DELETED] Record with Roll No " << r << " has been deleted.";
        } else {
            // Write validation records to temp file
            outFile << r << "\n" << n << "\n" << p << "\n" << a << "\n";
        }
    }

    inFile.close();
    outFile.close();

    if (found) {
        remove("hostel_data.txt");
        rename("temp.txt", "hostel_data.txt");
    } else {
        remove("temp.txt");
        cout << "\n [NOT FOUND] Record not found.";
    }
}

// --------------------------------------------------------------------------------------
// FUNCTION: main
// PURPOSE: The entry point of the program. Handles the Menu loop.
// --------------------------------------------------------------------------------------
int main() {
    int choice;
    
    // CONCEPT: Infinite Loop (controlled by user choice)
    // EXPLANATION: 'while(true)' runs forever until the 'exit(0)' command is encountered.
    while (true) {
        // system("cls"); // Optional: Clears screen (Windows only). Un-comment if needed locally.
        
        cout << "\n\n==========================================";
        cout << "\n       HOSTEL MANAGEMENT SYSTEM";
        cout << "\n==========================================";
        cout << "\n 1. Add New Student";
        cout << "\n 2. Process All Records (View)";
        cout << "\n 3. Search Student";
        cout << "\n 4. Update Student";
        cout << "\n 5. Delete Student";
        cout << "\n 6. Exit";
        cout << "\n------------------------------------------";
        cout << "\n Enter Your Choice: ";
        cin >> choice;

        // CONCEPT: Switch Case
        // SYNTAX: switch(variable) { case x: code; break; ... }
        // EXPLANATION: Selects one block of code to execute based on the value of 'choice'.
        // Better than multiple if-else statements for menus.
        switch (choice) {
            case 1:
                addStudent();
                break; // CONCEPT: break. Prevents falling through to next case.
            case 2:
                readAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                cout << "\n Thank you for using the application!";
                exit(0); // CONCEPT: exit(). Terminates the entire program immediately.
            default:
                cout << "\n [INVALID] Please enter a valid option (1-6).";
        }
        
        // system("pause"); // Optional: Waits for key press (Windows only).
    }
    
    return 0;
}
