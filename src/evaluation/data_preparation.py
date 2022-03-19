import datetime
import os
import time

import numpy as np
import pandas as pd

from src.constants import ABS_PATH, DATA_COLUMNS

DATA_PATH = os.path.join(ABS_PATH, 'data')


def read_data(path: str) -> np.ndarray:
    if not os.path.exists(path):
        raise ValueError('Path %s does not exist' % path)

    out = pd.read_csv(path)

    if out.empty:
        raise ValueError('The csv is empty')

    arr = out.to_numpy()
    if not arr.shape[1] == len(DATA_COLUMNS):
        raise ValueError('The csv has the wrong number of columns')

    return arr


def convert_time_format(data: np.ndarray) -> np.ndarray:
    out = data
    for row in out:
        row[0] = time.mktime(datetime.datetime.strptime(
            row[0], '%Y/%m/%d %H:%M:%S').timetuple())
    return out


def get_data_from_files(folder: str) -> np.ndarray:
    if not os.path.exists(folder):
        raise ValueError('The folder "%s" does not exist.' % folder)

    with os.scandir(folder) as ls:
        for item in ls:
            if item.is_file():
                filename = str(item.name)


def main():
    data = read_data(os.path.join(DATA_PATH, 'LOGGER25.CSV'))
    print(data)
    reformatted_data = convert_time_format(data)
    print(reformatted_data)


if __name__ == '__main__':
    main()
