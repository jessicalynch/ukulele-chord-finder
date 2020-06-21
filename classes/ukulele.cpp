#include "ukulele.h"
#include "customErrorClass.h"
#include <iostream>
#include <iomanip>
#include<bits/stdc++.h> 

/*****************************************************************************************/
/*                                   PUBLIC FUNCTIONS                                    */
/*****************************************************************************************/

/**************************** PUBLIC: Constructor ****************************/
Ukulele::Ukulele()
{
    int i = 0;
    shape = new int[NUM_STRINGS];
    fretboard = new int*[NUM_STRINGS];
    int offset[4] = {9, 4, 0, 7};

	for (i = 0; i < 4; ++i) 
    {
        fretboard[i] = new int[NUM_SEMITONES];

		for (int j = 0; j < NUM_SEMITONES; ++j) 
        {
            fretboard[i][j] = (j + offset[i]) % NUM_SEMITONES;
		}
	}
}

/**************************** PUBLIC: Destructor *************************************/
Ukulele::~Ukulele() 
{
    delete shape;
    
    int i = 0;
    for (i = 0; i < 4; ++i) 
    {
        delete fretboard[i];
    }

    delete fretboard;
}

/**************************** PUBLIC: printFretboardTones ****************************/
/* Print fretboard with int note values */
void Ukulele::printFretboardTones() 
{
    p_PrintFretboard(0);
}

/**************************** PUBLIC: printFretboardNotes ****************************/
/* Print fretboard with letter notes */
void Ukulele::printFretboardNotes() 
{
    p_PrintFretboard(1);
}

/**************************** PUBLIC: printChord *************************************/
void Ukulele::printChord(string rootNote, string chordType) 
{

    int i = 0, rootTone = -1;

    // Make sure rootNote is capital letter
    transform(rootNote.begin(), rootNote.end(), rootNote.begin(), ::toupper);

    // Find numeric value of rootNote
    for (i = 0; i < NUM_SEMITONES; i++)
    {
        if (rootNote.compare(Ukulele::notes[i]) == 0)
        {
            rootTone = i;
            break;
        }        
    }

    // Throw exception if rootNote is not in notes array
    if (rootTone == -1)
        throw myException("Not a valid root note", ERROR);

    // Build the chord
    try 
    {
        if (chordType == "M")
        {
            p_BuildChord(rootTone, 0);
        }
        else if (chordType == "m")
        {
            p_BuildChord(rootTone, 1);
        }
        else 
        {
            throw myException("Not a valid chord type", ERROR);
        }
    }
    catch (myException &e)
    {
        throw e;
    }
    
    // Print the shape
    for (i = 0; i < NUM_STRINGS; i++)
    {
        cout << notes[fretboard[i][0]] << " |--" << shape[i] << "--|" << endl;
    }

}

/*****************************************************************************************/
/*                                   PRIVATE FUNCTIONS                                   */
/*****************************************************************************************/

/**************************** PRIVATE: p_PrintFretboard ****************************/
void Ukulele::p_PrintFretboard(int option) 
{
  int m = 0, n = 0;
	for (m = 0; m < 4; ++m)
    {
		for (n = 0; n < NUM_SEMITONES; ++n)
        {
            if (option == 0) // tones
                cout << setfill('0') << setw(2) << fretboard[m][n];
            else // notes
                cout << setfill(' ') << left << setw(2) << Ukulele::notes[fretboard[m][n]];

			if (n == 0)
                cout << "|| ";
			else
                cout << " | ";

		}
		cout << endl;
	}
}

/**************************** PRIVATE: p_BuildChord ********************************/
void Ukulele::p_BuildChord(int root, int type) 
{
    int thirdOffset = -1, fifthOffset = -1;
    if (type == 0) // major
    { 
        thirdOffset = 4;
        fifthOffset = 7;
    }
    else if (type == 1) // minor
    {
        thirdOffset = 3; // flattened third
        fifthOffset = 7;
    }
    
    int i = 0, j = 0;
	for (i = 0; i < NUM_STRINGS; i++) 
		shape[i] = -1;

	int third = 0, fifth = 0;
    third = (root + thirdOffset) % NUM_SEMITONES;
	fifth = (root + fifthOffset) % NUM_SEMITONES;

	int rootFound = 0, thirdFound = 0, fifthFound = 0;
    int search_range = 5;
    int fret = 0;

	for (i = 0; i < NUM_STRINGS; i++) 
    {
		for (j = 0; j < search_range; j++) 
        {
            fret = fretboard[i][j];

			if (fret == root) 
            {
				shape[i] = j;
				rootFound += 1;
                break;
			}
            else if (fret == third) {
				shape[i] = j;
				thirdFound += 1;
                break;
			}
			else if (fret == fifth) 
            {
				shape[i] = j;
				fifthFound += 1;
                break;
			}

		}
	}

    /* TODO: handle missing tones */
	if (!thirdFound)
        throw myException("The third was not found.", ERROR);
	
	if (!fifthFound)
        throw myException("The fifth was not found.", ERROR);

}


/*****************************************************************************************/
/*                                   STATIC FUNCTIONS                                    */
/*****************************************************************************************/

string Ukulele::notes[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
