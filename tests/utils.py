from enum import Enum, auto

LIBREDWG_DATADIR = "../src/external/libredwg/test/test-data/"


class MessageType(Enum):
    DEBUG = auto()
    INFO = auto()
    WARNING = auto()
    ERROR = auto()


class LoggerForTest:
    def __init__(self):
        self.__messages = []

    def debug(self, message: str):
        self.__messages.append((MessageType.DEBUG, message))

    def info(self, message: str):
        self.__messages.append((MessageType.INFO, message))

    def warning(self, message: str):
        self.__messages.append((MessageType.WARNING, message))

    def error(self, message: str):
        self.__messages.append((MessageType.ERROR, message))

    def get_messages(self) -> list[tuple[MessageType, str]]:
        return self.__messages


class ExceptionalLogger(LoggerForTest):
    def debug(self, message: str):
        super().debug(message)
        raise RuntimeError()


def check_message(
    message: tuple[MessageType, str], expected_type: MessageType, expected_text: str
):
    assert message[0] == expected_type
    assert message[1] == expected_text
