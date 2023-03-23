{ pkgs ? import <nixpkgs> { } }:
pkgs.mkShell {
  buildInputs = with pkgs;
    [
      cmake
      gdb
      gcc9
      valgrind
      clang-tools

      # Jupyter notebook dependencies
      python310Packages.seaborn
      python310Packages.jupyter
      python310Packages.ipykernel
      python310Packages.numpy
      python310Packages.pandas

    ];
}
