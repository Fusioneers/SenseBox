import os

import keras
import numpy as np
import pandas
import pandas as pd
from tensorflow import metrics

import data_preparation
import joblib
import matplotlib.pyplot as plt
import seaborn as sns
from tensorflow_addons import activations

from src.evaluation import constants


def convert_altitude_to_pressure(altitude: np.ndarray) -> np.ndarray:
    A = 0.0000225577
    B = 5.2558
    C = 101325
    return np.power(-altitude * A + 1, B) * C / 100000


def evaluate_csv(model_path,
                 X_scaler_path, y_scaler_path, logger_path,
                 hallog_path):
    model = keras.models.load_model(model_path, custom_objects={
        'activations': activations})
    X_scaler = joblib.load(X_scaler_path)
    y_scaler = joblib.load(y_scaler_path)

    data, _, columns = data_preparation.get_dataset(logger_path, hallog_path,
                                                    None)
    X_dataset = X_scaler.transform(data)
    out = model.predict(X_dataset)
    out = y_scaler.inverse_transform(out)

    return out


def plot(path, X_test, y_test):
    model_path = path  # '/home/daniel/coding/SenseBox/src/evaluation/models/model_2022-05-20 21-40-10.523628.h5'
    X_scaler_path = '/home/daniel/coding/SenseBox/src/evaluation/X_scaler.bin'
    y_scaler_path = '/home/daniel/coding/SenseBox/src/evaluation/y_scaler.bin'
    logger_path = '/home/daniel/coding/SenseBox/data/2022-05-13_Messreihe_Zug_S1_Hbf_Kirchzarten/LOGGER03.CSV'
    hallog_path = '/home/daniel/coding/SenseBox/data/2022-05-13_Messreihe_Zug_S1_Hbf_Kirchzarten/HALLOG03.CSV'
    model = keras.models.load_model(model_path)
    y_scaler = joblib.load(y_scaler_path)

    out = evaluate_csv(model_path,
                       X_scaler_path,
                       y_scaler_path,
                       logger_path,
                       hallog_path)
    print(pd.DataFrame(out, columns=['altitude']).describe())
    data = pd.read_csv(logger_path)
    plt.plot(data['timestamp'], out)
    plt.title(path.split('/')[-1])
    plt.show()

    y_pred = model.predict(X_test)
    error = metrics.mean_absolute_error(
        y_scaler.inverse_transform(y_test[..., np.newaxis]).squeeze(),
        y_scaler.inverse_transform(y_pred).squeeze())

    return error


def main():
    (X_train, X_test, y_train, y_test,
     columns, X_scaler, y_scaler) = data_preparation.create_dataset()
    errors = []

    for path in os.scandir(constants.get_path('src', 'evaluation', 'models')):
        if path.is_file() and 'h5' in path.name:
            try:
                error = plot(path.path, X_test, y_test)
                errors.append([error, path.name])
            except Exception as e:
                print(e)
    print(f'Errors: {errors}')
    print(f'Min: {min(errors)}')


if __name__ == '__main__':
    main()
