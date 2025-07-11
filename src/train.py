import numpy as np
import tensorflow as tf
import argparse
from pathlib import Path
# from keras.models import Sequential
from sklearn.model_selection import train_test_split
from utils import load_audio_data, extract_mfcc

def train_model(data_dir, model_save_path, f_s=8000, n_mfcc=13, test_size=0.2, random_state=42):
    """
    Trains a neural network model on audio data.
    
    Args:
        data_dir (str): Path to the dataset directory.
        model_save_path (str): Path to save the trained model.
        f_s (int): Sampling frequency for audio files.
        n_mfcc (int): Number of MFCC features to extract.
        test_size (float): Proportion of the dataset to include in the test split.
        random_state (int): Random seed for reproducibility.
    """
    # Load audio data
    X, y = load_audio_data(data_dir, f_s)
    
    # Extract MFCC features
    mfcc_features = extract_mfcc(X, n_mfcc, f_s)
    
    # Pad sequences to ensure uniform input size
    max_length = max(len(mfcc) for mfcc in mfcc_features)
    X_padded = tf.keras.preprocessing.sequence.pad_sequences(mfcc_features, maxlen=max_length, padding='post', dtype='float32')
    
    # Convert labels to numpy array
    y = np.array(y)
    
    # Determine feature size for input layer
    feature_size = X_padded.shape[1]
    
    # Split the dataset into training and testing sets
    X_train, X_test, y_train, y_test = train_test_split(X_padded, y, test_size=test_size, random_state=random_state)
    
    # Define a simple neural network model
    model = tf.keras.Sequential([
        tf.keras.layers.Input(shape=(feature_size,)),
        tf.keras.layers.Dense(32, activation='relu'),
        tf.keras.layers.Dense(10, activation='softmax')
    ])
    # Compile the model
    model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
    
    # Train the model
    model.fit(X_train, y_train, epochs=10, batch_size=32, validation_data=(X_test, y_test))
    
    # Save the trained model
    model.save(model_save_path)
    
    print("Model trained and saved at", model_save_path)


if __name__ == "__main__":
    
    # parser = argparse.ArgumentParser(description="Train a neural network model on audio data.")
    # parser.add_argument('--data_dir', type=str, required=False, help='Path to the dataset directory.')
    # parser.add_argument('--model_save_path', type=str, required=False, help='Path to save the trained model.')
    # parser.add_argument('--f_s', type=int, default=8000, help='Sampling frequency for audio files.')
    # parser.add_argument('--n_mfcc', type=int, default=13, help='Number of MFCC features to extract.')
    
    # args = parser.parse_args()
    data_dir = Path(__file__).parent.parent / "dataset"
    model_save_path = Path(__file__).parent.parent / "models" / "audio_model.h5"
    f_s = 8000
    n_mfcc = 13
    train_model(data_dir, model_save_path, f_s, n_mfcc)