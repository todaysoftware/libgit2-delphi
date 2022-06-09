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

(**
 * Create a backend for the packfiles.
 *
 * @param out location to store the odb backend pointer
 * @param objects_dir the Git repository's objects directory
 *
 * @return 0 or an error code
 *)

function git_odb_backend_pack(out_: PPgit_odb_backend; objects_dir: PAnsiChar)  : Integer; cdecl; external libgit2_dll;

(**
 * Create a backend for loose objects
 *
 * @param out location to store the odb backend pointer
 * @param objects_dir the Git repository's objects directory
 * @param compression_level zlib compression level to use
 * @param do_fsync whether to do an fsync() after writing
 * @param dir_mode permissions to use creating a directory or 0 for defaults
 * @param file_mode permissions to use creating a file or 0 for defaults
 *
 * @return 0 or an error code
 *)

function git_odb_backend_loose(out_: PPgit_odb_backend; objects_dir: PAnsiChar;  compression_level, do_fsync: Integer;
dir_mode, file_mode: Cardinal): Integer; cdecl; external libgit2_dll;

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

function git_odb_backend_one_pack(out_: PPgit_odb_backend;  index_file: PAnsiChar): Integer; cdecl; external libgit2_dll;

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


