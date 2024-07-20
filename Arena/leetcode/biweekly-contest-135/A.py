class Solution:
    def losingPlayer(self, x: int, y: int) -> str:
        r = 0
        while x >= 1 and y >= 4:
            x -= 1
            y -= 4
            r += 1
        if r & 1:
            return 'Alice'
        return 'Bob'