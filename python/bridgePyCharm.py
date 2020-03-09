from Phidget22.Phidget import *
from Phidget22.Devices.VoltageRatioInput import *
import time
import matplotlib.pyplot as plt
import numpy as np

y0 = []
y1 = []
x = []

def onVoltageRatioChange(self, voltageRatio):
    volt = voltageRatio
    force = (5.125 * 1000000 * volt) - 1.
    if self.getChannel() == 0:
        y0.append(force)
        # print(y0[0])
    elif self.getChannel() == 1:
        y1.append(force)
        # print(y1[0])
    # print("VoltageRatio [" + str(self.getChannel()) + "]: " + str(force))


def aids():
    voltageRatioInput0 = VoltageRatioInput()
    voltageRatioInput1 = VoltageRatioInput()

    voltageRatioInput0.setChannel(0)
    voltageRatioInput1.setChannel(1)

    voltageRatioInput0.setOnVoltageRatioChangeHandler(onVoltageRatioChange)
    voltageRatioInput1.setOnVoltageRatioChangeHandler(onVoltageRatioChange)

    voltageRatioInput0.openWaitForAttachment(5000000)
    voltageRatioInput1.openWaitForAttachment(5000000)

    try:
        input("Press Enter to Stop\n")
    except (Exception, KeyboardInterrupt):
        pass

    voltageRatioInput0.close()
    voltageRatioInput1.close()

# def main():
aids()

len = len(y1)

y0 = y0[:len]
y1 = y1[:len]

x = np.arange(len)

plt.plot(x, y0, 'tab:blue')
plt.plot(x, y1, 'tab:red')
plt.ylabel("Force (g)")
plt.xlabel("Time (250 ms)")
plt.show()


# main()