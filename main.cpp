//
//  main.cpp
//  Assignment 4
//
//  Created by Riddhima Mathur on 9/24/18.
//  Copyright © 2018 Riddhima Mathur. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include "Semester.h"
#include "Student.h"

using namespace std;

vector<Student>student_list;     //vector to hold student names
int programs;          // number of programming assignments
int tests;              // number of tests
int finals;             // number of final exams
double progWeight;      //weight of each category
double testWeight;
double finalWeight;
Semester fall;
ofstream transactions;

void set_up()
{
    do {
        cout << "Enter number of Programming Assignments: " << endl;
        cin >> programs;
    } while(programs < 0 || programs > 6);

    do{
        cout << "Enter number of Tests: " << endl;
        cin >> tests;
    } while(tests <0 || tests >= 4);

    do{
        cout << "Enter number of Final Exams: " << endl;
        cin >> finals;
    } while(finals <0 || finals > 1);

    cout<< "Enter weight of the programming assignments category as a percentage: " << endl;
    cin >> progWeight;
    cout<< "Enter weight of the test category as a percentage: " << endl;
    cin >> testWeight;
    cout<< "Enter weight of the final exame category as a percentage: " << endl;
    cin >> finalWeight;
    while(progWeight + testWeight + finalWeight != 100)
    {
        cout << "Weight must add up to 100%. Please re-enter relative weights." << '\n' << "Enter weight of the programming assignments category as a percentage: " << endl;
        cin >> progWeight;
        cout<< "Enter weight of the test category as a percentage: " << endl;
        cin >> testWeight;
        cout<< "Enter weight of the final exame category as a percentage: " << endl;
        cin >> finalWeight;
    }
    fall.numPrograms = programs;
    fall.numTests = tests;
    for(int i = 0; i < student_list.size(); i++)   //initialize array progGrades to the number of programs the user inputted

    {
        student_list.at(i).progGrades = new double[programs];
    }


    transactions.open("Grades.trn"); //output summary to grades.trn
    transactions << programs << " number of assignments created, " << tests << " number of tests created, and " << finals << " number of final exams. These categories are worth " << progWeight << "% " << testWeight<< "% and " << finalWeight << "of the student's overall grade" << endl;

}

void add_student()
{
    Student tmp_student;
    cout << "Enter Student Name: " << endl;
    cin >> tmp_student.name;
    cout << "Enter student's number: " << endl;
    cin >> tmp_student.number;
    student_list.push_back(tmp_student); // add student to vector

    for(int i = 0; i < student_list.size() -1; i++)  //loop to alphabetically process vector of student names
    {
        for(int j = i+1; j < student_list.size();j++)
        {
            if(student_list.at(i).name > student_list.at(j).name)
            {
                Student tmp = student_list.at(i);
                student_list.at(i) = student_list.at(j);
                student_list.at(j) = tmp;
            }
        }
    }


    transactions << "Student, " << tmp_student.name << "with student number, " << tmp_student.number << " was added " << endl;


}

void record_prgGrade()
{
    int record_prg; //Program Assignment number
    double prg_grade;  // Assignment grade
    cout << "Enter Program number to be recorded: " << endl;
    cin >> record_prg;
    while(record_prg > fall.numPrograms) // assignment number must be <= total number of programs
    {
        cout << "Invalid program number. Please enter valid program number: " << endl;
        cin >> record_prg;
    }

    for(int j = 0; j < student_list.size(); j++)
    {
        cout << "Enter student's program grade" << endl;
        cout << student_list[j].name<< '\t';
        cin >> prg_grade;
        student_list.at(j).progGrades = &prg_grade;  //saves value of the program grade at the index specified by the user
    }


    transactions << "Grades for Program number " << record_prg << " was recorded." << endl;

}

void record_testGrade()
{
    int record_test; // test number
    double test_grade;  //test grade
    cout << "Enter Test number to be recorded: " << endl;
    cin >> record_test;

    while(record_test > fall.numTests) // test number must be <= total number of tests
    {
        cout << "Invalid test number. Please enter valid test number: " << endl;
        cin >> record_test;
    }

    for(int k = 0; k < student_list.size(); k++)
    {
        cout << "Enter student's test grade: " << endl;
        cout << student_list[k].name << '\t';
        cin >> test_grade;
        student_list.at(k).testGrades = &test_grade;  // saves value of the test grade at the index specified by the user
    }


    transactions << "Grades for Test number " << record_test << " was recorded." << endl;

}

void record_finalexam()
{
    double finalexam_grade;
    for(int l = 0; l < student_list.size(); l++)
    {
        cout << "Enter student's final exam grade: " << endl;
        cout << student_list[l].name << '\t';
        cin >> finalexam_grade;
        student_list.at(l).finalexamGrade = finalexam_grade; // saves final exam grade at the index specified by the user
    }

    transactions<< "Grades for the final exam were recorded" << endl;
}

void change_grade()
{
    double new_grade; // student's new grade
    double st_number; // student's number
    char typeChange;  //char for storing the type of grade user wants to change
    int index;
    cout << "Please enter student's number: " << endl;
    cin >> st_number;
    cout << "Please enter the student's new score: " << endl;
    cin >> new_grade;
    cout << "What type of grade would you like to change? Enter P for Programming Assignments, T for Tests, and F for final exam grade: " << endl;
    cin >> typeChange;


    for(int h = 0; h < student_list.size(); h++)
    {
        if(student_list.at(h).number == st_number)
        {
            if (typeChange == 'P')
            {
                cout << "Which programming assignment number would you like to change? " << endl;
                cin >> index;
                student_list.at(h).progGrades[index] = new_grade;   //goes to the index in progGrades and saves the value of the                            new grade
            }
            if (typeChange == 'T') {

                cout << "Which test number would you like to change? " << endl;
                cin >> index;
                student_list.at(h).testGrades[index] = new_grade;
            }
            if (typeChange == 'F') {

                student_list.at(h).finalexamGrade = new_grade;
            }
            else
                cout << "Not a valid type of grade.";

        }
    }


    transactions << typeChange <<" Grade for student with number : " << st_number << " was changed to a " << new_grade << endl;
}

void cal_finalgrade()
{
    int prg_size;           // size of the progGrades array
    int test_size;          // size of the testGrades array
    double finalgrade;      // students' final grades in the semester
    double testGrade;       // overall test grade
    double programGrade;    // overall programming assignment grade
    double finalexamGrade;  // final exam score
    double sum_test = 0;    // sum of all the elements in the testGrades array
    double sum_programs = 0;// sum of all the elements in the progGrades array


    for(int p = 0; p < student_list.size(); p++)
    {
        prg_size = (sizeof(student_list.at(p).progGrades)/sizeof(double));

        test_size = (sizeof(student_list.at(p).progGrades)/sizeof(double));

        for(int d = 0; d < student_list.size(); d++)
        {sum_programs += student_list.at(p).progGrades[d];  //loop through and add each value of the array to sum_programs
            sum_test += student_list.at(p).testGrades[d];   //loop through and add each value of the array to sum_test
        }

        student_list.at(p).avgProgram = sum_programs/prg_size;  // find average assignment grade by dividing the sum of the scores                                                                      by the size of the array

        student_list.at(p).avgTest = sum_test/prg_size; // find average test grade by dividing the sum of the scores                                                                      by the size of the array


        testGrade = student_list.at(p).avgTest * testWeight;        // multiply average test grade by the weight of the category
        programGrade = student_list.at(p).avgProgram * progWeight;  // multiply average assignment grade by the weight

        finalexamGrade = student_list.at(p).finalexamGrade * finalWeight; // multiply final exam grade by the weight
        finalgrade = testGrade + programGrade + finalexamGrade; // add the grades together

        student_list.at(p).finalGrade = finalgrade;     // save that value as each student's final grade
    }


    transactions<< "Final grades for all students calculated and saved" << endl;

}

void output()
{
    ofstream output;
    output.open("Grades.out");
    //prints students' name, number and final grades

    output << " Name \t Number \t Grades \n ";
    for(int i = 0; i < student_list.size(); i++)
    {
        output << student_list[i].name << '\t' << student_list[i].number << '\t' << student_list[i].finalGrade << '\n';
        output.close();
    }

    transactions<< "Student information (names, numbers, final grades) outputted to 'Grades.out'." << endl;
}

void quit()
{
    int prg_size;
    int test_size;

    ofstream data;
    string file = "Grades.dat";
    data.open(file);

    // outputs all final data entered in the Gradebook by user
    data << "Student Name \t Number \t  ";
    for(int i = 0; i < student_list.size(); i++)
    {
        data << '\n' << student_list[i].name << '\t' << student_list[i].number << '\t' << student_list[i].finalGrade << '\t';
        prg_size = (sizeof(student_list.at(i).progGrades)/sizeof(double));
        for (int j = 0; j < prg_size; i++)
        {
            //data << "Assignment " << j ;
            data << student_list.at(i).progGrades[j];

        }

        data << student_list.at(i).avgProgram << 't';

        test_size = (sizeof(student_list.at(i).testGrades)/sizeof(double));

        for (int k = 0; k < test_size; k++)
        {
            data << "Test " << k;
            data << '\n' << student_list.at(i).testGrades[k] << '\t';
        }

        data << student_list.at(i).avgTest << 't' << student_list.at(i).finalexamGrade << '\t' << student_list.at(i).finalGrade;
        data.close();
    }

    transactions << "Quit and save out of Gradebook Program. " << endl;
    transactions.close();
}

int main()
{
    bool repeat = false;
    set_up();
    char choice = '\0';  //variable to hold user choice
    while(choice != 'Q'|choice != 'q')
    {
        cout << "===============Welcome to your Gradebook. Chose one of the following options: ============\n S: Set up a new semester \n A: Add a new Student \n P: Record programming assignment grade \n T: Record test grade \n F: Record final exam grade \n C: Change a grade \n G: Calculate final grade \n O: Output grade data \n Q: Quit and save" << '\n';  //menu to select an action

        do
        {
            repeat = false;
            cin >> choice;
            choice = toupper (choice);
            switch(choice) //switch statement to handle different choices by calling appropriate functions
            {
                case 'S':
                    set_up();
                    break;
                case 'A':
                    add_student();
                    break;
                case 'P':
                    record_prgGrade();
                    break;
                case 'T':
                    record_testGrade();
                    break;
                case 'F':
                    record_finalexam();
                    break;
                case 'C':
                    change_grade();
                    break;
                case 'G':
                    cal_finalgrade();
                    break;
                case 'O':
                    output();
                    break;
                case 'Q':
                    quit();
                    return 0;
                    break;
                default:
                    cout << "Invalid Entry. Please try again" << endl;
                    repeat = true;
                    break;
            }
        }while(repeat == true);

    }

    return 0;
}
