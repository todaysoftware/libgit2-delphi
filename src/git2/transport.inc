(**
 * @file git2/transport.h
 * @brief Transports are the low-level mechanism to connect to a remote server
 * @defgroup git_transport Transports are the low-level mechanism to connect to a remote server
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
 * @return 0 on success or an error code
 *)

type
  git_transport_message_cb = function(str: PAnsiChar; len: Integer; payload: Pointer): Integer; cdecl;

  (** Signature of a function which creates a transport  *)

type
  (**
   * Signature of a function which creates a transport.
   *
   * @param out the transport generate
   * @param owner the owner for the transport
   * @param param the param to the transport creation
   * @return 0 on success or an error code
   *)
  git_transport_cb = function(out_: PPgit_transport; owner: Pgit_remote; param: Pointer): Integer; cdecl;

  (** @}  *)


