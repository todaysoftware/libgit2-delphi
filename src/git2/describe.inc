(**
 * @file git2/describe.h
 * @brief Git describing routines
 * @defgroup git_describe Git describing routines
 * @ingroup Git
 * @{
  *)

(**
 * Reference lookup strategy
 *
 * These behave like the --tags and --all options to git-describe,
 * namely they say to look for any reference in either refs/tags/ or
 * refs/ respectively.
  *)

const
  GIT_DESCRIBE_DEFAULT        = 0;
  GIT_DESCRIBE_TAGS           = 1;
  GIT_DESCRIBE_ALL            = 2;
type
  git_describe_strategy_t = Integer;

  (**
   * Describe options structure
   *
   * Initialize with `GIT_DESCRIBE_OPTIONS_INIT`. Alternatively, you can
   * use `git_describe_options_init`.
   *
   *)

  git_describe_options = record
    version: Cardinal;
    max_candidates_tags: Cardinal; (**< default: 10  *)
    describe_strategy: Cardinal; (**< default: GIT_DESCRIBE_DEFAULT  *)
    pattern: PAnsiChar;
    (**
     * When calculating the distance from the matching tag or
     * reference, only walk down the first-parent ancestry.
     *)
    only_follow_first_parent: Integer;
    (**
     * If no matching tag or reference is found, the describe
     * operation would normally fail. If this option is set, it
     * will instead fall back to showing the full id of the
     * commit.
     *)
    show_commit_oid_as_fallback: Integer;
  end;
  Pgit_describe_options = ^git_describe_options;

const
  GIT_DESCRIBE_DEFAULT_MAX_CANDIDATES_TAGS = 10;
  GIT_DESCRIBE_DEFAULT_ABBREVIATED_SIZE = 7;
  GIT_DESCRIBE_OPTIONS_VERSION = 1;
  //GIT_DESCRIBE_OPTIONS_INIT = { GIT_DESCRIBE_OPTIONS_VERSION , GIT_DESCRIBE_DEFAULT_MAX_CANDIDATES_TAGS , };
  (**
   * Initialize git_describe_options structure
   *
   * Initializes a `git_describe_options` with default values. Equivalent to creating
   * an instance with GIT_DESCRIBE_OPTIONS_INIT.
   *
   * @param opts The `git_describe_options` struct to initialize.
   * @param version The struct version; pass `GIT_DESCRIBE_OPTIONS_VERSION`.
   * @return Zero on success; -1 on failure.
   *)

function git_describe_options_init(opts: Pgit_describe_options; version: Cardinal): Integer; cdecl; external libgit2_dll;

(**
 * Describe format options structure
 *
 * Initialize with `GIT_DESCRIBE_FORMAT_OPTIONS_INIT`. Alternatively, you can
 * use `git_describe_format_options_init`.
 *
  *)

type
  git_describe_format_options = record
    version: Cardinal;
    (**
     * Size of the abbreviated commit id to use. This value is the
     * lower bound for the length of the abbreviated string. The
     * default is 7.
     *)
    abbreviated_size: Cardinal;
    (**
     * Set to use the long format even when a shorter name could be used.
     *)
    always_use_long_format: Integer;
    (**
     * If the workdir is dirty and this is set, this string will
     * be appended to the description string.
     *)
    dirty_suffix: PAnsiChar;
  end;
  Pgit_describe_format_options = ^git_describe_format_options;

const
  GIT_DESCRIBE_FORMAT_OPTIONS_VERSION = 1;
  //GIT_DESCRIBE_FORMAT_OPTIONS_INIT = { GIT_DESCRIBE_FORMAT_OPTIONS_VERSION , GIT_DESCRIBE_DEFAULT_ABBREVIATED_SIZE , };
  (**
   * Initialize git_describe_format_options structure
   *
   * Initializes a `git_describe_format_options` with default values. Equivalent to creating
   * an instance with GIT_DESCRIBE_FORMAT_OPTIONS_INIT.
   *
   * @param opts The `git_describe_format_options` struct to initialize.
   * @param version The struct version; pass `GIT_DESCRIBE_FORMAT_OPTIONS_VERSION`.
   * @return Zero on success; -1 on failure.
   *)

function git_describe_format_options_init(opts: Pgit_describe_format_options;
  version: Cardinal): Integer; cdecl; external libgit2_dll;

(**
 * A struct that stores the result of a describe operation.
 *)

type
  git_describe_result = record
  end;

  (**
   * Describe a commit
   *
   * Perform the describe operation on the given committish object.
   *
   * @param result pointer to store the result. You must free this once
   * you're done with it.
   * @param committish a committish to describe
   * @param opts the lookup options (or NULL for defaults)
   * @return 0 or an error code.
   *)

type
  PPgit_describe_result = ^Pgit_describe_result;
  Pgit_describe_result = ^git_describe_result;
function git_describe_commit(Result: PPgit_describe_result; committish: Pgit_object;
  opts: Pgit_describe_options): Integer; cdecl; external libgit2_dll;

(**
 * Describe a commit
 *
 * Perform the describe operation on the current commit and the
 * worktree. After performing describe on HEAD, a status is run and the
 * description is considered to be dirty if there are.
 *
 * @param out pointer to store the result. You must free this once
 * you're done with it.
 * @param repo the repository in which to perform the describe
 * @param opts the lookup options (or NULL for defaults)
 * @return 0 or an error code.
 *)

function git_describe_workdir(out_: PPgit_describe_result; repo: Pgit_repository;
  opts: Pgit_describe_options): Integer; cdecl; external libgit2_dll;

(**
 * Print the describe result to a buffer
 *
 * @param out The buffer to store the result
 * @param result the result from `git_describe_commit()` or
 * `git_describe_workdir()`.
 * @param opts the formatting options (or NULL for defaults)
 * @return 0 or an error code.
 *)

function git_describe_format(out_: Pgit_buf; Result: Pgit_describe_result;
  opts: Pgit_describe_format_options): Integer; cdecl; external libgit2_dll;

(**
 * Free the describe result.
 *
 * @param result The result to free.
 *)

procedure git_describe_result_free(Result: Pgit_describe_result); cdecl; external libgit2_dll;

(** @}  *)



