from pydub import AudioSegment
from pydub.silence import split_on_silence

import librosa
import datetime
import numpy as np

sound = AudioSegment.from_wav("/home/vutaliy/Downloads/task.wav")

# morseInternational = {"."}

# Split on loud parts
chunks = split_on_silence(sound,
    # Must be silent for at least 0.2 of a second
    min_silence_len=200,

    # Consider it silent if quieter than -40 dBFS
    silence_thresh=-40
)

for i, chunk in enumerate(chunks):
    # Export
    chunk.export("/home/vutaliy/prod/yandex_contest/3_audio/py_solution/buff/chunk{0}.wav".format(i), format="wav")
    
    # Get file duration in seconds
    y, sr = librosa.core.load("/home/vutaliy/prod/yandex_contest/3_audio/py_solution/buff/chunk{0}.wav".format(i))
    y_mono = librosa.to_mono(y)

    # Duration in seconds
    duration = librosa.get_duration(y)
    print ("{0}".format(i))
    print("File duration(s): ", str(datetime.timedelta(seconds=duration)))

    # Find peaks
    onset_env = librosa.onset.onset_strength(y=y_mono, sr=sr,
                                            hop_length=512,
                                            aggregate=np.median, fmax=8000, n_mels=256)
    peaks = librosa.util.peak_pick(onset_env, 3, 3, 3, 5, 5, 10)
    print('Peaks detected at: ', librosa.frames_to_time(peaks, sr=sr))


h