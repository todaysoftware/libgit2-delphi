(**
 * @file git2/credential.h
 * @brief Git authentication & credential management
 * @defgroup git_credential Authentication & credential management
 * @ingroup Git
 * @{
  *)

(**
 * Supported credential types
 *
 * This represents the various types of authentication methods supported by
 * the library.
  *)

const
  (**
   * A vanilla user/password request
   * @see git_credential_userpass_plaintext_new
   *)
  GIT_CREDENTIAL_USERPASS_PLAINTEXT_ = (1 shl 0);
  (**
   * An SSH key-based authentication request
   * @see git_credential_ssh_key_new
   *)
  GIT_CREDENTIAL_SSH_KEY_     = (1 shl 1);
  (**
   * An SSH key-based authentication request, with a custom signature
   * @see git_credential_ssh_custom_new
   *)
  GIT_CREDENTIAL_SSH_CUSTOM_  = (1 shl 2);
  (**
   * An NTLM/Negotiate-based authentication request.
   * @see git_credential_default
   *)
  GIT_CREDENTIAL_DEFAULT_     = (1 shl 3);
  (**
   * An SSH interactive authentication request
   * @see git_credential_ssh_interactive_new
   *)
  GIT_CREDENTIAL_SSH_INTERACTIVE_ = (1 shl 4);
  (**
   * Username-only authentication request
   *
   * Used as a pre-authentication step if the underlying transport
   * (eg. SSH, with no username in its URL) does not know which username
   * to use.
   *
   * @see git_credential_username_new
   *)
  GIT_CREDENTIAL_USERNAME_    = (1 shl 5);
  (**
   * An SSH key-based authentication request
   *
   * Allows credentials to be read from memory instead of files.
   * Note that because of differences in crypto backend support, it might
   * not be functional.
   *
   * @see git_credential_ssh_key_memory_new
   *)
  GIT_CREDENTIAL_SSH_MEMORY   = (1 shl 6);
type
  git_credential_t = Integer;

  (**
   * The base structure for all credential types
   *)

  git_credential = record
  end;

  git_credential_userpass_plaintext = record
  end;

  (** Username-only credential information  *)

  git_credential_username = record
  end;

  (** A key for NTLM/Kerberos "default" credentials  *)

  git_credential_default = record
  end;

  (**
   * A ssh key from disk
   *)

  git_credential_ssh_key = record
  end;

  (**
   * Keyboard-interactive based ssh authentication
   *)

  git_credential_ssh_interactive = record
  end;

  (**
   * A key with a custom signature function
   *)

  git_credential_ssh_custom = record
  end;

  (**
   * Credential acquisition callback.
   *
   * This callback is usually involved any time another system might need
   * authentication. As such, you are expected to provide a valid
   * git_credential object back, depending on allowed_types (a
   * git_credential_t bitmask).
   *
   * Note that most authentication details are your responsibility - this
   * callback will be called until the authentication succeeds, or you report
   * an error. As such, it's easy to get in a loop if you fail to stop providing
   * the same incorrect credentials.
   *
   * @param out The newly created credential object.
   * @param url The resource for which we are demanding a credential.
   * @param username_from_url The username that was embedded in a "user\@host"
   *                          remote url, or NULL if not included.
   * @param allowed_types A bitmask stating which credential types are OK to return.
   * @param payload The payload provided when specifying this callback.
   * @return 0 for success, < 0 to indicate an error, > 0 to indicate
   *       no credential was acquired
   *)

type
  PPgit_credential = ^Pgit_credential;
  Pgit_credential = ^git_credential;
  git_credential_acquire_cb = function(out_: PPgit_credential; url, username_from_url: PAnsiChar;
    allowed_types: Cardinal; payload: Pointer): Integer; cdecl;

  (**
   * Free a credential.
   *
   * This is only necessary if you own the object; that is, if you are a
   * transport.
   *
   * @param cred the object to free
   *)

procedure git_credential_free(cred: Pgit_credential); cdecl; external libgit2_dll;

(**
 * Check whether a credential object contains username information.
 *
 * @param cred object to check
 * @return 1 if the credential object has non-NULL username, 0 otherwise
  *)

function git_credential_has_username(cred: Pgit_credential): Integer; cdecl; external libgit2_dll;

(**
 * Return the username associated with a credential object.
 *
 * @param cred object to check
 * @return the credential username, or NULL if not applicable
 *)

function git_credential_get_username(cred: Pgit_credential): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Create a new plain-text username and password credential object.
 * The supplied credential parameter will be internally duplicated.
 *
 * @param out The newly created credential object.
 * @param username The username of the credential.
 * @param password The password of the credential.
 * @return 0 for success or an error code for failure
 *)

function git_credential_userpass_plaintext_new(out_: PPgit_credential;
  username, password: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Create a "default" credential usable for Negotiate mechanisms like NTLM
 * or Kerberos authentication.
 *
 * @param out The newly created credential object.
 * @return 0 for success or an error code for failure
 *)

function git_credential_default_new(out_: PPgit_credential): Integer; cdecl; external libgit2_dll;

(**
 * Create a credential to specify a username.
 *
 * This is used with ssh authentication to query for the username if
 * none is specified in the url.
 *
 * @param out The newly created credential object.
 * @param username The username to authenticate with
 * @return 0 for success or an error code for failure
 *)

function git_credential_username_new(out_: PPgit_credential; username: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Create a new passphrase-protected ssh key credential object.
 * The supplied credential parameter will be internally duplicated.
 *
 * @param out The newly created credential object.
 * @param username username to use to authenticate
 * @param publickey The path to the public key of the credential.
 * @param privatekey The path to the private key of the credential.
 * @param passphrase The passphrase of the credential.
 * @return 0 for success or an error code for failure
 *)

function git_credential_ssh_key_new(out_: PPgit_credential;
  username, publickey, privatekey, passphrase: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Create a new ssh key credential object reading the keys from memory.
 *
 * @param out The newly created credential object.
 * @param username username to use to authenticate.
 * @param publickey The public key of the credential.
 * @param privatekey The private key of the credential.
 * @param passphrase The passphrase of the credential.
 * @return 0 for success or an error code for failure
 *)

function git_credential_ssh_key_memory_new(out_: PPgit_credential;
  username, publickey, privatekey, passphrase: PAnsiChar): Integer; cdecl; external libgit2_dll;

(*
 * If the user hasn't included libssh2.h before git2.h, we need to
 * define a few types for the callback signatures.
 *)

type
  _LIBSSH2_SESSION = record
  end;
  LIBSSH2_SESSION = _LIBSSH2_SESSION;

  _LIBSSH2_USERAUTH_KBDINT_PROMPT = record
  end;
  LIBSSH2_USERAUTH_KBDINT_PROMPT = _LIBSSH2_USERAUTH_KBDINT_PROMPT;

  _LIBSSH2_USERAUTH_KBDINT_RESPONSE = record
  end;
  LIBSSH2_USERAUTH_KBDINT_RESPONSE = _LIBSSH2_USERAUTH_KBDINT_RESPONSE;

type
  PLIBSSH2_USERAUTH_KBDINT_RESPONSE = ^LIBSSH2_USERAUTH_KBDINT_RESPONSE;
  PLIBSSH2_USERAUTH_KBDINT_PROMPT = ^LIBSSH2_USERAUTH_KBDINT_PROMPT;
  git_credential_ssh_interactive_cb = procedure(name_: PAnsiChar; name_len: Integer; instruction: PAnsiChar;
    instruction_len, num_prompts: Integer; prompts: PLIBSSH2_USERAUTH_KBDINT_PROMPT;
    responses: PLIBSSH2_USERAUTH_KBDINT_RESPONSE; abstract_: PPointer); cdecl;

  (**
   * Create a new ssh keyboard-interactive based credential object.
   * The supplied credential parameter will be internally duplicated.
   *
   * @param out The newly created credential object.
   * @param username Username to use to authenticate.
   * @param prompt_callback The callback method used for prompts.
   * @param payload Additional data to pass to the callback.
   * @return 0 for success or an error code for failure.
   *)

function git_credential_ssh_interactive_new(out_: PPgit_credential; username: PAnsiChar;
  prompt_callback: git_credential_ssh_interactive_cb; payload: Pointer): Integer; cdecl; external libgit2_dll;

(**
 * Create a new ssh key credential object used for querying an ssh-agent.
 * The supplied credential parameter will be internally duplicated.
 *
 * @param out The newly created credential object.
 * @param username username to use to authenticate
 * @return 0 for success or an error code for failure
 *)

function git_credential_ssh_key_from_agent(out_: PPgit_credential;
  username: PAnsiChar): Integer; cdecl; external libgit2_dll;
type
  PLIBSSH2_SESSION = ^LIBSSH2_SESSION;
  git_credential_sign_cb = function(session: PLIBSSH2_SESSION; sig: PPByte; sig_len: Psize_t;
    data: PByte; data_len: size_t; abstract_: PPointer): Integer; cdecl;

  (**
   * Create an ssh key credential with a custom signing function.
   *
   * This lets you use your own function to sign the challenge.
   *
   * This function and its credential type is provided for completeness
   * and wraps `libssh2_userauth_publickey()`, which is undocumented.
   *
   * The supplied credential parameter will be internally duplicated.
   *
   * @param out The newly created credential object.
   * @param username username to use to authenticate
   * @param publickey The bytes of the public key.
   * @param publickey_len The length of the public key in bytes.
   * @param sign_callback The callback method to sign the data during the challenge.
   * @param payload Additional data to pass to the callback.
   * @return 0 for success or an error code for failure
   *)

function git_credential_ssh_custom_new(out_: PPgit_credential; username, publickey: PAnsiChar;
  publickey_len: size_t; sign_callback: git_credential_sign_cb; payload: Pointer): Integer; cdecl; external libgit2_dll;

(** @}  *)



