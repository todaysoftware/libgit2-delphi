(**
 * A data buffer for exporting data from libgit2
 *
 * Sometimes libgit2 wants to return an allocated data buffer to the
 * caller and have the caller take responsibility for freeing that memory.
 * To make ownership clear in these cases, libgit2 uses  `git_buf` to
 * return this data.  Callers should use `git_buf_dispose()` to release
 * the memory when they are done.
 *
 * A `git_buf` contains a pointer to a NUL-terminated C string, and
 * the length of the string (not including the NUL terminator).
  *)

type
  git_buf = record
    (**
  * The buffer contents.  `ptr` points to the start of the buffer
  * being returned.  The buffer's length (in bytes) is specified
  * by the `size` member of the structure, and contains a NUL
  * terminator at position `(size + 1)`.
   *)
    ptr: PAnsiChar;
    (**
  * This field is reserved and unused.
   *)
    reserved: size_t;
    (**
  * The length (in bytes) of the buffer pointed to by `ptr`,
  * not including a NUL terminator.
   *)
    size: size_t;
  end;

  (**
 * Use to initialize a `git_buf` before passing it to a function that
 * will populate it.
    *)

  //#define GIT_BUF_INIT { NULL, 0, 0 }

  (**
   * Free the memory referred to by the git_buf.
   *
   * Note that this does not free the `git_buf` itself, just the memory
   * pointed to by `buffer->ptr`.
   *
   * @param buffer The buffer to deallocate
    *)

type
  Pgit_buf = ^git_buf;

procedure git_buf_dispose(buffer: Pgit_buf); cdecl; external libgit2_dll;


