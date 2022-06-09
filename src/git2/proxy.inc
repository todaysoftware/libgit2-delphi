(**
 * The type of proxy to use.
 *)

const
  (**
   * Do not attempt to connect through a proxy
   *
   * If built against libcurl, it itself may attempt to connect
   * to a proxy if the environment variables specify it.
   *)
  GIT_PROXY_NONE              = 0;
  (**
   * Try to auto-detect the proxy from the git configuration.
   *)
  GIT_PROXY_AUTO              = 1;
  (**
   * Connect via the URL given in the options
   *)
  GIT_PROXY_SPECIFIED         = 2;
type
  git_proxy_t = Integer;

  (**
   * Options for connecting through a proxy
   *
   * Note that not all types may be supported, depending on the platform
   * and compilation options.
   *)

  git_proxy_options = record
    version: Cardinal;
    (**
     * The type of proxy to use, by URL, auto-detect.
     *)
    type_: git_proxy_t;
    (**
     * The URL of the proxy.
     *)
    url: PAnsiChar;
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
     * Payload to be provided to the credentials and certificate
     * check callbacks.
     *)
    payload: Pointer;
  end;
  Pgit_proxy_options = ^git_proxy_options;

const
  GIT_PROXY_OPTIONS_VERSION   = 1;
  //GIT_PROXY_OPTIONS_INIT = { GIT_PROXY_OPTIONS_VERSION };
  (**
   * Initialize git_proxy_options structure
   *
   * Initializes a `git_proxy_options` with default values. Equivalent to
   * creating an instance with `GIT_PROXY_OPTIONS_INIT`.
   *
   * @param opts The `git_proxy_options` struct to initialize.
   * @param version The struct version; pass `GIT_PROXY_OPTIONS_VERSION`.
   * @return Zero on success; -1 on failure.
   *)

function git_proxy_options_init(opts: Pgit_proxy_options; version: Cardinal): Integer; cdecl; external libgit2_dll;



