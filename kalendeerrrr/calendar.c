/*
File: calender.c
----------------
This program is used to generate a calender for a year
entered by the user.
*/

#include <stdio.h>
#include "simpio.h"
#include "genlib.h"

/*
Constants:
----------
Days of the week are represented by the integers 0-6.
Months of the year are identified by the integers 1-12;
because this numeric representation for months is in
common use, no special constants are defined.
*/

#define Sunday		0
#define Monday		1
#define Thuesday	2
#define Wednesday	3
#define Thursday	4
#define Friday		5
#define Saturday	6

int weekday;

/*Function prototypes*/

void displayMainMenu(void);
void giveInstructions(void);
int getYearFromUser(void);
int getMonthFromUser(void);
void printCalender(int year);
void printCalenderMonth(int month, int year);
void indentFirstLine(int weekday);
int monthDays(int month, int year);
int firstDayOfMonth(int month, int year);
string monthName(int month);
string dayName(int weekday);
bool isLeapYear(int year);
int calcWeekday(int day, int month, int year);
void displayYearCalender(void);
int findWeekDay(void);
void birthday(void);
void holiday(void);
int fatherDay(int year);
int fatherMonth(void);
int christmasDay(void);
int christmasMonth(void);
void anyKey();

/*Main program*/

main()
{
	int answer;

	while (TRUE)
	{
		displayMainMenu();
		printf("Which calender function would you like to use?\n");
		printf("    Enter 1 for Printing a whole year's calendar\n");
		printf("    Enter 2 for Finding the weekday of a specific date\n");
		printf("    Enter 3 for Birthday data\n");
		printf("    Enter 4 for Holidays\n");
		printf("    Enter 0 to Quit\n");
		printf("Your choice? ");
		answer = GetInteger();

		switch (answer)
		{
		case 1: displayYearCalender(getYearFromUser);
		case 2: findWeekDay(calcWeekday);
		case 3: birthday();
		case 4: holiday();
		case 0:
			exit(0);
		default: printf("Please enter a valid option\n"); break;
		}
		anyKey();
	}
}

/*

Function: displayMainMenu
Usage: displayMainMenu (void);
------------------------------
This function will show the Main Menu of our program.
*/

void displayMainMenu(void)
{
	system("cls");
}

/*
Function: GiveInstructions
Usade: GiveInstructions();
--------------------------
This procedure prints out instructions to the user.
*/

void giveInstructions(void)
{
	printf("This program displays a calender for a full\n");
	printf("year. The year must not be before 1900.\n");
}




/*
Function: GetYearFromUser
Usage: year = GetYearFromUser();
--------------------------------
This function reads in a year from the user an returns
that value. If the user enters a year before 1900, the
function gives the user another chance.
*/

int getYearFromUser(void)
{
	int year;

	while (TRUE) {
		printf("Which year? ");
		year = GetInteger();
		if (year >= 1900) return (year);
		printf("The year must be at least 1900.\n");
	}
}

/*
Function: GetMonthFromUser
Usage: GetMonthFromUser();
-------------------------
This function reads in a month from the user and returns
the value. If the user doesnt enter a month from 1 to 12
they will get another chance to do so.*/

int getMonthFromUser(void)
{
	int month;

	while (TRUE) {
		printf("Which month? ");
		month = GetInteger();
		if (month >= 1 && month <= 12); return (month);
		printf("The month must be a number between 1 and 12.\n");
	}
}

/*
Function: GetDayFromUser
Usage: int GetDayFromUser(int year, int month);
------------------------
This function reads in a day from the user and returns
the value. Depending if the year is a leap year or which
month it is, the user will have to enter the right number
between 1 and 31.*/

int getDayFromUser(month, year)
{
	int day;

	while (TRUE) {
		printf("Which day? ");
		day = GetInteger();
		if (day >= 1 && day <= monthDays); return day;
		printf("The day must be a number between 1 and 31.\n");
	}

}

/*
Function: PrintCalender
Usage: printCalender(year);
---------------------------
This procedure prints a calender for an entire year.
*/

void printCalender(int year)
{
	int month;

	for (month = 1; month <= 12; month++) {
		printCalenderMonth(month, year);
		printf("\n");
	}
}

/*
Function: PrintCalenderMonth
Usage: PrintCalenderMonth(month, year);
---------------------------------------
This procedure prints a calender for the given month
and year
*/

void printCalenderMonth(int month, int year)
{
	int weekday, nDays, day;

	printf("   %s %d\n", monthName(month), year);
	printf(" Su Mo Tu We Th Fr Sa\n");
	nDays = monthDays(month, year);
	weekday = firstDayOfMonth(month, year);
	indentFirstLine(weekday);
	for (day = 1; day <= nDays; day++)
	{
		printf(" %2d", day);
		if (weekday == Saturday) printf("\n");
		weekday = (weekday + 1) % 7;
	}
	if (weekday != Sunday) printf("\n");
}

/*
Function: IndentFirstLine
Usage: IndentFirstLine(weekday);
--------------------------------
This procedure indents the first line of the calender
by printing enough blank spaces to get to position
on the line corresponding to weekday.
*/

void indentFirstLine(int weekday)
{
	int i;

	for (i = 0; i < weekday; i++)
	{
		printf("   ");
	}
}

/*
Function: MonthDays
Usage: ndays = MonthDays(month, year);
-------------------------------------
MonthDays returns the number of days in the indicated
month and year. The year is required ti handle leap years.
*/

int monthDays(int month, int year)
{
	switch (month)
	{
	case 2:
		if (isLeapYear(year)) return (29);
		return 28;
	case 4: case 6: case 9: case 11:
		return (30);
	default:
		return (31);
	}
}

/*
Function: FirstDayOfMonth
Usage: weekday = FirstDayOfMonth(month, year);
----------------------------------------------
This function returns the day of the ween on which the
indicated month begins. This program simply counts
forward from January 1, 1900, which was Monday.
*/

int firstDayOfMonth(int month, int year)
{
	int weekday, i;

	weekday = Monday;
	for (i = 1900; i < year; i++)
	{
		weekday = (weekday + 365) % 7;
		if (isLeapYear(i)) weekday = (weekday + 1) % 7;
	}
	for (i = 1; i < month; i++)
	{
		weekday = (weekday + monthDays(i, year)) % 7;
	}
	return (weekday);
}

/*
Function: MonthName
Usage: name = MonthName(month);
-------------------------------
MonthName converts a numeric month in the range 1-12
into the string name for that month.
*/

string monthName(int month)
{
	switch (month)
	{
	case 1: return	("January");
	case 2: return	("February");
	case 3: return	("March");
	case 4: return	("April");
	case 5: return	("May");
	case 6: return	("June");
	case 7: return	("July");
	case 8: return	("August");
	case 9: return	("September");
	case 10: return ("October");
	case 11: return	("November");
	case 12: return ("December");
	default: return ("Illegal month");
	}
}


/*Function: DayName
Usage: day = DayName(date)
--------------------------
DayName converts a numeric date in the range 1-7
inte the string name for that day.
*/

string dayName(int weekday)
{
	switch (weekday)
	{
	case 0: return ("Sunday");
	case 1: return ("Monday");
	case 2: return ("Tuesday");
	case 3: return ("Wednesday");
	case 4: return ("Thursday");
	case 5: return ("Friday");
	case 6: return ("Saturday");
	default: return ("Illegal day");
	}
}
/*
Function: IsLeapYear
Usage: if (IsLeapYear(year))...
-------------------------------
This function returns TRUE if year is a leap year.
*/

bool isLeapYear(int year)
{
	return (((year % 4 == 0) && (year % 100 != 0))
		|| (year % 400 == 0));
}


/*
Function: displayYearCalender
Úsage: displayYearCalender(void);
---------------------------------
This function will return the months and days from the year
the user asks for.*/

void displayYearCalender(void)
{
	int year;

	giveInstructions();
	year = getYearFromUser();
	printCalender(year);

}

/*
Function: findWeekDay
Usage: findWeekDay(void);
------------------------
This function will return the name of the day which
the year, month and date accure.
*/


int findWeekDay()
{
	int  weekday, year, month, day;

	year = getYearFromUser();
	month = getMonthFromUser();
	day = getDayFromUser();
	weekday = calcWeekday(day, month, year);
	printf("%s %d %d was a %s.\n", monthName(month), day, year, dayName(weekday));

	anyKey();


}


/*Function: calcWeekday
Usage: calcWeekday(int year, int month, int day)
------------------------------------------------
This function calculates which weekday the chosen date is.
*/

int calcWeekday(int day, int month, int year)
{
	int weekday;

	//first day of month you add the day you are looking for - 1 as we are already on the first day
	weekday = firstDayOfMonth(month, year);
	weekday = (weekday + day - 1) % 7;

	return  weekday;

}


/*
Function: birthday
Usage: birthday(void);
---------------------
This function will return the day of the birthday and every day for
the ten years to come.
*/

void birthday(void)

{
	int  weekday, year, month, day, i;
	string name;
	printf("Please input the name of the person: \n");
	name = GetLine();
	printf("You will now be asked to input your birth date in three parts.\n");
	year = getYearFromUser();
	month = getMonthFromUser();
	day = getDayFromUser();
	weekday = calcWeekday(day, month, year);
	printf("%s was born on a %s.\n", name, dayName(weekday));
	year = 2019;

	for (i = 0; i <= 10; i++)
	{
		weekday = calcWeekday(day, month, year);
		printf("in %d %s birthday is on a %s.\n", year, name, dayName(weekday));
		year++;
	}

	anyKey();
}

/*
Function: calcBirthday
Usage: calcBirthday(int day, int month, int day)
------------------------------------------------
This function will return the name of the day the birthday
appears ten years forward.
*/


/*
Function: holiday
Usage: holiday(void)
--------------------
This function will display a number of holidays
for the year that is asked for.
*/

void holiday(void)
{
		int year, month, day, weekday;
		printf("Please input a year to calculate holidays for");
		year = getYearFromUser();
		month = christmasMonth();
		day = christmasDay();
		weekday = calcWeekday(day,month,year);
		printf("Christmas day in %d is on %s %d which is a %s\n", year,
			monthName(month), day, dayName(weekday));

		month = fatherMonth();
		day = fatherDay(year);
		weekday = calcWeekday(day, month, year);
		printf("Fathers day in %d is on %s %d which is a %s\n", year,
			monthName(month), day, dayName(weekday));



}



/*
Function: anyKey
Usage: anyKey();
----------------
This function lets the user press any key to continue.
*/

void anyKey()
{
	printf("Press any key to continue");
	getchar();
}
/*
Function: christmasMonth
Usage: christmasMonth(void);
------------------------
This function will return the month 12, December
*/
int christmasMonth(void)
{
	return 12;
}

/*
Function: christmasDay
Usage: christmasDay(void);
------------------------
This function will return the day 25, Christmas day.
*/
int christmasDay(void)
{
	return 25;
}

/*
Function: fatherMonth
Usage: fatherMonth(void);
------------------------
This function will return the month 11 which is the month November
*/
int fatherMonth(void)
{
	return 11;
}
/*
Function: fatherDay
Usage: fatherDay(int year);
------------------------
This function will calculate the fathers day of a particular year.
*/
int fatherDay(int year)
{
	int i;
	
		for (i = 8; i <= 14; i++)
		{
			if (calcWeekday(i, fatherMonth, year) == Sunday) 
			{
				break;
			}
			
		}
		return i;
}