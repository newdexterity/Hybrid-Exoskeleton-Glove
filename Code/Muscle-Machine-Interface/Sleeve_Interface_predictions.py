#!/usr/bin/env python
import numpy as np
import serial
import time
import pandas as pd
import pickle


class SleeveInterface:

    def __init__(self):

        # Variables
        self.data = []
        comport = "/dev/ttyACM0"
        filename = 'gesture_classifier'
        self.mdl = pickle.load(open(filename, 'rb'))
        self.pred_window = []
        self.pred_window_val = 10

        # Open Serial Port
        self.port = serial.Serial(comport, timeout=None, baudrate=115200, xonxoff=False, rtscts=False, dsrdtr=False)
        time.sleep(2)

    def read_port(self):

        # Read Serial port
        string = self.port.readline().rstrip()
        chunks = np.array(string.split(','))

        e1 = float(chunks[0])
        e2 = float(chunks[1])
        e3 = float(chunks[2])
        f1 = float(chunks[3])
        f2 = float(chunks[4])
        f3 = float(chunks[5])
        f4 = float(chunks[6])
        f5 = float(chunks[7])

        data = np.array([e1, e2, e3, f1, f2, f3, f4, f5])
        return data

    def run(self):
        while True:
            try:
                data = self.read_port()
                p = self.mdl.predict(data)
                self.pred_window.append(p[0])

                if len(self.pred_window) >= self.pred_window_val:
                    vote = max(set(self.pred_window), key=self.pred_window.count)
                    self.pred_window.pop(0)
                    if vote == 0:
                        print('Rest')
                    elif vote == 1:
                        print('Pinch')
                    elif vote == 2:
                        print('Tripod')
                    elif vote == 3:
                        print('Power')
                    elif vote == 4:
                        print('Spherical')
                    elif vote == 5:
                        print('Key')

            except KeyboardInterrupt:
                break

        self.port.close()


if __name__ == "__main__":
    A = SleeveInterface()
    A.run()
