(**
 * @file git2/commit.h
 * @brief Git commit parsing, formatting routines
 * @defgroup git_commit Git commit parsing, formatting routines
 * @ingroup Git
 * @{
  *)

(**
 * Lookup a commit object from a repository.
 *
 * The returned object should be released with `git_commit_free` when no
 * longer needed.
 *
 * @param commit pointer to the looked up commit
 * @param repo the repo to use when locating the commit.
 * @param id identity of the commit to locate. If the object is
 *		an annotated tag it will be peeled back to the commit.
 * @return 0 or an error code
  *)

function git_commit_lookup(commit: PPgit_commit; repo: Pgit_repository;
  id: Pgit_oid): Integer; cdecl; external libgit2_dll;

(**
 * Lookup a commit object from a repository, given a prefix of its
 * identifier (short id).
 *
 * The returned object should be released with `git_commit_free` when no
 * longer needed.
 *
 * @see git_object_lookup_prefix
 *
 * @param commit pointer to the looked up commit
 * @param repo the repo to use when locating the commit.
 * @param id identity of the commit to locate. If the object is
 *		an annotated tag it will be peeled back to the commit.
 * @param len the length of the short identifier
 * @return 0 or an error code
  *)

function git_commit_lookup_prefix(commit: PPgit_commit; repo: Pgit_repository; id: Pgit_oid;
  len: size_t): Integer; cdecl; external libgit2_dll;

(**
 * Close an open commit
 *
 * This is a wrapper around git_object_free()
 *
 * IMPORTANT:
 * It *is* necessary to call this method when you stop
 * using a commit. Failure to do so will cause a memory leak.
 *
 * @param commit the commit to close
  *)

procedure git_commit_free(commit: Pgit_commit); cdecl; external libgit2_dll;

(**
 * Get the id of a commit.
 *
 * @param commit a previously loaded commit.
 * @return object identity for the commit.
  *)

function git_commit_id(commit: Pgit_commit): Pgit_oid; cdecl; external libgit2_dll;

(**
 * Get the repository that contains the commit.
 *
 * @param commit A previously loaded commit.
 * @return Repository that contains this commit.
  *)

function git_commit_owner(commit: Pgit_commit): Pgit_repository; cdecl; external libgit2_dll;

(**
 * Get the encoding for the message of a commit,
 * as a string representing a standard encoding name.
 *
 * The encoding may be NULL if the `encoding` header
 * in the commit is missing; in that case UTF-8 is assumed.
 *
 * @param commit a previously loaded commit.
 * @return NULL, or the encoding
  *)

function git_commit_message_encoding(commit: Pgit_commit): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Get the full message of a commit.
 *
 * The returned message will be slightly prettified by removing any
 * potential leading newlines.
 *
 * @param commit a previously loaded commit.
 * @return the message of a commit
  *)

function git_commit_message(commit: Pgit_commit): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Get the full raw message of a commit.
 *
 * @param commit a previously loaded commit.
 * @return the raw message of a commit
  *)

function git_commit_message_raw(commit: Pgit_commit): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Get the short "summary" of the git commit message.
 *
 * The returned message is the summary of the commit, comprising the
 * first paragraph of the message with whitespace trimmed and squashed.
 *
 * @param commit a previously loaded commit.
 * @return the summary of a commit or NULL on error
  *)

function git_commit_summary(commit: Pgit_commit): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Get the long "body" of the git commit message.
 *
 * The returned message is the body of the commit, comprising
 * everything but the first paragraph of the message. Leading and
 * trailing whitespaces are trimmed.
 *
 * @param commit a previously loaded commit.
 * @return the body of a commit or NULL when no the message only
 *   consists of a summary
  *)

function git_commit_body(commit: Pgit_commit): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Get the commit time (i.e. committer time) of a commit.
 *
 * @param commit a previously loaded commit.
 * @return the time of a commit
  *)

function git_commit_time(commit: Pgit_commit): git_time_t; cdecl; external libgit2_dll;

(**
 * Get the commit timezone offset (i.e. committer's preferred timezone) of a commit.
 *
 * @param commit a previously loaded commit.
 * @return positive or negative timezone offset, in minutes from UTC
  *)

function git_commit_time_offset(commit: Pgit_commit): Integer; cdecl; external libgit2_dll;

(**
 * Get the committer of a commit.
 *
 * @param commit a previously loaded commit.
 * @return the committer of a commit
  *)

function git_commit_committer(commit: Pgit_commit): Pgit_signature; cdecl; external libgit2_dll;

(**
 * Get the author of a commit.
 *
 * @param commit a previously loaded commit.
 * @return the author of a commit
  *)

function git_commit_author(commit: Pgit_commit): Pgit_signature; cdecl; external libgit2_dll;

(**
 * Get the committer of a commit, using the mailmap to map names and email
 * addresses to canonical real names and email addresses.
 *
 * Call `git_signature_free` to free the signature.
 *
 * @param out a pointer to store the resolved signature.
 * @param commit a previously loaded commit.
 * @param mailmap the mailmap to resolve with. (may be NULL)
 * @return 0 or an error code
  *)

function git_commit_committer_with_mailmap(out_: PPgit_signature; commit: Pgit_commit;
  mailmap: Pgit_mailmap): Integer; cdecl; external libgit2_dll;

(**
 * Get the author of a commit, using the mailmap to map names and email
 * addresses to canonical real names and email addresses.
 *
 * Call `git_signature_free` to free the signature.
 *
 * @param out a pointer to store the resolved signature.
 * @param commit a previously loaded commit.
 * @param mailmap the mailmap to resolve with. (may be NULL)
 * @return 0 or an error code
  *)

function git_commit_author_with_mailmap(out_: PPgit_signature; commit: Pgit_commit;
  mailmap: Pgit_mailmap): Integer; cdecl; external libgit2_dll;

(**
 * Get the full raw text of the commit header.
 *
 * @param commit a previously loaded commit
 * @return the header text of the commit
  *)

function git_commit_raw_header(commit: Pgit_commit): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Get the tree pointed to by a commit.
 *
 * @param tree_out pointer where to store the tree object
 * @param commit a previously loaded commit.
 * @return 0 or an error code
  *)

function git_commit_tree(tree_out: PPgit_tree; commit: Pgit_commit): Integer; cdecl; external libgit2_dll;

(**
 * Get the id of the tree pointed to by a commit. This differs from
 * `git_commit_tree` in that no attempts are made to fetch an object
 * from the ODB.
 *
 * @param commit a previously loaded commit.
 * @return the id of tree pointed to by commit.
  *)

function git_commit_tree_id(commit: Pgit_commit): Pgit_oid; cdecl; external libgit2_dll;

(**
 * Get the number of parents of this commit
 *
 * @param commit a previously loaded commit.
 * @return integer of count of parents
  *)

function git_commit_parentcount(commit: Pgit_commit): Cardinal; cdecl; external libgit2_dll;

(**
 * Get the specified parent of the commit.
 *
 * @param out Pointer where to store the parent commit
 * @param commit a previously loaded commit.
 * @param n the position of the parent (from 0 to `parentcount`)
 * @return 0 or an error code
  *)

function git_commit_parent(out_: PPgit_commit; commit: Pgit_commit; n: Cardinal): Integer; cdecl; external libgit2_dll;

(**
 * Get the oid of a specified parent for a commit. This is different from
 * `git_commit_parent`, which will attempt to load the parent commit from
 * the ODB.
 *
 * @param commit a previously loaded commit.
 * @param n the position of the parent (from 0 to `parentcount`)
 * @return the id of the parent, NULL on error.
  *)

function git_commit_parent_id(commit: Pgit_commit; n: Cardinal): Pgit_oid; cdecl; external libgit2_dll;

(**
 * Get the commit object that is the <n>th generation ancestor
 * of the named commit object, following only the first parents.
 * The returned commit has to be freed by the caller.
 *
 * Passing `0` as the generation number returns another instance of the
 * base commit itself.
 *
 * @param ancestor Pointer where to store the ancestor commit
 * @param commit a previously loaded commit.
 * @param n the requested generation
 * @return 0 on success; GIT_ENOTFOUND if no matching ancestor exists
 * or an error code
  *)

function git_commit_nth_gen_ancestor(ancestor: PPgit_commit; commit: Pgit_commit;
  n: Cardinal): Integer; cdecl; external libgit2_dll;

(**
 * Get an arbitrary header field
 *
 * @param out the buffer to fill; existing content will be
 * overwritten
 * @param commit the commit to look in
 * @param field the header field to return
 * @return 0 on succeess, GIT_ENOTFOUND if the field does not exist,
 * or an error code
  *)

function git_commit_header_field(out_: Pgit_buf; commit: Pgit_commit; field: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Extract the signature from a commit
 *
 * If the id is not for a commit, the error class will be
 * `GIT_ERROR_INVALID`. If the commit does not have a signature, the
 * error class will be `GIT_ERROR_OBJECT`.
 *
 * @param signature the signature block; existing content will be
 * overwritten
 * @param signed_data signed data; this is the commit contents minus the signature block;
 * existing content will be overwritten
 * @param repo the repository in which the commit exists
 * @param commit_id the commit from which to extract the data
 * @param field the name of the header field containing the signature
 * block; pass `NULL` to extract the default 'gpgsig'
 * @return 0 on success, GIT_ENOTFOUND if the id is not for a commit
 * or the commit does not have a signature.
  *)

function git_commit_extract_signature(signature, signed_data: Pgit_buf; repo: Pgit_repository;
  commit_id: Pgit_oid; field: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Create new commit in the repository from a list of `git_object` pointers
 *
 * The message will **not** be cleaned up automatically. You can do that
 * with the `git_message_prettify()` function.
 *
 * @param id Pointer in which to store the OID of the newly created commit
 *
 * @param repo Repository where to store the commit
 *
 * @param update_ref If not NULL, name of the reference that
 *	will be updated to point to this commit. If the reference
 *	is not direct, it will be resolved to a direct reference.
 *	Use "HEAD" to update the HEAD of the current branch and
 *	make it point to this commit. If the reference doesn't
 *	exist yet, it will be created. If it does exist, the first
 *	parent must be the tip of this branch.
 *
 * @param author Signature with author and author time of commit
 *
 * @param committer Signature with committer and * commit time of commit
 *
 * @param message_encoding The encoding for the message in the
 *  commit, represented with a standard encoding name.
 *  E.g. "UTF-8". If NULL, no encoding header is written and
 *  UTF-8 is assumed.
 *
 * @param message Full message for this commit
 *
 * @param tree An instance of a `git_tree` object that will
 *  be used as the tree for the commit. This tree object must
 *  also be owned by the given `repo`.
 *
 * @param parent_count Number of parents for this commit
 *
 * @param parents Array of `parent_count` pointers to `git_commit`
 *  objects that will be used as the parents for this commit. This
 *  array may be NULL if `parent_count` is 0 (root commit). All the
 *  given commits must be owned by the `repo`.
 *
 * @return 0 or an error code
 *	The created commit will be written to the Object Database and
 *	the given reference will be updated to point to it
  *)

function git_commit_create(id: Pgit_oid; repo: Pgit_repository; update_ref: PAnsiChar;
  author, committer: Pgit_signature; message_encoding, message: PAnsiChar; tree: Pgit_tree;
  parent_count: size_t; parents: PPgit_commit): Integer; cdecl; external libgit2_dll;

(**
 * Create new commit in the repository using a variable argument list.
 *
 * The message will **not** be cleaned up automatically. You can do that
 * with the `git_message_prettify()` function.
 *
 * The parents for the commit are specified as a variable list of pointers
 * to `const git_commit *`. Note that this is a convenience method which may
 * not be safe to export for certain languages or compilers
 *
 * All other parameters remain the same as `git_commit_create()`.
 *
 * @see git_commit_create
  *)

function git_commit_create_v(id: Pgit_oid; repo: Pgit_repository; update_ref: PAnsiChar;
  author, committer: Pgit_signature; message_encoding, message: PAnsiChar; tree:
  Pgit_tree; parent_count: size_t): Integer; cdecl; varargs; external libgit2_dll;

type
  git_commit_create_options = record
    version: Cardinal;

    (**
     * Flags for creating the commit.
     *
     * If `allow_empty_commit` is specified, a commit with no changes
     * from the prior commit (and "empty" commit) is allowed. Otherwise,
     * commit creation will be stopped.
     *)
    flags: Cardinal;

    (** The commit author, or NULL for the default. *)
    author: Pgit_signature;

    (** The committer, or NULL for the default. *)
    committer: Pgit_signature;

    (** Encoding for the commit message; leave NULL for default. *)
    message_encoding: PAnsiChar;
  end;
  Pgit_commit_create_options = ^git_commit_create_options;

const
  GIT_COMMIT_ALLOW_EMPTY      = (1 shl 0);

  GIT_COMMIT_CREATE_OPTIONS_VERSION = 1;
  //GIT_COMMIT_CREATE_OPTIONS_INIT { GIT_COMMIT_CREATE_OPTIONS_VERSION }

(**
 * Commits the staged changes in the repository; this is a near analog to
 * `git commit -m message`.
 *
 * By default, empty commits are not allowed.
 *
 * @param id pointer to store the new commit's object id
 * @param repo repository to commit changes in
 * @param message the commit message
 * @param opts options for creating the commit
 * @return 0 on success, GIT_EUNCHANGED if there were no changes to commit, or an error code
 *)
function git_commit_create_from_stage(id: Pgit_oid; repo: Pgit_repository; message: PAnsiChar;
  opts: Pgit_commit_create_options): Integer; cdecl; external libgit2_dll;

(**
 * Amend an existing commit by replacing only non-NULL values.
 *
 * This creates a new commit that is exactly the same as the old commit,
 * except that any non-NULL values will be updated.  The new commit has
 * the same parents as the old commit.
 *
 * The `update_ref` value works as in the regular `git_commit_create()`,
 * updating the ref to point to the newly rewritten commit.  If you want
 * to amend a commit that is not currently the tip of the branch and then
 * rewrite the following commits to reach a ref, pass this as NULL and
 * update the rest of the commit chain and ref separately.
 *
 * Unlike `git_commit_create()`, the `author`, `committer`, `message`,
 * `message_encoding`, and `tree` parameters can be NULL in which case this
 * will use the values from the original `commit_to_amend`.
 *
 * All parameters have the same meanings as in `git_commit_create()`.
 *
 * @see git_commit_create
  *)

function git_commit_amend(id: Pgit_oid; commit_to_amend: Pgit_commit; update_ref: PAnsiChar;
  author, committer: Pgit_signature; message_encoding, message: PAnsiChar;
  tree: Pgit_tree): Integer; cdecl; external libgit2_dll;

(**
 * Create a commit and write it into a buffer
 *
 * Create a commit as with `git_commit_create()` but instead of
 * writing it to the objectdb, write the contents of the object into a
 * buffer.
 *
 * @param out the buffer into which to write the commit object content
 *
 * @param repo Repository where the referenced tree and parents live
 *
 * @param author Signature with author and author time of commit
 *
 * @param committer Signature with committer and * commit time of commit
 *
 * @param message_encoding The encoding for the message in the
 *  commit, represented with a standard encoding name.
 *  E.g. "UTF-8". If NULL, no encoding header is written and
 *  UTF-8 is assumed.
 *
 * @param message Full message for this commit
 *
 * @param tree An instance of a `git_tree` object that will
 *  be used as the tree for the commit. This tree object must
 *  also be owned by the given `repo`.
 *
 * @param parent_count Number of parents for this commit
 *
 * @param parents Array of `parent_count` pointers to `git_commit`
 *  objects that will be used as the parents for this commit. This
 *  array may be NULL if `parent_count` is 0 (root commit). All the
 *  given commits must be owned by the `repo`.
 *
 * @return 0 or an error code
  *)

function git_commit_create_buffer(out_: Pgit_buf; repo: Pgit_repository;
  author, committer: Pgit_signature; message_encoding, message: PAnsiChar; tree: Pgit_tree;
  parent_count: size_t; parents: PPgit_commit): Integer; cdecl; external libgit2_dll;

(**
 * Create a commit object from the given buffer and signature
 *
 * Given the unsigned commit object's contents, its signature and the
 * header field in which to store the signature, attach the signature
 * to the commit and write it into the given repository.
 *
 * @param out the resulting commit id
 * @param repo the repository to create the commit in.
 * @param commit_content the content of the unsigned commit object
 * @param signature the signature to add to the commit. Leave `NULL`
 * to create a commit without adding a signature field.
 * @param signature_field which header field should contain this
 * signature. Leave `NULL` for the default of "gpgsig"
 * @return 0 or an error code
  *)

function git_commit_create_with_signature(out_: Pgit_oid; repo: Pgit_repository;
  commit_content, signature, signature_field: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Create an in-memory copy of a commit. The copy must be explicitly
 * free'd or it will leak.
 *
 * @param out Pointer to store the copy of the commit
 * @param source Original commit to copy
 * @return 0
  *)

function git_commit_dup(out_: PPgit_commit; source: Pgit_commit): Integer; cdecl; external libgit2_dll;

(**
 * Commit creation callback: used when a function is going to create
 * commits (for example, in `git_rebase_commit`) to allow callers to
 * override the commit creation behavior.  For example, users may
 * wish to sign commits by providing this information to
 * `git_commit_create_buffer`, signing that buffer, then calling
 * `git_commit_create_with_signature`.  The resultant commit id
 * should be set in the `out` object id parameter.
 *
 * @param out pointer that this callback will populate with the object
 *            id of the commit that is created
 * @param author the author name and time of the commit
 * @param committer the committer name and time of the commit
 * @param message_encoding the encoding of the given message, or NULL
 *                         to assume UTF8
 * @param message the commit message
 * @param tree the tree to be committed
 * @param parent_count the number of parents for this commit
 * @param parents the commit parents
 * @param payload the payload pointer in the rebase options
 * @return 0 if this callback has created the commit and populated the out
 *         parameter, GIT_PASSTHROUGH if the callback has not created a
 *         commit and wants the calling function to create the commit as
 *         if no callback had been specified, any other value to stop
 *         and return a failure
 *)
type
  git_commit_create_cb = function(out_: Pgit_oid; author: Pgit_signature; committer: Pgit_signature;
    message_encoding: PAnsiChar; message: PAnsiChar; tree: Pgit_tree; parent_count: size_t; parents: PPgit_commit;
    payload: Pointer): Integer; cdecl;

  (** An array of commits returned from the library *)
type
  git_commitarray = record
    commits: PPgit_commit;
    Count: size_t;
  end;
  Pgit_commitarray = ^git_commitarray;

  (**
   * Free the commits contained in a commit array.  This method should
   * be called on `git_commitarray` objects that were provided by the
   * library.  Not doing so will result in a memory leak.
   *
   * This does not free the `git_commitarray` itself, since the library
   * will never allocate that object directly itself.
   *
   * @param array The git_commitarray that contains commits to free
   *)
procedure git_commitarray_dispose(array_: Pgit_commitarray); cdecl; external libgit2_dll;

(** @}  *)

