```markdown
# C Libraries Project

A compact C implementation of three data structures:
- dictionaries implemented as a hash table with separate chaining
- linked lists with dynamic insertion and removal
- tuples that store heterogeneous values

## Design

- The dictionary uses a hash table with separate chaining to resolve collisions.
- Values are stored as `void *` and tagged with the `enum types` values defined in `typesenum.h`.
- The insertion API is variadic, so callers pass the type tag first and then the corresponding value.
- The implementation is intended to be straightforward and educational while still demonstrating common systems-programming patterns such as dynamic memory management and linked-list traversal.

## Files

- `dictionaries.c` / `dictionaries.h` - dictionary implementation and API
- `list.c` / `list.h` - linked-list implementation and API
- `tuples.c` / `tuples.h` - heterogeneous tuple implementation and API
- `typesenum.h` - shared type definitions
- `main.c` - small demo program showing dictionary, list, and tuple usage

## Building

Compile the demo with GCC:

```bash
gcc -g main.c dictionaries.c list.c tuples.c -o main.exe
```

Run it with:

```bash
./main.exe
```

## Example Output

```text
=== Dictionary demo ===
Lookup name: Ada
Lookup age: 37
Type of 'score': 1
After removal, age found? no
Dictionary entry count: 2

=== List demo ===
[7,world,2.250000]

=== Tuple demo ===
(north,11,4.500000)
```

## Usage Notes

- `dict_get` returns a `void *`, so cast it to the appropriate type before use.
- `typeOffEntry` returns the stored type tag for a given key.
- When inserting into the dictionary or list, provide the tag first (`string`, `floating`, `integer`, or `pointer`) and then the value.


```