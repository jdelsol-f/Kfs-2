{ pkgs ? import <nixpkgs> {} }:



pkgs
.mkShell {

nativeBuildInputs =
    
with pkgs; [
        pkgsCross
.i686-embedded.buildPackages.gcc
        pkgs.mtools
        pkgs.grub2
        pkgs.qemu
];
}

