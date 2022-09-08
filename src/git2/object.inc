(**
 * @file git2/object.h
 * @brief Git revision object management routines
 * @defgroup git_object Git revision object management routines
 * @ingroup Git
 * @{
 *)

const
  GIT_OBJECT_SIZE_MAX         = UINT64_MAX;
  (**
 * Lookup a reference to one of the objects in a repository.
 *
 * The generated reference is owned by the repository and
 * should be closed with the `git_object_free` method
 * instead of free'd manually.
 *
 * The 'type' parameter must match the type of the object
 * in the odb; the method will fail otherwise.
 * The special value 'GIT_OBJECT_ANY' may be passed to let
 * the method guess the object's type.
 *
 * @param object pointer to the looked-up object
 * @param repo the repository to look up the object
 * @param id the unique identifier for the object
 * @param type the type of the object
 * @return 0 or an error code
 *)

function git_object_lookup(object_: PPgit_object; repo: Pgit_repository; id: Pgit_oid;
  type_: git_object_t): Integer; cdecl; external libgit2_dll;

(**
 * Lookup a reference to one of the objects in a repository,
 * given a prefix of its identifier (short id).
 *
 * The object obtained will be so that its identifier
 * matches the first 'len' hexadecimal characters
 * (packets of 4 bits) of the given 'id'.
 * 'len' must be at least GIT_OID_MINPREFIXLEN, and
 * long enough to identify a unique object matching
 * the prefix; otherwise the method will fail.
 *
 * The generated reference is owned by the repository and
 * should be closed with the `git_object_free` method
 * instead of free'd manually.
 *
 * The 'type' parameter must match the type of the object
 * in the odb; the method will fail otherwise.
 * The special value 'GIT_OBJECT_ANY' may be passed to let
 * the method guess the object's type.
 *
 * @param object_out pointer where to store the looked-up object
 * @param repo the repository to look up the object
 * @param id a short identifier for the object
 * @param len the length of the short identifier
 * @param type the type of the object
 * @return 0 or an error code
 *)

function git_object_lookup_prefix(object_out: PPgit_object; repo: Pgit_repository; id: Pgit_oid;
  len: size_t; type_: git_object_t): Integer; cdecl; external libgit2_dll;

(**
 * Lookup an object that represents a tree entry.
 *
 * @param out buffer that receives a pointer to the object (which must be freed
 *            by the caller)
 * @param treeish root object that can be peeled to a tree
 * @param path relative path from the root object to the desired object
 * @param type type of object desired
 * @return 0 on success, or an error code
 *)

function git_object_lookup_bypath(out_: PPgit_object; treeish: Pgit_object; path: PAnsiChar;
  type_: git_object_t): Integer; cdecl; external libgit2_dll;

(**
 * Get the id (SHA1) of a repository object
 *
 * @param obj the repository object
 * @return the SHA1 id
 *)

function git_object_id(obj: Pgit_object): Pgit_oid; cdecl; external libgit2_dll;

(**
 * Get a short abbreviated OID string for the object
 *
 * This starts at the "core.abbrev" length (default 7 characters) and
 * iteratively extends to a longer string if that length is ambiguous.
 * The result will be unambiguous (at least until new objects are added to
 * the repository).
 *
 * @param out Buffer to write string into
 * @param obj The object to get an ID for
 * @return 0 on success, <0 for error
 *)

function git_object_short_id(out_: Pgit_buf; obj: Pgit_object): Integer; cdecl; external libgit2_dll;

(**
 * Get the object type of an object
 *
 * @param obj the repository object
 * @return the object's type
 *)

function git_object_type(obj: Pgit_object): git_object_t; cdecl; external libgit2_dll;

(**
 * Get the repository that owns this object
 *
 * Freeing or calling `git_repository_close` on the
 * returned pointer will invalidate the actual object.
 *
 * Any other operation may be run on the repository without
 * affecting the object.
 *
 * @param obj the object
 * @return the repository who owns this object
 *)

function git_object_owner(obj: Pgit_object): Pgit_repository; cdecl; external libgit2_dll;

(**
 * Close an open object
 *
 * This method instructs the library to close an existing
 * object; note that git_objects are owned and cached by the repository
 * so the object may or may not be freed after this library call,
 * depending on how aggressive is the caching mechanism used
 * by the repository.
 *
 * IMPORTANT:
 * It *is* necessary to call this method when you stop using
 * an object. Failure to do so will cause a memory leak.
 *
 * @param object the object to close
 *)

procedure git_object_free(object_: Pgit_object); cdecl; external libgit2_dll;

(**
 * Convert an object type to its string representation.
 *
 * The result is a pointer to a string in static memory and
 * should not be free()'ed.
 *
 * @param type object type to convert.
 * @return the corresponding string representation.
 *)

function git_object_type2string(type_: git_object_t): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Convert a string object type representation to it's git_object_t.
 *
 * @param str the string to convert.
 * @return the corresponding git_object_t.
 *)

function git_object_string2type(str: PAnsiChar): git_object_t; cdecl; external libgit2_dll;

(**
 * Determine if the given git_object_t is a valid loose object type.
 *
 * @param type object type to test.
 * @return true if the type represents a valid loose object type,
 * false otherwise.
 *)

function git_object_typeisloose(type_: git_object_t): Integer; cdecl; external libgit2_dll;

(**
 * Recursively peel an object until an object of the specified type is met.
 *
 * If the query cannot be satisfied due to the object model,
 * GIT_EINVALIDSPEC will be returned (e.g. trying to peel a blob to a
 * tree).
 *
 * If you pass `GIT_OBJECT_ANY` as the target type, then the object will
 * be peeled until the type changes. A tag will be peeled until the
 * referenced object is no longer a tag, and a commit will be peeled
 * to a tree. Any other object type will return GIT_EINVALIDSPEC.
 *
 * If peeling a tag we discover an object which cannot be peeled to
 * the target type due to the object model, GIT_EPEEL will be
 * returned.
 *
 * You must free the returned object.
 *
 * @param peeled Pointer to the peeled git_object
 * @param object The object to be processed
 * @param target_type The type of the requested object (a GIT_OBJECT_ value)
 * @return 0 on success, GIT_EINVALIDSPEC, GIT_EPEEL, or an error code
 *)

function git_object_peel(peeled: PPgit_object; object_: Pgit_object;
  target_type: git_object_t): Integer; cdecl; external libgit2_dll;

(**
 * Create an in-memory copy of a Git object. The copy must be
 * explicitly free'd or it will leak.
 *
 * @param dest Pointer to store the copy of the object
 * @param source Original object to copy
 * @return 0 or an error code
 *)

function git_object_dup(dest: PPgit_object; source: Pgit_object): Integer; cdecl; external libgit2_dll;

(**
 * Analyzes a buffer of raw object content and determines its validity.
 * Tree, commit, and tag objects will be parsed and ensured that they
 * are valid, parseable content.  (Blobs are always valid by definition.)
 * An error message will be set with an informative message if the object
 * is not valid.
 *
 * @warning This function is experimental and its signature may change in
 * the future.
 *
 * @param valid Output pointer to set with validity of the object content
 * @param buf The contents to validate
 * @param len The length of the buffer
 * @param type The type of the object in the buffer
 * @return 0 on success or an error code
 *)

function git_object_rawcontent_is_valid(valid: PInteger; buf: PAnsiChar; len: size_t;
  type_: git_object_t): Integer; cdecl; external libgit2_dll;

(** @}  *)



