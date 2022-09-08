(**
 * @file git2/tree.h
 * @brief Git tree parsing, loading routines
 * @defgroup git_tree Git tree parsing, loading routines
 * @ingroup Git
 * @{
 *)

(**
 * Lookup a tree object from the repository.
 *
 * @param out Pointer to the looked up tree
 * @param repo The repo to use when locating the tree.
 * @param id Identity of the tree to locate.
 * @return 0 or an error code
 *)

function git_tree_lookup(out_: PPgit_tree; repo: Pgit_repository; id: Pgit_oid): Integer; cdecl; external libgit2_dll;

(**
 * Lookup a tree object from the repository,
 * given a prefix of its identifier (short id).
 *
 * @see git_object_lookup_prefix
 *
 * @param out pointer to the looked up tree
 * @param repo the repo to use when locating the tree.
 * @param id identity of the tree to locate.
 * @param len the length of the short identifier
 * @return 0 or an error code
 *)

function git_tree_lookup_prefix(out_: PPgit_tree; repo: Pgit_repository; id: Pgit_oid;
  len: size_t): Integer; cdecl; external libgit2_dll;

(**
 * Close an open tree
 *
 * You can no longer use the git_tree pointer after this call.
 *
 * IMPORTANT: You MUST call this method when you stop using a tree to
 * release memory. Failure to do so will cause a memory leak.
 *
 * @param tree The tree to close
 *)

procedure git_tree_free(tree: Pgit_tree); cdecl; external libgit2_dll;

(**
 * Get the id of a tree.
 *
 * @param tree a previously loaded tree.
 * @return object identity for the tree.
 *)

function git_tree_id(tree: Pgit_tree): Pgit_oid; cdecl; external libgit2_dll;

(**
 * Get the repository that contains the tree.
 *
 * @param tree A previously loaded tree.
 * @return Repository that contains this tree.
 *)

function git_tree_owner(tree: Pgit_tree): Pgit_repository; cdecl; external libgit2_dll;

(**
 * Get the number of entries listed in a tree
 *
 * @param tree a previously loaded tree.
 * @return the number of entries in the tree
 *)

function git_tree_entrycount(tree: Pgit_tree): size_t; cdecl; external libgit2_dll;

(**
 * Lookup a tree entry by its filename
 *
 * This returns a git_tree_entry that is owned by the git_tree.  You don't
 * have to free it, but you must not use it after the git_tree is released.
 *
 * @param tree a previously loaded tree.
 * @param filename the filename of the desired entry
 * @return the tree entry; NULL if not found
 *)

function git_tree_entry_byname(tree: Pgit_tree; filename: PAnsiChar): Pgit_tree_entry; cdecl; external libgit2_dll;

(**
 * Lookup a tree entry by its position in the tree
 *
 * This returns a git_tree_entry that is owned by the git_tree.  You don't
 * have to free it, but you must not use it after the git_tree is released.
 *
 * @param tree a previously loaded tree.
 * @param idx the position in the entry list
 * @return the tree entry; NULL if not found
 *)

function git_tree_entry_byindex(tree: Pgit_tree; idx: size_t): Pgit_tree_entry; cdecl; external libgit2_dll;

(**
 * Lookup a tree entry by SHA value.
 *
 * This returns a git_tree_entry that is owned by the git_tree.  You don't
 * have to free it, but you must not use it after the git_tree is released.
 *
 * Warning: this must examine every entry in the tree, so it is not fast.
 *
 * @param tree a previously loaded tree.
 * @param id the sha being looked for
 * @return the tree entry; NULL if not found
  *)

function git_tree_entry_byid(tree: Pgit_tree; id: Pgit_oid): Pgit_tree_entry; cdecl; external libgit2_dll;

(**
 * Retrieve a tree entry contained in a tree or in any of its subtrees,
 * given its relative path.
 *
 * Unlike the other lookup functions, the returned tree entry is owned by
 * the user and must be freed explicitly with `git_tree_entry_free()`.
 *
 * @param out Pointer where to store the tree entry
 * @param root Previously loaded tree which is the root of the relative path
 * @param path Path to the contained entry
 * @return 0 on success; GIT_ENOTFOUND if the path does not exist
 *)

function git_tree_entry_bypath(out_: PPgit_tree_entry; root: Pgit_tree; path: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Duplicate a tree entry
 *
 * Create a copy of a tree entry. The returned copy is owned by the user,
 * and must be freed explicitly with `git_tree_entry_free()`.
 *
 * @param dest pointer where to store the copy
 * @param source tree entry to duplicate
 * @return 0 or an error code
  *)

function git_tree_entry_dup(dest: PPgit_tree_entry; source: Pgit_tree_entry): Integer; cdecl; external libgit2_dll;

(**
 * Free a user-owned tree entry
 *
 * IMPORTANT: This function is only needed for tree entries owned by the
 * user, such as the ones returned by `git_tree_entry_dup()` or
 * `git_tree_entry_bypath()`.
 *
 * @param entry The entry to free
 *)

procedure git_tree_entry_free(entry: Pgit_tree_entry); cdecl; external libgit2_dll;

(**
 * Get the filename of a tree entry
 *
 * @param entry a tree entry
 * @return the name of the file
  *)

function git_tree_entry_name(entry: Pgit_tree_entry): PAnsiChar; cdecl; external libgit2_dll;

(**
 * Get the id of the object pointed by the entry
 *
 * @param entry a tree entry
 * @return the oid of the object
 *)

function git_tree_entry_id(entry: Pgit_tree_entry): Pgit_oid; cdecl; external libgit2_dll;

(**
 * Get the type of the object pointed by the entry
 *
 * @param entry a tree entry
 * @return the type of the pointed object
 *)

function git_tree_entry_type(entry: Pgit_tree_entry): git_object_t; cdecl; external libgit2_dll;

(**
 * Get the UNIX file attributes of a tree entry
 *
 * @param entry a tree entry
 * @return filemode as an integer
 *)

function git_tree_entry_filemode(entry: Pgit_tree_entry): git_filemode_t; cdecl; external libgit2_dll;

(**
 * Get the raw UNIX file attributes of a tree entry
 *
 * This function does not perform any normalization and is only useful
 * if you need to be able to recreate the original tree object.
 *
 * @param entry a tree entry
 * @return filemode as an integer
 *)

function git_tree_entry_filemode_raw(entry: Pgit_tree_entry): git_filemode_t; cdecl; external libgit2_dll;

(**
 * Compare two tree entries
 *
 * @param e1 first tree entry
 * @param e2 second tree entry
 * @return <0 if e1 is before e2, 0 if e1 == e2, >0 if e1 is after e2
 *)

function git_tree_entry_cmp(e1, e2: Pgit_tree_entry): Integer; cdecl; external libgit2_dll;

(**
 * Convert a tree entry to the git_object it points to.
 *
 * You must call `git_object_free()` on the object when you are done with it.
 *
 * @param object_out pointer to the converted object
 * @param repo repository where to lookup the pointed object
 * @param entry a tree entry
 * @return 0 or an error code
 *)

function git_tree_entry_to_object(object_out: PPgit_object; repo: Pgit_repository;
  entry: Pgit_tree_entry): Integer; cdecl; external libgit2_dll;

(**
 * Create a new tree builder.
 *
 * The tree builder can be used to create or modify trees in memory and
 * write them as tree objects to the database.
 *
 * If the `source` parameter is not NULL, the tree builder will be
 * initialized with the entries of the given tree.
 *
 * If the `source` parameter is NULL, the tree builder will start with no
 * entries and will have to be filled manually.
 *
 * @param out Pointer where to store the tree builder
 * @param repo Repository in which to store the object
 * @param source Source tree to initialize the builder (optional)
 * @return 0 on success; error code otherwise
 *)

function git_treebuilder_new(out_: PPgit_treebuilder; repo: Pgit_repository;
  source: Pgit_tree): Integer; cdecl; external libgit2_dll;

(**
 * Clear all the entries in the builder
 *
 * @param bld Builder to clear
 * @return 0 on success; error code otherwise
 *)

function git_treebuilder_clear(bld: Pgit_treebuilder): Integer; cdecl; external libgit2_dll;

(**
 * Get the number of entries listed in a treebuilder
 *
 * @param bld a previously loaded treebuilder.
 * @return the number of entries in the treebuilder
 *)

function git_treebuilder_entrycount(bld: Pgit_treebuilder): size_t; cdecl; external libgit2_dll;

(**
 * Free a tree builder
 *
 * This will clear all the entries and free to builder.
 * Failing to free the builder after you're done using it
 * will result in a memory leak
 *
 * @param bld Builder to free
 *)

procedure git_treebuilder_free(bld: Pgit_treebuilder); cdecl; external libgit2_dll;

(**
 * Get an entry from the builder from its filename
 *
 * The returned entry is owned by the builder and should
 * not be freed manually.
 *
 * @param bld Tree builder
 * @param filename Name of the entry
 * @return pointer to the entry; NULL if not found
 *)

function git_treebuilder_get(bld: Pgit_treebuilder; filename: PAnsiChar): Pgit_tree_entry; cdecl; external libgit2_dll;

(**
 * Add or update an entry to the builder
 *
 * Insert a new entry for `filename` in the builder with the
 * given attributes.
 *
 * If an entry named `filename` already exists, its attributes
 * will be updated with the given ones.
 *
 * The optional pointer `out` can be used to retrieve a pointer to the
 * newly created/updated entry.  Pass NULL if you do not need it. The
 * pointer may not be valid past the next operation in this
 * builder. Duplicate the entry if you want to keep it.
 *
 * By default the entry that you are inserting will be checked for
 * validity; that it exists in the object database and is of the
 * correct type.  If you do not want this behavior, set the
 * `GIT_OPT_ENABLE_STRICT_OBJECT_CREATION` library option to false.
 *
 * @param out Pointer to store the entry (optional)
 * @param bld Tree builder
 * @param filename Filename of the entry
 * @param id SHA1 oid of the entry
 * @param filemode Folder attributes of the entry. This parameter must
 *			be valued with one of the following entries: 0040000, 0100644,
 *			0100755, 0120000 or 0160000.
 * @return 0 or an error code
 *)

function git_treebuilder_insert(out_: PPgit_tree_entry; bld: Pgit_treebuilder; filename: PAnsiChar;
  id: Pgit_oid; filemode: git_filemode_t): Integer; cdecl; external libgit2_dll;

(**
 * Remove an entry from the builder by its filename
 *
 * @param bld Tree builder
 * @param filename Filename of the entry to remove
 * @return 0 or an error code
 *)

function git_treebuilder_remove(bld: Pgit_treebuilder; filename: PAnsiChar): Integer; cdecl; external libgit2_dll;

(**
 * Callback for git_treebuilder_filter
 *
 * The return value is treated as a boolean, with zero indicating that the
 * entry should be left alone and any non-zero value meaning that the
 * entry should be removed from the treebuilder list (i.e. filtered out).
 *)

type
  git_treebuilder_filter_cb = function(entry: Pgit_tree_entry; payload: Pointer): Integer; cdecl;

  (**
 * Selectively remove entries in the tree
 *
 * The `filter` callback will be called for each entry in the tree with a
 * pointer to the entry and the provided `payload`; if the callback returns
 * non-zero, the entry will be filtered (removed from the builder).
 *
 * @param bld Tree builder
 * @param filter Callback to filter entries
 * @param payload Extra data to pass to filter callback
 * @return 0 on success, non-zero callback return value, or error code
 *)

function git_treebuilder_filter(bld: Pgit_treebuilder; filter: git_treebuilder_filter_cb;
  payload: Pointer): Integer; cdecl; external libgit2_dll;

(**
 * Write the contents of the tree builder as a tree object
 *
 * The tree builder will be written to the given `repo`, and its
 * identifying SHA1 hash will be stored in the `id` pointer.
 *
 * @param id Pointer to store the OID of the newly written tree
 * @param bld Tree builder to write
 * @return 0 or an error code
 *)

function git_treebuilder_write(id: Pgit_oid; bld: Pgit_treebuilder): Integer; cdecl; external libgit2_dll;

(** Callback for the tree traversal method  *)

type
  git_treewalk_cb = function(root: PAnsiChar; entry: Pgit_tree_entry; payload: Pointer): Integer; cdecl;

  (** Tree traversal modes  *)

const
  GIT_TREEWALK_PRE            = 0; (* Pre-order  *)
  GIT_TREEWALK_POST           = 1; (* Post-order  *)
type
  git_treewalk_mode = Integer;

  (**
   * Traverse the entries in a tree and its subtrees in post or pre order.
   *
   * The entries will be traversed in the specified order, children subtrees
   * will be automatically loaded as required, and the `callback` will be
   * called once per entry with the current (relative) root for the entry and
   * the entry data itself.
   *
   * If the callback returns a positive value, the passed entry will be
   * skipped on the traversal (in pre mode). A negative value stops the walk.
   *
   * @param tree The tree to walk
   * @param mode Traversal mode (pre or post-order)
   * @param callback Function to call on each tree entry
   * @param payload Opaque pointer to be passed on each callback
   * @return 0 or an error code
   *)

function git_tree_walk(tree: Pgit_tree; mode: git_treewalk_mode; callback: git_treewalk_cb;
  payload: Pointer): Integer; cdecl; external libgit2_dll;

(**
 * Create an in-memory copy of a tree. The copy must be explicitly
 * free'd or it will leak.
 *
 * @param out Pointer to store the copy of the tree
 * @param source Original tree to copy
 * @return 0
 *)

function git_tree_dup(out_: PPgit_tree; source: Pgit_tree): Integer; cdecl; external libgit2_dll;

(**
 * The kind of update to perform
 *)

const
  (** Update or insert an entry at the specified path  *)
  GIT_TREE_UPDATE_UPSERT      = 0;
  (** Remove an entry from the specified path  *)
  GIT_TREE_UPDATE_REMOVE      = 1;
type
  git_tree_update_t = Integer;

  (**
   * An action to perform during the update of a tree
   *)

  git_tree_update = record
    (** Update action. If it's an removal, only the path is looked at  *)
    action: git_tree_update_t;
    (** The entry's id  *)
    id: git_oid;
    (** The filemode/kind of object  *)
    filemode: git_filemode_t;
    (** The full path from the root tree  *)
    path: PAnsiChar;
  end;

  (**
   * Create a tree based on another one with the specified modifications
   *
   * Given the `baseline` perform the changes described in the list of
   * `updates` and create a new tree.
   *
   * This function is optimized for common file/directory addition, removal and
   * replacement in trees. It is much more efficient than reading the tree into a
   * `git_index` and modifying that, but in exchange it is not as flexible.
   *
   * Deleting and adding the same entry is undefined behaviour, changing
   * a tree to a blob or viceversa is not supported.
   *
   * @param out id of the new tree
   * @param repo the repository in which to create the tree, must be the
   * same as for `baseline`
   * @param baseline the tree to base these changes on
   * @param nupdates the number of elements in the update list
   * @param updates the list of updates to perform
   * @return 0 or an error code
   *)

type
  Pgit_tree_update = ^git_tree_update;
function git_tree_create_updated(out_: Pgit_oid; repo: Pgit_repository; baseline: Pgit_tree;
  nupdates: size_t; updates: Pgit_tree_update): Integer; cdecl; external libgit2_dll;

(** @}  *)



