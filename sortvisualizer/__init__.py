from abc import ABC

WIN_WIDTH = 1200
WIN_HEIGHT = 800


class GameItem(ABC):
    def render(self) -> None:
        ...

    def refresh(self) -> None:
        ...
