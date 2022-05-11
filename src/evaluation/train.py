import os
from datetime import datetime

import keras
import numpy as np

import data_preparation
from model import create_model
from src.evaluation.constants import ABS_PATH

epochs = 6
batch_size = 32


def train(epochs,
          batch_size) -> (keras.models.Sequential,
                          np.ndarray, np.ndarray, np.ndarray, np.ndarray):
    """Train the model.

    Args:
        epochs: Number of epochs to train the model.
        batch_size: Batch size for training.

    Returns:
        The trained model.
    """

    (X_train, X_test, y_train, y_test,
     columns, X_scaler, y_scaler) = data_preparation.aggregate_dataset()
    print(f'X_train shape: {X_train.shape}')
    print(f'X_test shape: {X_test.shape}')
    print(f'y_train shape: {y_train.shape}')
    print(f'y_test shape: {y_test.shape}')

    model = create_model(X_train.shape[1:], 1)
    print(model.summary())
    model.fit(X_train, y_train, epochs=epochs, batch_size=batch_size,
              validation_data=(X_test, y_test))

    return model, X_train, X_test, y_train, y_test, columns, X_scaler, y_scaler


def main():
    (model, X_train, X_test, y_train, y_test,
     columns, X_scaler, y_scaler) = train(epochs, batch_size)
    print(X_train.shape)
    score = model.evaluate(X_test, y_test)
    print(y_scaler.inverse_transform(
        np.array(score)[..., np.newaxis, np.newaxis]).squeeze())
    model.save(
        os.path.join(ABS_PATH, 'src', 'evaluation', 'models',
                     f'model_{epochs}_epochs_{datetime.now()}.h5'))


if __name__ == '__main__':
    main()
