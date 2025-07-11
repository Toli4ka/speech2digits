from pathlib import Path
import librosa
import numpy as np

# Load audio files from a directory and extract labels from filenames
# data_dir = Path(__file__).parent.parent / "dataset"

def load_audio_data(data_dir, f_s=8000):
    """
    Loads audio files from a directory and extracts labels from filenames.
    Args:
        data_dir (Path or str): Path to the dataset directory.
    Returns:
        X (list): List of audio arrays.
        y (list): List of integer labels.
    """
    data_dir = Path(data_dir)
    X = []
    y = []
    for file in data_dir.iterdir():
        if file.suffix == '.wav':
            label = int(file.name[0])  # Assumes filenames start with the digit label
            audio, sr = librosa.load(str(file), sr=f_s)
            X.append(audio)
            y.append(label)
    print("Loaded", len(X), "files.")
    return X, y


# Extract the MFCC features from the audio data
def extract_mfcc(X, n_mfcc=13, f_s=8000):
    """
    Extracts MFCC features from audio data.
    Args:
        X (list): List of audio arrays.
        n_mfcc (int): Number of MFCC features to extract.
    Returns:
        mfcc_features (list): List of MFCC feature arrays.
    """
    mfcc_features = [librosa.feature.mfcc(y=audio, sr=f_s, n_mfcc=n_mfcc, n_fft=512, hop_length=128).T for audio in X]
    return mfcc_features