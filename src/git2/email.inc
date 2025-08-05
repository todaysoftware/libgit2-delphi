(**
 * @file git2/email.h
 * @brief Produce email-ready patches
 * @ingroup Git
 * @{
 *)

 (**
 * Formatting options for diff e-mail generation
 *)

const
  (** Normal patch, the default  *)
  GIT_EMAIL_CREATE_DEFAULT    = 0;
  (** do not include patch numbers in the subject prefix. *)
  GIT_EMAIL_CREATE_OMIT_NUMBERS = 1 shl 0;

  (**
   * Include numbers in the subject prefix even when the
   * patch is for a single commit (1/1).
   *)
  GIT_EMAIL_CREATE_ALWAYS_NUMBER = 1 shl 1;

  (** Do not perform rename or similarity detection. *)
  GIT_EMAIL_CREATE_NO_RENAMES = 1 shl 2;
type
  git_email_create_flags_t = Integer;

  (**
   * Options for controlling the formatting of the generated e-mail.
   *)

type
  git_email_create_options = record
    version: Cardinal;
    (** see `git_email_create_flags_t` above  *)
    flags: uint32_t;
    (** Options to use when creating diffs *)
    diff_opts: git_diff_options;

    (** Options for finding similarities within diffs *)
    diff_find_opts: git_diff_find_options;

    (**
     * The subject prefix, by default "PATCH".  If set to an empty
     * string ("") then only the patch numbers will be shown in the
     * prefix.  If the subject_prefix is empty and patch numbers
     * are not being shown, the prefix will be omitted entirely.
     *)
    subject_prefix: PAnsiChar;

    (**
     * The starting patch number; this cannot be 0.  By default,
     * this is 1.
     *)
    start_number: size_t;

    (** The "re-roll" number.  By default, there is no re-roll. *)
    reroll_number: size_t;

    (** This patch number  *)
    patch_no: size_t;
    (** Total number of patches in this series  *)
    total_patches: size_t;
    (** id to use for the commit  *)
    id: Pgit_oid;
    (** Summary of the change  *)
    summary: PAnsiChar;
    (** Commit message's body  *)
    body: PAnsiChar;
    (** Author of the change  *)
    author: Pgit_signature;
  end;
  Pgit_email_create_options = ^git_email_create_options;

const
  (** Current version for the `git_email_create_options` structure *)
  GIT_EMAIL_CREATE_OPTIONS_VERSION = 1;
  (** Static constructor for `git_email_create_options`
   *
   * By default, our options include rename detection and binary
   * diffs to match `git format-patch`.
   *)
  (*GIT_EMAIL_CREATE_OPTIONS_INIT =
  { \
   GIT_EMAIL_CREATE_OPTIONS_VERSION, \
   GIT_EMAIL_CREATE_DEFAULT, \
   { GIT_DIFF_OPTIONS_VERSION, GIT_DIFF_SHOW_BINARY, GIT_SUBMODULE_IGNORE_UNSPECIFIED, {NULL,0}, NULL, NULL, NULL, 3 }, \
   GIT_DIFF_FIND_OPTIONS_INIT \
  }
  *)

(**
 * Create a diff for a commit in mbox format for sending via email.
 * The commit must not be a merge commit.
 *
 * @param out buffer to store the e-mail patch in
 * @param commit commit to create a patch for
 * @param opts email creation options
 * @return 0 or an error code
 *)

function git_email_create_from_commit(_out: Pgit_buf; commit: Pgit_commit;
  opts: Pgit_email_create_options): Integer; cdecl; external libgit2_dll {$IFDEF LIBGIT2_DLL_DELAY_LOAD}delayed{$ENDIF};

(** @}  *)



