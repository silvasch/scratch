# scratch

Quickly open a scratch file to write some things down. 

## Usage

Run `scratch` to create a file in a temporary directory and open it in your
`$EDITOR`. If `$EDITOR` is not set, `nano` is used.

## Building and Running

To build the project, use `just build`. This will put your resulting executable
in `out/scratch`.

You can also directly build *and* run the project using `just run`.

## Building and Running Using Nix

This project also includes a `flake.nix` that provides a package to build and run
your program using `nix build` and `nix run`.

## Generating compile_commands.json

The `justfile` also contains a recipe for generating `compile_commands.json`
called `generate-compile-commands`. Run this before editing your project
to get LSP completions from `clang`.
