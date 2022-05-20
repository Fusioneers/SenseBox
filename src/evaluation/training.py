import os
from datetime import datetime

import keras
import tensorflow as tf
import numpy as np
from sklearn import metrics
import data_preparation
from model import create_model
from src.evaluation.constants import get_path

epochs = 5
batch_size = 32


def train(epochs,
          batch_size) -> (keras.models.Sequential,
                          np.ndarray, np.ndarray, np.ndarray, np.ndarray):
    (X_train, X_test, y_train, y_test,
     columns, X_scaler, y_scaler) = data_preparation.create_dataset()
    print(f'X_train shape: {X_train.shape}')
    print(f'X_test shape: {X_test.shape}')
    print(f'y_train shape: {y_train.shape}')
    print(f'y_test shape: {y_test.shape}')

    model = create_model(X_train.shape[1:], 1)
    print(model.summary())

    timestamp = datetime.strftime(datetime.now(), '%Y-%m-%d %H-%M-%S.%f')
    checkpoint_filepath = get_path('src', 'evaluation', 'models',
                                   f'model_{epochs}_epochs_{timestamp}.h5')
    model_checkpoint_callback = tf.keras.callbacks.ModelCheckpoint(
        filepath=checkpoint_filepath,
        save_weights_only=False,
        monitor='val_loss',
        mode='max',
        save_best_only=True)

    model.fit(X_train,
              y_train,
              epochs=epochs,
              batch_size=batch_size,
              validation_data=(X_test, y_test),
              callbacks=[model_checkpoint_callback],
              use_multiprocessing=True)

    return model, X_train, X_test, y_train, y_test, columns, X_scaler, y_scaler


def main():
    (model, X_train, X_test, y_train, y_test,
     columns, X_scaler, y_scaler) = train(epochs, batch_size)
    print(X_train.shape)
    y_pred = model.predict(X_test)
    print(metrics.mean_absolute_error(
        y_scaler.inverse_transform(y_test[..., np.newaxis]).squeeze(),
        y_scaler.inverse_transform(y_pred).squeeze()))
    # print('Layer weights:')
    # for layer in model.layers:
    #     print(layer.get_config(), layer.get_weights())


if __name__ == '__main__':
    main()
