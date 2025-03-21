
// this file is generated — do not edit it


/// <reference types="@sveltejs/kit" />

/**
 * Environment variables [loaded by Vite](https://vitejs.dev/guide/env-and-mode.html#env-files) from `.env` files and `process.env`. Like [`$env/dynamic/private`](https://kit.svelte.dev/docs/modules#$env-dynamic-private), this module cannot be imported into client-side code. This module only includes variables that _do not_ begin with [`config.kit.env.publicPrefix`](https://kit.svelte.dev/docs/configuration#env) _and do_ start with [`config.kit.env.privatePrefix`](https://kit.svelte.dev/docs/configuration#env) (if configured).
 * 
 * _Unlike_ [`$env/dynamic/private`](https://kit.svelte.dev/docs/modules#$env-dynamic-private), the values exported from this module are statically injected into your bundle at build time, enabling optimisations like dead code elimination.
 * 
 * ```ts
 * import { API_KEY } from '$env/static/private';
 * ```
 * 
 * Note that all environment variables referenced in your code should be declared (for example in an `.env` file), even if they don't have a value until the app is deployed:
 * 
 * ```
 * MY_FEATURE_FLAG=""
 * ```
 * 
 * You can override `.env` values from the command line like so:
 * 
 * ```bash
 * MY_FEATURE_FLAG="enabled" npm run dev
 * ```
 */
declare module '$env/static/private' {
	export const SHELL: string;
	export const LSCOLORS: string;
	export const SESSION_MANAGER: string;
	export const USER_ZDOTDIR: string;
	export const QT_ACCESSIBILITY: string;
	export const COLORTERM: string;
	export const XDG_CONFIG_DIRS: string;
	export const LESS: string;
	export const XDG_SESSION_PATH: string;
	export const NVM_INC: string;
	export const XDG_MENU_PREFIX: string;
	export const TERM_PROGRAM_VERSION: string;
	export const XDG_CONFIG_DIRS_VSCODE_SNAP_ORIG: string;
	export const GDK_BACKEND_VSCODE_SNAP_ORIG: string;
	export const ICEAUTHORITY: string;
	export const FONTCONFIG_PATH: string;
	export const LANGUAGE: string;
	export const NODE: string;
	export const LC_ADDRESS: string;
	export const GIO_MODULE_DIR_VSCODE_SNAP_ORIG: string;
	export const LC_NAME: string;
	export const SSH_AUTH_SOCK: string;
	export const XDG_DATA_HOME: string;
	export const MEMORY_PRESSURE_WRITE: string;
	export const PYDEVD_DISABLE_FILE_VALIDATION: string;
	export const npm_config_local_prefix: string;
	export const DESKTOP_SESSION: string;
	export const LC_MONETARY: string;
	export const BAMF_DESKTOP_FILE_HINT: string;
	export const GTK_RC_FILES: string;
	export const NO_AT_BRIDGE: string;
	export const KDE_FORK_SLAVES: string;
	export const XDG_SEAT: string;
	export const PWD: string;
	export const GSETTINGS_SCHEMA_DIR: string;
	export const LOGNAME: string;
	export const XDG_SESSION_DESKTOP: string;
	export const GTK_EXE_PREFIX: string;
	export const XDG_SESSION_TYPE: string;
	export const SYSTEMD_EXEC_PID: string;
	export const _: string;
	export const BUNDLED_DEBUGPY_PATH: string;
	export const XAUTHORITY: string;
	export const VSCODE_GIT_ASKPASS_NODE: string;
	export const PICO_SDK_PATH: string;
	export const XKB_DEFAULT_MODEL: string;
	export const GTK2_RC_FILES: string;
	export const HOME: string;
	export const LANG: string;
	export const LC_PAPER: string;
	export const LS_COLORS: string;
	export const XDG_CURRENT_DESKTOP: string;
	export const npm_package_version: string;
	export const VIRTUAL_ENV: string;
	export const MEMORY_PRESSURE_WATCH: string;
	export const WAYLAND_DISPLAY: string;
	export const QT_EXCLUDE_GENERIC_BEARER: string;
	export const KCRASH_DUMP_ONLY: string;
	export const GIT_ASKPASS: string;
	export const XDG_SEAT_PATH: string;
	export const PERL5LIB: string;
	export const INVOCATION_ID: string;
	export const QTWEBENGINE_DICTIONARIES_PATH: string;
	export const MANAGERPID: string;
	export const CHROME_DESKTOP: string;
	export const KDE_SESSION_UID: string;
	export const NVM_DIR: string;
	export const VSCODE_GIT_ASKPASS_EXTRA_ARGS: string;
	export const XKB_DEFAULT_LAYOUT: string;
	export const GSETTINGS_SCHEMA_DIR_VSCODE_SNAP_ORIG: string;
	export const GTK_IM_MODULE_FILE_VSCODE_SNAP_ORIG: string;
	export const LESSCLOSE: string;
	export const XDG_SESSION_CLASS: string;
	export const LC_IDENTIFICATION: string;
	export const TERM: string;
	export const npm_package_name: string;
	export const ZSH: string;
	export const GTK_PATH: string;
	export const PERL_MB_OPT: string;
	export const ZDOTDIR: string;
	export const LESSOPEN: string;
	export const USER: string;
	export const GTK_PATH_VSCODE_SNAP_ORIG: string;
	export const VSCODE_GIT_IPC_HANDLE: string;
	export const QT_WAYLAND_RECONNECT: string;
	export const KDE_SESSION_VERSION: string;
	export const PAM_KWALLET5_LOGIN: string;
	export const PERL_MM_OPT: string;
	export const DISPLAY: string;
	export const npm_lifecycle_event: string;
	export const SHLVL: string;
	export const NVM_CD_FLAGS: string;
	export const LOCPATH: string;
	export const GSM_SKIP_SSH_AGENT_WORKAROUND: string;
	export const PAGER: string;
	export const LC_TELEPHONE: string;
	export const MOZ_USE_XINPUT2: string;
	export const XDG_DATA_HOME_VSCODE_SNAP_ORIG: string;
	export const LC_MEASUREMENT: string;
	export const XDG_VTNR: string;
	export const GTK_EXE_PREFIX_VSCODE_SNAP_ORIG: string;
	export const XDG_SESSION_ID: string;
	export const VIRTUAL_ENV_PROMPT: string;
	export const npm_config_user_agent: string;
	export const npm_execpath: string;
	export const XDG_RUNTIME_DIR: string;
	export const XDG_DATA_DIRS_VSCODE_SNAP_ORIG: string;
	export const DEBUGINFOD_URLS: string;
	export const npm_package_json: string;
	export const LC_TIME: string;
	export const BUN_INSTALL: string;
	export const FONTCONFIG_FILE: string;
	export const VSCODE_GIT_ASKPASS_MAIN: string;
	export const QT_AUTO_SCREEN_SCALE_FACTOR: string;
	export const JOURNAL_STREAM: string;
	export const XDG_DATA_DIRS: string;
	export const PERL_LOCAL_LIB_ROOT: string;
	export const KDE_FULL_SESSION: string;
	export const GDK_BACKEND: string;
	export const PATH: string;
	export const ORIGINAL_XDG_CURRENT_DESKTOP: string;
	export const DBUS_SESSION_BUS_ADDRESS: string;
	export const GTK_IM_MODULE_FILE: string;
	export const KDE_APPLICATIONS_AS_SCOPE: string;
	export const NVM_BIN: string;
	export const LOCPATH_VSCODE_SNAP_ORIG: string;
	export const GIO_MODULE_DIR: string;
	export const npm_node_execpath: string;
	export const LC_NUMERIC: string;
	export const OLDPWD: string;
	export const TERM_PROGRAM: string;
	export const NODE_ENV: string;
}

/**
 * Similar to [`$env/static/private`](https://kit.svelte.dev/docs/modules#$env-static-private), except that it only includes environment variables that begin with [`config.kit.env.publicPrefix`](https://kit.svelte.dev/docs/configuration#env) (which defaults to `PUBLIC_`), and can therefore safely be exposed to client-side code.
 * 
 * Values are replaced statically at build time.
 * 
 * ```ts
 * import { PUBLIC_BASE_URL } from '$env/static/public';
 * ```
 */
declare module '$env/static/public' {
	
}

/**
 * This module provides access to runtime environment variables, as defined by the platform you're running on. For example if you're using [`adapter-node`](https://github.com/sveltejs/kit/tree/master/packages/adapter-node) (or running [`vite preview`](https://kit.svelte.dev/docs/cli)), this is equivalent to `process.env`. This module only includes variables that _do not_ begin with [`config.kit.env.publicPrefix`](https://kit.svelte.dev/docs/configuration#env) _and do_ start with [`config.kit.env.privatePrefix`](https://kit.svelte.dev/docs/configuration#env) (if configured).
 * 
 * This module cannot be imported into client-side code.
 * 
 * ```ts
 * import { env } from '$env/dynamic/private';
 * console.log(env.DEPLOYMENT_SPECIFIC_VARIABLE);
 * ```
 * 
 * > In `dev`, `$env/dynamic` always includes environment variables from `.env`. In `prod`, this behavior will depend on your adapter.
 */
declare module '$env/dynamic/private' {
	export const env: {
		SHELL: string;
		LSCOLORS: string;
		SESSION_MANAGER: string;
		USER_ZDOTDIR: string;
		QT_ACCESSIBILITY: string;
		COLORTERM: string;
		XDG_CONFIG_DIRS: string;
		LESS: string;
		XDG_SESSION_PATH: string;
		NVM_INC: string;
		XDG_MENU_PREFIX: string;
		TERM_PROGRAM_VERSION: string;
		XDG_CONFIG_DIRS_VSCODE_SNAP_ORIG: string;
		GDK_BACKEND_VSCODE_SNAP_ORIG: string;
		ICEAUTHORITY: string;
		FONTCONFIG_PATH: string;
		LANGUAGE: string;
		NODE: string;
		LC_ADDRESS: string;
		GIO_MODULE_DIR_VSCODE_SNAP_ORIG: string;
		LC_NAME: string;
		SSH_AUTH_SOCK: string;
		XDG_DATA_HOME: string;
		MEMORY_PRESSURE_WRITE: string;
		PYDEVD_DISABLE_FILE_VALIDATION: string;
		npm_config_local_prefix: string;
		DESKTOP_SESSION: string;
		LC_MONETARY: string;
		BAMF_DESKTOP_FILE_HINT: string;
		GTK_RC_FILES: string;
		NO_AT_BRIDGE: string;
		KDE_FORK_SLAVES: string;
		XDG_SEAT: string;
		PWD: string;
		GSETTINGS_SCHEMA_DIR: string;
		LOGNAME: string;
		XDG_SESSION_DESKTOP: string;
		GTK_EXE_PREFIX: string;
		XDG_SESSION_TYPE: string;
		SYSTEMD_EXEC_PID: string;
		_: string;
		BUNDLED_DEBUGPY_PATH: string;
		XAUTHORITY: string;
		VSCODE_GIT_ASKPASS_NODE: string;
		PICO_SDK_PATH: string;
		XKB_DEFAULT_MODEL: string;
		GTK2_RC_FILES: string;
		HOME: string;
		LANG: string;
		LC_PAPER: string;
		LS_COLORS: string;
		XDG_CURRENT_DESKTOP: string;
		npm_package_version: string;
		VIRTUAL_ENV: string;
		MEMORY_PRESSURE_WATCH: string;
		WAYLAND_DISPLAY: string;
		QT_EXCLUDE_GENERIC_BEARER: string;
		KCRASH_DUMP_ONLY: string;
		GIT_ASKPASS: string;
		XDG_SEAT_PATH: string;
		PERL5LIB: string;
		INVOCATION_ID: string;
		QTWEBENGINE_DICTIONARIES_PATH: string;
		MANAGERPID: string;
		CHROME_DESKTOP: string;
		KDE_SESSION_UID: string;
		NVM_DIR: string;
		VSCODE_GIT_ASKPASS_EXTRA_ARGS: string;
		XKB_DEFAULT_LAYOUT: string;
		GSETTINGS_SCHEMA_DIR_VSCODE_SNAP_ORIG: string;
		GTK_IM_MODULE_FILE_VSCODE_SNAP_ORIG: string;
		LESSCLOSE: string;
		XDG_SESSION_CLASS: string;
		LC_IDENTIFICATION: string;
		TERM: string;
		npm_package_name: string;
		ZSH: string;
		GTK_PATH: string;
		PERL_MB_OPT: string;
		ZDOTDIR: string;
		LESSOPEN: string;
		USER: string;
		GTK_PATH_VSCODE_SNAP_ORIG: string;
		VSCODE_GIT_IPC_HANDLE: string;
		QT_WAYLAND_RECONNECT: string;
		KDE_SESSION_VERSION: string;
		PAM_KWALLET5_LOGIN: string;
		PERL_MM_OPT: string;
		DISPLAY: string;
		npm_lifecycle_event: string;
		SHLVL: string;
		NVM_CD_FLAGS: string;
		LOCPATH: string;
		GSM_SKIP_SSH_AGENT_WORKAROUND: string;
		PAGER: string;
		LC_TELEPHONE: string;
		MOZ_USE_XINPUT2: string;
		XDG_DATA_HOME_VSCODE_SNAP_ORIG: string;
		LC_MEASUREMENT: string;
		XDG_VTNR: string;
		GTK_EXE_PREFIX_VSCODE_SNAP_ORIG: string;
		XDG_SESSION_ID: string;
		VIRTUAL_ENV_PROMPT: string;
		npm_config_user_agent: string;
		npm_execpath: string;
		XDG_RUNTIME_DIR: string;
		XDG_DATA_DIRS_VSCODE_SNAP_ORIG: string;
		DEBUGINFOD_URLS: string;
		npm_package_json: string;
		LC_TIME: string;
		BUN_INSTALL: string;
		FONTCONFIG_FILE: string;
		VSCODE_GIT_ASKPASS_MAIN: string;
		QT_AUTO_SCREEN_SCALE_FACTOR: string;
		JOURNAL_STREAM: string;
		XDG_DATA_DIRS: string;
		PERL_LOCAL_LIB_ROOT: string;
		KDE_FULL_SESSION: string;
		GDK_BACKEND: string;
		PATH: string;
		ORIGINAL_XDG_CURRENT_DESKTOP: string;
		DBUS_SESSION_BUS_ADDRESS: string;
		GTK_IM_MODULE_FILE: string;
		KDE_APPLICATIONS_AS_SCOPE: string;
		NVM_BIN: string;
		LOCPATH_VSCODE_SNAP_ORIG: string;
		GIO_MODULE_DIR: string;
		npm_node_execpath: string;
		LC_NUMERIC: string;
		OLDPWD: string;
		TERM_PROGRAM: string;
		NODE_ENV: string;
		[key: `PUBLIC_${string}`]: undefined;
		[key: `${string}`]: string | undefined;
	}
}

/**
 * Similar to [`$env/dynamic/private`](https://kit.svelte.dev/docs/modules#$env-dynamic-private), but only includes variables that begin with [`config.kit.env.publicPrefix`](https://kit.svelte.dev/docs/configuration#env) (which defaults to `PUBLIC_`), and can therefore safely be exposed to client-side code.
 * 
 * Note that public dynamic environment variables must all be sent from the server to the client, causing larger network requests — when possible, use `$env/static/public` instead.
 * 
 * ```ts
 * import { env } from '$env/dynamic/public';
 * console.log(env.PUBLIC_DEPLOYMENT_SPECIFIC_VARIABLE);
 * ```
 */
declare module '$env/dynamic/public' {
	export const env: {
		[key: `PUBLIC_${string}`]: string | undefined;
	}
}
