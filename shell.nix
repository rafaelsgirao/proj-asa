{ pkgs ? import <nixpkgs> { } }:
pkgs.mkShell {
  buildInputs = with pkgs;
    [
      gdb
      gcc9
    ];
}
