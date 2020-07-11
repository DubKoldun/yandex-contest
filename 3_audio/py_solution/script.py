from pydub import AudioSegment
from pydub.silence import split_on_silence

import librosa
import datetime
import numpy as np

sound = AudioSegment.from_wav("/home/vutaliy/Downloads/task.wav")

morseInternational = {
    ".-"   : 'A',
    "-..." : 'B',
    "-.-." : 'C',
    "-.."  : 'D',
    "."    : 'E',
    "..-." : 'F',
    "--."  : 'G',
    "...." : 'H',
    ".."   : 'I',
    ".---" : 'J',
    "-.-"  : 'K',
    ".-.." : 'L',
    "--"   : 'M',
    "-."   : 'N',
    "---"  : 'O',
    ".--." : 'P',
    "--.-" : 'Q',
    ".-."  : 'R',
    "..."  : 'S',
    "-"    : 'T',
    "..-"  : 'U',
    "...-" : 'V',
    ".--"  : 'W',
    "-..-" : 'X',
    "-.--" : 'Y',
    "--.." : 'Z',
    ".----" : '1',
    "..---" : '2',
    "...--" : '3',
    "....-" : '4',
    "....." : '5',
    "-...." : '6',
    "--..." : '7',
    "---.." : '8',
    "----." : '9',
    "-----" : '0',
    ".-.-.-" : '.',
    "--..--" : '?',
    "-.-.--" : '!',
    ".----." : '\'',
    ".-..-." : '"',
    "-.--."  : '(',
    "-.--.-" : ')',
    ".-..."  : '&',
    "---..." : ':',
    "-.-.-." : ';',
    "-..-."  : '/',
    "..--.-" : '_',
    "-...-"  : '=',
    ".-.-."  : '+',
    "-....-" : '-',
    ".--.-." : '@',
    "...-..-" : '$',
    "-.---..." : '*',
    "" : '*'
    }


# Split on loud parts
chunks = split_on_silence(sound,
    # Must be silent for at least 0.2 of a second
    min_silence_len=500,

    # Consider it silent if quieter than -40 dBFS
    silence_thresh=-45
)

ans = ""

for i, chunk in enumerate(chunks):
    # Export
    chunk.export("/home/vutaliy/prod/yandex_contest/3_audio/py_solution/buff/chunk{0}.wav".format(i), format="wav")
    
    # Get file duration in seconds
    y, sr = librosa.core.load("/home/vutaliy/prod/yandex_contest/3_audio/py_solution/buff/chunk{0}.wav".format(i))
    y_mono = librosa.to_mono(y)

    # Duration in seconds
    duration = librosa.get_duration(y)
    print ("{0}".format(i))
    print("File duration(s): ", str(duration))

    # Find peaks ищи пики ручками !!! TODO()
    onset_env = librosa.onset.onset_strength(y=y_mono, sr=sr,
                                            hop_length=512,
                                            aggregate=np.median, fmax=8000, n_mels=256)
    peaks = librosa.util.peak_pick(onset_env, 3, 3, 3, 5, 5, 10)

    times = librosa.frames_to_time(peaks, sr=sr)
    prev = times[0]
    last = prev
    s = ""

    for i, some in enumerate(times):
        if i != 0:
            if some - prev < 0.6: 
                s = s + '.'
            else:
                s = s + '-'  
            prev = some
        last = some
    if duration - last < 0.6: 
        s = s + '.'
    else:
        s = s + '-' 
    
    print('Peaks detected at: ', librosa.frames_to_time(peaks, sr=sr))
    print (morseInternational[s])
    ans = ans + s + " "

print (ans)