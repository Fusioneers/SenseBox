import io
import os

import keras
import numpy as np
import pandas
import pandas as pd
from tensorflow import metrics

import data_preparation
import joblib
import matplotlib.pyplot as plt
import seaborn as sns
from tensorflow_addons import activations

from src.evaluation import constants
from src.evaluation.constants import get_path


def convert_altitude_to_pressure(altitude: np.ndarray) -> np.ndarray:
    A = 0.0000225577
    B = 5.2558
    C = 101325
    return np.power(-altitude * A + 1, B) * C / 100000


def evaluate_csv(model_path,
                 X_scaler_path, y_scaler_path, logger_path):
    model = keras.models.load_model(model_path, custom_objects={
        'activations': activations})
    X_scaler = joblib.load(X_scaler_path)
    y_scaler = joblib.load(y_scaler_path)

    data, _, columns = data_preparation.get_dataset(logger_path, None)
    X_dataset = X_scaler.transform(data)
    out = model.predict(X_dataset)
    out = y_scaler.inverse_transform(out)

    return out


def plot(path, X_test, y_test, n):
    model_path = path
    X_scaler_path = get_path('src', 'evaluation', 'X_scaler.bin')
    y_scaler_path = get_path('src', 'evaluation', 'y_scaler.bin')
    logger_path = get_path(
        'data', '2022-05-03-0004-VG-exact-pressure.CSV')
    model = keras.models.load_model(model_path)
    y_scaler = joblib.load(y_scaler_path)

    out = evaluate_csv(model_path,
                       X_scaler_path,
                       y_scaler_path,
                       logger_path)
    # print(pd.DataFrame(out, columns=['altitude']).describe())
    data = pd.read_csv(logger_path)
    plt.plot(data['timestamp'], out)
    plt.savefig(
        get_path('docs', 'Laborbuch-AI-assets', 'images',
                 str(n) + '.png'))
    plt.clf()
    y_pred = model.predict(X_test)
    error = metrics.mean_absolute_error(
        y_scaler.inverse_transform(y_test[..., np.newaxis]).squeeze(),
        y_scaler.inverse_transform(y_pred).squeeze())

    s = io.StringIO()
    model.summary(print_fn=lambda x: s.write(x + '\n'))
    model_summary = s.getvalue()
    s.close()
    model.save(get_path('docs', 'models', f'model-{n}.h5'))
    return error, model_summary


def main():
    (X_train, X_test, y_train, y_test,
     columns, X_scaler, y_scaler) = data_preparation.create_dataset()
    with open(
            get_path('docs', 'Laborbuch-AI-assets', 'Laborbuch-AI.md'),
            'a') as f:
        for n, path in enumerate(
                os.scandir(
                    constants.get_path('src', 'evaluation', 'models-old'))):
            if path.is_file() and 'h5' in path.name:
                try:
                    error, summary = plot(path.path, X_test, y_test, n)

                    out = f"""\
## Model {n}

### Model Architektur

```
{summary}
```

### Durchschnittlicher absoluter Fehler auf Testdaten (in Meter)

{error.numpy()}m

### Daten 2022-05-03-0004-VG mit Model ausgewertet
![{str(n)}.png](images/{str(n)}.png)

"""
                    f.write(out)
                except Exception as e:
                    print(e)
                    print(path.name)


if __name__ == '__main__':
    main()
