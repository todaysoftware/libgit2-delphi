const
  (**
   * The version string for libgit2.  This string follows semantic
   * versioning (v2) guidelines.
   *)
  LIBGIT2_VERSION             = '1.8.1';

  (** The major version number for this version of libgit2. *)
  LIBGIT2_VER_MAJOR           = 1;

  (** The minor version number for this version of libgit2. *)
  LIBGIT2_VER_MINOR           = 8;

  (** The revision ("teeny") version number for this version of libgit2. *)
  LIBGIT2_VER_REVISION        = 1;

  (** The Windows DLL patch number for this version of libgit2. *)
  LIBGIT2_VER_PATCH           = 0;

  (**
   * The prerelease string for this version of libgit2.  For development
   * (nightly) builds, this will be "alpha".  For prereleases, this will be
   * a prerelease name like "beta" or "rc1".  For final releases, this will
   * be `NULL`.
   *)
  LIBGIT2_VER_PRERELEASE      : PAnsiChar = nil;

  (**
   * The library ABI soversion for this version of libgit2. This should
   * only be changed when the library has a breaking ABI change, and so
   * may trail the library's version number.
   *)
  LIBGIT2_SOVERSION           = '1.8';

