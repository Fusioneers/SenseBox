import gpxpy
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
from scipy import optimize

file = open(
    '/home/daniel/coding/SenseBox/data/2022-05-03-Fahrradtour_Vg'
    '/Test_Sensorbox.gpx')
gpx = gpxpy.parse(file)
heights = []
for track in gpx.tracks:
    for segment in track.segments:
        for point in segment.points:
            heights.append([point.time.timestamp(), point.elevation])
heights = np.array(heights)
heights_range = np.linspace(heights[0, 0], heights[-1, 0],
                           int(heights[-1, 0] - heights[0, 0]))
heights = np.interp(heights_range, heights[:, 0], heights[:, 1])

logger_path = '/home/daniel/coding/SenseBox/data/2022-05-03-Fahrradtour_Vg/' \
              'datalogger/LOGGER04.CSV'
logger = pd.read_csv(logger_path)
logger = np.array(logger)[:, (0, -2)]
logger[:, 0] *= 0.001
logger_range = np.linspace(0, logger[0, -1], int(logger[0, -1]))
logger = np.interp(logger_range, logger[:, 0], logger[:, 1])
heights_len = heights.shape[0]
logger_len = logger.shape[0]


def height(time):
    return np.interp(time, heights_range, heights)


def logger_height(time):
    return np.interp(time, logger_range, logger)


def fit(params):
    def f(x):
        return np.abs(
            height((params[0] + x).astype('int')) + params[1] - logger_height(
                x))

    sample_len = int(heights_len - logger_len - params[0])
    out = np.average(f(np.linspace(0, sample_len, sample_len)))
    print(f'out: {out}, params: {params}')
    return out


initial_guess = np.array([1, 1])
result = optimize.minimize(fit,
                           initial_guess,
                           bounds=((0, heights_len - logger_len),
                                   (None, None)),
                           method='COBYLA')
print(result)