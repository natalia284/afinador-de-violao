import pyaudio
import numpy as np
import matplotlib.pyplot as plt
import serial
import time
import struct
arduino = serial.Serial('/dev/ttyUSB0', 115200, timeout=.1)

time.sleep(1)

# Não usar notação científica
np.set_printoptions(suppress=True)

# Número de pontos de dados a ser lido por vez
CHUNK = 4096

# Resolução de tempo do dispositivo de gravação (Hz)
RATE = 44100

# Inicializa a classe PyAudio

p=pyaudio.PyAudio() 

# Habilita o microfone conetado ao computador

stream=p.open(format=pyaudio.paInt16,channels=1,rate=RATE,input=True,
              frames_per_buffer=CHUNK)

# Cria um array numpy contendo uma única leitura de dados de áudio
# Fica executando o código infinitamente

while True: 

    # Realiza a leitura dos dados de 16 bit inteiro
    data = np.fromstring(stream.read(CHUNK),dtype=np.int16)
    
    # Suaviza o TRF por janelas de dados
    data = data * np.hanning(len(data)) 

    # Filtra apenas a parte positiva do sinal 
    fft = abs(np.fft.fft(data).real)

    # Calcula a frequência usando o TDF

    fft = fft[:int(len(fft)/2)] 
    freq = np.fft.fftfreq(CHUNK,1.0/RATE)
    freq = freq[:int(len(freq)/2)] 
    freqPeak = freq[np.where(fft==np.max(fft))[0][0]]+1

    # Imprime os valores de frequências em (Hz)
    print("Frequência: %d Hz"%freqPeak)

    # Classifica as frequências e envia o sinal para o Arduino
    
    if (freqPeak > 300 and freqPeak <= 340):
        print("Mizinho")
        arduino.write(struct.pack('>B', 1))
    elif (freqPeak > 200 and freqPeak <= 255):
        print("Si")
        arduino.write(struct.pack('>B', 2))
    elif (freqPeak > 170 and freqPeak <= 199):
        print("Sol")
        arduino.write(struct.pack('>B', 3))
    elif (freqPeak > 120 and freqPeak <= 157):
        print("Ré")
        arduino.write(struct.pack('>B', 4))
    elif (freqPeak > 90 and freqPeak <= 115):
        print("Lá")
        arduino.write(struct.pack('>B', 5))
    elif (freqPeak >= 65 and freqPeak <= 100 and freqPeak != 162):
        print("Mizão")
        arduino.write(struct.pack('>B', 6))
    else:
        arduino.write(struct.pack('>B', 0))

# Mostra os gráficos das amostras 

plt.plot(freq,fft)
plt.axis([0,4000,None,None])
plt.show()
plt.close()

# Encerra a execução do programa normalmente

stream.stop_stream()
stream.close()
p.terminate()