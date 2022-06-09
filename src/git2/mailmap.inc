(**
 * @file git2/mailmap.h
 * @brief Mailmap parsing routines
 * @defgroup git_mailmap Git mailmap routines
 * @ingroup Git
 * @{
 *)

(**
 * Allocate a new mailmap object.
 *
 * This object is empty, so you'll have to add a mailmap file before you can do
 * anything with it. The mailmap must be freed with 'git_mailmap_free'.
 *
 * @param out pointer to store the new mailmap
 * @return 0 on success, or an error code
 *)

function git_mailmap_new(out_: PPgit_mailmap): Integer; cdecl; external libgit2_dll;

(**
 * Free the mailmap and its associated memory.
 *
 * @param mm the mailmap to free
 *)

procedure git_mailmap_free(mm: Pgit_mailmap); cdecl; external libgit2_dll;

(**
 * Add a single entry to the given mailmap object. If the entry already exists,
 * it will be replaced with the new entry.
 *
 * @param mm mailmap to add the entry to
 * @param real_name the real name to use, or NULL
 * @param real_email the real email to use, or NULL
 * @param replace_name the name to replace, or NULL
 * @param replace_email the email to replace
 * @return 0 on success, or an error code
 *)

function git_mailmap_add_entry(mm: Pgit_mailmap;
  real_name, real_email, replace_name, replace_email: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Create a new mailmap instance containing a single mailmap file
 *
 * @param out pointer to store the new mailmap
 * @param buf buffer to parse the mailmap from
 * @param len the length of the input buffer
 * @return 0 on success, or an error code
 *)

function git_mailmap_from_buffer(out_: PPgit_mailmap; buf: PAnsiChar; len: size_t): Integer; cdecl; external libgit2_dll;

(**
 * Create a new mailmap instance from a repository, loading mailmap files based
 * on the repository's configuration.
 *
 * Mailmaps are loaded in the following order:
 *  1. '.mailmap' in the root of the repository's working directory, if present.
 *  2. The blob object identified by the 'mailmap.blob' config entry, if set.
 * 	   [NOTE: 'mailmap.blob' defaults to 'HEAD:.mailmap' in bare repositories]
 *  3. The path in the 'mailmap.file' config entry, if set.
 *
 * @param out pointer to store the new mailmap
 * @param repo repository to load mailmap information from
 * @return 0 on success, or an error code
 *)

function git_mailmap_from_repository(out_: PPgit_mailmap; repo: Pgit_repository): Integer; cdecl; external libgit2_dll;

(**
 * Resolve a name and email to the corresponding real name and email.
 *
 * The lifetime of the strings are tied to `mm`, `name`, and `email` parameters.
 *
 * @param real_name pointer to store the real name
 * @param real_email pointer to store the real email
 * @param mm the mailmap to perform a lookup with (may be NULL)
 * @param name the name to look up
 * @param email the email to look up
 * @return 0 on success, or an error code
 *)

function git_mailmap_resolve(real_name, real_email: PPAnsiChar; mm: Pgit_mailmap;
  name_, email: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Resolve a signature to use real names and emails with a mailmap.
 *
 * Call `git_signature_free()` to free the data.
 *
 * @param out new signature
 * @param mm mailmap to resolve with
 * @param sig signature to resolve
 * @return 0 or an error code
 *)

function git_mailmap_resolve_signature(out_: PPgit_signature; mm: Pgit_mailmap;
  sig: Pgit_signature): Integer; cdecl; external libgit2_dll;

(** @}  *)


