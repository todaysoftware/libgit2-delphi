(**
 * List names of linked working trees
 *
 * The returned list should be released with `git_strarray_free`
 * when no longer needed.
 *
 * @param out pointer to the array of working tree names
 * @param repo the repo to use when listing working trees
 * @return 0 or an error code
 *)

function git_worktree_list(out_: Pgit_strarray; repo: Pgit_repository): Integer; cdecl; external libgit2_dll;

(**
 * Lookup a working tree by its name for a given repository
 *
 * @param out Output pointer to looked up worktree or `NULL`
 * @param repo The repository containing worktrees
 * @param name Name of the working tree to look up
 * @return 0 or an error code
 *)

function git_worktree_lookup(out_: PPgit_worktree; repo: Pgit_repository; name_: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Open a worktree of a given repository
 *
 * If a repository is not the main tree but a worktree, this
 * function will look up the worktree inside the parent
 * repository and create a new `git_worktree` structure.
 *
 * @param out Out-pointer for the newly allocated worktree
 * @param repo Repository to look up worktree for
 *)

function git_worktree_open_from_repository(out_: PPgit_worktree;
  repo: Pgit_repository): Integer; cdecl; external libgit2_dll;

(**
 * Free a previously allocated worktree
 *
 * @param wt worktree handle to close. If NULL nothing occurs.
 *)

procedure git_worktree_free(wt: Pgit_worktree); cdecl; external libgit2_dll;

(**
 * Check if worktree is valid
 *
 * A valid worktree requires both the git data structures inside
 * the linked parent repository and the linked working copy to be
 * present.
 *
 * @param wt Worktree to check
 * @return 0 when worktree is valid, error-code otherwise
 *)

function git_worktree_validate(wt: Pgit_worktree): Integer; cdecl; external libgit2_dll;

(**
 * Worktree add options structure
 *
 * Initialize with `GIT_WORKTREE_ADD_OPTIONS_INIT`. Alternatively, you can
 * use `git_worktree_add_options_init`.
 *
 *)

type
  git_worktree_add_options = record
    version: Cardinal;
    lock: Integer; (**< lock newly created worktree  *)
    ref: Pgit_reference; (**< reference to use for the new worktree HEAD  *)
  end;
  Pgit_worktree_add_options = ^git_worktree_add_options;

const
  GIT_WORKTREE_ADD_OPTIONS_VERSION = 1;
  //GIT_WORKTREE_ADD_OPTIONS_INIT = { GIT_WORKTREE_ADD_OPTIONS_VERSION , 0 , NULL };
  (**
   * Initialize git_worktree_add_options structure
   *
   * Initializes a `git_worktree_add_options` with default values. Equivalent to
   * creating an instance with `GIT_WORKTREE_ADD_OPTIONS_INIT`.
   *
   * @param opts The `git_worktree_add_options` struct to initialize.
   * @param version The struct version; pass `GIT_WORKTREE_ADD_OPTIONS_VERSION`.
   * @return Zero on success; -1 on failure.
   *)

function git_worktree_add_options_init(opts: Pgit_worktree_add_options; version: Cardinal): Integer; cdecl; external libgit2_dll;

(**
 * Add a new working tree
 *
 * Add a new working tree for the repository, that is create the
 * required data structures inside the repository and check out
 * the current HEAD at `path`
 *
 * @param out Output pointer containing new working tree
 * @param repo Repository to create working tree for
 * @param name Name of the working tree
 * @param path Path to create working tree at
 * @param opts Options to modify default behavior. May be NULL
 * @return 0 or an error code
 *)

function git_worktree_add(out_: PPgit_worktree; repo: Pgit_repository; name_, path: PAnsiChar;
  opts: Pgit_worktree_add_options): Integer; cdecl; external libgit2_dll;

(**
 * Lock worktree if not already locked
 *
 * Lock a worktree, optionally specifying a reason why the linked
 * working tree is being locked.
 *
 * @param wt Worktree to lock
 * @param reason Reason why the working tree is being locked
 * @return 0 on success, non-zero otherwise
 *)

function git_worktree_lock(wt: Pgit_worktree; reason: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Unlock a locked worktree
 *
 * @param wt Worktree to unlock
 * @return 0 on success, 1 if worktree was not locked, error-code
 *  otherwise
 *)

function git_worktree_unlock(wt: Pgit_worktree): Integer; cdecl; external libgit2_dll;

(**
 * Check if worktree is locked
 *
 * A worktree may be locked if the linked working tree is stored
 * on a portable device which is not available.
 *
 * @param reason Buffer to store reason in. If NULL no reason is stored.
 * @param wt Worktree to check
 * @return 0 when the working tree not locked, a value greater
 *  than zero if it is locked, less than zero if there was an
 *  error
 *)

function git_worktree_is_locked(reason: Pgit_buf; wt: Pgit_worktree): Integer; cdecl; external libgit2_dll;

(**
 * Retrieve the name of the worktree
 *
 * @param wt Worktree to get the name for
 * @return The worktree's name. The pointer returned is valid for the
 *  lifetime of the git_worktree
 *)

function git_worktree_name(wt: Pgit_worktree): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Retrieve the filesystem path for the worktree
 *
 * @param wt Worktree to get the path for
 * @return The worktree's filesystem path. The pointer returned
 *  is valid for the lifetime of the git_worktree.
 *)

function git_worktree_path(wt: Pgit_worktree): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Flags which can be passed to git_worktree_prune to alter its
 * behavior.
 *)

const
  (* Prune working tree even if working tree is valid  *)
  GIT_WORKTREE_PRUNE_VALID    = 1 shl 0;
  (* Prune working tree even if it is locked  *)
  GIT_WORKTREE_PRUNE_LOCKED   = 1 shl 1;
  (* Prune checked out working tree  *)
  GIT_WORKTREE_PRUNE_WORKING_TREE = 1 shl 2;
type
  git_worktree_prune_t = Integer;

  (**
   * Worktree prune options structure
   *
   * Initialize with `GIT_WORKTREE_PRUNE_OPTIONS_INIT`. Alternatively, you can
   * use `git_worktree_prune_options_init`.
   *
   *)

  git_worktree_prune_options = record
    version: Cardinal;
    (** A combination of `git_worktree_prune_t` *)
    flags: uint32_t;
  end;
  Pgit_worktree_prune_options = ^git_worktree_prune_options;

const
  GIT_WORKTREE_PRUNE_OPTIONS_VERSION = 1;
  //GIT_WORKTREE_PRUNE_OPTIONS_INIT = { GIT_WORKTREE_PRUNE_OPTIONS_VERSION , 0 };
  (**
   * Initialize git_worktree_prune_options structure
   *
   * Initializes a `git_worktree_prune_options` with default values. Equivalent to
   * creating an instance with `GIT_WORKTREE_PRUNE_OPTIONS_INIT`.
   *
   * @param opts The `git_worktree_prune_options` struct to initialize.
   * @param version The struct version; pass `GIT_WORKTREE_PRUNE_OPTIONS_VERSION`.
   * @return Zero on success; -1 on failure.
   *)

function git_worktree_prune_options_init(opts: Pgit_worktree_prune_options; version: Cardinal): Integer; cdecl; external libgit2_dll;

(**
 * Is the worktree prunable with the given options?
 *
 * A worktree is not prunable in the following scenarios:
 *
 * - the worktree is linking to a valid on-disk worktree. The
 *   `valid` member will cause this check to be ignored.
 * - the worktree is locked. The `locked` flag will cause this
 *   check to be ignored.
 *
 * If the worktree is not valid and not locked or if the above
 * flags have been passed in, this function will return a
 * positive value.
  *)
function git_worktree_is_prunable(wt: Pgit_worktree; opts: Pgit_worktree_prune_options): Integer; cdecl; external libgit2_dll;

(**
 * Prune working tree
 *
 * Prune the working tree, that is remove the git data
 * structures on disk. The repository will only be pruned of
 * `git_worktree_is_prunable` succeeds.
 *
 * @param wt Worktree to prune
 * @param opts Specifies which checks to override. See
 *        `git_worktree_is_prunable`. May be NULL
 * @return 0 or an error code
  *)

function git_worktree_prune(wt: Pgit_worktree; opts: Pgit_worktree_prune_options): Integer; cdecl; external libgit2_dll;

(** @}  *)



