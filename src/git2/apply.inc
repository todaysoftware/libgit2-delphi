(**
 * @file git2/apply.h
 * @brief Git patch application routines
 * @defgroup git_apply Git patch application routines
 * @ingroup Git
 * @{
  *)

(**
 * When applying a patch, callback that will be made per delta (file).
 *
 * When the callback:
 * - returns < 0, the apply process will be aborted.
 * - returns > 0, the delta will not be applied, but the apply process
 *      continues
 * - returns 0, the delta is applied, and the apply process continues.
 *
 * @param delta The delta to be applied
 * @param payload User-specified payload
 * @return 0 if the delta is applied, < 0 if the apply process will be aborted
 *	or > 0 if the delta will not be applied.
  *)

type
  git_apply_delta_cb = function(delta: Pgit_diff_delta; payload: Pointer): Integer; cdecl;

  (**
   * When applying a patch, callback that will be made per hunk.
   *
   * When the callback:
   * - returns < 0, the apply process will be aborted.
   * - returns > 0, the hunk will not be applied, but the apply process
   *      continues
   * - returns 0, the hunk is applied, and the apply process continues.
   *
   * @param hunk The hunk to be applied
   * @param payload User-specified payload
   * @return 0 if the hunk is applied, < 0 if the apply process will be aborted
   *	or > 0 if the hunk will not be applied.
    *)

type
  git_apply_hunk_cb = function(hunk: Pgit_diff_hunk; payload: Pointer): Integer; cdecl;

  (** Flags controlling the behavior of git_apply  *)

const
  (**
  * Don't actually make changes, just test that the patch applies.
  * This is the equivalent of `git apply --check`.
   *)
  GIT_APPLY_CHECK             = (1 shl 0);
type
  git_apply_flags_t = Integer;

  (**
 * Apply options structure
 *
 * Initialize with `GIT_APPLY_OPTIONS_INIT`. Alternatively, you can
 * use `git_apply_options_init`.
 *
 * @see git_apply_to_tree, git_apply
  *)

  git_apply_options = record
    version: Cardinal; (**< The version  *)
    (** When applying a patch, callback that will be made per delta (file).  *)
    delta_cb: git_apply_delta_cb;
    (** When applying a patch, callback that will be made per hunk.  *)
    hunk_cb: git_apply_hunk_cb;
    (** Payload passed to both delta_cb & hunk_cb.  *)
    payload: Pointer;
    (** Bitmask of git_apply_flags_t  *)
    flags: Cardinal;
  end;
  Pgit_apply_options = ^git_apply_options;

const
  GIT_APPLY_OPTIONS_VERSION   = 1;
  //GIT_APPLY_OPTIONS_INIT = { GIT_APPLY_OPTIONS_VERSION };

(**
 * Initialize git_apply_options structure
 *
 * Initialize a `git_apply_options` with default values. Equivalent to creating
 * an instance with GIT_APPLY_OPTIONS_INIT.
 *
 * @param opts The `git_apply_options` struct to initialize.
 * @param version The struct version; pass `GIT_APPLY_OPTIONS_VERSION`
 * @return 0 on success or -1 on failure.
 *)

function git_apply_options_init(opts: Pgit_apply_options; version: Cardinal)
  : Integer; cdecl; external libgit2_dll;

(**
 * Apply a `git_diff` to a `git_tree`, and return the resulting image
 * as an index.
 *
 * @param out the postimage of the application
 * @param repo the repository to apply
 * @param preimage the tree to apply the diff to
 * @param diff the diff to apply
 * @param options the options for the apply (or null for defaults)
 * @return 0 or an error code
  *)

function git_apply_to_tree(out_: PPgit_index; repo: Pgit_repository; preimage: Pgit_tree; diff: Pgit_diff; options:
  Pgit_apply_options): Integer; cdecl; external libgit2_dll;

(** Possible application locations for git_apply  *)

const
  (**
  * Apply the patch to the workdir, leaving the index untouched.
  * This is the equivalent of `git apply` with no location argument.
   *)
  GIT_APPLY_LOCATION_WORKDIR  = 0;
  (**
  * Apply the patch to the index, leaving the working directory
  * untouched.  This is the equivalent of `git apply --cached`.
   *)
  GIT_APPLY_LOCATION_INDEX    = 1;
  (**
  * Apply the patch to both the working directory and the index.
  * This is the equivalent of `git apply --index`.
   *)
  GIT_APPLY_LOCATION_BOTH     = 2;
type
  git_apply_location_t = Integer;

  (**
 * Apply a `git_diff` to the given repository, making changes directly
 * in the working directory, the index, or both.
 *
 * @param repo the repository to apply to
 * @param diff the diff to apply
 * @param location the location to apply (workdir, index or both)
 * @param options the options for the apply (or null for defaults)
 * @return 0 or an error code
  *)

function git_apply(repo: Pgit_repository; diff: Pgit_diff; location: git_apply_location_t; options: Pgit_apply_options): Integer;
  cdecl; external libgit2_dll;

(** @}  *)



