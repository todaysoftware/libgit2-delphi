(**
 * @file git2/common.h
 * @brief Git common platform definitions
 * @defgroup git_common Git common platform definitions
 * @ingroup Git
 * @{
 *)

const
  {$IFDEF MSWINDOWS}
  GIT_PATH_LIST_SEPARATOR     = ';';
  {$ELSE}
  GIT_PATH_LIST_SEPARATOR     = ':';
  {$ENDIF}

  (**
   * The maximum length of a valid git path.
   *)

  GIT_PATH_MAX                = 4096;
  (**
   * The string representation of the null object ID.
   *)

  GIT_OID_HEX_ZERO            = '0000000000000000000000000000000000000000';
  (**
   * Return the version of the libgit2 library
   * being currently used.
   *
   * @param major Store the major version number
   * @param minor Store the minor version number
   * @param rev Store the revision (patch) number
   * @return 0 on success or an error code on failure
   *)

function git_libgit2_version(major, minor, rev: PInteger): Integer; cdecl; external libgit2_dll;

(**
 * Combinations of these values describe the features with which libgit2
 * was compiled
 *)

const
  (**
   * If set, libgit2 was built thread-aware and can be safely used from multiple
   * threads.
   *)
  GIT_FEATURE_THREADS         = (1 shl 0);
  (**
   * If set, libgit2 was built with and linked against a TLS implementation.
   * Custom TLS streams may still be added by the user to support HTTPS
   * regardless of this.
   *)
  GIT_FEATURE_HTTPS           = (1 shl 1);
  (**
   * If set, libgit2 was built with and linked against libssh2. A custom
   * transport may still be added by the user to support libssh2 regardless of
   * this.
   *)
  GIT_FEATURE_SSH             = (1 shl 2);
  (**
   * If set, libgit2 was built with support for sub-second resolution in file
   * modification times.
   *)
  GIT_FEATURE_NSEC            = (1 shl 3);
type
  git_feature_t = Integer;

  (**
   * Query compile time options for libgit2.
   *
   * @return A combination of GIT_FEATURE_* values.
   *
   * - GIT_FEATURE_THREADS
   *   Libgit2 was compiled with thread support. Note that thread support is
   *   still to be seen as a 'work in progress' - basic object lookups are
   *   believed to be threadsafe, but other operations may not be.
   *
   * - GIT_FEATURE_HTTPS
   *   Libgit2 supports the https:// protocol. This requires the openssl
   *   library to be found when compiling libgit2.
   *
   * - GIT_FEATURE_SSH
   *   Libgit2 supports the SSH protocol for network operations. This requires
   *   the libssh2 library to be found when compiling libgit2
   *)

function git_libgit2_features: Integer; cdecl; external libgit2_dll;

(**
 * Global library options
 *
 * These are used to select which global option to set or get and are
 * used in `git_libgit2_opts()`.
 *)

const
  GIT_OPT_GET_MWINDOW_SIZE    = 0;
  GIT_OPT_SET_MWINDOW_SIZE    = 1;
  GIT_OPT_GET_MWINDOW_MAPPED_LIMIT = 2;
  GIT_OPT_SET_MWINDOW_MAPPED_LIMIT = 3;
  GIT_OPT_GET_SEARCH_PATH     = 4;
  GIT_OPT_SET_SEARCH_PATH     = 5;
  GIT_OPT_SET_CACHE_OBJECT_LIMIT = 6;
  GIT_OPT_SET_CACHE_MAX_SIZE  = 7;
  GIT_OPT_ENABLE_CACHING      = 8;
  GIT_OPT_GET_CACHED_MEMORY   = 9;
  GIT_OPT_GET_TEMPLATE_PATH   = 10;
  GIT_OPT_SET_TEMPLATE_PATH   = 11;
  GIT_OPT_SET_SSL_CERT_LOCATIONS = 12;
  GIT_OPT_SET_USER_AGENT      = 13;
  GIT_OPT_ENABLE_STRICT_OBJECT_CREATION = 14;
  GIT_OPT_ENABLE_STRICT_SYMBOLIC_REF_CREATION = 15;
  GIT_OPT_SET_SSL_CIPHERS     = 16;
  GIT_OPT_GET_USER_AGENT      = 17;
  GIT_OPT_ENABLE_OFS_DELTA    = 18;
  GIT_OPT_ENABLE_FSYNC_GITDIR = 19;
  GIT_OPT_GET_WINDOWS_SHAREMODE = 20;
  GIT_OPT_SET_WINDOWS_SHAREMODE = 21;
  GIT_OPT_ENABLE_STRICT_HASH_VERIFICATION = 22;
  GIT_OPT_SET_ALLOCATOR       = 23;
  GIT_OPT_ENABLE_UNSAVED_INDEX_SAFETY = 24;
  GIT_OPT_GET_PACK_MAX_OBJECTS = 25;
  GIT_OPT_SET_PACK_MAX_OBJECTS = 26;
  GIT_OPT_DISABLE_PACK_KEEP_FILE_CHECKS = 27;
  GIT_OPT_ENABLE_HTTP_EXPECT_CONTINUE = 28;
  GIT_OPT_GET_MWINDOW_FILE_LIMIT = 29;
  GIT_OPT_SET_MWINDOW_FILE_LIMIT = 30;
  GIT_OPT_SET_ODB_PACKED_PRIORITY = 31;
  GIT_OPT_SET_ODB_LOOSE_PRIORITY = 32;
  GIT_OPT_GET_EXTENSIONS      = 33;
  GIT_OPT_SET_EXTENSIONS      = 34;
  GIT_OPT_GET_OWNER_VALIDATION = 35;
  GIT_OPT_SET_OWNER_VALIDATION = 36;
type
  git_libgit2_opt_t = Integer;

  (**
   * Set or query a library global option
   *
   * Available options:
   *
   *	* opts(GIT_OPT_GET_MWINDOW_SIZE, size_t * ):
   *
   *		> Get the maximum mmap window size
   *
   *	* opts(GIT_OPT_SET_MWINDOW_SIZE, size_t):
   *
   *		> Set the maximum mmap window size
   *
   *	* opts(GIT_OPT_GET_MWINDOW_MAPPED_LIMIT, size_t * ):
   *
   *		> Get the maximum memory that will be mapped in total by the library
   *
   *	* opts(GIT_OPT_SET_MWINDOW_MAPPED_LIMIT, size_t):
   *
   *		> Set the maximum amount of memory that can be mapped at any time
   *		> by the library
   *
   *	* opts(GIT_OPT_GET_MWINDOW_FILE_LIMIT, size_t * ):
   *
   *		> Get the maximum number of files that will be mapped at any time by the
   *		> library
   *
   *	* opts(GIT_OPT_SET_MWINDOW_FILE_LIMIT, size_t):
   *
   *		> Set the maximum number of files that can be mapped at any time
   *		> by the library. The default (0) is unlimited.
   *
   *	* opts(GIT_OPT_GET_SEARCH_PATH, int level, git_buf *buf)
   *
   *		> Get the search path for a given level of config data.  "level" must
   *		> be one of `GIT_CONFIG_LEVEL_SYSTEM`, `GIT_CONFIG_LEVEL_GLOBAL`,
   *		> `GIT_CONFIG_LEVEL_XDG`, or `GIT_CONFIG_LEVEL_PROGRAMDATA`.
   *		> The search path is written to the `out` buffer.
   *
   *	* opts(GIT_OPT_SET_SEARCH_PATH, int level, const char *path)
   *
   *		> Set the search path for a level of config data.  The search path
   *		> applied to shared attributes and ignore files, too.
   *		>
   *		> - `path` lists directories delimited by GIT_PATH_LIST_SEPARATOR.
   *		>   Pass NULL to reset to the default (generally based on environment
   *		>   variables).  Use magic path `$PATH` to include the old value
   *		>   of the path (if you want to prepend or append, for instance).
   *		>
   *		> - `level` must be `GIT_CONFIG_LEVEL_SYSTEM`,
   *		>   `GIT_CONFIG_LEVEL_GLOBAL`, `GIT_CONFIG_LEVEL_XDG`, or
   *		>   `GIT_CONFIG_LEVEL_PROGRAMDATA`.
   *
   *	* opts(GIT_OPT_SET_CACHE_OBJECT_LIMIT, git_object_t type, size_t size)
   *
   *		> Set the maximum data size for the given type of object to be
   *		> considered eligible for caching in memory.  Setting to value to
   *		> zero means that that type of object will not be cached.
   *		> Defaults to 0 for GIT_OBJECT_BLOB (i.e. won't cache blobs) and 4k
   *		> for GIT_OBJECT_COMMIT, GIT_OBJECT_TREE, and GIT_OBJECT_TAG.
   *
   *	* opts(GIT_OPT_SET_CACHE_MAX_SIZE, ssize_t max_storage_bytes)
   *
   *		> Set the maximum total data size that will be cached in memory
   *		> across all repositories before libgit2 starts evicting objects
   *		> from the cache.  This is a soft limit, in that the library might
   *		> briefly exceed it, but will start aggressively evicting objects
   *		> from cache when that happens.  The default cache size is 256MB.
   *
   *	* opts(GIT_OPT_ENABLE_CACHING, int enabled)
   *
   *		> Enable or disable caching completely.
   *		>
   *		> Because caches are repository-specific, disabling the cache
   *		> cannot immediately clear all cached objects, but each cache will
   *		> be cleared on the next attempt to update anything in it.
   *
   *	* opts(GIT_OPT_GET_CACHED_MEMORY, ssize_t *current, ssize_t *allowed)
   *
   *		> Get the current bytes in cache and the maximum that would be
   *		> allowed in the cache.
   *
   *	* opts(GIT_OPT_GET_TEMPLATE_PATH, git_buf *out)
   *
   *		> Get the default template path.
   *		> The path is written to the `out` buffer.
   *
   *	* opts(GIT_OPT_SET_TEMPLATE_PATH, const char *path)
   *
   *		> Set the default template path.
   *		>
   *		> - `path` directory of template.
   *
   *	* opts(GIT_OPT_SET_SSL_CERT_LOCATIONS, const char *file, const char *path)
   *
   *		> Set the SSL certificate-authority locations.
   *		>
   *		> - `file` is the location of a file containing several
   *		>   certificates concatenated together.
   *		> - `path` is the location of a directory holding several
   *		>   certificates, one per file.
   *		>
   * 		> Either parameter may be `NULL`, but not both.
   *
   *	* opts(GIT_OPT_SET_USER_AGENT, const char *user_agent)
   *
   *		> Set the value of the User-Agent header.  This value will be
   *		> appended to "git/1.0", for compatibility with other git clients.
   *		>
   *		> - `user_agent` is the value that will be delivered as the
   *		>   User-Agent header on HTTP requests.
   *
   *	* opts(GIT_OPT_SET_WINDOWS_SHAREMODE, unsigned long value)
   *
   *		> Set the share mode used when opening files on Windows.
   *		> For more information, see the documentation for CreateFile.
   *		> The default is: FILE_SHARE_READ | FILE_SHARE_WRITE.  This is
   *		> ignored and unused on non-Windows platforms.
   *
   *	* opts(GIT_OPT_GET_WINDOWS_SHAREMODE, unsigned long *value)
   *
   *		> Get the share mode used when opening files on Windows.
   *
   *	* opts(GIT_OPT_ENABLE_STRICT_OBJECT_CREATION, int enabled)
   *
   *		> Enable strict input validation when creating new objects
   *		> to ensure that all inputs to the new objects are valid.  For
   *		> example, when this is enabled, the parent(s) and tree inputs
   *		> will be validated when creating a new commit.  This defaults
   *		> to enabled.
   *
   *	* opts(GIT_OPT_ENABLE_STRICT_SYMBOLIC_REF_CREATION, int enabled)
   *
   *		> Validate the target of a symbolic ref when creating it.  For
   *		> example, `foobar` is not a valid ref, therefore `foobar` is
   *		> not a valid target for a symbolic ref by default, whereas
   *		> `refs/heads/foobar` is.  Disabling this bypasses validation
   *		> so that an arbitrary strings such as `foobar` can be used
   *		> for a symbolic ref target.  This defaults to enabled.
   *
   *	* opts(GIT_OPT_SET_SSL_CIPHERS, const char *ciphers)
   *
   *		> Set the SSL ciphers use for HTTPS connections.
   *		>
   *		> - `ciphers` is the list of ciphers that are eanbled.
   *
   *	* opts(GIT_OPT_GET_USER_AGENT, git_buf *out)
   *
   *		> Get the value of the User-Agent header.
   *		> The User-Agent is written to the `out` buffer.
   *
   *	* opts(GIT_OPT_ENABLE_OFS_DELTA, int enabled)
   *
   *		> Enable or disable the use of "offset deltas" when creating packfiles,
   *		> and the negotiation of them when talking to a remote server.
   *		> Offset deltas store a delta base location as an offset into the
   *		> packfile from the current location, which provides a shorter encoding
   *		> and thus smaller resultant packfiles.
   *		> Packfiles containing offset deltas can still be read.
   *		> This defaults to enabled.
   *
   *	* opts(GIT_OPT_ENABLE_FSYNC_GITDIR, int enabled)
   *
   *		> Enable synchronized writes of files in the gitdir using `fsync`
   *		> (or the platform equivalent) to ensure that new object data
   *		> is written to permanent storage, not simply cached.  This
   *		> defaults to disabled.
   *
   *	 opts(GIT_OPT_ENABLE_STRICT_HASH_VERIFICATION, int enabled)
   *
   *		> Enable strict verification of object hashsums when reading
   *		> objects from disk. This may impact performance due to an
   *		> additional checksum calculation on each object. This defaults
   *		> to enabled.
   *
   *	 opts(GIT_OPT_SET_ALLOCATOR, git_allocator *allocator)
   *
   *		> Set the memory allocator to a different memory allocator. This
   *		> allocator will then be used to make all memory allocations for
   *		> libgit2 operations.  If the given `allocator` is NULL, then the
   *		> system default will be restored.
   *
   *	 opts(GIT_OPT_ENABLE_UNSAVED_INDEX_SAFETY, int enabled)
   *
   *		> Ensure that there are no unsaved changes in the index before
   *		> beginning any operation that reloads the index from disk (eg,
   *		> checkout).  If there are unsaved changes, the instruction will
   *		> fail.  (Using the FORCE flag to checkout will still overwrite
   *		> these changes.)
   *
   *	 opts(GIT_OPT_GET_PACK_MAX_OBJECTS, size_t *out)
   *
   *		> Get the maximum number of objects libgit2 will allow in a pack
   *		> file when downloading a pack file from a remote. This can be
   *		> used to limit maximum memory usage when fetching from an untrusted
   *		> remote.
   *
   *	 opts(GIT_OPT_SET_PACK_MAX_OBJECTS, size_t objects)
   *
   *		> Set the maximum number of objects libgit2 will allow in a pack
   *		> file when downloading a pack file from a remote.
   *
   *	 opts(GIT_OPT_DISABLE_PACK_KEEP_FILE_CHECKS, int enabled)
   *		> This will cause .keep file existence checks to be skipped when
   *		> accessing packfiles, which can help performance with remote filesystems.
   *
   *	 opts(GIT_OPT_ENABLE_HTTP_EXPECT_CONTINUE, int enabled)
   *		> When connecting to a server using NTLM or Negotiate
   *		> authentication, use expect/continue when POSTing data.
   *		> This option is not available on Windows.
   *
   *
   *       opts(GIT_OPT_SET_ODB_PACKED_PRIORITY, int priority)
   *              > Override the default priority of the packed ODB backend which
   *              > is added when default backends are assigned to a repository
   *
   *       opts(GIT_OPT_SET_ODB_LOOSE_PRIORITY, int priority)
   *              > Override the default priority of the loose ODB backend which
   *              > is added when default backends are assigned to a repository
   *
   *   opts(GIT_OPT_GET_EXTENSIONS, git_strarray *out)
   *      > Returns the list of git extensions that are supported.  This
   *      > is the list of built-in extensions supported by libgit2 and
   *      > custom extensions that have been added with
   *      > `GIT_OPT_SET_EXTENSIONS`.  Extensions that have been negated
   *      > will not be returned.  The returned list should be released
   *      > with `git_strarray_dispose`.
   *
   *   opts(GIT_OPT_SET_EXTENSIONS, const char **extensions, size_t len)
   *      > Set that the given git extensions are supported by the caller.
   *      > Extensions supported by libgit2 may be negated by prefixing
   *      > them with a `!`.  For example: setting extensions to
   *      > { "!noop", "newext" } indicates that the caller does not want
   *      > to support repositories with the `noop` extension but does want
   *      > to support repositories with the `newext` extension.
   *
   *   opts(GIT_OPT_GET_OWNER_VALIDATION, int *enabled)
   *      > Gets the owner validation setting for repository
   *      > directories.
   *
   *   opts(GIT_OPT_SET_OWNER_VALIDATION, int enabled)
   *      > Set that repository directories should be owned by the current
   *      > user. The default is to validate ownership.
   *
   * @param option Option key
   * @param ... value to set the option
   * @return 0 on success, <0 on failure
   *)

function git_libgit2_opts(option: Integer): Integer; cdecl varargs; external libgit2_dll;



