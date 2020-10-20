//
//  Student.h
//  Assignment 4
//
//  Created by Riddhima Mathur on 9/26/18.
//  Copyright © 2018 Riddhima Mathur. All rights reserved.
//

#ifndef Student_h
#define Student_h
using namespace std;
class Student
{
public:
    string name;
    int number;
    double* progGrades = NULL;
    double* testGrades = NULL;
    double finalexamGrade;
    double finalGrade;
    double avgProgram;
    double avgTest;
};

#endif /* Student_h */
