(**
 * @file git2/strarray.h
 * @brief An array of strings for the user to free
 * @defgroup git_strarray An array of strings for the user to free
 * @ingroup Git
 * @{
 *)

(** Array of strings  *)

type
  git_strarray = record
    strings: PPAnsiChar;
    Count: size_t;
  end;
  Pgit_strarray = ^git_strarray;

  (**
 * Free the strings contained in a string array.  This method should
 * be called on `git_strarray` objects that were provided by the
 * library.  Not doing so, will result in a memory leak.
 *
 * This does not free the `git_strarray` itself, since the library will
 * never allocate that object directly itself.
 *
 * @param array The git_strarray that contains strings to free
 *)

procedure git_strarray_dispose(array_: Pgit_strarray); cdecl; external libgit2_dll {$IFDEF LIBGIT2_DLL_DELAY_LOAD}delayed{$ENDIF};

(** @}  *)

