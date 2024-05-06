
            
#!/usr/bin/env python3
import serial, time


temp = 0
temperatura = 0

press = 0
pressione = 0

alt = 0
altezza = 0


def readTemperature():
	temp = ser.readline().decode('utf-8').rstrip()
	temperatura = temp
	print("Temperatura: " + temperatura + " C")
	temp = None
	getTemp(temperatura)

def getTemp(temp):
	return temp
	
	
	
def readPressure():
	press = ser.readline().decode('utf-8').rstrip()
	pressione = press
	print("Pressione: " + pressione + " Pa")
	press = None

def readAlti():
	alt = ser.readline().decode('utf-8').rstrip()
	altezza = alt
	print("Altezza: " + altezza + " m sul livello del mare")
	alt = None
	
def readX():
	rX = ser.readline().decode('utf-8').rstrip()
	x = rX
	print("X: " + x)
	rX = None
	
def readY():
	rY = ser.readline().decode('utf-8').rstrip()
	y = rY
	print("Y: " + y)
	rY = None

def readZ():
	rZ = ser.readline().decode('utf-8').rstrip()
	z = rZ
	print("Z: " + z)
	rZ = None
	
def readLight():
	l = ser.readline().decode('utf-8').rstrip()
	light = l
	print("Livello luminosità: " + light)
	l = None
	
def readSound():
	s = ser.readline().decode('utf-8').rstrip()
	sound = s
	print("Livello suono: " + sound)
	s = None

	
if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            if line == "1":
                print("Air sensor")
                readTemperature()
                time.sleep(2)
                readPressure()
                time.sleep(2)
                readAlti()
                time.sleep(2)
            elif line == "2":
                print("Accellerometer")
                readX()
                time.sleep(2)
                readY()
                time.sleep(2)
                readZ()
                time.sleep(2)
            elif line == "3":
                print("Light Sensor")
                time.sleep(2)
                readLight()
                time.sleep(2)          
            elif line == "4":
                print("Sound Sensor")
                time.sleep(2)
                readSound()
                time.sleep(2)             
            
