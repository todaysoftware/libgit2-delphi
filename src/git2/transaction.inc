(**
 * @file git2/transaction.h
 * @brief Git transactional reference routines
 * @defgroup git_transaction Git transactional reference routines
 * @ingroup Git
 * @{
 *)

(**
 * Create a new transaction object
 *
 * This does not lock anything, but sets up the transaction object to
 * know from which repository to lock.
 *
 * @param out the resulting transaction
 * @param repo the repository in which to lock
 * @return 0 or an error code
 *)

function git_transaction_new(out_: PPgit_transaction; repo: Pgit_repository): Integer; cdecl; external libgit2_dll;

(**
 * Lock a reference
 *
 * Lock the specified reference. This is the first step to updating a
 * reference.
 *
 * @param tx the transaction
 * @param refname the reference to lock
 * @return 0 or an error message
 *)

function git_transaction_lock_ref(tx: Pgit_transaction; refname: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Set the target of a reference
 *
 * Set the target of the specified reference. This reference must be
 * locked.
 *
 * @param tx the transaction
 * @param refname reference to update
 * @param target target to set the reference to
 * @param sig signature to use in the reflog; pass NULL to read the identity from the config
 * @param msg message to use in the reflog
 * @return 0, GIT_ENOTFOUND if the reference is not among the locked ones, or an error code
 *)

function git_transaction_set_target(tx: Pgit_transaction; refname: PAnsiChar; target: Pgit_oid;
  sig: Pgit_signature; msg: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Set the target of a reference
 *
 * Set the target of the specified reference. This reference must be
 * locked.
 *
 * @param tx the transaction
 * @param refname reference to update
 * @param target target to set the reference to
 * @param sig signature to use in the reflog; pass NULL to read the identity from the config
 * @param msg message to use in the reflog
 * @return 0, GIT_ENOTFOUND if the reference is not among the locked ones, or an error code
 *)

function git_transaction_set_symbolic_target(tx: Pgit_transaction; refname, target: PAnsiChar;
  sig: Pgit_signature; msg: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Set the reflog of a reference
 *
 * Set the specified reference's reflog. If this is combined with
 * setting the target, that update won't be written to the reflog.
 *
 * @param tx the transaction
 * @param refname the reference whose reflog to set
 * @param reflog the reflog as it should be written out
 * @return 0, GIT_ENOTFOUND if the reference is not among the locked ones, or an error code
 *)

function git_transaction_set_reflog(tx: Pgit_transaction; refname: PAnsiChar;
  reflog: Pgit_reflog): Integer; cdecl; external libgit2_dll;

(**
 * Remove a reference
 *
 * @param tx the transaction
 * @param refname the reference to remove
 * @return 0, GIT_ENOTFOUND if the reference is not among the locked ones, or an error code
 *)

function git_transaction_remove(tx: Pgit_transaction; refname: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Commit the changes from the transaction
 *
 * Perform the changes that have been queued. The updates will be made
 * one by one, and the first failure will stop the processing.
 *
 * @param tx the transaction
 * @return 0 or an error code
 *)

function git_transaction_commit(tx: Pgit_transaction): Integer; cdecl; external libgit2_dll;

(**
 * Free the resources allocated by this transaction
 *
 * If any references remain locked, they will be unlocked without any
 * changes made to them.
 *
 * @param tx the transaction
 *)

procedure git_transaction_free(tx: Pgit_transaction); cdecl; external libgit2_dll;

(** @}  *)


