(**
 * @file git2/oidarray.h
 * @brief An array of object IDs
 * @defgroup git_oidarray Arrays of object IDs
 * @ingroup Git
 * @{
 *)

(** Array of object ids  *)

type
  git_oidarray = record
    ids: Pgit_oid;
    Count: size_t;
  end;

  (**
   * Free the object IDs contained in an oid_array.  This method should
   * be called on `git_oidarray` objects that were provided by the
   * library.  Not doing so will result in a memory leak.
   *
   * This does not free the `git_oidarray` itself, since the library will
   * never allocate that object directly itself.
   *
   * @param array git_oidarray from which to free oid data
   *)

type
  Pgit_oidarray = ^git_oidarray;

procedure git_oidarray_dispose(array_: Pgit_oidarray); cdecl; external libgit2_dll {$IFDEF LIBGIT2_DLL_DELAY_LOAD}delayed{$ENDIF};

(** @}  *)


