(**
 * @file git2/stash.h
 * @brief Git stash management routines
 * @ingroup Git
 * @{
 *)

(**
 * Stash flags
 *)

const
  (**
   * No option, default
   *)
  GIT_STASH_DEFAULT           = 0;
  (**
   * All changes already added to the index are left intact in
   * the working directory
   *)
  GIT_STASH_KEEP_INDEX        = (1 shl 0);
  (**
   * All untracked files are also stashed and then cleaned up
   * from the working directory
   *)
  GIT_STASH_INCLUDE_UNTRACKED = (1 shl 1);
  (**
   * All ignored files are also stashed and then cleaned up from
   * the working directory
   *)
  GIT_STASH_INCLUDE_IGNORED   = (1 shl 2);
type
  git_stash_flags = Integer;

  (**
   * Save the local modifications to a new stash.
   *
   * @param out Object id of the commit containing the stashed state.
   * This commit is also the target of the direct reference refs/stash.
   *
   * @param repo The owning repository.
   *
   * @param stasher The identity of the person performing the stashing.
   *
   * @param message Optional description along with the stashed state.
   *
   * @param flags Flags to control the stashing process. (see GIT_STASH_* above)
   *
   * @return 0 on success, GIT_ENOTFOUND where there's nothing to stash,
   * or error code.
   *)

function git_stash_save(out_: Pgit_oid; repo: Pgit_repository; stasher: Pgit_signature;
  message: PAnsiChar; flags: uint32_t): Integer; cdecl; external libgit2_dll;

(** Stash application flags.  *)

const
  GIT_STASH_APPLY_DEFAULT     = 0;
  (* Try to reinstate not only the working tree's changes,
   * but also the index's changes.
   *)
  GIT_STASH_APPLY_REINSTATE_INDEX = (1 shl 0);
type
  git_stash_apply_flags = Integer;

  (** Stash apply progression states  *)

const
  GIT_STASH_APPLY_PROGRESS_NONE = 0;
  (** Loading the stashed data from the object database.  *)
  GIT_STASH_APPLY_PROGRESS_LOADING_STASH = 1;
  (** The stored index is being analyzed.  *)
  GIT_STASH_APPLY_PROGRESS_ANALYZE_INDEX = 2;
  (** The modified files are being analyzed.  *)
  GIT_STASH_APPLY_PROGRESS_ANALYZE_MODIFIED = 3;
  (** The untracked and ignored files are being analyzed.  *)
  GIT_STASH_APPLY_PROGRESS_ANALYZE_UNTRACKED = 4;
  (** The untracked files are being written to disk.  *)
  GIT_STASH_APPLY_PROGRESS_CHECKOUT_UNTRACKED = 5;
  (** The modified files are being written to disk.  *)
  GIT_STASH_APPLY_PROGRESS_CHECKOUT_MODIFIED = 6;
  (** The stash was applied successfully.  *)
  GIT_STASH_APPLY_PROGRESS_DONE = 7;
type
  git_stash_apply_progress_t = Integer;

  (**
   * Stash application progress notification function.
   * Return 0 to continue processing, or a negative value to
   * abort the stash application.
   *)

  git_stash_apply_progress_cb = function(progress: git_stash_apply_progress_t; payload: Pointer): Integer; cdecl;

  (**
   * Stash application options structure
   *
   * Initialize with `GIT_STASH_APPLY_OPTIONS_INIT`. Alternatively, you can
   * use `git_stash_apply_options_init`.
   *
   *)

  git_stash_apply_options = record
    version: Cardinal;
    (** See `git_stash_apply_flags`, above.  *)
    flags: uint32_t;
    (** Options to use when writing files to the working directory.  *)
    checkout_options: git_checkout_options;
    (** Optional callback to notify the consumer of application progress.  *)
    progress_cb: git_stash_apply_progress_cb;
    progress_payload: Pointer;
  end;
  Pgit_stash_apply_options = ^git_stash_apply_options;

const
  GIT_STASH_APPLY_OPTIONS_VERSION = 1;
  //GIT_STASH_APPLY_OPTIONS_INIT = { GIT_STASH_APPLY_OPTIONS_VERSION , GIT_STASH_APPLY_DEFAULT , GIT_CHECKOUT_OPTIONS_INIT };
  (**
   * Initialize git_stash_apply_options structure
   *
   * Initializes a `git_stash_apply_options` with default values. Equivalent to
   * creating an instance with `GIT_STASH_APPLY_OPTIONS_INIT`.
   *
   * @param opts The `git_stash_apply_options` struct to initialize.
   * @param version The struct version; pass `GIT_STASH_APPLY_OPTIONS_VERSION`.
   * @return Zero on success; -1 on failure.
   *)

function git_stash_apply_options_init(opts: Pgit_stash_apply_options; version: Cardinal): Integer; cdecl; external libgit2_dll;

(**
 * Apply a single stashed state from the stash list.
 *
 * If local changes in the working directory conflict with changes in the
 * stash then GIT_EMERGECONFLICT will be returned.  In this case, the index
 * will always remain unmodified and all files in the working directory will
 * remain unmodified.  However, if you are restoring untracked files or
 * ignored files and there is a conflict when applying the modified files,
 * then those files will remain in the working directory.
 *
 * If passing the GIT_STASH_APPLY_REINSTATE_INDEX flag and there would be
 * conflicts when reinstating the index, the function will return
 * GIT_EMERGECONFLICT and both the working directory and index will be left
 * unmodified.
 *
 * Note that a minimum checkout strategy of `GIT_CHECKOUT_SAFE` is implied.
 *
 * @param repo The owning repository.
 * @param index The position within the stash list. 0 points to the
 *              most recent stashed state.
 * @param options Optional options to control how stashes are applied.
 *
 * @return 0 on success, GIT_ENOTFOUND if there's no stashed state for the
 *         given index, GIT_EMERGECONFLICT if changes exist in the working
 *         directory, or an error code
 *)

function git_stash_apply(repo: Pgit_repository; index_: size_t;
  options: Pgit_stash_apply_options): Integer; cdecl; external libgit2_dll;

(**
 * This is a callback function you can provide to iterate over all the
 * stashed states that will be invoked per entry.
 *
 * @param index The position within the stash list. 0 points to the
 *              most recent stashed state.
 * @param message The stash message.
 * @param stash_id The commit oid of the stashed state.
 * @param payload Extra parameter to callback function.
 * @return 0 to continue iterating or non-zero to stop.
 *)

type
  git_stash_cb = function(index_: size_t; message: PAnsiChar; stash_id: Pgit_oid; payload: Pointer): Integer; cdecl;

  (**
   * Loop over all the stashed states and issue a callback for each one.
   *
   * If the callback returns a non-zero value, this will stop looping.
   *
   * @param repo Repository where to find the stash.
   *
   * @param callback Callback to invoke per found stashed state. The most
   *                 recent stash state will be enumerated first.
   *
   * @param payload Extra parameter to callback function.
   *
   * @return 0 on success, non-zero callback return value, or error code.
   *)

function git_stash_foreach(repo: Pgit_repository; callback: git_stash_cb;
  payload: Pointer): Integer; cdecl; external libgit2_dll;

(**
 * Remove a single stashed state from the stash list.
 *
 * @param repo The owning repository.
 *
 * @param index The position within the stash list. 0 points to the
 * most recent stashed state.
 *
 * @return 0 on success, GIT_ENOTFOUND if there's no stashed state for the given
 * index, or error code.
 *)

function git_stash_drop(repo: Pgit_repository; index_: size_t): Integer; cdecl; external libgit2_dll;

(**
 * Apply a single stashed state from the stash list and remove it from the list
 * if successful.
 *
 * @param repo The owning repository.
 * @param index The position within the stash list. 0 points to the
 *              most recent stashed state.
 * @param options Optional options to control how stashes are applied.
 *
 * @return 0 on success, GIT_ENOTFOUND if there's no stashed state for the given
 * index, or error code. (see git_stash_apply() above for details)
 *)

function git_stash_pop(repo: Pgit_repository; index_: size_t;
  options: Pgit_stash_apply_options): Integer; cdecl; external libgit2_dll;

(** @}  *)



