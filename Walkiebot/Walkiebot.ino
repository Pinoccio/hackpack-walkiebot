/**
This is the Walkiebot sketch from https://github.com/Pinoccio/library-pinoccio
Modified by @JacobRosenthal to be a wrapper for the excellent TimerThree library
Please get and install that library from: https://github.com/jacobrosenthal/TimerThree

The MIT License (MIT)

Copyright (c) 2014 Pinoccio

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <TimerThree.h>

#include <SPI.h>
#include <Wire.h>
#include <Scout.h>
#include <GS.h>
#include <bitlash.h>
#include <lwm.h>
#include <js0n.h>

#include "version.h"

void setup() {
  Timer3.initialize(20000);
  
  addBitlashFunction("timer3.initialize", (bitlash_function)timer3Initialize);
  addBitlashFunction("timer3.setPeriod", (bitlash_function)timer3SetPeriod);
  addBitlashFunction("timer3.start", (bitlash_function)timer3Start);
  addBitlashFunction("timer3.stop", (bitlash_function)timer3Stop);
  addBitlashFunction("timer3.restart", (bitlash_function)timer3Restart);
  addBitlashFunction("timer3.resume", (bitlash_function)timer3Resume);
  addBitlashFunction("timer3.pwm", (bitlash_function)timer3Pwm);
  addBitlashFunction("timer3.setPwmDuty", (bitlash_function)timer3SetPwmDuty);
  addBitlashFunction("timer3.disablePwm", (bitlash_function)timer3DisablePwm);

  // all directions based on looking at the bot from the back
  addBitlashFunction("wb.centerleft", (bitlash_function)wbCenterLeft);
  addBitlashFunction("wb.centercenter", (bitlash_function)wbCenterCenter);
  addBitlashFunction("wb.centerright", (bitlash_function)wbCenterRight);
  addBitlashFunction("wb.rightforward", (bitlash_function)wbRightForward);
  addBitlashFunction("wb.rightbackward", (bitlash_function)wbRightBackward);
  addBitlashFunction("wb.rightcenter", (bitlash_function)wbRightCenter);
  addBitlashFunction("wb.leftforward", (bitlash_function)wbLeftForward);
  addBitlashFunction("wb.leftbackward", (bitlash_function)wbLeftBackward);
  addBitlashFunction("wb.leftcenter", (bitlash_function)wbLeftCenter);
  addBitlashFunction("wb.centerall", (bitlash_function)wbCenterAll);
  
  addBitlashFunction("wb.leftgaitf", (bitlash_function)wbLeftGaitF);
  addBitlashFunction("wb.rightgaitf", (bitlash_function)wbRightGaitF);
  addBitlashFunction("wb.leftgaitb", (bitlash_function)wbLeftGaitB);
  addBitlashFunction("wb.rightgaitb", (bitlash_function)wbRightGaitB);
  
  addBitlashFunction("wb.stepforward", (bitlash_function)wbStepForward);
  addBitlashFunction("wb.stepbackward", (bitlash_function)wbStepBackward);
  
   // if servo articulation vars aren't set, default them here:
  if (getVar('a'-'a') == 0) { assignVar('a'-'a', 52); } // left servo, forward position
  if (getVar('b'-'a') == 0) { assignVar('b'-'a', 62); } // left servo, center position
  if (getVar('c'-'a') == 0) { assignVar('c'-'a', 72); } // left servo, backward position
  if (getVar('d'-'a') == 0) { assignVar('d'-'a', 54); } // center servo, left leg down
  if (getVar('e'-'a') == 0) { assignVar('e'-'a', 62); } // center servo, both legs down
  if (getVar('f'-'a') == 0) { assignVar('f'-'a', 70); } // center servo, right leg down
  if (getVar('g'-'a') == 0) { assignVar('g'-'a', 72); } // right servo, forward position
  if (getVar('h'-'a') == 0) { assignVar('h'-'a', 62); } // right servo, center position
  if (getVar('i'-'a') == 0) { assignVar('i'-'a', 52); } // right servo, backward position
  
  Scout.setup(SKETCH_NAME, SKETCH_REVISION, SKETCH_BUILD);
  // Add custom setup code here
}

void loop() {
  Scout.loop();
  // Add custom loop code here
}

numvar timer3Initialize(void) {
  Timer3.initialize(getarg(1));
}

numvar timer3SetPeriod(void) {
  Timer3.setPeriod(getarg(1));
}

numvar timer3Start(void) {
  Timer3.start();
}

numvar timer3Stop(void) {
  Timer3.stop();
}

numvar timer3Restart(void) {
  Timer3.restart();
}

numvar timer3Resume(void) {
  Timer3.resume();
}

numvar timer3Pwm(void) {
  Timer3.pwm(getarg(1), getarg(2));
}

numvar timer3SetPwmDuty(void) {
  Timer3.setPwmDuty(getarg(1), getarg(2));
}

numvar timer3DisablePwm(void) {
  Timer3.disablePwm(getarg(1));
}

// walking functions
numvar wbLeftForward(void) {
  Timer3.pwm(5, getVar('a'-'a'));
}

numvar wbLeftCenter(void) {
  Timer3.pwm(5, getVar('b'-'a'));
}

numvar wbLeftBackward(void) {
  Timer3.pwm(5, getVar('c'-'a'));
}

numvar wbCenterLeft(void) {
  Timer3.pwm(4, getVar('d'-'a'));
}

numvar wbCenterCenter(void) {
  Timer3.pwm(4, getVar('e'-'a'));
}

numvar wbCenterRight(void) {
  Timer3.pwm(4, getVar('f'-'a'));
}

numvar wbRightForward(void) {
  Timer3.pwm(3, getVar('g'-'a'));
}

numvar wbRightCenter(void) {
  Timer3.pwm(3, getVar('h'-'a'));
}

numvar wbRightBackward(void) {
  Timer3.pwm(3, getVar('i'-'a'));
}

numvar wbCenterAll(void) {
  Shell.delay(10, "wb.leftcenter");
  Shell.delay(50, "wb.centercenter");
  Shell.delay(100, "wb.rightcenter");
}

numvar wbLeftGaitF(void) {
  Shell.delay(10, "wb.centerleft");
  Shell.delay(100, "wb.rightbackward");
  Shell.delay(200, "wb.leftforward");
}

numvar wbRightGaitF(void) {
  Shell.delay(10, "wb.centerright");
  Shell.delay(100, "wb.leftbackward");
  Shell.delay(200, "wb.rightforward");
}

numvar wbLeftGaitB(void) {
  Shell.delay(10, "wb.centerleft");
  Shell.delay(100, "wb.leftbackward");
  Shell.delay(200, "wb.rightforward");
}

numvar wbRightGaitB(void) {
  Shell.delay(10, "wb.centerright");
  Shell.delay(100, "wb.rightbackward");
  Shell.delay(200, "wb.leftforward");
}

numvar wbStepForward(void) {
  Shell.delay(10, "wb.leftgaitf");
  Shell.delay(300, "wb.rightgaitf");
}

numvar wbStepBackward(void) {
  Shell.delay(10, "wb.rightgaitb");
  Shell.delay(300, "wb.leftgaitb");
}
