(**
 * @file git2/remote.h
 * @brief Git remote management functions
 * @defgroup git_remote remote management functions
 * @ingroup Git
 * @{
 *)

(**
 * Argument to the completion callback which tells it which operation
 * finished.
 *)

const
  GIT_REMOTE_COMPLETION_DOWNLOAD = 0;
  GIT_REMOTE_COMPLETION_INDEXING = 1;
  GIT_REMOTE_COMPLETION_ERROR = 2;
type
  git_remote_completion_t = Integer;

  (** Push network progress notification function  *)

  git_push_transfer_progress_cb = function(current, total: Cardinal;
    bytes: size_t; payload: Pointer): Integer; cdecl;

  (**
   * Represents an update which will be performed on the remote during push
   *)

  git_push_update = record
    (**
     * The source name of the reference
     *)
    src_refname: PAnsiChar;
    (**
     * The name of the reference to update on the server
     *)
    dst_refname: PAnsiChar;
    (**
     * The current target of the reference
     *)
    src: git_oid;
    (**
     * The new target for the reference
     *)
    dst: git_oid;
  end;

  (**
   * Callback used to inform of upcoming updates.
   *
   * @param updates an array containing the updates which will be sent
   * as commands to the destination.
   * @param len number of elements in `updates`
   * @param payload Payload provided by the caller
   *)

type
  PPgit_push_update = ^Pgit_push_update;
  Pgit_push_update = ^git_push_update;
  git_push_negotiation = function(updates: PPgit_push_update; len: size_t; payload: Pointer): Integer; cdecl;

  (**
   * Callback used to inform of the update status from the remote.
   *
   * Called for each updated reference on push. If `status` is
   * not `NULL`, the update was rejected by the remote server
   * and `status` contains the reason given.
   *
   * @param refname refname specifying to the remote ref
   * @param status status message sent from the remote
   * @param data data provided by the caller
   * @return 0 on success, otherwise an error
   *)

  git_push_update_reference_cb = function(refname, status: PAnsiChar; data: Pointer): Integer; cdecl;

  {$IFNDEF GIT_DEPRECATE_HARD}
  (**
 * Callback to resolve URLs before connecting to remote
 *
 * If you return GIT_PASSTHROUGH, you don't need to write anything to
 * url_resolved.
 *
 * @param url_resolved The buffer to write the resolved URL to
 * @param url The URL to resolve
 * @param direction GIT_DIRECTION_FETCH or GIT_DIRECTION_PUSH
 * @param payload Payload provided by the caller
 * @return 0 on success, GIT_PASSTHROUGH or an error
 * @deprecated Use `git_remote_set_instance_url`
 *)

  git_url_resolve_cb = function(url_resolved: Pgit_buf; url: PAnsiChar; direction: Integer; payload: Pointer): Integer; cdecl;
  {$ENDIF}

  (**
   * Callback invoked immediately before we attempt to connect to the
   * given url.  Callers may change the URL before the connection by
   * calling `git_remote_set_instance_url` in the callback.
   *
   * @param remote The remote to be connected
   * @param direction GIT_DIRECTION_FETCH or GIT_DIRECTION_PUSH
   * @param payload Payload provided by the caller
   * @return 0 on success, or an error
   *)
  git_remote_ready_cb = function(remote: git_remote; direction: Integer; payload: Pointer): Integer; cdecl;

  (**
   * The callback settings structure
   *
   * Set the callbacks to be called by the remote when informing the user
   * about the progress of the network operations.
   *)

  git_remote_callbacks = record
    version: Cardinal; (**< The version  *)
    (**
     * Textual progress from the remote. Text send over the
     * progress side-band will be passed to this function (this is
     * the 'counting objects' output).
     *)
    sideband_progress: git_transport_message_cb;
    (**
     * Completion is called when different parts of the download
     * process are done (currently unused).
     *)
    completion: function(type_: git_remote_completion_t; data: Pointer): Integer; cdecl;
    (**
     * This will be called if the remote host requires
     * authentication in order to connect to it.
     *
     * Returning GIT_PASSTHROUGH will make libgit2 behave as
     * though this field isn't set.
     *)
    credentials: git_credential_acquire_cb;
    (**
     * If cert verification fails, this will be called to let the
     * user make the final decision of whether to allow the
     * connection to proceed. Returns 0 to allow the connection
     * or a negative value to indicate an error.
     *)
    certificate_check: git_transport_certificate_check_cb;
    (**
     * During the download of new data, this will be regularly
     * called with the current count of progress done by the
     * indexer.
     *)
    transfer_progress: git_indexer_progress_cb;
    (**
     * Each time a reference is updated locally, this function
     * will be called with information about it.
     *)
    update_tips: function(refname: PAnsiChar; a, b: Pgit_oid; data: Pointer): Integer; cdecl;
    (**
     * Function to call with progress information during pack
     * building. Be aware that this is called inline with pack
     * building operations, so performance may be affected.
     *)
    pack_progress: git_packbuilder_progress;
    (**
     * Function to call with progress information during the
     * upload portion of a push. Be aware that this is called
     * inline with pack building operations, so performance may be
     * affected.
     *)
    push_transfer_progress: git_push_transfer_progress_cb;
    (**
     * See documentation of git_push_update_reference_cb
     *)
    push_update_reference: git_push_update_reference_cb;
    (**
     * Called once between the negotiation step and the upload. It
     * provides information about what updates will be performed.
     *)
    push_negotiation: git_push_negotiation;
    (**
     * Create the transport to use for this operation. Leave NULL
     * to auto-detect.
     *)
    transport: git_transport_cb;
    (**
     * Callback when the remote is ready to connect.
     *)
    remote_ready: git_remote_ready_cb;
    (**
     * This will be passed to each of the callbacks in this struct
     * as the last parameter.
     *)
    payload: Pointer;
    (**
     * Resolve URL before connecting to remote.
     * The returned URL will be used to connect to the remote instead.
     *)
    {$IFDEF GIT_DEPRECATE_HARD}
    reserved: Pointer;
    {$ELSE}
    (**
     * Resolve URL before connecting to remote.
     * The returned URL will be used to connect to the remote instead.
     *
     * This callback is deprecated; users should use
     * git_remote_ready_cb and configure the instance URL instead.
     *)
    resolve_url: git_url_resolve_cb;
    {$ENDIF}
  end;
  Pgit_remote_callbacks = ^git_remote_callbacks;
  PPgit_remote_callbacks = ^Pgit_remote_callbacks;

const
  GIT_REMOTE_CALLBACKS_VERSION = 1;
  //GIT_REMOTE_CALLBACKS_INIT = { GIT_REMOTE_CALLBACKS_VERSION };
  (**
   * Initializes a `git_remote_callbacks` with default values. Equivalent to
   * creating an instance with GIT_REMOTE_CALLBACKS_INIT.
   *
   * @param opts the `git_remote_callbacks` struct to initialize
   * @param version Version of struct; pass `GIT_REMOTE_CALLBACKS_VERSION`
   * @return Zero on success; -1 on failure.
   *)

function git_remote_init_callbacks(opts: Pgit_remote_callbacks; version: Cardinal): Integer; cdecl; external libgit2_dll;

(** Acceptable prune settings when fetching  *)

const
  (**
   * Use the setting from the configuration
   *)
  GIT_FETCH_PRUNE_UNSPECIFIED = 0;
  (**
   * Force pruning on
   *)
  GIT_FETCH_PRUNE             = 1;
  (**
   * Force pruning off
   *)
  GIT_FETCH_NO_PRUNE          = 2;
type
  git_fetch_prune_t = Integer;

  (**
   * Automatic tag following option
   *
   * Lets us select the --tags option to use.
   *)

const
  (**
   * Use the setting from the configuration.
   *)
  GIT_REMOTE_DOWNLOAD_TAGS_UNSPECIFIED = 0;
  (**
   * Ask the server for tags pointing to objects we're already
   * downloading.
   *)
  GIT_REMOTE_DOWNLOAD_TAGS_AUTO = 1;
  (**
   * Don't ask for any tags beyond the refspecs.
   *)
  GIT_REMOTE_DOWNLOAD_TAGS_NONE = 2;
  (**
   * Ask for the all the tags.
   *)
  GIT_REMOTE_DOWNLOAD_TAGS_ALL = 3;
type
  git_remote_autotag_option_t = Integer;

  (**
   * Remote redirection settings; whether redirects to another host
   * are permitted.  By default, git will follow a redirect on the
   * initial request (`/info/refs`), but not subsequent requests.
   *)
const
  (**
   * Do not follow any off-site redirects at any stage of
   * the fetch or push.
   *)
  GIT_REMOTE_REDIRECT_NONE    = (1 shl 0);
  (**
   * Allow off-site redirects only upon the initial request.
   * This is the default.
   *)
  GIT_REMOTE_REDIRECT_INITIAL = (1 shl 1);
  (**
   * Allow redirects at any stage in the fetch or push.
   *)
  GIT_REMOTE_REDIRECT_ALL     = (1 shl 2);
type
  git_remote_redirect_t = Integer;

const
  (** Constants for fetch depth (shallowness of fetch). *)
  (** The fetch is "full" (not shallow). This is the default. *)
  GIT_FETCH_DEPTH_FULL        = 0;

  (** The fetch should "unshallow" and fetch missing data. *)
  GIT_FETCH_DEPTH_UNSHALLOW   = 2147483647;

  (**
   * Fetch options structure.
   *
   * Zero out for defaults.  Initialize with `GIT_FETCH_OPTIONS_INIT` macro to
   * correctly set the `version` field.  E.g.
   *
   *		git_fetch_options opts = GIT_FETCH_OPTIONS_INIT;
   *)
type
  git_fetch_options = record
    version: Cardinal;
    (**
     * Callbacks to use for this fetch operation
     *)
    callbacks: git_remote_callbacks;
    (**
     * Whether to perform a prune after the fetch
     *)
    prune: git_fetch_prune_t;
    (**
     * How to handle reference updates; see `git_remote_update_flags`.
     *)
    update_fetchhead: Integer;
    (**
     * Determines how to behave regarding tags on the remote, such
     * as auto-downloading tags for objects we're downloading or
     * downloading all of them.
     *
     * The default is to auto-follow tags.
     *)
    download_tags: git_remote_autotag_option_t;
    (**
     * Proxy options to use, by default no proxy is used.
     *)
    proxy_opts: git_proxy_options;
    (**
     * Depth of the fetch to perform, or `GIT_FETCH_DEPTH_FULL`
     * (or `0`) for full history, or `GIT_FETCH_DEPTH_UNSHALLOW`
     * to "unshallow" a shallow repository.
     *
     * The default is full (`GIT_FETCH_DEPTH_FULL` or `0`).
     *)
    depth: Integer;
    (**
     * Whether to allow off-site redirects.  If this is not
     * specified, the `http.followRedirects` configuration setting
     * will be consulted.
     *)
    follow_redirects: git_remote_redirect_t;
    (**
     * Extra headers for this fetch operation
     *)
    custom_headers: git_strarray;
  end;
  Pgit_fetch_options = ^git_fetch_options;

const
  GIT_FETCH_OPTIONS_VERSION   = 1;
  //GIT_FETCH_OPTIONS_INIT = { GIT_FETCH_OPTIONS_VERSION , GIT_REMOTE_CALLBACKS_INIT , GIT_FETCH_PRUNE_UNSPECIFIED , 1 , GIT_REMOTE_DOWNLOAD_TAGS_UNSPECIFIED , GIT_PROXY_OPTIONS_INIT };
  (**
   * Initialize git_fetch_options structure
   *
   * Initializes a `git_fetch_options` with default values. Equivalent to
   * creating an instance with `GIT_FETCH_OPTIONS_INIT`.
   *
   * @param opts The `git_fetch_options` struct to initialize.
   * @param version The struct version; pass `GIT_FETCH_OPTIONS_VERSION`.
   * @return Zero on success; -1 on failure.
   *)

function git_fetch_options_init(opts: Pgit_fetch_options; version: Cardinal): Integer; cdecl; external libgit2_dll;

(**
 * Controls the behavior of a git_push object.
 *)

type
  git_push_options = record
    version: Cardinal;
    (**
     * If the transport being used to push to the remote requires the creation
     * of a pack file, this controls the number of worker threads used by
     * the packbuilder when creating that pack file to be sent to the remote.
     *
     * If set to 0, the packbuilder will auto-detect the number of threads
     * to create. The default value is 1.
     *)
    pb_parallelism: Cardinal;
    (**
     * Callbacks to use for this push operation
     *)
    callbacks: git_remote_callbacks;
    (**
     * Proxy options to use, by default no proxy is used.
     *)
    proxy_opts: git_proxy_options;
    (**
     * Whether to allow off-site redirects.  If this is not
     * specified, the `http.followRedirects` configuration setting
     * will be consulted.
     *)
    follow_redirects: git_remote_redirect_t;
    (**
     * Extra headers for this push operation
     *)
    custom_headers: git_strarray;
    (**
     * "Push options" to deliver to the remote.
     *)
    remote_push_options: git_strarray;
  end;
  Pgit_push_options = ^git_push_options;

const
  GIT_PUSH_OPTIONS_VERSION    = 1;
  //GIT_PUSH_OPTIONS_INIT = { GIT_PUSH_OPTIONS_VERSION , 1 , GIT_REMOTE_CALLBACKS_INIT , GIT_PROXY_OPTIONS_INIT };
  (**
   * Initialize git_push_options structure
   *
   * Initializes a `git_push_options` with default values. Equivalent to
   * creating an instance with `GIT_PUSH_OPTIONS_INIT`.
   *
   * @param opts The `git_push_options` struct to initialize.
   * @param version The struct version; pass `GIT_PUSH_OPTIONS_VERSION`.
   * @return Zero on success; -1 on failure.
   *)

function git_push_options_init(opts: Pgit_push_options; version: Cardinal): Integer; cdecl; external libgit2_dll;

(**
 * Add a remote with the default fetch refspec to the repository's configuration.
 *
 * @param out the resulting remote
 * @param repo the repository in which to create the remote
 * @param name the remote's name
 * @param url the remote's url
 * @return 0, GIT_EINVALIDSPEC, GIT_EEXISTS or an error code
 *)

function git_remote_create(out_: PPgit_remote; repo: Pgit_repository;
  name_, url: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Remote creation options flags
 *)
const
  (** Ignore the repository apply.insteadOf configuration  *)
  GIT_REMOTE_CREATE_SKIP_INSTEADOF = (1 shl 0);
  (** Don't build a fetchspec from the name if none is set  *)
  GIT_REMOTE_CREATE_SKIP_DEFAULT_FETCHSPEC = (1 shl 1);

type
  git_remote_create_flags = Cardinal;

  (**
   * How to handle reference updates.
   *)
const
  (* Write the fetch results to FETCH_HEAD. *)
  GIT_REMOTE_UPDATE_FETCHHEAD = (1 shl 0);
  (* Report unchanged tips in the update_tips callback. *)
  GIT_REMOTE_UPDATE_REPORT_UNCHANGED = (1 shl 1);

type
  git_remote_update_flags = Cardinal;

  (**
   * Remote creation options structure
   *
   * Initialize with `GIT_REMOTE_CREATE_OPTIONS_INIT`. Alternatively, you can
   * use `git_remote_create_options_init`.
   *
   *)

  git_remote_create_options = record
    version: Cardinal;
    (**
     * The repository that should own the remote.
     * Setting this to NULL results in a detached remote.
     *)
    repository: Pgit_repository;
    (**
     * The remote's name.
     * Setting this to NULL results in an in-memory/anonymous remote.
     *)
    name_: PAnsiChar;
    (** The fetchspec the remote should use.  *)
    fetchspec: PAnsiChar;
    (** Additional flags for the remote. See git_remote_create_flags.  *)
    flags: Cardinal;
  end;
  Pgit_remote_create_options = ^git_remote_create_options;

const
  GIT_REMOTE_CREATE_OPTIONS_VERSION = 1;
  //GIT_REMOTE_CREATE_OPTIONS_INIT = { GIT_REMOTE_CREATE_OPTIONS_VERSION };
  (**
   * Initialize git_remote_create_options structure
   *
   * Initializes a `git_remote_create_options` with default values. Equivalent to
   * creating an instance with `GIT_REMOTE_CREATE_OPTIONS_INIT`.
   *
   * @param opts The `git_remote_create_options` struct to initialize.
   * @param version The struct version; pass `GIT_REMOTE_CREATE_OPTIONS_VERSION`.
   * @return Zero on success; -1 on failure.
   *)

function git_remote_create_options_init(opts: Pgit_remote_create_options; version: Cardinal): Integer; cdecl; external libgit2_dll;

(**
 * Create a remote, with options.
 *
 * This function allows more fine-grained control over the remote creation.
 *
 * Passing NULL as the opts argument will result in a detached remote.
 *
 * @param out the resulting remote
 * @param url the remote's url
 * @param opts the remote creation options
 * @return 0, GIT_EINVALIDSPEC, GIT_EEXISTS or an error code
 *)

function git_remote_create_with_opts(out_: PPgit_remote; url: PAnsiChar;
  opts: Pgit_remote_create_options): Integer; cdecl; external libgit2_dll;

(**
 * Add a remote with the provided fetch refspec (or default if NULL) to the repository's
 * configuration.
 *
 * @param out the resulting remote
 * @param repo the repository in which to create the remote
 * @param name the remote's name
 * @param url the remote's url
 * @param fetch the remote fetch value
 * @return 0, GIT_EINVALIDSPEC, GIT_EEXISTS or an error code
 *)

function git_remote_create_with_fetchspec(out_: PPgit_remote; repo: Pgit_repository;
  name_, url, fetch: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Create an anonymous remote
 *
 * Create a remote with the given url in-memory. You can use this when
 * you have a URL instead of a remote's name.
 *
 * @param out pointer to the new remote objects
 * @param repo the associated repository
 * @param url the remote repository's URL
 * @return 0 or an error code
 *)

function git_remote_create_anonymous(out_: PPgit_remote; repo: Pgit_repository;
  url: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Create a remote without a connected local repo
 *
 * Create a remote with the given url in-memory. You can use this when
 * you have a URL instead of a remote's name.
 *
 * Contrasted with git_remote_create_anonymous, a detached remote
 * will not consider any repo configuration values (such as insteadof url
 * substitutions).
 *
 * @param out pointer to the new remote objects
 * @param url the remote repository's URL
 * @return 0 or an error code
 *)

function git_remote_create_detached(out_: PPgit_remote; url: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Get the information for a particular remote
 *
 * The name will be checked for validity.
 * See `git_tag_create()` for rules about valid names.
 *
 * @param out pointer to the new remote object
 * @param repo the associated repository
 * @param name the remote's name
 * @return 0, GIT_ENOTFOUND, GIT_EINVALIDSPEC or an error code
  *)

function git_remote_lookup(out_: PPgit_remote; repo: Pgit_repository; name_: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Create a copy of an existing remote.  All internal strings are also
 * duplicated. Callbacks are not duplicated.
 *
 * Call `git_remote_free` to free the data.
 *
 * @param dest pointer where to store the copy
 * @param source object to copy
 * @return 0 or an error code
 *)

function git_remote_dup(dest: PPgit_remote; source: Pgit_remote): Integer; cdecl; external libgit2_dll;

(**
 * Get the remote's repository
 *
 * @param remote the remote
 * @return a pointer to the repository
 *)

function git_remote_owner(remote: Pgit_remote): Pgit_repository; cdecl; external libgit2_dll;

(**
 * Get the remote's name
 *
 * @param remote the remote
 * @return a pointer to the name or NULL for in-memory remotes
 *)

function git_remote_name(remote: Pgit_remote): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Get the remote's url
 *
 * return the modified URL.  If `git_remote_set_instance_pushurl`
 * has been called for this remote, then that URL will be returned.
 *
 * @param remote the remote
 * @return a pointer to the url
 *)

function git_remote_url(remote: Pgit_remote): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Get the remote's url for pushing.
 *
 * will return the modified URL.  If `git_remote_set_instance_pushurl`
 * has been called for this remote, then that URL will be returned.
 *
 * @param remote the remote
 * @return a pointer to the url or NULL if no special url for pushing is set
 *)

function git_remote_pushurl(remote: Pgit_remote): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Set the remote's url in the configuration
 *
 * Remote objects already in memory will not be affected. This assumes
 * the common case of a single-url remote and will otherwise return an error.
 *
 * @param repo the repository in which to perform the change
 * @param remote the remote's name
 * @param url the url to set
 * @return 0 or an error value
 *)

function git_remote_set_url(repo: Pgit_repository; remote, url: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Set the remote's url for pushing in the configuration.
 *
 * Remote objects already in memory will not be affected. This assumes
 * the common case of a single-url remote and will otherwise return an error.
 *
 *
 * @param repo the repository in which to perform the change
 * @param remote the remote's name
 * @param url the url to set
 * @return 0, or an error code
 *)

function git_remote_set_pushurl(repo: Pgit_repository; remote, url: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Set the url for this particular url instance.  The URL in the
 * configuration will be ignored, and will not be changed.
 *
 * @param remote the remote's name
 * @param url the url to set
 * @return 0 or an error value
 *)

function git_remote_set_instance_url(remote: Pgit_remote; url: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Set the push url for this particular url instance.  The URL in the
 * configuration will be ignored, and will not be changed.
 *
 * @param remote the remote's name
 * @param url the url to set
 * @return 0 or an error value
 *)

function git_remote_set_instance_pushurl(remote: Pgit_remote; url: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Add a fetch refspec to the remote's configuration
 *
 * Add the given refspec to the fetch list in the configuration. No
 * loaded remote instances will be affected.
 *
 * @param repo the repository in which to change the configuration
 * @param remote the name of the remote to change
 * @param refspec the new fetch refspec
 * @return 0, GIT_EINVALIDSPEC if refspec is invalid or an error value
 *)

function git_remote_add_fetch(repo: Pgit_repository; remote, refspec: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Get the remote's list of fetch refspecs
 *
 * The memory is owned by the user and should be freed with
 * `git_strarray_free`.
 *
 * @param array pointer to the array in which to store the strings
 * @param remote the remote to query
 * @return 0 or an error code.
 *)

function git_remote_get_fetch_refspecs(array_: Pgit_strarray; remote: Pgit_remote): Integer; cdecl; external libgit2_dll;

(**
 * Add a push refspec to the remote's configuration
 *
 * Add the given refspec to the push list in the configuration. No
 * loaded remote instances will be affected.
 *
 * @param repo the repository in which to change the configuration
 * @param remote the name of the remote to change
 * @param refspec the new push refspec
 * @return 0, GIT_EINVALIDSPEC if refspec is invalid or an error value
 *)

function git_remote_add_push(repo: Pgit_repository; remote, refspec: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Get the remote's list of push refspecs
 *
 * The memory is owned by the user and should be freed with
 * `git_strarray_free`.
 *
 * @param array pointer to the array in which to store the strings
 * @param remote the remote to query
 * @return 0 or an error code.
 *)

function git_remote_get_push_refspecs(array_: Pgit_strarray; remote: Pgit_remote): Integer; cdecl; external libgit2_dll;

(**
 * Get the number of refspecs for a remote
 *
 * @param remote the remote
 * @return the amount of refspecs configured in this remote
 *)

function git_remote_refspec_count(remote: Pgit_remote): size_t; cdecl; external libgit2_dll;

(**
 * Get a refspec from the remote
 *
 * @param remote the remote to query
 * @param n the refspec to get
 * @return the nth refspec
 *)

function git_remote_get_refspec(remote: Pgit_remote; n: size_t): Pgit_refspec; cdecl; external libgit2_dll;

(**
 * Get the remote repository's reference advertisement list
 *
 * Get the list of references with which the server responds to a new
 * connection.
 *
 * The remote (or more exactly its transport) must have connected to
 * the remote repository. This list is available as soon as the
 * connection to the remote is initiated and it remains available
 * after disconnecting.
 *
 * The memory belongs to the remote. The pointer will be valid as long
 * as a new connection is not initiated, but it is recommended that
 * you make a copy in order to make use of the data.
 *
 * @param out pointer to the array
 * @param size the number of remote heads
 * @param remote the remote
 * @return 0 on success, or an error code
 *)

function git_remote_ls(out_: PPPgit_remote_head; size: Psize_t; remote: Pgit_remote): Integer; cdecl; external libgit2_dll;

(**
 * Check whether the remote is connected
 *
 * Check whether the remote's underlying transport is connected to the
 * remote host.
 *
 * @param remote the remote
 * @return 1 if it's connected, 0 otherwise.
 *)

function git_remote_connected(remote: Pgit_remote): Integer; cdecl; external libgit2_dll;

(**
 * Cancel the operation
 *
 * At certain points in its operation, the network code checks whether
 * the operation has been cancelled and if so stops the operation.
 *
 * @param remote the remote
 * @return 0 on success, or an error code
 *)

function git_remote_stop(remote: Pgit_remote): Integer; cdecl; external libgit2_dll;

(**
 * Disconnect from the remote
 *
 * Close the connection to the remote.
 *
 * @param remote the remote to disconnect from
 * @return 0 on success, or an error code
 *)

function git_remote_disconnect(remote: Pgit_remote): Integer; cdecl; external libgit2_dll;

(**
 * Free the memory associated with a remote
 *
 * This also disconnects from the remote, if the connection
 * has not been closed yet (using git_remote_disconnect).
 *
 * @param remote the remote to free
 *)

procedure git_remote_free(remote: Pgit_remote); cdecl; external libgit2_dll;

(**
 * Get a list of the configured remotes for a repo
 *
 * The string array must be freed by the user.
 *
 * @param out a string array which receives the names of the remotes
 * @param repo the repository to query
 * @return 0 or an error code
 *)

function git_remote_list(out_: Pgit_strarray; repo: Pgit_repository): Integer; cdecl; external libgit2_dll;

(**
 * Remote creation options structure
 *
 * Initialize with `GIT_REMOTE_CREATE_OPTIONS_INIT`. Alternatively, you can
 * use `git_remote_create_options_init`.
 *
 *)
type
  git_remote_connect_options = record
    version: Cardinal;

    (** Callbacks to use for this connection *)
    callbacks: git_remote_callbacks;

    (** HTTP Proxy settings *)
    proxy_opts: git_proxy_options;

    (**
     * Whether to allow off-site redirects.  If this is not
     * specified, the `http.followRedirects` configuration setting
     * will be consulted.
     *)
    follow_redirects: git_remote_redirect_t;

    (** Extra HTTP headers to use in this connection *)
    custom_headers: git_strarray;
  end;
  Pgit_remote_connect_options = ^git_remote_connect_options;

const
  GIT_REMOTE_CONNECT_OPTIONS_VERSION = 1;
  (*#define GIT_REMOTE_CONNECT_OPTIONS_INIT { \
 GIT_REMOTE_CONNECT_OPTIONS_VERSION, \
 GIT_REMOTE_CALLBACKS_INIT, \
 GIT_PROXY_OPTIONS_INIT }*)

(**
 * Initialize git_remote_connect_options structure.
 *
 * Initializes a `git_remote_connect_options` with default values.
 * Equivalent to creating an instance with
 * `GIT_REMOTE_CONNECT_OPTIONS_INIT`.
 *
 * @param opts The `git_remote_connect_options` struct to initialize.
 * @param version The struct version; pass `GIT_REMOTE_CONNECT_OPTIONS_VERSION`.
 * @return Zero on success; -1 on failure.
 *)

function git_remote_connect_options_init(opts: Pgit_remote_connect_options; version: Cardinal): Integer; cdecl; external libgit2_dll;

(**
 * Open a connection to a remote.
 *
 * The transport is selected based on the URL; the direction argument
 * is due to a limitation of the git protocol which starts up a
 * specific binary which can only do the one or the other.
 *
 * @param remote the remote to connect to
 * @param direction GIT_DIRECTION_FETCH if you want to fetch or
 * GIT_DIRECTION_PUSH if you want to push
 * @param callbacks the callbacks to use for this connection
 * @param proxy_opts proxy settings
 * @param custom_headers extra HTTP headers to use in this connection
 * @return 0 or an error code
 *)

function git_remote_connect(remote: Pgit_remote; direction: git_direction;
  callbacks: Pgit_remote_callbacks; proxy_opts: Pgit_proxy_options;
  custom_headers: Pgit_strarray): Integer; cdecl; external libgit2_dll;

(**
 * Open a connection to a remote with extended options.
 *
 * The transport is selected based on the URL; the direction argument
 * is due to a limitation of the git protocol which starts up a
 * specific binary which can only do the one or the other.
 *
 * The given options structure will form the defaults for connection
 * options and callback setup.  Callers may override these defaults
 * by specifying `git_fetch_options` or `git_push_options` in
 * subsequent calls.
 *
 * @param remote the remote to connect to
 * @param direction GIT_DIRECTION_FETCH if you want to fetch or
 * GIT_DIRECTION_PUSH if you want to push
 * @param opts the remote connection options
 * @return 0 or an error code
 *)

function git_remote_connect_ext(remote: Pgit_remote; direction: git_direction;
  opts: Pgit_remote_connect_options): Integer; cdecl; external libgit2_dll;

(**
 * Download and index the packfile
 *
 * Connect to the remote if it hasn't been done yet, negotiate with
 * the remote git which objects are missing, download and index the
 * packfile.
 *
 * The .idx file will be created and both it and the packfile with be
 * renamed to their final name.
 *
 * If options are specified and this remote is already connected then
 * the existing remote connection options will be discarded and the
 * remote will now use the new options.
 *
 * @param remote the remote
 * @param refspecs the refspecs to use for this negotiation and
 * download. Use NULL or an empty array to use the base refspecs
 * @param opts the options to use for this fetch or NULL
 * @return 0 or an error code
 *)

function git_remote_download(remote: Pgit_remote; refspecs: Pgit_strarray;
  opts: Pgit_fetch_options): Integer; cdecl; external libgit2_dll;

(**
 * Create a packfile and send it to the server
 *
 * Connect to the remote if it hasn't been done yet, negotiate with
 * the remote git which objects are missing, create a packfile with
 * the missing objects and send it.
 *
 * If options are specified and this remote is already connected then
 * the existing remote connection options will be discarded and the
 * remote will now use the new options.
 *
 * @param remote the remote
 * @param refspecs the refspecs to use for this negotiation and
 * upload. Use NULL or an empty array to use the base refspecs
 * @param opts the options to use for this push
 * @return 0 or an error code
 *)

function git_remote_upload(remote: Pgit_remote; refspecs: Pgit_strarray;
  opts: Pgit_push_options): Integer; cdecl; external libgit2_dll;

(**
 * Update the tips to the new state.
 *
 * If callbacks are not specified then the callbacks specified to
 * `git_remote_connect` will be used (if it was called).
 *
 * @param remote the remote to update
 * @param reflog_message The message to insert into the reflogs. If
 * NULL and fetching, the default is "fetch <name>", where <name> is
 * the name of the remote (or its url, for in-memory remotes). This
 * parameter is ignored when pushing.
 * @param callbacks  pointer to the callback structure to use or NULL
 * @param update_flags the git_remote_update_flags for these tips.
 * @param download_tags what the behaviour for downloading tags is for this fetch. This is
 * ignored for push. This must be the same value passed to `git_remote_download()`.
 * @return 0 or an error code
 *)

function git_remote_update_tips(remote: Pgit_remote; callbacks: Pgit_remote_callbacks;
  update_flags: Cardinal; download_tags: git_remote_autotag_option_t;
  reflog_message: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Download new data and update tips.
 *
 * Convenience function to connect to a remote, download the data,
 * disconnect and update the remote-tracking branches.
 *
 * If options are specified and this remote is already connected then
 * the existing remote connection options will be discarded and the
 * remote will now use the new options.
 *
 * @param remote the remote to fetch from
 * @param refspecs the refspecs to use for this fetch. Pass NULL or an
 *                 empty array to use the base refspecs.
 * @param opts options to use for this fetch or NULL
 * @param reflog_message The message to insert into the reflogs. If NULL, the
 *								 default is "fetch"
 * @return 0 or an error code
 *)

function git_remote_fetch(remote: Pgit_remote; refspecs: Pgit_strarray; opts: Pgit_fetch_options;
  reflog_message: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Prune tracking refs that are no longer present on remote.
 *
 * If callbacks are not specified then the callbacks specified to
 * `git_remote_connect` will be used (if it was called).
 *
 * @param remote the remote to prune
 * @param callbacks callbacks to use for this prune
 * @return 0 or an error code
 *)

function git_remote_prune(remote: Pgit_remote; callbacks: Pgit_remote_callbacks): Integer; cdecl; external libgit2_dll;

(**
 * Perform a push.
 *
 * If options are specified and this remote is already connected then
 * the existing remote connection options will be discarded and the
 * remote will now use the new options.
 *
 * @param remote the remote to push to
 * @param refspecs the refspecs to use for pushing. If NULL or an empty
 *                 array, the configured refspecs will be used
 * @param opts options to use for this push
 * @return 0 or an error code.
 *)

function git_remote_push(remote: Pgit_remote; refspecs: Pgit_strarray; opts: Pgit_push_options): Integer; cdecl; external libgit2_dll;

(**
 * Get the statistics structure that is filled in by the fetch operation.
 *)

function git_remote_stats(remote: Pgit_remote): Pgit_indexer_progress; cdecl; external libgit2_dll;

(**
 * Retrieve the tag auto-follow setting
 *
 * @param remote the remote to query
 * @return the auto-follow setting
 *)

function git_remote_autotag(remote: Pgit_remote): git_remote_autotag_option_t; cdecl; external libgit2_dll;

(**
 * Set the remote's tag following setting.
 *
 * The change will be made in the configuration. No loaded remotes
 * will be affected.
 *
 * @param repo the repository in which to make the change
 * @param remote the name of the remote
 * @param value the new value to take.
 * @return 0, or an error code.
 *)

function git_remote_set_autotag(repo: Pgit_repository; remote: PAnsiChar;
  Value: git_remote_autotag_option_t): Integer; cdecl; external libgit2_dll;

(**
 * Retrieve the ref-prune setting
 *
 * @param remote the remote to query
 * @return the ref-prune setting
 *)

function git_remote_prune_refs(remote: Pgit_remote): Integer; cdecl; external libgit2_dll;

(**
 * Give the remote a new name
 *
 * All remote-tracking branches and configuration settings
 * for the remote are updated.
 *
 * The new name will be checked for validity.
 * See `git_tag_create()` for rules about valid names.
 *
 * No loaded instances of a the remote with the old name will change
 * their name or their list of refspecs.
 *
 * @param problems non-default refspecs cannot be renamed and will be
 * stored here for further processing by the caller. Always free this
 * strarray on successful return.
 * @param repo the repository in which to rename
 * @param name the current name of the remote
 * @param new_name the new name the remote should bear
 * @return 0, GIT_EINVALIDSPEC, GIT_EEXISTS or an error code
 *)

function git_remote_rename(problems: Pgit_strarray; repo: Pgit_repository;
  name_, new_name: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Ensure the remote name is well-formed.
 *
 * @param valid output pointer to set with validity of given remote name
 * @param remote_name name to be checked.
 * @return 0 on success or an error code
 *)

function git_remote_name_is_valid(valid: PInteger; remote_name: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
* Delete an existing persisted remote.
*
* All remote-tracking branches and configuration settings
* for the remote will be removed.
*
* @param repo the repository in which to act
* @param name the name of the remote to delete
* @return 0 on success, or an error code.
*)

function git_remote_delete(repo: Pgit_repository; name_: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Retrieve the name of the remote's default branch
 *
 * The default branch of a repository is the branch which HEAD points
 * to. If the remote does not support reporting this information
 * directly, it performs the guess as git does; that is, if there are
 * multiple branches which point to the same commit, the first one is
 * chosen. If the master branch is a candidate, it wins.
 *
 * This function must only be called after connecting.
 *
 * @param out the buffer in which to store the reference name
 * @param remote the remote
 * @return 0, GIT_ENOTFOUND if the remote does not have any references
 * or none of them point to HEAD's commit, or an error message.
 *)

function git_remote_default_branch(out_: Pgit_buf; remote: Pgit_remote): Integer; cdecl; external libgit2_dll;

(** @}  *)

