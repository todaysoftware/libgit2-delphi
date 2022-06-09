(**
 * @file git2/checkout.h
 * @brief Git checkout routines
 * @defgroup git_checkout Git checkout routines
 * @ingroup Git
 * @{
  *)

(**
 * Checkout behavior flags
 *
 * In libgit2, checkout is used to update the working directory and index
 * to match a target tree.  Unlike git checkout, it does not move the HEAD
 * commit for you - use `git_repository_set_head` or the like to do that.
 *
 * Checkout looks at (up to) four things: the "target" tree you want to
 * check out, the "baseline" tree of what was checked out previously, the
 * working directory for actual files, and the index for staged changes.
 *
 * You give checkout one of three strategies for update:
 *
 * - `GIT_CHECKOUT_NONE` is a dry-run strategy that checks for conflicts,
 *   etc., but doesn't make any actual changes.
 *
 * - `GIT_CHECKOUT_FORCE` is at the opposite extreme, taking any action to
 *   make the working directory match the target (including potentially
 *   discarding modified files).
 *
 * - `GIT_CHECKOUT_SAFE` is between these two options, it will only make
 *   modifications that will not lose changes.
 *
 *                         |  target == baseline   |  target != baseline  |
 *    ---------------------|-----------------------|----------------------|
 *     workdir == baseline |       no action       |  create, update, or  |
 *                         |                       |     delete file      |
 *    ---------------------|-----------------------|----------------------|
 *     workdir exists and  |       no action       |   conflict (notify   |
 *       is != baseline    | notify dirty MODIFIED | and cancel checkout) |
 *    ---------------------|-----------------------|----------------------|
 *      workdir missing,   | notify dirty DELETED  |     create file      |
 *      baseline present   |                       |                      |
 *    ---------------------|-----------------------|----------------------|
 *
 * To emulate `git checkout`, use `GIT_CHECKOUT_SAFE` with a checkout
 * notification callback (see below) that displays information about dirty
 * files.  The default behavior will cancel checkout on conflicts.
 *
 * To emulate `git checkout-index`, use `GIT_CHECKOUT_SAFE` with a
 * notification callback that cancels the operation if a dirty-but-existing
 * file is found in the working directory.  This core git command isn't
 * quite "force" but is sensitive about some types of changes.
 *
 * To emulate `git checkout -f`, use `GIT_CHECKOUT_FORCE`.
 *
 *
 * There are some additional flags to modify the behavior of checkout:
 *
 * - GIT_CHECKOUT_ALLOW_CONFLICTS makes SAFE mode apply safe file updates
 *   even if there are conflicts (instead of cancelling the checkout).
 *
 * - GIT_CHECKOUT_REMOVE_UNTRACKED means remove untracked files (i.e. not
 *   in target, baseline, or index, and not ignored) from the working dir.
 *
 * - GIT_CHECKOUT_REMOVE_IGNORED means remove ignored files (that are also
 *   untracked) from the working directory as well.
 *
 * - GIT_CHECKOUT_UPDATE_ONLY means to only update the content of files that
 *   already exist.  Files will not be created nor deleted.  This just skips
 *   applying adds, deletes, and typechanges.
 *
 * - GIT_CHECKOUT_DONT_UPDATE_INDEX prevents checkout from writing the
 *   updated files' information to the index.
 *
 * - Normally, checkout will reload the index and git attributes from disk
 *   before any operations.  GIT_CHECKOUT_NO_REFRESH prevents this reload.
 *
 * - Unmerged index entries are conflicts.  GIT_CHECKOUT_SKIP_UNMERGED skips
 *   files with unmerged index entries instead.  GIT_CHECKOUT_USE_OURS and
 *   GIT_CHECKOUT_USE_THEIRS to proceed with the checkout using either the
 *   stage 2 ("ours") or stage 3 ("theirs") version of files in the index.
 *
 * - GIT_CHECKOUT_DONT_OVERWRITE_IGNORED prevents ignored files from being
 *   overwritten.  Normally, files that are ignored in the working directory
 *   are not considered "precious" and may be overwritten if the checkout
 *   target contains that file.
 *
 * - GIT_CHECKOUT_DONT_REMOVE_EXISTING prevents checkout from removing
 *   files or folders that fold to the same name on case insensitive
 *   filesystems.  This can cause files to retain their existing names
 *   and write through existing symbolic links.
  *)

const
  GIT_CHECKOUT_NONE           = 0; (**< default is a dry run, no actual updates  *)
  (**
  * Allow safe updates that cannot overwrite uncommitted data.
  * If the uncommitted changes don't conflict with the checked out files,
  * the checkout will still proceed, leaving the changes intact.
  *
  * Mutually exclusive with GIT_CHECKOUT_FORCE.
  * GIT_CHECKOUT_FORCE takes precedence over GIT_CHECKOUT_SAFE.
   *)
  GIT_CHECKOUT_SAFE           = (1 shl 0);
  (**
  * Allow all updates to force working directory to look like index.
  *
  * Mutually exclusive with GIT_CHECKOUT_SAFE.
  * GIT_CHECKOUT_FORCE takes precedence over GIT_CHECKOUT_SAFE.
   *)
  GIT_CHECKOUT_FORCE          = (1 shl 1);
  (** Allow checkout to recreate missing files  *)
  GIT_CHECKOUT_RECREATE_MISSING = (1 shl 2);
  (** Allow checkout to make safe updates even if conflicts are found  *)
  GIT_CHECKOUT_ALLOW_CONFLICTS = (1 shl 4);
  (** Remove untracked files not in index (that are not ignored)  *)
  GIT_CHECKOUT_REMOVE_UNTRACKED = (1 shl 5);
  (** Remove ignored files not in index  *)
  GIT_CHECKOUT_REMOVE_IGNORED = (1 shl 6);
  (** Only update existing files, don't create new ones  *)
  GIT_CHECKOUT_UPDATE_ONLY    = (1 shl 7);
  (**
  * Normally checkout updates index entries as it goes; this stops that.
  * Implies `GIT_CHECKOUT_DONT_WRITE_INDEX`.
   *)
  GIT_CHECKOUT_DONT_UPDATE_INDEX = (1 shl 8);
  (** Don't refresh index/config/etc before doing checkout  *)
  GIT_CHECKOUT_NO_REFRESH     = (1 shl 9);
  (** Allow checkout to skip unmerged files  *)
  GIT_CHECKOUT_SKIP_UNMERGED  = (1 shl 10);
  (** For unmerged files, checkout stage 2 from index  *)
  GIT_CHECKOUT_USE_OURS       = (1 shl 11);
  (** For unmerged files, checkout stage 3 from index  *)
  GIT_CHECKOUT_USE_THEIRS     = (1 shl 12);
  (** Treat pathspec as simple list of exact match file paths  *)
  GIT_CHECKOUT_DISABLE_PATHSPEC_MATCH = (1 shl 13);
  (** Ignore directories in use, they will be left empty  *)
  GIT_CHECKOUT_SKIP_LOCKED_DIRECTORIES = (1 shl 18);
  (** Don't overwrite ignored files that exist in the checkout target  *)
  GIT_CHECKOUT_DONT_OVERWRITE_IGNORED = (1 shl 19);
  (** Write normal merge files for conflicts  *)
  GIT_CHECKOUT_CONFLICT_STYLE_MERGE = (1 shl 20);
  (** Include common ancestor data in diff3 format files for conflicts  *)
  GIT_CHECKOUT_CONFLICT_STYLE_DIFF3 = (1 shl 21);
  (** Don't overwrite existing files or folders  *)
  GIT_CHECKOUT_DONT_REMOVE_EXISTING = (1 shl 22);
  (** Normally checkout writes the index upon completion; this prevents that.  *)
  GIT_CHECKOUT_DONT_WRITE_INDEX = (1 shl 23);
  (**
   * THE FOLLOWING OPTIONS ARE NOT YET IMPLEMENTED
   *)
  (** Recursively checkout submodules with same options (NOT IMPLEMENTED)  *)
  GIT_CHECKOUT_UPDATE_SUBMODULES = (1 shl 16);
  (** Recursively checkout submodules if HEAD moved in super repo (NOT IMPLEMENTED)  *)
  GIT_CHECKOUT_UPDATE_SUBMODULES_IF_CHANGED = (1 shl 17);
type
  git_checkout_strategy_t = Integer;

  (**
 * Checkout notification flags
 *
 * Checkout will invoke an options notification callback (`notify_cb`) for
 * certain cases - you pick which ones via `notify_flags`:
 *
 * Returning a non-zero value from this callback will cancel the checkout.
 * The non-zero return value will be propagated back and returned by the
 * git_checkout_... call.
 *
 * Notification callbacks are made prior to modifying any files on disk,
 * so canceling on any notification will still happen prior to any files
 * being modified.
  *)

const
  GIT_CHECKOUT_NOTIFY_NONE    = 0;
  (**
   * Invokes checkout on conflicting paths.
   *)
  GIT_CHECKOUT_NOTIFY_CONFLICT = (1 shl 0);
  (**
   * Notifies about "dirty" files, i.e. those that do not need an update
   * but no longer match the baseline.  Core git displays these files when
   * checkout runs, but won't stop the checkout.
   *)
  GIT_CHECKOUT_NOTIFY_DIRTY   = (1 shl 1);
  (**
   * Sends notification for any file changed.
   *)
  GIT_CHECKOUT_NOTIFY_UPDATED = (1 shl 2);
  (**
   * Notifies about untracked files.
   *)
  GIT_CHECKOUT_NOTIFY_UNTRACKED = (1 shl 3);
  (**
   * Notifies about ignored files.
   *)
  GIT_CHECKOUT_NOTIFY_IGNORED = (1 shl 4);
  GIT_CHECKOUT_NOTIFY_ALL     = $0FFFF;
type
  git_checkout_notify_t = Integer;

  (** Checkout performance-reporting structure  *)

  git_checkout_perfdata = record
    mkdir_calls: size_t;
    stat_calls: size_t;
    chmod_calls: size_t;
  end;
  Pgit_checkout_perfdata = ^git_checkout_perfdata;

  (** Checkout notification callback function  *)

type
  git_checkout_notify_cb = function(why: git_checkout_notify_t; path: PAnsiChar; baseline, target, workdir: Pgit_diff_file;
    payload: Pointer): Integer; cdecl;

  (** Checkout progress notification function  *)

type
  git_checkout_progress_cb = procedure(path: PAnsiChar; completed_steps, total_steps: size_t; payload: Pointer); cdecl;

  (** Checkout perfdata notification function  *)

  git_checkout_perfdata_cb = procedure(perfdata: Pgit_checkout_perfdata; payload: Pointer); cdecl;

  (**
   * Checkout options structure
   *
   * Initialize with `GIT_CHECKOUT_OPTIONS_INIT`. Alternatively, you can
   * use `git_checkout_options_init`.
   *
    *)

type
  git_checkout_options = record
    version: Cardinal; (**< The version  *)
    checkout_strategy: Cardinal; (**< default will be a safe checkout  *)
    disable_filters: Integer; (**< don't apply filters like CRLF conversion  *)
    dir_mode: Cardinal; (**< default is 0755  *)
    file_mode: Cardinal; (**< default is 0644 or 0755 as dictated by blob  *)
    file_open_flags: Integer; (**< default is O_CREAT | O_TRUNC | O_WRONLY  *)
    notify_flags: Cardinal; (**< see `git_checkout_notify_t` above  *)
    (**
     * Optional callback to get notifications on specific file states.
     * @see git_checkout_notify_t
     *)
    notify_cb: git_checkout_notify_cb;
    (** Payload passed to notify_cb  *)
    notify_payload: Pointer;
    (** Optional callback to notify the consumer of checkout progress.  *)
    progress_cb: git_checkout_progress_cb;
    (** Payload passed to progress_cb  *)
    progress_payload: Pointer;
    (**
     * A list of wildmatch patterns or paths.
     *
     * By default, all paths are processed. If you pass an array of wildmatch
     * patterns, those will be used to filter which paths should be taken into
     * account.
     *
     * Use GIT_CHECKOUT_DISABLE_PATHSPEC_MATCH to treat as a simple list.
     *)
    paths: git_strarray;
    (**
     * The expected content of the working directory; defaults to HEAD.
     *
     * If the working directory does not match this baseline information,
     * that will produce a checkout conflict.
     *)
    baseline: Pgit_tree;
    (**
     * Like `baseline` above, though expressed as an index.  This
     * option overrides `baseline`.
     *)
    baseline_index: Pgit_index;
    target_directory: PAnsiChar; (**< alternative checkout path to workdir  *)
    ancestor_label: PAnsiChar; (**< the name of the common ancestor side of conflicts  *)
    our_label: PAnsiChar; (**< the name of the "our" side of conflicts  *)
    their_label: PAnsiChar; (**< the name of the "their" side of conflicts  *)
    (** Optional callback to notify the consumer of performance data.  *)
    perfdata_cb: git_checkout_perfdata_cb;
    (** Payload passed to perfdata_cb  *)
    perfdata_payload: Pointer;
  end;
  Pgit_checkout_options = ^git_checkout_options;

const
  GIT_CHECKOUT_OPTIONS_VERSION = 1;
  //GIT_CHECKOUT_OPTIONS_INIT = { GIT_CHECKOUT_OPTIONS_VERSION , GIT_CHECKOUT_SAFE };
  (**
   * Initialize git_checkout_options structure
   *
   * Initializes a `git_checkout_options` with default values. Equivalent to creating
   * an instance with GIT_CHECKOUT_OPTIONS_INIT.
   *
   * @param opts The `git_checkout_options` struct to initialize.
   * @param version The struct version; pass `GIT_CHECKOUT_OPTIONS_VERSION`.
   * @return Zero on success; -1 on failure.
   *)

function git_checkout_options_init(opts: Pgit_checkout_options; version: Cardinal): Integer; cdecl; external libgit2_dll;

(**
 * Updates files in the index and the working tree to match the content of
 * the commit pointed at by HEAD.
 *
 * Note that this is _not_ the correct mechanism used to switch branches;
 * do not change your `HEAD` and then call this method, that would leave
 * you with checkout conflicts since your working directory would then
 * appear to be dirty.  Instead, checkout the target of the branch and
 * then update `HEAD` using `git_repository_set_head` to point to the
 * branch you checked out.
 *
 * @param repo repository to check out (must be non-bare)
 * @param opts specifies checkout options (may be NULL)
 * @return 0 on success, GIT_EUNBORNBRANCH if HEAD points to a non
 *         existing branch, non-zero value returned by `notify_cb`, or
 *         other error code < 0 (use git_error_last for error details)
  *)

function git_checkout_head(repo: Pgit_repository;
  opts: Pgit_checkout_options): Integer; cdecl; external libgit2_dll;

(**
 * Updates files in the working tree to match the content of the index.
 *
 * @param repo repository into which to check out (must be non-bare)
 * @param index index to be checked out (or NULL to use repository index)
 * @param opts specifies checkout options (may be NULL)
 * @return 0 on success, non-zero return value from `notify_cb`, or error
 *         code < 0 (use git_error_last for error details)
  *)

function git_checkout_index(repo: Pgit_repository; index_: Pgit_index;
  opts: Pgit_checkout_options): Integer; cdecl; external libgit2_dll;

(**
 * Updates files in the index and working tree to match the content of the
 * tree pointed at by the treeish.
 *
 * @param repo repository to check out (must be non-bare)
 * @param treeish a commit, tag or tree which content will be used to update
 * the working directory (or NULL to use HEAD)
 * @param opts specifies checkout options (may be NULL)
 * @return 0 on success, non-zero return value from `notify_cb`, or error
 *         code < 0 (use git_error_last for error details)
  *)

function git_checkout_tree(repo: Pgit_repository; treeish: Pgit_object;
  opts: Pgit_checkout_options): Integer; cdecl; external libgit2_dll;

(** @}  *)



