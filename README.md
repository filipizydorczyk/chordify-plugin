# 🎼 Whst is this plugin

This plugin's goal is to produce chords in selected scale based on played note. I am creating it basically to learn how to code music plugins therefore I am planing to actually support VST build later. This project is based on [example](https://lv2plug.in/book/#_fifths) lv2 plugin on lv2's page

# 🔨 Building

On linux to build go with

```sh
cmake .
make
```

Then you should have direcotry `build/chordify.lv2`. On linux there is post build command that also automaticly copy this directory to `~/.lv2` so that you can instantly test it at any host. You can also run script `./scripts/install-build.sh`.

There is no windows scripts at the moment.

Since I use **CMake** you should be able to go with any IDE and compiler.

---

**TO DO:**

-   [ ] make VST build
-   [ ] add UI
-   [ ] test on windows
-   [ ] update gitignore for diffrent possible IDEs
-   [ ] code refactor (naming convetion, changing to pointers etc.)
-   [ ] add bypassing created output
-   [ ] figure out what `FIFTHS_URIS_H` define is used for
-   [x] decide if I still need fetaures that are used
-   [ ] make sure notes are not going out of octave
-   [ ] consider making scale a singleton
-   [ ] make scale class know how many notes it has
