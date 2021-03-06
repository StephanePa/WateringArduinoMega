///////////////////////////////////////////////////////////////////////////////
// File spt_timer.cpp
// Creation date: 2017/09/08
///////////////////////////////////////////////////////////////////////////////

#include "spt_timer.h"

///////////////////////////////////////////////////////////////////////////////
// Class spt_timer
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// Public Constructor
//-----------------------------------------------------------------------------
spt_timer::spt_timer()
{
  Reset();
  TimerValue=10000L; // 10 seconds by default
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public Reset function
//-----------------------------------------------------------------------------
void spt_timer::Reset()
{
  Reference=millis();
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public SetTimerValue function
//-----------------------------------------------------------------------------
void spt_timer::SetTimerValue(unsigned int timervalue)
{
  TimerValue=(unsigned long)timervalue;
  TimerValue *= 1000L;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public GetTimerValue function
//-----------------------------------------------------------------------------
unsigned int spt_timer::GetTimerValue()
{
  unsigned long i;
  unsigned int j;
  i = TimerValue / 1000L;
  return ((unsigned int)i);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public IsDone function
//-----------------------------------------------------------------------------
bool spt_timer::IsDone()
{
  if ((millis()-Reference)>=TimerValue) return true;
  return false;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public GetCurrentValue function
//-----------------------------------------------------------------------------
double  spt_timer::GetCurrentValue()
{
  double d;
  unsigned long delta;
  delta=millis()-Reference;
  d=((double)delta)/1000.0;
  return d;
}
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
