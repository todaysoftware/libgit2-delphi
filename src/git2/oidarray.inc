(** Array of object ids  *)

type
  git_oidarray = record
    ids: Pgit_oid;
    Count: size_t;
  end;

  (**
   * Free the OID array
   *
   * This method must (and must only) be called on `git_oidarray`
   * objects where the array is allocated by the library. Not doing so,
   * will result in a memory leak.
   *
   * This does not free the `git_oidarray` itself, since the library will
   * never allocate that object directly itself (it is more commonly embedded
   * inside another struct or created on the stack).
   *
   * @param array git_oidarray from which to free oid data
   *)

type
  Pgit_oidarray = ^git_oidarray;

procedure git_oidarray_free(array_: Pgit_oidarray); cdecl; external libgit2_dll;

(** @}  *)


