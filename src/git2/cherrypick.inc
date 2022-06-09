(**
 * @file git2/cherrypick.h
 * @brief Git cherry-pick routines
 * @defgroup git_cherrypick Git cherry-pick routines
 * @ingroup Git
 * @{
  *)

(**
 * Cherry-pick options
  *)

type
  git_cherrypick_options = record
    version: Cardinal;
    (** For merge commits, the "mainline" is treated as the parent.  *)
    mainline: Cardinal;
    merge_opts: git_merge_options; (**< Options for the merging  *)
    checkout_opts: git_checkout_options; (**< Options for the checkout  *)
  end;
  Pgit_cherrypick_options = ^git_cherrypick_options;

const
  GIT_CHERRYPICK_OPTIONS_VERSION = 1;
  //GIT_CHERRYPICK_OPTIONS_INIT = { GIT_CHERRYPICK_OPTIONS_VERSION , 0 , GIT_MERGE_OPTIONS_INIT , GIT_CHECKOUT_OPTIONS_INIT };
  (**
   * Initialize git_cherrypick_options structure
   *
   * Initializes a `git_cherrypick_options` with default values. Equivalent to creating
   * an instance with GIT_CHERRYPICK_OPTIONS_INIT.
   *
   * @param opts The `git_cherrypick_options` struct to initialize.
   * @param version The struct version; pass `GIT_CHERRYPICK_OPTIONS_VERSION`.
   * @return Zero on success; -1 on failure.
   *)

function git_cherrypick_options_init(opts: Pgit_cherrypick_options;
  version: Cardinal): Integer; cdecl; external libgit2_dll;

(**
 * Cherry-picks the given commit against the given "our" commit, producing an
 * index that reflects the result of the cherry-pick.
 *
 * The returned index must be freed explicitly with `git_index_free`.
 *
 * @param out pointer to store the index result in
 * @param repo the repository that contains the given commits
 * @param cherrypick_commit the commit to cherry-pick
 * @param our_commit the commit to cherry-pick against (eg, HEAD)
 * @param mainline the parent of the `cherrypick_commit`, if it is a merge
 * @param merge_options the merge options (or null for defaults)
 * @return zero on success, -1 on failure.
 *)

function git_cherrypick_commit(out_: PPgit_index; repo: Pgit_repository; cherrypick_commit, our_commit: Pgit_commit;
  mainline: Cardinal; merge_options: Pgit_merge_options): Integer; cdecl; external libgit2_dll;

(**
 * Cherry-pick the given commit, producing changes in the index and working directory.
 *
 * @param repo the repository to cherry-pick
 * @param commit the commit to cherry-pick
 * @param cherrypick_options the cherry-pick options (or null for defaults)
 * @return zero on success, -1 on failure.
 *)

function git_cherrypick(repo: Pgit_repository; commit: Pgit_commit;
  cherrypick_options: Pgit_cherrypick_options): Integer; cdecl; external libgit2_dll;

(** @}  *)



