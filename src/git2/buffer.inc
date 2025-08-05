(**
 * @file git2/buffer.h
 * @brief A data structure to return data to callers
 * @ingroup Git
 *
 * The `git_buf` buffer is used to return arbitrary data - typically
 * strings - to callers. Callers are responsible for freeing the memory
 * in a buffer with the `git_buf_dispose` function.
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
  Pgit_buf = ^git_buf;

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

procedure git_buf_dispose(buffer: Pgit_buf); cdecl; external libgit2_dll {$IFDEF LIBGIT2_DLL_DELAY_LOAD}delayed{$ENDIF};


