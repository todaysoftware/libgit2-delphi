(**
 * @file git2/backend.h
 * @brief Git custom backend functions
 * @defgroup git_odb Git object database routines
 * @ingroup Git
 * @{
 *)

(*
 * Constructors for in-box ODB backends.
 *)

(** Options for configuring a packfile object backend. *)
type
  git_odb_backend_pack_options = record
    version: Cardinal; (**< version for the struct *)

    (**
     * Type of object IDs to use for this object database, or
     * 0 for default (currently SHA1).
     *)
    oid_type: git_oid_t;
  end;
  Pgit_odb_backend_pack_options = ^git_odb_backend_pack_options;

  (* The current version of the diff options structure *)
const
  GIT_ODB_BACKEND_PACK_OPTIONS_VERSION = 1;

  (* Stack initializer for odb pack backend options.  Alternatively use
   * `git_odb_backend_pack_options_init` programmatic initialization.
   *)
  //#DEFINE GIT_ODB_BACKEND_PACK_OPTIONS_INIT { GIT_ODB_BACKEND_PACK_OPTIONS_VERSION }

    (**
    * Create a backend for the packfiles.
    *
    * @param out location to store the odb backend pointer
    * @param objects_dir the Git repository's objects directory
    *
    * @return 0 or an error code
    *)

  {$IFDEF GIT_EXPERIMENTAL_SHA256}
function git_odb_backend_pack(out_: PPgit_odb_backend; objects_dir: PAnsiChar;
  opts: Pgit_odb_backend_pack_options): Integer; cdecl; external libgit2_dll;

{$ELSE}
function git_odb_backend_pack(out_: PPgit_odb_backend; objects_dir: PAnsiChar): Integer; cdecl; external libgit2_dll;
{$ENDIF}

(**
 * Create a backend out of a single packfile
 *
 * This can be useful for inspecting the contents of a single
 * packfile.
 *
 * @param out location to store the odb backend pointer
 * @param index_file path to the packfile's .idx file
 *
 * @return 0 or an error code
 *)
{$IFDEF GIT_EXPERIMENTAL_SHA256}
function git_odb_backend_one_pack(out_: PPgit_odb_backend; index_file: PAnsiChar;
  opts: Pgit_odb_backend_pack_options): Integer; cdecl; external libgit2_dll;

{$ELSE}
function git_odb_backend_one_pack(out_: PPgit_odb_backend; index_file: PAnsiChar): Integer; cdecl; external libgit2_dll;
{$ENDIF}

const
  GIT_ODB_BACKEND_LOOSE_FSYNC = (1 shl 0);
type
  git_odb_backend_loose_flag_t = Integer;

  (** Options for configuring a loose object backend. *)
type
  git_odb_backend_loose_options = record
    version: Cardinal; (**< version for the struct *)

    (** A combination of the `git_odb_backend_loose_flag_t` types. *)
    flags: uint32_t;

    (**
     * zlib compression level to use (0-9), where 1 is the fastest
     * at the expense of larger files, and 9 produces the best
     * compression at the expense of speed.  0 indicates that no
     * compression should be performed.  -1 is the default (currently
     * optimizing for speed).
     *)
    compression_level: Integer;

    (** Permissions to use creating a directory or 0 for defaults *)
    dir_mode: Cardinal;

    (** Permissions to use creating a file or 0 for defaults *)
    file_mode: Cardinal;

    (**
     * Type of object IDs to use for this object database, or
     * 0 for default (currently SHA1).
     *)
    oid_type: git_oid_t;
  end;
  Pgit_odb_backend_loose_options = ^git_odb_backend_loose_options;

  (* The current version of the diff options structure *)
const
  GIT_ODB_BACKEND_LOOSE_OPTIONS_VERSION = 1;

  (* Stack initializer for odb loose backend options.  Alternatively use
   * `git_odb_backend_loose_options_init` programmatic initialization.
   *)
  //#define GIT_ODB_BACKEND_LOOSE_OPTIONS_INIT { GIT_ODB_BACKEND_LOOSE_OPTIONS_VERSION, 0, -1 }

  (**
   * Create a backend for loose objects
   *
   * @param out location to store the odb backend pointer
   * @param objects_dir the Git repository's objects directory
   * @param opts options for the loose object backend or NULL
   *
   * @return 0 or an error code
   *)

  {$IFDEF GIT_EXPERIMENTAL_SHA256}
function git_odb_backend_loose(out_: PPgit_odb_backend; objects_dir: PAnsiChar;
  opts: Pgit_odb_backend_loose_options): Integer; cdecl; external libgit2_dll;

{$ELSE}
function git_odb_backend_loose(out_: PPgit_odb_backend; objects_dir: PAnsiChar; compression_level, do_fsync: Integer;
  dir_mode, file_mode: Cardinal): Integer; cdecl; external libgit2_dll;
{$ENDIF}

(** Streaming mode  *)

const
  GIT_STREAM_RDONLY           = (1 shl 1);
  GIT_STREAM_WRONLY           = (1 shl 2);
  GIT_STREAM_RW               = (GIT_STREAM_RDONLY or GIT_STREAM_WRONLY);
type
  git_odb_stream_t = Integer;

  (**
   * A stream to read/write from a backend.
   *
   * This represents a stream of data being written to or read from a
   * backend. When writing, the frontend functions take care of
   * calculating the object's id and all `finalize_write` needs to do is
   * store the object with the id it is passed.
   *)

  Pgit_odb_stream = ^git_odb_stream;
  PPgit_odb_stream = ^Pgit_odb_stream;
  git_odb_stream = record
    backend: Pgit_odb_backend;
    mode: Cardinal;
    hash_ctx: Pointer;
    declared_size: git_object_size_t;
    received_bytes: git_object_size_t;
    (**
     * Write at most `len` bytes into `buffer` and advance the stream.
     *)
    read_: function(stream: Pgit_odb_stream; buffer: PAnsiChar; len: size_t): Integer; cdecl;
    (**
     * Write `len` bytes from `buffer` into the stream.
     *)
    write_: function(stream: Pgit_odb_stream; buffer: PAnsiChar; len: size_t): Integer; cdecl;
    (**
     * Store the contents of the stream as an object with the id
     * specified in `oid`.
     *
     * This method might not be invoked if:
     * - an error occurs earlier with the `write` callback,
     * - the object referred to by `oid` already exists in any backend, or
     * - the final number of received bytes differs from the size declared
     *   with `git_odb_open_wstream()`
     *)
    finalize_write: function(stream: Pgit_odb_stream; oid: Pgit_oid): Integer; cdecl;
    (**
     * Free the stream's memory.
     *
     * This method might be called without a call to `finalize_write` if
     * an error occurs or if the object is already present in the ODB.
     *)
    Free: procedure(stream: Pgit_odb_stream); cdecl;
  end;

  (** A stream to write a pack file to the ODB  *)

type
  Pgit_odb_writepack = ^git_odb_writepack;
  PPgit_odb_writepack = ^Pgit_odb_writepack;
  git_odb_writepack = record
    backend: Pgit_odb_backend;
    append: function(writepack: Pgit_odb_writepack; data: Pointer; size: size_t;
      stats: Pgit_indexer_progress): Integer; cdecl;
    commit: function(writepack: Pgit_odb_writepack; stats: Pgit_indexer_progress)
    : Integer; cdecl;
    Free: procedure(writepack: Pgit_odb_writepack); cdecl;
  end;



