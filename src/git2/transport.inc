(**
 * @file git2/transport.h
 * @brief Git transport interfaces and functions
 * @defgroup git_transport interfaces and functions
 * @ingroup Git
 * @{
 *)

(**
 * Callback for messages received by the transport.
 *
 * Return a negative value to cancel the network operation.
 *
 * @param str The message from the transport
 * @param len The length of the message
 * @param payload Payload provided by the caller
 *)

type
  git_transport_message_cb = function(str: PAnsiChar; len: Integer; payload: Pointer): Integer; cdecl;

  (** Signature of a function which creates a transport  *)

type
  git_transport_cb = function(out_: PPgit_transport; owner: Pgit_remote; param: Pointer): Integer; cdecl;

  (** @}  *)


