#!/usr/bin/env python3
import serial

# Funzione per leggere e stampare i dati del sensore di temperatura
def read_temperature(serial_connection):
    serial_connection.write(b'0\n')  # Invia il comando per leggere la temperatura
    temperature_data = serial_connection.readline().decode().strip()
    print("Temperatura:", temperature_data, "°C")

# Funzione per leggere e stampare i dati del sensore di accelerazione
def read_acceleration(serial_connection):
    serial_connection.write(b'1\n')  # Invia il comando per leggere l'accelerazione
    acceleration_data = serial_connection.readline().decode().strip()
    print("Accelerazione:", acceleration_data)

# Funzione per leggere e stampare i dati del sensore di luce
def read_light(serial_connection):
    serial_connection.write(b'2\n')  # Invia il comando per leggere la luce
    light_data = serial_connection.readline().decode().strip()
    print("Livello di luce:", light_data)

# Funzione per leggere e stampare i dati del sensore del suono
def read_sound(serial_connection):
    serial_connection.write(b'3\n')  # Invia il comando per leggere il suono
    sound_data = serial_connection.readline().decode().strip()
    print("Livello di suono:", sound_data)

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode().rstrip()
            if line == "1":  # Se il comando "1" è stato inviato dall'Arduino (temperatura)
                read_temperature(ser)
            elif line == "2":  # Se il comando "2" è stato inviato dall'Arduino (accelerazione)
                read_acceleration(ser)
            elif line == "3":  # Se il comando "3" è stato inviato dall'Arduino (luce)
                read_light(ser)
            elif line == "4":  # Se il comando "4" è stato inviato dall'Arduino (suono)
                read_sound(ser)
