import os

def build_index(path):
    for root, dirs, files in os.walk(path):
        for file in files:
            if os.path.splitext(file)[1] != '.mp4':
                files.remove(file)
    print(files)
    print(len(files))

build_index("/Users/lovever/Movies/命运石之门")
