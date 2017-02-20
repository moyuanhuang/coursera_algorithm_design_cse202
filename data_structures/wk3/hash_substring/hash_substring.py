# python3


class TextSearch:
    def __init__(self, pattern, text):
        self._pattern = pattern
        self._text = text
        self._window = len(pattern)
        self._check = []
        self._scan_bound = len(text) - len(pattern) + 1

    def check(self, string):
        return sum([ord(string[i]) for i in range(len(string))])

    def precompute_hashes(self):
        self._check = [self.check(self._text[:self._window])]

        for i in range(1, self._scan_bound):
            old_hash = self._check[i - 1]
            left = ord(self._text[i - 1])
            right = ord(self._text[i + self._window - 1])

            new_hash = old_hash - left + right
            self._check.append(new_hash)

    def find(self):
        """Returns all occurrences of pattern in the text."""
        pattern_checksum = self.check(self._pattern)
        self.precompute_hashes()

        results = []
        for i in range(self._scan_bound):
            if pattern_checksum == self._check[i]:
                if self._pattern == self._text[i:i + self._window]:
                    results.append(i)
        return results


if __name__ == "__main__":
    pattern, text = input().rstrip(), input().rstrip()

    ts = TextSearch(pattern, text)
    result = ts.find()

    print(" ".join(map(str, result)))