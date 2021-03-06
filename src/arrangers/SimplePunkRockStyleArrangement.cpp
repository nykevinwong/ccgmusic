#include "SimplePunkRockStyleArrangement.h"
string SimplePunkRockStyleArrangement::getScriptName()
{
    return "Simple Punk Rock Style Arrangement";
}
void SimplePunkRockStyleArrangement::arrange(Song *s)
{
    int bars = s->getBars();
    
    s->addTrack("Melody", GM_RAND_SYNTH_LEAD, 127, 64,false);
    s->addTrack("Alt Voice", GM_RAND_BRASS, 127, 64,false);

    s->addTrack("Guitar Left", GM_RAND_GUITAR, 127, 20,false);
    s->addTrack("Guitar Right", GM_RAND_GUITAR, 127, 100,false);
    s->addTrack("Guitar Center", GM_RAND_GUITAR, 127, 64,false);

    s->addTrack("Bass", GM_RAND_BASS, 127, 64,false);

    s->addTrack("Drums", 16, 127, 64,true);    
    s->addTrack("Brass", GM_RAND_BRASS, 127, 64,false);
  
    int cnt = 0;
    int chorus_cnt = 0;
    int intro_start = this->rndInt(0, 1);
    int bass_start = this->rndInt(0, 4);
    for (int i = 0; i < s->getParts(); ++i )
    {
        switch(s->getPart(i)->getArrHint())
        {
            case MusicScript::MainVoice:
                s->addRenderEvent("Simple Melody", this->rndMax(), 0, s->getPartStartBar(i), s->getPartEndBar(i), 2, this->createTime(0, 0), 0.7);
                break;
            case MusicScript::AltVoice:
                s->addRenderEvent("Simple Melody", this->rndMax(), 1, s->getPartStartBar(i), s->getPartEndBar(i), 2, this->createTime(0, 0), 0.8);
                break;
            case MusicScript::Chorus:
                s->addRenderEvent("Simple Melody", this->rndMax(), 0, s->getPartStartBar(i), s->getPartEndBar(i), 2, this->createTime(0, 0), 0.7);
                break;
            default:
                break;
        }

        if (s->getPart(i)->getArrHint() == MusicScript::Chorus)
        {
            int seed = this->rndMax();
            s->addRenderEvent("Punk Guitar Chords", seed, 4, s->getPartStartBar(i), s->getPartEndBar(i), 0, this->createTime(0, 0), 1.0);
            s->setParam(RenderEvent::MODE, 3);
            s->addRenderEvent("Simple Melody", this->rndMax(), 1, s->getPartStartBar(i), s->getPartEndBar(i), 2, this->createTime(0, 0), 0.8);
            s->addRenderEvent("Fast Bass", this->rndMax(), 5, s->getPartStartBar(i), s->getPartEndBar(i), -1, this->createTime(0, 0), 1.0);
            s->addRenderEvent("Drums - Punk Rock", this->rndMax(), 6, s->getPartStartBar(i), s->getPartEndBar(i) - 1, 1, this->createTime(0, 0), 1.0);
            if(this->rndInt(0,4)>0)
                s->setParam(RenderEvent::FOOT_SNARE, 1);
            if(this->rndInt(0,4)>0)
                s->setParam(RenderEvent::VERSE_HIHAT, 1);
            s->addRenderEvent("Drums - Punk Rock", this->rndMax(), 6, s->getPartEndBar(i) - 1, s->getPartEndBar(i), 1, this->createTime(0, 0), 1.0);
            s->setParam(RenderEvent::TRANSITION, 1);
            if (chorus_cnt > 1)
            {
                s->addRenderEvent("Punk Guitar Chords", seed, 7, s->getPartStartBar(i), s->getPartEndBar(i), 1, this->createTime(0, 0), 1.0);
                s->setParam(RenderEvent::MODE, 2);
            }
            
            chorus_cnt++;
        }
        else
        {
            int bars_cut = this->rndInt(1, 2);
            if (cnt == intro_start)
            {
                s->addRenderEvent("Drums - Punk Rock", this->rndMax(), 6, s->getPartStartBar(i), s->getPartEndBar(i) - bars_cut, 1, this->createTime(0, 0), 1.0);
                s->setParam(RenderEvent::INTRO_HIHAT, 1);
            }
            else
            {
                if (cnt > intro_start)
                {
                    if (this->rndInt(0, 2) > 0)
                    {
                        s->addRenderEvent("Drums - Punk Rock", this->rndMax(), 6, s->getPartStartBar(i), s->getPartEndBar(i) - bars_cut, 1, this->createTime(0, 0), 1.0);
                        s->setParam(RenderEvent::VERSE_HIHAT, 1);
                    }
                    if (this->rndInt(0, 2) > 0)
                    {
                        s->addRenderEvent("Drums - Punk Rock", this->rndMax(), 6, s->getPartStartBar(i), s->getPartEndBar(i) - bars_cut, 1, this->createTime(0, 0), 1.0);
                        s->setParam(RenderEvent::FOOT_SNARE, 1);
                    }
                }
            }
            s->addRenderEvent("Drums - Punk Rock", this->rndMax(), 6, s->getPartEndBar(i) - bars_cut, s->getPartEndBar(i), 1, this->createTime(0, 0), 1.0);
            s->setParam(RenderEvent::TRANSITION, 1);
            s->addRenderEvent("Punk Guitar Chords", this->rndMax(), 4, s->getPartEndBar(i) - bars_cut, s->getPartEndBar(i), 0, this->createTime(0, 0), 1.0);
            s->setParam(RenderEvent::MODE, 3);
            if (cnt >= bass_start)
            {
                s->addRenderEvent("Fast Bass", this->rndMax(), 5, s->getPartStartBar(i), s->getPartEndBar(i) - 1, -1, this->createTime(0, 0), 1.0);
            }
            s->addRenderEvent("Fast Bass", this->rndMax(), 5, s->getPartEndBar(i) - 1, s->getPartEndBar(i), -1, this->createTime(0, 0), 1.0);
            if (cnt == 0)
            {
                s->addRenderEvent("Punk Guitar Chords", this->rndMax(), 4, s->getPartStartBar(i), s->getPartEndBar(i) - bars_cut, 0, this->createTime(0, 0), 1.0);
                s->setParam(RenderEvent::MODE, this->rndInt(1, 2));
            }
            if (cnt == 1)
            {
                s->addRenderEvent("Punk Guitar Chords", this->rndMax(), 4, s->getPartStartBar(i), s->getPartEndBar(i) - bars_cut, 0, this->createTime(0, 0), 1.0);
                s->setParam(RenderEvent::MODE, this->rndInt(1, 2));
                s->addRenderEvent("Punk Guitar Chords", this->rndMax(), 2, s->getPartStartBar(i), s->getPartEndBar(i) - bars_cut, 0, this->createTime(0, 0), 0.9);
                s->setParam(RenderEvent::MODE, this->rndInt(1, 2));
            }
            else
            {
                if (cnt > 1)
                {
                    bool skip = false;
                    if (cnt >= bass_start && cnt > intro_start && this->rndInt(0, 3) == 0)
                    {
                        skip = true;
                    }
                    if (!skip)
                    {
                        s->addRenderEvent("Punk Guitar Chords", this->rndMax(), 4, s->getPartStartBar(i), s->getPartEndBar(i) - bars_cut, 0, this->createTime(0, 0), 1.0);
                        s->setParam(RenderEvent::MODE, this->rndInt(1, 2));
                        s->addRenderEvent("Punk Guitar Chords", this->rndMax(), 2, s->getPartStartBar(i), s->getPartEndBar(i) - bars_cut, 0, this->createTime(0, 0), 0.9);
                        s->setParam(RenderEvent::MODE, this->rndInt(1, 2));
                        s->addRenderEvent("Punk Guitar Chords", this->rndMax(), 3, s->getPartStartBar(i), s->getPartEndBar(i) - bars_cut, 0, this->createTime(0, 0), 0.9);
                        s->setParam(RenderEvent::MODE, this->rndInt(1, 2));
                    }
                }
            }
            
            cnt++;
        }
    }

    int intro = this->rndInt(0, 2);
    if (intro == 1)
    {
        int metros[2]={GM_PERC_SIDE_STICK,GM_PERC_HAND_CLAP};
        int metro=Utils::getRandomArray(metros,2);
        s->addRenderEvent("Metronome", this->rndMax(), 6, 0, 1, 0, this->createTime(-1, 0), 0.8);
        s->setParam(RenderEvent::PITCH, metro);
    }
    else
    {
        if (intro == 0)
        {
            int cymbals[2]={GM_PERC_RIDE_CYMBAL1,GM_PERC_RIDE_CYMBAL2};
            int cymbal=Utils::getRandomArray(cymbals,2);

            s->addRenderEvent("Metronome", this->rndMax(), 6, 0, 1, 0, this->createTime(-1, 0), 0.8);
            s->setParam(RenderEvent::PITCH, cymbal);
        }
    }
    if(this->rndInt(0,1) > 0)
        s->addRenderEvent("Drums - Simple Cymbal", 0, 6, bars - 1, bars, 1, this->createTime(1, 0), 1.0);
}
