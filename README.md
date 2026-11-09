*This project has been created as part of the 42 curriculum by mutalay.*

# get_next_line

## Description

`get_next_line` is a C function that reads a file descriptor **one line at a time**.
Each call returns the next line, including the terminating `\n` (except for the last
line of a file that does not end with `\n`). When there is nothing left to read, or an
error occurs, it returns `NULL`.

```c
char	*get_next_line(int fd);
```

The main goal of the project is to learn how **static variables** work in C: the
function has to remember data between calls without using global variables.

It works with regular files, the standard input, pipes, and any other readable file
descriptor.

The **bonus** version can read from several file descriptors at the same time
(for example fd 3, then fd 4, then fd 3 again) without mixing their data, using only
one static variable.

## Instructions

### Files

| Part      | Files |
|-----------|-------|
| Mandatory | `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h` |
| Bonus     | `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h` |

### Compilation

The project has no `main`. Write your own test program and compile it together with
the source files:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
```

- `-D BUFFER_SIZE=n` sets how many bytes `read()` reads at a time.
  If it is not given, the default value is `42`.
- For the bonus, use the `_bonus` files instead. The maximum number of file descriptors
  can be changed with `-D FD_SIZE=n` (default: `1024`).

### Usage example

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

Every returned line is allocated with `malloc`, so the caller must `free` it.

## Algorithm

### Idea

`read()` does not know about lines: it returns blocks of `BUFFER_SIZE` bytes. A block
can contain part of a line, exactly one line, or several lines. So the function needs a
place to keep the bytes that were read but not returned yet. This place is a
**static pointer** called `stored`, which keeps its value between calls.

### Steps

Each call to `get_next_line(fd)` does the following:

1. **Check the input.** If `fd < 0` or `BUFFER_SIZE <= 0`, return `NULL`.

2. **Prepare `stored`** (`fill_stored`). If `stored` is `NULL` (first call, or the
   previous data was used up), it becomes an empty string `""`, so that it can be
   searched and joined safely. A buffer of `BUFFER_SIZE + 1` bytes is allocated
   with `malloc`.

3. **Read until a newline** (`read_until_newline`). While `stored` does not contain
   `\n` and `read()` returns more than `0`:
   - read up to `BUFFER_SIZE` bytes into the buffer,
   - add `'\0'` after the bytes that were read,
   - join the buffer to the end of `stored` (the old `stored` is freed).

   The loop stops when a `\n` is found or when `read()` returns `0` (end of file).
   If `read()` returns `-1`, `stored` is freed and set to `NULL`, and the function
   returns `NULL`.

4. **Split `stored`** (`split_stored`):
   - If `stored` contains `\n`: the part up to and including `\n` is copied into a new
     string and returned. The part after `\n` becomes the new `stored`.
   - If there is no `\n` but `stored` is not empty: this is the last line of the file.
     It is returned as it is, and `stored` becomes `NULL`.
   - If `stored` is empty: there is nothing left. `stored` is freed and set to `NULL`,
     and the function returns `NULL`.

### Why this approach

- **It reads as little as possible.** Reading stops as soon as one full line is
  available. The whole file is never read in advance.
- **It works with any `BUFFER_SIZE`.** The buffer is allocated on the **heap** with
  `malloc`, not declared as a local array on the stack. A local array of 10,000,000
  bytes would be bigger than the stack limit (usually 8 MB) and would crash the
  program. On the heap this is not a problem.
  - With `BUFFER_SIZE=1`, the function calls `read()` once per character: it is slow,
    but correct.
  - With a very large `BUFFER_SIZE`, one `read()` can return many lines: the extra
    lines stay in `stored` for the next calls.
- **It works with any line length.** `stored` grows with `ft_strjoin`, so there is no
  fixed maximum line length.
- **No memory leaks** when the file is read until the end: every `malloc` has a
  matching `free`, and every freed pointer is set to `NULL` so it cannot be used or
  freed again.

### Bonus: multiple file descriptors

The operating system keeps a separate read position for every file descriptor, but
the mandatory version has only **one** `stored`. If two files are read one after the
other, the leftover data of one file would be returned as a line of the other.

The bonus solves this by making the static variable an **array of pointers**:

```c
static char	*stored[FD_SIZE];
```

Each file descriptor uses its own element: `stored[fd]`. The helper functions do not
change, they just receive the element that belongs to the current `fd`. A file
descriptor greater than or equal to `FD_SIZE` returns `NULL`, so the array is never
accessed out of bounds. `FD_SIZE` is `1024` by default, which is the default limit of
open files per process on Linux (`ulimit -n`).

### Limits

- If the caller stops calling `get_next_line` before the end of the file, the data in
  `stored` is not freed.
- As stated in the subject, the behavior is undefined when reading a binary file, or
  when the file is modified between two calls.

## Resources

- `man 2 read`: return values of `read()` (`0` at end of file, `-1` on error)
- `man 3 malloc`, `man 3 free`: dynamic memory, and the fact that `free(NULL)` does nothing
- [Valgrind Quick Start Guide](https://valgrind.org/docs/manual/quick-start.html): checking for memory leaks and invalid memory access
- [cppreference: Storage-class specifiers](https://en.cppreference.com/w/c/language/storage_duration): `static` and storage duration in C

### AI usage

AI (Claude) was used as a learning and review tool, not to write the project code:

- **Explanations:** static variables, stack vs heap memory, pointers to pointers
  (`char **`), the return values of `read()`, and why a freed pointer should be set
  to `NULL`.
- **Review and testing:** finding problems in the code (for example, the first bonus
  version still used a single `stored`), testing with different `BUFFER_SIZE` values
  and different file descriptors (files, standard input, pipes, invalid fds), and
  reading Valgrind output.
- **This README:** drafted with AI, then reviewed and edited by me.