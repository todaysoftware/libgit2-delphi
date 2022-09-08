(**
 * @file git2/pack.h
 * @brief Git pack management routines
 *
 * Packing objects
 * ---------------
 *
 * Creation of packfiles requires two steps:
 *
 * - First, insert all the objects you want to put into the packfile
 *   using `git_packbuilder_insert` and `git_packbuilder_insert_tree`.
 *   It's important to add the objects in recency order ("in the order
 *   that they are 'reachable' from head").
 *
 *   "ANY order will give you a working pack, ... [but it is] the thing
 *   that gives packs good locality. It keeps the objects close to the
 *   head (whether they are old or new, but they are _reachable_ from the
 *   head) at the head of the pack. So packs actually have absolutely
 *   _wonderful_ IO patterns." - Linus Torvalds
 *   git.git/Documentation/technical/pack-heuristics.txt
 *
 * - Second, use `git_packbuilder_write` or `git_packbuilder_foreach` to
 *   write the resulting packfile.
 *
 *   libgit2 will take care of the delta ordering and generation.
 *   `git_packbuilder_set_threads` can be used to adjust the number of
 *   threads used for the process.
 *
 * See tests/pack/packbuilder.c for an example.
 *
 * @ingroup Git
 * @{
 *)

(**
 * Stages that are reported by the packbuilder progress callback.
 *)

const
  GIT_PACKBUILDER_ADDING_OBJECTS = 0;
  GIT_PACKBUILDER_DELTAFICATION = 1;
type
  git_packbuilder_stage_t = Integer;

  (**
   * Initialize a new packbuilder
   *
   * @param out The new packbuilder object
   * @param repo The repository
   *
   * @return 0 or an error code
   *)

function git_packbuilder_new(out_: PPgit_packbuilder; repo: Pgit_repository): Integer; cdecl; external libgit2_dll;

(**
 * Set number of threads to spawn
 *
 * By default, libgit2 won't spawn any threads at all;
 * when set to 0, libgit2 will autodetect the number of
 * CPUs.
 *
 * @param pb The packbuilder
 * @param n Number of threads to spawn
 * @return number of actual threads to be used
 *)

function git_packbuilder_set_threads(pb: Pgit_packbuilder; n: Cardinal): Cardinal; cdecl; external libgit2_dll;

(**
 * Insert a single object
 *
 * For an optimal pack it's mandatory to insert objects in recency order,
 * commits followed by trees and blobs.
 *
 * @param pb The packbuilder
 * @param id The oid of the commit
 * @param name The name; might be NULL
 *
 * @return 0 or an error code
 *)

function git_packbuilder_insert(pb: Pgit_packbuilder; id: Pgit_oid; name_: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Insert a root tree object
 *
 * This will add the tree as well as all referenced trees and blobs.
 *
 * @param pb The packbuilder
 * @param id The oid of the root tree
 *
 * @return 0 or an error code
 *)

function git_packbuilder_insert_tree(pb: Pgit_packbuilder; id: Pgit_oid): Integer; cdecl; external libgit2_dll;

(**
 * Insert a commit object
 *
 * This will add a commit as well as the completed referenced tree.
 *
 * @param pb The packbuilder
 * @param id The oid of the commit
 *
 * @return 0 or an error code
 *)

function git_packbuilder_insert_commit(pb: Pgit_packbuilder; id: Pgit_oid): Integer; cdecl; external libgit2_dll;

(**
 * Insert objects as given by the walk
 *
 * Those commits and all objects they reference will be inserted into
 * the packbuilder.
 *
 * @param pb the packbuilder
 * @param walk the revwalk to use to fill the packbuilder
 *
 * @return 0 or an error code
 *)

function git_packbuilder_insert_walk(pb: Pgit_packbuilder; walk: Pgit_revwalk): Integer; cdecl; external libgit2_dll;

(**
 * Recursively insert an object and its referenced objects
 *
 * Insert the object as well as any object it references.
 *
 * @param pb the packbuilder
 * @param id the id of the root object to insert
 * @param name optional name for the object
 * @return 0 or an error code
 *)

function git_packbuilder_insert_recur(pb: Pgit_packbuilder; id: Pgit_oid; name_: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Write the contents of the packfile to an in-memory buffer
 *
 * The contents of the buffer will become a valid packfile, even though there
 * will be no attached index
 *
 * @param buf Buffer where to write the packfile
 * @param pb The packbuilder
 * @return 0 or an error code
 *)

function git_packbuilder_write_buf(buf: Pgit_buf; pb: Pgit_packbuilder): Integer; cdecl; external libgit2_dll;

(**
 * Write the new pack and corresponding index file to path.
 *
 * @param pb The packbuilder
 * @param path Path to the directory where the packfile and index should be stored, or NULL for default location
 * @param mode permissions to use creating a packfile or 0 for defaults
 * @param progress_cb function to call with progress information from the indexer (optional)
 * @param progress_cb_payload payload for the progress callback (optional)
 *
 * @return 0 or an error code
 *)

function git_packbuilder_write(pb: Pgit_packbuilder; path: PAnsiChar; mode: Cardinal;
  progress_cb: git_indexer_progress_cb; progress_cb_payload: Pointer): Integer; cdecl; external libgit2_dll;

{$IFNDEF GIT_DEPRECATE_HARD}
(**
 * Get the packfile's hash
 *
 * A packfile's name is derived from the sorted hashing of all object
 * names. This is only correct after the packfile has been written.
 *
 * @deprecated use git_packbuilder_name
 * @param pb The packbuilder object
 * @return 0 or an error code
*)

function git_packbuilder_hash(pb: Pgit_packbuilder): Pgit_oid; cdecl; external libgit2_dll;
{$ENDIF}

(**
 * Get the unique name for the resulting packfile.
 *
 * The packfile's name is derived from the packfile's content.
 * This is only correct after the packfile has been written.
 *
 * @param pb the packbuilder instance
 * @return a NUL terminated string for the packfile name
 *)
function git_packbuilder_name(pb: Pgit_packbuilder): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Callback used to iterate over packed objects
 *
 * @see git_packbuilder_foreach
 *
 * @param buf A pointer to the object's data
 * @param size The size of the underlying object
 * @param payload Payload passed to git_packbuilder_foreach
 * @return non-zero to terminate the iteration
 *)

type
  git_packbuilder_foreach_cb = function(buf: Pointer; size: size_t;
    payload: Pointer): Integer; cdecl;

  (**
   * Create the new pack and pass each object to the callback
   *
   * @param pb the packbuilder
   * @param cb the callback to call with each packed object's buffer
   * @param payload the callback's data
   * @return 0 or an error code
   *)

function git_packbuilder_foreach(pb: Pgit_packbuilder; cb: git_packbuilder_foreach_cb;
  payload: Pointer): Integer; cdecl; external libgit2_dll;

(**
 * Get the total number of objects the packbuilder will write out
 *
 * @param pb the packbuilder
 * @return the number of objects in the packfile
 *)

function git_packbuilder_object_count(pb: Pgit_packbuilder): size_t; cdecl; external libgit2_dll;

(**
 * Get the number of objects the packbuilder has already written out
 *
 * @param pb the packbuilder
 * @return the number of objects which have already been written
 *)

function git_packbuilder_written(pb: Pgit_packbuilder): size_t; cdecl; external libgit2_dll;

(** Packbuilder progress notification function  *)

type
  git_packbuilder_progress = function(stage: Integer; current, total: uint32_t; payload: Pointer): Integer; cdecl;

  (**
   * Set the callbacks for a packbuilder
   *
   * @param pb The packbuilder object
   * @param progress_cb Function to call with progress information during
   * pack building. Be aware that this is called inline with pack building
   * operations, so performance may be affected.
   * @param progress_cb_payload Payload for progress callback.
   * @return 0 or an error code
   *)

function git_packbuilder_set_callbacks(pb: Pgit_packbuilder; progress_cb: git_packbuilder_progress;
  progress_cb_payload: Pointer): Integer; cdecl; external libgit2_dll;

(**
 * Free the packbuilder and all associated data
 *
 * @param pb The packbuilder
 *)

procedure git_packbuilder_free(pb: Pgit_packbuilder); cdecl; external libgit2_dll;

(** @}  *)



