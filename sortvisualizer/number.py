import typing
import random
import raylibpy as rl

from . import WIN_HEIGHT, WIN_WIDTH, GameItem

HEIGHT_MAGNIFICATION_FACTOR = 2
MAX_NUMBER_VAL = 200
NUMS_LEN = 100
PADDING = 2


class Number(GameItem):
    def __init__(self, value: int, idx: int) -> None:
        self.width = WIN_WIDTH / NUMS_LEN - PADDING * 2
        self.height = value * HEIGHT_MAGNIFICATION_FACTOR
        self.x = (idx * self.width) + (PADDING * idx)
        self.y = WIN_HEIGHT - self.height

        print(f"{self.x=} {self.y=} {self.width=} {self.height=}")

        self.rect = rl.Rectangle(self.x, self.y, self.width, self.height)
        self.value = value

    def render(self, target: bool) -> None:
        col = rl.RED if target else rl.WHITE
        rl.draw_rectangle_rec(self.rect, col)

    def refresh(self) -> None:
        pass

    def __lt__(self, other: "Number"):
        return self.value < other.value

    def __le__(self, other: "Number"):
        return self.value <= other.value

    def __gt__(self, other: "Number"):
        return self.value >= other.value

    def __ge__(self, other: "Number"):
        return self.value >= other.value

    def __eq__(self, other: "Number"):
        return self.value == other.value

    def __ne__(self, other: "Number"):
        return self.value != other.value


class Numbers:
    def __init__(self, nums: list[Number]) -> None:
        self.outer_loop_idx = 0
        self.inner_loop_idx = 1
        self.in_inner_loop = True

        self.curr_targets: tuple[int, int] = (0, 1)
        self.elems: list[Number] = nums

    def render(self) -> None:
        for idx, elem in enumerate(self.elems):
            is_target = False if idx not in self.curr_targets else True
            elem.render(is_target)

    def refresh(self) -> None:
        pass

    @staticmethod
    def gen_random(count: int, max: int) -> "Numbers":
        get_val = lambda *_: random.randint(0, max)
        return Numbers([Number(get_val(), idx) for idx in range(count)])

    def __len__(self) -> int:
        return len(self.elems)

    def __iter__(self) -> typing.Self:
        return self

    def __next__(self) -> Number:
        if self.curr_iter_idx < len(self):
            next_index = self.curr_iter_idx + 1
            val = self.elems[self.curr_iter_idx]
            self.curr_iter_idx = next_index
            return val
        else:
            raise StopIteration

    def __getitem__(self, idx: int) -> Number:
        return self.elems[idx]
