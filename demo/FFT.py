import matplotlib.pyplot as plt
import numpy as np
import serial
import time

select = 0.24 # 240ms

Fs = 484.0/select/2;  # sampling rate
Ts = 1/Fs; # sampling interval
t = np.arange(0,2,Ts/select) # time vector; create Fs samples between 0 and 1.0 sec.
y = np.arange(0,2,Ts/select) # signal vector; create Fs samples

n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # a vector of frequencies; two sides frequency range
frq = frq[range(int(n/20))] # one side frequency range

serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)
for x in range(0, 484):
    line=s.readline() # Read an echo string from B_L4S5I_IOT01A terminated with '\n'
    # print line
    y[x] = float(line)

Y = np.fft.fft(y)/n*2 # fft computing and normalization
Y = Y[range(int(n/20))] # remove the conjugate frequency parts

fig, ax = plt.subplots(2, 1)
ax[0].plot(t,y)
ax[0].set_xlabel('Time')
ax[0].set_ylabel('Amplitude')
ax[1].plot(frq,abs(Y),'r') # plotting the spectrum
ax[1].set_xlabel('Freq (Hz)')
ax[1].set_ylabel('|Y(freq)|')
plt.show()
s.close() 