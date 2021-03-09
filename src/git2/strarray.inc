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
    strings : PPAnsiChar;
    count : size_t;
  end;
  Pgit_strarray = ^git_strarray;

  (**
 * Close a string array object
 *
 * This method should be called on `git_strarray` objects where the strings
 * array is allocated and contains allocated strings, such as what you
 * would get from `git_strarray_copy()`.  Not doing so, will result in a
 * memory leak.
 *
 * This does not free the `git_strarray` itself, since the library will
 * never allocate that object directly itself (it is more commonly embedded
 * inside another struct or created on the stack).
 *
 * @param array git_strarray from which to free string data
  *)

procedure git_strarray_free(array_: Pgit_strarray); cdecl; external libgit2_dll;

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

