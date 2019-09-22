#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<string.h>
#include<sstream>
#include<iomanip>
#include<vector>
#include<math.h>

using namespace std;

void getFileData(ifstream& in_s, string& song1File, string& fragment, string& song2File, string& fragment1);
int convertString(ifstream& in_s);
int convertString1(ifstream& in_s);
int convertString2(ifstream& in_s);
int similartity(ifstream& in_s);
string openSecondFile(string& song1File, int& song1Id, 	string& musicalnotes1);																												//Functions used to open input file, derive data, create matrix and align the songs
string openThirdFile(string& song2File, int& song2Id, 	string& musicalnotes2);
int maximum (int a, int b, int c);
void AlignmentMtx(vector<vector<int> >& mtx, int song2Size, int song1Size, int rows, int columns, int gap, string musicalnotes1, string musicalnotes2, 	int match, 	int mismmatch);
void TraceBack(vector<vector<int> > mtx, string musicalnotes1, string musicalnotes2, int gap, int mismmatch, int song2Size, int song1Size, 	string song1, 	string song2, int song1Id, int song2Id, 	int copyrightPercent);

int main ()
{
	ifstream in_s;        //if stream variables that are used to read in data from text files
	string song1File;		 //song a file
	string fragment;    //hold substrings
	string song2File;   // song b file
	string fragment1;  //hold substrings
	int match;         //hold match score
	int mismmatch;     //hold mistmatch score
	int gap;            //hold gap score
	int copyrightPercent;  //hold copyright percent
	string song1;     //song 1 name
	int song1Id;     //song 1 id
	string musicalnotes1;   //song 1 notes
	int song2Id;  // song 2 id
	string musicalnotes2;  //song 2 notes
	string song2;  //song name
	vector<vector<int> > mtx;  // 2D vector to hold mtx

	getFileData(in_s, song1File, fragment, song2File, fragment1);      //calling to open input file

	match	= convertString(in_s);  //derives match score

	mismmatch = convertString1(in_s);  //derives mismmatch score

	gap = convertString2(in_s);  ////derives gap score

	copyrightPercent = similartity(in_s);   //derives  copyright percent

	song1 = openSecondFile(song1File, song1Id, musicalnotes1); //opens song a file and derives data

	song2 = openThirdFile(song2File, song2Id, musicalnotes2); //opens song b file and derives data

	int song2Size = musicalnotes2.length();  //creates size variables that will hold size of song notes
	int song1Size = musicalnotes1.length();
	int rows = song1Size + 1;    //holds matrix bounds
	int columns = song2Size + 1;

	AlignmentMtx(mtx, song2Size, song1Size, rows, columns, gap, musicalnotes1, musicalnotes2, match, mismmatch);  //calling function to fill matrix

	TraceBack(mtx, musicalnotes1, musicalnotes2, gap, mismmatch, song2Size, song1Size, song1, song2, song1Id, song2Id, copyrightPercent); // calling function to traceback

return 0;
}

void getFileData(ifstream& in_s, string& song1File, string& fragment, string& song2File, string& fragment1)                                                                                                                    //getfilename and getfilename1 opens the user entered text files
{
	char input_file[30];

	cout << "Enter the name of the input file: ";
	cin >> input_file;							//storing file name

	in_s.open(input_file);							//opeing input file

	if(in_s.fail())								//if file does not exist a fail message will appear
	{
		cout << "Unable to open input file " << input_file << endl;
		exit(EXIT_FAILURE);
	}

	getline(in_s, fragment);
	song1File = fragment.substr(7);   // getting song 1 and 2 files names

	getline (in_s, fragment1);
	song2File = fragment1.substr(7);
}

int convertString(ifstream& in_s)
{
	string fragment2, frag;
	int final;

	getline(in_s, fragment2);		//reading in match score
	frag = fragment2.substr(6);
	istringstream convert(frag);  //converting to int
	if(!(convert >> final)) { final = 0; }

	return final;
}

int convertString1(ifstream& in_s)
{
	string fragment2, frag;
	int final;

	getline(in_s, fragment2);  //reading in mismmatch score
	frag = fragment2.substr(9);
	istringstream convert(frag);  //converting to int
	if(!(convert >> final)) { final = 0; }

	return final;
}

int convertString2(ifstream& in_s)
{
	string fragment2, frag;
	int final;

	getline(in_s, fragment2); //reading in gap score
	frag = fragment2.substr(4);
	istringstream convert(frag);  //converting to int
	if(!(convert >> final)) { final = 0; }

	return final;
}

int similartity(ifstream& in_s)
{
	string fragment2, frag;
	int final;

	getline(in_s, fragment2);  //reading in copyrightPercent
	frag = fragment2.substr(19);
	istringstream convert(frag);  //converting to int
	if(!(convert >> final)) { final = 0; }

	in_s.close();

	return final;
}

string openSecondFile(string& song1File, int& song1Id, 	string& musicalnotes1)
{
	string SongName;
	string frag;
	ifstream in_s;

	in_s.open(song1File.c_str());   //opening song a file

	if(in_s.fail())								//if file does not exist a fail message will appear
	{
		cout << "Unable to open input file " << song1File << endl;
		exit(EXIT_FAILURE);
	}

	getline(in_s, frag, '|');  //reading in song name
	SongName = frag.substr(1);

	in_s >> song1Id;   //reading in ID

	in_s >> musicalnotes1; //reading in notes

	in_s.clear();

	in_s.close();
	return SongName;
}

string openThirdFile(string& song2File, int& song2Id, 	string& musicalnotes2)
{
	string SongName;
	string frag;
	ifstream in_s;

	in_s.open(song2File.c_str());   //opening song b file

	if(in_s.fail())								//if file does not exist a fail message will appear
	{
		cout << "Unable to open input file " << song2File << endl;
		exit(EXIT_FAILURE);
	}

	getline(in_s, frag, '|');  //reading in song name
	SongName = frag.substr(1);

	in_s >> song2Id;   //reading in ID

	in_s >> musicalnotes2;  //reading in notes
	in_s.close();

	return SongName;
}

int maximum( int a, int b, int c )
{
   int max = ( a < b ) ? b : a;       // returns maximum of 3 ints
   return ( ( max < c ) ? c : max );
}

void AlignmentMtx(vector<vector<int> >& mtx, int song2Size, int song1Size, int rows, int columns, int gap, string musicalnotes1, string musicalnotes2, 	int match, 	int mismmatch)
{
	int t = 0;

	for(int i = 0; i < rows; i++)						//creating 2d matrix size of two songs
	{
		vector<int> v;
		for(int j = 0; j < columns; j++)
		{
			v.push_back(t);
		}
		mtx.push_back(v);
	}

	for(int i = 0; i < columns; i++)
	{
		mtx[0][i] = i*gap;            //initializing the first columns with i*gap
	}

	for(int i = 0; i < rows; i++)
	{
		mtx[i][0] = i*gap;           //initializing the first row with i*gap
	}

	for(int i = 1; i < rows; ++i)
	{
		for(int j = 1; j < columns; ++j)
		{
			int up = mtx[i][j-1] + gap;
			int left = mtx[i-1][j] + gap;									//initializing the inside portion of matrix depending on if notes match or not
			int diag;

			if(musicalnotes1.at(i-1) == musicalnotes2.at(j-1))
			{
				diag = mtx[i-1][j-1] + match;						//if a match, add diagonal with match
			}
			else
			{
				diag = mtx[i-1][j-1] + mismmatch;
			}
			mtx[i][j] = maximum(up, left, diag);  //else find max value
		}
	}
	cout << "Left Song's musical notes: " << musicalnotes1 << endl;
	cout << "Alignment Matrix" << endl;
  cout << setw(3) << "-" << " ";
	for(int i = 0; i < columns-1; ++i)												//simply printing the matrix
	{
			cout << setw(3) << musicalnotes2.at(i) << " ";
	}

	cout << endl;
	for(int i = 0; i < mtx.size(); i++)
	{
		for(int j = 0; j < mtx[i].size(); j++)
		{
			cout << setw(3) << mtx[i][j] << " ";
		}
		cout << endl;
	}
}

void TraceBack(vector<vector<int> > mtx, string musicalnotes1, string musicalnotes2, int gap, int mismmatch, int song2Size, int song1Size, 	string song1, 	string song2, int song1Id, int song2Id, 	int copyrightPercent)
{
	int k = song2Size;								//index variables
	int j = song1Size;
	string s1_align; //musicalnotes1
	string s2_align; //musicalnotes2

	while(k > 1 || j > 1)						//until reaches leftmost or topmost side of matrix
	{
		int op1 = (mtx[j-1][k-1]) + mismmatch;
		int op2 = ((mtx[j][k-1]) + gap);															//computing values for the diagonal, up or left position
		int op3 = ((mtx[j-1][k]) + gap);
		if(musicalnotes1.at(j-1) == musicalnotes2.at(k-1)) 				//if notes match
		{
			s1_align += musicalnotes1.at(j-1);						//add notes to strings
			s2_align += musicalnotes2.at(k-1);

			j = j -1;					//move diagonally
			k = k -1;
		}
		else
		{
			if(mtx[j][k] == op1)						//else check diagonal value and if a match then add letters to string and move diagonally
			{
				s1_align += musicalnotes1.at(j-1);
				s2_align += musicalnotes2.at(k-1);

				j = j -1;
				k = k -1;
			}
			else if(mtx[j][k] == op3)     //else check up value if a match then add letters to string and move up
			{
				s1_align += musicalnotes1.at(j-1);
				s2_align += "-";

				j = j - 1;
			}
			else if(mtx[j][k] == op2)  //else check left value if a match then add letters to string and move left
			{
				s1_align += "-";
				s2_align += musicalnotes1.at(k-1);

				k = k -1;
			}
		}
	};
string finalA;
string finalB;

	if(j == 1 || ((s1_align.size() < s2_align.size()) || (s2_align.size() > s1_align.size())))   //if the song isnt complete add final notes
	{
		s2_align += "-";
		s1_align += musicalnotes1.at(j-1);
	}


	cout << song1Id << "    " << song1 << setw(7) << " :";
for(int x = s1_align.length()-1; x >= 0; x--)									//print alignment backwards
{
	finalA = s1_align[x];
	cout << finalA;
}
cout << endl;
cout << song2Id << "    " << song2 << setw(7) << " :";
for(int x = s2_align.length()-1; x >= 0; x--)
{
	finalB = s2_align[x];
	cout << finalB;
}
cout << endl;

float count = 0;

for(int i = 0; i < s1_align.size(); i++)
{
    if(s1_align[i] == s2_align[i])					//finding similar characters
    {
       count++;
     }
}
float size = s1_align.size();				//computing hamming distance
float hamming = (count/size) * 100;

hamming = nearbyint(hamming);

if(hamming < copyrightPercent)			//comparing to copyright percent and outputting correct statement -
{
	cout << "The similarity between the two songs was " << hamming << "% and is below the similarity threshold " << copyrightPercent << "%. Thus, copyright infringement has not occurred." << endl;
}
else
{
	cout << "The similarity between the two songs was " << hamming << "% and is above the similarity threshold " << copyrightPercent << "%. Thus, copyright infringement has occurred." << endl;
}

}
