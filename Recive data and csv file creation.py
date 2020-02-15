import serial
import csv
import time
Filename = 'Filename.csv'
# Check your bluetooth module COM port. After pairing module Open bluetooth -> More bluetooth options -> COM ports
# Also fill baudrate of bluetooth module
serialArduino = serial.Serial('COM10', 9600)   

with open(Filename, mode='a', newline='') as csv_file:

        now = time.strftime('%H:%M:%S')
        fieldnames = ['Time', 'AccX', 'AccY', 'AccZ', 'GyroX', 'GyroY', 'GyroZ', 'MagX', 'MagY', 'MagZ', 'Temp', 'Analog']
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames,delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
        writer.writeheader()
   
while True:
        while (serialArduino.inWaiting() == 0):
            pass
        valueRead =(serialArduino.readline())
        valueRead = valueRead.decode("utf-8")
        #print(valueRead)
        x=valueRead.split()
        print(x)
        with open(Filename, mode='a', newline='') as csv_file:
             
             now = time.strftime('%H:%M:%S')
        
             writer = csv.DictWriter(csv_file, fieldnames=fieldnames,delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
       
             writer.writerow({'Time': now, 'AccX': x[0], 'AccY': x[1], 'AccZ': x[2], 'GyroX': x[3], 'GyroY': x[4], 'GyroZ': x[5], 'MagX': x[6], 'MagY': x[7], 'MagZ': x[8], 'Temp': x[9], 'Analog':x[10]})
             print(valueRead)
