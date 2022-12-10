{ pkgs ? import <nixpkgs> { } }:
pkgs.mkShell {
  buildInputs = with pkgs;
    [
      cmake
      gdb
      gcc9
      valgrind
      clang-tools
    ];
}
