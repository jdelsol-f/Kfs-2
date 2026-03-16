{ pkgs ? import <nixpkgs> {} }:



pkgs
.mkShell {
  
#packages = with pkgs; [
#        libguestfs 
#        libguestfs-with-appliance
#];

nativeBuildInputs =
    
with pkgs; [
        pkgsCross
.i686-embedded.buildPackages.gcc
    
];
}

