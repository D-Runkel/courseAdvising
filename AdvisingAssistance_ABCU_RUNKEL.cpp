// AdvisingAssistance_ABCU_RUNKEL.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 
// Author: Dustin Runkel
// Date: 08/09/2022
// Last updated: 08/09/2022
// Description: Main driver for the ABCU advising assistance system
// 
//

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include "binaryTree.h"


int main()
{
    //general variables to help with user input
    BinaryTree BST;
    string path = "courses.csv";
    char userInput;
    string temp;
    Course tmpC;
    bool CSVparsed = false;

menu:

    cout << setfill('*') << setw(30) << "";
    cout << "\nMAIN MENU\n";
    cout << setfill('*') << setw(30) << ""
        << "\nSelect an option:\n\n"
        << "1: Load CSV into Binary Tree\n"
        << "2: Print course list\n"
        << "3: Print a course and preReq's\n"
        << "0: Exit Program\n";
        cout << setfill('*') << setw(30) << "" << endl;

        //grabbing the user input, and torching the newline from the buffer
        userInput = cin.get();
        cin.get(); 

       
        switch (userInput)
        {
            case '1':
                if (!CSVparsed)
                {
                    cout << "Loading CSV...\n";
                    checkCSV(path);
                    BST.loadCSV(path);
                    CSVparsed = true;
                    cout << "CSV Loaded!\n";
                }
                else
                {
                    cout << "CSV already loaded.\n";
                }
                goto menu;
                break;
              
            case '2':
                BST.PrintAlphaNum();
                goto menu;
                break;
              
            case '3':
                cout << "Enter a courseId\n";
                cin >> temp;

                tmpC = BST.search(temp);

                if (tmpC.name == "")
                {
                    cout << "Course not found, try another.\n";
                    //need to flush the buffer after bad input
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    goto menu;
                }
                else
                {
                    BST.PrintCourse(tmpC);
                }

                goto menu;
                break;
                
            case '0':
                cout << "gooobye!\n";
                return 0;
                break;

            default:
                cout << "Please enter a valid option\n";
                goto menu;

        }

}