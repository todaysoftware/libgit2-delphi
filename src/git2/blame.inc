(**
 * @file git2/blame.h
 * @brief Git blame routines
 * @defgroup git_blame Git blame routines
 * @ingroup Git
 * @{
  *)

(**
 * Flags for indicating option behavior for git_blame APIs.
  *)

const
  (** Normal blame, the default  *)
  GIT_BLAME_NORMAL            = 0;
  (**
   * Track lines that have moved within a file (like `git blame -M`).
   *
   * This is not yet implemented and reserved for future use.
   *)
  GIT_BLAME_TRACK_COPIES_SAME_FILE = (1 shl 0);
  (**
   * Track lines that have moved across files in the same commit
   * (like `git blame -C`).
   *
   * This is not yet implemented and reserved for future use.
   *)
  GIT_BLAME_TRACK_COPIES_SAME_COMMIT_MOVES = (1 shl 1);
  (**
   * Track lines that have been copied from another file that exists
   * in the same commit (like `git blame -CC`).  Implies SAME_FILE.
   *
   * This is not yet implemented and reserved for future use.
   *)
  GIT_BLAME_TRACK_COPIES_SAME_COMMIT_COPIES = (1 shl 2);
  (**
   * Track lines that have been copied from another file that exists in
   * *any* commit (like `git blame -CCC`).  Implies SAME_COMMIT_COPIES.
   *
   * This is not yet implemented and reserved for future use.
   *)
  GIT_BLAME_TRACK_COPIES_ANY_COMMIT_COPIES = (1 shl 3);
  (**
   * Restrict the search of commits to those reachable following only
   * the first parents.
   *)
  GIT_BLAME_FIRST_PARENT      = (1 shl 4);
  (**
   * Use mailmap file to map author and committer names and email
   * addresses to canonical real names and email addresses. The
   * mailmap will be read from the working directory, or HEAD in a
   * bare repository.
   *)
  GIT_BLAME_USE_MAILMAP       = (1 shl 5);
  (** Ignore whitespace differences  *)
  GIT_BLAME_IGNORE_WHITESPACE = (1 shl 6);

type
  git_blame_flag_t = Integer;

  (**
 * Blame options structure
 *
 * Initialize with `GIT_BLAME_OPTIONS_INIT`. Alternatively, you can
 * use `git_blame_options_init`.
 *
  *)

  git_blame_options = record
    version: Cardinal;
    (** A combination of `git_blame_flag_t`  *)
    flags: uint32_t;
    (**
     * The lower bound on the number of alphanumeric characters that
     * must be detected as moving/copying within a file for it to
     * associate those lines with the parent commit. The default value
     * is 20.
     *
     * This value only takes effect if any of the `GIT_BLAME_TRACK_COPIES_*`
     * flags are specified.
     *)
    min_match_characters: uint16_t;
    (** The id of the newest commit to consider. The default is HEAD.  *)
    newest_commit: git_oid;
    (**
     * The id of the oldest commit to consider.
     * The default is the first commit encountered with a NULL parent.
     *)
    oldest_commit: git_oid;
    (**
     * The first line in the file to blame.
     * The default is 1 (line numbers start with 1).
     *)
    min_line: size_t;
    (**
     * The last line in the file to blame.
     * The default is the last line of the file.
     *)
    max_line: size_t;
  end;
  Pgit_blame_options = ^git_blame_options;

const
  GIT_BLAME_OPTIONS_VERSION   = 1;
  //GIT_BLAME_OPTIONS_INIT = { GIT_BLAME_OPTIONS_VERSION };
  (**
 * Initialize git_blame_options structure
 *
 * Initializes a `git_blame_options` with default values. Equivalent to creating
 * an instance with GIT_BLAME_OPTIONS_INIT.
 *
 * @param opts The `git_blame_options` struct to initialize.
 * @param version The struct version; pass `GIT_BLAME_OPTIONS_VERSION`.
 * @return Zero on success; -1 on failure.
  *)

function git_blame_options_init(opts: Pgit_blame_options; version: Cardinal): Integer; cdecl; external libgit2_dll;

(**
 * Structure that represents a blame hunk.
 *)

type
  git_blame_hunk = record
    (**
     * The number of lines in this hunk.
     *)
    lines_in_hunk: size_t;
    (**
     * The OID of the commit where this line was last changed.
     *)
    final_commit_id: git_oid;
    (**
     * The 1-based line number where this hunk begins, in the final version
     * of the file.
     *)
    final_start_line_number: size_t;
    (**
     * The author of `final_commit_id`. If `GIT_BLAME_USE_MAILMAP` has been
     * specified, it will contain the canonical real name and email address.
     *)
    final_signature: Pgit_signature;
    (**
     * The OID of the commit where this hunk was found.
     * This will usually be the same as `final_commit_id`, except when
     * `GIT_BLAME_TRACK_COPIES_ANY_COMMIT_COPIES` has been specified.
     *)
    orig_commit_id: git_oid;
    (**
     * The path to the file where this hunk originated, as of the commit
     * specified by `orig_commit_id`.
     *)
    orig_path: PAnsiChar;
    (**
     * The 1-based line number where this hunk begins in the file named by
     * `orig_path` in the commit specified by `orig_commit_id`.
     *)
    orig_start_line_number: size_t;
    (**
     * The author of `orig_commit_id`. If `GIT_BLAME_USE_MAILMAP` has been
     * specified, it will contain the canonical real name and email address.
     *)
    orig_signature: Pgit_signature;
    (**
     * The 1 iff the hunk has been tracked to a boundary commit (the root,
     * or the commit specified in git_blame_options.oldest_commit)
     *)
    boundary: AnsiChar;
  end;

  (** Opaque structure to hold blame results  *)

  git_blame = record
  end;

  (**
 * Gets the number of hunks that exist in the blame structure.
  *)

type
  Pgit_blame = ^git_blame;

function git_blame_get_hunk_count(blame: Pgit_blame): uint32_t; cdecl; external libgit2_dll;

(**
 * Gets the blame hunk at the given index.
 *
 * @param blame the blame structure to query
 * @param index index of the hunk to retrieve
 * @return the hunk at the given index, or NULL on error
  *)

type
  Pgit_blame_hunk = ^git_blame_hunk;

function git_blame_get_hunk_byindex(blame: Pgit_blame; index_: uint32_t): Pgit_blame_hunk; cdecl; external libgit2_dll;

(**
 * Gets the hunk that relates to the given line number in the newest commit.
 *
 * @param blame the blame structure to query
 * @param lineno the (1-based) line number to find a hunk for
 * @return the hunk that contains the given line, or NULL on error
  *)

function git_blame_get_hunk_byline(blame: Pgit_blame; lineno: size_t): Pgit_blame_hunk; cdecl; external libgit2_dll;

(**
 * Get the blame for a single file.
 *
 * @param out pointer that will receive the blame object
 * @param repo repository whose history is to be walked
 * @param path path to file to consider
 * @param options options for the blame operation.  If NULL, this is treated as
 *                though GIT_BLAME_OPTIONS_INIT were passed.
 * @return 0 on success, or an error code. (use git_error_last for information
 *         about the error.)
  *)

type
  PPgit_blame = ^Pgit_blame;

function git_blame_file(out_: PPgit_blame; repo: Pgit_repository; path: PAnsiChar;
  options: Pgit_blame_options): Integer; cdecl; external libgit2_dll;

(**
 * Get blame data for a file that has been modified in memory. The `reference`
 * parameter is a pre-calculated blame for the in-odb history of the file. This
 * means that once a file blame is completed (which can be expensive), updating
 * the buffer blame is very fast.
 *
 * Lines that differ between the buffer and the committed version are marked as
 * having a zero OID for their final_commit_id.
 *
 * @param out pointer that will receive the resulting blame data
 * @param reference cached blame from the history of the file (usually the output
 *                  from git_blame_file)
 * @param buffer the (possibly) modified contents of the file
 * @param buffer_len number of valid bytes in the buffer
 * @return 0 on success, or an error code. (use git_error_last for information
 *         about the error)
  *)

function git_blame_buffer(out_: PPgit_blame; reference: Pgit_blame; buffer: PAnsiChar;
  buffer_len: size_t): Integer; cdecl; external libgit2_dll;

(**
 * Free memory allocated by git_blame_file or git_blame_buffer.
 *
 * @param blame the blame structure to free
  *)

procedure git_blame_free(blame: Pgit_blame); cdecl; external libgit2_dll;

(** @}  *)



