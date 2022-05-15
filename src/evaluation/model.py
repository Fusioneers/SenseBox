import keras
from keras import layers


def create_model(input_shape, output_shape):
    """
    Creates a model with the given input and output shape.

    Args:
        input_shape: The shape of the input data.
        output_shape: The shape of the output data.

    """
    model = keras.Sequential()
    model.add(layers.Dense(units=10, activation='relu',
                           input_shape=input_shape))
    model.add(layers.Dense(units=10, activation='relu'))
    model.add(layers.Dense(units=10, activation='relu'))
    model.add(layers.Dense(units=10, activation='relu'))
    model.add(layers.Dense(units=output_shape, activation='linear'))

    model.compile(loss='mean_squared_error', optimizer='adam')
    return model
