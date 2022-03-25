import keras
from keras import layers


def create_model(input_shape, output_shape):
    """
    Creates a model with the given input and output shape.
    """
    model = keras.Sequential()
    model.add(layers.Dense(units=100, activation='relu',
                           input_shape=input_shape))
    model.add(layers.Dense(units=50, activation='relu'))
    model.add(layers.Dense(units=output_shape, activation='linear'))

    print(model.summary())
    model.compile(loss='mean_squared_error', optimizer='adam')
    return model
