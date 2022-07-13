(*
 * Copyright (C) 2021 Today Software
 * Distributed under the MIT licence see LICENCE file for more details
 * https://opensource.org/licenses/MIT
 *)
unit LibGit2;

{$IFDEF FPC}
{$MODE objfpc}{$H+}
{$ENDIF}

{$DEFINE GIT_DEPRECATE_HARD}

interface

uses
  SysUtils;

const
  {$IFDEF MSWINDOWS}
  libgit2_dll                 = 'git2.dll';
  {$ELSE}
  libgit2_dll                 = 'libgit2.so';
  {$ENDIF}

type
  PPByte = ^PByte;

  {$I git2/stdint.inc}
  {$IFNDEF FPC}
type
  size_t = uintptr_t;
  {$ENDIF}

procedure InitLibgit2;
procedure ShutdownLibgit2;

// Headers sourced and converted from https://github.com/libgit2/libgit2 and where all under the following licence
  (*
   * Copyright (C) the libgit2 contributors. All rights reserved.
   *
   * This file is part of libgit2, distributed under the GNU GPL v2 with
   * a Linking Exception. For full terms see the included COPYING file.
   *
   * https://github.com/libgit2/libgit2/blob/main/COPYING
    *)
{$I git2/version.inc}
{$I git2/common.inc}
{$I git2/types.inc}
{$I git2/buffer.inc}
{$I git2/oid.inc}
{$I git2/oidarray.inc}
{$I git2/strarray.inc}
{$I git2/repository.inc}
{$I git2/diff.inc}
{$I git2/object.inc}
{$I git2/annotated_commit.inc}
{$I git2/apply.inc}
{$I git2/attr.inc}
{$I git2/blame.inc}
{$I git2/blob.inc}
{$I git2/branch.inc}
{$I git2/cert.inc}
{$I git2/checkout.inc}
{$I git2/email.inc}
{$I git2/indexer.inc}
{$I git2/index.inc}
{$I git2/merge.inc}
{$I git2/cherrypick.inc}
{$I git2/pack.inc}
{$I git2/credential.inc}
{$I git2/credential_helpers.inc}
{$I git2/proxy.inc}
{$I git2/net.inc}
{$I git2/refspec.inc}
{$I git2/transport.inc}
{$I git2/remote.inc}
{$I git2/clone.inc}
{$I git2/commit.inc}
{$I git2/config.inc}
{$I git2/describe.inc}
{$I git2/errors.inc}
{$I git2/filter.inc}
{$I git2/global.inc}
{$I git2/graph.inc}
{$I git2/ignore.inc}
{$I git2/mailmap.inc}
{$I git2/message.inc}
{$I git2/notes.inc}
{$I git2/odb_backend.inc}
{$I git2/odb.inc}
{$I git2/patch.inc}
{$I git2/pathspec.inc}
{$I git2/rebase.inc}
{$I git2/refdb.inc}
{$I git2/reflog.inc}
{$I git2/refs.inc}
{$I git2/reset.inc}
{$I git2/revert.inc}
{$I git2/revparse.inc}
{$I git2/revwalk.inc}
{$I git2/signature.inc}
{$I git2/stash.inc}
{$I git2/status.inc}
{$I git2/submodule.inc}
{$I git2/tag.inc}
{$I git2/trace.inc}
{$I git2/transaction.inc}
{$I git2/tree.inc}
{$I git2/worktree.inc}

implementation

var
  Libgit2init: Boolean;

procedure InitLibgit2;
begin
  if not Libgit2init then
  begin
    Libgit2init := True;
    git_libgit2_init;
  end;
end;

procedure ShutdownLibgit2;
begin
  if Libgit2init then
  begin
    Libgit2init := False;
    git_libgit2_shutdown;
  end;
end;

{ attr }

function GIT_ATTR_IS_TRUE(attr: PAnsiChar): Boolean;
begin
  Result := git_attr_value(attr) = GIT_ATTR_VALUE_TRUE;
end;

function GIT_ATTR_IS_FALSE(attr: PAnsiChar): Boolean;
begin
  Result := git_attr_value(attr) = GIT_ATTR_VALUE_FALSE;
end;

function GIT_ATTR_IS_UNSPECIFIED(attr: PAnsiChar): Boolean;
begin
  Result := git_attr_value(attr) = GIT_ATTR_VALUE_UNSPECIFIED;
end;

function GIT_ATTR_HAS_VALUE(attr: PAnsiChar): Boolean;
begin
  Result := git_attr_value(attr) = GIT_ATTR_VALUE_STRING;
end;

{ index }

function GIT_INDEX_ENTRY_STAGE_GET(var E: git_index_entry): uint16_t;
begin
  Result := (E.flags and GIT_INDEX_ENTRY_STAGEMASK) shr GIT_INDEX_ENTRY_STAGESHIFT;
end;

procedure GIT_INDEX_ENTRY_STAGE_SET(var E: git_index_entry; S: uint16_t);
begin
  E.flags := (E.flags and not GIT_INDEX_ENTRY_STAGEMASK) or ((S and 3) shl GIT_INDEX_ENTRY_STAGESHIFT);
end;

{ submodule }

function GIT_SUBMODULE_STATUS_IS_UNMODIFIED(S: Integer): Boolean;
begin
  Result := (S and not GIT_SUBMODULE_STATUS__IN_FLAGS) = 0;
end;

function GIT_SUBMODULE_STATUS_IS_INDEX_UNMODIFIED(S: Integer): Boolean;
begin
  Result := (S and GIT_SUBMODULE_STATUS__INDEX_FLAGS) = 0;
end;

function GIT_SUBMODULE_STATUS_IS_WD_UNMODIFIED(S: Integer): Boolean;
begin
  Result := (S and GIT_SUBMODULE_STATUS__WD_FLAGS and not GIT_SUBMODULE_STATUS_WD_UNINITIALIZED) = 0;
end;

function GIT_SUBMODULE_STATUS_IS_WD_DIRTY(S: Integer): Boolean;
begin
  Result := (S and (GIT_SUBMODULE_STATUS_WD_INDEX_MODIFIED or GIT_SUBMODULE_STATUS_WD_WD_MODIFIED or
    GIT_SUBMODULE_STATUS_WD_UNTRACKED)) = 0;
end;

end.


