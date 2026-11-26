# Implementation

`solution.h` implements the required template. `main.cpp` runs the supplied
sample scenarios, and CMake builds it as `code`.

Nodes form a circular list in increasing bound order. Each jump table stores
the successors at distances 1, 2, 4, and so on. Tables are built one level at
a time so both halves of every doubled jump are already available.

Lookup uses a contiguous sorted index owned by the head node. Binary search
finds the first bound at least as large as the hash code in O(log n) time.
This avoids pointer chasing through jump tables. The tables are still built
to the prescribed layout. Missing reads do not insert entries.

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

# Judge history

- Submission 879468: 85/100. Tests 1-9 passed, including memory checks.
  The speed test returned Wrong Answer in 269 ms, so time was not the issue.
- Changed duplicate insertion to preserve the first value using `map::insert`.
  The statement specifies insertion without specifying replacement; this
  addresses a semantic ambiguity that the small tests did not distinguish.
- Submission 879470: 85/100 again, with the same failing test.
  Restored replacement on duplicate writes and changed reads to use
  `map::operator[]`, which stores the default value for missing keys.
- Submission 879472: 85/100, with the same failing test. Neither semantic
  experiment explained the failure. Restored non-inserting reads and replaced
  the lookup path with binary search over a contiguous index in the head node.
  No members were added to the outer list class.
- Submission 879476: Accepted, 100/100. All ten groups passed. Speed test:
  242 ms and 32231424 bytes. Accepted source commit: fe7020f.
  Four valid submissions were used; the rejected Git request created no ID.
