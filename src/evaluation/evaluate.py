import keras
import numpy as np
import pandas
import pandas as pd

import data_preparation
import joblib
import matplotlib.pyplot as plt
import seaborn as sns


def convert_altitude_to_pressure(altitude: np.ndarray) -> np.ndarray:
    A = 0.0000225577
    B = 5.2558
    C = 101325
    return np.power(-altitude * A + 1, B) * C / 100000


def evaluate_csv(model_path,
                 X_scaler_path, y_scaler_path, logger_path,
                 hallog_path):
    model = keras.models.load_model(model_path)
    X_scaler = joblib.load(X_scaler_path)
    y_scaler = joblib.load(y_scaler_path)

    data, _, columns = data_preparation.get_dataset(logger_path, hallog_path,
                                                    None)
    X_dataset = X_scaler.transform(data)
    out = model.predict(X_dataset)
    out = y_scaler.inverse_transform(out)

    # sns.pairplot(pd.read_csv(logger_path))
    # plt.show()

    return out


def main():
    model_path = '/home/daniel/coding/SenseBox/src/evaluation/models/model_2_epochs_2022-05-18 16-13-43.051212.h5'
    X_scaler_path = '/home/daniel/coding/SenseBox/src/evaluation/X_scaler.bin'
    y_scaler_path = '/home/daniel/coding/SenseBox/src/evaluation/y_scaler.bin'
    logger_path = '/home/daniel/coding/SenseBox/data/2022-05-13_Messreihe_Zug_S1_Hbf_Kirchzarten/LOGGER03.CSV'
    hallog_path = '/home/daniel/coding/SenseBox/data/2022-05-13_Messreihe_Zug_S1_Hbf_Kirchzarten/HALLOG03.CSV'
    out = evaluate_csv(model_path,
                       X_scaler_path,
                       y_scaler_path,
                       logger_path,
                       hallog_path)
    print(pd.DataFrame(out, columns=['altitude']).describe())
    plt.plot(out)
    plt.show()


if __name__ == '__main__':
    main()
