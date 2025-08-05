(**
 * @file git2/indexer.h
 * @brief Packfile indexing
 * @ingroup Git
 * @{
 *
 * Indexing is the operation of taking a packfile - which is simply a
 * collection of unordered commits - and producing an "index" so that
 * one can lookup a commit in the packfile by object ID.
 *)

(** A git indexer object  *)

type
  git_indexer = record
  end;
  PPgit_indexer = ^Pgit_indexer;
  Pgit_indexer = ^git_indexer;

  (**
   * This structure is used to provide callers information about the
   * progress of indexing a packfile, either directly or part of a
   * fetch or clone that downloads a packfile.
   *)

  git_indexer_progress = record
    (** number of objects in the packfile being indexed  *)
    total_objects: Cardinal;
    (** received objects that have been hashed  *)
    indexed_objects: Cardinal;
    (** received_objects: objects which have been downloaded  *)
    received_objects: Cardinal;
    (**
    * locally-available objects that have been injected in order
    * to fix a thin pack
    *)
    local_objects: Cardinal;
    (** number of deltas in the packfile being indexed  *)
    total_deltas: Cardinal;
    (** received deltas that have been indexed  *)
    indexed_deltas: Cardinal;
    (** size of the packfile received up to now  *)
    received_bytes: size_t;
  end;
  Pgit_indexer_progress = ^git_indexer_progress;

  (**
   * Type for progress callbacks during indexing.  Return a value less
   * than zero to cancel the indexing or download.
   *
   * @param stats Structure containing information about the state of the tran    sfer
   * @param payload Payload provided by caller
   *)

type
  git_indexer_progress_cb = function(stats: Pgit_indexer_progress; payload: Pointer): Integer; cdecl;

  (**
   * Options for indexer configuration
   *)

type
  git_indexer_options = record
    version: Cardinal;
    {$IFDEF GIT_EXPERIMENTAL_SHA256}
    (** permissions to use creating packfile or 0 for defaults *)
    mode: Cardinal;
  	(** the type of object ids in the packfile or 0 for SHA1 *)
	  oid_type: git_oid_t;
    (**
     * object database from which to read base objects when
     * fixing thin packs. This can be NULL if there are no thin
     * packs; if a thin pack is encountered, an error will be
     * returned if there are bases missing.
     *)
    odb: Pgit_odb;
    {$ENDIF}
    (** progress_cb function to call with progress information  *)
    progress_cb: git_indexer_progress_cb;
    (** progress_cb_payload payload for the progress callback  *)
    progress_cb_payload: Pointer;
    (** Do connectivity checks for the received pack  *)
    verify: Byte;
  end;
  Pgit_indexer_options = ^git_indexer_options;

const
  (** Current version for the `git_indexer_options` structure *)
  GIT_INDEXER_OPTIONS_VERSION = 1;
  (** Static constructor for `git_indexer_options` *)
  //GIT_INDEXER_OPTIONS_INIT = { GIT_INDEXER_OPTIONS_VERSION };
  (**
   * Initializes a `git_indexer_options` with default values. Equivalent to
   * creating an instance with GIT_INDEXER_OPTIONS_INIT.
   *
   * @param opts the `git_indexer_options` struct to initialize.
   * @param version Version of struct; pass `GIT_INDEXER_OPTIONS_VERSION`
   * @return Zero on success; -1 on failure.
   *)

function git_indexer_options_init(opts: Pgit_indexer_options; version: Cardinal): Integer; cdecl; external libgit2_dll {$IFDEF LIBGIT2_DLL_DELAY_LOAD}delayed{$ENDIF};

{$IFDEF GIT_EXPERIMENTAL_SHA256}
(**
 * Create a new indexer instance
 *
 * @param out where to store the indexer instance
 * @param path to the directory where the packfile should be stored
 * @param opts the options to create the indexer with
 * @return 0 or an error code.
 *)
function git_indexer_new(out_: PPgit_indexer; path: PAnsiChar;
  opts: Pgit_indexer_options): Integer; cdecl; external libgit2_dll {$IFDEF LIBGIT2_DLL_DELAY_LOAD}delayed{$ENDIF};
{$ELSE}
(**
 * Create a new indexer instance
 *
 * @param out where to store the indexer instance
 * @param path to the directory where the packfile should be stored
 * @param mode permissions to use creating packfile or 0 for defaults
 * @param odb object database from which to read base objects when
 * fixing thin packs. Pass NULL if no thin pack is expected (an error
 * will be returned if there are bases missing)
 * @param opts Optional structure containing additional options. See
 * `git_indexer_options` above.
 * @return 0 or an error code.
 *)

function git_indexer_new(out_: PPgit_indexer; path: PAnsiChar; mode: Cardinal; odb: Pgit_odb;
  opts: Pgit_indexer_options): Integer; cdecl; external libgit2_dll {$IFDEF LIBGIT2_DLL_DELAY_LOAD}delayed{$ENDIF};
{$ENDIF}

(**
 * Add data to the indexer
 *
 * @param idx the indexer
 * @param data the data to add
 * @param size the size of the data in bytes
 * @param stats stat storage
 * @return 0 or an error code.
  *)
function git_indexer_append(idx: Pgit_indexer; data: Pointer; size: size_t;
  stats: Pgit_indexer_progress): Integer; cdecl; external libgit2_dll {$IFDEF LIBGIT2_DLL_DELAY_LOAD}delayed{$ENDIF};

(**
 * Finalize the pack and index
 *
 * Resolve any pending deltas and write out the index file
 *
 * @param idx the indexer
 * @param stats Stat storage.
 * @return 0 or an error code.
 *)

function git_indexer_commit(idx: Pgit_indexer; stats: Pgit_indexer_progress): Integer; cdecl; external libgit2_dll {$IFDEF LIBGIT2_DLL_DELAY_LOAD}delayed{$ENDIF};

{$IFNDEF GIT_DEPRECATE_HARD}
(**
 * Get the packfile's hash
 *
 * A packfile's name is derived from the sorted hashing of all object
 * names. This is only correct after the index has been finalized.
 *
 * @deprecated use git_indexer_name
 * @param idx the indexer instance
 * @return the packfile's hash
 *)

function git_indexer_hash(idx: Pgit_indexer): Pgit_oid; cdecl; external libgit2_dll {$IFDEF LIBGIT2_DLL_DELAY_LOAD}delayed{$ENDIF};
{$ENDIF}

(**
 * Get the unique name for the resulting packfile.
 *
 * The packfile's name is derived from the packfile's content.
 * This is only correct after the index has been finalized.
 *
 * @param idx the indexer instance
 * @return a NUL terminated string for the packfile name
 *)
function git_indexer_name(idx: Pgit_indexer): PAnsiChar; cdecl; external libgit2_dll {$IFDEF LIBGIT2_DLL_DELAY_LOAD}delayed{$ENDIF};

(**
 * Free the indexer and its resources
 *
 * @param idx the indexer to free
 *)

procedure git_indexer_free(idx: Pgit_indexer); cdecl; external libgit2_dll {$IFDEF LIBGIT2_DLL_DELAY_LOAD}delayed{$ENDIF};



