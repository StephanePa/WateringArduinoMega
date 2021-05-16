///////////////////////////////////////////////////////////////////////////////
// File spt_timer.h
// Creation date: 2017/09/08
///////////////////////////////////////////////////////////////////////////////

#ifndef SPT_TIMER_H
#define SPT_TIMER_H

#include "spt_definition.h"
#include "arduino.h"

///////////////////////////////////////////////////////////////////////////////
// Class spt_timer
///////////////////////////////////////////////////////////////////////////////
class spt_timer
{
  public:
    // constructor
    spt_timer();
    // Reset function : "Reference" reinitialisation to "CurrentArduinoTimer"
    void Reset();
    // SetTimerValue : "TimerValue" reinitialisation
    void SetTimerValue(unsigned int timervalue); // in second
    unsigned int GetTimerValue(); // in second
    //unsigned int GetReference(); // in second
    // IsDone: true when ("CurrentArduinoTimer" - Reference) >= "TimerValue"
    // IsDone: false when ("CurrentArduinoTimer" - Reference) < "TimerValue"
    bool IsDone();
    // Get Current timetag in seconds : return ("CurrentArduinoTimer" - Reference)/1000;
    double GetCurrentValue(); //in second
  protected:
    // reference timetag
	unsigned long Reference; // in millisecond
    // timer value
    unsigned long TimerValue; // in millisecond
};
///////////////////////////////////////////////////////////////////////////////

#endif // SPT_TIMER_H
