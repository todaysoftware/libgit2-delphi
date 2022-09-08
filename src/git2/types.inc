(**
 * @file git2/types.h
 * @brief libgit2 base & compatibility types
 * @ingroup Git
 * @{
 *)

 (**
 * Cross-platform compatibility types for off_t / time_t
 *
 * NOTE: This needs to be in a public header so that both the library
 * implementation and client applications both agree on the same types.
 * Otherwise we get undefined behavior.
 *
 * Use the "best" types that each platform provides. Currently we truncate
 * these intermediate representations for compatibility with the git ABI, but
 * if and when it changes to support 64 bit types, our code will naturally
 * adapt.
 * NOTE: These types should match those that are returned by our internal
 * stat() functions, for all platforms.
 *)

type
  git_off_t = int64_t;
  git_time_t = int64_t;

  (** The maximum size of an object  *)

  git_object_size_t = uint64_t;

  (** Basic type (loose or packed) of any Git object.  *)

const
  GIT_OBJECT_ANY              = -2; (**< Object can be any of the following  *)
  GIT_OBJECT_INVALID          = -1; (**< Object is invalid.  *)
  GIT_OBJECT_COMMIT           = 1; (**< A commit object.  *)
  GIT_OBJECT_TREE             = 2; (**< A tree (directory listing) object.  *)
  GIT_OBJECT_BLOB             = 3; (**< A file revision object.  *)
  GIT_OBJECT_TAG              = 4; (**< An annotated tag object.  *)
  GIT_OBJECT_OFS_DELTA        = 6; (**< A delta, base is given by an offset.  *)
  GIT_OBJECT_REF_DELTA        = 7; (**< A delta, base is given by object id.  *)
type
  git_object_t = Integer;

  (** An open object database handle.  *)

  git_odb = record
  end;
  Pgit_odb = ^git_odb;
  PPgit_odb = ^Pgit_odb;

  (** A custom backend in an ODB  *)

  git_odb_backend = record
  end;
  Pgit_odb_backend = ^git_odb_backend;
  PPgit_odb_backend = ^Pgit_odb_backend;

  (** An object read from the ODB  *)

  git_odb_object = record
  end;
  Pgit_odb_object = ^git_odb_object;
  PPgit_odb_object = ^Pgit_odb_object;

  (** A stream to read/write from the ODB  *)

  //git_odb_stream = record
  //end;
  //Pgit_odb_stream = ^git_odb_stream;
  //PPgit_odb_stream = ^Pgit_odb_stream;

  (** A stream to write a packfile to the ODB  *)

  //git_odb_writepack = record
  //end;
  //Pgit_odb_writepack = ^git_odb_writepack;
  //PPgit_odb_writepack = ^Pgit_odb_writepack;

  (** a writer for multi-pack-index files. *)

  git_midx_writer = record
  end;
  Pgit_midx_writer = ^git_midx_writer;
  PPgit_midx_writer = ^Pgit_midx_writer;

  (** An open refs database handle.  *)

  git_refdb = record
  end;
  Pgit_refdb = ^git_refdb;
  PPgit_refdb = ^Pgit_refdb;

  (** A custom backend for refs  *)

  git_refdb_backend = record
  end;
  Pgit_refdb_backend = ^git_refdb_backend;
  PPgit_refdb_backend = ^Pgit_refdb_backend;

  (** A git commit-graph *)

  git_commit_graph = record
  end;
  Pgit_commit_graph = ^git_commit_graph;
  PPgit_commit_graph = ^Pgit_commit_graph;

  (** a writer for commit-graph files. *)

  git_commit_graph_writer = record
  end;
  Pgit_commit_graph_writer = ^git_commit_graph_writer;
  PPgit_commit_graph_writer = ^Pgit_commit_graph_writer;

  (**
   * Representation of an existing git repository,
   * including all its object contents
   *)

  git_repository = record
  end;
  Pgit_repository = ^git_repository;
  PPgit_repository = ^Pgit_repository;

  (** Representation of a working tree  *)

  git_worktree = record
  end;
  Pgit_worktree = ^git_worktree;
  PPgit_worktree = ^Pgit_worktree;

  (** Representation of a generic object in a repository  *)

  git_object = record
  end;
  Pgit_object = ^git_object;
  PPgit_object = ^Pgit_object;

  (** Representation of an in-progress walk through the commits in a repo  *)

  git_revwalk = record
  end;
  Pgit_revwalk = ^git_revwalk;
  PPgit_revwalk = ^Pgit_revwalk;

  (** Parsed representation of a tag object.  *)

  git_tag = record
  end;
  Pgit_tag = ^git_tag;
  PPgit_tag = ^Pgit_tag;

  (** In-memory representation of a blob object.  *)

  git_blob = record
  end;
  Pgit_blob = ^git_blob;
  PPgit_blob = ^Pgit_blob;

  (** Parsed representation of a commit object.  *)

  git_commit = record
  end;
  Pgit_commit = ^git_commit;
  PPgit_commit = ^Pgit_commit;

  (** Representation of each one of the entries in a tree object.  *)

  git_tree_entry = record
  end;
  Pgit_tree_entry = ^git_tree_entry;
  PPgit_tree_entry = ^Pgit_tree_entry;

  (** Representation of a tree object.  *)

  git_tree = record
  end;
  Pgit_tree = ^git_tree;
  PPgit_tree = ^Pgit_tree;

  (** Constructor for in-memory trees  *)

  git_treebuilder = record
  end;
  Pgit_treebuilder = ^git_treebuilder;
  PPgit_treebuilder = ^Pgit_treebuilder;

  (** Memory representation of an index file.  *)

  git_index = record
  end;
  Pgit_index = ^git_index;
  PPgit_index = ^Pgit_index;

  (** An iterator for entries in the index.  *)

  git_index_iterator = record
  end;
  Pgit_index_iterator = ^git_index_iterator;
  PPgit_index_iterator = ^Pgit_index_iterator;

  (** An iterator for conflicts in the index.  *)

  git_index_conflict_iterator = record
  end;
  Pgit_index_conflict_iterator = ^git_index_conflict_iterator;
  PPgit_index_conflict_iterator = ^Pgit_index_conflict_iterator;

  (** Memory representation of a set of config files  *)

  git_config = record
  end;
  Pgit_config = ^git_config;
  PPgit_config = ^Pgit_config;

  (** Interface to access a configuration file  *)

  git_config_backend = record
  end;
  Pgit_config_backend = ^git_config_backend;
  PPgit_config_backend = ^Pgit_config_backend;

  (** Representation of a reference log entry  *)

  git_reflog_entry = record
  end;
  Pgit_reflog_entry = ^git_reflog_entry;
  PPgit_reflog_entry = ^Pgit_reflog_entry;

  (** Representation of a reference log  *)

  git_reflog = record
  end;
  Pgit_reflog = ^git_reflog;
  PPgit_reflog = ^Pgit_reflog;

  (** Representation of a git note  *)

  git_note = record
  end;
  Pgit_note = ^git_note;
  PPgit_note = ^Pgit_note;

  (** Representation of a git packbuilder  *)

  git_packbuilder = record
  end;
  Pgit_packbuilder = ^git_packbuilder;
  PPgit_packbuilder = ^Pgit_packbuilder;

  (** Time in a signature  *)

  git_time = record
    time: git_time_t; (**< time in seconds from epoch  *)
    offset: Integer; (**< timezone offset, in minutes  *)
    sign: AnsiChar; (**< indicator for questionable '-0000' offsets in signature  *)
  end;
  Pgit_time = ^git_time;

  (** An action signature (e.g. for committers, taggers, etc)  *)

  git_signature = record
    name_: PAnsiChar; (**< full name of the author  *)
    email: PAnsiChar; (**< email of the author  *)
    when: git_time; (**< time when the action happened  *)
  end;
  Pgit_signature = ^git_signature;
  PPgit_signature = ^Pgit_signature;

  (** In-memory representation of a reference.  *)

  git_reference = record
  end;
  Pgit_reference = ^git_reference;
  PPgit_reference = ^Pgit_reference;

  (** Iterator for references  *)

  git_reference_iterator = record
  end;
  Pgit_reference_iterator = ^git_reference_iterator;
  PPgit_reference_iterator = ^Pgit_reference_iterator;

  (** Transactional interface to references  *)

  git_transaction = record
  end;
  Pgit_transaction = ^git_transaction;
  PPgit_transaction = ^Pgit_transaction;

  (** Annotated commits, the input to merge and rebase.  *)

  git_annotated_commit = record
  end;
  Pgit_annotated_commit = ^git_annotated_commit;
  PPgit_annotated_commit = ^Pgit_annotated_commit;

  (** Representation of a status collection  *)

  git_status_list = record
  end;
  Pgit_status_list = ^git_status_list;
  PPgit_status_list = ^Pgit_status_list;

  (** Representation of a rebase  *)

  git_rebase = record
  end;
  Pgit_rebase = ^git_rebase;
  PPgit_rebase = ^Pgit_rebase;

  (** Basic type of any Git reference.  *)

const
  GIT_REFERENCE_INVALID       = 0; (**< Invalid reference  *)
  GIT_REFERENCE_DIRECT        = 1; (**< A reference that points at an object id  *)
  GIT_REFERENCE_SYMBOLIC      = 2; (**< A reference that points at another reference  *)
  GIT_REFERENCE_ALL           = GIT_REFERENCE_DIRECT or GIT_REFERENCE_SYMBOLIC;
type
  git_reference_t = Integer;

  (** Basic type of any Git branch.  *)

const
  GIT_BRANCH_LOCAL            = 1;
  GIT_BRANCH_REMOTE           = 2;
  GIT_BRANCH_ALL              = GIT_BRANCH_LOCAL or GIT_BRANCH_REMOTE;
type
  git_branch_t = Integer;

  (** Valid modes for index and tree entries.  *)

const
  GIT_FILEMODE_UNREADABLE     = 0;
  GIT_FILEMODE_TREE           = 16384;
  GIT_FILEMODE_BLOB           = 33188;
  GIT_FILEMODE_BLOB_EXECUTABLE = 33261;
  GIT_FILEMODE_LINK           = 40960;
  GIT_FILEMODE_COMMIT         = 57344;
type
  git_filemode_t = Integer;

  (**
   * A refspec specifies the mapping between remote and local reference
   * names when fetch or pushing.
   *)

  git_refspec = record
  end;
  Pgit_refspec = ^git_refspec;
  PPgit_refspec = ^Pgit_refspec;

  (**
   * Git's idea of a remote repository. A remote can be anonymous (in
   * which case it does not have backing configuration entries).
   *)

  git_remote = record
  end;
  Pgit_remote = ^git_remote;
  PPgit_remote = ^Pgit_remote;

  (**
   * Interface which represents a transport to communicate with a
   * remote.
   *)

  git_transport = record
  end;
  Pgit_transport = ^git_transport;
  PPgit_transport = ^Pgit_transport;

  (**
   * Preparation for a push operation. Can be used to configure what to
   * push and the level of parallelism of the packfile builder.
   *)

  git_push = record
  end;
  Pgit_push = ^git_push;
  PPgit_push = ^Pgit_push;

  (* documentation in the definition  *)

  //git_remote_head = record
  //end;
  //Pgit_remote_head = ^;
  //PPgit_remote_head = ^Pgit_remote_head;

  //git_remote_callbacks = record
  //end;
  //Pgit_remote_callbacks = ^git_remote_callbacks;
  //PPgit_remote_callbacks = ^Pgit_remote_callbacks;

  (**
   * Parent type for `git_cert_hostkey` and `git_cert_x509`.
   *)

  //git_cert = record
  //end;
  //Pgit_cert = ^;
  //PPgit_cert = ^Pgit_cert;

  (**
   * Opaque structure representing a submodule.
   *)

  git_submodule = record
  end;
  Pgit_submodule = ^git_submodule;
  PPgit_submodule = ^Pgit_submodule;

  (**
   * Submodule update values
   *
   * These values represent settings for the `submodule.$name.update`
   * configuration value which says how to handle `git submodule update` for
   * this submodule.  The value is usually set in the ".gitmodules" file and
   * copied to ".git/config" when the submodule is initialized.
   *
   * You can override this setting on a per-submodule basis with
   * `git_submodule_set_update()` and write the changed value to disk using
   * `git_submodule_save()`.  If you have overwritten the value, you can
   * revert it by passing `GIT_SUBMODULE_UPDATE_RESET` to the set function.
   *
   * The values are:
   *
   * - GIT_SUBMODULE_UPDATE_CHECKOUT: the default; when a submodule is
   *   updated, checkout the new detached HEAD to the submodule directory.
   * - GIT_SUBMODULE_UPDATE_REBASE: update by rebasing the current checked
   *   out branch onto the commit from the superproject.
   * - GIT_SUBMODULE_UPDATE_MERGE: update by merging the commit in the
   *   superproject into the current checkout out branch of the submodule.
   * - GIT_SUBMODULE_UPDATE_NONE: do not update this submodule even when
   *   the commit in the superproject is updated.
   * - GIT_SUBMODULE_UPDATE_DEFAULT: not used except as static initializer
   *   when we don't want any particular update rule to be specified.
   *)

const
  GIT_SUBMODULE_UPDATE_CHECKOUT = 1;
  GIT_SUBMODULE_UPDATE_REBASE = 2;
  GIT_SUBMODULE_UPDATE_MERGE  = 3;
  GIT_SUBMODULE_UPDATE_NONE   = 4;
  GIT_SUBMODULE_UPDATE_DEFAULT = 0;
type
  git_submodule_update_t = Integer;

  (**
   * Submodule ignore values
   *
   * These values represent settings for the `submodule.$name.ignore`
   * configuration value which says how deeply to look at the working
   * directory when getting submodule status.
   *
   * You can override this value in memory on a per-submodule basis with
   * `git_submodule_set_ignore()` and can write the changed value to disk
   * with `git_submodule_save()`.  If you have overwritten the value, you
   * can revert to the on disk value by using `GIT_SUBMODULE_IGNORE_RESET`.
   *
   * The values are:
   *
   * - GIT_SUBMODULE_IGNORE_UNSPECIFIED: use the submodule's configuration
   * - GIT_SUBMODULE_IGNORE_NONE: don't ignore any change - i.e. even an
   *   untracked file, will mark the submodule as dirty.  Ignored files are
   *   still ignored, of course.
   * - GIT_SUBMODULE_IGNORE_UNTRACKED: ignore untracked files; only changes
   *   to tracked files, or the index or the HEAD commit will matter.
   * - GIT_SUBMODULE_IGNORE_DIRTY: ignore changes in the working directory,
   *   only considering changes if the HEAD of submodule has moved from the
   *   value in the superproject.
   * - GIT_SUBMODULE_IGNORE_ALL: never check if the submodule is dirty
   * - GIT_SUBMODULE_IGNORE_DEFAULT: not used except as static initializer
   *   when we don't want any particular ignore rule to be specified.
   *)

const
  GIT_SUBMODULE_IGNORE_UNSPECIFIED = -1; (**< use the submodule's configuration  *)
  GIT_SUBMODULE_IGNORE_NONE   = 1; (**< any change or untracked == dirty  *)
  GIT_SUBMODULE_IGNORE_UNTRACKED = 2; (**< dirty if tracked files change  *)
  GIT_SUBMODULE_IGNORE_DIRTY  = 3; (**< only dirty if HEAD moved  *)
  GIT_SUBMODULE_IGNORE_ALL    = 4; (**< never dirty  *)
type
  git_submodule_ignore_t = Integer;

  (**
   * Options for submodule recurse.
   *
   * Represent the value of `submodule.$name.fetchRecurseSubmodules`
   *
   * * GIT_SUBMODULE_RECURSE_NO    - do no recurse into submodules
   * * GIT_SUBMODULE_RECURSE_YES   - recurse into submodules
   * * GIT_SUBMODULE_RECURSE_ONDEMAND - recurse into submodules only when
   *                                    commit not already in local clone
   *)

const
  GIT_SUBMODULE_RECURSE_NO    = 0;
  GIT_SUBMODULE_RECURSE_YES   = 1;
  GIT_SUBMODULE_RECURSE_ONDEMAND = 2;
type
  git_submodule_recurse_t = Integer;

  (** A type to write in a streaming fashion, for example, for filters.  *)
  Pgit_writestream = ^git_writestream;
  PPgit_writestream = ^Pgit_writestream;
  git_writestream = record
    write: function(stream: Pgit_writestream; const buffer: PAnsiChar; len: size_t): Integer;
    close: function(stream: Pgit_writestream): Integer;
    Free: procedure(stream: Pgit_writestream);
  end;

  (** Representation of .mailmap file state.  *)

type
  git_mailmap = record
  end;
  Pgit_mailmap = ^git_mailmap;
  PPgit_mailmap = ^Pgit_mailmap;

