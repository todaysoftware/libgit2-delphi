(**
 * @file git2/revparse.h
 * @brief Git revision parsing routines
 * @defgroup git_revparse Git revision parsing routines
 * @ingroup Git
 * @{
 *)

(**
 * Find a single object, as specified by a revision string.
 *
 * See `man gitrevisions`, or
 * http://git-scm.com/docs/git-rev-parse.html#_specifying_revisions for
 * information on the syntax accepted.
 *
 * The returned object should be released with `git_object_free` when no
 * longer needed.
 *
 * @param out pointer to output object
 * @param repo the repository to search in
 * @param spec the textual specification for an object
 * @return 0 on success, GIT_ENOTFOUND, GIT_EAMBIGUOUS, GIT_EINVALIDSPEC or an error code
 *)

function git_revparse_single(out_: PPgit_object; repo: Pgit_repository; spec: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Find a single object and intermediate reference by a revision string.
 *
 * See `man gitrevisions`, or
 * http://git-scm.com/docs/git-rev-parse.html#_specifying_revisions for
 * information on the syntax accepted.
 *
 * In some cases (`@{<-n>}` or `<branchname>@{upstream}`), the expression may
 * point to an intermediate reference. When such expressions are being passed
 * in, `reference_out` will be valued as well.
 *
 * The returned object should be released with `git_object_free` and the
 * returned reference with `git_reference_free` when no longer needed.
 *
 * @param object_out pointer to output object
 * @param reference_out pointer to output reference or NULL
 * @param repo the repository to search in
 * @param spec the textual specification for an object
 * @return 0 on success, GIT_ENOTFOUND, GIT_EAMBIGUOUS, GIT_EINVALIDSPEC
 * or an error code
 *)

function git_revparse_ext(object_out: PPgit_object; reference_out: PPgit_reference; repo: Pgit_repository;
  spec: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Revparse flags.  These indicate the intended behavior of the spec passed to
 * git_revparse.
 *)

const
  (** The spec targeted a single object.  *)
  GIT_REVSPEC_SINGLE_         = 1 shl 0;
  (** The spec targeted a range of commits.  *)
  GIT_REVSPEC_RANGE           = 1 shl 1;
  (** The spec used the '...' operator, which invokes special semantics.  *)
  GIT_REVSPEC_MERGE_BASE      = 1 shl 2;
type
  git_revspec_mode_t = Integer;

  (**
   * Git Revision Spec: output of a `git_revspec` operation
   *)

  git_revspec = record
    (** The left element of the revspec; must be freed by the user  *)
    from: Pgit_object;
    (** The right element of the revspec; must be freed by the user  *)
    to_: Pgit_object;
    (** The intent of the revspec (i.e. `git_revparse_mode_t` flags)  *)
    flags: Cardinal;
  end;
  Pgit_revspec = ^git_revspec;

  (**
   * Parse a revision string for `from`, `to`, and intent.
   *
   * See `man gitrevisions` or
   * http://git-scm.com/docs/git-rev-parse.html#_specifying_revisions for
   * information on the syntax accepted.
   *
   * @param revspec Pointer to an user-allocated git_revspec struct where
   *	              the result of the rev-parse will be stored
   * @param repo the repository to search in
   * @param spec the rev-parse spec to parse
   * @return 0 on success, GIT_INVALIDSPEC, GIT_ENOTFOUND, GIT_EAMBIGUOUS or an error code
   *)

function git_revparse(revspec: Pgit_revspec; repo: Pgit_repository; spec: PAnsiChar): Integer; cdecl; external libgit2_dll;

(** @}  *)



