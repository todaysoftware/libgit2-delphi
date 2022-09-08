(**
 * @file git2/reflog.h
 * @brief Git reflog management routines
 * @defgroup git_reflog Git reflog management routines
 * @ingroup Git
 * @{
 *)

(**
 * Read the reflog for the given reference
 *
 * If there is no reflog file for the given
 * reference yet, an empty reflog object will
 * be returned.
 *
 * The reflog must be freed manually by using
 * git_reflog_free().
 *
 * @param out pointer to reflog
 * @param repo the repository
 * @param name reference to look up
 * @return 0 or an error code
 *)

function git_reflog_read(out_: PPgit_reflog; repo: Pgit_repository; name_: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Write an existing in-memory reflog object back to disk
 * using an atomic file lock.
 *
 * @param reflog an existing reflog object
 * @return 0 or an error code
 *)

function git_reflog_write(reflog: Pgit_reflog): Integer; cdecl; external libgit2_dll;

(**
 * Add a new entry to the in-memory reflog.
 *
 * `msg` is optional and can be NULL.
 *
 * @param reflog an existing reflog object
 * @param id the OID the reference is now pointing to
 * @param committer the signature of the committer
 * @param msg the reflog message
 * @return 0 or an error code
 *)

function git_reflog_append(reflog: Pgit_reflog; id: Pgit_oid; committer: Pgit_signature;
  msg: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Rename a reflog
 *
 * The reflog to be renamed is expected to already exist
 *
 * The new name will be checked for validity.
 * See `git_reference_create_symbolic()` for rules about valid names.
 *
 * @param repo the repository
 * @param old_name the old name of the reference
 * @param name the new name of the reference
 * @return 0 on success, GIT_EINVALIDSPEC or an error code
 *)

function git_reflog_rename(repo: Pgit_repository; old_name, name_: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Delete the reflog for the given reference
 *
 * @param repo the repository
 * @param name the reflog to delete
 * @return 0 or an error code
 *)

function git_reflog_delete(repo: Pgit_repository; name_: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Get the number of log entries in a reflog
 *
 * @param reflog the previously loaded reflog
 * @return the number of log entries
 *)

function git_reflog_entrycount(reflog: Pgit_reflog): size_t; cdecl; external libgit2_dll;

(**
 * Lookup an entry by its index
 *
 * Requesting the reflog entry with an index of 0 (zero) will
 * return the most recently created entry.
 *
 * @param reflog a previously loaded reflog
 * @param idx the position of the entry to lookup. Should be greater than or
 * equal to 0 (zero) and less than `git_reflog_entrycount()`.
 * @return the entry; NULL if not found
 *)

function git_reflog_entry_byindex(reflog: Pgit_reflog; idx: size_t): Pgit_reflog_entry; cdecl; external libgit2_dll;

(**
 * Remove an entry from the reflog by its index
 *
 * To ensure there's no gap in the log history, set `rewrite_previous_entry`
 * param value to 1. When deleting entry `n`, member old_oid of entry `n-1`
 * (if any) will be updated with the value of member new_oid of entry `n+1`.
 *
 * @param reflog a previously loaded reflog.
 *
 * @param idx the position of the entry to remove. Should be greater than or
 * equal to 0 (zero) and less than `git_reflog_entrycount()`.
 *
 * @param rewrite_previous_entry 1 to rewrite the history; 0 otherwise.
 *
 * @return 0 on success, GIT_ENOTFOUND if the entry doesn't exist
 * or an error code.
 *)

function git_reflog_drop(reflog: Pgit_reflog; idx: size_t; rewrite_previous_entry: Integer): Integer; cdecl; external libgit2_dll;

(**
 * Get the old oid
 *
 * @param entry a reflog entry
 * @return the old oid
 *)

function git_reflog_entry_id_old(entry: Pgit_reflog_entry): Pgit_oid; cdecl; external libgit2_dll;

(**
 * Get the new oid
 *
 * @param entry a reflog entry
 * @return the new oid at this time
 *)

function git_reflog_entry_id_new(entry: Pgit_reflog_entry): Pgit_oid; cdecl; external libgit2_dll;

(**
 * Get the committer of this entry
 *
 * @param entry a reflog entry
 * @return the committer
 *)

function git_reflog_entry_committer(entry: Pgit_reflog_entry): Pgit_signature; cdecl; external libgit2_dll;

(**
 * Get the log message
 *
 * @param entry a reflog entry
 * @return the log msg
 *)

function git_reflog_entry_message(entry: Pgit_reflog_entry): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Free the reflog
 *
 * @param reflog reflog to free
 *)

procedure git_reflog_free(reflog: Pgit_reflog); cdecl; external libgit2_dll;

(** @}  *)


