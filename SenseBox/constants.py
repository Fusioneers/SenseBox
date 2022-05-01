import os

ABS_PATH = os.path.dirname(os.path.normpath(os.path.dirname(__file__)))

GROUND_TRUTH_COLUMN = 5 # 'altitude'
DATA_COLUMNS = ['time', 'temperature', 'pressure', 'humidity', 'altitude', 'uv']
