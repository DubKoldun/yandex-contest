from pydub import AudioSegment
from pydub.silence import split_on_silence

sound = AudioSegment.from_wav("/home/vutaliy/Downloads/task.wav")
# sound = AudioSegment.from_file("sound1.wav")

chunks = split_on_silence(sound,
    # must be silent for at least half a second
    min_silence_len=500,

    # consider it silent if quieter than -16 dBFS
    silence_thresh=-28
)

for i, chunk in enumerate(chunks):
    chunk.export("/home/vutaliy/prod/yandex_contest/3_audio/cpp_solution/chunk{0}.wav".format(i), format="wav")
