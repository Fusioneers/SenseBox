import csv
import matplotlib.pyplot as plt

# read in csv-file with wind speed data
# contains time of every rotation of anemometer in milliseconds from start
def read_wind_speed(file_name):
    """
    Reads in csv-file with wind speed data.
    Contains time of every rotation of anemometer in milliseconds from start.
    :param file_name: name of csv-file
    :return: list with wind speed data
    """
    wind_speed_data_file = []
    wind_speed_data = []
    with open(file_name, 'r') as csv_file:
        csv_reader = csv.reader(csv_file)
        for row in csv_reader:
            wind_speed_data_file.append(row[0])
        for row in wind_speed_data_file[1:]:
            wind_speed_data.append(int(row))
    return wind_speed_data


print(read_wind_speed('../../data/2022-05-17-0002-FT/HALLOG03.CSV'))


# calulate wind speed in m/s from time in milliseconds
def calculate_wind_speed(wind_speed_data):
    speeds = []
    for i in range(1, len(wind_speed_data)):
        speed = 1 / (wind_speed_data[i] - wind_speed_data[i - 1]) * 1000
        speeds.append(((int(wind_speed_data[i] + wind_speed_data[i - 1]) / 2), speed))
    return speeds



speeds = calculate_wind_speed(read_wind_speed('../../data/2022-05-17-0002-FT/HALLOG03.CSV'))

print(speeds)

# plot wind speeds
plt.plot([x[0] for x in speeds], [x[1] for x in speeds])
plt.show()