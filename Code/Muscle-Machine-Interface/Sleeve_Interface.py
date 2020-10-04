#!/usr/bin/env python
import numpy as np
import serial
import time
import pandas as pd


class SleeveInterface:

    def __init__(self):

        # Variables
        self.data = []
        comport = "/dev/ttyACM0"

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

    def write_data(self, data, filename):
        if len(data):
            print('Writing Data')
            d = np.asarray(data)
            dd = np.reshape(d[0], [1, d[0].shape[0]])
            for i in range(d.shape[0] - 1):
                dd = np.concatenate((dd, np.reshape(d[i + 1], [1, d[i + 1].shape[0]])), 0)
            # concatenate the load cell information to the other features
            # dd = np.concatenate((dd, self.data_load_cell), 0)
            df = pd.DataFrame(data=dd)
            df.to_csv(filename, index=False)
            print('Filename: {}, Rows: {}, Cols: {}'.format(filename, dd.shape[0], dd.shape[1]))

    def run(self):
        while True:
            try:
                data = self.read_port()
                self.data.append(data)
            except KeyboardInterrupt:
                break

        self.port.close()
        self.write_data(self.data, 'pinch.csv')


if __name__ == "__main__":
    A = SleeveInterface()
    A.run()
