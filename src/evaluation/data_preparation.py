import datetime
import os
import time
from typing import Optional

import numpy as np
import pandas as pd

from src.constants import ABS_PATH, DATA_COLUMNS

DATA_PATH = os.path.join(ABS_PATH, 'data')


def read_data(path: str) -> Optional[np.ndarray]:
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
    out = data
    for row in out:
        row[0] = time.mktime(datetime.datetime.strptime(
            row[0], '%Y/%m/%d %H:%M:%S').timetuple())
    return out


def get_data_from_files(folder: str) -> np.ndarray:
    if not os.path.exists(folder):
        raise ValueError('The folder "%s" does not exist.' % folder)

    # accumulate all the data in a folder
    data = []
    for file in os.listdir(folder):
        if file.endswith('.csv') or file.endswith('.CSV'):
            path = os.path.join(folder, file)
            data.append(read_data(path))

    # converts the time format
    # data = [convert_time_format(d) for d in data if d is not None]

    out = []
    for set in data:
        for row in set:
            out.append(row)

    return np.array(out)


def main():
    data = get_data_from_files(DATA_PATH)
    print(data)
    print(data.shape)


if __name__ == '__main__':
    main()
