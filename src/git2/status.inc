(**
 * @file git2/status.h
 * @brief Git file status routines
 * @defgroup git_status Git file status routines
 * @ingroup Git
 * @{
 *)

(**
 * Status flags for a single file.
 *
 * A combination of these values will be returned to indicate the status of
 * a file.  Status compares the working directory, the index, and the
 * current HEAD of the repository.  The `GIT_STATUS_INDEX` set of flags
 * represents the status of file in the index relative to the HEAD, and the
 * `GIT_STATUS_WT` set of flags represent the status of the file in the
 * working directory relative to the index.
 *)

const
  GIT_STATUS_CURRENT          = 0;
  GIT_STATUS_INDEX_NEW        = (1 shl 0);
  GIT_STATUS_INDEX_MODIFIED   = (1 shl 1);
  GIT_STATUS_INDEX_DELETED    = (1 shl 2);
  GIT_STATUS_INDEX_RENAMED    = (1 shl 3);
  GIT_STATUS_INDEX_TYPECHANGE = (1 shl 4);
  GIT_STATUS_WT_NEW           = (1 shl 7);
  GIT_STATUS_WT_MODIFIED      = (1 shl 8);
  GIT_STATUS_WT_DELETED       = (1 shl 9);
  GIT_STATUS_WT_TYPECHANGE    = (1 shl 10);
  GIT_STATUS_WT_RENAMED       = (1 shl 11);
  GIT_STATUS_WT_UNREADABLE    = (1 shl 12);
  GIT_STATUS_IGNORED          = (1 shl 14);
  GIT_STATUS_CONFLICTED       = (1 shl 15);
type
  git_status_t = Integer;

  (**
   * Function pointer to receive status on individual files
   *
   * `path` is the relative path to the file from the root of the repository.
   *
   * `status_flags` is a combination of `git_status_t` values that apply.
   *
   * `payload` is the value you passed to the foreach function as payload.
   *)

type
  git_status_cb = function(path: PAnsiChar; status_flags: Cardinal; payload: Pointer): Integer; cdecl;

  (**
   * Select the files on which to report status.
   *
   * With `git_status_foreach_ext`, this will control which changes get
   * callbacks.  With `git_status_list_new`, these will control which
   * changes are included in the list.
   *)

const
  (**
   * The default. This roughly matches `git status --porcelain` regarding
   * which files are included and in what order.
   *)
  GIT_STATUS_SHOW_INDEX_AND_WORKDIR = 0;
  (**
   * Only gives status based on HEAD to index comparison, not looking at
   * working directory changes.
   *)
  GIT_STATUS_SHOW_INDEX_ONLY  = 1;
  (**
   * Only gives status based on index to working directory comparison,
   * not comparing the index to the HEAD.
   *)
  GIT_STATUS_SHOW_WORKDIR_ONLY = 2;
type
  git_status_show_t = Integer;

  (**
   * Flags to control status callbacks
   *
   * Calling `git_status_foreach()` is like calling the extended version
   * with: GIT_STATUS_OPT_INCLUDE_IGNORED, GIT_STATUS_OPT_INCLUDE_UNTRACKED,
   * and GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS.  Those options are bundled
   * together as `GIT_STATUS_OPT_DEFAULTS` if you want them as a baseline.
   *)

const
  (**
   * Says that callbacks should be made on untracked files.
   * These will only be made if the workdir files are included in the status
   * "show" option.
   *)
  GIT_STATUS_OPT_INCLUDE_UNTRACKED = (1 shl 0);
  (**
   * Says that ignored files get callbacks.
   * Again, these callbacks will only be made if the workdir files are
   * included in the status "show" option.
   *)
  GIT_STATUS_OPT_INCLUDE_IGNORED = (1 shl 1);
  (**
   * Indicates that callback should be made even on unmodified files.
   *)
  GIT_STATUS_OPT_INCLUDE_UNMODIFIED = (1 shl 2);
  (**
   * Indicates that submodules should be skipped.
   * This only applies if there are no pending typechanges to the submodule
   * (either from or to another type).
   *)
  GIT_STATUS_OPT_EXCLUDE_SUBMODULES = (1 shl 3);
  (**
   * Indicates that all files in untracked directories should be included.
   * Normally if an entire directory is new, then just the top-level
   * directory is included (with a trailing slash on the entry name).
   * This flag says to include all of the individual files in the directory
   * instead.
   *)
  GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS = (1 shl 4);
  (**
   * Indicates that the given path should be treated as a literal path,
   * and not as a pathspec pattern.
   *)
  GIT_STATUS_OPT_DISABLE_PATHSPEC_MATCH = (1 shl 5);
  (**
   * Indicates that the contents of ignored directories should be included
   * in the status. This is like doing `git ls-files -o -i --exclude-standard`
   * with core git.
   *)
  GIT_STATUS_OPT_RECURSE_IGNORED_DIRS = (1 shl 6);
  (**
   * Indicates that rename detection should be processed between the head and
   * the index and enables the GIT_STATUS_INDEX_RENAMED as a possible status
   * flag.
   *)
  GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX = (1 shl 7);
  (**
   * Indicates that rename detection should be run between the index and the
   * working directory and enabled GIT_STATUS_WT_RENAMED as a possible status
   * flag.
   *)
  GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR = (1 shl 8);
  (**
   * Overrides the native case sensitivity for the file system and forces
   * the output to be in case-sensitive order.
   *)
  GIT_STATUS_OPT_SORT_CASE_SENSITIVELY = (1 shl 9);
  (**
   * Overrides the native case sensitivity for the file system and forces
   * the output to be in case-insensitive order.
   *)
  GIT_STATUS_OPT_SORT_CASE_INSENSITIVELY = (1 shl 10);
  (**
   * Iindicates that rename detection should include rewritten files.
   *)
  GIT_STATUS_OPT_RENAMES_FROM_REWRITES = (1 shl 11);
  (**
   * Bypasses the default status behavior of doing a "soft" index reload
   * (i.e. reloading the index data if the file on disk has been modified
   * outside libgit2).
   *)
  GIT_STATUS_OPT_NO_REFRESH   = (1 shl 12);
  (**
   * Tells libgit2 to refresh the stat cache in the index for files that are
   * unchanged but have out of date stat einformation in the index.
   * It will result in less work being done on subsequent calls to get status.
   * This is mutually exclusive with the NO_REFRESH option.
   *)
  GIT_STATUS_OPT_UPDATE_INDEX = (1 shl 13);
  (**
   * Normally files that cannot be opened or read are ignored as
   * these are often transient files; this option will return
   * unreadable files as `GIT_STATUS_WT_UNREADABLE`.
   *)
  GIT_STATUS_OPT_INCLUDE_UNREADABLE = (1 shl 14);
  (**
   * Unreadable files will be detected and given the status
   * untracked instead of unreadable.
   *)
  GIT_STATUS_OPT_INCLUDE_UNREADABLE_AS_UNTRACKED = (1 shl 15);
type
  git_status_opt_t = Integer;

const
  GIT_STATUS_OPT_DEFAULTS     = (GIT_STATUS_OPT_INCLUDE_IGNORED or GIT_STATUS_OPT_INCLUDE_UNTRACKED or
    GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS);
  (**
   * Options to control how `git_status_foreach_ext()` will issue callbacks.
   *
   * Initialize with `GIT_STATUS_OPTIONS_INIT`. Alternatively, you can
   * use `git_status_options_init`.
   *
   *)

type
  git_status_options = record
    (**
     * The struct version; pass `GIT_STATUS_OPTIONS_VERSION`.
     *)
    version: Cardinal;
    (**
     * The `show` value is one of the `git_status_show_t` constants that
     * control which files to scan and in what order.
     *)
    show: git_status_show_t;
    (**
     * The `flags` value is an OR'ed combination of the
     * `git_status_opt_t` values above.
     *)
    flags: Cardinal;
    (**
     * The `pathspec` is an array of path patterns to match (using
     * fnmatch-style matching), or just an array of paths to match
     * exactly if `GIT_STATUS_OPT_DISABLE_PATHSPEC_MATCH` is specified
     * in the flags.
     *)
    pathspec: git_strarray;
    (**
     * The `baseline` is the tree to be used for comparison to the
     * working directory and index; defaults to HEAD.
     *)
    baseline: Pgit_tree;
  	(**
	   * Threshold above which similar files will be considered renames.
	   * This is equivalent to the -M option. Defaults to 50.
	   *)
	   rename_threshold: Word;
  end;
  Pgit_status_options = ^git_status_options;

const
  GIT_STATUS_OPTIONS_VERSION  = 1;
  //GIT_STATUS_OPTIONS_INIT = { GIT_STATUS_OPTIONS_VERSION };
  (**
   * Initialize git_status_options structure
   *
   * Initializes a `git_status_options` with default values. Equivalent to
   * creating an instance with `GIT_STATUS_OPTIONS_INIT`.
   *
   * @param opts The `git_status_options` struct to initialize.
   * @param version The struct version; pass `GIT_STATUS_OPTIONS_VERSION`.
   * @return Zero on success; -1 on failure.
   *)

function git_status_options_init(opts: Pgit_status_options; version: Cardinal): Integer; cdecl; external libgit2_dll;

(**
 * A status entry, providing the differences between the file as it exists
 * in HEAD and the index, and providing the differences between the index
 * and the working directory.
 *
 * The `status` value provides the status flags for this file.
 *
 * The `head_to_index` value provides detailed information about the
 * differences between the file in HEAD and the file in the index.
 *
 * The `index_to_workdir` value provides detailed information about the
 * differences between the file in the index and the file in the
 * working directory.
 *)

type
  git_status_entry = record
    status: git_status_t;
    head_to_index: Pgit_diff_delta;
    index_to_workdir: Pgit_diff_delta;
  end;

  (**
 * Gather file statuses and run a callback for each one.
 *
 * The callback is passed the path of the file, the status (a combination of
 * the `git_status_t` values above) and the `payload` data pointer passed
 * into this function.
 *
 * If the callback returns a non-zero value, this function will stop looping
 * and return that value to caller.
 *
 * @param repo A repository object
 * @param callback The function to call on each file
 * @param payload Pointer to pass through to callback function
 * @return 0 on success, non-zero callback return value, or error code
 *)

function git_status_foreach(repo: Pgit_repository; callback: git_status_cb;
  payload: Pointer): Integer; cdecl; external libgit2_dll;

(**
 * Gather file status information and run callbacks as requested.
 *
 * This is an extended version of the `git_status_foreach()` API that
 * allows for more granular control over which paths will be processed and
 * in what order.  See the `git_status_options` structure for details
 * about the additional controls that this makes available.
 *
 * Note that if a `pathspec` is given in the `git_status_options` to filter
 * the status, then the results from rename detection (if you enable it) may
 * not be accurate.  To do rename detection properly, this must be called
 * with no `pathspec` so that all files can be considered.
 *
 * @param repo Repository object
 * @param opts Status options structure
 * @param callback The function to call on each file
 * @param payload Pointer to pass through to callback function
 * @return 0 on success, non-zero callback return value, or error code
 *)

function git_status_foreach_ext(repo: Pgit_repository; opts: Pgit_status_options;
  callback: git_status_cb; payload: Pointer): Integer; cdecl; external libgit2_dll;

(**
 * Get file status for a single file.
 *
 * This tries to get status for the filename that you give.  If no files
 * match that name (in either the HEAD, index, or working directory), this
 * returns GIT_ENOTFOUND.
 *
 * If the name matches multiple files (for example, if the `path` names a
 * directory or if running on a case- insensitive filesystem and yet the
 * HEAD has two entries that both match the path), then this returns
 * GIT_EAMBIGUOUS because it cannot give correct results.
 *
 * This does not do any sort of rename detection.  Renames require a set of
 * targets and because of the path filtering, there is not enough
 * information to check renames correctly.  To check file status with rename
 * detection, there is no choice but to do a full `git_status_list_new` and
 * scan through looking for the path that you are interested in.
 *
 * @param status_flags Output combination of git_status_t values for file
 * @param repo A repository object
 * @param path The exact path to retrieve status for relative to the
 * repository working directory
 * @return 0 on success, GIT_ENOTFOUND if the file is not found in the HEAD,
 *      index, and work tree, GIT_EAMBIGUOUS if `path` matches multiple files
 *      or if it refers to a folder, and -1 on other errors.
 *)

function git_status_file(status_flags: PCardinal; repo: Pgit_repository;
  path: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Gather file status information and populate the `git_status_list`.
 *
 * Note that if a `pathspec` is given in the `git_status_options` to filter
 * the status, then the results from rename detection (if you enable it) may
 * not be accurate.  To do rename detection properly, this must be called
 * with no `pathspec` so that all files can be considered.
 *
 * @param out Pointer to store the status results in
 * @param repo Repository object
 * @param opts Status options structure
 * @return 0 on success or error code
 *)

function git_status_list_new(out_: PPgit_status_list; repo: Pgit_repository;
  opts: Pgit_status_options): Integer; cdecl; external libgit2_dll;

(**
 * Gets the count of status entries in this list.
 *
 * If there are no changes in status (at least according the options given
 * when the status list was created), this can return 0.
 *
 * @param statuslist Existing status list object
 * @return the number of status entries
 *)

function git_status_list_entrycount(statuslist: Pgit_status_list): size_t; cdecl; external libgit2_dll;

(**
 * Get a pointer to one of the entries in the status list.
 *
 * The entry is not modifiable and should not be freed.
 *
 * @param statuslist Existing status list object
 * @param idx Position of the entry
 * @return Pointer to the entry; NULL if out of bounds
  *)

type
  Pgit_status_entry = ^git_status_entry;
function git_status_byindex(statuslist: Pgit_status_list; idx: size_t): Pgit_status_entry; cdecl; external libgit2_dll;

(**
 * Free an existing status list
 *
 * @param statuslist Existing status list object
 *)

procedure git_status_list_free(statuslist: Pgit_status_list); cdecl; external libgit2_dll;

(**
 * Test if the ignore rules apply to a given file.
 *
 * This function checks the ignore rules to see if they would apply to the
 * given file.  This indicates if the file would be ignored regardless of
 * whether the file is already in the index or committed to the repository.
 *
 * One way to think of this is if you were to do "git add ." on the
 * directory containing the file, would it be added or not?
 *
 * @param ignored Boolean returning 0 if the file is not ignored, 1 if it is
 * @param repo A repository object
 * @param path The file to check ignores for, rooted at the repo's workdir.
 * @return 0 if ignore rules could be processed for the file (regardless
 *         of whether it exists or not), or an error < 0 if they could not.
 *)

function git_status_should_ignore(ignored: PInteger; repo: Pgit_repository;
  path: PAnsiChar): Integer; cdecl; external libgit2_dll;

(** @}  *)



