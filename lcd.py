from pyfirmata import util, STRING_DATA

def escrever(placa, col, lin, texto):
    dados = str(col) + ';' + str(lin) + ';' + texto
    if dados:
        placa.send_sysex(STRING_DATA, util.str_to_two_byte_iter(dados))
        
def limpar(placa):
    escrever(placa, 0, 0, ' ' * 16)
    escrever(placa, 0, 1, ' ' * 16)
    
def escreverTemp(placa, temp):
    escrever(placa, 0, 0, f'Temperatura: {temp} °C')