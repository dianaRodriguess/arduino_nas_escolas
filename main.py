import pyfirmata
import time

# Configuração da placa Arduino
port = 'COM3'  # Altere para a porta correta do seu Arduino
board = pyfirmata.Arduino(port)

# Configuração dos pinos
temp_pin = board.get_pin('a:0:i')  # Pino analógico A0 para o sensor LM35
red_pin = board.get_pin('d:9:p')   # Pino digital 9 para o LED vermelho
green_pin = board.get_pin('d:10:p') # Pino digital 10 para o LED verde
blue_pin = board.get_pin('d:11:p')  # Pino digital 11 para o LED azul

# Função para definir a cor do LED RGB
def set_color(red, green, blue):
    red_pin.write(red)
    green_pin.write(green)
    blue_pin.write(blue)

# Inicializa o iterator para leitura dos sensores
it = pyfirmata.util.Iterator(board)
it.start()
temp_pin.enable_reporting()

try:
    while True:
        temp_value = temp_pin.read()
        if temp_value is not None:
            temp_celsius = temp_value * 5.0 * 100.0  # Conversão para graus Celsius
            print(f'Temperatura: {temp_celsius:.2f} °C')

            if temp_celsius < 25:
                set_color(0, 0, 1)  # Azul (Endotérmica)
            elif temp_celsius > 30:
                set_color(1, 0, 0)  # Vermelho (Exotérmica)
            else:
                set_color(0, 1, 0)  # Verde (Normal)

        time.sleep(1)

except KeyboardInterrupt:
    print("Programa interrompido pelo usuário")

finally:
    board.exit()

