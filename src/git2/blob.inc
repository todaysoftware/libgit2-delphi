(**
 * @file git2/blob.h
 * @brief Git blob load and write routines
 * @defgroup git_blob Git blob load and write routines
 * @ingroup Git
 * @{
  *)

(**
 * Lookup a blob object from a repository.
 *
 * @param blob pointer to the looked up blob
 * @param repo the repo to use when locating the blob.
 * @param id identity of the blob to locate.
 * @return 0 or an error code
  *)

function git_blob_lookup(blob: PPgit_blob; repo: Pgit_repository; id: Pgit_oid): Integer; cdecl; external libgit2_dll;

(**
 * Lookup a blob object from a repository,
 * given a prefix of its identifier (short id).
 *
 * @see git_object_lookup_prefix
 *
 * @param blob pointer to the looked up blob
 * @param repo the repo to use when locating the blob.
 * @param id identity of the blob to locate.
 * @param len the length of the short identifier
 * @return 0 or an error code
  *)

function git_blob_lookup_prefix(blob: PPgit_blob; repo: Pgit_repository; id: Pgit_oid;
  len: size_t): Integer; cdecl; external libgit2_dll;

(**
 * Close an open blob
 *
 * This is a wrapper around git_object_free()
 *
 * IMPORTANT:
 * It *is* necessary to call this method when you stop
 * using a blob. Failure to do so will cause a memory leak.
 *
 * @param blob the blob to close
  *)

procedure git_blob_free(blob: Pgit_blob); cdecl; external libgit2_dll;

(**
 * Get the id of a blob.
 *
 * @param blob a previously loaded blob.
 * @return SHA1 hash for this blob.
  *)

function git_blob_id(blob: Pgit_blob): Pgit_oid; cdecl; external libgit2_dll;

(**
 * Get the repository that contains the blob.
 *
 * @param blob A previously loaded blob.
 * @return Repository that contains this blob.
  *)

function git_blob_owner(blob: Pgit_blob): Pgit_repository; cdecl; external libgit2_dll;

(**
 * Get a read-only buffer with the raw content of a blob.
 *
 * A pointer to the raw content of a blob is returned;
 * this pointer is owned internally by the object and shall
 * not be free'd. The pointer may be invalidated at a later
 * time.
 *
 * @param blob pointer to the blob
 * @return the pointer, or NULL on error
  *)

function git_blob_rawcontent(blob: Pgit_blob): Pointer; cdecl; external libgit2_dll;

(**
 * Get the size in bytes of the contents of a blob
 *
 * @param blob pointer to the blob
 * @return size on bytes
  *)

function git_blob_rawsize(blob: Pgit_blob): git_object_size_t; cdecl; external libgit2_dll;

(**
 * Flags to control the functionality of `git_blob_filter`.
  *)

const
  (** When set, filters will not be applied to binary files.  *)
  GIT_BLOB_FILTER_CHECK_FOR_BINARY = (1 shl 0);
  (**
   * When set, filters will not load configuration from the
   * system-wide `gitattributes` in `/etc` (or system equivalent).
    *)
  GIT_BLOB_FILTER_NO_SYSTEM_ATTRIBUTES = (1 shl 1);
  (**
   * When set, filters will be loaded from a `.gitattributes` file
   * in the HEAD commit.
    *)
  GIT_BLOB_FILTER_ATTRIBUTES_FROM_HEAD = (1 shl 2);
  (**
   * When set, filters will be loaded from a `.gitattributes` file
   * in the specified commit.
   *)
  GIT_BLOB_FILTER_ATTRIBUTES_FROM_COMMIT = (1 shl 3);
type
  git_blob_filter_flag_t = Integer;

  (**
 * The options used when applying filter options to a file.
 *
 * Initialize with `GIT_BLOB_FILTER_OPTIONS_INIT`. Alternatively, you can
 * use `git_blob_filter_options_init`.
 *
  *)

  git_blob_filter_options = record
    version: Integer;
    (** Flags to control the filtering process, see `git_blob_filter_flag_t` above  *)
    flags: uint32_t;
    {$IFDEF GIT_DEPRECATE_HARD}
    commit_id: Pgit_oid;
    {$ELSE}
    reserved: Pointer;
    {$ENDIF}
    (**
     * The commit to load attributes from, when
     * `GIT_BLOB_FILTER_ATTRIBUTES_FROM_COMMIT` is specified.
     *)
    attr_commit_id: git_oid;
  end;
  Pgit_blob_filter_options = ^git_blob_filter_options;

const
  GIT_BLOB_FILTER_OPTIONS_VERSION = 1;
  //GIT_BLOB_FILTER_OPTIONS_INIT = { GIT_BLOB_FILTER_OPTIONS_VERSION , GIT_BLOB_FILTER_CHECK_FOR_BINARY };

(**
   * Initialize git_blob_filter_options structure
   *
   * Initializes a `git_blob_filter_options` with default values. Equivalent
   * to creating an instance with `GIT_BLOB_FILTER_OPTIONS_INIT`.
   *
   * @param opts The `git_blob_filter_options` struct to initialize.
   * @param version The struct version; pass `GIT_BLOB_FILTER_OPTIONS_VERSION`.
   * @return Zero on success; -1 on failure.
    *)

function git_blob_filter_options_init(opts: Pgit_blob_filter_options;
  version: Cardinal): Integer; cdecl; external libgit2_dll;

(**
* Get a buffer with the filtered content of a blob.
*
* This applies filters as if the blob was being checked out to the
* working directory under the specified filename.  This may apply
* CRLF filtering or other types of changes depending on the file
* attributes set for the blob and the content detected in it.
*
* The output is written into a `git_buf` which the caller must free
* when done (via `git_buf_dispose`).
*
* If no filters need to be applied, then the `out` buffer will just
* be populated with a pointer to the raw content of the blob.  In
* that case, be careful to *not* free the blob until done with the
* buffer or copy it into memory you own.
*
* @param out The git_buf to be filled in
* @param blob Pointer to the blob
* @param as_path Path used for file attribute lookups, etc.
* @param opts Options to use for filtering the blob
* @return 0 on success or an error code
*)

function git_blob_filter(out_: Pgit_buf; blob: Pgit_blob; as_path: PAnsiChar;
  opts: Pgit_blob_filter_options): Integer; cdecl; external libgit2_dll;

(**
 * Read a file from the working folder of a repository
 * and write it to the Object Database as a loose blob
 *
 * @param id return the id of the written blob
 * @param repo repository where the blob will be written.
 *	this repository cannot be bare
 * @param relative_path file from which the blob will be created,
 *	relative to the repository's working dir
 * @return 0 or an error code
  *)

function git_blob_create_from_workdir(id: Pgit_oid; repo: Pgit_repository;
  relative_path: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Read a file from the filesystem and write its content
 * to the Object Database as a loose blob
 *
 * @param id return the id of the written blob
 * @param repo repository where the blob will be written.
 *	this repository can be bare or not
 * @param path file from which the blob will be created
 * @return 0 or an error code
  *)

function git_blob_create_from_disk(id: Pgit_oid; repo: Pgit_repository;
  path: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Create a stream to write a new blob into the object db
 *
 * This function may need to buffer the data on disk and will in
 * general not be the right choice if you know the size of the data
 * to write. If you have data in memory, use
 * `git_blob_create_from_buffer()`. If you do not, but know the size of
 * the contents (and don't want/need to perform filtering), use
 * `git_odb_open_wstream()`.
 *
 * Don't close this stream yourself but pass it to
 * `git_blob_create_from_stream_commit()` to commit the write to the
 * object db and get the object id.
 *
 * If the `hintpath` parameter is filled, it will be used to determine
 * what git filters should be applied to the object before it is written
 * to the object database.
 *
 * @param out the stream into which to write
 * @param repo Repository where the blob will be written.
 *        This repository can be bare or not.
 * @param hintpath If not NULL, will be used to select data filters
 *        to apply onto the content of the blob to be created.
 * @return 0 or error code
  *)

function git_blob_create_from_stream(out_: PPgit_writestream; repo: Pgit_repository;
  hintpath: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Close the stream and write the blob to the object db
 *
 * The stream will be closed and freed.
 *
 * @param out the id of the new blob
 * @param stream the stream to close
 * @return 0 or an error code
  *)

function git_blob_create_from_stream_commit(out_: Pgit_oid; stream: Pgit_writestream): Integer; cdecl; external libgit2_dll;

(**
 * Write an in-memory buffer to the ODB as a blob
 *
 * @param id return the id of the written blob
 * @param repo repository where the blob will be written
 * @param buffer data to be written into the blob
 * @param len length of the data
 * @return 0 or an error code
  *)

function git_blob_create_from_buffer(id: Pgit_oid; repo: Pgit_repository; buffer: Pointer;
  len: size_t): Integer; cdecl; external libgit2_dll;

(**
 * Determine if the blob content is most certainly binary or not.
 *
 * The heuristic used to guess if a file is binary is taken from core git:
 * Searching for NUL bytes and looking for a reasonable ratio of printable
 * to non-printable characters among the first 8000 bytes.
 *
 * @param blob The blob which content should be analyzed
 * @return 1 if the content of the blob is detected
 * as binary; 0 otherwise.
  *)

function git_blob_is_binary(blob: Pgit_blob): Integer; cdecl; external libgit2_dll;

(**
 * Create an in-memory copy of a blob. The copy must be explicitly
 * free'd or it will leak.
 *
 * @param out Pointer to store the copy of the object
 * @param source Original object to copy
  *)

function git_blob_dup(out_: PPgit_blob; source: Pgit_blob): Integer; cdecl; external libgit2_dll;

(** @}  *)



