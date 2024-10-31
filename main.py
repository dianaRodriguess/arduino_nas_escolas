import serial
import time

# Configuração da porta serial (substitua por sua porta serial correta)
porta_serial = '/dev/ttyUSB0'  # Use 'COM3' no Windows
baud_rate = 9600  # Taxa de transmissão

# Inicializa a conexão serial
ser = serial.Serial(porta_serial, baud_rate)
time.sleep(2)  # Aguarde para garantir que a conexão está estabelecida

try:
    while True:
        if ser.in_waiting > 0:
            temperatura = ser.readline().decode('latin-1').strip()  # Lê e decodifica os dados
            print(f"Temperatura: {temperatura} °C")
        time.sleep(1)

except KeyboardInterrupt:
    print("Programa interrompido pelo usuário.")

finally:
    ser.close()
