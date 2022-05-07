import os

ABS_PATH = os.path.normpath(
    os.path.dirname(os.path.dirname(os.path.dirname(__file__))))


def get_path(*args) -> str:
    return os.path.join(ABS_PATH, *args)
