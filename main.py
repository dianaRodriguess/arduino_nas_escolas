from pyfirmata import Arduino
import serial
import time
import lcd

# Configuração da porta serial (substitua por sua porta serial correta)
porta_serial = '/dev/ttyUSB0'  # Use 'COM3' no Windows
baud_rate = 9600  # Taxa de transmissão
arduino = Arduino(porta_serial)

lcd.escrever(arduino, 0, 0, 'Iniciando...')

# Inicializa a conexão serial
ser = serial.Serial(porta_serial, baud_rate)
time.sleep(1)  # Aguarde para garantir que a conexão está estabelecida

try:
    while True:
        if ser.in_waiting > 0:
            temperatura = ser.readline().decode('latin-1').strip()  # Lê e decodifica os dados
            print(f"Temperatura: {temperatura} °C")
            # liblcd.escreverTemp(Arduino(porta_serial), temperatura)
        time.sleep(0.5)
        # liblcd.escrever(Arduino(porta_serial), 0, 0, f'Temperatura: {temperatura} °C')

except KeyboardInterrupt:
    print("\nPrograma interrompido pelo usuário.")
    arduino.exit()

except Exception as e:
    print(f"\nOcorreu um erro: {e}")
    
finally:
    ser.close()
    

