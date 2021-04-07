# midterm

## I. Introduction

In this assignment, we will gengerate a waveform with a fixed frequency and the selected slew rate, then send it to the picoscope and PC. By doing this, we can compare the difference between signal displayed on the picoscope, also the sampled signal.

## II. Equipment List
### 1. PC or notebook (or an optional VM copy just in case your notebook fails)
### 2. USB Stick to transfer codes and backup data (Recommended but optional)
### 3. A phone (to take a picture of your hardware setup)
### 4. B_L4S5I_IOT01A
### 5. Bread board
### 6. Buttons * 3 (Please keep the same connection as HW2)
### 7. Picoscope
### 8. uLCD display
### 9. Wires

## III. Implement

![image](https://github.com/107061105/midterm/blob/master/45573.jpg)

We need to contain following

### 1.Inputs
Add buttons on the bread board (as DigitalIn): up, down and select. In this assignment, we can select four different slew rates: 1/8, 1/4, 1/2, 1.
### 2.Display
When we implement this program, we will show four slew rates as a menu in uLCD.
![image](https://github.com/107061105/midterm/blob/master/45570.jpg)
### 3.Generate waveform 
Use DAC to generate a waveform with a fixed frequency and the selected slew rate.
### 4.Measure
Use Picoscope to measure the generated wave form, and use measure function to verify signal.
### 5.Sample
Sample the generated wave form and send the value to PC/Python.
### 6.Analysis
Analyze the captured waveform: show frequency response and wave on screen with Matplotlib.

## IV. Result

The result is as following:
### 1
![image](https://github.com/107061105/midterm/blob/master/1.png)
![image](https://github.com/107061105/midterm/blob/master/Figure_1.png)
### 1/2
![image](https://github.com/107061105/midterm/blob/master/0.5.png)
![image](https://github.com/107061105/midterm/blob/master/Figure_0.5.png)
### 1/4
![image](https://github.com/107061105/midterm/blob/master/0.25.png)
![image](https://github.com/107061105/midterm/blob/master/Figure_0.25.png)
### 1/8
![image](https://github.com/107061105/midterm/blob/master/0.125.png)
![image](https://github.com/107061105/midterm/blob/master/Figure_0.125.png)

