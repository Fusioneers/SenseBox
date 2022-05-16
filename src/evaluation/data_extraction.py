import datetime
import os
from typing import Tuple, Optional

import gpxpy
import gpxpy.gpx
import numpy as np
import pandas as pd

from constants import ABS_PATH


def get_altitude(path: str) -> pd.DataFrame:
    gpx_file = open(path, 'r')

    data = []
    gpx = gpxpy.parse(gpx_file)
    for track in gpx.tracks:
        for segment in track.segments:
            for point in segment.points:
                data.append([point.time.timestamp(), point.elevation])

    return pd.DataFrame(data=data, columns=['time', 'altitude'])


def read_data(path: str) -> Optional[Tuple[np.ndarray, list]]:
    """
    Read the data from a file.
    Args:
        path: The path to the file.

    Returns:
        The data and the columns.
    """
    if not os.path.exists(path):
        raise ValueError('Path %s does not exist' % path)

    try:
        out = pd.read_csv(path, on_bad_lines='skip')
    except pd.errors.EmptyDataError as e:
        print(str(e) + ' ' + path)
        return None

    if out.empty:
        raise ValueError('The csv is empty')

    out = out.drop(columns=['altitude', 'timestamp'])
    # out = out.drop(columns=['timestamp'])

    return out.to_numpy(), out.columns.tolist()


# def get_wind_speed(path: str) -> np.ndarray:
#     csv = pd.read_csv(path, on_bad_lines='skip')
#     data = csv.dropna().drop_duplicates().to_numpy().squeeze()
#     diff = np.diff(data)
#     speed = 1000 / diff
#     return np.array([data[1:-1], speed[1:]]).T


def main():
    # print(get_altitude(
    #     os.path.join(ABS_PATH, 'data', 'Fahrradtour_Vg_03-05-2022',
    #                  'Test_Sensorbox.gpx')))
    # print(get_wind_speed(
    #     os.path.join(ABS_PATH, 'data', 'Fahrradtour_Vg_03-05-2022',
    #                  'datalogger-hall-sensor', '(deprecated)HALLOG01.CSV')))


if __name__ == '__main__':
    main()
