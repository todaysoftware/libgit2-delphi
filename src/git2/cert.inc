(**
 * @file git2/cert.h
 * @brief Git certificate objects
 * @defgroup git_cert Certificate objects
 * @ingroup Git
 * @{
  *)

(**
 * Type of host certificate structure that is passed to the check callback
  *)

const
  (**
	 * No information about the certificate is available. This may
	 * happen when using curl.
	  *)
  GIT_CERT_NONE = 0;
  (**
	 * The `data` argument to the callback will be a pointer to
	 * the DER-encoded data.
	  *)
  GIT_CERT_X509_ = 1;
  (**
	 * The `data` argument to the callback will be a pointer to a
	 * `git_cert_hostkey` structure.
	  *)
  GIT_CERT_HOSTKEY_LIBSSH2 = 2;
  (**
	 * The `data` argument to the callback will be a pointer to a
	 * `git_strarray` with `name:content` strings containing
	 * information about the certificate. This is used when using
	 * curl.
	  *)
  GIT_CERT_STRARRAY = 3;
type
  git_cert_t = Integer;

  (**
 * Parent type for `git_cert_hostkey` and `git_cert_x509`.
  *)

  git_cert = record
    (**
	 * Type of certificate. A `GIT_CERT_` value.
	  *)
    cert_type : git_cert_t;
  end;
  Pgit_cert = ^git_cert;

  (**
 * Callback for the user's custom certificate checks.
 *
 * @param cert The host certificate
 * @param valid Whether the libgit2 checks (OpenSSL or WinHTTP) think
 * this certificate is valid
 * @param host Hostname of the host libgit2 connected to
 * @param payload Payload provided by the caller
 * @return 0 to proceed with the connection, < 0 to fail the connection
 *         or > 0 to indicate that the callback refused to act and that
 *         the existing validity determination should be honored
  *)

type
  git_transport_certificate_check_cb = function(cert: Pgit_cert; valid: Integer;
    host: PAnsiChar; payload: Pointer): Integer; cdecl;


(**
 * Type of SSH host fingerprint
  *)

const
  (** MD5 is available  *)
  GIT_CERT_SSH_MD5 = ( 1 shl 0 );
  (** SHA-1 is available  *)
  GIT_CERT_SSH_SHA1 = ( 1 shl 1 );
  (** SHA-256 is available  *)
  GIT_CERT_SSH_SHA256 = ( 1 shl 2 );
type
  git_cert_ssh_t = Integer;

  (**
 * Hostkey information taken from libssh2
  *)

  git_cert_hostkey = record
    parent : git_cert;  (**< The parent cert  *)
    (**
	 * A hostkey type from libssh2, either
	 * `GIT_CERT_SSH_MD5` or `GIT_CERT_SSH_SHA1`
	  *)
    type_ : git_cert_ssh_t;
    (**
	 * Hostkey hash. If type has `GIT_CERT_SSH_MD5` set, this will
	 * have the MD5 hash of the hostkey.
	  *)
    hash_md5 : array [0..15] of Byte;
    (**
	 * Hostkey hash. If type has `GIT_CERT_SSH_SHA1` set, this will
	 * have the SHA-1 hash of the hostkey.
	  *)
    hash_sha1 : array [0..19] of Byte;
    (**
	 * Hostkey hash. If type has `GIT_CERT_SSH_SHA256` set, this will
	 * have the SHA-256 hash of the hostkey.
	  *)
    hash_sha256 : array [0..31] of Byte;
  end;
  Pgit_cert_hostkey = ^git_cert_hostkey;

  (**
 * X.509 certificate information
  *)

  git_cert_x509 = record
    parent : git_cert;  (**< The parent cert  *)
    (**
	 * Pointer to the X.509 certificate data
	  *)
    data : Pointer;
    (**
	 * Length of the memory block pointed to by `data`.
	  *)
    len : size_t;
  end;
  Pgit_cert_x509 = ^git_cert_x509;

  (** @}  *)

