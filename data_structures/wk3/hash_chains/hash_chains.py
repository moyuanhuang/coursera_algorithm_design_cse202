# python3


class QueryProcessor:
    _multiplier = 263
    _prime = 1000000007

    def __init__(self, bucket_count):
        self.bucket_count = bucket_count
        self.buckets = [[] for _ in range(bucket_count)]

    def _hash_func(self, s):
        ans = 0
        for c in reversed(s):
            ans = (ans * self._multiplier + ord(c)) % self._prime
        # print s, "mapped to", ans % self.bucket_count
        return ans % self.bucket_count

    def check(self, i):
        return self.buckets[i]

    def add(self, string):
        ind = self._hash_func(string)
        bucket = self.buckets[ind]
        if string not in bucket:
            self.buckets[ind] = [string] + bucket

    def delete(self, string):
        ind = self._hash_func(string)
        bucket = self.buckets[ind]
        for i in range(len(bucket)):
            if bucket[i] == string:
                bucket.pop(i)
                break

    def find(self, string):
        ind = self._hash_func(string)
        if string in self.buckets[ind]:
            return "yes"
        return "no"


def process_queries(queries):
    for query in queries:
        command, arg = query.split()
        if command == "add":
            qp.add(arg)
        elif command == "del":
            qp.delete(arg)
        elif command == "find":
            print(qp.find(arg))
        elif command == "check":
            arg = int(arg)
            # ans = qp.check(arg)
            # print ans
            print(" ".join(str(b) for b in qp.check(arg)))


if __name__ == "__main__":
    bucket_count = int(input())
    n = int(input())

    qp = QueryProcessor(bucket_count)
    queries = [input() for i in range(n)]
    process_queries(queries)
