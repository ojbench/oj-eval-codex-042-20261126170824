# Implementation

`solution.h` implements the required template. `main.cpp` runs the supplied
sample scenarios, and CMake builds it as `code`.

Nodes form a circular list in increasing bound order. Each jump table stores
the successors at distances 1, 2, 4, and so on. Tables are built one level at
a time so both halves of every doubled jump are already available.

Lookup returns the head for codes at or below its bound. Otherwise it walks
jump levels from largest to smallest, accepting only strictly increasing
bounds below the target code. The resulting node is the target's predecessor.
The highest level may be used up to three times because the prescribed table
length is floor(log2(n)); every subsequent level needs at most one jump.
Thus lookup takes O(log n) time. Inclusive upper bounds and circular wraparound
are handled explicitly. Missing reads do not insert map entries.

Construction takes O(n log n) time and space. Each operation additionally
hashes the key and accesses the destination node's ordered map. Destruction
deletes every node and jump array exactly once.

# Validation

- Supplied sample output matches, allowing for CRLF line endings.
- `tests/test.cpp` checks every jump pointer and boundary lookup for sizes
  including 1, powers of two, nearby sizes, 1000, and 50000.
- Randomized reads and writes are compared with a standard map, including
  200000 operations on the largest ring.
- AddressSanitizer and UndefinedBehaviorSanitizer pass these tests.
- Local testing caught and fixed the need to repeat the highest jump level.

Run the independent tests with:

```sh
g++ -std=c++17 -O1 -g -fsanitize=address,undefined tests/test.cpp -o /tmp/ring-test
/tmp/ring-test
```

The submission client's missing source submission method was implemented.
The live problem API accepts only `cpp`, so submission uses `solution.h`
directly. The initial Git request was rejected with HTTP 400 and created no
submission. The repository remains the versioned source of the solution.
