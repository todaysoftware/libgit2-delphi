(**
 * @file git2/version.h
 * @brief The version of libgit2
 * @ingroup Git
 * @{
 *)

const
  (**
   * The version string for libgit2.  This string follows semantic
   * versioning (v2) guidelines.
   *)
  LIBGIT2_VERSION             = '1.9.1';

  (** The major version number for this version of libgit2. *)
  LIBGIT2_VERSION_MAJOR       = 1;

  (** The minor version number for this version of libgit2. *)
  LIBGIT2_VERSION_MINOR       = 9;

  (** The revision ("teeny") version number for this version of libgit2. *)
  LIBGIT2_VERSION_REVISION    = 1;

  (** The Windows DLL patch number for this version of libgit2. *)
  LIBGIT2_VERSION_PATCH       = 0;

  (**
   * The prerelease string for this version of libgit2.  For development
   * (nightly) builds, this will be "alpha".  For prereleases, this will be
   * a prerelease name like "beta" or "rc1".  For final releases, this will
   * be `NULL`.
   *)
  LIBGIT2_VERSION_PRERELEASE  : PAnsiChar = nil;

  (**
   * The library ABI soversion for this version of libgit2. This should
   * only be changed when the library has a breaking ABI change, and so
   * may not reflect the library's API version number.
   *)
  LIBGIT2_SOVERSION           = '1.9';

  (**
   * An integer value representing the libgit2 version number. For example,
   * libgit2 1.6.3 is 1060300.
   *)
  LIBGIT2_VERSION_NUMBER      =
    (LIBGIT2_VERSION_MAJOR * 1000000) +
    (LIBGIT2_VERSION_MINOR * 10000) +
    (LIBGIT2_VERSION_REVISION * 100);

(**
 * Compare the libgit2 version against a given version. Evaluates to true
 * if the given major, minor, and revision values are greater than or equal
 * to the currently running libgit2 version. For example:
 *
 *  #if LIBGIT2_VERSION_CHECK(1, 6, 3)
 *  # error libgit2 version is >= 1.6.3
 *  #endif
 *)
function LIBGIT2_VERSION_CHECK(major, minor, revision: Integer): Boolean;

