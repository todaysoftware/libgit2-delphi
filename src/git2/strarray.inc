(**
 * @file git2/strarray.h
 * @brief Git string array routines
 * @defgroup git_strarray Git string array routines
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

procedure git_strarray_dispose(array_: Pgit_strarray); cdecl; external libgit2_dll;

(**
 * Copy a string array object from source to target.
 *
 * Note: target is overwritten and hence should be empty, otherwise its
 * contents are leaked.  Call git_strarray_free() if necessary.
 *
 * @param tgt target
 * @param src source
 * @return 0 on success, < 0 on allocation failure
 *)

function git_strarray_copy(tgt, src: Pgit_strarray): Integer; cdecl; external libgit2_dll;

(** @}  *)


