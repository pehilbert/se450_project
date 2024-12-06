#include "StudentUtility.h"

/*
Name: deepCopyStudentDAta
Process: copies one StudentType item into another
Function input/parameters: source data (const StudentType)
Function output/parameters: destination data (StudentType *)
Function output/returned: none
Device input/ ---: none
Device output/ ---: none
Dependencies: privateCopyString
*/
void deepCopyStudentData( StudentType *dest, const StudentType source )
	{
	 privateCopyString(dest->name, source.name);
	 dest->studentId = source.studentId;
	 dest->gender = source.gender;
	 dest->gpa = source.gpa;
	 dest->priority = source.priority;
	}

/*
Name: studentDataToString
Process: creates display string from all object data
Method input/parameters: none
Method output/parameters: pointer to return string (char * const)
Method output/returned: none
Device input/keyboard: none
Device output/monitor: none
Dependencies: sprintf
*/
void studentDataToString( char *outString, const StudentType toDisplay )
	{
	 sprintf(outString, "Nm: %s, Id: %d, Gndr: %c, GPA: %f, Priority: %d",
			 toDisplay.name, toDisplay.studentId, toDisplay.gender,
			 toDisplay.gpa, toDisplay.priority);
	}



