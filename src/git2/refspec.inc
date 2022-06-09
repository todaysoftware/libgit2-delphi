(**
 * @file git2/refspec.h
 * @brief Git refspec attributes
 * @defgroup git_refspec Git refspec attributes
 * @ingroup Git
 * @{
 *)

(**
 * Parse a given refspec string
 *
 * @param refspec a pointer to hold the refspec handle
 * @param input the refspec string
 * @param is_fetch is this a refspec for a fetch
 * @return 0 if the refspec string could be parsed, -1 otherwise
  *)

function git_refspec_parse(refspec: PPgit_refspec; input: PAnsiChar; is_fetch: Integer): Integer; cdecl; external libgit2_dll;

(**
 * Free a refspec object which has been created by git_refspec_parse
 *
 * @param refspec the refspec object
 *)

procedure git_refspec_free(refspec: Pgit_refspec); cdecl; external libgit2_dll;

(**
 * Get the source specifier
 *
 * @param refspec the refspec
 * @return the refspec's source specifier
 *)

function git_refspec_src(refspec: Pgit_refspec): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Get the destination specifier
 *
 * @param refspec the refspec
 * @return the refspec's destination specifier
 *)

function git_refspec_dst(refspec: Pgit_refspec): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Get the refspec's string
 *
 * @param refspec the refspec
 * @returns the refspec's original string
 *)

function git_refspec_string(refspec: Pgit_refspec): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Get the force update setting
 *
 * @param refspec the refspec
 * @return 1 if force update has been set, 0 otherwise
 *)

function git_refspec_force(refspec: Pgit_refspec): Integer; cdecl; external libgit2_dll;

(**
 * Get the refspec's direction.
 *
 * @param spec refspec
 * @return GIT_DIRECTION_FETCH or GIT_DIRECTION_PUSH
 *)

function git_refspec_direction(spec: Pgit_refspec): git_direction; cdecl; external libgit2_dll;

(**
 * Check if a refspec's source descriptor matches a reference
 *
 * @param refspec the refspec
 * @param refname the name of the reference to check
 * @return 1 if the refspec matches, 0 otherwise
 *)

function git_refspec_src_matches(refspec: Pgit_refspec; refname: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Check if a refspec's destination descriptor matches a reference
 *
 * @param refspec the refspec
 * @param refname the name of the reference to check
 * @return 1 if the refspec matches, 0 otherwise
 *)

function git_refspec_dst_matches(refspec: Pgit_refspec; refname: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Transform a reference to its target following the refspec's rules
 *
 * @param out where to store the target name
 * @param spec the refspec
 * @param name the name of the reference to transform
 * @return 0, GIT_EBUFS or another error
 *)

function git_refspec_transform(out_: Pgit_buf; spec: Pgit_refspec; name_: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Transform a target reference to its source reference following the refspec's rules
 *
 * @param out where to store the source reference name
 * @param spec the refspec
 * @param name the name of the reference to transform
 * @return 0, GIT_EBUFS or another error
 *)

function git_refspec_rtransform(out_: Pgit_buf; spec: Pgit_refspec; name_: PAnsiChar): Integer; cdecl; external libgit2_dll;


