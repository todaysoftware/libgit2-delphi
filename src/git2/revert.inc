(**
 * @file git2/revert.h
 * @brief Git revert routines
 * @defgroup git_revert Git revert routines
 * @ingroup Git
 * @{
 *)

(**
 * Options for revert
 *)

type
  git_revert_options = record
    version: Cardinal;
    (** For merge commits, the "mainline" is treated as the parent.  *)
    mainline: Cardinal;
    merge_opts: git_merge_options; (**< Options for the merging  *)
    checkout_opts: git_checkout_options; (**< Options for the checkout  *)
  end;
  Pgit_revert_options = ^git_revert_options;

const
  GIT_REVERT_OPTIONS_VERSION  = 1;
  //GIT_REVERT_OPTIONS_INIT = { GIT_REVERT_OPTIONS_VERSION , 0 , GIT_MERGE_OPTIONS_INIT , GIT_CHECKOUT_OPTIONS_INIT };
  (**
   * Initialize git_revert_options structure
   *
   * Initializes a `git_revert_options` with default values. Equivalent to
   * creating an instance with `GIT_REVERT_OPTIONS_INIT`.
   *
   * @param opts The `git_revert_options` struct to initialize.
   * @param version The struct version; pass `GIT_REVERT_OPTIONS_VERSION`.
   * @return Zero on success; -1 on failure.
   *)

function git_revert_options_init(opts: Pgit_revert_options; version: Cardinal): Integer; cdecl; external libgit2_dll;

(**
 * Reverts the given commit against the given "our" commit, producing an
 * index that reflects the result of the revert.
 *
 * The returned index must be freed explicitly with `git_index_free`.
 *
 * @param out pointer to store the index result in
 * @param repo the repository that contains the given commits
 * @param revert_commit the commit to revert
 * @param our_commit the commit to revert against (eg, HEAD)
 * @param mainline the parent of the revert commit, if it is a merge
 * @param merge_options the merge options (or null for defaults)
 * @return zero on success, -1 on failure.
 *)

function git_revert_commit(out_: PPgit_index; repo: Pgit_repository; revert_commit, our_commit: Pgit_commit;
  mainline: Cardinal; merge_options: Pgit_merge_options): Integer; cdecl; external libgit2_dll;

(**
 * Reverts the given commit, producing changes in the index and working directory.
 *
 * @param repo the repository to revert
 * @param commit the commit to revert
 * @param given_opts the revert options (or null for defaults)
 * @return zero on success, -1 on failure.
 *)

function git_revert(repo: Pgit_repository; commit: Pgit_commit;
  given_opts: Pgit_revert_options): Integer; cdecl; external libgit2_dll;

(** @}  *)



