(**
 * @file git2/trace.h
 * @brief Git tracing configuration routines
 * @defgroup git_trace Git tracing configuration routines
 * @ingroup Git
 * @{
 *)

(**
 * Available tracing levels.  When tracing is set to a particular level,
 * callers will be provided tracing at the given level and all lower levels.
 *)

const
  (** No tracing will be performed.  *)
  GIT_TRACE_NONE              = 0;
  (** Severe errors that may impact the program's execution  *)
  GIT_TRACE_FATAL             = 1;
  (** Errors that do not impact the program's execution  *)
  GIT_TRACE_ERROR             = 2;
  (** Warnings that suggest abnormal data  *)
  GIT_TRACE_WARN              = 3;
  (** Informational messages about program execution  *)
  GIT_TRACE_INFO              = 4;
  (** Detailed data that allows for debugging  *)
  GIT_TRACE_DEBUG             = 5;
  (** Exceptionally detailed debugging data  *)
  GIT_TRACE_TRACE             = 6;
type
  git_trace_level_t = Integer;

  (**
   * An instance for a tracing function
   *)

  git_trace_cb = procedure(level: git_trace_level_t; msg: PAnsiChar); cdecl;

  (**
   * Sets the system tracing configuration to the specified level with the
   * specified callback.  When system events occur at a level equal to, or
   * lower than, the given level they will be reported to the given callback.
   *
   * @param level Level to set tracing to
   * @param cb Function to call with trace data
   * @return 0 or an error code
   *)

function git_trace_set(level: git_trace_level_t; cb: git_trace_cb): Integer; cdecl; external libgit2_dll;

(** @}  *)


