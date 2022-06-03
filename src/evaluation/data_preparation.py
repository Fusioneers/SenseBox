import os
from typing import Tuple, Optional

import numpy as np
import pandas as pd
import seaborn as sns
from matplotlib import pyplot as plt
from sklearn import model_selection
from sklearn import preprocessing
import joblib

from src.evaluation import data_extraction, constants


def standardize(data: np.ndarray) -> Tuple[
    np.ndarray, preprocessing.StandardScaler]:
    scaler = preprocessing.StandardScaler().fit(data)
    return scaler.transform(data), scaler


# def add_wind_speed(data: np.ndarray, path: str) -> np.ndarray:
#     wind_speed = data_extraction.get_wind_speed(path)
#     if wind_speed.shape[0]:
#         wind_speed = np.concatenate(
#             ([[0, 0]], wind_speed, [[data[0, -1], 0]]), axis=0)
#         interp_wind_speed = np.interp(data[:, 0], wind_speed[0], wind_speed[1])
#         with open('interp_wind_speed.txt', 'w') as f:
#             f.write(str(interp_wind_speed.tolist()))
#         with open('wind_speed.txt', 'w') as f:
#             f.write(str(wind_speed.tolist()))
#         new_data = np.concatenate((data, interp_wind_speed[..., np.newaxis]),
#                                   axis=1)
#     else:
#         new_data = np.concatenate((data, np.zeros((data.shape[0], 1))), axis=1)
#     return new_data


def get_dataset(logger_path: str,
                fix_height: Optional[float]) -> (np.ndarray, np.ndarray, list):
    X_dataset, columns = data_extraction.read_data(logger_path)

    if fix_height is not None:
        y_dataset = np.full(X_dataset.shape[0], fix_height)
        return X_dataset, y_dataset, columns
    else:
        return X_dataset, None, columns


def get_paths():
    hallog_file_paths = []
    logger_file_paths = []
    fix_heights = []

    for folder in os.scandir(constants.get_path('data')):
        if folder.is_dir():
            if '_Messreihe_' in folder.name \
                    and 'Zug' not in folder.name:
                for file in os.scandir(folder.path):
                    if file.is_file():
                        if file.name.startswith('HALLOG'):
                            hallog_file_paths.append(file.path)
                        elif file.name.startswith('LOGGER'):
                            logger_file_paths.append(file.path)
                        elif file.name.startswith('FIXHEIGHT'):
                            with open(file.path, 'r') as f:
                                fix_heights.append(float(f.readline()))

    return logger_file_paths, hallog_file_paths, fix_heights


def aggregate_dataset(logger_file_paths: list,
                      hallog_file_paths: list,
                      fix_heights: list) -> (
        np.ndarray, np.ndarray, np.ndarray, np.ndarray, list,
        preprocessing.StandardScaler, preprocessing.StandardScaler):
    X_datasets, y_datasets, columns = [], [], []
    if hallog_file_paths and logger_file_paths:
        for hallog, logger, fix_height in zip(hallog_file_paths,
                                              logger_file_paths,
                                              fix_heights):
            X_dataset, y_dataset, columns = get_dataset(logger, fix_height)
            X_datasets.append(X_dataset)
            y_datasets.append(y_dataset)

        resized_X_datasets = []
        resized_y_datasets = []
        min_size = int(np.median(np.array([X.shape[0] for X in X_datasets])))
        for X_dataset, y_dataset in zip(X_datasets, y_datasets):
            idx = np.random.randint(X_dataset.shape[0], size=min_size)
            resized_X_datasets.append(X_dataset[idx])
            resized_y_datasets.append(y_dataset[idx])

        X_dataset = np.concatenate(resized_X_datasets, axis=0)
        y_dataset = np.concatenate(resized_y_datasets, axis=0)

        print('X_dataset descriptive statistics:')
        print(pd.DataFrame(data=X_dataset, columns=columns).describe())
        print('y_dataset descriptive statistics:')
        print(pd.DataFrame(data=y_dataset, columns=['altitude']).describe())

        X_dataset, X_scaler = standardize(X_dataset)
        y_dataset, y_scaler = standardize(y_dataset[..., np.newaxis])
        y_dataset = y_dataset.squeeze()

        return X_dataset, y_dataset, X_scaler, y_scaler, columns
    else:
        raise FileNotFoundError('There are no logfiles in the data folder.')


def create_dataset(test_size: float = 0.1, shuffle=True):
    X_dataset, y_dataset, X_scaler, y_scaler, columns = aggregate_dataset(
        *get_paths())

    X_train, X_test, y_train, y_test = model_selection.train_test_split(
        X_dataset, y_dataset, test_size=test_size, shuffle=shuffle)

    return X_train, X_test, y_train, y_test, columns, X_scaler, y_scaler


def plot_data(X_dataset, y_dataset, columns, X_scaler, y_scaler):
    X_dataset_ = X_scaler.inverse_transform(X_dataset)
    y_dataset_ = y_scaler.inverse_transform(
        y_dataset[..., np.newaxis]).squeeze()
    columns_ = {key: X_dataset_[:, i] for i, key in enumerate(columns)}
    columns_['altitude'] = y_dataset_
    df = pd.DataFrame(data=columns_)
    sns.pairplot(df)
    plt.show()


def main():
    (X_train, X_test, y_train, y_test,
     columns, X_scaler, y_scaler) = create_dataset()
    joblib.dump(X_scaler, 'X_scaler.bin')
    joblib.dump(y_scaler, 'y_scaler.bin')
    print('Saved scalers')
    plot_data(X_train, y_train, columns, X_scaler, y_scaler)


if __name__ == '__main__':
    main()
