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
