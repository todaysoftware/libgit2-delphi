(**
 * @file git2/attr.h
 * @brief Git attribute management routines
 * @defgroup git_attr Git attribute management routines
 * @ingroup Git
 * @{
  *)

(**
 * GIT_ATTR_TRUE checks if an attribute is set on.  In core git
 * parlance, this the value for "Set" attributes.
 *
 * For example, if the attribute file contains:
 *
 *    *.c foo
 *
 * Then for file `xyz.c` looking up attribute "foo" gives a value for
 * which `GIT_ATTR_TRUE(value)` is true.
  *)

function GIT_ATTR_IS_TRUE(attr: PAnsiChar): Boolean;

(**
* GIT_ATTR_FALSE checks if an attribute is set off.  In core git
* parlance, this is the value for attributes that are "Unset" (not to
* be confused with values that a "Unspecified").
*
* For example, if the attribute file contains:
*
*    *.h -foo
*
* Then for file `zyx.h` looking up attribute "foo" gives a value for
* which `GIT_ATTR_FALSE(value)` is true.
*)

function GIT_ATTR_IS_FALSE(attr: PAnsiChar): Boolean;

(**
* GIT_ATTR_UNSPECIFIED checks if an attribute is unspecified.  This
* may be due to the attribute not being mentioned at all or because
* the attribute was explicitly set unspecified via the `!` operator.
*
* For example, if the attribute file contains:
*
*    *.c foo
*    *.h -foo
*    onefile.c !foo
*
* Then for `onefile.c` looking up attribute "foo" yields a value with
* `GIT_ATTR_UNSPECIFIED(value)` of true.  Also, looking up "foo" on
* file `onefile.rb` or looking up "bar" on any file will all give
* `GIT_ATTR_UNSPECIFIED(value)` of true.
*)

function GIT_ATTR_IS_UNSPECIFIED(attr: PAnsiChar): Boolean;

(**
* GIT_ATTR_HAS_VALUE checks if an attribute is set to a value (as
* opposed to TRUE, FALSE or UNSPECIFIED).  This would be the case if
* for a file with something like:
*
*    *.txt eol=lf
*
* Given this, looking up "eol" for `onefile.txt` will give back the
* string "lf" and `GIT_ATTR_SET_TO_VALUE(attr)` will return true.
*)

function GIT_ATTR_HAS_VALUE(attr: PAnsiChar): Boolean;

(**
* Possible states for an attribute
*)

const
  GIT_ATTR_VALUE_UNSPECIFIED  = 0; (**< The attribute has been left unspecified  *)
  GIT_ATTR_VALUE_TRUE         = 1; (**< The attribute has been set  *)
  GIT_ATTR_VALUE_FALSE        = 2; (**< The attribute has been unset  *)
  GIT_ATTR_VALUE_STRING       = 3; (**< This attribute has a value  *)
type
  git_attr_value_t = Integer;

  (**
  * Return the value type for a given attribute.
  *
  * This can be either `TRUE`, `FALSE`, `UNSPECIFIED` (if the attribute
  * was not set at all), or `VALUE`, if the attribute was set to an
  * actual string.
  *
  * If the attribute has a `VALUE` string, it can be accessed normally
  * as a NULL-terminated C string.
  *
  * @param attr The attribute
  * @return the value type for the attribute
  *)

function git_attr_value(attr: PAnsiChar): git_attr_value_t; cdecl; external libgit2_dll;

(**
 * Check attribute flags: Reading values from index and working directory.
 *
 * When checking attributes, it is possible to check attribute files
 * in both the working directory (if there is one) and the index (if
 * there is one).  You can explicitly choose where to check and in
 * which order using the following flags.
 *
 * Core git usually checks the working directory then the index,
 * except during a checkout when it checks the index first.  It will
 * use index only for creating archives or for a bare repo (if an
 * index has been specified for the bare repo).
  *)

const
  GIT_ATTR_CHECK_FILE_THEN_INDEX = 0;
  GIT_ATTR_CHECK_INDEX_THEN_FILE = 1;
  GIT_ATTR_CHECK_INDEX_ONLY      = 2;
  (**
 * Check attribute flags: controlling extended attribute behavior.
 *
 * Normally, attribute checks include looking in the /etc (or system
 * equivalent) directory for a `gitattributes` file.  Passing the
 * `GIT_ATTR_CHECK_NO_SYSTEM` flag will cause attribute checks to
 * ignore that file.
 *
 * Passing the `GIT_ATTR_CHECK_INCLUDE_HEAD` flag will use attributes
 * from a `.gitattributes` file in the repository at the HEAD revision.
 *
 * Passing the `GIT_ATTR_CHECK_INCLUDE_COMMIT` flag will use attributes
 * from a `.gitattributes` file in a specific commit.
  *)

  GIT_ATTR_CHECK_NO_SYSTEM    = (1 shl 2);
  GIT_ATTR_CHECK_INCLUDE_HEAD = (1 shl 3);
  GIT_ATTR_CHECK_INCLUDE_COMMIT = (1 shl 4);
  (**
  * An options structure for querying attributes.
  *)
type
  git_attr_options = record
    version: Cardinal;
    (** A combination of GIT_ATTR_CHECK flags *)
    flags: Cardinal;

    {$IFDEF GIT_DEPRECATE_HARD}
    reserved: Pointer;
    {$ELSE}
    commit_id: Pgit_oid;
    {$ENDIF}
    (**
     * The commit to load attributes from, when
     * `GIT_ATTR_CHECK_INCLUDE_COMMIT` is specified.
     *)
    attr_commit_id: git_oid;
  end;
  Pgit_attr_options = ^git_attr_options;

const
  GIT_ATTR_OPTIONS_VERSION    = 1;
  //GIT_ATTR_OPTIONS_INIT {GIT_ATTR_OPTIONS_VERSION}

  (**
  * Look up the value of one git attribute for path.
  *
  * @param value_out Output of the value of the attribute.  Use the GIT_ATTR_...
  *             macros to test for TRUE, FALSE, UNSPECIFIED, etc. or just
  *             use the string value for attributes set to a value.  You
  *             should NOT modify or free this value.
  * @param repo The repository containing the path.
  * @param flags A combination of GIT_ATTR_CHECK... flags.
  * @param path The path to check for attributes.  Relative paths are
  *             interpreted relative to the repo root.  The file does
  *             not have to exist, but if it does not, then it will be
  *             treated as a plain file (not a directory).
  * @param name The name of the attribute to look up.
  * @return 0 or an error code.
  *)

function git_attr_get(value_out: PPAnsiChar; repo: Pgit_repository; flags: uint32_t; path,
  name_: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Look up the value of one git attribute for path with extended options.
 *
 * @param value_out Output of the value of the attribute.  Use the GIT_ATTR_...
 *             macros to test for TRUE, FALSE, UNSPECIFIED, etc. or just
 *             use the string value for attributes set to a value.  You
 *             should NOT modify or free this value.
 * @param repo The repository containing the path.
 * @param opts The `git_attr_options` to use when querying these attributes.
 * @param path The path to check for attributes.  Relative paths are
 *             interpreted relative to the repo root.  The file does
 *             not have to exist, but if it does not, then it will be
 *             treated as a plain file (not a directory).
 * @param name The name of the attribute to look up.
 * @return 0 or an error code.
 *)

function git_attr_get_ext(value_out: PPAnsiChar; repo: Pgit_repository; opts: Pgit_attr_options;
  path, name_: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Look up a list of git attributes for path.
 *
 * Use this if you have a known list of attributes that you want to
 * look up in a single call.  This is somewhat more efficient than
 * calling `git_attr_get()` multiple times.
 *
 * For example, you might write:
 *
 *     const char *attrs[] = { "crlf", "diff", "foo" };
 *     const char **values[3];
 *     git_attr_get_many(values, repo, 0, "my/fun/file.c", 3, attrs);
 *
 * Then you could loop through the 3 values to get the settings for
 * the three attributes you asked about.
 *
 * @param values_out An array of num_attr entries that will have string
 *             pointers written into it for the values of the attributes.
 *             You should not modify or free the values that are written
 *             into this array (although of course, you should free the
 *             array itself if you allocated it).
 * @param repo The repository containing the path.
 * @param flags A combination of GIT_ATTR_CHECK... flags.
 * @param path The path inside the repo to check attributes.  This
 *             does not have to exist, but if it does not, then
 *             it will be treated as a plain file (i.e. not a directory).
 * @param num_attr The number of attributes being looked up
 * @param names An array of num_attr strings containing attribute names.
 * @return 0 or an error code.
  *)

function git_attr_get_many(values_out: PPAnsiChar; repo: Pgit_repository; flags: uint32_t; path: PAnsiChar;
  num_attr: size_t; names: PPAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Look up a list of git attributes for path with extended options.
 *
 * @param values_out An array of num_attr entries that will have string
 *             pointers written into it for the values of the attributes.
 *             You should not modify or free the values that are written
 *             into this array (although of course, you should free the
 *             array itself if you allocated it).
 * @param repo The repository containing the path.
 * @param opts The `git_attr_options` to use when querying these attributes.
 * @param path The path inside the repo to check attributes.  This
 *             does not have to exist, but if it does not, then
 *             it will be treated as a plain file (i.e. not a directory).
 * @param num_attr The number of attributes being looked up
 * @param names An array of num_attr strings containing attribute names.
 * @return 0 or an error code.
 *)

function git_attr_get_many_ext(values_out: PPAnsiChar; repo: Pgit_repository; opts: Pgit_attr_options; path: PAnsiChar; num_attr:
  size_t; names: PPAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * The callback used with git_attr_foreach.
 *
 * This callback will be invoked only once per attribute name, even if there
 * are multiple rules for a given file. The highest priority rule will be
 * used.
 *
 * @see git_attr_foreach.
 *
 * @param name The attribute name.
 * @param value The attribute value. May be NULL if the attribute is explicitly
 *              set to UNSPECIFIED using the '!' sign.
 * @param payload A user-specified pointer.
 * @return 0 to continue looping, non-zero to stop. This value will be returned
 *         from git_attr_foreach.
  *)

type
  git_attr_foreach_cb = function(name_, Value: PAnsiChar; payload: Pointer): Integer; cdecl;

  (**
   * Loop over all the git attributes for a path.
   *
   * @param repo The repository containing the path.
   * @param flags A combination of GIT_ATTR_CHECK... flags.
   * @param path Path inside the repo to check attributes.  This does not have
   *             to exist, but if it does not, then it will be treated as a
   *             plain file (i.e. not a directory).
   * @param callback Function to invoke on each attribute name and value.
   *                 See git_attr_foreach_cb.
   * @param payload Passed on as extra parameter to callback function.
   * @return 0 on success, non-zero callback return value, or error code
    *)

function git_attr_foreach(repo: Pgit_repository; flags: uint32_t; path: PAnsiChar; callback: git_attr_foreach_cb;
  payload: Pointer): Integer; cdecl; external libgit2_dll;

(**
 * Loop over all the git attributes for a path with extended options.
 *
 * @param repo The repository containing the path.
 * @param opts The `git_attr_options` to use when querying these attributes.
 * @param path Path inside the repo to check attributes.  This does not have
 *             to exist, but if it does not, then it will be treated as a
 *             plain file (i.e. not a directory).
 * @param callback Function to invoke on each attribute name and value.
 *                 See git_attr_foreach_cb.
 * @param payload Passed on as extra parameter to callback function.
 * @return 0 on success, non-zero callback return value, or error code
 *)

function git_attr_foreach_ext(repo: Pgit_repository; opts: Pgit_attr_options; path: PAnsiChar;
  callback: git_attr_foreach_cb; payload: Pointer): Integer; cdecl; external libgit2_dll;

(**
 * Flush the gitattributes cache.
 *
 * Call this if you have reason to believe that the attributes files on
 * disk no longer match the cached contents of memory.  This will cause
 * the attributes files to be reloaded the next time that an attribute
 * access function is called.
 *
 * @param repo The repository containing the gitattributes cache
 * @return 0 on success, or an error code
  *)

function git_attr_cache_flush(repo: Pgit_repository): Integer; cdecl; external libgit2_dll;

(**
 * Add a macro definition.
 *
 * Macros will automatically be loaded from the top level `.gitattributes`
 * file of the repository (plus the built-in "binary" macro).  This
 * function allows you to add others.  For example, to add the default
 * macro, you would call:
 *
 *     git_attr_add_macro(repo, "binary", "-diff -crlf");
 *
 * @param repo The repository to add the macro in.
 * @param name The name of the macro.
 * @param values The value for the macro.
 * @return 0 or an error code.
  *)

function git_attr_add_macro(repo: Pgit_repository; name_, values: PAnsiChar): Integer; cdecl; external libgit2_dll;

(** @}  *)



