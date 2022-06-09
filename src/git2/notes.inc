(**
 * @file git2/notes.h
 * @brief Git notes management routines
 * @defgroup git_note Git notes management routines
 * @ingroup Git
 * @{
*)

(**
 * Callback for git_note_foreach.
 *
 * Receives:
 * - blob_id: Oid of the blob containing the message
 * - annotated_object_id: Oid of the git object being annotated
 * - payload: Payload data passed to `git_note_foreach`
  *)

type
  git_note_foreach_cb = function(blob_id, annotated_object_id: Pgit_oid; payload: Pointer): Integer; cdecl;

  (**
   * note iterator
   *)

  git_iterator = record
  end;
  git_note_iterator = git_iterator;
  PPgit_note_iterator = ^Pgit_note_iterator;
  Pgit_note_iterator = ^git_note_iterator;

  (**
   * Creates a new iterator for notes
   *
   * The iterator must be freed manually by the user.
   *
   * @param out pointer to the iterator
   * @param repo repository where to look up the note
   * @param notes_ref canonical name of the reference to use (optional); defaults to
   *                  "refs/notes/commits"
   *
   * @return 0 or an error code
   *)

function git_note_iterator_new(out_: PPgit_note_iterator; repo: Pgit_repository;
  notes_ref: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Creates a new iterator for notes from a commit
 *
 * The iterator must be freed manually by the user.
 *
 * @param out pointer to the iterator
 * @param notes_commit a pointer to the notes commit object
 *
 * @return 0 or an error code
 *)

function git_note_commit_iterator_new(out_: PPgit_note_iterator; notes_commit: Pgit_commit): Integer; cdecl; external libgit2_dll;

(**
 * Frees an git_note_iterator
 *
 * @param it pointer to the iterator
 *)

procedure git_note_iterator_free(it: Pgit_note_iterator); cdecl; external libgit2_dll;

(**
 * Return the current item (note_id and annotated_id) and advance the iterator
 * internally to the next value
 *
 * @param note_id id of blob containing the message
 * @param annotated_id id of the git object being annotated
 * @param it pointer to the iterator
 *
 * @return 0 (no error), GIT_ITEROVER (iteration is done) or an error code
 *         (negative value)
 *)

function git_note_next(note_id, annotated_id: Pgit_oid; it: Pgit_note_iterator): Integer; cdecl; external libgit2_dll;

(**
 * Read the note for an object
 *
 * The note must be freed manually by the user.
 *
 * @param out pointer to the read note; NULL in case of error
 * @param repo repository where to look up the note
 * @param notes_ref canonical name of the reference to use (optional); defaults to
 *                  "refs/notes/commits"
 * @param oid OID of the git object to read the note from
 *
 * @return 0 or an error code
 *)

function git_note_read(out_: PPgit_note; repo: Pgit_repository; notes_ref: PAnsiChar;
  oid: Pgit_oid): Integer; cdecl; external libgit2_dll;

(**
 * Read the note for an object from a note commit
 *
 * The note must be freed manually by the user.
 *
 * @param out pointer to the read note; NULL in case of error
 * @param repo repository where to look up the note
 * @param notes_commit a pointer to the notes commit object
 * @param oid OID of the git object to read the note from
 *
 * @return 0 or an error code
 *)

function git_note_commit_read(out_: PPgit_note; repo: Pgit_repository; notes_commit: Pgit_commit;
  oid: Pgit_oid): Integer; cdecl; external libgit2_dll;

(**
 * Get the note author
 *
 * @param note the note
 * @return the author
 *)

function git_note_author(note: Pgit_note): Pgit_signature; cdecl; external libgit2_dll;

(**
 * Get the note committer
 *
 * @param note the note
 * @return the committer
 *)

function git_note_committer(note: Pgit_note): Pgit_signature; cdecl; external libgit2_dll;

(**
 * Get the note message
 *
 * @param note the note
 * @return the note message
 *)

function git_note_message(note: Pgit_note): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Get the note object's id
 *
 * @param note the note
 * @return the note object's id
 *)

function git_note_id(note: Pgit_note): Pgit_oid; cdecl; external libgit2_dll;

(**
 * Add a note for an object
 *
 * @param out pointer to store the OID (optional); NULL in case of error
 * @param repo repository where to store the note
 * @param notes_ref canonical name of the reference to use (optional);
 *					defaults to "refs/notes/commits"
 * @param author signature of the notes commit author
 * @param committer signature of the notes commit committer
 * @param oid OID of the git object to decorate
 * @param note Content of the note to add for object oid
 * @param force Overwrite existing note
 *
 * @return 0 or an error code
 *)

function git_note_create(out_: Pgit_oid; repo: Pgit_repository; notes_ref: PAnsiChar;
  author, committer: Pgit_signature; oid: Pgit_oid; note: PAnsiChar; force: Integer): Integer; cdecl; external libgit2_dll;

(**
 * Add a note for an object from a commit
 *
 * This function will create a notes commit for a given object,
 * the commit is a dangling commit, no reference is created.
 *
 * @param notes_commit_out pointer to store the commit (optional);
 *					NULL in case of error
 * @param notes_blob_out a point to the id of a note blob (optional)
 * @param repo repository where the note will live
 * @param parent Pointer to parent note
 *					or NULL if this shall start a new notes tree
 * @param author signature of the notes commit author
 * @param committer signature of the notes commit committer
 * @param oid OID of the git object to decorate
 * @param note Content of the note to add for object oid
 * @param allow_note_overwrite Overwrite existing note
 *
 * @return 0 or an error code
 *)

function git_note_commit_create(notes_commit_out, notes_blob_out: Pgit_oid; repo: Pgit_repository;
  parent: Pgit_commit; author, committer: Pgit_signature; oid: Pgit_oid; note: PAnsiChar;
  allow_note_overwrite: Integer): Integer; cdecl; external libgit2_dll;

(**
 * Remove the note for an object
 *
 * @param repo repository where the note lives
 * @param notes_ref canonical name of the reference to use (optional);
 *					defaults to "refs/notes/commits"
 * @param author signature of the notes commit author
 * @param committer signature of the notes commit committer
 * @param oid OID of the git object to remove the note from
 *
 * @return 0 or an error code
 *)

function git_note_remove(repo: Pgit_repository; notes_ref: PAnsiChar;
  author, committer: Pgit_signature; oid: Pgit_oid): Integer; cdecl; external libgit2_dll;

(**
 * Remove the note for an object
 *
 * @param notes_commit_out pointer to store the new notes commit (optional);
 *					NULL in case of error.
 *					When removing a note a new tree containing all notes
 *					sans the note to be removed is created and a new commit
 *					pointing to that tree is also created.
 *					In the case where the resulting tree is an empty tree
 *					a new commit pointing to this empty tree will be returned.
 * @param repo repository where the note lives
 * @param notes_commit a pointer to the notes commit object
 * @param author signature of the notes commit author
 * @param committer signature of the notes commit committer
 * @param oid OID of the git object to remove the note from
 *
 * @return 0 or an error code
 *)

function git_note_commit_remove(notes_commit_out: Pgit_oid; repo: Pgit_repository; notes_commit: Pgit_commit;
  author, committer: Pgit_signature; oid: Pgit_oid): Integer; cdecl; external libgit2_dll;

(**
 * Free a git_note object
 *
 * @param note git_note object
 *)

procedure git_note_free(note: Pgit_note); cdecl; external libgit2_dll;

(**
 * Get the default notes reference for a repository
 *
 * @param out buffer in which to store the name of the default notes reference
 * @param repo The Git repository
 *
 * @return 0 or an error code
 *)

function git_note_default_ref(out_: Pgit_buf; repo: Pgit_repository): Integer; cdecl; external libgit2_dll;

(**
 * Loop over all the notes within a specified namespace
 * and issue a callback for each one.
 *
 * @param repo Repository where to find the notes.
 *
 * @param notes_ref Reference to read from (optional); defaults to
 *        "refs/notes/commits".
 *
 * @param note_cb Callback to invoke per found annotation.  Return non-zero
 *        to stop looping.
 *
 * @param payload Extra parameter to callback function.
 *
 * @return 0 on success, non-zero callback return value, or error code
 *)

function git_note_foreach(repo: Pgit_repository; notes_ref: PAnsiChar; note_cb: git_note_foreach_cb;
  payload: Pointer): Integer; cdecl; external libgit2_dll;

(** @}  *)



