//---------------------------------------------------------------------
// Name: Ryan Coplien and Ryan Holtz - 50/50 work
// Course:  CS 1430, Section 4 and Section 3,  Fall 2018
// Purpose: Program to maintain the student records for two teachers.
//
// Input: Your program will read and process commands from the 
// standard input until end-of-file. Commands consist of teacher ID, 
// followed by an action command and possibly followed by parameters, 
// with one or more spaces between each item.
//	
// Output: Feedback for each command entered, List of students when 
// printed, 
//---------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

//Declare constants
const int MAX_STUDENTS = 5;
const int NAME_WIDTH = 15;
const int TCHR_ID_WIDTH = 5;
const int SDT_STH_LVL = 10;
const int ALL_GRDS = 10;
const float TEST_WEIGHT_REM = 0.20f;
const float FINAL_WEIGHT_REM = 0.30f;
const float QUIZ_WEIGHT_REM = 0.20f;
const float HOMEWORK_WEIGHT_REM = 0.30f;
const float TEST_WEIGHT_REG = 0.25f;
const float FINAL_WEIGHT_REG = 0.35f;
const float QUIZ_WEIGHT_REG = 0.15f;
const float HOMEWORK_WEIGHT_REG = 0.25f;
const float TEST_WEIGHT_ADV = 0.30f;
const float FINAL_WEIGHT_ADV = 0.40f;
const float QUIZ_WEIGHT_ADV = 0.10f;
const float HOMEWORK_WEIGHT_ADV = 0.20f;
const string ID_TEACHER1 = "T1";
const string ID_TEACHER2 = "T2";

enum StrengthLevel {REMEDIAL = 'M', REGULAR = 'G', ADVANCE = 'V'};

// Declare classes
class Teacher
{
private:
	string students[MAX_STUDENTS];
	StrengthLevel level[MAX_STUDENTS];
	int quiz[MAX_STUDENTS];
	int test[MAX_STUDENTS];
	int homework[MAX_STUDENTS];
	int finalExam[MAX_STUDENTS];
	float weightedScore[MAX_STUDENTS];
	int numStudents;

	int Find(string student)
	{
		for (int i = 0; i < numStudents; i++)
			if (students[i] == student)
				return i;
		return -1;
	}

	void UpdateStudentInfo(int index, char score_type, int score)
	{
		switch (score_type)
		{
			case 'Q': 
				quiz[index] = score;
				break;
			case 'T':
				test[index] = score;
				break;
			case 'H':
				homework[index] = score;
				break;
			case 'F':
				finalExam[index] = score;
				break;
			default : 
				break;
		}
	}

public:
	Teacher()
	{
		numStudents = 0;
	}

	void AddStudent(string student, char lvl)
	{
		int index = Find(student);
		if (index >= 0)
			cout << "Record already exists for " << student << endl;
		else
		{
			if (numStudents == MAX_STUDENTS)
				cout << "Can't handle any more students" << endl;
			else
			{
				students[numStudents] = student;
				level[numStudents] = StrengthLevel (lvl);

				numStudents++;

				cout << "Record added for " << student << endl;
			}
		}
	}

	void RemoveStudent(string student)
	{
		int index = Find(student);
		if (index < 0)
			cout << "Can't remove student " << student 
			<< " - Student doesn't exist" << endl;
		else
		{
			students[index] = students[index - 1];
			level[index] = level[index - 1];
			quiz[index] = quiz[index - 1];
			test[index] = test[index - 1];
			homework[index] = homework[index - 1];
			finalExam[index] = finalExam[index - 1];
			weightedScore[index] = weightedScore[index - 1];

			numStudents--;

			cout << "Record removed for " << student << endl;
		}
	}

	void Print()
	{
		cout << "List of Students" << endl;
		WeightGrade();
		if (numStudents > 0)
		{
			for (int i = 0; i < numStudents; i++)
			{
				cout << setw(NAME_WIDTH) << right << students[i]
					<< setw(ALL_GRDS) << right << quiz[i]
					<< setw(ALL_GRDS) << right << test[i]
					<< setw(ALL_GRDS) << right << homework[i]
					<< setw(ALL_GRDS) << right << finalExam[i]
					<< setw(ALL_GRDS) << right << weightedScore[i] 
					<< endl;
			}
		} 
	}

	void Update(char updateCmd, string student, int grade)
	{
		int index = Find(student);
		if (index >= 0)
		{
			UpdateStudentInfo(index, updateCmd, grade);
			cout << "Grade updated to " << grade << " for " << student 
				<< endl;
		}
		else
			cout << "No record found for student: " << student << endl;
	}

	void WeightGrade()
	{
		for (int i = 0; i < numStudents; i++)
		{
			weightedScore[i] = 0;
			switch (level[i])
			{
				case REMEDIAL:
					weightedScore[i] += test[i] * TEST_WEIGHT_REM;
					weightedScore[i] += finalExam[i] * FINAL_WEIGHT_REM;
					weightedScore[i] += quiz[i] * QUIZ_WEIGHT_REM;
					weightedScore[i] += homework[i] * HOMEWORK_WEIGHT_REM;
					break;
				case REGULAR:
					weightedScore[i] += test[i] * TEST_WEIGHT_REG;
					weightedScore[i] += finalExam[i] * FINAL_WEIGHT_REG;
					weightedScore[i] += quiz[i] * QUIZ_WEIGHT_REG;
					weightedScore[i] += homework[i] * HOMEWORK_WEIGHT_REG;
					break;
				case ADVANCE:
					weightedScore[i] += test[i] * TEST_WEIGHT_ADV;
					weightedScore[i] += finalExam[i] * FINAL_WEIGHT_ADV;
					weightedScore[i] += quiz[i] * QUIZ_WEIGHT_ADV;
					weightedScore[i] += homework[i] * HOMEWORK_WEIGHT_ADV;
					break;
			}
		}
	}
}; // End of class Teacher

void ProcessCommandForTeacher(Teacher & teacher, char command);

int main()
{
	char command;
	string teacherID;
	Teacher teacher1;
	Teacher teacher2;

	cout << fixed << showpoint << setprecision(2);

	cin >> teacherID;
	cin >> command;
	while (cin)
	{
		
		if (teacherID == ID_TEACHER1)
		{
			cout << ID_TEACHER1 << ": ";
			ProcessCommandForTeacher(teacher1, command);
		}
		else
		{
			cout << ID_TEACHER2 << ": ";
			ProcessCommandForTeacher(teacher2, command);
		}
		cin >> teacherID;
		cin >> command;
	}

	cout << "Normal Termination of Teacher Roster Program.";

	cin.get();
	cin.get();
	return 0;
}

// Function headers
//----------------------------------------------------------------------
// Function description
// params: (in, out, in)
//----------------------------------------------------------------------
void ProcessCommandForTeacher(Teacher & teacher, char command)
{
	string student;
	char lvl;
	char updateCmd;
	int grade;
	switch (command)
	{
	case 'A':
		cin >> student;
		cin >> lvl;
		teacher.AddStudent(student, lvl);
		break;
	case 'R':
		cin >> student;
		teacher.RemoveStudent(student);
		break;
	case 'P':
		teacher.Print();
		break;
	case 'U':
		cin >> updateCmd;
		cin >> student;
		cin >> grade;
		teacher.Update(updateCmd, student, grade);
		break;
	}
}
