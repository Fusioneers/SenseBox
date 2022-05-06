import os

import gpxpy
import gpxpy.gpx
from constants import ABS_PATH


def get_elevation(path: str):
    gpx_file = open(path, 'r')

    data = []
    gpx = gpxpy.parse(gpx_file)
    for track in gpx.tracks:
        for segment in track.segments:
            for point in segment.points:
                data.append([point.time, point.elevation])
    return data
