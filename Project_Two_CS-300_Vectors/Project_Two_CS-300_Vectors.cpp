// Project_Two_CS-300_Vectors.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
//creating a class for course
class Course
{
public:
    string title;
    string number;
    vector<string> pre_reqs;
    //creating constructor forcourses that have prereqs
    Course(string title, string number, vector<string> pre_reqs)
    {
        this->title = title;
        this->number = number;
        this->pre_reqs = pre_reqs;
    }
    //creating constructor for courses w/o prereqs
    Course(string title, string number)
    {
        this->title = title;
        this->number = number;
    }
    //creating function to get titles
    string getTitle()
    {
        return title;
    }
    //creating getNumber func for course number
    string getNumber()
    {
        return number;
    }
    //creating a printInfo func
    void printInfo()
    {
        cout << "Course title: " << getTitle() << endl;
        cout << "Prerequisites: " << endl;
        for (int i = 0; i < pre_reqs.size(); i++)
        {
            cout << pre_reqs[i] << endl;
        }
    }
};
//creating function to read file for the user
bool readClassData(string fileName, vector<Course>& courses)
{
    //variables for opening file
    fstream myFile;
    myFile.open(fileName.c_str(), ios::in);
    if (myFile.is_open())
    {
        string line;
        //while loop for when the file is open
        while (!myFile.eof())
        {
            //creating global variables
            string courseName;
            string courseTitle;
            string pre_REQ;

            getline(myFile, line);
            int i;
            i = line.find(",");
            string courseNumber = line.substr(0, i);
            line = line.substr(i + 1);
            i = line.find(",");
            //if statement for if the string doesn't have a pre_req and adds it it to the vector 
            if (i == string::npos)
            {
                courseTitle = line;
                Course c(courseTitle, courseNumber);
                courses.push_back(c);
            }
            //else if the program finds prereqs it will add it to the vector
            else
            {
                courseTitle = line.substr(0, i);
                vector<string> prerequisites;
                while (true)
                {
                    line = line.substr(i + 1);
                    i = line.find(",");
                    if (i == string::npos)
                    {
                        prerequisites.push_back(line);
                        break;
                    }
                    else
                    {
                        pre_REQ = line.substr(0, i);
                        prerequisites.push_back(pre_REQ);
                    }
                }
                Course c(courseTitle, courseNumber, prerequisites);
                courses.push_back(c);
            }
        }
        myFile.close();
        return true;
    }
    return false;
}
//creating a funct for sorting the courses in alphanumeric order
void sort(vector<Course>& course)
{
    int i, j;
    for (i = 0; i < course.size() - 1; i++) {
        for (j = 0; j < course.size() - i - 1; j++) {
            if (course[j].getTitle() > course[j + 1].getTitle())
            {
                Course temp = course[j];
                course[j] = course[j + 1];
                course[j + 1] = temp;
            }
        }
    }
}

int main()
{

    //creating global variables
    vector<Course> courses;
    bool isLoaded = false;
    string u_input;
    string courseNumber;
    int u_choice=0;

    //a while loop so that user can repetively add options
    while (u_choice != 9)
    {
        //creating menu for the user to select from
        cout << "	SELECT FROM THE MENU	" << endl;
        cout << "  | PRINT 1. Load Data Structure "<< endl;
        cout << "  | PRINT 2. Course List" << endl;
        cout << "  | PRINT 3. Course" << endl;
        cout << "  | PRINT 9. Exit " << endl;
        cin >> u_choice;

        //adding functionality that corresponds with the menu
        switch(u_choice)
        {
        case 1:
        {
                //loadcourse
            cout << "input file name";
                cin >> u_input;
                isLoaded = readClassData(u_input, courses);
                break;
            }
              case 2:
              {
                //print Course Lists
                sort(courses);
                cout << "List for courses: " << endl;
                for (int i = 0; i < courses.size(); i++)
                {
                    cout << courses[i].getTitle() << endl;
                }
                break;
            }
             case 3:
             {
                //print course;
                //use a vector
                cout << "What course do you want to know about? ";
                cin >> courseNumber;
                for (int i = 0; i < courses.size(); i++)
                    if (courseNumber == courses[i].getNumber())
                    {
                        courses[i].printInfo();
                    }
                break;
            }
             case 9:
             {
                cout << "Thank You for your time, please stop by again";
                break;
            }
            default:
            {
                // if the user input isn't valid it will show this error.
                cout << "Error: " << u_choice << " is an invalid option";
                break;
            }
        }
        }  
}
