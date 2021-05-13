/* Author: Jonathan Dang
*  Project: Recursive Functions 9.1
*  Purpose: Warm ups for recursive projects.
*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void R1_levels(int level, int platform);
void R2_Boxes(string name, int levels);
void R3_Catman(string first, string second);
unsigned int R4_Counting(string input);
double R5_Sumover(unsigned int input);
void R16_Guess(unsigned int low, unsigned int high);

int main()
{
	cout << "=============================\n";
	R1_levels(1,4);
	cout << "=============================\n";
	R2_Boxes("BOX", 3);
	cout << "=============================\n";
	R3_Catman("Cat", "man");
	cout << "=============================\n";
	cout << "Amount of Boxes: " << R4_Counting("") << endl;
	cout << "=============================\n";
	cout << "Sum Over 3: " << R5_Sumover(unsigned int(3)) << endl;
	cout << "=============================\n";
	R16_Guess(1, 1000000);
	cout << "==============END============\n";
	return 0;
}

void R1_levels(int level, int platform)
{
	for (int i = 0; i != level; i++) //Indentation Machine
	{
		cout << " ";
	}
	cout << "This was sent in level " << level << endl;

	if (level == platform) //Level Checker
	{
		for (int i = 0; i != level; i++)
		{
			cout << " ";
		}
		cout << "This was ALSO sent in level " << level << endl;
	}
	else
	{
		R1_levels(level + 1, platform);
	}

	if (level != platform) //Returning Function
	{ 
		for (int i = 0; i != level; i++)
		{
			cout << " ";
		}
		cout << "This was ALSO sent in level " << level << endl;
	}
}

void R2_Boxes(string name, int levels)
{
	string s = name;
	for (int i = 1; i < 10; i++)
	{
		s = name;
		s += '.';
		s += char('0' + i);
		cout << s << endl;
	}

	if (levels > 1)
	{
		R2_Boxes(s, levels - 1);
	}
}

void R3_Catman(string first, string second)
{
	if (first.empty()) //Checks if first is empty, acts as an end function
	{
		cout << second << endl;
	}

	for (unsigned int i = 0; i < first.size(); i++) 
		//Creates a substring and adds the first char to second, then shuffles first.
	{
		R3_Catman(first.substr(1), first[0] + second);
		rotate(first.begin(), first.begin() + 1, first.end());
	}
}

unsigned int R4_Counting(string input)
{
	static unsigned int output = 0;
	unsigned int user = 0;

	if (input.size()) //Checks the level of the box
	{
		cout << "Box: " << input << endl;
	}

	cout << "How Many Boxes Do You See?\n";
	cin >> user;

	output += user;

	if (input.size()) // Displays Level of Box
	{
		input += ".";
	}

	for (unsigned int i = 1; i <= user; i++)
	{
		R4_Counting(input + to_string(i));
	}
	return output;
}

double R5_Sumover(unsigned int input)
{
	if (input == 0)
	{
		return 0.0;
	}

	return double(1) / input + R5_Sumover(input - 1);
	//The double 1 is because if I had placed a 1, the IDE said it was an
	//int rather than a double.
}

void R16_Guess(unsigned int low, unsigned int high)
{
	char answer = NULL;
	unsigned int mid = (low + high) / 2;

	if (low == high && low == mid && high == mid)
		//Machine's Forced Guess
	{
		cout << "Your Number is " << low << endl;
		cout << "There isn't any shadow of a doubt that this is your number!\n";
		return;
		//Using return brings us out of the recursion loop since it acts as our
		//final statement
	}

	while (answer != 'l' && answer != 'h') 
		//I don't see a reason why the Higher or lower question
		//can't be paired with the number guess.
	{
		cout << "Is your number Lower or Higher than " << mid << endl;
		cout << "Or is This your number? Type y if it is." << endl;
		cin >> answer;
		if (answer == 'y')
		{
			return;
		}
	}

	if (answer == 'l')
	{
		R16_Guess(low, mid - 1);
	}
	else
	{
		R16_Guess(mid + 1, high);
	}
}

