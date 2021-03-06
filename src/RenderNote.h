#ifndef RENDERNOTE_H
#define RENDERNOTE_H
#include "Common.h"
#include "Time.h"
using namespace std;
class RenderNote {
	Time start;
	Time end;
	uint8_t pitch;
	uint8_t volume;
	uint8_t trackIndex;
	bool percussion;
public:
	RenderNote(Time, Time, uint8_t, uint8_t, uint8_t, bool);
	void translate(int);
	void translate(Time);
	Time getStart();
	Time getEnd();
	int8_t getPitch();
	int8_t getVolume();
	int8_t getTrackIndex();
	bool isPercussion();

	class Comparator {
	public:
		bool operator()( const RenderNote *lhs, const RenderNote *rhs ) {
			Time lstart = (*lhs).start;
			Time rstart = (*rhs).start;
			long offl = (long)(192 * (lstart.mBar + lstart.mPos / 4)) + 192;
			long offr = (long)(192 * (rstart.mBar + rstart.mPos / 4)) + 192;
			return offl < offr;
		};
	};

};
#endif // RENDERNOTE_H
