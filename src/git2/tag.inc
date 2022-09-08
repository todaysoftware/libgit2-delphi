(**
 * @file git2/tag.h
 * @brief Git tag parsing routines
 * @defgroup git_tag Git tag management
 * @ingroup Git
 * @{
 *)

(**
 * Lookup a tag object from the repository.
 *
 * @param out pointer to the looked up tag
 * @param repo the repo to use when locating the tag.
 * @param id identity of the tag to locate.
 * @return 0 or an error code
 *)

function git_tag_lookup(out_: PPgit_tag; repo: Pgit_repository; id: Pgit_oid): Integer; cdecl; external libgit2_dll;

(**
 * Lookup a tag object from the repository,
 * given a prefix of its identifier (short id).
 *
 * @see git_object_lookup_prefix
 *
 * @param out pointer to the looked up tag
 * @param repo the repo to use when locating the tag.
 * @param id identity of the tag to locate.
 * @param len the length of the short identifier
 * @return 0 or an error code
 *)

function git_tag_lookup_prefix(out_: PPgit_tag; repo: Pgit_repository; id: Pgit_oid;
  len: size_t): Integer; cdecl; external libgit2_dll;

(**
 * Close an open tag
 *
 * You can no longer use the git_tag pointer after this call.
 *
 * IMPORTANT: You MUST call this method when you are through with a tag to
 * release memory. Failure to do so will cause a memory leak.
 *
 * @param tag the tag to close
 *)

procedure git_tag_free(tag: Pgit_tag); cdecl; external libgit2_dll;

(**
 * Get the id of a tag.
 *
 * @param tag a previously loaded tag.
 * @return object identity for the tag.
 *)

function git_tag_id(tag: Pgit_tag): Pgit_oid; cdecl; external libgit2_dll;

(**
 * Get the repository that contains the tag.
 *
 * @param tag A previously loaded tag.
 * @return Repository that contains this tag.
 *)

function git_tag_owner(tag: Pgit_tag): Pgit_repository; cdecl; external libgit2_dll;

(**
 * Get the tagged object of a tag
 *
 * This method performs a repository lookup for the
 * given object and returns it
 *
 * @param target_out pointer where to store the target
 * @param tag a previously loaded tag.
 * @return 0 or an error code
 *)

function git_tag_target(target_out: PPgit_object; tag: Pgit_tag): Integer; cdecl; external libgit2_dll;

(**
 * Get the OID of the tagged object of a tag
 *
 * @param tag a previously loaded tag.
 * @return pointer to the OID
 *)

function git_tag_target_id(tag: Pgit_tag): Pgit_oid; cdecl; external libgit2_dll;

(**
 * Get the type of a tag's tagged object
 *
 * @param tag a previously loaded tag.
 * @return type of the tagged object
 *)

function git_tag_target_type(tag: Pgit_tag): git_object_t; cdecl; external libgit2_dll;

(**
 * Get the name of a tag
 *
 * @param tag a previously loaded tag.
 * @return name of the tag
 *)

function git_tag_name(tag: Pgit_tag): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Get the tagger (author) of a tag
 *
 * @param tag a previously loaded tag.
 * @return reference to the tag's author or NULL when unspecified
 *)

function git_tag_tagger(tag: Pgit_tag): Pgit_signature; cdecl; external libgit2_dll;

(**
 * Get the message of a tag
 *
 * @param tag a previously loaded tag.
 * @return message of the tag or NULL when unspecified
 *)

function git_tag_message(tag: Pgit_tag): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Create a new tag in the repository from an object
 *
 * A new reference will also be created pointing to
 * this tag object. If `force` is true and a reference
 * already exists with the given name, it'll be replaced.
 *
 * The message will not be cleaned up. This can be achieved
 * through `git_message_prettify()`.
 *
 * The tag name will be checked for validity. You must avoid
 * the characters '~', '^', ':', '\\', '?', '[', and '*', and the
 * sequences ".." and "@{" which have special meaning to revparse.
 *
 * @param oid Pointer where to store the OID of the
 * newly created tag. If the tag already exists, this parameter
 * will be the oid of the existing tag, and the function will
 * return a GIT_EEXISTS error code.
 *
 * @param repo Repository where to store the tag
 *
 * @param tag_name Name for the tag; this name is validated
 * for consistency. It should also not conflict with an
 * already existing tag name
 *
 * @param target Object to which this tag points. This object
 * must belong to the given `repo`.
 *
 * @param tagger Signature of the tagger for this tag, and
 * of the tagging time
 *
 * @param message Full message for this tag
 *
 * @param force Overwrite existing references
 *
 * @return 0 on success, GIT_EINVALIDSPEC or an error code
 *	A tag object is written to the ODB, and a proper reference
 *	is written in the /refs/tags folder, pointing to it
 *)

function git_tag_create(oid: Pgit_oid; repo: Pgit_repository; tag_name: PAnsiChar; target: Pgit_object;
  tagger: Pgit_signature; message: PAnsiChar; force: Integer): Integer; cdecl; external libgit2_dll;

(**
 * Create a new tag in the object database pointing to a git_object
 *
 * The message will not be cleaned up. This can be achieved
 * through `git_message_prettify()`.
 *
 * @param oid Pointer where to store the OID of the
 * newly created tag
 *
 * @param repo Repository where to store the tag
 *
 * @param tag_name Name for the tag
 *
 * @param target Object to which this tag points. This object
 * must belong to the given `repo`.
 *
 * @param tagger Signature of the tagger for this tag, and
 * of the tagging time
 *
 * @param message Full message for this tag
 *
 * @return 0 on success or an error code
 *)

function git_tag_annotation_create(oid: Pgit_oid; repo: Pgit_repository; tag_name: PAnsiChar;
  target: Pgit_object; tagger: Pgit_signature; message: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Create a new tag in the repository from a buffer
 *
 * @param oid Pointer where to store the OID of the newly created tag
 * @param repo Repository where to store the tag
 * @param buffer Raw tag data
 * @param force Overwrite existing tags
 * @return 0 on success; error code otherwise
 *)

function git_tag_create_from_buffer(oid: Pgit_oid; repo: Pgit_repository; buffer: PAnsiChar;
  force: Integer): Integer; cdecl; external libgit2_dll;

(**
 * Create a new lightweight tag pointing at a target object
 *
 * A new direct reference will be created pointing to
 * this target object. If `force` is true and a reference
 * already exists with the given name, it'll be replaced.
 *
 * The tag name will be checked for validity.
 * See `git_tag_create()` for rules about valid names.
 *
 * @param oid Pointer where to store the OID of the provided
 * target object. If the tag already exists, this parameter
 * will be filled with the oid of the existing pointed object
 * and the function will return a GIT_EEXISTS error code.
 *
 * @param repo Repository where to store the lightweight tag
 *
 * @param tag_name Name for the tag; this name is validated
 * for consistency. It should also not conflict with an
 * already existing tag name
 *
 * @param target Object to which this tag points. This object
 * must belong to the given `repo`.
 *
 * @param force Overwrite existing references
 *
 * @return 0 on success, GIT_EINVALIDSPEC or an error code
 *	A proper reference is written in the /refs/tags folder,
 * pointing to the provided target object
 *)

function git_tag_create_lightweight(oid: Pgit_oid; repo: Pgit_repository; tag_name: PAnsiChar;
  target: Pgit_object; force: Integer): Integer; cdecl; external libgit2_dll;

(**
 * Delete an existing tag reference.
 *
 * The tag name will be checked for validity.
 * See `git_tag_create()` for rules about valid names.
 *
 * @param repo Repository where lives the tag
 *
 * @param tag_name Name of the tag to be deleted;
 * this name is validated for consistency.
 *
 * @return 0 on success, GIT_EINVALIDSPEC or an error code
 *)

function git_tag_delete(repo: Pgit_repository; tag_name: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Fill a list with all the tags in the Repository
 *
 * The string array will be filled with the names of the
 * matching tags; these values are owned by the user and
 * should be free'd manually when no longer needed, using
 * `git_strarray_free`.
 *
 * @param tag_names Pointer to a git_strarray structure where
 *		the tag names will be stored
 * @param repo Repository where to find the tags
 * @return 0 or an error code
  *)

function git_tag_list(tag_names: Pgit_strarray; repo: Pgit_repository): Integer; cdecl; external libgit2_dll;

(**
 * Fill a list with all the tags in the Repository
 * which name match a defined pattern
 *
 * If an empty pattern is provided, all the tags
 * will be returned.
 *
 * The string array will be filled with the names of the
 * matching tags; these values are owned by the user and
 * should be free'd manually when no longer needed, using
 * `git_strarray_free`.
 *
 * @param tag_names Pointer to a git_strarray structure where
 *		the tag names will be stored
 * @param pattern Standard fnmatch pattern
 * @param repo Repository where to find the tags
 * @return 0 or an error code
 *)

function git_tag_list_match(tag_names: Pgit_strarray; pattern: PAnsiChar;
  repo: Pgit_repository): Integer; cdecl; external libgit2_dll;

(**
 * Callback used to iterate over tag names
 *
 * @see git_tag_foreach
 *
 * @param name The tag name
 * @param oid The tag's OID
 * @param payload Payload passed to git_tag_foreach
 * @return non-zero to terminate the iteration
 *)

type
  git_tag_foreach_cb = function(name_: PAnsiChar; oid: Pgit_oid; payload: Pointer): Integer; cdecl;

  (**
 * Call callback `cb' for each tag in the repository
 *
 * @param repo Repository
 * @param callback Callback function
 * @param payload Pointer to callback data (optional)
 *)

function git_tag_foreach(repo: Pgit_repository; callback: git_tag_foreach_cb;
  payload: Pointer): Integer; cdecl; external libgit2_dll;

(**
 * Recursively peel a tag until a non tag git_object is found
 *
 * The retrieved `tag_target` object is owned by the repository
 * and should be closed with the `git_object_free` method.
 *
 * @param tag_target_out Pointer to the peeled git_object
 * @param tag The tag to be processed
 * @return 0 or an error code
 *)

function git_tag_peel(tag_target_out: PPgit_object; tag: Pgit_tag): Integer; cdecl; external libgit2_dll;

(**
 * Create an in-memory copy of a tag. The copy must be explicitly
 * free'd or it will leak.
 *
 * @param out Pointer to store the copy of the tag
 * @param source Original tag to copy
 * @return 0
 *)

function git_tag_dup(out_: PPgit_tag; source: Pgit_tag): Integer; cdecl; external libgit2_dll;

(**
 * Determine whether a tag name is valid, meaning that (when prefixed
 * with `refs/tags/`) that it is a valid reference name, and that any
 * additional tag name restrictions are imposed (eg, it cannot start
 * with a `-`).
 *
 * @param valid output pointer to set with validity of given tag name
 * @param name a tag name to test
 * @return 0 on success or an error code
 *)

function git_tag_name_is_valid(valid: PInteger; const name_: PAnsiChar): Integer; cdecl; external libgit2_dll;

(** @}  *)



