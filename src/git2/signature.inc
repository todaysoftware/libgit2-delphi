(**
 * @file git2/signature.h
 * @brief Git signature creation
 * @defgroup git_signature Git signature creation
 * @ingroup Git
 * @{
 *)

(**
 * Create a new action signature.
 *
 * Call `git_signature_free()` to free the data.
 *
 * Note: angle brackets ('<' and '>') characters are not allowed
 * to be used in either the `name` or the `email` parameter.
 *
 * @param out new signature, in case of error NULL
 * @param name name of the person
 * @param email email of the person
 * @param time time (in seconds from epoch) when the action happened
 * @param offset timezone offset (in minutes) for the time
 * @return 0 or an error code
 *)

function git_signature_new(out_: PPgit_signature; name_, email: PAnsiChar; time: git_time_t;
  offset: Integer): Integer; cdecl; external libgit2_dll;

(**
 * Create a new action signature with a timestamp of 'now'.
 *
 * Call `git_signature_free()` to free the data.
 *
 * @param out new signature, in case of error NULL
 * @param name name of the person
 * @param email email of the person
 * @return 0 or an error code
 *)

function git_signature_now(out_: PPgit_signature; name_, email: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Create a new action signature with default user and now timestamp.
 *
 * This looks up the user.name and user.email from the configuration and
 * uses the current time as the timestamp, and creates a new signature
 * based on that information.  It will return GIT_ENOTFOUND if either the
 * user.name or user.email are not set.
 *
 * @param out new signature
 * @param repo repository pointer
 * @return 0 on success, GIT_ENOTFOUND if config is missing, or error code
 *)

function git_signature_default(out_: PPgit_signature; repo: Pgit_repository): Integer; cdecl; external libgit2_dll;

(**
 * Create a new signature by parsing the given buffer, which is
 * expected to be in the format "Real Name <email> timestamp tzoffset",
 * where `timestamp` is the number of seconds since the Unix epoch and
 * `tzoffset` is the timezone offset in `hhmm` format (note the lack
 * of a colon separator).
 *
 * @param out new signature
 * @param buf signature string
 * @return 0 on success, or an error code
 *)

function git_signature_from_buffer(out_: PPgit_signature; buf: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Create a copy of an existing signature.  All internal strings are also
 * duplicated.
 *
 * Call `git_signature_free()` to free the data.
 *
 * @param dest pointer where to store the copy
 * @param sig signature to duplicate
 * @return 0 or an error code
 *)

function git_signature_dup(dest: PPgit_signature; sig: Pgit_signature): Integer; cdecl; external libgit2_dll;

(**
 * Free an existing signature.
 *
 * Because the signature is not an opaque structure, it is legal to free it
 * manually, but be sure to free the "name" and "email" strings in addition
 * to the structure itself.
 *
 * @param sig signature to free
 *)

procedure git_signature_free(sig: Pgit_signature); cdecl; external libgit2_dll;

(** @}  *)


