(**
 * @file git2/refdb.h
 * @brief Git custom refs backend functions
 * @defgroup git_refdb Git custom refs backend API
 * @ingroup Git
 * @{
 *)

(**
 * Create a new reference database with no backends.
 *
 * Before the Ref DB can be used for read/writing, a custom database
 * backend must be manually set using `git_refdb_set_backend()`
 *
 * @param out location to store the database pointer, if opened.
 *			Set to NULL if the open failed.
 * @param repo the repository
 * @return 0 or an error code
 *)

function git_refdb_new(out_: PPgit_refdb; repo: Pgit_repository): Integer; cdecl; external libgit2_dll;

(**
 * Create a new reference database and automatically add
 * the default backends:
 *
 *  - git_refdb_dir: read and write loose and packed refs
 *      from disk, assuming the repository dir as the folder
 *
 * @param out location to store the database pointer, if opened.
 *			Set to NULL if the open failed.
 * @param repo the repository
 * @return 0 or an error code
 *)

function git_refdb_open(out_: PPgit_refdb; repo: Pgit_repository): Integer; cdecl; external libgit2_dll;

(**
 * Suggests that the given refdb compress or optimize its references.
 * This mechanism is implementation specific.  For on-disk reference
 * databases, for example, this may pack all loose references.
 *)

function git_refdb_compress(refdb: Pgit_refdb): Integer; cdecl; external libgit2_dll;

(**
 * Close an open reference database.
 *
 * @param refdb reference database pointer or NULL
 *)

procedure git_refdb_free(refdb: Pgit_refdb); cdecl; external libgit2_dll;

(** @}  *)

