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

from src.evaluation import data_extraction, constants


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


def standardize(data: np.ndarray) -> Tuple[
    np.ndarray, preprocessing.StandardScaler]:
    """Get a StandardScaler object.

    Args:
        data: The data to get the scaler from.

    Returns:
         The StandardScaler object.
    """

    scaler = preprocessing.StandardScaler().fit(data)
    return scaler.transform(data), scaler


def add_wind_speed(data: np.ndarray, path: str) -> np.ndarray:
    wind_speed = data_extraction.get_wind_speed(path)
    if wind_speed.shape[0] > 3:
        interp_wind_speed = np.interp(data[:, 0], wind_speed[0], wind_speed[1])
        new_data = np.concatenate((data, interp_wind_speed[..., np.newaxis]),
                                  axis=1)
    else:
        new_data = np.concatenate((data, np.zeros((data.shape[0], 1))), axis=1)
    return new_data


def get_y_dataset():
    pass


def get_dataset(data_path: str,
                wind_path: str,
                fix_height: float = None) -> (np.ndarray, np.ndarray, list):
    data, columns = data_extraction.read_data(data_path)
    X_dataset = add_wind_speed(data, wind_path)

    if fix_height is not None:
        y_dataset = np.full(X_dataset.shape[0], fix_height)
    else:
        y_dataset = get_y_dataset()

    return X_dataset, y_dataset, columns


def plot_data(X_dataset: np.ndarray, y_dataset: np.ndarray, columns: list):
    columns = {key: X_dataset[:, i] for i, key in enumerate(columns)}
    columns['altitude'] = y_dataset
    df = pd.DataFrame(data=columns)
    sns.pairplot(df)
    plt.show()


def aggregate_dataset(test_size: float = 0.1, shuffle=True) -> (
        np.ndarray, np.ndarray, np.ndarray, np.ndarray, list,
        preprocessing.StandardScaler, preprocessing.StandardScaler):
    hallog_file_paths = []
    logger_file_paths = []
    fix_heights = []

    for file in os.scandir(
            constants.get_path('data', 'Messreihen_Rohdaten_10-05-2022')):
        if file.is_file():
            if file.name.startswith('HALLOG'):
                hallog_file_paths.append(file.path)
            elif file.name.startswith('LOGGER'):
                logger_file_paths.append(file.path)
            elif file.name.startswith('FIXHEIGHT'):
                with open(file.path, 'r') as f:
                    fix_heights.append(float(f.readline()))

    X_datasets, y_datasets, columns = [], [], []
    if hallog_file_paths and logger_file_paths:
        for hallog, logger, fix_height in zip(hallog_file_paths,
                                              logger_file_paths,
                                              fix_heights):
            X_dataset, y_dataset, columns = get_dataset(logger, hallog,
                                                        fix_height=fix_height)
            X_datasets.append(X_dataset)
            y_datasets.append(y_dataset)

        X_dataset = np.concatenate(X_datasets, axis=0)
        y_dataset = np.concatenate(y_datasets, axis=0)

        X_dataset, X_scaler = standardize(X_dataset)
        y_dataset, y_scaler = standardize(y_dataset[..., np.newaxis])
        y_dataset = y_dataset.squeeze()

        X_train, X_test, y_train, y_test = model_selection.train_test_split(
            X_dataset, y_dataset, test_size=test_size, shuffle=shuffle)

        return X_train, X_test, y_train, y_test, columns, X_scaler, y_scaler
    else:
        raise FileNotFoundError('There are no logfiles in the data folder.')


def main():
    (X_train, X_test, y_train, y_test,
     columns, X_scaler, y_scaler) = aggregate_dataset()
    print(X_train.shape)
    print(X_test.shape)
    print(y_train.shape)
    print(y_test.shape)
    plot_data(X_train, y_train, columns)


if __name__ == '__main__':
    main()
