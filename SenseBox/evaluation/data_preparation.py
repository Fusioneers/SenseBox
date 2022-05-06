import os
from typing import Optional, Tuple
import datetime
import time

import numpy as np
import pandas as pd
import seaborn as sns
from matplotlib import pyplot as plt
from sklearn import preprocessing
from sklearn import model_selection

from SenseBox.evaluation import data_extraction, constants

GROUND_TRUTH_COLUMN = 5  # 'altitude'
DATA_COLUMNS = ['time', 'temperature', 'pressure', 'humidity', 'altitude',
                'uv']


# os.path.join(ABS_PATH, 'data', 'Fahrradtour_Vg_03-05-2022',
# 'Test_Sensorbox.gpx')
# convert the time format
# data = [convert_time_format(d) for d in data if d is not None]


# TODO get the time
def convert_time_format(data: np.ndarray) -> np.ndarray:
    """Convert the time format of the data to unix time.

    Args:
        data: The data to convert.

    Returns:
         The data with the time format converted.
    """

    out = data
    for row in out:
        row[0] = np.random.randint(0, 100)
    return out


def get_standard_scaler(data) -> preprocessing.StandardScaler:
    """Get a StandardScaler object.

    Args:
        data: The data to get the scaler from.

    Returns:
         The StandardScaler object.
    """
    scaler = preprocessing.StandardScaler().fit(data)
    return scaler


def add_wind_speed(data: np.ndarray, path: str) -> np.ndarray:
    wind_speed = data_extraction.get_wind_speed(path)
    interp_wind_speed = np.interp(data[:, 0], wind_speed[0], wind_speed[1])
    new_data = np.concatenate((data, interp_wind_speed[..., np.newaxis]),
                              axis=1)
    return new_data


def get_y_dataset():
    pass


def get_dataset(data_path: str, wind_path: str, test_size: float = 0.1,
                shuffle=True) -> (
        np.ndarray, np.ndarray, np.ndarray, np.ndarray, list):
    data, columns = data_extraction.read_data(data_path)
    data = add_wind_speed(data, wind_path)

    scaler = get_standard_scaler(data)
    X_dataset = scaler.transform(data)
    y_dataset = get_y_dataset()

    X_train, X_test, y_train, y_test = model_selection.train_test_split(
        X_dataset, y_dataset, test_size=test_size, shuffle=shuffle)

    return X_train, X_test, y_train, y_test, columns


def plot_data(X_dataset: np.ndarray, y_dataset: np.ndarray, columns: list):
    columns = {key: X_dataset[:, i] for i, key in enumerate(DATA_COLUMNS)}
    columns['altitude'] = y_dataset
    df = pd.DataFrame(data=columns)
    sns.pairplot(df)
    plt.show()


def main():
    X_train, X_test, y_train, y_test, columns = get_dataset(
        constants.get_path('data', 'Fahrradtour_Vg_03-05-2022', 'datalogger',
                           'LOGGER01.CSV'),
        constants.get_path('data', 'Fahrradtour_Vg_03-05-2022',
                           'datalogger-hall-sensor', 'HALLOG01.CSV'))
    print(X_train.shape)
    print(X_test.shape)
    print(y_train.shape)
    print(y_test.shape)
    plot_data(X_train, y_train, columns)


if __name__ == '__main__':
    main()
