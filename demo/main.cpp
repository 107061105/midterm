#include "mbed.h"
#include "uLCD_4DGL.h"
using namespace std::chrono;

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

AnalogIn Ain(A0);
AnalogOut  aout(PA_4);
InterruptIn up(PB_1);
InterruptIn down(PB_4);
InterruptIn confirm(PA_3);
EventQueue queue(64 * EVENTS_EVENT_SIZE);
Timer debounce;                  //define debounce timer
Timer t0;

Thread t;
float ADCdata[500];

int flag = 0;
int c = 1;
int j = 0;
int k = 0;
int _wait = 0;
int _slew = 0;

void Freq_info() {
      uLCD.cls();
      uLCD.printf("\n Slew rate is:\n");
      if (c == 0) {
            uLCD.printf("\n   1\n");
            uLCD.printf("\n   1/2\n");
            uLCD.printf("\n   1/4\n");
            uLCD.printf("\n > 1/8\n");
      } else if (c == 1) {
            uLCD.printf("\n   1\n");
            uLCD.printf("\n   1/2\n");
            uLCD.printf("\n > 1/4\n");
            uLCD.printf("\n   1/8\n");
      } else if (c == 2) {
            uLCD.printf("\n   1\n");
            uLCD.printf("\n > 1/2\n");
            uLCD.printf("\n   1/4\n");
            uLCD.printf("\n   1/8\n");
      } else if (c == 3) {
            uLCD.printf("\n > 1\n");
            uLCD.printf("\n   1/2\n");
            uLCD.printf("\n   1/4\n");
            uLCD.printf("\n   1/8\n");
      }
}

void Freq_confirm() {
      uLCD.printf("\n Confirm!\n");
}

void Freq_up() {
      if (duration_cast<milliseconds>(debounce.elapsed_time()).count() > 500) {
            flag = 0;
            if (c == 3) c = 0;
            else c++;
            queue.call(Freq_info);
            debounce.reset(); //restart timer when the toggle is performed
      }
}

void Freq_down() {
      if (duration_cast<milliseconds>(debounce.elapsed_time()).count() > 500) {
            flag = 0;
            if (c == 0) c = 3;
            else c--;
            queue.call(Freq_info);
            debounce.reset(); //restart timer when the toggle is performed
      }
}

void Freq_conf() {
      if (duration_cast<milliseconds>(debounce.elapsed_time()).count() > 500) {
            flag = 1;
            j = k = 0;
            queue.call(Freq_confirm);
            debounce.reset(); //restart timer when the toggle is performed
      }      
}

int main(void)
{     
      t.start(callback(&queue, &EventQueue::dispatch_forever));
      debounce.start();

      up.rise(Freq_up);
      down.rise(Freq_down);
      confirm.rise(Freq_conf);

      while (1) {
            if (c == 0) {
                  _wait = 220000;
                  _slew = 100;
            } else if (c == 1) {
                  _wait = 200000;
                  _slew = 200;
            } else if (c == 2) {
                  _wait = 160000;
                  _slew = 400;
            } else if (c == 3) {
                  _wait = 80000;
                  _slew = 800;
            }

            if (flag) {
                  for (float i = 0.0f; i < 0.9f; i += 0.009f) {
                        aout = i;
                        wait_us(_slew-15);
                        if (j == 201 || j == 202) ADCdata[k++] = Ain;
                  } 

                  wait_us(_wait);

                  for (float i = 0.9; i > 0.0f; i -= 0.009f) {
                        aout = i;
                        wait_us(_slew-15);
                        if (j == 201 || j == 202) ADCdata[k++] = Ain;                        
                  }
            }
            //if (j == 202 && flag) for (int k = 0; k < 200; k++) printf("%f\r\n", ADCdata[k]);
            j++;
      }
}