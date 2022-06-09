(**
 * @file git2/net.h
 * @brief Git networking declarations
 * @ingroup Git
 * @{
 *)

const
  GIT_DEFAULT_PORT            = '9418';
  (**
   * Direction of the connection.
   *
   * We need this because we need to know whether we should call
   * git-upload-pack or git-receive-pack on the remote end when get_refs
   * gets called.
   *)

const
  GIT_DIRECTION_FETCH         = 0;
  GIT_DIRECTION_PUSH          = 1;
type
  git_direction = Integer;

  (**
   * Description of a reference advertised by a remote server, given out
   * on `ls` calls.
   *)

  git_remote_head = record
    local_: Integer; (* available locally  *)
    oid: git_oid;
    loid: git_oid;
    name_: PAnsiChar;
    (**
     * If the server send a symref mapping for this ref, this will
     * point to the target.
     *)
    symref_target: PAnsiChar;
  end;
  Pgit_remote_head = ^git_remote_head;
  PPgit_remote_head = ^Pgit_remote_head;
  PPPgit_remote_head = ^PPgit_remote_head;

  (** @}  *)


