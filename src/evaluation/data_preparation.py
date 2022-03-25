import datetime
import os
import time
from typing import Optional

import numpy as np
import pandas as pd
import seaborn as sns
from matplotlib import pyplot as plt
from sklearn import preprocessing
from sklearn import model_selection

from src.constants import ABS_PATH, DATA_COLUMNS


def read_data(path: str) -> Optional[np.ndarray]:
    """
    Read the data from a file.
    :param path: The path to the file.
    :return: The data in the file. If the file is empty, return None.
    """

    if not os.path.exists(path):
        raise ValueError('Path %s does not exist' % path)

    try:
        out = pd.read_csv(path)
    except pd.errors.EmptyDataError as e:
        print(str(e) + ' ' + path)
        return None

    if out.empty:
        raise ValueError('The csv is empty')

    arr = out.to_numpy()
    if not arr.shape[1] == len(DATA_COLUMNS):
        raise ValueError('The csv has the wrong number of columns')

    return arr


def convert_time_format(data: np.ndarray) -> np.ndarray:
    """
    Convert the time format of the data to unix time.
    :param data: The data to convert.
    :return: The data with the time format converted.
    """

    out = data
    for row in out:
        # row[0] = time.mktime(datetime.datetime.strptime(
        #     row[0], '%Y/%m/%d %H:%M:%S').timetuple())
        row[0] = np.random.randint(0, 100)
    return out


def get_data_from_files(folder: str) -> np.ndarray:
    """
    Get the data from all the files in the folder.
    :param folder: The folder to get the data from.
    :return: Numpy array of all the data.
    """

    if not os.path.exists(folder):
        raise ValueError('The folder "%s" does not exist.' % folder)

    # accumulate all the data in a folder
    data = []
    for file in os.listdir(folder):
        if file.endswith('.csv') or file.endswith('.CSV'):
            path = os.path.join(folder, file)
            data.append(read_data(path))

    # converts the time format
    data = [convert_time_format(d) for d in data if d is not None]

    out = []
    for d in data:
        for row in d:
            out.append(row)

    return np.array(out)


def get_standard_scaler(data) -> preprocessing.StandardScaler:
    """
    Get a StandardScaler object.
    :param data: The data to get the scaler from.
    :return: The StandardScaler object.
    """

    scaler = preprocessing.StandardScaler().fit(data)
    return scaler


def separate_ground_truths(data) -> (np.ndarray, np.ndarray):
    """
    Separate the ground truths from the data.
    :param data: The data to separate.
    :return: The ground truths and the data.
    """

    ground_truths = data[:, -1]
    data = data[:, :-1]

    return ground_truths, data


def get_dataset(data_path: str,
                test_size: float = 0.1) -> (
        np.ndarray, np.ndarray, np.ndarray, np.ndarray):
    """
    Get the dataset.
    :param data_path: The path to the folder containing the data.
    :param test_size: The size of the test set.
    :return: The training and the test set.
    """

    data = get_data_from_files(data_path)

    scaler = get_standard_scaler(data)
    scaled = scaler.transform(data)

    y_dataset, X_dataset = separate_ground_truths(scaled)
    X_train, X_test, y_train, y_test = model_selection.train_test_split(
        X_dataset, y_dataset, test_size=test_size)

    return X_train, X_test, y_train, y_test


def plot_data(data: np.ndarray, ground_truth: np.ndarray):
    """
    Plot the data.
    :param ground_truth: The ground truth to plot.
    :param data: The data to plot.
    """

    columns = {key: data[:, i] for i, key in enumerate(DATA_COLUMNS[:-1])}
    columns[DATA_COLUMNS[-1]] = ground_truth
    df = pd.DataFrame(data=columns)
    sns.pairplot(df)
    plt.show()


def main():
    X_train, X_test, y_train, y_test = get_dataset(
        os.path.join(ABS_PATH, 'data'))
    print(X_train.shape)
    print(X_test.shape)
    print(y_train.shape)
    print(y_test.shape)
    plot_data(X_train, y_train)


if __name__ == '__main__':
    main()
