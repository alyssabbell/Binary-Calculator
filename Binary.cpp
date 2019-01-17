/*
Name: Alyssa Bell

Date: 12/10/16

filename: Binary.cpp

Purpose: This program is a driver program designed to implement & test
functions GetBinary(), GetDecimal(), ValidBin(), ValidDec()ConvertFromBinary(), 
ConvertFromDecimal(), Add/Subtract/Multiplication/Division/ModulusOperation(),
ProcessFiles().

Assumptions: The user will not try to divide by 00000000. 
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>               // for toupper and tolower
#include <fstream>				// for file stream
#include <sstream>
using namespace std;

// Constants
const int BYTE_SIZE = 8;		// 8 bits in a Byte
const int BYTE_MAX = 255;		// Max value for an 8 bit string
const int BYTE_MIN = 0;			// Min value for an 8 bit string
const char SENT_VALUE = 'Q';

// Function Prototypes:
void PrintGreeting();
void Greeting();
bool ValidBin(/* IN */ string byte);
bool ValidDec(/* IN */ int decimal);
string GetBinary();
int GetDecimal();
int ConvertFromBinary(/* IN */ string byte);
string ConvertFromDecimal(/* IN */ int num);
char GetMenuPick();
void AddOperation();
void SubtractOperation();
void MultiplicationOperation();
void DivisionOperation();
void ModulusOperation();
void ProcessFiles();
void PrintSummary(int addCount, int subCount, int multCount, int divCount, int modCount, int procFilesCount, int convertBinCount, int convertDecCount);
void WrapConvertFromBinary();
void WrapConvertFromDecimal();

int main()
{

	string byteStr1;			// 1st user-entered byte of data
	string byteStr2;			// 2nd user-entered byte of data
	string conByteStr;			// Converted Decimal to base two string
	int decimalValue = 0;			// The decimal equivalent of the byte the user entered
	char menuChoice;			// operator or letter entered by user
	ifstream din;				// input file variable
	ofstream dout;				// output file variable
	string inFileName;			// stores input file
	string outFileName;			// stores output file 
	int addOpCount = 0;
	int subOpCount = 0;
	int multOpCount = 0;
	int divOpCount = 0;
	int modOpCount = 0;
	int procFilesCount = 0;
	int convertBinCount = 0;
	int convertDecCount = 0;


	
	// All Actions count Vars

	PrintGreeting();			// Call to welcome user before menu options

	// Call to void Greeting()
	do
	{
		Greeting();
		menuChoice = GetMenuPick();

		// Run menu functions
		switch (menuChoice)
		{
		case '+': AddOperation();
			addOpCount++;
			break;
		case '-': SubtractOperation();
			subOpCount++;
			break;
		case '*': MultiplicationOperation();
			multOpCount++;
			break;
		case '/': DivisionOperation();
			divOpCount++;
			break;
		case '%': ModulusOperation();
			modOpCount++;
			break;
		case 'p':
		case 'P': ProcessFiles();
			procFilesCount++;
			break;
		case 'b':
		case 'B': WrapConvertFromBinary();
			convertBinCount++;
			break;
		case 'c':
		case 'C': WrapConvertFromDecimal();
			convertDecCount++;
			break;
		case 'q':
			menuChoice = toupper(menuChoice);
		case 'Q':
		default: 
			break;
		}
	} while (menuChoice != SENT_VALUE);
	if (menuChoice == SENT_VALUE)
	{
		PrintSummary(addOpCount, subOpCount, multOpCount, divOpCount, modOpCount, procFilesCount, convertBinCount, convertDecCount);
	}
	
	return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Function PrintGreeting() Welcomes user upon entering program
*/
void PrintGreeting()
{
	system("cls");
	cout << "************************************************************" << endl;
	cout << "*                                                          *" << endl;
	cout << "*          Welcome to the Super Binary Calculator!         *" << endl;
	cout << "*                                                          *" << endl;
	cout << "*                Created by Alyssa Bell                    *" << endl;
	cout << "*                                                          *" << endl;
	cout << "************************************************************" << endl 
		<< endl;
	system("pause");
	system("cls");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Function Greeting() lists the operation menu upon opening the program.
*/

void Greeting()
{
	system("cls");
	cout << "************************************************************" << endl;
	cout << "*     Binary Calculator Menu Options                       *" << endl;
	cout << "*     Please select an operation from the following menu:  *" << endl;
	cout << "*     + for Binary Addition                                *" << endl;
	cout << "*     - for Binary Subtraction                             *" << endl;
	cout << "*     * for Binary Multiplication                          *" << endl;
	cout << "*     / for Binary Division                                *" << endl;
	cout << "*     % for Binary Modulus                                 *" << endl;
	cout << "*     P to process an input file                           *" << endl;
	cout << "*     B to convert Binary to Decimal                       *" << endl;
	cout << "*     C to convert Decimal to Binary                       *" << endl;
	cout << "*     Q to quit the program                                *" << endl;
	cout << "************************************************************" << endl;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
Function ValidBin(). This function will test whether a the value of a
string variable represents a valid 8-bit binary number or not. This function
takes a string as an argument and returns true if that string contains
exactly eight ‘1’s and ‘0’s and false otherwise:
*/
bool ValidBin(/* IN */ string byte)
{
	bool isValid = true;

	// test if string is not 8 chars long, also validates number is between 0 and 255
	if (byte.length() != BYTE_SIZE)
	{
		cout << "Invalid length!" << endl;
		isValid = false;
	}
	// test if chars in string are not 1 or 0
	else {
		for (int i = 0; i < BYTE_SIZE; i++)
		{
			if (byte[i] == '1' || byte[i] == '0')
			{

			}
			else
				isValid = false;
		}
	}
	return isValid;
}

bool ValidDec(int decimal)  // validates Decimal entered by user when selecting C
{
	bool isValid = true;

	// test if user decimal is less than 0 or greater than 255
	if (decimal <= BYTE_MIN || decimal >= BYTE_MAX)
	{
		cout << "Overflow error!" << endl;
		isValid = false;
	}
	return isValid;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
Create SVRF GetBinay(). This function will get a binary (string) from the user
and send it back as a string. The binary string will be validated through function ValidBin()
after it is read.
*/

string GetBinary()
{

	string binary; // locally/temporarily stores 8 bit binary entered by user

	do {
		cout << "Please enter an 8 bit binary number." << endl;
		cin >> binary;
	} while (!ValidBin(binary));

	return binary;

}

int GetDecimal()
{

	int decimal; // locally/temporarily stores a decimal value entered by user

	// ask for a valid decimal while user enters invalid decimal
	do {
		cout << "Please enter a decimal value between 0 and 255." << endl;
		cin >> decimal;
	} while (!ValidDec(decimal));  // while decimal is ValidDec returns false

	return decimal;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
Create SVRF ConvertFromBinary(). This function will convert a string value
which represents a valid byte, (tested with function ValidBin()), and
converts it to a base 10, or decimal, value. This function takes a single
string argument, corresponding to an 8 bit binary # (this string should be
validated prior to sending it to this function), and converts (and returns)
the decimal equivalent of the argument:
*/


int ConvertFromBinary(/* IN */ string byte)
{
	int sum = 0;
	int placeVal = 128;  // Initiliaze starting placeVal, pos 0, 128 in base 10

	for (int pos = 0; pos < BYTE_SIZE; pos++)
	{
		// Check for a 1 in current position
		if (byte[pos] == '1')
			sum = placeVal + sum;  // adds the base 10 value of the current place holder to existing sum
		placeVal = placeVal / 2;   // divides the current placeVal by 2 to get the next placeVal
	}

	// return the sum of the binary values in base 10.
	return sum;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
Create SVRF ConvertFromDecimal(). This function will convert a decimal
value to its corresponding string value.  This function takes a single
decimal argument, (in the range 0 to 255), and converts (and returns)
the 8 bit binary equivalent, stored as a string.
*/

string ConvertFromDecimal(/* IN */ int num)
{
	string binVal = "00000000";  // initialized value of binary string
	int placeVal = 128;


	for (int pos = 0; pos < BYTE_SIZE; pos++)
	{
		if (num >= placeVal)
		{
			binVal[pos] = '1';
			num = num - placeVal;
		}
		placeVal = (placeVal / 2);
	}
	return binVal;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
Create SVRF GetMenuPick(). This function will get a menu pick from the user
in the form of a single character.
*/

char GetMenuPick()
{
	char choice;
	bool validSelection = false;


	do{
		cin >> choice;
		switch (choice)
		{
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
			validSelection = true;
			break;
		case 'p':
		case 'c':
		case 'b':
		case 'q':
			toupper(choice);
			validSelection = true;
			break;
		case 'P':
		case 'C':
		case 'B':
		case 'Q':
			validSelection = true;
			break;
		default:
			validSelection = false;
				cout << "Please enter a valid character.";
		}
	}while (validSelection == false);

			return choice;
	}


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/*
	Create void PrintSummary(). This function will keep track of the total
	number of times each operation is performed.
	*/


void PrintSummary(int addCount, int subCount, int multCount, int divCount, int modCount, int procFilesCount, int convertBinCount, int convertDecCount)
	{
		ofstream dout;
		//dout.open("calc.out");

		cout << "Summary Of Operations" << endl << endl;
		cout << "The total number of addition operations is: " << addCount << endl;
		cout << "The total number of subtraction operations is: " << subCount << endl;
		cout << "The total number of multiplication operations is: " << multCount << endl;
		cout << "The total number of division operations is: " << divCount << endl;
		cout << "The total number of modulus operations is: " << modCount << endl;
		cout << "The total number of process files operations is: " << procFilesCount << endl;
		cout << "The total number of convert from binary operations is: " << convertBinCount << endl;
		cout << "The total number of convert from decimal operations is: " << convertDecCount << endl;

	}



	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/*
	Create AddOperation(). This function will receive user input byte strings, store them locally,
	call ConvertFromBinary which will convert to two decimals that will be stored locally.
	AddOperation() adds the two decimal values together.
	Calls ConvertFromDecimal to return a binary conversion.
	*/


	void AddOperation()
	{
		string strByte1, strByte2, strSum;		// temporarily stores user binaries and sum
		int intValue1, intValue2, intSum = 0;

		system("cls");

		cout << "Binary Addition" << endl << endl;

		strByte1 = GetBinary();					// Call to get 1st input binary num
		strByte2 = GetBinary();					// Call to get 2nd input binary num

		intValue1 = ConvertFromBinary(strByte1);	// Call to convert binary1 to an int, store as int1
		intValue2 = ConvertFromBinary(strByte2);	// Call to convert binary2 to an int, store as int2
		
		intSum = intValue1 + intValue2;				// Performs addition if valid
		if (intSum > BYTE_MAX)
			cout << "Sum is too large to store in an 8 bit binary number." << endl;
		else if (intSum < BYTE_MIN)
			cout << "Sum is too small." << endl;
		else
			 strSum = ConvertFromDecimal(intSum);		// Converts decimal sum back to binary
			 
		cout << strByte1 << " + " << strByte2 << " = " << strSum << endl;
		system("pause");


	}


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/*
	Create SubtractOperation(). This function will subtract decimal 2 from decimal 1 (conversions
	of the 8 bit binary numbers), then return the difference (in decimal) for
	ConvertFromDecimal to return a binary conversion.
	*/


	void SubtractOperation()
	{
		string strByte1, strByte2, strAns;		// temporarily stores user binaries and sum
		int intValue1, intValue2, intAns = 0;


		system("cls");

		cout << "Binary Subtraction" << endl << endl;

		strByte1 = GetBinary();					// Call to get 1st input binary num
		strByte2 = GetBinary();					// Call to get 2nd input binary num

		intValue1 = ConvertFromBinary(strByte1);	// Call to convert binary1 to an int, store as int1
		intValue2 = ConvertFromBinary(strByte2);	// Call to convert binary2 to an int, store as int2

		intAns = intValue1 - intValue2;			// Performs subtraction if valid 
		if (intAns > BYTE_MAX)
			cout << "Difference is too large to store in an 8 bit binary number." << endl;
		else if (intAns < BYTE_MIN)
			cout << "Not a valid binary number." << endl;
		else{
			strAns = ConvertFromDecimal(intAns);		// Converts decimal back to binary
			cout << strByte1 << " - " << strByte2 << " = " << strAns << endl;
		}
	
		//cout << strByte1 << " - " << strByte2 << " = " << strAns << endl;
		system("pause");
	}



	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/*
	Create MultiplicationOperation(). This function will multilpy decimal 1 and decimal 2 (conversions
	of the 8 bit binary numbers input by user), then concert the product (in decimal) to binary through
	ConvertFromDecimal.
	*/


	void MultiplicationOperation()
	{
		string strByte1, strByte2, strAns;		// temporarily stores user binaries and sum
		int intValue1, intValue2, intAns = 0;

		system("cls");

		cout << "Binary Multiplication" << endl << endl;

		strByte1 = GetBinary();					// Call to get 1st input binary num
		strByte2 = GetBinary();					// Call to get 2nd input binary num

		intValue1 = ConvertFromBinary(strByte1);	// Call to convert binary1 to an int, store as int1
		intValue2 = ConvertFromBinary(strByte2);	// Call to convert binary2 to an int, store as int2

		intAns = intValue1 * intValue2;			// Performs multiplication if valid
		if (intAns > BYTE_MAX)
			cout << "Product is too large to store in an 8 bit binary number." << endl;
		else if (intAns < BYTE_MIN)
			cout << "Product is too small." << endl;
		else
			strAns = ConvertFromDecimal(intAns);	// Converts decimal product back to binary
		
		cout << strByte1 << " * " << strByte2 << " = " << strAns << endl;
		system("pause");
	}


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/*
	Create DivisionOperation(). This function will divide decimal 1 by decimal 2 (conversions
	of the 8 bit binary numbers input by user), then produced the quotient (in decimal) for
	ConvertFromDecimal to return a binary conversion.
	*/


	void DivisionOperation()
	{
		string strByte1, strByte2, strAns;		// 1 and 2 temporarily stores user binaries 
		int intValue1, intValue2, intAns;
		

		system("cls");

		cout << "Binary Division" << endl << endl;

		strByte1 = GetBinary();					// Call to get 1st input binary num
		strByte2 = GetBinary();					// Call to get 2nd input binary num - cannot be 0
		/*
		
		DO NOT ALLOW DIVISION BY 0
		strByte2 should not equal 00000000
	

		*/

		intValue1 = ConvertFromBinary(strByte1);	// Call to convert binary1 to an int, store as int1
		intValue2 = ConvertFromBinary(strByte2);	// Call to convert binary2 to an int, store as int2
		
		intAns = intValue1 / intValue2;			// Performs division if valid in base 10

		if (intAns > BYTE_MAX)
			cout << "Quotient is too large to store in an 8 bit binary number." << endl;
		else if (intAns < BYTE_MIN)
			cout << "Quotient is too small." << endl;
		else
			strAns = ConvertFromDecimal(intAns);	// Converts decimal quotient back to binary
		
		cout << strAns << " / " << strByte2 << " = " << strAns << endl;
		system("pause");
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/*
	Create ModulusOperation(). This function will divide decimal 1 by decimal 2 (conversions
	of the 8 bit binary numbers input by user). If decimal 2 divides into decimal 1 evenly
	without a remainder, the function will return a binary 0 (00000000). If there is a remainder,
	the remainder will be outputted.
	*/

	void ModulusOperation()
	{
		string strByte1, strByte2, strAns;		// temporarily stores user binaries and sum
		int intValue1, intValue2, intAns = 0;


		system("cls");

		cout << "Binary Modulo" << endl << endl;

		strByte1 = GetBinary();					// Call to get 1st input binary num
		strByte2 = GetBinary();					// Call to get 2nd input binary num

		intValue1 = ConvertFromBinary(strByte1);	// Call to convert binary1 to an int, store as int1
		intValue2 = ConvertFromBinary(strByte2);	// Call to convert binary2 to an int, store as int2

		intAns = intValue1 % intValue2;			// Performs modulus if valid
		if (intAns > BYTE_MAX)
			cout << "Remainder is too large to store in an 8 bit binary number." << endl;
		else if (intAns < BYTE_MIN)
			cout << "Remainder is too small." << endl;
		else
			strAns = ConvertFromDecimal(intAns);	// Converts decimal answer back to binary
		
		cout << strByte1 << " % " << strByte2 << " = " << strAns << endl;
		system("pause");
	}


	/*
	Function ProcessFiles() will allow the user to select P or p in the menu, which
	will prompt them to list input and output file names. The input file will be in
	the format of operator > operand 1 > operand 2. The output file (which will be
	created by binary.cpp) will be in the format of operand 1 > operator > operand 2
	> = result.
	*/

	void ProcessFiles()			// If user selects P or p
	{

		//char getMenuFunction;			// meun choice from user 
		string inFileName;				// name of input file
		string outFileName;				// name of output file
		string operand1;				// stores 1st binary number
		string operand2;				// stores 2nd binary number
		char operation;					// stores the operand
		string answer;					// binary answer
		ifstream din;
		ofstream dout;
		int intValue1, intValue2, intSum = 0;
		int prvErrorCount = 0;
		int errorCount = 0;
		system("cls");
		string line;


		cout << "Please enter the name of the input file: " << endl;
		cin >> inFileName;
		cout << "Please enter the name of the output file: " << endl;
		cin >> outFileName;
		din.open(inFileName.c_str());
		dout.open(outFileName.c_str());

		if (din)						// if input file is found
		{

			while (getline(din, line))
			{
				istringstream linestream(line);
				linestream >> operation >> operand1 >> operand2;
				if ((operation != NULL && operand1 != "" && operand2 != "") && (operation == '+' || operation == '-' || operation == '*' || operation == '/' || operation == '%'))
				{
					intValue1 = ConvertFromBinary(operand1);
					intValue2 = ConvertFromBinary(operand2);

					prvErrorCount = errorCount;
					//dout << "Process Summary"<<  << endl;
					if (intValue1 <= BYTE_MIN || intValue1 >= BYTE_MAX)		// if int is outside of 0-255
						errorCount++;
					else if (intValue1 >= BYTE_MIN || intValue1 <= BYTE_MAX)
					{

						// use switch statement to perform output on operation in file
						switch (operation)
						{
						case '+':
							intSum = intValue1 + intValue2;
							if (intSum > BYTE_MAX)
								errorCount++;
							break;
						case '-':
							intSum = intValue1 - intValue2;
							if (intSum > BYTE_MAX)
								errorCount++;
							break;
						case '*':
							intSum = intValue1 * intValue2;
							if (intSum > BYTE_MAX)
								errorCount++;
							break;
						case '/':
							intSum = intValue1 / intValue2;
							if (intSum > BYTE_MAX)
								errorCount++;
							break;
						case '%':
							intSum = intValue1 % intValue2;
							if (intSum > BYTE_MAX)
								errorCount++;
							break;
						default: break;
						}
					}
					else{}
					//covert to bi
					if (prvErrorCount == errorCount){
						answer = ConvertFromDecimal(intSum);
						dout << operand1 << operation << operand2 << " = "
							<< answer << endl;

					}
				}
				else{
					errorCount++;

				}
					din >> operation >> operand1 >> operand2;
		
			}
			// add Error Count to dout
			dout << "The number of invalid operations is: " << errorCount << endl;


		}

		din.close();     // Close input file
		dout.close();    // Close output file

		system("pause");
		
	}



	void WrapConvertFromBinary()
	{
		string userBinary;		// temporarily stores user entered binary
		int returnDecimal;

		system("cls");

		cout << "Convert from Binary" << endl << endl;
		userBinary = GetBinary();					// Call to get input binary num

		returnDecimal = ConvertFromBinary(userBinary);	// storing decimal conversion 
		cout << userBinary << " converts to " << returnDecimal << endl;
		system("pause");


	}

	void WrapConvertFromDecimal()
	{
		int userDecimal;		// temporarily stores user decimal
		string returnBinary;

		system("cls");

		cout << "Convert from Decimal" << endl << endl;
		userDecimal = GetDecimal();					// Call to get input decimal number

		returnBinary = ConvertFromDecimal(userDecimal);	

		cout << userDecimal << " converts to " << returnBinary << endl;
		system("pause");
	}

	