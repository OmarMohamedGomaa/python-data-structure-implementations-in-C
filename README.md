# C Libraries Project

Some of C data structure implementations including:
- Dictionaries
- Lists
- Tuples

## Files

implementation
- `dictionaries.c/h` - Dictionary implementation
- `list.c/h` - List implementation
- `tuples.c/h` - Tuple implementation
- `typesenum.h` - Type definitions and enumerations


## Building

Use the provided build task or compile with GCC:

```bash
gcc -g main.c dictionaries.c list.c tuples.c -o main.exe
```

## Usage

[
   - when retrieving data it returns a void pointer so you need to cast it to its suitable type first before using.

   - There is a func that returns an enum type of the node or entry 
   
   - before inserting or r wether in initialization or in inserting specify wether the inserted data is string,floating,integer or pointer by giving their enum before the data  
   
   - the implementation is not perfect and might have flaws and can be improved
]
