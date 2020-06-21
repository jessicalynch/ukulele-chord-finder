#ifndef __UKULELE__H__
#define __UKULELE__H__

#include "customErrorClass.h"
#include <iostream>
#include <fstream>
#include <string>

#define NUM_STRINGS 4
#define NUM_SEMITONES 12

using namespace std;

class Ukulele{
    
    public:
        Ukulele(void);
        ~Ukulele(void);
        static string notes[NUM_SEMITONES];

        void printFretboardTones(void);
        void printFretboardNotes(void);
        void printChord(string, string);

    private:
        int **fretboard;
        int *shape; // chord shape

        void p_PrintFretboard(int);
        void p_BuildChord(int, int);

};

#endif