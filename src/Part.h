#ifndef PART_H
#define PART_H
#include "Common.h"
#include "ChromaticEvent.h"
#include "Time.h"
using namespace std;
class Part {
 int8_t startBar;
 int8_t endBar;
 int uniquePart;
 float tempoMod;
 int transpose;
 int scale;
 int arrHint;
 int *currentScale;
 vector<ChromaticEvent*> chromaticEvents;
public:
 static int CHROMATIC_BASE;
 ~Part();
 Part();
 vector<ChromaticEvent*> *getChromaticEventList();
 int getStartBar();
 int getEndBar();
 int getUniquePart();
 void setUniquePart(int);
 double getTempoMod();
 void setTempoMod(double);
 int getTranspose();
 void setTranspose(int);
 int getScale();
 void setScale(int);
 int getArrHint();
 void setArrHint(int);
 void setStartBar(int);
 void setEndBar(int);
 void addEvent(Time,Time,int);
 int computePitch(int);
 int* getScaleOffsets();
};
#endif // PART_H
