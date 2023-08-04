import raylibpy as rl

from . import WIN_WIDTH, WIN_HEIGHT
from .number import Numbers

class Sort:
    def __init__(self) -> None:
        self.nums = Numbers.gen_random(120, 375)

    def _refresh(self) -> None:
        pass

    def _render(self) -> None:
        rl.draw_text("very scuffed", 20, 20, 20, rl.BLUE)
        self.nums.render()

    def run(self) -> None:
        self._setup() 
        while not rl.window_should_close():
            with rl.drawing():
                rl.clear_background(rl.BLACK)
                self._render()
        self._unload()

    def _setup(self) -> None:
        rl.init_window(WIN_WIDTH, WIN_HEIGHT, "Sort Visualizer")
        rl.set_target_fps(60)

    def _unload(self) -> None:
        rl.close_window()
