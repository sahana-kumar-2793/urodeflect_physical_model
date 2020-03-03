import serial
import syslog
import time
import numpy as np
import matplotlib as plt

#The following line is for serial over GPIO
port = '/dev/ttyS0'
time = []
potentiometerOne = []
potentiometerTwo = []
loadCell = []

fig, axs = plt.subplots(2, 2)
axs[0, 0].plot(x, y)
axs[0, 0].set_title('Axis [0, 0]')
axs[0, 1].plot(x, y, 'tab:orange')
axs[0, 1].set_title('Axis [0, 1]')
axs[1, 0].plot(x, -y, 'tab:green')
axs[1, 0].set_title('Axis [1, 0]')


axs.flat[0].set(xlabel='time', y-label='Stepper Left: Potentiometer')
axs.flat[1].set(xlabel='time', y-label='Stepper Right: Potentiometer')
axs.flat[2].set(xlabel='time', y-label='Load Cell: Testing Rig')

axs.flat[0].plot(time, potentiometerOne)
axs.flat[1].plot(time, potentiometerTwo)
axs.flat[2].plot(time, loadCell)





ard = serial.Serial(port,9600,timeout=5)
time.sleep(2) #wait for Arduino

for i in range(0, 100):
	# Serial read section
    msg = ard.read(ard.inWaiting()) # read all characters in buffer
    print ("Message from arduino: ")
    print (msg)
    currErrors = msg.split(",") #separate errors into list [timestamp, force error, current force error, velocity error, current velocity error]
    time.append(currErrors[0])
    potentiometerOne.append(currErrors[1])
    potentiometerTwo.append(currErrors[2])
    loadCell.append(currErrors[3])


