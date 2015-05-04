//
//  Knob.h
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 4/24/15.
//
//

#ifndef ChuckPluginTest4_KnobInfo_h
#define ChuckPluginTest4_KnobInfo_h


#endif


enum knobType
{
    linear=0,
    logarithmic,
    exponential
};

struct KnobInfo
{
    KnobInfo():type(linear) {};
    float value01;
    float valueConverted;
    knobType type;
    int knobId;
    
    
};

