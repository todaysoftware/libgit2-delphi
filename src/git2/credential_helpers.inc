(**
 * @file git2/credential_helpers.h
 * @brief Utility functions for credential management
 * @defgroup git_credential_helpers credential management helpers
 * @ingroup Git
 * @{
  *)

(**
 * Payload for git_credential_userpass_plaintext.
 *)

type
  git_credential_userpass_payload = record
    username: PAnsiChar;
    password: PAnsiChar;
  end;

  (**
   * Stock callback usable as a git_credential_acquire_cb.  This calls
   * git_cred_userpass_plaintext_new unless the protocol has not specified
   * `GIT_CREDENTIAL_USERPASS_PLAINTEXT` as an allowed type.
   *
   * @param out The newly created credential object.
   * @param url The resource for which we are demanding a credential.
   * @param user_from_url The username that was embedded in a "user\@host"
   *                          remote url, or NULL if not included.
   * @param allowed_types A bitmask stating which credential types are OK to return.
   * @param payload The payload provided when specifying this callback.  (This is
   *        interpreted as a `git_credential_userpass_payload*`.)
   *)

function git_credential_userpass(out_: PPgit_credential; url, user_from_url: PAnsiChar;
  allowed_types: Cardinal; payload: Pointer): Integer; cdecl; external libgit2_dll;

(** @}  *)



