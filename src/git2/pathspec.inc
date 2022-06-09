(**
 * Compiled pathspec
 *)

type
  git_pathspec = record
  end;

  (**
   * List of filenames matching a pathspec
   *)

  git_pathspec_match_list = record
  end;

  (**
   * Options controlling how pathspec match should be executed
   *)

const
  GIT_PATHSPEC_DEFAULT        = 0;
  (**
   * GIT_PATHSPEC_IGNORE_CASE forces match to ignore case; otherwise
   * match will use native case sensitivity of platform filesystem
   *)
  GIT_PATHSPEC_IGNORE_CASE    = (1 shl 0);
  (**
   * GIT_PATHSPEC_USE_CASE forces case sensitive match; otherwise
   * match will use native case sensitivity of platform filesystem
   *)
  GIT_PATHSPEC_USE_CASE       = (1 shl 1);
  (**
   * GIT_PATHSPEC_NO_GLOB disables glob patterns and just uses simple
   * string comparison for matching
   *)
  GIT_PATHSPEC_NO_GLOB        = (1 shl 2);
  (**
   * GIT_PATHSPEC_NO_MATCH_ERROR means the match functions return error
   * code GIT_ENOTFOUND if no matches are found; otherwise no matches is
   * still success (return 0) but `git_pathspec_match_list_entrycount`
   * will indicate 0 matches.
   *)
  GIT_PATHSPEC_NO_MATCH_ERROR = (1 shl 3);
  (**
   * GIT_PATHSPEC_FIND_FAILURES means that the `git_pathspec_match_list`
   * should track which patterns matched which files so that at the end of
   * the match we can identify patterns that did not match any files.
   *)
  GIT_PATHSPEC_FIND_FAILURES  = (1 shl 4);
  (**
   * GIT_PATHSPEC_FAILURES_ONLY means that the `git_pathspec_match_list`
   * does not need to keep the actual matching filenames.  Use this to
   * just test if there were any matches at all or in combination with
   * GIT_PATHSPEC_FIND_FAILURES to validate a pathspec.
   *)
  GIT_PATHSPEC_FAILURES_ONLY  = (1 shl 5);
type
  git_pathspec_flag_t = Integer;

  (**
   * Compile a pathspec
   *
   * @param out Output of the compiled pathspec
   * @param pathspec A git_strarray of the paths to match
   * @return 0 on success, <0 on failure
   *)

type
  PPgit_pathspec = ^Pgit_pathspec;
  Pgit_pathspec = ^git_pathspec;
function git_pathspec_new(out_: PPgit_pathspec; pathspec: Pgit_strarray): Integer; cdecl; external libgit2_dll;

(**
 * Free a pathspec
 *
 * @param ps The compiled pathspec
 *)

procedure git_pathspec_free(ps: Pgit_pathspec); cdecl; external libgit2_dll;

(**
 * Try to match a path against a pathspec
 *
 * Unlike most of the other pathspec matching functions, this will not
 * fall back on the native case-sensitivity for your platform.  You must
 * explicitly pass flags to control case sensitivity or else this will
 * fall back on being case sensitive.
 *
 * @param ps The compiled pathspec
 * @param flags Combination of git_pathspec_flag_t options to control match
 * @param path The pathname to attempt to match
 * @return 1 is path matches spec, 0 if it does not
 *)

function git_pathspec_matches_path(ps: Pgit_pathspec; flags: uint32_t;
  path: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Match a pathspec against the working directory of a repository.
 *
 * This matches the pathspec against the current files in the working
 * directory of the repository.  It is an error to invoke this on a bare
 * repo.  This handles git ignores (i.e. ignored files will not be
 * considered to match the `pathspec` unless the file is tracked in the
 * index).
 *
 * If `out` is not NULL, this returns a `git_patchspec_match_list`.  That
 * contains the list of all matched filenames (unless you pass the
 * `GIT_PATHSPEC_FAILURES_ONLY` flag) and may also contain the list of
 * pathspecs with no match (if you used the `GIT_PATHSPEC_FIND_FAILURES`
 * flag).  You must call `git_pathspec_match_list_free()` on this object.
 *
 * @param out Output list of matches; pass NULL to just get return value
 * @param repo The repository in which to match; bare repo is an error
 * @param flags Combination of git_pathspec_flag_t options to control match
 * @param ps Pathspec to be matched
 * @return 0 on success, -1 on error, GIT_ENOTFOUND if no matches and
 *         the GIT_PATHSPEC_NO_MATCH_ERROR flag was given
 *)

type
  PPgit_pathspec_match_list = ^Pgit_pathspec_match_list;
  Pgit_pathspec_match_list = ^git_pathspec_match_list;
function git_pathspec_match_workdir(out_: PPgit_pathspec_match_list; repo: Pgit_repository;
  flags: uint32_t; ps: Pgit_pathspec): Integer; cdecl; external libgit2_dll;

(**
 * Match a pathspec against entries in an index.
 *
 * This matches the pathspec against the files in the repository index.
 *
 * NOTE: At the moment, the case sensitivity of this match is controlled
 * by the current case-sensitivity of the index object itself and the
 * USE_CASE and IGNORE_CASE flags will have no effect.  This behavior will
 * be corrected in a future release.
 *
 * If `out` is not NULL, this returns a `git_patchspec_match_list`.  That
 * contains the list of all matched filenames (unless you pass the
 * `GIT_PATHSPEC_FAILURES_ONLY` flag) and may also contain the list of
 * pathspecs with no match (if you used the `GIT_PATHSPEC_FIND_FAILURES`
 * flag).  You must call `git_pathspec_match_list_free()` on this object.
 *
 * @param out Output list of matches; pass NULL to just get return value
 * @param index The index to match against
 * @param flags Combination of git_pathspec_flag_t options to control match
 * @param ps Pathspec to be matched
 * @return 0 on success, -1 on error, GIT_ENOTFOUND if no matches and
 *         the GIT_PATHSPEC_NO_MATCH_ERROR flag is used
 *)

function git_pathspec_match_index(out_: PPgit_pathspec_match_list; index_: Pgit_index; flags: uint32_t;
  ps: Pgit_pathspec): Integer; cdecl; external libgit2_dll;

(**
 * Match a pathspec against files in a tree.
 *
 * This matches the pathspec against the files in the given tree.
 *
 * If `out` is not NULL, this returns a `git_patchspec_match_list`.  That
 * contains the list of all matched filenames (unless you pass the
 * `GIT_PATHSPEC_FAILURES_ONLY` flag) and may also contain the list of
 * pathspecs with no match (if you used the `GIT_PATHSPEC_FIND_FAILURES`
 * flag).  You must call `git_pathspec_match_list_free()` on this object.
 *
 * @param out Output list of matches; pass NULL to just get return value
 * @param tree The root-level tree to match against
 * @param flags Combination of git_pathspec_flag_t options to control match
 * @param ps Pathspec to be matched
 * @return 0 on success, -1 on error, GIT_ENOTFOUND if no matches and
 *         the GIT_PATHSPEC_NO_MATCH_ERROR flag is used
 *)

function git_pathspec_match_tree(out_: PPgit_pathspec_match_list; tree: Pgit_tree; flags: uint32_t;
  ps: Pgit_pathspec): Integer; cdecl; external libgit2_dll;

(**
 * Match a pathspec against files in a diff list.
 *
 * This matches the pathspec against the files in the given diff list.
 *
 * If `out` is not NULL, this returns a `git_patchspec_match_list`.  That
 * contains the list of all matched filenames (unless you pass the
 * `GIT_PATHSPEC_FAILURES_ONLY` flag) and may also contain the list of
 * pathspecs with no match (if you used the `GIT_PATHSPEC_FIND_FAILURES`
 * flag).  You must call `git_pathspec_match_list_free()` on this object.
 *
 * @param out Output list of matches; pass NULL to just get return value
 * @param diff A generated diff list
 * @param flags Combination of git_pathspec_flag_t options to control match
 * @param ps Pathspec to be matched
 * @return 0 on success, -1 on error, GIT_ENOTFOUND if no matches and
 *         the GIT_PATHSPEC_NO_MATCH_ERROR flag is used
 *)

function git_pathspec_match_diff(out_: PPgit_pathspec_match_list; diff: Pgit_diff; flags: uint32_t;
  ps: Pgit_pathspec): Integer; cdecl; external libgit2_dll;

(**
 * Free memory associates with a git_pathspec_match_list
 *
 * @param m The git_pathspec_match_list to be freed
 *)

procedure git_pathspec_match_list_free(m: Pgit_pathspec_match_list); cdecl; external libgit2_dll;

(**
 * Get the number of items in a match list.
 *
 * @param m The git_pathspec_match_list object
 * @return Number of items in match list
 *)

function git_pathspec_match_list_entrycount(m: Pgit_pathspec_match_list): size_t; cdecl; external libgit2_dll;

(**
 * Get a matching filename by position.
 *
 * This routine cannot be used if the match list was generated by
 * `git_pathspec_match_diff`.  If so, it will always return NULL.
 *
 * @param m The git_pathspec_match_list object
 * @param pos The index into the list
 * @return The filename of the match
 *)

function git_pathspec_match_list_entry(m: Pgit_pathspec_match_list; pos: size_t): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Get a matching diff delta by position.
 *
 * This routine can only be used if the match list was generated by
 * `git_pathspec_match_diff`.  Otherwise it will always return NULL.
 *
 * @param m The git_pathspec_match_list object
 * @param pos The index into the list
 * @return The filename of the match
 *)

function git_pathspec_match_list_diff_entry(m: Pgit_pathspec_match_list; pos: size_t): Pgit_diff_delta; cdecl; external libgit2_dll;

(**
 * Get the number of pathspec items that did not match.
 *
 * This will be zero unless you passed GIT_PATHSPEC_FIND_FAILURES when
 * generating the git_pathspec_match_list.
 *
 * @param m The git_pathspec_match_list object
 * @return Number of items in original pathspec that had no matches
 *)

function git_pathspec_match_list_failed_entrycount(m: Pgit_pathspec_match_list): size_t; cdecl; external libgit2_dll;

(**
 * Get an original pathspec string that had no matches.
 *
 * This will be return NULL for positions out of range.
 *
 * @param m The git_pathspec_match_list object
 * @param pos The index into the failed items
 * @return The pathspec pattern that didn't match anything
 *)

function git_pathspec_match_list_failed_entry(m: Pgit_pathspec_match_list; pos: size_t): PAnsiChar; cdecl; external libgit2_dll;



