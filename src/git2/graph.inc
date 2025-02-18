(**
 * @file git2/graph.h
 * @brief Graph traversal routines
 * @defgroup git_revwalk Git graph traversal routines
 * @ingroup Git
 * @{
  *)

(**
 * Count the number of unique commits between two commit objects
 *
 * There is no need for branches containing the commits to have any
 * upstream relationship, but it helps to think of one as a branch and
 * the other as its upstream, the `ahead` and `behind` values will be
 * what git would report for the branches.
 *
 * @param ahead number of unique from commits in `upstream`
 * @param behind number of unique from commits in `local`
 * @param repo the repository where the commits exist
 * @param local the commit for local
 * @param upstream the commit for upstream
 * @return 0 or an error code.
 *)

function git_graph_ahead_behind(ahead, behind: Psize_t; repo: Pgit_repository;
  local_, upstream: Pgit_oid): Integer; cdecl; external libgit2_dll;

(**
 * Determine if a commit is the descendant of another commit.
 *
 * Note that a commit is not considered a descendant of itself, in contrast
 * to `git merge-base --is-ancestor`.
 *
 * @param repo the repository where the commits exist
 * @param commit a previously loaded commit
 * @param ancestor a potential ancestor commit
 * @return 1 if the given commit is a descendant of the potential ancestor,
 * 0 if not, error code otherwise.
 *)

function git_graph_descendant_of(repo: Pgit_repository; commit, ancestor: Pgit_oid): Integer; cdecl; external libgit2_dll;

(**
 * Determine if a commit is reachable from any of a list of commits by
 * following parent edges.
 *
 * @param repo the repository where the commits exist
 * @param commit a previously loaded commit
 * @param descendant_array oids of the commits
 * @param length the number of commits in the provided `descendant_array`
 * @return 1 if the given commit is an ancestor of any of the given potential
 * descendants, 0 if not, error code otherwise.
 *)

function git_graph_reachable_from_any(repo: Pgit_repository; commit: Pgit_oid;
  descendant_array: Pgit_oid; Length: size_t): Integer; cdecl; external libgit2_dll;

(** @}  *)



