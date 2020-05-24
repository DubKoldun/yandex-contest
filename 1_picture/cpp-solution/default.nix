/* with import <nixpkgs> {};
stdenv.mkDerivation {
    name = "dev-environment";
    src = ./.;
    buildPhase = ''
        make
    '';
    builder = "${bash}/bin/bash";
    args = [ ./builder.sh ];

    buildInputs = [ pkgconfig leptonica opencv tesseract cmake gnumake gcc ];
    builder = "${cmake}/bin/cmake";
} */


with import <nixpkgs> {};
stdenv.mkDerivation {
    name = "dev-environment"; # Probably put a more meaningful name here
    src = ./.;
    buildInputs = [ pkgconfig zlib cmake leptonica opencv tesseract4 gcc ];
}
