#ifndef SIMPLERANDOMRYTHM_H
#define SIMPLERANDOMRYTHM_H
#include "Common.h"
#include "MusicScript.h"
#include "RythmGenerator.h"
#include "UniquePhrase.h"
#include "Time.h"
using namespace std;
class SimpleRandomRythm : public RythmGenerator {
public:
 void Add(UniquePhrase*,Time,Time);
 void generateRythm(UniquePhrase*);
};
#endif // SIMPLERANDOMRYTHM_H
