(**
 * @file git2/message.h
 * @brief Git message management routines
 * @ingroup Git
 * @{
 *)

(**
 * Clean up excess whitespace and make sure there is a trailing newline in the message.
 *
 * Optionally, it can remove lines which start with the comment character.
 *
 * @param out The user-allocated git_buf which will be filled with the
 *     cleaned up message.
 *
 * @param message The message to be prettified.
 *
 * @param strip_comments Non-zero to remove comment lines, 0 to leave them in.
 *
 * @param comment_char Comment character. Lines starting with this character
 * are considered to be comments and removed if `strip_comments` is non-zero.
 *
 * @return 0 or an error code.
 *)

function git_message_prettify(out_: Pgit_buf; message: PAnsiChar; strip_comments: Integer;
  comment_char: AnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Represents a single git message trailer.
 *)

type
  git_message_trailer = record
    key: PAnsiChar;
    Value: PAnsiChar;
  end;
  Pgit_message_trailer = ^git_message_trailer;

  (**
   * Represents an array of git message trailers.
   *
   * Struct members under the private comment are private, subject to change
   * and should not be used by callers.
   *)

type
  git_message_trailer_array = record
    trailers: Pgit_message_trailer;
    Count: size_t;
    (* private  *)
    _trailer_block: PAnsiChar;
  end;
  Pgit_message_trailer_array = ^git_message_trailer_array;

  (**
   * Parse trailers out of a message, filling the array pointed to by +arr+.
   *
   * Trailers are key/value pairs in the last paragraph of a message, not
   * including any patches or conflicts that may be present.
   *
   * @param arr A pre-allocated git_message_trailer_array struct to be filled in
   *            with any trailers found during parsing.
   * @param message The message to be parsed
   * @return 0 on success, or non-zero on error.
   *)

function git_message_trailers(arr: Pgit_message_trailer_array; message: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Clean's up any allocated memory in the git_message_trailer_array filled by
 * a call to git_message_trailers.
 *
 * @param arr The trailer to free.
 *)

procedure git_message_trailer_array_free(arr: Pgit_message_trailer_array); cdecl; external libgit2_dll;

(** @}  *)



