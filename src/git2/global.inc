(**
 * Init the global state
 *
 * This function must be called before any other libgit2 function in
 * order to set up global state and threading.
 *
 * This function may be called multiple times - it will return the number
 * of times the initialization has been called (including this one) that have
 * not subsequently been shutdown.
 *
 * @return the number of initializations of the library, or an error code.
 *)

function git_libgit2_init: Integer; cdecl; external libgit2_dll;

(**
 * Shutdown the global state
 *
 * Clean up the global state and threading context after calling it as
 * many times as `git_libgit2_init()` was called - it will return the
 * number of remainining initializations that have not been shutdown
 * (after this one).
 *
 * @return the number of remaining initializations of the library, or an
 * error code.
 *)

function git_libgit2_shutdown: Integer; cdecl; external libgit2_dll;

(** @}  *)

